#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIN_WIDTH 900
#define WIN_HEIGHT 600
#define PANEL_TOP 120
#define PANEL_BOTTOM 500
#define PANEL_LEFT 60
#define PANEL_RIGHT 840
#define BAR_GAP 6
#define MAX_SIZE 100

// Sorting arrays for test cases
int test_cases[][MAX_SIZE] = {
    {5,3,8,1},
    {9,7,5,3},
    {1,1,1},
    {},
    {10},
    {30,25,11,9,7,5,3,99,80,76,44,78,88,99,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50}
};
int test_sizes[] = {4,4,3,0,1,50};
const char *test_labels[] = {
    "[5,3,8,1] Bubble",
    "[9,7,5,3] Quick",
    "[1,1,1] Bubble",
    "[] Edge",
    "[10] Edge",
    "[Many] Perf"
};
int current_test = 0;

int arr[MAX_SIZE];
int n = 0;
int comparisons = 0, speed = 15;
char algo[16] = "Bubble";
int sorting = 0, done = 0;
int slider_drag = 0;

SDL_Window *win;
SDL_Renderer *ren;
TTF_Font *font;

// UI positions
SDL_FRect btn_bubble = {370, 70, 110, 35};
SDL_FRect btn_quick = {500, 70, 110, 35};
SDL_FRect btn_reset = {630, 70, 110, 35};
SDL_FRect btn_prev = {60, 70, 60, 35};
SDL_FRect btn_next = {130, 70, 60, 35};
SDL_FRect slider = {220, 70, 120, 35};

// Utility: Render text
void render_text(const char *msg, int x, int y, SDL_Color color, int center) {
    SDL_Surface *surf = TTF_RenderText_Blended(font, msg, strlen(msg), color);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);
    float w = (float)surf->w, h = (float)surf->h;
    SDL_FRect dest = {(float)x, (float)y, w, h};
    if(center) dest.x -= w/2;
    SDL_RenderTexture(ren, tex, NULL, &dest);
    SDL_DestroyTexture(tex);
    SDL_DestroySurface(surf);
}

// Utility: Button rendering
void render_button(SDL_FRect btn, const char *label, int selected) {
    SDL_Color c = selected ? (SDL_Color){0,128,255,255} : (SDL_Color){220,220,220,255};
    SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, c.a);
    SDL_RenderFillRect(ren, &btn);
    SDL_SetRenderDrawColor(ren, 0,0,0,255);
    SDL_RenderRect(ren, &btn);
    render_text(label, btn.x+btn.w/2, btn.y+btn.h/2-10, (SDL_Color){0,0,0,255}, 1);
}

// Utility: Comparison counter
void render_counter() {
    char cmp[64];
    sprintf(cmp,"Comparisons: %d", comparisons);
    render_text(cmp, 770, 30, (SDL_Color){64,64,64,255}, 0);
}

// Utility: Speed slider
void render_speed_slider() {
    SDL_SetRenderDrawColor(ren,220,220,220,255);
    SDL_RenderFillRect(ren, &slider);
    SDL_SetRenderDrawColor(ren,0,0,0,255);
    SDL_RenderRect(ren, &slider);
    int knobx = slider.x + (speed*slider.w/30);
    SDL_FRect knob = {knobx-8, slider.y+3, 16, slider.h-6};
    SDL_SetRenderDrawColor(ren,0,128,255,255);
    SDL_RenderFillRect(ren, &knob);
    SDL_SetRenderDrawColor(ren,0,0,0,255);
    SDL_RenderRect(ren, &knob);

    char s[32];
    sprintf(s,"Speed: %d", speed);
    render_text(s, slider.x+slider.w/2, slider.y+slider.h+2, (SDL_Color){0,0,0,255}, 1);
}

// Utility: Array value rendering
void render_array_values(int width, int maxv, int base, float x) {
    SDL_Color col = {0,0,0,255};
    for(int i=0;i<n;i++) {
        int val = arr[i];
        char num[12];
        sprintf(num,"%d",val);
        float h = (val*1.0/maxv)*(PANEL_BOTTOM-PANEL_TOP-40);
        render_text(num, x+width/2, base-h-22, col, 1);
        x += width + BAR_GAP;
    }
}

// Draw everything
void render_all(int highlight1, int highlight2) {
    SDL_SetRenderDrawColor(ren,255,255,255,255);
    SDL_RenderClear(ren);

    // Title
    render_text("Sorting Visualization", WIN_WIDTH/2, 20, (SDL_Color){0,0,0,255}, 1);

    // Buttons
    render_button(btn_prev, "<", 0);
    render_button(btn_next, ">", 0);
    render_button(btn_bubble, "Bubble Sort", strcmp(algo,"Bubble")==0);
    render_button(btn_quick, "Quick Sort", strcmp(algo,"Quick")==0);
    render_button(btn_reset, "Reset", 0);

    // Test case label
    render_text(test_labels[current_test], 200, 32, (SDL_Color){128,0,128,255}, 0);

    // Speed slider
    render_speed_slider();

    // Comparisons
    render_counter();

    // Visualization panel
    SDL_FRect panel = {PANEL_LEFT, PANEL_TOP, PANEL_RIGHT-PANEL_LEFT, PANEL_BOTTOM-PANEL_TOP};
    SDL_SetRenderDrawColor(ren,230,230,230,255);
    SDL_RenderFillRect(ren, &panel);
    SDL_SetRenderDrawColor(ren,0,0,0,255);
    SDL_RenderRect(ren, &panel);

    // Draw array bars
    int i, maxv = 1;
    for(i=0;i<n;i++) if(arr[i]>maxv) maxv = arr[i];
    int width = n>0 ? (PANEL_RIGHT-PANEL_LEFT-n*BAR_GAP)/n : 30;
    if(width<5) width=5;
    int base = PANEL_BOTTOM-10;
    float x = PANEL_LEFT + BAR_GAP;
    for(i=0;i<n;i++) {
        float h = (arr[i]*1.0/maxv)*(PANEL_BOTTOM-PANEL_TOP-40);
        SDL_FRect bar = {x, base-h, width, h};
        SDL_Color c = (i==highlight1||i==highlight2) ? (SDL_Color){255,64,64,255} : (SDL_Color){0,192,255,255};
        SDL_SetRenderDrawColor(ren, c.r,c.g,c.b,c.a);
        SDL_RenderFillRect(ren, &bar);
        SDL_SetRenderDrawColor(ren,0,0,0,255);
        SDL_RenderRect(ren, &bar);
        x += width + BAR_GAP;
    }
    // Draw array values above bars
    x = PANEL_LEFT + BAR_GAP;
    render_array_values(width, maxv, base, x);

    SDL_RenderPresent(ren);
}

void sdl_delay() {
    SDL_Event e;
    Uint32 start = SDL_GetTicks();
    int ms = 50 + (31-speed)*9;
    while(SDL_GetTicks()-start < ms) {
        while(SDL_PollEvent(&e)) {
            if(e.type==SDL_EVENT_QUIT) exit(0);
        }
        SDL_Delay(5);
    }
}

// Sorting algorithms
void bubble_sort() {
    int i, j;
    for(i=0; i<n-1; ++i) {
        for(j=0; j<n-i-1; ++j) {
            comparisons++;
            render_all(j, j+1);
            sdl_delay();
            if(arr[j]>arr[j+1]) {
                int t=arr[j]; arr[j]=arr[j+1]; arr[j+1]=t;
                render_all(j, j+1);
                sdl_delay();
            }
        }
    }
    render_all(-1,-1);
}

int partition(int low, int high) {
    int pivot = arr[high], i = low-1, j;
    for(j=low;j<high;++j) {
        comparisons++;
        render_all(j, high);
        sdl_delay();
        if(arr[j]<pivot) {
            ++i;
            int t=arr[i]; arr[i]=arr[j]; arr[j]=t;
            render_all(i, j);
            sdl_delay();
        }
    }
    int t=arr[i+1]; arr[i+1]=arr[high]; arr[high]=t;
    render_all(i+1, high);
    sdl_delay();
    return i+1;
}

void quick_sort(int low, int high) {
    if(low<high) {
        int pi=partition(low,high);
        quick_sort(low,pi-1);
        quick_sort(pi+1,high);
    }
}

void reset_arr() {
    memcpy(arr, test_cases[current_test], sizeof(int)*test_sizes[current_test]);
    n = test_sizes[current_test];
    comparisons = 0;
    sorting = 0;
    done = 0;
    // Set default algorithm for test case
    if(strstr(test_labels[current_test],"Quick")) strcpy(algo,"Quick");
    else strcpy(algo,"Bubble");
}

int hit_btn(SDL_FRect btn, int mx, int my) {
    return mx>=btn.x && mx<=btn.x+btn.w && my>=btn.y && my<=btn.y+btn.h;
}

int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    win = SDL_CreateWindow("Sorting Visualization", WIN_WIDTH, WIN_HEIGHT, 0);
    ren = SDL_CreateRenderer(win, NULL);
    font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 22); // Use a system font

    reset_arr();
    render_all(-1,-1);

    SDL_Event e;
    while(1) {
        while(SDL_PollEvent(&e)) {
            if(e.type==SDL_EVENT_QUIT) goto end;
            if(e.type==SDL_EVENT_MOUSE_BUTTON_DOWN) {
                int mx = e.button.x, my = e.button.y;
                if(hit_btn(btn_bubble,mx,my) && !sorting) {
                    strcpy(algo,"Bubble");
                    render_all(-1,-1);
                }
                if(hit_btn(btn_quick,mx,my) && !sorting) {
                    strcpy(algo,"Quick");
                    render_all(-1,-1);
                }
                if(hit_btn(btn_reset,mx,my) && !sorting) {
                    reset_arr();
                    render_all(-1,-1);
                }
                if(hit_btn(btn_prev,mx,my) && !sorting) {
                    if(current_test>0) current_test--;
                    reset_arr();
                    render_all(-1,-1);
                }
                if(hit_btn(btn_next,mx,my) && !sorting) {
                    if(current_test < (sizeof(test_sizes)/sizeof(test_sizes[0]))-1) current_test++;
                    reset_arr();
                    render_all(-1,-1);
                }
                if(hit_btn(slider,mx,my)) slider_drag=1;
                // Start sort when clicking visualization panel if not sorting
                SDL_FRect panel = {PANEL_LEFT, PANEL_TOP, PANEL_RIGHT-PANEL_LEFT, PANEL_BOTTOM-PANEL_TOP};
                if(mx>=panel.x && mx<=panel.x+panel.w && my>=panel.y && my<=panel.y+panel.h && !sorting && n>0) {
                    sorting=1;
                    comparisons=0;
                    render_all(-1,-1);
                    if(strcmp(algo,"Bubble")==0) bubble_sort();
                    else quick_sort(0,n-1);
                    sorting=0; done=1;
                    render_all(-1,-1);
                }
            }
            if(e.type==SDL_EVENT_MOUSE_BUTTON_UP) slider_drag=0;
            if(e.type==SDL_EVENT_MOUSE_MOTION) {
                if(slider_drag) {
                    int mx = e.motion.x;
                    if(mx<slider.x) mx=slider.x;
                    if(mx>slider.x+slider.w) mx=slider.x+slider.w;
                    speed = ((mx-slider.x)/(float)slider.w)*30;
                    if(speed<1) speed=1;
                    if(speed>30) speed=30;
                    render_all(-1,-1);
                }
            }
        }
        SDL_Delay(10);
    }
end:
    TTF_CloseFont(font);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
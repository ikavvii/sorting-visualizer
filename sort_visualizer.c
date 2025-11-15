#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define MAX_SIZE 50
#define MIN_SPEED 1
#define MAX_SPEED 10

typedef struct {
    int array[MAX_SIZE];
    int size;
    int comparisons;
    int swaps;
    int speed;
    int selected_algo;
    int is_sorting;
} SortState;

typedef enum {
    BUBBLE_SORT = 0,
    SELECTION_SORT = 1,
    MERGE_SORT = 2,
    QUICK_SORT = 3
} Algorithm;

const char* algo_names[] = {
    "Bubble Sort",
    "Selection Sort",
    "Merge Sort",
    "Quick Sort"
};

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clear_screen() {
    system("cls");
}

void set_color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void hide_cursor() {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void draw_ui(SortState* state) {
    gotoxy(0, 0);
    set_color(15);
    
    printf("================================================================================\n");
    printf("                     SORTING ALGORITHM VISUALIZER                             \n");
    printf("================================================================================\n");
    
    printf("\n Algorithm: ");
    set_color(11);
    printf("%-20s", algo_names[state->selected_algo]);
    set_color(15);
    printf(" (UP/DOWN to change)");
    
    printf("\n Speed: ");
    set_color(10);
    for (int i = 0; i < state->speed; i++) printf("#");
    for (int i = state->speed; i < MAX_SPEED; i++) printf("-");
    set_color(15);
    printf(" (LEFT/RIGHT to adjust)");
    
    printf("\n\n Comparisons: ");
    set_color(14);
    printf("%-6d", state->comparisons);
    set_color(15);
    printf("  |  Swaps: ");
    set_color(14);
    printf("%-6d", state->swaps);
    set_color(15);
    
    printf("\n\n");
    printf("================================================================================\n");
    printf("                          MEMORY VISUALIZATION                                \n");
    printf("================================================================================\n");
}

void draw_array(SortState* state, int highlight1, int highlight2, int pivot) {
    gotoxy(0, 11);
    
    set_color(15);
    printf("\n Array Indices:\n ");
    for (int i = 0; i < state->size; i++) {
        printf("[%2d]", i);
    }
    printf("\n\n");
    
    set_color(7);
    printf(" Memory Layout:\n ");
    set_color(15);
    for (int i = 0; i < state->size; i++) {
        if (i == highlight1 || i == highlight2) {
            set_color(12);  // Red for comparing/swapping
            printf(" %3d", state->array[i]);
            set_color(15);
        } else if (i == pivot) {
            set_color(13);  // Magenta for pivot
            printf(" %3d", state->array[i]);
            set_color(15);
        } else {
            set_color(11);  // Cyan for normal
            printf(" %3d", state->array[i]);
            set_color(15);
        }
    }
    printf("\n\n");
    
    if (highlight1 >= 0 || highlight2 >= 0 || pivot >= 0) {
        printf(" Indicators:\n ");
        for (int i = 0; i < state->size; i++) {
            if (i == highlight1 || i == highlight2) {
                set_color(12);
                printf("  ^ ");
                set_color(15);
            } else if (i == pivot) {
                set_color(13);
                printf("  P ");
                set_color(15);
            } else {
                printf("    ");
            }
        }
        printf("\n");
    } else {
        printf(" Indicators:\n");
        printf("                                                                                \n");
    }
    
    printf("\n");
    set_color(7);
    printf(" Status: ");
    set_color(15);
    if (highlight1 >= 0 && highlight2 >= 0) {
        printf("Comparing indices %d and %d (values: %d vs %d)                              ", 
               highlight1, highlight2, state->array[highlight1], state->array[highlight2]);
    } else {
        printf("Idle                                                                        ");
    }
    printf("\n\n");
    
    set_color(7);
    printf(" Legend: ");
    set_color(12);
    printf("[RED] Comparing/Swapping  ");
    set_color(13);
    printf("[MAGENTA] Pivot  ");
    set_color(11);
    printf("[CYAN] Normal\n");
    set_color(15);
    
    printf("\n Controls: [SPACE] Start/Pause  [R] Reset  [ESC] Exit\n");
}

void delay_ms(int speed) {
    int delay = (MAX_SPEED - speed + 1) * 50;
    Sleep(delay);
}

void swap(int* a, int* b, SortState* state) {
    int temp = *a;
    *a = *b;
    *b = temp;
    state->swaps++;
}

void bubble_sort(SortState* state) {
    for (int i = 0; i < state->size - 1 && state->is_sorting; i++) {
        for (int j = 0; j < state->size - i - 1 && state->is_sorting; j++) {
            state->comparisons++;
            draw_ui(state);
            draw_array(state, j, j + 1, -1);
            delay_ms(state->speed);
            
            if (state->array[j] > state->array[j + 1]) {
                swap(&state->array[j], &state->array[j + 1], state);
                draw_ui(state);
                draw_array(state, j, j + 1, -1);
                delay_ms(state->speed);
            }
            
            if (_kbhit()) {
                int ch = _getch();
                if (ch == 27) {
                    state->is_sorting = 0;
                    return;
                } else if (ch == ' ') {
                    while (!_kbhit()) Sleep(100);
                    ch = _getch();
                    if (ch == 27) {
                        state->is_sorting = 0;
                        return;
                    }
                }
            }
        }
    }
    draw_ui(state);
    draw_array(state, -1, -1, -1);
}

void selection_sort(SortState* state) {
    for (int i = 0; i < state->size - 1 && state->is_sorting; i++) {
        int min_idx = i;
        
        for (int j = i + 1; j < state->size && state->is_sorting; j++) {
            state->comparisons++;
            draw_ui(state);
            draw_array(state, i, j, min_idx);
            delay_ms(state->speed);
            
            if (state->array[j] < state->array[min_idx]) {
                min_idx = j;
            }
            
            if (_kbhit()) {
                int ch = _getch();
                if (ch == 27) {
                    state->is_sorting = 0;
                    return;
                } else if (ch == ' ') {
                    while (!_kbhit()) Sleep(100);
                    ch = _getch();
                    if (ch == 27) {
                        state->is_sorting = 0;
                        return;
                    }
                }
            }
        }
        
        if (min_idx != i) {
            swap(&state->array[min_idx], &state->array[i], state);
            draw_ui(state);
            draw_array(state, i, min_idx, -1);
            delay_ms(state->speed);
        }
    }
    draw_ui(state);
    draw_array(state, -1, -1, -1);
}

void merge_display(int arr[], int l, int m, int r, SortState* state) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    
    int L[MAX_SIZE], R[MAX_SIZE];
    
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    
    i = 0;
    j = 0;
    k = l;
    
    while (i < n1 && j < n2 && state->is_sorting) {
        state->comparisons++;
        draw_ui(state);
        draw_array(state, l + i, m + 1 + j, -1);
        delay_ms(state->speed);
        
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        state->swaps++;
        k++;
        
        draw_ui(state);
        draw_array(state, k - 1, -1, -1);
        delay_ms(state->speed);
        
        if (_kbhit()) {
            int ch = _getch();
            if (ch == 27) {
                state->is_sorting = 0;
                return;
            } else if (ch == ' ') {
                while (!_kbhit()) Sleep(100);
                ch = _getch();
                if (ch == 27) {
                    state->is_sorting = 0;
                    return;
                }
            }
        }
    }
    
    while (i < n1 && state->is_sorting) {
        arr[k] = L[i];
        state->swaps++;
        i++;
        k++;
        draw_ui(state);
        draw_array(state, k - 1, -1, -1);
        delay_ms(state->speed);
    }
    
    while (j < n2 && state->is_sorting) {
        arr[k] = R[j];
        state->swaps++;
        j++;
        k++;
        draw_ui(state);
        draw_array(state, k - 1, -1, -1);
        delay_ms(state->speed);
    }
}

void merge_sort_helper(int arr[], int l, int r, SortState* state) {
    if (l < r && state->is_sorting) {
        int m = l + (r - l) / 2;
        
        merge_sort_helper(arr, l, m, state);
        merge_sort_helper(arr, m + 1, r, state);
        merge_display(arr, l, m, r, state);
    }
}

void merge_sort(SortState* state) {
    merge_sort_helper(state->array, 0, state->size - 1, state);
    draw_ui(state);
    draw_array(state, -1, -1, -1);
}

int partition(int arr[], int low, int high, SortState* state) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high && state->is_sorting; j++) {
        state->comparisons++;
        draw_ui(state);
        draw_array(state, j, i + 1, high);
        delay_ms(state->speed);
        
        if (arr[j] < pivot) {
            i++;
            if (i != j) {
                swap(&arr[i], &arr[j], state);
                draw_ui(state);
                draw_array(state, i, j, high);
                delay_ms(state->speed);
            }
        }
        
        if (_kbhit()) {
            int ch = _getch();
            if (ch == 27) {
                state->is_sorting = 0;
                return i + 1;
            } else if (ch == ' ') {
                while (!_kbhit()) Sleep(100);
                ch = _getch();
                if (ch == 27) {
                    state->is_sorting = 0;
                    return i + 1;
                }
            }
        }
    }
    
    if (i + 1 != high) {
        swap(&arr[i + 1], &arr[high], state);
        draw_ui(state);
        draw_array(state, i + 1, high, -1);
        delay_ms(state->speed);
    }
    
    return i + 1;
}

void quick_sort_helper(int arr[], int low, int high, SortState* state) {
    if (low < high && state->is_sorting) {
        int pi = partition(arr, low, high, state);
        
        quick_sort_helper(arr, low, pi - 1, state);
        quick_sort_helper(arr, pi + 1, high, state);
    }
}

void quick_sort(SortState* state) {
    quick_sort_helper(state->array, 0, state->size - 1, state);
    draw_ui(state);
    draw_array(state, -1, -1, -1);
}

void input_array(SortState* state) {
    clear_screen();
    set_color(15);
    printf("================================================================================\n");
    printf("                            INPUT ARRAY DATA                                  \n");
    printf("================================================================================\n\n");
    
    printf(" Enter array size (1-%d): ", MAX_SIZE);
    scanf("%d", &state->size);
    
    if (state->size < 1) state->size = 1;
    if (state->size > MAX_SIZE) state->size = MAX_SIZE;
    
    printf("\n Choose input method:\n");
    printf(" 1. Manual input\n");
    printf(" 2. Random generation\n");
    printf(" Choice: ");
    
    int choice;
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("\n Enter %d space-separated elements: ", state->size);
        for (int i = 0; i < state->size; i++) {
            scanf("%d", &state->array[i]);
        }
    } else {
        printf("\n Generating random array...\n");
        for (int i = 0; i < state->size; i++) {
            state->array[i] = rand() % 100 + 1;
        }
        
        printf(" Generated array: ");
        for (int i = 0; i < state->size; i++) {
            printf("%d ", state->array[i]);
        }
        printf("\n");
        Sleep(2000);
    }
    
    state->comparisons = 0;
    state->swaps = 0;
}

void reset_state(SortState* state, int original_array[]) {
    for (int i = 0; i < state->size; i++) {
        state->array[i] = original_array[i];
    }
    state->comparisons = 0;
    state->swaps = 0;
    state->is_sorting = 0;
}

int main() {
    SortState state;
    int original_array[MAX_SIZE];
    
    state.speed = 5;
    state.selected_algo = 0;
    state.is_sorting = 0;
    
    hide_cursor();
    
    input_array(&state);
    
    for (int i = 0; i < state.size; i++) {
        original_array[i] = state.array[i];
    }
    
    clear_screen();
    draw_ui(&state);
    draw_array(&state, -1, -1, -1);
    
    while (1) {
        if (_kbhit()) {
            int ch = _getch();
            
            if (ch == 224) {
                ch = _getch();
                
                if (ch == 72) {
                    state.selected_algo = (state.selected_algo - 1 + 4) % 4;
                    reset_state(&state, original_array);
                    clear_screen();
                    draw_ui(&state);
                    draw_array(&state, -1, -1, -1);
                }
                else if (ch == 80) {
                    state.selected_algo = (state.selected_algo + 1) % 4;
                    reset_state(&state, original_array);
                    clear_screen();
                    draw_ui(&state);
                    draw_array(&state, -1, -1, -1);
                }
                else if (ch == 75) {
                    if (state.speed > MIN_SPEED) {
                        state.speed--;
                        draw_ui(&state);
                        draw_array(&state, -1, -1, -1);
                    }
                }
                else if (ch == 77) {
                    if (state.speed < MAX_SPEED) {
                        state.speed++;
                        draw_ui(&state);
                        draw_array(&state, -1, -1, -1);
                    }
                }
            }
            else if (ch == ' ') {
                if (!state.is_sorting) {
                    state.is_sorting = 1;
                    
                    switch (state.selected_algo) {
                        case BUBBLE_SORT:
                            bubble_sort(&state);
                            break;
                        case SELECTION_SORT:
                            selection_sort(&state);
                            break;
                        case MERGE_SORT:
                            merge_sort(&state);
                            break;
                        case QUICK_SORT:
                            quick_sort(&state);
                            break;
                    }
                    
                    state.is_sorting = 0;
                }
            }
            else if (ch == 'r' || ch == 'R') {
                reset_state(&state, original_array);
                clear_screen();
                draw_ui(&state);
                draw_array(&state, -1, -1, -1);
            }
            else if (ch == 27) {
                break;
            }
        }
        
        Sleep(50);
    }
    
    clear_screen();
    set_color(15);
    printf("\n Thank you for using the Sorting Visualizer!\n\n");
    
    return 0;
}

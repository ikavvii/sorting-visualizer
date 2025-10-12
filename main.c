#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define RESET "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"

#define MAX_SPEED_LEVEL 5
#define MIN_SPEED_LEVEL 1

void clearScreen();
void delay(int milliseconds);
void printArray(int arr[], int n, int sortedIndex, int currentIndex,
                int comparisons, int swaps, int isAfterSwap, int speed);
void bubbleSort(int arr[], int size, int speed);
void clearInputBuffer();

int main()
{
    int *arr = NULL;
    int *originalArr = NULL;
    int size = 0;
    float floatNum;
    int speed, algorithmChoice, isInputOk = 0;
    char userActive = 'Y';

    printf("\n------ SORTING VISUALIZER ------\n\n");
    printf("Press enter or any key to start...\n");
    clearInputBuffer();

    printf("Input Array (space-separated positive integers, press Enter to finish) :-\n");

    while (scanf("%f", &floatNum) == 1)
    {

        int *temp = realloc(arr, (size + 1) * sizeof(int));

        if (temp == NULL)
        {
            printf("\nMemory allocation failed.");
            free(arr);
            return 1;
        }

        arr = temp;
        int num = (int)floatNum;
        if (num != floatNum)
        {
            printf("Warning: Non-integer value %.2f truncated to %d.\n", floatNum, num);
        }
        arr[size++] = num;

        int c = getchar();

        if (c == '\n' || c == EOF)
            break;
    }

    if (size == 0)
    {
        printf("No input provided. Exiting...\n");
        return 0;
    }

    originalArr = malloc(size * sizeof(int));
    if (originalArr == NULL)
    {
        printf("\nMemory allocation failed.");
        free(arr);
        return 1;
    }

    for (int i = 0; i < size; i++)
    {
        originalArr[i] = arr[i];
    }

    do
    {
        printf("\nVisualization Speed Level (1-5): ");
        isInputOk = scanf("%d", &speed);

        if (isInputOk != 1)
        {
            printf("Invalid input. Setting speed to default level %d.\n", MIN_SPEED_LEVEL);
            speed = MIN_SPEED_LEVEL;
            clearInputBuffer();
        }

        speed = (speed < MIN_SPEED_LEVEL) ? MIN_SPEED_LEVEL : (speed > MAX_SPEED_LEVEL) ? MAX_SPEED_LEVEL
                                                                                        : speed;

        printf("\nSpeed level set to %d.\n", speed);
        printf("Select algorithm:\n");
        printf("1. Bubble Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Insertion Sort\n");
        printf("4. Quick Sort\n");
        printf("Enter choice (1-4): ");
        isInputOk = scanf("%d", &algorithmChoice);

        if (isInputOk != 1)
        {
            printf("Invalid input. Please enter a number between 1 and 4.\n");
            clearInputBuffer();
            continue;
        }

        // Restore original array for new sort

        for (int i = 0; i < size; i++)
        {
            arr[i] = originalArr[i];
        }

        switch (algorithmChoice)
        {
        case 1:
            printf("Bubble Sort selected.\n");
            bubbleSort(arr, size, speed);
            break;
        case 2:
            printf("Selection Sort selected.\n");
            // yet to be implemented
            break;
        case 3:
            printf("Insertion Sort selected.\n");
            // yet to be implemented
            break;
        case 4:
            printf("Quick Sort selected.\n");
            // yet to be implemented
            break;
        default:
            printf("Invalid choice. Please enter a number between 1 and 4.\n");
            break;
        }

        printf("\n");
        printf("Original Array: ");
        for (int i = 0; i < size; i++)
        {
            printf("%d ", originalArr[i]);
        }
        printf("\nDo you want to try different algorithms (Y/N): ");
        scanf(" %c", &userActive);

    } while (userActive == 'Y' || userActive == 'y');

    free(arr);
    free(originalArr);

    clearInputBuffer();
    printf("\nPress enter or any key to exit...\n");
    getchar();

    return 0;
}

void clearScreen()
{
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Unix/Linux/macOS
#endif
}

void delay(int milliseconds)
{
    long pause;
    clock_t now, then;

    pause = milliseconds * (CLOCKS_PER_SEC / 1000);
    now = then = clock();
    while ((now - then) < pause)
    {
        now = clock();
    }
}

void printArray(int arr[], int n, int sortedIndex, int currentIndex,
                int comparisons, int swaps, int isAfterSwap, int speed)
{
    clearScreen();

    printf("Output Array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    if (n <= 10)
    {
        printf("Comparisons: %d, Swaps: %d\n", comparisons, swaps);

        for (int i = 0; i < n; i++)
        {
            if (i == currentIndex || i == currentIndex - 1)
                if (isAfterSwap)
                    printf(YELLOW);
                else
                    printf(RED);

            else if (i >= sortedIndex)
                printf(GREEN);
            else
                printf(BLUE);

            printf("%3d: ", arr[i]);
            for (int j = 0; j < arr[i]; j++)
                printf("*");
            printf("\n");
        }
        printf(RESET);
        printf("------\n");

        delay((MAX_SPEED_LEVEL - speed + MIN_SPEED_LEVEL) * 400);
    }
}

void bubbleSort(int arr[], int size, int speed)
{
    int newn, i, temp;
    int n = size;
    int comparisons = 0, swaps = 0;

    printArray(arr, size, n, -1, comparisons, swaps, 0, speed);
    do
    {
        newn = 0;
        for (i = 1; i <= n - 1; i++)
        {
            comparisons++;

            printArray(arr, size, n, i, comparisons, swaps, 0, speed);

            if (arr[i - 1] > arr[i])
            {
                temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;

                swaps++;

                printArray(arr, size, n, i, comparisons, swaps, 1, speed);
                newn = i;
            }
            printArray(arr, size, n, i, comparisons, swaps, 1, speed);
        }
        n = newn;

    } while (n > 0);
    printArray(arr, size, 0, -1, comparisons, swaps, 0, speed);
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

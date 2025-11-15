# Sorting Algorithm Visualizer

A comprehensive console-based C program that provides animated visualization of popular sorting algorithms with real-time statistics tracking.

## Features

- **4 Sorting Algorithms**: Bubble Sort, Selection Sort, Merge Sort, Quick Sort
- **Visual Representation**: Bar chart visualization with color-coded elements
- **Memory Layout View**: Shows array state in memory during sorting
- **Interactive Controls**:
  - Algorithm selection dropdown (↑↓ arrow keys)
  - Speed slider (←→ arrow keys) - 10 levels
  - Start/Pause functionality (SPACE)
  - Reset to original array (R)
  - Exit program (ESC)
- **Real-time Counters**:
  - Comparison counter
  - Swap counter
- **Flexible Input**:
  - Manual array input
  - Random array generation
  - Configurable array size (1-50 elements)

## Compilation

### Windows (GCC/MinGW)
```bash
gcc sort_visualizer.c -o sort_visualizer.exe
```

### Windows (MSVC)
```bash
cl sort_visualizer.c
```

## Usage

1. Run the compiled executable:
   ```bash
   sort_visualizer.exe
   ```

2. Enter array size and choose input method:
   - Manual input: Enter each element individually
   - Random generation: Automatically generates random numbers

3. Use the interactive interface:
   - **↑/↓ Arrow Keys**: Switch between sorting algorithms
   - **←/→ Arrow Keys**: Adjust animation speed
   - **SPACE**: Start/pause sorting animation
   - **R**: Reset array to original state
   - **ESC**: Exit program

## Color Legend

- **Blue (██)**: Normal elements
- **Red (██)**: Elements being compared or swapped
- **Magenta (██)**: Pivot element (Quick Sort)

## Example

```
╔══════════════════════════════════════════════════════════════════════════════╗
║                     SORTING ALGORITHM VISUALIZER                             ║
╚══════════════════════════════════════════════════════════════════════════════╝

 Algorithm: Bubble Sort (↑↓ to change)
 Speed: █████░░░░░ (←→ to adjust)

 Comparisons: 45  │  Swaps: 12

╔══════════════════════════════════════════════════════════════════════════════╗
║                          VISUALIZATION PANEL                                 ║
╚══════════════════════════════════════════════════════════════════════════════╝

 [Visual bar chart showing sorting progress]
 
 Memory Layout: [5, 12, 8, 23, 15, ...]
 
 Legend: █ Comparing/Swapping  █ Pivot  █ Normal
 
 Controls: [SPACE] Start/Pause  [R] Reset  [ESC] Exit
```

## Algorithm Details

### Bubble Sort
- Time Complexity: O(n²)
- Space Complexity: O(1)
- Stable: Yes

### Selection Sort
- Time Complexity: O(n²)
- Space Complexity: O(1)
- Stable: No

### Merge Sort
- Time Complexity: O(n log n)
- Space Complexity: O(n)
- Stable: Yes

### Quick Sort
- Time Complexity: O(n log n) average, O(n²) worst
- Space Complexity: O(log n)
- Stable: No

## Requirements

- Windows OS (uses Windows API for console manipulation)
- GCC/MinGW or MSVC compiler
- Console with ANSI color support

## Notes

- Maximum array size is limited to 50 elements for optimal visualization
- The program uses Windows-specific functions (windows.h, conio.h)
- Speed levels range from 1 (slowest) to 10 (fastest)
- Press SPACE during sorting to pause, and SPACE again to resume

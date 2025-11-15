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

## Analysis

| Algorithm        | Time Complexity (Best/Average/Worst) | Space Complexity | Stability | Adaptive | # Comparisons (Worst) | # Swaps (Worst) | Application | When Best/Worst Case Occur | Short Description | Other Notes |
|------------------|--------------------------------------|------------------|-----------|----------|----------------------|-----------------|-------------|--------------------------|-------------------|------------|
| **Bubble Sort**  | Best: O(n)<br>Avg/Worst: O(n²)       | O(1)             | Yes       | Yes      | O(n²)               | O(n²)           | Educational, simple small lists | Best: Already sorted<br>Worst: Reverse sorted | Repeatedly swaps adjacent out-of-order elements ("bubbles" largest/smallest to end each pass) | Early exit possible; rarely used in practice beyond teaching |
| **Selection Sort** | O(n²) for all cases                 | O(1)             | No        | No       | O(n²)               | O(n)             | Small static datasets | No adaptivity: always quadratic | Repeatedly selects minimum from unsorted portion, swaps with first unsorted position | Minimizes swaps; good for write-limited storage |
| **Merge Sort**   | O(n log n) for all cases             | O(n)             | Yes       | No       | ~O(n log n)         | O(n) (copies)     | Large lists, linked lists, external sorting | Always splits & merges, so same for any input | Recursively splits list into halves, sorts, merges sorted halves | Good for linked lists and external sort; extra space needed |
| **Quicksort**    | Best: O(n log n)<br>Avg: O(n log n)<br>Worst: O(n²) | O(log n) average (stack)<br>O(n) worst | Not usually | No       | O(n²) (worst)         | O(n²) (worst)                 | Fast in-practice, generic sort, in-memory | Best: Balanced splits<br>Worst: Poor pivot (already/reverse sorted, all same with naive pivot) | Picks a pivot, partitions into < and > pivot, recurses | Randomized or better pivot selection reduces risk of worst case |

**Legend & Additional Notes:**
- *Stability*: Whether equal keys retain initial order. Merge, Bubble are stable; Selection and most Quicksort implementations are not.
- *Adaptive*: Takes advantage of existing order (Bubble and Insertion are adaptive, others are not). Bubble can run in O(n) if input sorted and early exit used.
- *Space Complexity*: Merge Sort uses O(n) extra for merge arrays; Quicksort is usually in-place but can use O(n) in worst case due to stack.
- *Comparisons/Swaps*: Selection makes fewer swaps than Bubble; Merge Sort moves elements but doesn't "swap".
- *Applications*: Bubble and Selection are mainly for teaching, Merge Sort is strong for linked lists and disk-based sorting, Quicksort is a general-purpose, fast in-memory sort.
- *Best/Worst Case*: Quicksort's worst case is rare with good pivots (median-of-three, random). Bubble’s best case only happens if already sorted and the algorithm includes early stopping.


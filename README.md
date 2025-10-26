# Sorting Visualizer

## Status: 
I think it will be very hard to implement graphics libraries like SDL3.
We better work with console for easier implementation. 
I don't think we can finish on time, if we spend lot of time in graphics libs.
We need to prep and modify slides, learn and study the algorithms, and implment the visualizations also.

## Scope

**Implement** Bubble, Selection, Merge, Quick Sort with animations.

## Test Cases

- [5,3,8,1] → Bubble sort steps until [1,3,5,8]
- [9,7,5,3] → Quick sort → [3,5,7,9]
- [1,1,1] → [1,1,1]
- Edge: Empty list → []
- Edge: Single element [10] → [10]
- Edge: Large dataset → Performance check

## UI Design

Input array box, dropdown for algorithm, visualization panel.

## WOW Factor

Bars moving with animations; speed slider + comparison counter.


## Resources
[Sorting.ppt](https://cse.iitkgp.ac.in/~pds/semester/2025a/slides/12-Sorting.pdf)

## Note

* To compile sdl_sort_visualizer.c use,
>gcc sdl_sort_visualizer.c -o sdl_sort_visualizer.exe \
  -I SDL3-3.2.24/x86_64-w64-mingw32/include \
  -I SDL3_ttf-3.2.2/x86_64-w64-mingw32/include \
  -L SDL3-3.2.24/x86_64-w64-mingw32/lib \
  -L SDL3_ttf-3.2.2/x86_64-w64-mingw32/lib \
  -lSDL3 -lSDL3_ttf -mwindows

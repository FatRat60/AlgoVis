# AlgoVis - Kyle Hultgren

## Features

- Press 1 - 4 in to switch between sorting methods
- Implemented Sorts:
    - Bubble Sort
    - Merge Sort
    - Selection Sort
    - Insertion Sort
- Press R to shufffle the array
- Space Bar begins the sort
- 3 threads: Render, Event handling, Sorting
- Clicking github url in top right opens the repo in browser
- K can be pressed during a sort to stop the sort prematurely
- Fun animation played upon sort finishing
- Displays number of swaps and array accesses in top left

## Build Instructions

Fetch Content used for SFML making building locally as easy as cloning this repo
and running the compile.sh script given that CMake is properly installed and
configured on your machine. Upon successful build the compile script will run 
the project for you. The executable will be found in AlgoVis/build/

## Example Pictures

![Shuffled array awaiting to be sorted](/resources/pre_sort_shuffled.jpg)
![Screenshot taken in the middle of bubble sort](/resources/mid_shuffle_bubble.jpg)
![Screenshot taken post sort. Animation has finished to all boxes are green](/resources/post_sort.jpg)
![Screenshot taken after aborting insertion sort early using K](/resources/insertion_killed.jpg)

## Libraries used

- [SFML](https://www.sfml-dev.org/index.php) used for the rendering 
- [CMake](https://cmake.org/) used for building project

## External Code Used

- [string_format() code](https://ideone.com/jr7M5a)
- [cross-platform URL opening](https://stackoverflow.com/questions/17347950/how-do-i-open-a-url-from-c)

## Development Roadblocks

Originally the program allowed for window resizing however I ran into synchronization issues when resizing
during a sort due to the event thread needing to recalculate the box sizes to fit the new window. I attempted
to use a mutex to lock the array and stall the sort thread while the event thread handled the resizing but
even still the boxes visually got messed up after the resize so I decided to remove resizing and limit the 
window to 800 x 600.
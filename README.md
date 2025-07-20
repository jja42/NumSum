# NumSum - My Boot.Dev Personal Project

## Overview

**Num Sum** is a logic-based puzzle grid game written in C using SDL for rendering.  
Outside of the SDL Rendering, everything is self made. 
Yes, even the JSON parser which took around half of my work time.

## Goal
Your objective is to identify which numbers belong on the grid.

Each column and row has a target sum:
- **Above each column** is the total of all valid numbers in that column.
- **To the left of each row** is the total of all valid numbers in that row.

Use logic and cross-referencing to deduce which numbers are correct.  
Focus on how each number lines up with both its **row** and **column** sums.

## How to Play
1. After clicking Start, choose a grid size (3x3 to 8x8).
2. Analyze the row and column sums to figure out which numbers are valid.
3. Mark valid numbers to reduce the displayed sum for the associated rows and columns.
4. You can also erase invalid numbers to help with clarity and organization.
5. Marked Numbers will be highlighted Gold.
6. You start with 4 Lives. You **Lose a Life** if:
   - You attempt to mark an invalid number. It will be Highlighted Red.
   - You attempt to erase a valid number. It will be Highlighted Red.
7. You **Win** by marking all valid numbers and reducing all sums to zero.
8. You **Lose** if you run out of lives.

## How to Run
**FIRST**
Make sure you have the following installed:
- SDL2 and SDL_ttf
```sudo apt install libsdl2-dev libsdl2-ttf-dev build-essential```

1. Clone the Repository: ```git clone https://github.com/jja42/NumSum/```
2. CD into Folder: ```cd NumSum```     
3. Compile with: ```gcc -o num_sum.exe *.c `sdl2-config --cflags --libs` -lSDL2_ttf```
4. Run it: ```./num_sum```

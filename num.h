#ifndef NUM_H
#define NUM_H

#include "list.h"

#define ROW 0
#define COL 1

typedef struct Sum{
    list_t* valid_nums;
    int value;
}Sum;

typedef struct Num{
    int value;
    int x;
    int y;
    bool is_valid;
}Num;

//Will hold an in-game representation of the grid to iterate through as well as info about the grid
//such as its dimensions and the sums associated with it
typedef struct Grid{
    list_t* grid; //Double List [X,Y]
    int columns; //X
    int rows;   //Y
    list_t* sums_c; //the sums for each column, size of X
    list_t* sums_r; //the sums for each row, size of Y
}Grid;

//Create a grid with x columns and y rows
Grid* create_grid(int x, int y);

//Creates a number at position x,y with value of val
Num* create_num(int val, int x, int y);

//creates a sum and the valid nums that make up that sum
Sum* create_sum(int val, int num_count);

//make sure we don't have dupes when generating our sum's split points
int check_dupe(int num, int arr[], int size);

//function to compare our values for sorting
int compare(const void *n1, const void *n2);

//Since we're generating sums and their parts, we'll do that for either the rows/columns and then
//derive the sums for the columns/rows dependant on which we generated first
//Side Note: Maybe I should've generated the grid first?
Sum* derive_sum(Grid* grid, int c_r);

#endif
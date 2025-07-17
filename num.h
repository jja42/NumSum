#ifndef NUM_H
#define NUM_H

#include "list.h"

#define ROW 0
#define COL 1

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
    int size;
    list_t* sums_c; //the sums for each column, size of X
    list_t* sums_r; //the sums for each row, size of Y
}Grid;

//Create a grid with size columns and size rows
Grid* create_grid(int size);

//fill out our grid. use create nums to create random plausible sum components. make rows and columns. set valid numbers. derive sums. 
void generate_grid(Grid* grid);

//Creates a number at position x,y with value of val. is_valid set to false by default
Num* create_num(int val, int x, int y);

//creates a list of num_count numbers that add to a sum
list_t* create_nums(int sum, int num_count);

//make sure we don't have dupes when generating our list's split points
int check_dupe(int num, int arr[], int size);

//function to compare our values for sorting
int compare(const void *n1, const void *n2);

#endif
#ifndef NUM_H
#define NUM_H

#include "list.h"

typedef struct Sum{
    list_t* valid_nums;
    int value;
}Sum;

typedef struct Num{
    int value;
    int x;
    int y;
}Num;

typedef struct Grid{
    list_t* grid; //Double List [X,Y]
    int columns; //X
    int rows;   //Y
    list_t* sums; //Sums mark each row and column
}Grid;

//Create a grid with x columns and y rows
Grid* create_grid(int x, int y);

//Creates a number at position x,y with value of val
Num* create_num(int val, int x, int y);

//stores a sum and the value nums that make up that sum
Sum* create_sum(int value, list_t* valid);


#endif
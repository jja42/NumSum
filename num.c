#include "num.h"
#include <stdlib.h>

Grid* create_grid(int size){
    Grid* g = malloc(sizeof(Grid));
    
    //Handle Malloc Error
    if (g == NULL) {
        printf("Failed to Allocate Grid.\n");
        return NULL;
    }

    list_t* grid = new_list(size);
   
    //Handle Malloc Error
    if (grid == NULL) {
        printf("Failed to Allocate Grid List.\n");
        return NULL;
    }

    //Generate our numbers
    for(int i = 0; i < size; i++){
        
        int rand_num = rand() % (size - 1) + 1;
        
        list_t* section_1 = create_nums(rand_num,size/2);
        list_t* section_2 = create_nums(rand_num,size/2);

        list_t* col = list_join(section_1,section_2);
        
        //Handle Malloc Error
        if (col == NULL) {
            printf("Failed to Allocate Grid List.\n");
            return NULL;
        }

        grid->data[i] = col;
    }

    g->size = size;

    return g;
}

//fill out our grid. use create nums to create random plausible sum components. make rows and columns. set valid numbers. derive sums. 
void generate_grid(Grid* grid){
    return;
}

//Creates a number at position x,y with value of val. is_valid set to false by default
Num* create_num(int val, int x, int y){
    Num* n = malloc(sizeof(Num));
    
    //Handle Malloc Error
    if (n == NULL) {
        printf("Failed to Allocate Num.\n");
        return NULL;
    }

    return n;
}


list_t* create_nums(int val, int num_count){
    list_t* nums = new_list(val);

    //Handle Malloc Error
    if (nums == NULL) {
        printf("Failed to Allocate Num List.\n");
        return NULL;
    }

    //to split into num_count parts we must do that many splits minus 1
    int splits = num_count - 1;

    //declare our arrays for splitting
    int split_arr[splits];
    int parts[num_count];

    int i = 0;

    while (i< splits)
    {
        //Generate a number between 1 and val minus 1
        int rand_num = rand() % (val - 1) + 1;   // Modulo gives us 0 through value - 2. +1 gives us 1 through value

        //Check for dupe rand_num in our split_arr
        int b = check_dupe(rand_num,split_arr,i);
        
        //if so retry
        if(b == 1){
            continue;
        }
        //Otherwise continue

        //add rand_num to our array
        split_arr[i] = rand_num;

        //rand_num will become an effective index into our sum as an array.

        i++;
    }

    //with our splits done, it's now time to generate our actual parts

    //first we'll sort our splits
    qsort(split_arr, splits, sizeof(int), compare);

    //set up a reference to our last split point
    //start at 0
    int last_split = 0;

    //iterate through our parts array except the last index
    for (int i = 0; i < num_count - 1; i++) {

        //our value becomes the difference between the last split and our split point
        //for our first split point, this is just the value of the split point
        //ie: if our next split is 18 and our last split was 12, our part is 6
        //since our splits break into sections that total to our sum
        //this ensures that we get a perfect range of numbers that add to our sum
        parts[i] = split_arr[i] - last_split;
        last_split = split_arr[i];
    }
    //our last part is from our last split to our total value
    //ie if our total is 20 and our last split is 17, our last part is 3
    parts[num_count - 1] = val - last_split;

    for(int p = 0; p<num_count; p++){
        list_add(nums, parts[p]);
    }

    return nums;
}

int check_dupe(int num, int arr[], int size){
    //loop through our array and check for a dupe
    for (int n = 0; n < size; n++) {
        if (arr[n] == num){
            //if true
            return 1;
        }
    }
    //if false
    return 0;
}


int compare(const void *n1, const void *n2) {
    //cast our values to int pointers
    //derefrence them
    //return the difference
    //qsort can use that to sort them
    return (*(int *)n1 - *(int *)n2);
}
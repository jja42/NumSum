#include "num.h"
#include <stdlib.h>

Sum* create_sum(int val, int num_count){
    Sum* s = malloc(sizeof(Sum));
    
    //Handle Malloc Error
    if (s == NULL) {
    printf("Failed to Allocate Sum.\n");
    return NULL;
    }

    s->value = val;

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

    list_t* valid = new_list(val);

    //Handle Malloc Error
    if (valid == NULL) {
    free(s);
    printf("Failed to Allocate Valid Num List for Sum.\n");
    return NULL;
    }

    for(int p = 0; p<num_count; p++){
        list_add(valid, parts[p]);
    }

    s->valid_nums = valid;

    return s;
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

Sum* derive_sum(Grid* grid, int c_r){
    if(c_r == ROW){

    }
    if(c_r == COL){

    }

    printf("2nd Argument passed to Derive Sum is not an Accepted Value");
    return NULL;
}
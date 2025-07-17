#include "num.h"
#include <stdlib.h>
#include <stdio.h>

Grid* create_grid(int size){
    Grid* g = malloc(sizeof(Grid));
    
    //Handle Malloc Error
    if (g == NULL) {
        printf("Failed to Allocate Grid.\n");
        return NULL;
    }

    list_t* rows = new_list(size);
   
    //Handle Malloc Error
    if (rows == NULL) {
        printf("Failed to Allocate Grid List.\n");
        return NULL;
    }

    list_t* sum_r = new_list(size);
   
    //Handle Malloc Error
    if (sum_r == NULL) {
        printf("Failed to Allocate Grid List.\n");
        return NULL;
    }

    list_t* sum_c = new_list(size);
   
    //Handle Malloc Error
    if (sum_c == NULL) {
        printf("Failed to Allocate Grid List.\n");
        return NULL;
    }

    g->size = size;
    g->grid = rows;
    g->sums_c = sum_c;
    g->sums_r = sum_r;

    generate_grid(g);

    return g;
}

void generate_grid(Grid* g){
    int size = g->size;

    //Generate our numbers
    for(int i = 0; i < size; i++){
        
        int max_size =  size * 2;
        int min_size = size/2 + 1;
        //generate random number. modulo our max gives 0 through max - 1. Add 1 for 0 through max. 
        //minus min for the modulo and add it back after to give us the correct lower bound
        int rand_num = rand() % (max_size - min_size) + min_size;
        
        //generate twice to provide plausible invalid nums
        list_t* section_1 = create_nums(rand_num,size/2);
        list_t* section_2 = create_nums(rand_num,size/2);

        list_t* col = list_join(section_1,section_2);
        
        //Handle Malloc Error
        if (col == NULL) {
            printf("Failed to Generate Grid.\n");
            return;
        }

        list_add(g->grid,col);
    }

    //Set valid numbers randomly
    for(int row = 0; row < size; row++){  
        //init array with our indices
        int index_arr[size];
        for (int i = 0; i < size; i++) index_arr[i] = i;
        shuffle(index_arr, size);

        int max_size =  (size/2) + 1;
        int min_size = 2;
    
        int valid_count = rand() % (max_size - min_size + 1) + min_size;

        //Mark shuffled list as valid up to count
        for (int i = 0; i < valid_count; i++) {
            list_t* row_list = (list_t*)g->grid->data[row];
            Num* n = (Num*)row_list->data[index_arr[i]];
            n->is_valid = true;
        }
    }

    //finally calculate our sums

    //start with rows
    for(int row = 0; row < size; row++){  
        list_t* valid_nums = new_list(1);

        //Handle Malloc Error
        if (valid_nums == NULL) {
            printf("Failed to Generate Grid.\n");
            return;
        }

        //get all the valid nums from each column in our row
        list_t* column = (list_t*)g->grid->data[row];
        for(int col = 0; col < size; col++){
            Num* n = (Num*)column->data[col];
            if(n->is_valid){
                list_add(valid_nums,n);
            }
        }

        int* sum = malloc(sizeof(int));

        *sum = 0;

        //Handle Malloc Error
        if (sum == NULL) {
            printf("Failed to Generate Grid.\n");
            return;
        }

        for(int i = 0; i<valid_nums->count; i++){
            Num* n = (Num*)valid_nums->data[i];
            *sum += n->value;
        }

        list_add(g->sums_r, sum);


        free_list(valid_nums);
    }


    //then columns
    for(int col = 0; col < size; col++){  
        list_t* valid_nums = new_list(1);

        //Handle Malloc Error
        if (valid_nums == NULL) {
            printf("Failed to Generate Grid.\n");
            return;
        }

        //loop through our rows
        for(int row = 0; row < size; row++){
            //get all the valid nums from only the designated column in each row
            list_t* column = (list_t*)g->grid->data[row];
            Num* n = (Num*)column->data[col];
            if(n->is_valid){
                list_add(valid_nums,n);
            }
        }

        int* sum = malloc(sizeof(int));

        *sum = 0;

        //Handle Malloc Error
        if (sum == NULL) {
            printf("Failed to Generate Grid.\n");
            return;
        }

        for(int i = 0; i<valid_nums->count; i++){
            Num* n = (Num*)valid_nums->data[i];
            *sum += n->value;
        }

        list_add(g->sums_c, sum);

        free_list(valid_nums);
    }
}

Num* create_num(int val){
    Num* n = malloc(sizeof(Num));
    
    //Handle Malloc Error
    if (n == NULL) {
        printf("Failed to Allocate Num.\n");
        return NULL;
    }
    
    n->value = val;

    return n;
}


list_t* create_nums(int val, int num_count){
    list_t* nums = new_list(num_count);

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
        Num* n = create_num(parts[p]);
        list_add(nums, n);
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

void shuffle(int* arr, int size){
    //loop through, pick a random index and shuffle
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void free_grid(Grid* g){
    for(int j = 0; j< g->size; j++){
        int* sum_c = (int*)g->sums_c->data[j];
        int* sum_r = (int*)g->sums_r->data[j];
        free(sum_c);
        free(sum_r);
    }
    free_list(g->sums_c);
    free_list(g->sums_r);

    list_t* rows = g->grid;
    for(int i = 0; i< g->size; i++){
        list_t* column = (list_t*)rows->data[i];
        for(int j = 0; j< g->size; j++){
            Num* n = (Num*)column->data[j];
            free(n);
        }
        free_list(column);
    }
    free_list(g->grid);
    free(g);
}


void print_grid(Grid* g){
    printf("   ");

    for(int c = 0; c< g->size; c++){
        int* sum = (int*)g->sums_c->data[c];
        printf("_%d_ ", *sum);
    }

    printf("\n");

    list_t* rows = g->grid;
    for(int i = 0; i< g->size; i++){
        int* sum = (int*)g->sums_r->data[i];
        printf("%d| ", *sum);
        list_t* column = (list_t*)rows->data[i];
        for(int j = 0; j< g->size; j++){
            Num* n = (Num*)column->data[j];
            printf("[%d] ",n->value);
        }
        printf("\n");
    }
}
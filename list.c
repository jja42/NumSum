#include "list.h"
#include <stdlib.h>
#include <stdio.h>


void free_list(list_t* list) {
  if (list == NULL) {
    return;
  }

  if (list->data != NULL) {
    free(list->data);
  }

  free(list);
}

void list_remove(list_t* list, void* item){

    //search through list for data item
     for (int i = 0; i < list->count; i++) {
        //if exists, set it to null and reduce count
        if(list->data[i] == item){
            list->data[i] = NULL;
            list->count--;
            return;
        }
    }
    printf("Could Not Remove Item.\n");
    return;
}

void list_add(list_t* list, void* item) {
  //resize list if too small
  if (list->count == list->capacity) {
    resize_list(list);
  }

  //if slot is null, change it to item data
  for (int i = 0; i < list->capacity; i++) {
        if(list->data[i] == NULL){
            list->data[i] = item;
            list->count++;
            return;
        }
    }

    printf("Unable to Add Item to List\n");
    return;
}

void resize_list(list_t* list){
  //create new capacity
  int new_capacity =  list->capacity * 2;
  //attempt realloc
  void **temp = realloc(list->data, new_capacity * sizeof(void *));
  if (temp == NULL) {
      printf("Unable to resize list.\n");
      exit(1);
  }
    list->data = temp;

  //null new data
  for (int i = list->capacity; i < new_capacity; i++) {
        list->data[i] = NULL;
  }
  
  //update capacity
  list->capacity = new_capacity;
}


list_t* new_list(int capacity) {
  //malloc list
  list_t* list = malloc(sizeof(list_t));
  if (list == NULL) {
    printf("Failed to Allocate List.\n");
    return NULL;
  }

  //set count and capacity
  list->count = 0;
  list->capacity = capacity;

  //malloc data
  list->data = malloc(list->capacity * sizeof(void *));
  if (list->data == NULL) {
    free(list);
    return NULL;
  }

  //init data to null
  for (int i = 0; i < list->capacity; i++) {
    list->data[i] = NULL;
    }

  return list;
}

//Loop through list and set values to NULL
void clear_list(list_t* list){
  for (int i = 0; i < list->capacity; i++) {
    list->data[i] = NULL;
    }
}

list_t* list_join(list_t* list1, list_t* list2){
  int new_capacity = list1->capacity + list2->capacity;
  list_t* new_l = new_list(new_capacity);
  if(new_l == NULL){
    return NULL;
  }

  for(int i = 0; i<list1->capacity; i++){
    new_l->data[i] = list1->data[i];
  }

  for(int j = 0; j<list2->capacity; j++){
    new_l->data[list1->capacity + j] = list2->data[j];
  }

  free_list(list1);
  free_list(list2);

  return new_l;
}
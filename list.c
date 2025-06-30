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
    printf("Could Not Remove Item.");
    return;
}

void list_add(list_t* list, void* item) {

  //resize list if too small
  if (list->count == list->capacity) {
    list->capacity *= 2;
    void **temp = realloc(list->data, list->capacity * sizeof(void *));
    if (temp == NULL) {
      list->capacity /= 2;
      exit(1);
    }
    list->data = temp;
  }

  //if slot is null, change it to item data
  for (int i = 0; i < list->capacity; i++) {
        if(list->data[i] == NULL){
            list->data[i] = item;
            list->count++;
            return;
        }
    }

    printf("Unable to Add Item to List");
    return;
}


list_t* new_list(int capacity) {
  //malloc list
  list_t* list = malloc(sizeof(list_t));
  if (list == NULL) {
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
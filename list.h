#ifndef LIST_H
#define LIST_H

typedef struct List {
  int count;
  int capacity;
  void **data;
} list_t;

//Makes a new list. all spots are null
list_t* new_list(int capacity);

//adds a value to the first non null space
void list_add(list_t* list, void* item);

//removes a value from the list
void list_remove(list_t* list, void* item);

//responsible memory management.
void free_list(list_t* list);

//remove all values from the list
void clear_list(list_t* list);

#endif
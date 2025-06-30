#ifndef LIST_H
#define LIST_H

typedef struct List {
  int count;
  int capacity;
  void **data;
} list_t;

list_t* new_list(int capacity);
void list_add(list_t* list, void* item);
void list_remove(list_t* list, void* item);
void free_list(list_t* list);

#endif
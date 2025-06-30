#ifndef STACK_H
#define STACK_H

typedef struct Stack {
  int count;
  int capacity;
  void **data;
} stack_t;

stack_t *stack_new(int capacity);

#endif
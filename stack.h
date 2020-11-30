#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include "memory.h"

struct Stack;

struct Stack *stack_create(memory_allocator alloc, memory_deallocator dealloc);

void stack_free(struct Stack *stack);

void stack_push(struct Stack *stack, void *value);

void *stack_pop(struct Stack *stack);

void *stack_peek(struct Stack *stack);

size_t stack_size(struct Stack *stack);

#endif
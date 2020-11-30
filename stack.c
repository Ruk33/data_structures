#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "list.h"
#include "stack.h"

struct Stack {
    memory_deallocator dealloc;
    struct List *elements;
    size_t size;
};

struct Stack *stack_create(memory_allocator alloc, memory_deallocator dealloc)
{
    assert(alloc);
    assert(dealloc);

    struct Stack *stack = alloc(sizeof(*stack));

    memset(stack, 0, sizeof(*stack));

    stack->elements = list_create(alloc, dealloc);
    stack->dealloc = dealloc;

    return stack;
}

void stack_free(struct Stack *stack)
{
    assert(stack);
    assert(stack->dealloc);
    assert(stack->elements);

    list_free(stack->elements);
    stack->dealloc(stack);
}

void stack_push(struct Stack *stack, void *value)
{
    assert(stack);
    assert(stack->elements);

    list_add_beginning(&stack->elements, value);
    stack->size++;
}

void *stack_pop(struct Stack *stack)
{
    assert(stack);
    assert(stack->elements);

    struct ListEntry *last = list_get_iterator(stack->elements);
    void *value = list_get_value(last);

    list_remove(&stack->elements, last);
    stack->size--;

    return value;
}

void *stack_peek(struct Stack *stack)
{
    assert(stack);
    assert(stack->elements);

    struct ListEntry *last = list_get_iterator(stack->elements);
    return list_get_value(last);
}

size_t stack_size(struct Stack *stack)
{
    assert(stack);
    return stack->size;
}
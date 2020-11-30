#ifndef LIST_H
#define LIST_H

#include "memory.h"

/**
 * Data structure used to store values in a chain
 * 
 * Example:
 * 
 * struct List *list = list_create(malloc, free);
 * struct ListEntry *iterator = NULL;
 * 
 * int foo = 42;
 * int bar = 24;
 * 
 * list_add_last(&list, &foo);
 * list_add_last(&list, &bar);
 * 
 * iterator = list_get_iterator(list);
 * 
 * while (iterator) {
 *      printf("%d\n", list_get_value(iterator));
 *      iterator = list_get_next(iterator);
 * }
 * 
 * list_free(list);
 */
struct List;

struct ListEntry;

struct List *list_create(memory_allocator alloc, memory_deallocator dealloc);

void list_free(struct List *list);

struct ListEntry *list_add_beginning(struct List **list, void *value);

struct ListEntry *list_add_last(struct List **list, void *value);

void list_remove(struct List **list, struct ListEntry *node);

struct ListEntry *list_get_iterator(struct List *list);

int list_has_next(struct ListEntry *entry);

struct ListEntry *list_get_next(struct ListEntry *entry);

/**
 * Get value stored by list when the 
 * value was added using list_add
 */
void *list_get_value(struct ListEntry *entry);

#endif
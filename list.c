#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memory.h"
#include "list.h"

struct ListEntry {
    void *value;
    struct ListEntry *next;
};

struct List {
    memory_allocator alloc;
    memory_deallocator dealloc;
    struct ListEntry *elements;
};

struct List *list_create(memory_allocator alloc, memory_deallocator dealloc)
{
    assert(alloc);
    assert(dealloc);

    struct List *list = alloc(sizeof(*list));

    memset(list, 0, sizeof(*list));

    list->alloc = alloc;
    list->dealloc = dealloc;

    return list;
}

void list_free(struct List *list)
{
    assert(list);
    assert(list->dealloc);

    struct ListEntry *iterator = list_get_iterator(list);
    struct ListEntry *next = NULL;

    while (iterator) {
        next = list_get_next(iterator);
        list->dealloc(iterator);
        iterator = next;
    }

    list->dealloc(list);
}

struct ListEntry *list_add_beginning(struct List **list, void *value)
{
    assert(*list);
    assert((*list)->alloc);

    struct ListEntry *new_node = (*list)->alloc(sizeof(*new_node));
    struct ListEntry **last = &(*list)->elements;

    new_node->value = value;
    new_node->next = (*list)->elements;

    *last = new_node;

    return new_node;
}

struct ListEntry *list_add_last(struct List **list, void *value)
{
    assert(*list);
    assert((*list)->alloc);

    struct ListEntry *new_node = (*list)->alloc(sizeof(*new_node));
    struct ListEntry **last = &(*list)->elements;

    new_node->value = value;
    new_node->next = NULL;

    while (*last) {
        last = &(*last)->next;
    }

    *last = new_node;

    return new_node;
}

void list_remove(struct List **list, struct ListEntry *node)
{
    assert(*list);
    assert(node);

    struct ListEntry **head = &(*list)->elements;

    while (*head != node) {
        head = &(*head)->next;
    }

    *head = node->next;
    (*list)->dealloc(node);
}

struct ListEntry *list_get_iterator(struct List *list)
{
    assert(list);
    return list->elements;
}

int list_has_next(struct ListEntry *entry)
{
    assert(entry);
    return list_get_next(entry) != NULL;
}

struct ListEntry *list_get_next(struct ListEntry *entry)
{
    assert(entry);
    return entry->next;
}

void *list_get_value(struct ListEntry *entry)
{
    assert(entry);
    return entry->value;
}
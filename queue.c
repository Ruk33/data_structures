#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "memory.h"

struct Queue {
    memory_deallocator dealloc;
    struct List *elements;
    size_t size;
};

struct Queue *queue_create(memory_allocator alloc, memory_deallocator dealloc)
{
    assert(alloc);
    assert(dealloc);

    struct Queue *queue = alloc(sizeof(*queue));

    memset(queue, 0, sizeof(*queue));

    queue->elements = list_create(alloc, dealloc);
    queue->dealloc = dealloc;

    return queue;
}

void queue_free(struct Queue *queue)
{
    assert(queue);
    assert(queue->dealloc);
    assert(queue->elements);

    list_free(queue->elements);
    queue->dealloc(queue);
}

void queue_enqueue(struct Queue *queue, void *value)
{
    assert(queue);
    assert(queue->elements);

    list_add_last(&queue->elements, value);
    queue->size++;
}

void *queue_dequeue(struct Queue *queue)
{
    assert(queue);
    assert(queue->elements);

    struct ListEntry *first = list_get_iterator(queue->elements);
    void *value = NULL;

    if (!first) {
        return NULL;
    }

    value = list_get_value(first);
    list_remove(&queue->elements, first);
    queue->size--;

    return value;
}

size_t queue_size(struct Queue *queue)
{
    assert(queue);
    return queue->size;
}
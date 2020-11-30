#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include "memory.h"

struct Queue;

struct Queue *queue_create(memory_allocator alloc, memory_deallocator dealloc);

void queue_free(struct Queue *queue);

void queue_enqueue(struct Queue *queue, void *value);

void *queue_dequeue(struct Queue *queue);

size_t queue_size(struct Queue *queue);

#endif
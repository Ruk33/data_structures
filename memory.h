#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>

typedef void *(*memory_allocator)(size_t);
typedef void (*memory_deallocator)(void *);

#endif
#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdlib.h>
#include "memory.h"

/**
 * Data structure to store and get values
 * as performant as possible using a key
 * 
 * Example:
 * 
 * struct HashMap *hash_map = hash_map_create(malloc, free, 25);
 * int *value = NULL;
 * 
 * char foo_key[] = "foo";
 * int foo = 42;
 * 
 * hash_map_set(hash_map, foo_key, sizeof(foo_key), &foo);
 * value = hash_map_get(hash_map, foo_key, sizeof(foo_key)); // => 42
 * 
 * hash_map_free(hash_map);
 */
struct HashMap;

struct HashMap *hash_map_create(memory_allocator alloc, memory_deallocator dealloc, size_t size);

void hash_map_free(struct HashMap *hash_map);

void hash_map_set(struct HashMap *hash_map, char *key, size_t key_size, void *value);

void *hash_map_get(struct HashMap *hash_map, char *key, size_t key_size);

int hash_map_has_key(struct HashMap *hash_map, char *key, size_t key_size);

#endif
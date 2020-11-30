#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "list.h"
#include "hash_map.h"

struct HashMapEntry {
    char *key;
    void *value;
};

struct HashMap {
    memory_allocator alloc;
    memory_deallocator dealloc;
    struct List **entries;
    size_t size;
};

struct HashMap *hash_map_create(memory_allocator alloc, memory_deallocator dealloc, size_t size)
{
    assert(alloc);
    assert(dealloc);
    assert(size > 0);

    struct HashMap *hash_map = alloc(sizeof(*hash_map));

    memset(hash_map, 0, sizeof(*hash_map));

    hash_map->alloc = alloc;
    hash_map->dealloc = dealloc;
    hash_map->entries = alloc(sizeof(*hash_map->entries) * size);
    hash_map->size = size;

    memset(hash_map->entries, 0, sizeof(*hash_map->entries) * size);

    return hash_map;
}

void hash_map_free(struct HashMap *hash_map)
{
    assert(hash_map);
    assert(hash_map->dealloc);

    // clean children

    hash_map->dealloc(hash_map->entries);
    hash_map->dealloc(hash_map);
}

static size_t hash(char *key, size_t key_size)
{
    size_t hash = 5381;
    int c = 0;

    for (size_t i = 0; i < key_size; i++) {
        c = *key++;
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

void hash_map_set(struct HashMap *hash_map, char *key, size_t key_size, void *value)
{
    assert(hash_map);
    assert(key);
    assert(key_size > 0);
    assert(hash_map->alloc);
    assert(hash_map->dealloc);
    assert(hash_map->entries);

    struct HashMapEntry *new_entry = hash_map->alloc(sizeof(*new_entry));
    size_t index = 0;

    new_entry->key = hash_map->alloc(sizeof(*new_entry->key) * key_size);
    new_entry->value = value;

    memcpy(new_entry->key, key, key_size);

    index = hash(new_entry->key, key_size) % hash_map->size;

    if (!hash_map->entries[index]) {
        hash_map->entries[index] = list_create(hash_map->alloc, hash_map->dealloc);
    }

    list_add_beginning(&hash_map->entries[index], new_entry);
}

static struct HashMapEntry *get_entry(struct HashMap *hash_map, char *key, size_t key_size)
{
    assert(hash_map);
    assert(key);
    assert(key_size > 0);
    assert(hash_map->entries);

    size_t index = hash(key, key_size) % hash_map->size;
    struct List *entries = hash_map->entries[index];
    struct ListEntry *iterator = NULL;
    struct HashMapEntry *entry = NULL;

    if (!entries) {
        return NULL;
    }

    iterator = list_get_iterator(entries);

    while (iterator) {
        entry = list_get_value(iterator);

        if (memcmp(key, entry->key, key_size) == 0) {
            return entry;
        }

        iterator = list_get_next(iterator);
    }

    return NULL;
}

void *hash_map_get(struct HashMap *hash_map, char *key, size_t key_size)
{
    assert(hash_map);
    assert(key);
    assert(key_size > 0);

    struct HashMapEntry *entry = get_entry(hash_map, key, key_size);

    if (entry) {
        return entry->value;
    }

    return NULL;
}

int hash_map_has_key(struct HashMap *hash_map, char *key, size_t key_size)
{
    assert(hash_map);
    assert(key);
    assert(key_size > 0);

    return get_entry(hash_map, key, key_size) != NULL;
}
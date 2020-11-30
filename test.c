#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "stack.h"
#include "queue.h"
#include "hash_map.h"

void test_list()
{
    struct List *list = list_create(malloc, free);
    struct ListEntry *iterator = NULL;
    int *value = NULL;
    int values[] = {42, 24, 2};
    int values_count = (int) (sizeof(values) / sizeof(values[0]));

    list_add_beginning(&list, &values[0]);
    list_add_beginning(&list, &values[1]);
    list_add_beginning(&list, &values[2]);

    iterator = list_get_iterator(list);

    for (int i = values_count - 1; i >= 0; i--) {
        value = list_get_value(iterator);
        assert(values[i] == *value);
        iterator = list_get_next(iterator);
    }

    iterator = list_get_iterator(list);

    for (int i = 0; i < values_count - 1; i++) {
        assert(list_has_next(iterator));
        iterator = list_get_next(iterator);
    }

    iterator = list_get_iterator(list);
    value = list_get_value(iterator);

    assert(*value == values[2]);
    list_remove(&list, iterator);

    iterator = list_get_iterator(list);
    value = list_get_value(iterator);
    assert(*value == values[1]);
    assert(list_has_next(iterator));

    iterator = list_get_next(iterator);
    value = list_get_value(iterator);
    assert(*value == values[0]);
    assert(!list_has_next(iterator));

    list_free(list);
}


void test_stack()
{
    struct Stack *stack = stack_create(malloc, free);

    int values[] = {42, 24, 2};
    int *value = NULL;

    assert(stack_size(stack) == 0);

    stack_push(stack, &values[0]);
    assert(stack_size(stack) == 1);
    
    value = stack_peek(stack);
    assert(stack_size(stack) == 1);
    assert(*value == values[0]);

    stack_push(stack, &values[1]);
    stack_push(stack, &values[2]);
    assert(stack_size(stack) == 3);

    value = stack_pop(stack);
    assert(stack_size(stack) == 2);
    assert(*value == values[2]);

    value = stack_pop(stack);
    assert(stack_size(stack) == 1);
    assert(*value == values[1]);

    stack_push(stack, &values[2]);
    value = stack_pop(stack);
    assert(*value == values[2]);

    value = stack_pop(stack);
    assert(stack_size(stack) == 0);
    assert(*value == values[0]);

    stack_free(stack);
}

void test_queue()
{
    struct Queue *queue = queue_create(malloc, free);

    int values[] = {42, 24, 2};
    int *value = NULL;

    assert(queue_size(queue) == 0);

    queue_enqueue(queue, &values[0]);
    assert(queue_size(queue) == 1);

    queue_enqueue(queue, &values[1]);
    queue_enqueue(queue, &values[2]);
    assert(queue_size(queue) == 3);

    value = queue_dequeue(queue);
    assert(queue_size(queue) == 2);
    assert(*value == values[0]);

    value = queue_dequeue(queue);
    assert(queue_size(queue) == 1);
    assert(*value == values[1]);

    queue_enqueue(queue, &values[1]);
    value = queue_dequeue(queue);
    assert(*value == values[2]);

    value = queue_dequeue(queue);
    assert(queue_size(queue) == 0);
    assert(*value == values[1]);

    queue_free(queue);
}

void test_hash_map()
{
    struct HashMap *hash_map = hash_map_create(malloc, free, 25);

    char foo_key[] = "foo";
    char bar_key[] = "bar";
    char baz_key[] = "baz";

    int foo = 42;
    int bar = 24;
    int baz = 2;

    int *value = NULL;

    assert(!hash_map_has_key(hash_map, foo_key, sizeof(foo_key)));
    assert(!hash_map_has_key(hash_map, bar_key, sizeof(bar_key)));
    assert(!hash_map_has_key(hash_map, baz_key, sizeof(baz_key)));

    hash_map_set(hash_map, foo_key, sizeof(foo_key), &foo);
    value = hash_map_get(hash_map, foo_key, sizeof(foo_key));
    assert(hash_map_has_key(hash_map, foo_key, sizeof(foo_key)));
    assert(foo == *value);

    hash_map_set(hash_map, bar_key, sizeof(bar_key), &bar);
    value = hash_map_get(hash_map, bar_key, sizeof(bar_key));
    assert(hash_map_has_key(hash_map, bar_key, sizeof(bar_key)));
    assert(bar == *value);

    hash_map_set(hash_map, baz_key, sizeof(baz_key), &baz);
    value = hash_map_get(hash_map, baz_key, sizeof(baz_key));
    assert(hash_map_has_key(hash_map, baz_key, sizeof(baz_key)));
    assert(baz == *value);

    hash_map_free(hash_map);
}

int main(/* int argc, char **argv */)
{
    printf("Starting tests\n");

    printf("Testing list\n");
    test_list();
    printf("List tests completed successfully\n");

    printf("Testing stack\n");
    test_stack();
    printf("Stack tests completed successfully\n");

    printf("Testing queue\n");
    test_queue();
    printf("Queue tests completed successfully\n");

    printf("Testing hash map\n");
    test_hash_map();
    printf("Hash map tests completed successfully\n");

    printf("Tests ran successfully\n");

    return EXIT_SUCCESS;
}
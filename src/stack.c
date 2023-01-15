#include "stack.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int_stack_t* int_stack_create() {
    return int_stack_with_capacity(32);
}

int_stack_t* int_stack_with_capacity(size_t capacity) {
    int_stack_t* stack = malloc(sizeof(int_stack_t));

    stack->capacity = capacity;
    stack->size = 0;
    stack->buffer = malloc(sizeof(int) * stack->capacity);

    return stack;
}

int_stack_t* int_stack_from(int array[], size_t size) {
    int_stack_t* stack = int_stack_with_capacity(size);

    stack->size = size;
    memcpy(stack->buffer, array, sizeof(int) * size);

    return stack;
}

void int_stack_destroy(int_stack_t* stack) {
    assert(stack && stack->buffer);
    free(stack->buffer);
    free(stack);
}

size_t int_stack_len(int_stack_t* stack) {
    assert(stack);
    return stack->size;
}

int int_stack_is_empty(int_stack_t* stack) {
    assert(stack);
    return !stack->size;
}

int int_stack_is_full(int_stack_t* stack) {
    assert(stack);
    return stack->capacity == stack->size;
}

void int_stack_reserve(int_stack_t* stack, size_t amount) {
    assert(stack);
    int alloc = 0;
    while ((stack->capacity - stack->size) < amount) {
        stack->capacity *= 2;
        alloc = 1;
    }
    if (alloc) {
        stack->buffer = realloc(stack->buffer, sizeof(int) * stack->capacity);
    }
}

int int_stack_get(int_stack_t* stack, size_t index) {
    // assert(stack && index < stack->size);
    return *(stack->buffer + index);
}

void int_stack_set(int_stack_t* stack, size_t index, int value) {
    assert(stack && index < stack->size);
    *(stack->buffer + index) = value;
}

int int_stack_first(int_stack_t* stack) {
    return int_stack_get(stack, 0);
}

int int_stack_last(int_stack_t* stack) {
    return int_stack_get(stack, stack->size);
}

int int_stack_pop(int_stack_t* stack) {
    assert(stack && stack->size != 0);

    return int_stack_get(stack, --stack->size);
}

void int_stack_push(int_stack_t* stack, int value) {
    assert(stack);

    if (stack->size == stack->capacity) {
        int_stack_reserve(stack, 1);
    }
    int_stack_set(stack, stack->size++, value);
}

int int_stack_remove(int_stack_t* stack, size_t index) {
    assert(stack && index < stack->size);

    int_stack_t* remainder = int_stack_split(stack, index + 1);
    int value = int_stack_pop(stack);
    int_stack_append(stack, remainder);
    int_stack_destroy(remainder);
    return value;
}

void int_stack_insert(int_stack_t* stack, size_t index, int value) {
    assert(stack && index <= stack->size);

    int_stack_t* remainder = int_stack_split(stack, index);
    int_stack_push(stack, value);
    int_stack_append(stack, remainder);
    int_stack_destroy(remainder);
}

int_stack_t* int_stack_slice(int_stack_t* stack, size_t start, size_t stop) {
    assert(stack && stop < stack->size && stop >= start);
    return int_stack_from(stack->buffer + start, stop - start);
}

int int_stack_sort_cmp(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}
void int_stack_sort(int_stack_t* stack) {
    assert(stack);
    qsort(stack->buffer, stack->size, sizeof(int), int_stack_sort_cmp);
}

int int_stack_contains(int_stack_t* stack, int value) {
    assert(stack);
    for (size_t i = 0; i < stack->size; i++) {
        if (int_stack_get(stack, i) == value) {
            return 1;
        }
    }
    return 0;
}

size_t int_stack_search(int_stack_t* stack, int value) {
    (void)stack;
    (void)value;
    return 0;
}

void int_stack_swap(int_stack_t* stack, size_t first, size_t second) {
    assert(stack && first < stack->size && second < stack->size);
    int tmp = int_stack_get(stack, first);
    int_stack_set(stack, first, int_stack_get(stack, second));
    int_stack_set(stack, second, tmp);
}

void int_stack_reverse(int_stack_t* stack) {
    assert(stack);
    size_t l = 0;
    size_t r = stack->size - 1;
    while (l < r) {
        int_stack_swap(stack, l, r);
        l++;
        r--;
    }
}

void int_stack_append(int_stack_t* stack, int_stack_t* other) {
    assert(stack && other);
    int_stack_reserve(stack, other->size);
    memcpy(stack->buffer + stack->size, other->buffer, sizeof(int) * other->size);
    stack->size += other->size;
    other->size = 0;
}

int_stack_t* int_stack_split(int_stack_t* stack, size_t index) {
    assert(stack && index <= stack->size);
    int_stack_t* split = int_stack_from(stack->buffer + index, stack->size - index);
    stack->size = index;
    return split;
}

void int_stack_fill(int_stack_t* stack, int filler) {
    assert(stack);
    for (size_t i = 0; i < stack->capacity; i++) {
        int_stack_push(stack, filler);
    }
}

void int_stack_truncate(int_stack_t* stack, size_t size) {
    assert(stack);
    stack->size = size;
}

void int_stack_resize(int_stack_t* stack, size_t size, int filler) {
    assert(stack);
    if (size > stack->size) {
        for (size_t i = stack->size; i < size; i++) {
            int_stack_push(stack, filler);
        }
    } else {
        int_stack_truncate(stack, size);
    }
}

void int_stack_map(int_stack_t* stack, int_stack_map_fn map_fn) {
    assert(stack && map_fn);
    for (size_t i = 0; i < stack->size; i++) {
        int_stack_set(stack, i, map_fn(int_stack_get(stack, i)));
    }
}

void int_stack_filter(int_stack_t* stack, int_stack_filter_fn filter_fn) {
    assert(stack && filter_fn);
    for (size_t i = 0; i < stack->size; i++) {
        if (!filter_fn(int_stack_get(stack, i))) {
            int_stack_remove(stack, i);
        }
    }
}

int* int_stack_find(int_stack_t* stack, int_stack_filter_fn filter_fn) {
    assert(stack && filter_fn);
    for (size_t i = 0; i < stack->size; i++) {
        if (filter_fn(int_stack_get(stack, i))) {
            return (stack->buffer + i);
        }
    }
    return NULL;
}

int int_stack_fold(int_stack_t* stack, int initial, int_stack_fold_fn fold_fn) {
    assert(stack && fold_fn);
    for (size_t i = 0; i < stack->size; i++) {
        fold_fn(&initial, int_stack_get(stack, i));
    }
    return initial;
}

void int_stack_sum_helper(int* acc, int value) {
    *acc += value;
}
void int_stack_product_helper(int* acc, int value) {
    *acc *= value;
}

int int_stack_sum(int_stack_t* stack) {
    return int_stack_fold(stack, 0, int_stack_sum_helper);
}
int int_stack_product(int_stack_t* stack) {
    return int_stack_fold(stack, 1, int_stack_product_helper);
}

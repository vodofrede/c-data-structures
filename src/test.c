#include "stack.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef void (*testfn)();
const testfn tests[];
const size_t len;

int main(void) {
    printf("running %zu test%s ... ", len, len > 1 ? "s" : "");
    for (size_t i = 0; i < len; i++) {
        tests[i]();
    }
    printf("ok.\n");
}

void test_stack_create();
void test_stack_conditionals();
void test_stack_access();
void test_stack_sort();
void test_stack_search();
void test_stack_operations();
void test_stack_functional();

const testfn tests[] = {
    test_stack_create,
    test_stack_conditionals,
    test_stack_access,
    test_stack_sort,
    test_stack_search,
    test_stack_operations,
    test_stack_functional};
const size_t len = sizeof(tests) / sizeof(testfn);

/* stack tests */
void print_stack(int_stack_t* stack) {
    for (size_t i = 0; i < stack->size; i++) {
        printf("%d ", int_stack_get(stack, i));
    }
    printf("\n");
}

void test_stack_create() {
    int_stack_t* stack = int_stack_create();
    assert(stack->capacity == 32);
    assert(stack->size == 0);
    assert(stack->buffer);

    int_stack_t* with_capacity = int_stack_with_capacity(64);
    assert(with_capacity->capacity == 64);
    assert(with_capacity->size == 0);
    assert(with_capacity->buffer);

    int array[] = {0, 1, 2, 3, 4};
    int_stack_t* from = int_stack_from(array, sizeof(array) / sizeof(int));
    assert(from->capacity == 5);
    assert(from->size == 5);
    assert(from->buffer);

    int_stack_destroy(stack);
    int_stack_destroy(with_capacity);
    int_stack_destroy(from);
}

void test_stack_conditionals() {
    int_stack_t* stack = int_stack_create();
    assert(int_stack_is_empty(stack));

    int a[] = {0, 1, 2};
    int_stack_t* second = int_stack_from(a, sizeof(a) / sizeof(int));
    assert(int_stack_is_full(second));

    int_stack_destroy(stack);
    int_stack_destroy(second);
}

void test_stack_access() {
    int init[] = {0, 1, 2, 3, 4};
    int_stack_t* stack = int_stack_from(init, 5);

    int_stack_t* slice = int_stack_slice(stack, 1, 4);
    int z[] = {1, 2, 3};
    assert(!memcmp(slice->buffer, z, sizeof(z)));

    int_stack_destroy(slice);
    int_stack_destroy(stack);
}

void test_stack_sort() {
    int init[] = {4, 1, 0, 3, 2};
    int_stack_t* stack = int_stack_from(init, 5);

    int a[] = {0, 1, 2, 3, 4};
    int_stack_sort(stack);
    assert(!memcmp(stack->buffer, a, sizeof(a)));

    int_stack_destroy(stack);
}

void test_stack_search() {
    int_stack_t* stack = int_stack_create();

    int_stack_destroy(stack);
}

void test_stack_operations() {
    int_stack_t* stack = int_stack_create();

    int_stack_destroy(stack);
}

int triple(int value) {
    return value * 3;
}

int is_even(int value) {
    return !(value % 2);
}

void sum(int* acc, int value) {
    *acc += value;
}

void test_stack_functional() {
    int init[] = {0, 1, 2, 3, 4};
    int_stack_t* stack = int_stack_from(init, 5);

    int_stack_t* slice = int_stack_slice(stack, 1, 4);
    int z[] = {1, 2, 3};
    assert(!memcmp(slice->buffer, z, sizeof(z)));
    int_stack_destroy(slice);

    int_stack_map(stack, triple);
    int a[] = {0, 3, 6, 9, 12};
    assert(!memcmp(stack->buffer, a, sizeof(a)));

    int_stack_filter(stack, is_even);
    int b[] = {0, 6, 12};
    assert(!memcmp(stack->buffer, b, sizeof(b)));

    int v = int_stack_fold(stack, 0, sum);
    int c = 18;
    assert(v == c);

    int_stack_destroy(stack);
}

// void test_stack() {
//     int_stack_t* stack = int_stack_create();

//     int_stack_push(stack, 3);
//     int_stack_push(stack, 2);
//     int_stack_push(stack, 1);
//     // print_stack(stack);
//     assert(stack->size == 3);

//     int_stack_sort(stack);
//     // print_stack(stack);
//     assert(int_stack_get(stack, 0) == 1);

//     int_stack_reverse(stack);
//     // print_stack(stack);
//     assert(int_stack_get(stack, 0) == 3);

//     int_stack_t* other_stack = int_stack_create();
//     int_stack_push(other_stack, 4);
//     int_stack_push(other_stack, 5);

//     int_stack_append(stack, other_stack);
//     // print_stack(stack);
//     assert(stack->size == 5 && other_stack->size == 0);

//     int_stack_resize(stack, 7, 1);
//     assert(stack->size == 7);
//     // print_stack(stack);

//     int_stack_t* split_stack = int_stack_split(stack, 4);
//     assert(stack->size == 4);
//     // print_stack(stack);
//     assert(split_stack->size == 3);
//     // print_stack(split_stack);

//     int_stack_truncate(stack, 3);
//     assert(stack->size == 3);

//     int_stack_insert(stack, 3, 6);
//     // print_stack(stack);

//     int_stack_map(stack, triple);
//     // print_stack(stack);

//     int_stack_filter(stack, is_even);
//     // print_stack(stack);

//     int total = int_stack_fold(stack, 0, sum);
//     assert(total == 24);

//     int total_2 = int_stack_sum(stack);
//     assert(total == total_2);

//     // int_stack_fill(stack, 2);
//     // print_stack(stack);

//     int_stack_resize(stack, 10, 2);
//     print_stack(stack);

//     int_stack_destroy(stack);
//     int_stack_destroy(other_stack);
//     int_stack_destroy(split_stack);
// }
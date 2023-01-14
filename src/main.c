#include "stack.h"

#include <assert.h>
#include <stdio.h>

void print_stack(int_stack_t* stack) {
    for (size_t i = 0; i < stack->size; i++) {
        printf("%d ", int_stack_get(stack, i));
    }
    printf("\n");
}

int main(void) {
    int_stack_t* stack = int_stack_create();

    int_stack_push(stack, 3);
    int_stack_push(stack, 2);
    int_stack_push(stack, 1);
    print_stack(stack);

    int_stack_sort(stack);
    print_stack(stack);

    int_stack_reverse(stack);
    print_stack(stack);

    int_stack_destroy(stack);
}
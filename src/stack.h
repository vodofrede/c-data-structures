#include <stdlib.h>

/// @brief A stack containing integers. The stack will only every grow in size.
typedef struct {
    int* buffer;
    size_t capacity;
    size_t size;
} int_stack_t;

/// @brief Create a new stack. It will have an initial capacity of 32 elements.
/// @return A pointer to the newly created stack.
int_stack_t* int_stack_create();

/// @brief Create a new stack with given capacity.
/// @param capacity Initial capacity.
/// @return A pointer to the newly created stack.
int_stack_t* int_stack_with_capacity(size_t capacity);

/// @brief Create a new stack with initial values given by the passed array.
/// @param array Initial values.
/// @return A pointer to the newly created stack.
int_stack_t* int_stack_from(int array[], size_t size);

/// @brief Free the memory of an existing stack.
/// @param stack The stack to destroy.
void int_stack_destroy(int_stack_t* stack);

/// @brief Get the length/size of the stack.
/// @param stack The stack.
/// @return Length of the stack.
size_t int_stack_len(int_stack_t* stack);

/// @brief Check if the stack is empty.
/// @param stack The stack.
/// @return True if the stack is empty.
int int_stack_is_empty(int_stack_t* stack);

/// @brief Check is the stack is full.
/// @param stack The stack.
/// @return True if the stack is full.
int int_stack_is_full(int_stack_t* stack);

/// @brief Reserve at least amount additional spaces in the stack, reallocating if necessary.
/// @param stack The stack.
/// @param amount Minimum amount to be reserved.
void int_stack_reserve(int_stack_t* stack, size_t amount);

/// @brief Get the element in the stack at the place specified by index.
/// @param stack The stack.
/// @param index Index of the element in the stack.
/// @return Value at the specified index in the stack.
int int_stack_get(int_stack_t* stack, size_t index);

/// @brief Set the element at the specified index in the stack to the specified value.
/// @param stack The stack.
/// @param index Index of the element.
/// @param value Value to set.
void int_stack_set(int_stack_t* stack, size_t index, int value);

/// @brief Get the first element of the stack.
/// @param stack The stack.
/// @return First element in the stack.
int int_stack_first(int_stack_t* stack);

/// @brief Get the last element of the stack.
/// @param stack The stack.
/// @return Last element in the stack.
int int_stack_last(int_stack_t* stack);

/// @brief Pop the top-most value in the stack.
/// @param stack The stack.
/// @return Top-most element.
int int_stack_pop(int_stack_t* stack);

/// @brief Push an element to the top of the stack.
/// @param stack The stack.
/// @param value Value to push.
void int_stack_push(int_stack_t* stack, int value);

/// @brief Remove element at given index. This will shift elements to the right of the element over.
/// @param stack The stack.
/// @param index Index of element to remove.
/// @return Value of the removed element.
int int_stack_remove(int_stack_t* stack, size_t index);

/// @brief Insert an element at given index. This will shift elements to the right of the element away.
/// @param stack The stack.
/// @param index Index at which to insert element.
/// @param value Value of element to insert.
void int_stack_insert(int_stack_t* stack, size_t index, int value);

/// @brief Create a subslice of the stack. This operation will copy the elements in the stack to the new slice stack.
/// @param stack The stack.
/// @param start Start index, inclusive.
/// @param stop Stop index, exclusive.
/// @return A new stack containing the sliced elements.
int_stack_t* int_stack_slice(int_stack_t* stack, size_t start, size_t stop);

/// @brief Sort the stack using quicksort.
/// @param stack The stack.
void int_stack_sort(int_stack_t* stack);

/// @brief Searches the stack linearly for the value and returns true if any element matches the value.
/// @param stack The stack.
/// @param value Value to match.
/// @return True if the value was found.
int int_stack_contains(int_stack_t* stack, int value);

/// @brief Performs a binary search for the value and returns the index if it is found.
/// @param stack The stack.
/// @param value Value to match.
/// @return Index of the value, or -1 if value was not found.
size_t int_stack_search(int_stack_t* stack, int value);

/// @brief Rotate the elements in the stack left.
/// @param stack The stack.
/// @param amount Amount of times to rotate.
void int_stack_rotate_left(int_stack_t* stack, size_t amount);

/// @brief Rotate the elements in the stack right.,
/// @param stack The stack.
/// @param amount Amount of times to rotate.
void int_stack_rotate_right(int_stack_t* stack, size_t amount);

/// @brief Swap two values in the stack.
/// @param stack The stack.
/// @param left Index of the first element.
/// @param right Index of the second element.
void int_stack_swap(int_stack_t* stack, size_t first, size_t second);

/// @brief Reverse the order of the values in the stack in-place.
/// @param stack The stack.
void int_stack_reverse(int_stack_t* stack);

/// @brief Move all the elements of other into the stack.
/// @param stack The stack.
/// @param other Stack which will be emptied.
void int_stack_append(int_stack_t* stack, int_stack_t* other);

/// @brief Divides the stack into two separate stacks at the index, with the first stack excluding the element at the specified index.
/// @param stack The stack.
/// @param index Index at which to split the stack.
/// @return A pointer to a new stack containing the remaining elements.
int_stack_t* int_stack_split(int_stack_t* stack, size_t index);

/// @brief Fills the stack with filler elements.
/// @param stack The stack.
/// @param filler Filler value.
void int_stack_fill(int_stack_t* stack, int filler);

/// @brief Truncate the stack to desired size, discarding excess elements.
/// @param stack The stack.
/// @param size New size of stack.
void int_stack_truncate(int_stack_t* stack, size_t size);

/// @brief Resize the stack to desired size, truncating if size is less than before or extending if it is greater.
/// @param stack The stack.
/// @param size New size of stack.
/// @param filler Value to insert into new spaces if size is greater than before.
void int_stack_resize(int_stack_t* stack, size_t size, int filler);

typedef int (*int_stack_map_fn)(int);
typedef int (*int_stack_filter_fn)(int);
typedef void (*int_stack_fold_fn)(int*, int);

/// @brief Maps every value in the stack according to the function passed.
/// @param stack The stack.
/// @param map_fn Function which takes an int value and maps it to another int value.
void int_stack_map(int_stack_t* stack, int_stack_map_fn map_fn);

/// @brief Filters values in the stack and leaves every value matching the predicate.
/// @param stack The stack.
/// @param filter_fn Function which takes an int and returns whether it should be retained.
void int_stack_filter(int_stack_t* stack, int_stack_filter_fn filter_fn);

/// @brief Finds the first value that satisfies the filter function predicate.
/// @param stack The stack.
/// @param filter_fn Function which should return true when the correct value is found.
/// @return Pointer to the first value that satisfies the filter function. NULL no element matched the predicate.
int* int_stack_find(int_stack_t* stack, int_stack_filter_fn filter_fn);

/// @brief Reduces every value down to to a single int accumulator.
/// @param stack The stack.
/// @param initial Initial value for the accumulator.
/// @param map_fn Function which takes an accumulator and an int value and folds the value into the accumulator.
int int_stack_fold(int_stack_t* stack, int initial, int_stack_fold_fn fold_fn);

/// @brief Sums the values of the stack.
/// @param stack The stack.
/// @return Sum of all values in the stack.
int int_stack_sum(int_stack_t* stack);

/// @brief Calculates the product of all values in the stack.
/// @param stack The stack.
/// @return Product of all values in the stack.
int int_stack_product(int_stack_t* stack);

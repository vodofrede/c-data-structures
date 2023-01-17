#include <stdlib.h>

/// @brief A double-ended queue with a front and back for easy insertion into both ends of the structure. Uses the FIFO-principle.
struct queue {
    size_t size;
    size_t capacity;
    int* buffer;
};

/// @brief Create a new queue with a default capacity of 32.
/// @return A new queue.
struct queue* queue_create();
/// @brief Create a new queue with specified maximum capacity.
/// @param capacity Capacity of the queue.
/// @return A new queue.
struct queue* queue_with_capacity(size_t capacity);
/// @brief Create a new queue from the specified array and size.
/// @param array An array.
/// @param size Size of the array.
/// @return A new queue.
struct queue* queue_from(int array[], size_t size);
/// @brief Destroy the queue, freeing it from memory.
/// @param queue The queue.
void queue_destroy(struct queue* queue);

size_t queue_len(struct queue* queue);
int queue_is_empty(struct queue* queue);
int queue_is_full(struct queue* queue);
int queue_is_contiguous(struct queue* queue);

void queue_reserve(struct queue* queue);
void queue_make_contiguous(struct queue* queue);
void queue_fill(struct queue* queue, int filler);
typedef int (*queue_fill_fn)();
void queue_fill_with(struct queue* queue, queue_fill_fn fill_fn);

int* queue_get(struct queue* queue, size_t index);
void queue_set(struct queue* queue, size_t index, int value);
int* queue_first(struct queue* queue);
int* queue_last(struct queue* queue);
/// @brief Take the front-most element in the queue.
/// @param queue The queue.
/// @return Front-most element.
int queue_pop_front(struct queue* queue);
/// @brief Take the back-most element in the queue.
/// @param queue The queue.
/// @return Back-most element.
int queue_pop_back(struct queue* queue);
/// @brief Push the value to the front of the queue.
/// @param queue The queue.
/// @param value Value to push.
void queue_push_front(struct queue* queue, int value);
/// @brief Push the value to the back of the queue.
/// @param queue The queue.
/// @param value Value to push.
void queue_push_back(struct queue* queue, int value);
int queue_remove(struct queue* queue, size_t index);
void queue_insert(struct queue* queue, size_t index, int value);

struct queue* queue_split_front(struct queue* queue, size_t index);
struct queue* queue_split_back(struct queue* queue, size_t index);
void queue_append(struct queue* queue, struct queue* other);
void queue_prepend(struct queue* queue, struct queue* other);
void queue_truncate_front(struct queue* queue, size_t index);
void queue_truncate_back(struct queue* queue, size_t index);
void queue_resize_front(struct queue* queue, size_t size, int filler);
void queue_resize_back(struct queue* queue, size_t size, int filler);
struct queue* queue_slice_front(struct queue* queue, size_t start, size_t stop);
struct queue* queue_slice_back(struct queue* queue, size_t start, size_t stop);

void queue_swap(struct queue* queue, size_t first, size_t second);
void queue_reverse(struct queue* queue);
void queue_rotate_right(struct queue* queue, size_t amount);
void queue_rotate_left(struct queue* queue, size_t amount);

typedef int (*queue_map_fn)(int);
typedef int (*queue_filter_fn)(int);
typedef void (*queue_fold_fn)(int*, int);

void queue_map(struct queue* queue, queue_map_fn map_fn);
void queue_filter(struct queue* queue, queue_map_fn filter_fn);
int* queue_find(struct queue* queue, queue_map_fn filter_fn);
int queue_fold(struct queue* queue, queue_map_fn fold_fn);
int queue_sum(struct queue* queue);
int queue_product(struct queue* queue);

void queue_sort(struct queue* queue);
void queue_sort_by(struct queue* queue, __compar_fn_t cmp);
size_t queue_search(struct queue* queue, int value);
int queue_contains(struct queue* queue, int value);
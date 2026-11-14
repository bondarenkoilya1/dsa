#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef struct Vector {
    size_t length;
    size_t capacity;
    int *items;
} Vector;


enum vector_status {
    VECTOR_OK = 0,
    VECTOR_ERR_NULL,
    VECTOR_ERR_EMPTY,
    VECTOR_ERR_INDEX,
    VECTOR_ERR_ALLOC,
    VECTOR_ERR_CAPACITY,
    VECTOR_NOT_FOUND
};

Vector *vector_init(size_t capacity);

enum vector_status vector_free(Vector *v);

// adds elements to the end of the vector (at v[length])
enum vector_status vector_push(Vector *v, int value);

/* vector_pop removes last element and returns it to the incoming pV.
    it accepts vector and pointer to the variable to save removed item
    warn: unsafe. leave removed elements as it is */
enum vector_status vector_pop(Vector *v, int *out);

// vector_peek reads last element without removing it
enum vector_status vector_peek(const Vector *v, int *out);

/* vector_insert places value at v[index], shifting every element from
    v[index] onward one position to the right, and increases the length by 1. */
enum vector_status vector_insert(Vector *v, size_t index, int value);

/* vector_remove deletes the element at v[index] by shifting every element
    after it one position to the left, then decreases the length by 1 */
enum vector_status vector_remove(Vector *v, size_t index);

/* vector_shrink releases the unused slots (indices length..capacity-1)
    by reducing capacity to max(length+spare, 1) */
enum vector_status vector_shrink(Vector *v, size_t spare);

/* vector_reserve grows capacity to at least new_cap.
    It never shrinks: if new_cap <= v->capacity, nothing happens. */
enum vector_status vector_reserve(Vector *v, size_t new_cap);

/* vector_find searches for value and writes its index to *out (only when FOUND).
    is_sorted == true:  binary search, v must be sorted ascending, returns ANY matching index.
    is_sorted == false: linear search, returns the FIRST matching index. */
enum vector_status vector_find(Vector *v, int value, size_t *out, bool is_sorted);

enum vector_status vector_reverse(Vector *v);

enum vector_status vector_sort(Vector *v);

bool vector_is_empty(const Vector *v);

enum vector_status vector_clear(Vector *v);

void vector_show(const Vector *v, bool show_empty);

enum vector_status vector_expand(Vector *v);

// vector_realloc reallocates memory to specified capacity for the vector
enum vector_status vector_realloc(Vector *v, size_t new_cap);

//  vector_copy(v)

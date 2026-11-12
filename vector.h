#pragma once
#include <stdbool.h>
#include <stddef.h>

struct Vector {
    size_t length;
    size_t capacity;
    int *items;
};

// start
struct Vector *vector_init(size_t capacity);
void vector_free(struct Vector *v);

// core operations
int vector_push(struct Vector *v, int value);
int vector_pop(struct Vector *v, int *out);
int vector_peek(const struct Vector *v, int *out);
int vector_insert(struct Vector *v, size_t index, int value);
int vector_remove(struct Vector *v, size_t index);

// state and utilities
bool vector_is_empty(const struct Vector *v);
int vector_clear(struct Vector *v);
void vector_show(const struct Vector *v, bool show_empty);
int vector_expand(struct Vector *v);

// Medium (memory)
//
//  vector_remove(v, index)
//  vector_shrink(v)
//  vector_reserve(v, new_cap)
//
// Harder (algorithms and pointers)
//
//  vector_find(v, value)
//  vector_reverse(v)
//  vector_sort(v)
//  vector_copy(v)
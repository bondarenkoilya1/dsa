#pragma once
#include <stdbool.h>
#include <stddef.h>

struct Vector {
    size_t length;
    size_t capacity;
    int *items;
};

struct Vector *vector_init(size_t capacity);
void vector_free(struct Vector *v);

int vector_push(struct Vector *v, int value);
int vector_pop(struct Vector *v, int *out);
int vector_peek(const struct Vector *v, int *out);
int vector_insert(struct Vector *v, size_t index, int value);
int vector_remove(struct Vector *v, size_t index);
int vector_shrink(struct Vector *v, size_t spare);
int vector_reserve(struct Vector *v, size_t new_cap);
enum binary_search_result vector_find(struct Vector *v, int value, size_t *out, bool is_sorted);
int vector_reverse(struct Vector *v);
int vector_sort(struct Vector *v);

bool vector_is_empty(const struct Vector *v);
int vector_clear(struct Vector *v);
void vector_show(const struct Vector *v, bool show_empty);
int vector_expand(struct Vector *v);
int vector_realloc(struct Vector *v, size_t new_cap);

//  vector_reverse(v)
//  vector_sort(v)
//  vector_copy(v)
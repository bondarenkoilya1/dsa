#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "vector.h"
#include "search.h"
#include "sort.h"


/* ---------- LIFECYCLE ---------- */

Vector *vector_init(const size_t capacity) {
    if (capacity == 0) return NULL;

    Vector *v = malloc(sizeof *v);
    if (v == NULL) return NULL;

    int *buff = malloc(capacity * sizeof *v->items);
    if (buff == NULL) {
        free(v);
        return NULL;
    }

    v->capacity = capacity;
    v->length = 0;
    v->items = buff;

    return v;
}

enum vector_status vector_free(Vector *v) {
    if (v == NULL) return VECTOR_ERR_NULL;
    free(v->items);
    free(v);
    return VECTOR_OK;
}

/* ---------- CORE OPERATIONS ---------- */

enum vector_status vector_push(Vector *v, const int value) {
    if (v == NULL) return VECTOR_ERR_NULL;
    if (v->length == v->capacity) {
        const enum vector_status st = vector_expand(v);
        if (st != VECTOR_OK) return st;
    }

    v->items[v->length] = value;
    v->length++;
    return VECTOR_OK;
}

enum vector_status vector_pop(Vector *v, int *out) {
    if (v == NULL) return VECTOR_ERR_NULL;
    if (v->length < 1) return VECTOR_ERR_EMPTY;

    v->length--;
    if (out != NULL) *out = v->items[v->length];

    return VECTOR_OK;
}

enum vector_status vector_peek(const Vector *v, int *out) {
    if (v == NULL) return VECTOR_ERR_NULL;
    if (v->length < 1) return VECTOR_ERR_EMPTY;

    if (out == NULL) return VECTOR_ERR_NULL;
    *out = v->items[v->length - 1];

    return VECTOR_OK;
}

enum vector_status vector_insert(Vector *v, const size_t index, const int value) {
    if (v == NULL) return VECTOR_ERR_NULL;
    if (index > v->length) return VECTOR_ERR_INDEX;

    if (v->length == v->capacity) {
        const enum vector_status st = vector_expand(v);
        if (st != VECTOR_OK) return st;
    }

    memmove(&v->items[index+1],
            &v->items[index],
            (v->length - index) * sizeof *v->items);

    v->items[index] = value;
    v->length++;

    return VECTOR_OK;
}

enum vector_status vector_remove(Vector *v, const size_t index) {
    if (v == NULL) return VECTOR_ERR_NULL;
    if (index >= v->length) return VECTOR_ERR_INDEX;


    memmove(&v->items[index],
            &v->items[index+1],
            (v->length - index - 1) * sizeof *v->items);

    v->length--;
    return VECTOR_OK;
}

enum vector_status vector_shrink(Vector *v, const size_t spare) {
    if (v == NULL) return VECTOR_ERR_NULL;
    if (spare >= v->capacity - v->length) return VECTOR_OK;

    size_t new_cap = v->length + spare;
    if (new_cap == 0) new_cap = 1;
    if (new_cap == v->capacity) return VECTOR_OK;

    return vector_realloc(v, new_cap);
}

enum vector_status vector_reserve(Vector *v, const size_t new_cap) {
    if (v == NULL) return VECTOR_ERR_NULL;
    if (new_cap <= v->capacity) return VECTOR_OK;

    return vector_realloc(v, new_cap);
}

enum vector_status vector_find(const Vector *v, const int value, size_t *out, const bool is_sorted) {
    if (v == NULL || out == NULL) return VECTOR_ERR_NULL;

    if (is_sorted) return binary_search(v, value, out);

    return linear_search(v, value, out);
}

enum vector_status vector_reverse(Vector *v) {
    if (v == NULL) return VECTOR_ERR_NULL;

    for (size_t i = 0; i < v->length / 2; i++) {
        const int tmp = v->items[i];
        v->items[i] = v->items[v->length - 1 - i];
        v->items[v->length - 1 - i] = tmp;
    }

    return VECTOR_OK;
}

enum vector_status vector_sort(Vector *v) {
    if (v == NULL) return VECTOR_ERR_NULL;

    return selection_sort(v);
}

/* ---------- STATE AND UTILITIES ---------- */

bool vector_is_empty(const Vector *v) {
    assert(v != NULL);
    return v->length == 0;
}

enum vector_status vector_clear(Vector *v) {
    if (v == NULL) return VECTOR_ERR_NULL;

    v->length = 0;

    return VECTOR_OK;
}

enum vector_status vector_show(const Vector *v, const bool show_empty) {
    if (v == NULL) return VECTOR_ERR_NULL;

    const size_t limit = show_empty ? v->capacity : v->length;

    for (size_t i = 0; i < limit; i++) {
        if (i < v->length)
            printf("| %d ", v->items[i]);
        else
            printf("| _ ");
    }
    printf("|  %zu/%zu\n", v->length, v->capacity);
    return VECTOR_OK;
}

enum vector_status vector_expand(Vector *v) {
    if (v == NULL) return VECTOR_ERR_NULL;

    if (v->capacity > SIZE_MAX / 2 / sizeof *v->items) return VECTOR_ERR_CAPACITY;

    const size_t new_cap = v->capacity * 2;

    return vector_realloc(v, new_cap);
}

enum vector_status vector_realloc(Vector *v, const size_t new_cap) {
    if (v == NULL) return VECTOR_ERR_NULL;
    if (new_cap == 0
        || new_cap < v->length
        || new_cap > SIZE_MAX / sizeof *v->items)
        return VECTOR_ERR_CAPACITY;


    int *tmp = realloc(v->items, new_cap * sizeof *v->items);
    if (tmp == NULL) return VECTOR_ERR_ALLOC;

    v->items = tmp;
    v->capacity = new_cap;

    return VECTOR_OK;
}

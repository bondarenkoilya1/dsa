#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "vector.h"
#include "search.h"

#include <assert.h>

int main(void) {
    struct Vector *v = vector_init(3);
    if (v == NULL) return EXIT_FAILURE;

    for (int i = 1; i <= 16; i++) vector_push(v, i);
    printf("After push: ");
    vector_show(v, 1);

    // Search: every value from 0 to 17, so we hit "less than all" and "greater than all"
    for (int x = 0; x <= 17; x++) {
        size_t idx;
        enum result r = vector_find(v, x, &idx, true);
        if (x >= 1 && x <= 16) assert(r == FOUND && v->items[idx] == x);
        else assert(r == NOT_FOUND);
    }

    // The rest: one call per function
    int value;
    vector_peek(v, &value);
    vector_pop(v, &value);
    vector_insert(v, 1, 99);
    vector_remove(v, 2);
    vector_reserve(v, 10);
    vector_shrink(v, 0);
    printf("After insert/remove/reserve/shrink: ");
    vector_show(v, 1);

    // Search on an empty vector
    vector_clear(v);
    size_t idx;
    assert(vector_find(v, 5, &idx, true) == NOT_FOUND);
    printf("Empty: %s\n", vector_is_empty(v) ? "yes" : "no");

    vector_free(v);
    return EXIT_SUCCESS;
}

/* ---------- start: lifecycle ---------- */

// vector_init creates an empty vector with the specified initial capacity.
struct Vector *vector_init(const size_t capacity) {
    if (capacity == 0) {
        fprintf(stderr, "vector_init: capacity cannot be equal to 0\n");
        return NULL;
    }

    struct Vector *v = malloc(sizeof *v);
    if (v == NULL) {
        return NULL;
    }

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

// vector_free frees the memory taken by vector items and the vector itself
void vector_free(struct Vector *v) {
    if (v == NULL) return;
    free(v->items);
    free(v);
}

/* ---------- middle: core operations ---------- */

int vector_push(struct Vector *v, const int value) {
    if (v == NULL) {
        fprintf(stderr, "vector_push: v == NULL\n");
        return EXIT_FAILURE;
    }

    if (v->length == v->capacity) vector_expand(v);

    v->items[v->length] = value;
    v->length++;
    return EXIT_SUCCESS;
}

// vector_pop removes last element and returns it to the incoming pV.
// it accepts vector and pointer to the variable to save removed item
// warn: unsafe. leave removed elements as it is
int vector_pop(struct Vector *v, int *out) {
    if (v == NULL || v->length < 1) {
        fprintf(stderr, "vector_pop: v == NULL or vector is empty\n");
        return EXIT_FAILURE;
    }

    v->length--;

    if (out != NULL) *out = v->items[v->length];

    return EXIT_SUCCESS;
}

// vector_peek reads last element without removing it
int vector_peek(const struct Vector *v, int *out) {
    if (v == NULL || v->length < 1) {
        fprintf(stderr, "vector_peek: v == NULL or vector is empty\n");
        return EXIT_FAILURE;
    }

    if (out == NULL) {
        fprintf(stderr, "vector_peek: out == NULL\n");
        return EXIT_FAILURE;
    }

    *out = v->items[v->length - 1];

    return EXIT_SUCCESS;
}

// vector_insert places value at v[index], shifting every element from
// v[index] onward one position to the right, and increases the length by 1.
int vector_insert(struct Vector *v, const size_t index, const int value) {
    if (v == NULL) {
        fprintf(stderr, "vector_insert: v == NULL\n");
        return EXIT_FAILURE;
    };

    if (index > v->length) {
        fprintf(stderr, "vector_insert: index out of bounds\n");
        return EXIT_FAILURE;
    }

    if (v->length == v->capacity) vector_expand(v);

    for (size_t i = v->length; i > index; i--) {
        v->items[i] = v->items[i - 1];
    }
    v->items[index] = value;
    v->length++;

    return EXIT_SUCCESS;
}

// vector_remove deletes the element at v[index] by shifting every element
// after it one position to the left, then decreases the length by 1
int vector_remove(struct Vector *v, const size_t index) {
    if (v == NULL) {
        fprintf(stderr, "vector_remove: v == NULL\n");
        return EXIT_FAILURE;
    }

    if (index >= v->length) {
        fprintf(stderr, "vector_remove: index out of bounds\n");
        return EXIT_FAILURE;
    }

    for (size_t i = index; i + 1 < v->length; i++) {
        v->items[i] = v->items[i + 1];
    }
    v->length--;
    return EXIT_SUCCESS;
}

// vector_shrink releases the unused slots (indices length..capacity-1)
// by reducing capacity to max(length+spare, 1)
int vector_shrink(struct Vector *v, const size_t spare) {
    if (v == NULL) {
        fprintf(stderr, "vector_shrink: v == NULL\n");
        return EXIT_FAILURE;
    }

    if (spare >= v->capacity - v->length) return EXIT_SUCCESS;

    size_t new_cap = v->length + spare;
    if (new_cap == 0) new_cap = 1;
    if (new_cap == v->capacity) return EXIT_SUCCESS;

    return vector_realloc(v, new_cap);
}

// vector_reserve grows capacity to at least new_cap.
// It never shrinks: if new_cap <= v->capacity, nothing happens.
int vector_reserve(struct Vector *v, const size_t new_cap) {
    if (v == NULL) {
        fprintf(stderr, "vector_reserve: v == NULL\n");
        return EXIT_FAILURE;
    }

    if (new_cap <= v->capacity) return EXIT_SUCCESS;

    return vector_realloc(v, new_cap);
}

// vector_find searches for value and writes its index to *out (only when FOUND).
// is_sorted == true:  binary search, v must be sorted ascending, returns ANY matching index.
// is_sorted == false: linear search, returns the FIRST matching index.
enum result vector_find(struct Vector *v, const int value, size_t *out, const bool is_sorted) {
    if (v == NULL) {
        fprintf(stderr, "vector_find: v == NULL\n");
        return ERROR;
    }

    if (out == NULL) {
        fprintf(stderr, "vector_find: out == NULL\n");
        return ERROR;
    }

    if (is_sorted) return bs(v, value, out);

    for (size_t i = 0; i < v->length; i++) {
        if (v->items[i] == value) {
            *out = i;
            return FOUND;
        }
    }

    return NOT_FOUND;
}


/* ---------- end: state and utilities ---------- */

bool vector_is_empty(const struct Vector *v) {
    assert(v != NULL);
    return v->length == 0;
}

int vector_clear(struct Vector *v) {
    if (v == NULL) {
        fprintf(stderr, "vector_clear: v == NULL\n");
        return EXIT_FAILURE;
    };

    v->length = 0;

    return EXIT_SUCCESS;
}

void vector_show(const struct Vector *v, const bool show_empty) {
    if (v == NULL) {
        fprintf(stderr, "vector_show: v == NULL\n");
        return;
    }

    const size_t limit = show_empty ? v->capacity : v->length;

    for (size_t i = 0; i < limit; i++) {
        if (i < v->length)
            printf("| %d ", v->items[i]);
        else
            printf("| _ ");
    }
    printf("|  %zu/%zu\n", v->length, v->capacity);
}

int vector_expand(struct Vector *v) {
    if (v == NULL) {
        fprintf(stderr, "vector_expand: v == NULL\n");
        return EXIT_FAILURE;
    }

    if (v->capacity > SIZE_MAX / 2 / sizeof *v->items) {
        fprintf(stderr, "vector_expand: capacity too large\n");
        return EXIT_FAILURE;
    }

    const size_t new_cap = v->capacity * 2;

    return vector_realloc(v, new_cap);
}

// vector_realloc reallocates memory to specified capacity for the vector
int vector_realloc(struct Vector *v, const size_t new_cap) {
    if (v == NULL) {
        fprintf(stderr, "vector_realloc: v == NULL\n");
        return EXIT_FAILURE;
    }

    if (new_cap == 0) {
        fprintf(stderr, "vector_realloc: capacity cannot be equal to 0\n");
        return EXIT_FAILURE;
    }

    if (new_cap > SIZE_MAX / sizeof *v->items) {
        fprintf(stderr, "vector_realloc: capacity too large\n");
        return EXIT_FAILURE;
    }

    if (new_cap < v->length) {
        fprintf(stderr, "vector_realloc: new capacity cannot be smaller than v->length\n");
        return EXIT_FAILURE;
    }


    int *tmp = realloc(v->items, new_cap * sizeof *v->items);
    if (tmp == NULL) {
        fprintf(stderr, "vector_realloc: realloc failed\n");
        return EXIT_FAILURE;
    }
    v->items = tmp;
    v->capacity = new_cap;

    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

#include <assert.h>
#include <stdbool.h>

int main(void) {
    struct Vector *v = vector_init(4);
    printf("empty: %d\n", vector_is_empty(v));

    for (int i = 1; i <= 5; i++) vector_push(v, i);
    vector_show(v, 1);

    int out = 0;
    vector_peek(v, &out);
    printf("peek: %d\n", out);
    vector_pop(v, &out);
    printf("pop: %d\n", out);
    vector_show(v, 1);

    vector_insert(v, 0, 9);
    vector_show(v,0);
    vector_insert(v, 2, 8);
    vector_show(v,0);
    vector_insert(v, v->length, 99);
    vector_insert(v, v->length, 100);
    vector_show(v,0);
    vector_insert(v, v->length, 101);
    vector_show(v,1);

    vector_clear(v);
    vector_show(v,1);
    printf("empty: %d\n", vector_is_empty(v));

    vector_free(v);
    return EXIT_SUCCESS;
}

/* ---------- start: lifecycle ---------- */

struct Vector *vector_init(const size_t capacity) {
    if (capacity == 0) {
        printf("capacity == 0\n");
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

void vector_free(struct Vector *v) {
    if (v == NULL) return;
    free(v->items);
    free(v);
}

/* ---------- middle: core operations ---------- */

int vector_push(struct Vector *v, const int value) {
    if (v == NULL) {
        printf("v == NULL\n");
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
        printf("v == NULL or v.length < 1\n");
        return EXIT_FAILURE;
    }

    v->length--;

    if (out != NULL) *out = v->items[v->length];

    return EXIT_SUCCESS;
}

// vector_peek reads last element without removing it
int vector_peek(const struct Vector *v, int *out) {
    if (v == NULL || v->length < 1) {
        printf("v == NULL or v.length < 1\n");
        return EXIT_FAILURE;
    }

    if (out == NULL) {
        printf("out == NULL\n");
        return EXIT_FAILURE;
    }

    *out = v->items[v->length - 1];

    return EXIT_SUCCESS;
}

// vector_insert places a new value at v[index] and shifts all elements
// from v[index] onward one position to the right
int vector_insert(struct Vector *v, const size_t index, const int value) {
    if (v == NULL) {
        printf("v == NULL\n");
        return EXIT_FAILURE;
    };

    if (index > v->length || (int) index < 0) {
        printf("index out of bounds\n");
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

/* ---------- end: state and utilities ---------- */

bool vector_is_empty(const struct Vector *v) {
    assert(v != NULL);
    return v->length == 0;
}

int vector_clear(struct Vector *v) {
    if (v == NULL) {
        printf("v == NULL\n");
        return EXIT_FAILURE;
    };

    v->length = 0;

    return EXIT_SUCCESS;
}

void vector_show(const struct Vector *v, const bool show_empty) {
    if (v == NULL) {
        printf("v == NULL\n");
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
    const size_t new_cap = v->capacity > SIZE_MAX / 2 / sizeof *v->items
                               ? 0
                               : v->capacity * 2;

    if (new_cap == 0) {
        printf("memory overflow during new_cap assignation\n");
        return EXIT_FAILURE;
    }

    int *tmp = realloc(v->items, new_cap * sizeof *v->items);
    if (tmp == NULL) {
        return EXIT_FAILURE;
    }
    v->items = tmp;
    v->capacity = new_cap;
    return EXIT_SUCCESS;
}

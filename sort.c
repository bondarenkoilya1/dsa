#include "sort.h"

#include <stdio.h>
#include <stdlib.h>


int selection_sort(struct Vector *v) {
    if (v == NULL) {
        fprintf(stderr, "selection_sort: v == NULL\n");
        return EXIT_FAILURE;
    };

    struct Vector *copy = vector_init(v->capacity);
    copy->length = v->length;
    for (size_t i = 0; i < v->length; i++) {
        copy->items[i] = v->items[i];
    }

    for (size_t i = 0; i < v->length; i++) {
        size_t smallest_index;
        find_smallest(copy, &smallest_index);
        const int smallest = copy->items[smallest_index];
        vector_remove(copy, smallest_index);
        v->items[i] = smallest;
    }

    vector_free(copy);
    return EXIT_SUCCESS;
}

int find_smallest(const struct Vector *v, size_t *out) {
    size_t smallest_index = 0;

    for (size_t i = 1; i < v->length; i++) {
        if (v->items[i] < v->items[smallest_index]) {
            smallest_index = i;
        }
    }

    *out = smallest_index;
    return EXIT_SUCCESS;
}


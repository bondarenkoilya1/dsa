#include "search.h"

#include <stdio.h>


// Binary search
enum result bs(struct Vector *v, const int value, size_t *out) {
    if (v == NULL) {
        fprintf(stderr, "vector_bs: v == NULL\n");
        return ERROR;
    }

    if (out == NULL) {
        fprintf(stderr, "vector_bs: out == NULL\n");
        return ERROR;
    }

    if (v->length == 0) return NOT_FOUND;

    size_t low = 0;
    size_t high = v->length - 1;

    while (low <= high) {
        const size_t mid = low + (high - low) / 2;
        const int guess = v->items[mid];

        if (guess == value) {
            *out = mid;
            return FOUND;
        }

        if (guess < value) {
            low = mid + 1;
        } else {
            if (mid == 0) break;
            high = mid - 1;
        }
    }

    return NOT_FOUND;
}

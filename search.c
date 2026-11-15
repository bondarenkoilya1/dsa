#include "search.h"

#include <stdio.h>


enum vector_status binary_search(const Vector *v, const int value, size_t *out) {
    if (v == NULL || out == NULL) return VECTOR_ERR_NULL;
    if (v->length == 0) return VECTOR_NOT_FOUND;

    size_t low = 0;
    size_t high = v->length - 1;

    while (low <= high) {
        const size_t mid = low + (high - low) / 2;
        const int guess = v->items[mid];

        if (guess == value) {
            *out = mid;
            return VECTOR_OK;
        }

        if (guess < value) {
            low = mid + 1;
        } else {
            if (mid == 0) break;
            high = mid - 1;
        }
    }

    return VECTOR_NOT_FOUND;
}

enum vector_status linear_search(const Vector *v, const int value, size_t *out) {
    if (v == NULL || out == NULL) return VECTOR_ERR_NULL;
    if (v->length == 0) return VECTOR_NOT_FOUND;

    for (size_t i = 0; i < v->length; i++) {
        if (v->items[i] == value) {
            *out = i;
            return VECTOR_OK;
        }
    }

    return VECTOR_NOT_FOUND;
}
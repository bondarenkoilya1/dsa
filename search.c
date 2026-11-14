#include "search.h"

#include <stdio.h>


// binary search
enum vector_status bs(struct Vector *v, const int value, size_t *out) {
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

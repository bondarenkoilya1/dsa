#include "sort.h"

static size_t find_smallest(const Vector *v, const size_t start) {
    size_t smallest = start;

    for (size_t i = start + 1; i < v->length; i++) {
        if (v->items[i] < v->items[smallest]) smallest = i;
    }

    return smallest;
}

enum vector_status selection_sort(const Vector *v) {
    if (v == NULL) return VECTOR_ERR_NULL;

    for (size_t i = 0; i + 1 < v->length; i++) {
        const size_t smallest = find_smallest(v, i);

        if (smallest != i) {
            const int tmp = v->items[i];
            v->items[i] = v->items[smallest];
            v->items[smallest] = tmp;
        }
    }

    return VECTOR_OK;
}

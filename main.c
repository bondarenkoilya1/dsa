#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// #include "vector.h"
#include "list.h"

int main(void) {
  List l;
  list_init(&l);
  list_unshift(&l, 3);
  list_unshift(&l, 7);
  list_unshift(&l, 9);
  list_unshift(&l, 1);
  list_show(&l);
  list_remove(&l, 2);
}

/* int main(void) {
    Vector *v = vector_init(3);
    if (v == NULL) return EXIT_FAILURE;

    for (int i = 1; i <= 16; i++) vector_push(v, i);
    printf("After push: ");
    vector_show(v, 1);

    // Search: every value from 0 to 17, so we hit "less than all" and
    "greater than all" for (int x = 0; x <= 17; x++) {
        size_t idx;
        const enum vector_status r = vector_find(v, x, &idx, true);
        if (x >= 1 && x <= 16)
            assert(r == VECTOR_OK && v->items[idx] == x);
        else
            assert(r == VECTOR_NOT_FOUND);
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

    vector_reverse(v);
    printf("After reverse: ");
    vector_show(v, 1);

    vector_sort(v);
    printf("After sort: ");
    vector_show(v, 1);

    // Search on an empty vector
    vector_clear(v);
    size_t idx;
    assert(vector_find(v, 5, &idx, true) == VECTOR_NOT_FOUND);
    printf("Empty: %s\n", vector_is_empty(v) ? "yes" : "no");

    vector_free(v);
    return EXIT_SUCCESS;
} */
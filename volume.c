#include <stdio.h>
#include <stdlib.h>
#include "volume.h"

#include <assert.h>
#include <stdbool.h>

int main(void) {
    struct Volume *v = volume_init(4);
    printf("empty: %d\n", volume_is_empty(v));

    for (int i = 1; i <= 5; i++) volume_push(v, i);
    volume_show(v);

    int out = 0;
    volume_peek(v, &out);
    printf("peek: %d\n", out);
    volume_pop(v, &out);
    printf("pop: %d\n", out);
    volume_show(v);

    volume_insert(v, 0, 9); // start
    volume_show(v);
    volume_insert(v, 2, 8); // middle
    volume_show(v);

    volume_clear(v);
    volume_show(v);
    printf("empty: %d\n", volume_is_empty(v));

    volume_free(v);
    return EXIT_SUCCESS;
}

/* ---------- start: lifecycle ---------- */

struct Volume *volume_init(const size_t capacity) {
    if (capacity == 0) {
        printf("capacity == 0\n");
        return NULL;
    }

    struct Volume *v = malloc(sizeof *v);
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

void volume_free(struct Volume *v) {
    if (v == NULL) return;
    free(v->items);
    free(v);
}

/* ---------- middle: core operations ---------- */

int volume_push(struct Volume *v, const int value) {
    if (v == NULL) {
        printf("v == NULL\n");
        return EXIT_FAILURE;
    }

    if (v->length == v->capacity) {
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
    }

    v->items[v->length] = value;
    v->length++;
    return EXIT_SUCCESS;
}

// volume_pop removes last element and returns it to the incoming pV.
// it accepts volume and pointer to the variable to save removed item
// warn: unsafe. leave removed elements as it is
int volume_pop(struct Volume *v, int *out) {
    if (v == NULL || v->length < 1) {
        printf("v == NULL or v.length < 1\n");
        return EXIT_FAILURE;
    }

    v->length--;

    if (out != NULL) *out = v->items[v->length];

    return EXIT_SUCCESS;
}

// volume_peek reads last element without removing it
int volume_peek(const struct Volume *v, int *out) {
    if (v == NULL || v->length < 1) {
        printf("v == NULL or v.length < 1\n");
        return EXIT_FAILURE;
    }

    if (out == NULL) {
        printf("out == NULL\n");
        return EXIT_FAILURE;
    }

    *out = v->items[v->length-1];

    return EXIT_SUCCESS;
}

// volume_insert places a new value at v[index] and shifts all elements
// from v[index] onward one position to the right
int volume_insert(struct Volume *v, const size_t index, const int value) {
    if (v == NULL) {
        printf("v == NULL\n");
        return EXIT_FAILURE;
    };

    if (index > v->length || (int)index < 0) {
        printf("index out of bounds\n");
        return EXIT_FAILURE;
    }

    // todo: here we shrink
    if (v->capacity == v->length) {
        printf("capacity overflow\n");
        return EXIT_FAILURE;
    }

    for (size_t i = v->length; i > index; i--) {
        v->items[i] = v->items[i - 1];
    }
    v->items[index] = value;
    v->length++;

    return EXIT_SUCCESS;
}

/* ---------- end: state and utilities ---------- */

bool volume_is_empty(const struct Volume *v) {
    assert(v != NULL);
    return v->length == 0;
}

int volume_clear(struct Volume *v) {
    if (v == NULL) {
        printf("v == NULL\n");
        return EXIT_FAILURE;
    };

    v->length = 0;

    return EXIT_SUCCESS;
}

void volume_show(const struct Volume *v) {
    if (v == NULL) {
        printf("v == NULL\n");
        return;
    }

    for (size_t i = 0; i < v->capacity; i++) {
        if (i < v->length)
            printf("| %d ", v->items[i]);
        else
            printf("| _ ");
    }
    printf("|  %zu/%zu\n", v->length, v->capacity);
}
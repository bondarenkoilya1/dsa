#include <stdio.h>
#include <stdlib.h>
#include "volume.h"

#include <assert.h>
#include <stdbool.h>

int main(void) {
    struct Volume *v = volume_init(10);
    printf("volume empty: %d\n", volume_is_empty(v));
    for (int i = 0; i < 7; i++) {
        volume_push(v, i + 1);
    }

    int out = 0;

    volume_show(v);
    volume_pop(v, &out);
    volume_show(v);
    printf("out: %d\n", out);
    volume_push(v, 5);
    volume_show(v);

    for (int i = 0; i < 7; i++) {
        volume_push(v, i + 7);
        volume_show(v);
    }

    volume_free(v);
    return EXIT_SUCCESS;
}

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

int volume_push(struct Volume *v, const int value) {
    if (v == NULL) {
        printf("v == NULL\n");
        return EXIT_FAILURE;
    }

    if (v->length == v->capacity) {
        size_t new_cap = v->capacity > SIZE_MAX / 2 / sizeof *v->items
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

int volume_clear(struct Volume *v) {
    if (v == NULL) {
        printf("v == NULL\n");
        return EXIT_FAILURE;
    };

    v->length = 0;

    return EXIT_SUCCESS;
}

bool volume_is_empty(const struct Volume *v) {
    assert(v != NULL);
    return v->length == 0;
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

int volume_insert(struct Volume *v, const int index, const int value) {
    if (v == NULL) {
        printf("v == NULL\n");
        return EXIT_FAILURE;
    };



}
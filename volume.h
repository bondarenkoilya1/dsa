#pragma once
#include <stdbool.h>
#include <stddef.h>

struct Volume {
    size_t length;
    size_t capacity;
    int *items;
};

//

struct Volume *volume_init(size_t capacity);
void volume_free(struct Volume *v);
void volume_show(const struct Volume *v);
int volume_clear(struct Volume *v);
bool volume_is_empty(const struct Volume *v);

int volume_push(struct Volume *v, int value);
int volume_pop(struct Volume *v, int *out);
int volume_peek(const struct Volume *v, int *out);


// Medium (memory)
//
//  volume_insert(v, index, value)
//  volume_remove(v, index)
//  volume_shrink(v)
//  volume_reserve(v, new_cap)
//  grow (private helper, reused by push, insert, reserve)
//
// Harder (algorithms and pointers)
//
//  volume_find(v, value)
//  volume_reverse(v)
//  volume_sort(v)
//  volume_copy(v)
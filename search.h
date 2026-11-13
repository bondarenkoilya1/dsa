#pragma once

#include <stddef.h>
#include "vector.h"

enum binary_search_result {
    ERROR = -1,
    FOUND = 0,
    NOT_FOUND = 1,
};

enum binary_search_result bs(struct Vector *v, int value, size_t *out);


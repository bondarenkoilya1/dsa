#pragma once

#include <stddef.h>
#include "vector.h"

enum vector_status binary_search(const Vector *v, int value, size_t *out);

enum vector_status linear_search(const Vector *v, int value, size_t *out);

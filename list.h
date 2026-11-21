#pragma once
#include <stdbool.h>
#include <stddef.h>

/* ---------- TYPES ---------- */

typedef struct Node {
  int value;         // 4 (+4 padding)
  struct Node *next; // 8
} Node;              // 16 bytes total

typedef struct List {
  size_t length; // 8 bytes on x64
  Node *head;    // 8; first element
  Node *tail;    // 8; last element
} List;

enum list_status {
  LIST_OK,        // success
  LIST_ERR,       // generic error
  LIST_ERR_NULL,  // NULL pointer passed
  LIST_ERR_ALLOC, // malloc failed
  LIST_ERR_EMPTY, // list has no elements
  LIST_ERR_INDEX  // index out of range
};

/* ---------- PUBLIC API ---------- */

enum list_status list_init(List *l);
enum list_status list_free(List *l);
enum list_status list_insert(List *l, size_t index, int value);
enum list_status list_remove(List *l, size_t index);
enum list_status list_show(const List *l);
enum list_status list_copy(List *l, List *out);
enum list_status list_clear(List *l);
bool list_is_empty(const List *l);

// add getters, setters, clear (to 0s), reverse< sort, find
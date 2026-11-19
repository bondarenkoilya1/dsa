#include "stddef.h"

typedef struct Node {
  int value;         // 4
  struct Node *next; // 8
} Node;              // mem rounds up to 16

typedef struct List {
  size_t length; // 8 bytes on x64
  Node *head;    // 8; Is the first element
  Node *tail;    // 8; Is the last element
} List;

enum list_status {
  LIST_OK,
  LIST_ERR,
  LIST_ERR_NULL,
  LIST_ERR_ALLOC,
  LIST_ERR_EMPTY
};

enum list_status list_init(List *l);

// adds elements at the start
enum list_status list_unshift(List *l, int value);

// adds elements at the end
enum list_status list_push(List *l, int value);

// removes element from the end
enum list_status list_pop(List *l);

// removes element from the start
enum list_status list_shift(List *l);

enum list_status list_show(List *l);
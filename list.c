#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

/* ---------- INIT ---------- */

enum list_status list_init(List *l) {
  if (l == NULL) {
    return LIST_ERR_NULL;
  }

  l->head = NULL;
  l->tail = NULL;
  l->length = 0;
  return LIST_OK;
}

enum list_status list_free(List *l) {
  if (l == NULL) {
    return LIST_ERR_NULL;
  }

  Node *current = l->head;
  while (current != NULL) {
    Node *next = current->next;
    free(current);
    current = next;
  }

  l->head = NULL;
  l->tail = NULL;
  l->length = 0;

  return LIST_OK;
}

enum list_status list_get(const List *l, size_t index, Node **out) {
  if (l == NULL || out == NULL) {
    return LIST_ERR_NULL;
  }

  if (l->head == NULL) {
    return LIST_NOT_FOUND;
  }

  if (index >= l->length) {
    return LIST_ERR_INDEX;
  }

  Node *current = l->head;
  for (size_t i = 0; i < index; i++) {
    current = current->next;
  }

  *out = current;
  return LIST_OK;
}

enum list_status list_set(List *l, size_t index, int value) {
  if (l == NULL || l->head == NULL) {
    return LIST_ERR_NULL;
  }

  if (index >= l->length) {
    return LIST_ERR_INDEX;
  }

  Node *current = l->head;
  for (size_t i = 0; i < index; i++) {
    current = current->next;
  }

  current->value = value;
  return LIST_OK;
}

/* ---------- START OF LIST ---------- */

static enum list_status list_unshift(List *l, int value) {
  if (l == NULL) {
    return LIST_ERR_NULL;
  }

  Node *buff = malloc(sizeof(Node));
  if (buff == NULL) {
    return LIST_ERR_ALLOC;
  }
  buff->value = value;
  buff->next = l->head;
  l->head = buff;

  if (l->length == 0) {
    l->tail = buff;
  }

  l->length++;
  return LIST_OK;
}

static enum list_status list_shift(List *l) {
  if (l == NULL) {
    return LIST_ERR_NULL;
  }

  if (l->head == NULL || l->length == 0) {
    return LIST_ERR_EMPTY;
  }

  Node *tmp = l->head;
  l->head = tmp->next;

  if (l->head == NULL) {
    l->tail = NULL;
  }

  free(tmp);
  l->length--;

  return LIST_OK;
}

/* ---------- END OF LIST ---------- */

static enum list_status list_push(List *l, int value) {
  if (l == NULL) {
    return LIST_ERR_NULL;
  }

  Node *buff = malloc(sizeof(Node));
  if (buff == NULL) {
    return LIST_ERR_ALLOC;
  }
  buff->value = value;
  buff->next = NULL;

  if (l->length == 0) {
    l->head = buff;
  } else {
    l->tail->next = buff;
  }

  l->tail = buff;
  l->length++;

  return LIST_OK;
}

static enum list_status list_pop(List *l) {
  if (l == NULL) {
    return LIST_ERR_NULL;
  }

  if (l->head == NULL) {
    return LIST_ERR_EMPTY;
  }

  // single element
  if (l->head == l->tail) {
    free(l->head);
    l->head = NULL;
    l->tail = NULL;
    l->length = 0;
    return LIST_OK;
  }

  // find the node right before the tail
  for (Node *current = l->head;; current = current->next) {
    if (current->next == l->tail) {
      free(l->tail);
      current->next = NULL;
      l->tail = current;
      l->length--;
      return LIST_OK;
    }
  }

  return LIST_ERR;
}

/* ---------- ARBITRARY POSITION ---------- */

enum list_status list_insert(List *l, size_t index, int value) {
  if (l == NULL) {
    return LIST_ERR_NULL;
  }

  if (index > l->length) {
    return LIST_ERR_INDEX;
  }

  if (index == 0) {
    return list_unshift(l, value);
  }

  if (index == l->length) {
    return list_push(l, value);
  }

  Node *prev = l->head;
  for (size_t i = 0; i < index - 1; i++) {
    prev = prev->next;
  }

  Node *buff = malloc(sizeof(Node));
  if (buff == NULL) {
    return LIST_ERR_ALLOC;
  }
  buff->value = value;
  buff->next = prev->next;

  prev->next = buff;
  l->length++;
  return LIST_OK;
}

enum list_status list_remove(List *l, size_t index) {
  if (l == NULL) {
    return LIST_ERR_NULL;
  }

  if (index >= l->length) {
    return LIST_ERR_INDEX;
  }

  if (index == 0) {
    return list_shift(l);
  }

  if (index == l->length - 1) {
    return list_pop(l);
  }

  // walk to the node before the target
  Node *prev = l->head;
  for (size_t i = 0; i < index - 1; i++) {
    prev = prev->next;
  }

  Node *target = prev->next;
  prev->next = target->next;
  free(target);
  l->length--;

  return LIST_OK;
}

/* ---------- UTILS ---------- */

enum list_status list_show(const List *l) {
  if (l == NULL) {
    return LIST_ERR_NULL;
  }

  putchar('[');
  for (const Node *current = l->head; current != NULL;
       current = current->next) {
    if (current != l->head) {
      printf(", ");
    }
    printf("%d", current->value);
  }
  puts("]");

  return LIST_OK;
}

enum list_status list_copy(List *l, List *out) {
  if (l == NULL || out == NULL) {
    return LIST_ERR_NULL;
  }

  if (l == out) {
    return LIST_ERR;
  }

  size_t counter = 0;

  list_init(out);
  Node *current = l->head;
  while (current != NULL) {
    enum list_status res = list_insert(out, counter++, current->value);
    if (res != LIST_OK) {
      list_free(out);
      return res;
    }
    current = current->next;
  }

  return LIST_OK;
}

enum list_status list_clear(List *l) {
  if (l == NULL || l->head == NULL) {
    return LIST_ERR_NULL;
  }

  Node *current = l->head;
  while (current != NULL) {
    current->value = 0;
    current = current->next;
  }

  return LIST_OK;
}

bool list_is_empty(const List *l) {
  if (l == NULL) {
    return true;
  }

  assert((l->length == 0) == (l->head == NULL));
  assert((l->length == 0) == (l->tail == NULL));

  return l->length == 0;
}
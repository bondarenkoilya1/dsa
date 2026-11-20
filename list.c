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
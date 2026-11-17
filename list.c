#include "list.h"
#include "stdio.h"
#include "stdlib.h"

enum list_status list_init(List *l) {
  l->head = NULL;
  l->tail = NULL;
  l->length = 0;
  return LIST_OK;
}

enum list_status list_unshift(List *l, int value) {
  if (l == NULL)
    return LIST_ERR_NULL;

  Node *buff = malloc(sizeof(Node));
  if (buff == NULL)
    return LIST_ERR_ALLOC;
  buff->next = l->head;
  buff->value = value;
  l->head = buff;

  if (l->length == 0) {
    l->tail = buff;
  }

  l->length++;
  return LIST_OK;
}

enum list_status list_show(List *l) {
  if (l == NULL || l->head == NULL)
    return LIST_ERR_NULL;

  putchar('[');
  for (Node *current = l->head; current != NULL; current = current->next) {
    if (current != l->head)
      printf(", ");
    printf("%d", current->value);
  }
  puts("]");

  return LIST_OK;
}
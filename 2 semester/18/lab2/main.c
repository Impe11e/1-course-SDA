#include <stdio.h>
#include <stdlib.h>

#define old_chunk 10
#define new_chunk 5

int sign(int value) { return value == 0 ? 0 : value > 0 ? 1 : -1; }

enum Status {
  success = 0,
  error = 1,
};

typedef struct Node {
  int data;
  struct Node *prev;
  struct Node *next;
} Node;

Node *create_node(int data) {
  Node *new = (Node *)malloc(sizeof(Node));

  if (!new) {
    printf("Memmory allocation error\n");
    exit(error);
  }

  new->data = data;
  new->prev = NULL;
  new->next = NULL;
  return new;
}

void append(Node **head, int data) {
  Node *new = create_node(data);

  if (*head == NULL) {
    *head = new;
    return;
  }

  Node *temp = *head;

  while (temp->next != NULL) {
    temp = temp->next;
  }

  temp->next = new;
  new->prev = temp;
}

void swap(Node *prt1, Node *ptr2) {
  int temp = prt1->data;
  prt1->data = ptr2->data;
  ptr2->data = temp;
}

Node *goto_next(Node *ptr, int steps) {
  while (ptr && steps > 0) {
    ptr = ptr->next;
    steps--;
  }

  return ptr;
}

void print_list(Node *head) {
  while (head) {
    printf("%d ", head->data);
    head = head->next;
  }

  printf("\n");
}

void free_list(Node *head) {
  Node *temp;

  while (head) {
    temp = head;
    head = head->next;
    free(temp);
  }
}

void reorder_list(Node *head) {
  if (!head) {
    return;
  }

  Node *current = head, *ptr1, *ptr2, *next1, *next2;

  while (current) {
    ptr1 = goto_next(current, new_chunk);
    ptr2 = goto_next(ptr1, new_chunk);

    for (int i = 0; i < new_chunk; i++) {
      next1 = ptr1->next;
      next2 = ptr2->next;

      swap(ptr1, ptr2);

      ptr1 = next1;
      ptr2 = next2;
    }

    current = goto_next(current, old_chunk * 2);
  }
}

int main() {
  int count;

  printf("Input count of element (multiple 20): ");
  scanf("%d", &count);

  if (count <= 0 || count % 20 != 0) {
    printf("Invalid count\n");
    return error;
  }

  Node *head = NULL;

  int value, sgn = -1;
  for (int i = 0; i < count; i++) {
    if (i % old_chunk == 0) {
      sgn *= -1;
    }

    scanf("%d", &value);

    if (sign(value) != sgn) {
      printf("Invalid value\n");
      return error;
    }

    append(&head, value);
  }

  printf("Start list:\n");
  print_list(head);

  reorder_list(head);

  printf("Reordered list:\n");
  print_list(head);

  free_list(head);
  return success;
}

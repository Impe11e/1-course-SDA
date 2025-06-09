#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct List {
    double data;
    struct List* next;
    struct List* prev;
} List;

void InputNumberOfElements(int* n) {
    printf("Enter the number of elements:");
    if (scanf("%d", n) != 1 || *n <= 0) {
        printf("\nInvalid input\n");
        exit(EXIT_FAILURE);
    }
}

void Append(List** head, const double value) {
    List* newNode = malloc(sizeof(List));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = value;

    if (!*head) {
        newNode->next = newNode->prev = newNode;
        *head = newNode;
    } else {
        List* tail = (*head)->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = *head;
        (*head)->prev = newNode;
    }
}

double RandomRange(const double min, const double max) {
    return min + rand() / (RAND_MAX / (max - min));
}

void FillListWithRandomValues(List** head, const int n) {
    for (int i = 0; i < n; i++) {
        double randValue = RandomRange(-10.0, 10.0);
        double roundedValue = round(randValue * 100) / 100;
        Append(head, roundedValue);
    }
}

void PrintList(List* head) {
    if (!head) return;

    List* temp = head;

    printf("\nRandomly filled list:\n");
    do {
        printf("%.2lf ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

void ComputeExpression(List* head, const int n) {
    if (!head) return;

    List* left = head;
    List* right = head->prev;
    double sum = 0;

    for (int i = 0; i < n / 2; i++) {
        sum += left->data * right->data * 2;
        left = left->next;
        right = right->prev;
    }

    if ((n & 1) != 0) {
        sum += left->data * left->data;
    }

    printf("\nResult: %.2lf\n", sum);
}

void FreeList(List** head) {
    if (!*head) return;

    List* current = *head;

    printf("\nFreeing memory:\n");
    do {
        List *temp = current;
        current = current->next;
        printf("Freeing up: %.2lf\n", temp->data);
        free(temp);
    } while (current != *head);

    *head = NULL;
    printf("Memory freeing completed\n");
}

int main() {
    srand(time(NULL));

    int n;
    List* head = NULL;

    InputNumberOfElements(&n);

    FillListWithRandomValues(&head, n);
    PrintList(head);
    ComputeExpression(head, n);

    FreeList(&head);

    return 0;
}
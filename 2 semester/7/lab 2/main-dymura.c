#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int data;
    struct ListNode* next;
    struct ListNode* prev;
} ListNode;

ListNode* createNode(const int data)
{
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void pushBack(ListNode** tail, const int data)
{
    ListNode* newNode = createNode(data);

    if (*tail == NULL) {
        *tail = newNode;
        return;
    }

    ListNode* temp = *tail;
    temp->next = newNode;
    newNode->prev = temp;

    *tail = newNode;
}

void printListForward(ListNode* head)
{
    ListNode* temp = head;
    printf("List: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void clearListFromHead(ListNode* head) {
    ListNode* temp = head;
    while (temp != NULL) {
        ListNode* next = temp->next;
        free(temp);
        temp = next;
    }
}

int main(void) {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    ListNode* head = NULL;
    pushBack(&head, 1);

    ListNode* tail = head;
    for (int i = 2; i <= 2 * n; i++) {
        pushBack(&tail, i);
    }

    printListForward(head);

    ListNode* start = head;


    // він казав, що краще в окрему функцію винести

    int result = 0;

    for (int i = 0; i < n; i++) {
        result += start->data * tail->data;

        start = start->next;
        tail = tail->prev;
    }

    printf("Result: %d\n", result);

    clearListFromHead(head);

    return 0;
}

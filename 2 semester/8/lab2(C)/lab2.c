#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

void add(struct Node **head_ref, int new_data) {
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
    }
    else{
    struct Node *last = *head_ref;

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;}
}

void freeList(struct Node *head) {
    struct Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int sameSign(int a, int b) {
    return (a >= 0 && b >= 0) || (a < 0 && b < 0);
}

void reshuffle(struct Node **head_ref) {

    struct Node *prev = *head_ref;
    struct Node *curr = (*head_ref)->next;

    while (curr != NULL) {
        if (sameSign(prev->data, curr->data)) {
            struct Node *temp = curr->next;
            struct Node *temp_prev = curr;

            while (temp != NULL && sameSign(prev->data, temp->data)) {
                temp_prev = temp;
                temp = temp->next;
            }

            if (temp == NULL) break;

            temp_prev->next = temp->next;
            temp->next = curr;
            prev->next = temp;

            prev = temp;
        } else {
            prev = curr;
        }

        curr = prev->next;
    }
}

void printList(struct Node *node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    unsigned int n,i;
    int num;
    srand(time(NULL));

    printf("enter number of nodes (even):\n");
    scanf("%u", &n);

    if (n % 2 != 0) {
        printf("The number of nodes must be even!\n");
        main();
        return;
    }

    struct Node *head = NULL;
    printf("enter nodes data (same amount of nodes <0 and >0,0 is not allowed):\n");
    for(i=1;i<=n;i++){
    scanf("%d", &num);
    add(&head,num);

    }


    printf("List before reshuffling:\n");
    printList(head);

    reshuffle(&head);

    printf("List after reshuffling:\n");
    printList(head);

    freeList(head);

    return 0;
}

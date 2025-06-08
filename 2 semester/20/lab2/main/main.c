#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct element {
    int value;
    struct element* next;
};

struct element* create_element(int value) {
    struct element* new_element = (struct element*)malloc(sizeof(struct element));
    new_element->value = value;
    new_element->next = NULL;
    return new_element;
}

void insert(struct element** head, int value) {
    struct element* new_element = create_element(value);
    new_element->next = *head;
    *head = new_element;
}

void print_list(struct element* head) {
    struct element* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->value);
        temp = temp->next;
    }
    printf("NULL\n");
}

void regroup_list(struct element** head) {

    if (!head || !(*head)) return;

    struct element* first = *head;
    struct element* second = (*head)->next;

    while(second && second->next) {
        first = first->next;
        second = second->next->next;
    }

    struct element* first_part = *head;
    struct element* second_part = first->next;

    first->next = NULL;

    while(second_part) {
        struct element* first_temp = first_part->next;
        struct element* second_temp = second_part->next;
        first_part->next = second_part;
        second_part->next = first_temp;
        first_part = first_temp;
        second_part = second_temp;
    }

}

void free_list(struct element* head) {
    struct element* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct element* head = NULL;
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if(n % 2 != 0 || n < 0) {
        printf("Invalid number of elements");
        return 1;
    }

    printf("\n");

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int value = (rand() % 21) - 10;
        insert(&head, value);
    }

    printf("Generated Linked List: \n\n");
    print_list(head);

    printf("\n");

    regroup_list(&head);
    printf("Regrouped Linked List: \n\n");
    print_list(head);

    free_list(head);
    return 0;
}

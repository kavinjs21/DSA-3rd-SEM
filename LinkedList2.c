//CH.SC.U4CSE24119 Kavin.J.S
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *prev, *next;
};

struct node *head = NULL, *tail = NULL;

void displayForward() {
    struct node *temp = head;
    printf("Forward: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void displayBackward() {
    struct node *temp = tail;
    printf("Backward: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

void createList() {
    int c;
    do {
        struct node *newnode = (struct node*)malloc(sizeof(struct node));
        printf("Enter data: ");
        scanf("%d", &newnode->data);
        newnode->prev = newnode->next = NULL;

        if (head == NULL) {
            head = tail = newnode;
        } else {
            tail->next = newnode;
            newnode->prev = tail;
            tail = newnode;
        }

        printf("Do you want to continue (1 for Yes / 0 for No): ");
        scanf("%d", &c);
    } while (c == 1);
}

void insertAtBeginning() {
    struct node *newnode = (struct node*)malloc(sizeof(struct node));
    printf("Enter data: ");
    scanf("%d", &newnode->data);
    newnode->prev = NULL;
    newnode->next = head;
    if (head != NULL)
        head->prev = newnode;
    head = newnode;
    if (tail == NULL)
        tail = newnode;
    displayForward();
    displayBackward();
}

void insertAtEnd() {
    struct node *newnode = (struct node*)malloc(sizeof(struct node));
    printf("Enter data: ");
    scanf("%d", &newnode->data);
    newnode->next = NULL;
    newnode->prev = tail;
    if (tail != NULL)
        tail->next = newnode;
    tail = newnode;
    if (head == NULL)
        head = newnode;
    displayForward();
    displayBackward();
}

void insertAtPosition() {
    int pos, i = 1;
    struct node *temp = head;
    struct node *newnode = (struct node*)malloc(sizeof(struct node));
    printf("Enter position and data: ");
    scanf("%d %d", &pos, &newnode->data);

    while (i < pos - 1 && temp != NULL) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        printf("Invalid position!\n");
        free(newnode);
        return;
    }

    newnode->next = temp->next;
    newnode->prev = temp;
    if (temp->next != NULL)
        temp->next->prev = newnode;
    temp->next = newnode;

    if (newnode->next == NULL)
        tail = newnode;

    displayForward();
    displayBackward();
}

void deleteFromBeginning() {
    struct node *temp = head;
    if (head != NULL) {
        head = head->next;
        if (head != NULL)
            head->prev = NULL;
        else
            tail = NULL;
        free(temp);
    }
    displayForward();
    displayBackward();
}

void deleteFromEnd() {
    struct node *temp = tail;
    if (tail != NULL) {
        tail = tail->prev;
        if (tail != NULL)
            tail->next = NULL;
        else
            head = NULL;
        free(temp);
    }
    displayForward();
    displayBackward();
}

void deleteFromPosition() {
    int pos, i = 1;
    struct node *temp = head;
    printf("Enter position to delete: ");
    scanf("%d", &pos);

    while (i < pos && temp != NULL) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        printf("Invalid position!\n");
        return;
    }

    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    else
        head = temp->next;

    if (temp->next != NULL)
        temp->next->prev = temp->prev;
    else
        tail = temp->prev;

    free(temp);
    displayForward();
    displayBackward();
}

int main() {
    printf("CH.SC.U4CSE24119 KAVIN\n");
    int choice;

    createList();
    displayForward();
    displayBackward();

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert at beginning\n2. Insert at end\n3. Insert at specific position\n");
        printf("4. Delete from beginning\n5. Delete from end\n6. Delete from specific position\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: insertAtBeginning(); break;
            case 2: insertAtEnd(); break;
            case 3: insertAtPosition(); break;
            case 4: deleteFromBeginning(); break;
            case 5: deleteFromEnd(); break;
            case 6: deleteFromPosition(); break;
            case 7: exit(0);
            default: printf("Enter a valid choice!\n");
        }
    }

    return 0;
}

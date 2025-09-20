//CH.SC.U4CSE24119 Kavin.J.S
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* head = NULL;
struct Node* tail = NULL;

void displayForward() {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void displayBackward() {
    struct Node* temp = tail;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

void createList() {
    int choice = 1;
    while (choice) {
        struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
        printf("Enter data: ");
        scanf("%d", &newnode->data);
        newnode->prev = NULL;
        newnode->next = NULL;

        if (head == NULL) {
            head = tail = newnode;
        } else {
            tail->next = newnode;
            newnode->prev = tail;
            tail = newnode;
        }

        printf("Do you want to continue? (1 for yes, 0 for no): ");
        scanf("%d", &choice);
    }
}

void insertAtBeginning() {
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
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
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
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
    struct Node* temp = head;
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    printf("Enter position: ");
    scanf("%d", &pos);
    printf("Enter data: ");
    scanf("%d", &newnode->data);

    if (pos == 1) {
        insertAtBeginning();
        return;
    }

    while (i < pos - 1 && temp != NULL) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        printf("Invalid position\n");
        free(newnode);
        return;
    }

    newnode->next = temp->next;
    newnode->prev = temp;

    if (temp->next != NULL)
        temp->next->prev = newnode;
    else
        tail = newnode;

    temp->next = newnode;

    displayForward();
    displayBackward();
}

void deleteFromBeginning() {
    if (head == NULL)
        return;

    struct Node* temp = head;
    head = head->next;

    if (head != NULL)
        head->prev = NULL;
    else
        tail = NULL;

    free(temp);

    displayForward();
    displayBackward();
}

void deleteFromEnd() {
    if (tail == NULL)
        return;

    struct Node* temp = tail;
    tail = tail->prev;

    if (tail != NULL)
        tail->next = NULL;
    else
        head = NULL;

    free(temp);

    displayForward();
    displayBackward();
}

void deleteFromPosition() {
    int pos, i = 1;
    struct Node* temp = head;

    printf("Enter position: ");
    scanf("%d", &pos);

    if (head == NULL)
        return;

    if (pos == 1) {
        deleteFromBeginning();
        return;
    }

    while (i < pos && temp != NULL) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        printf("Invalid position\n");
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

    while (1) {
        printf("\n1. Insert at beginning\n2. Insert at end\n3. Insert at specific position\n");
        printf("4. Delete from beginning\n5. Delete from end\n6. Delete from specific position\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insertAtBeginning();
                break;
            case 2:
                insertAtEnd();
                break;
            case 3:
                insertAtPosition();
                break;
            case 4:
                deleteFromBeginning();
                break;
            case 5:
                deleteFromEnd();
                break;
            case 6:
                deleteFromPosition();
                break;
            case 7:
                exit(0);
            default:
                printf("Enter a valid number\n");
        }
    }

    return 0;
}

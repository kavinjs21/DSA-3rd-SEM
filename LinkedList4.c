//CH.SC.U4CSE24119 Kavin.J.S

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Node* head = NULL;
struct Node* tail = NULL;
struct Node* temp = NULL;
struct Node* newnode = NULL;
struct Node* u = NULL;

void create() {
    newnode = (struct Node*)malloc(sizeof(struct Node));
    printf("Enter the data: ");
    scanf("%d", &newnode->data);
    newnode->next = NULL;
    newnode->prev = NULL;

    if (head == NULL) {
        head = newnode;
        tail = newnode;
        temp = newnode;
    } else {
        temp->next = newnode;
        newnode->prev = temp;
        temp = newnode;
        tail = newnode;
    }
}

void dis() {
    temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

void dis1() {
    temp = tail;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
}

void insertbeg(int a) {
    newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->data = a;
    newnode->next = head;
    newnode->prev = NULL;

    if (head != NULL)
        head->prev = newnode;

    head = newnode;

    if (tail == NULL)
        tail = newnode;
}

void insertend(int a) {
    newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->data = a;
    newnode->next = NULL;
    newnode->prev = tail;

    if (tail != NULL)
        tail->next = newnode;

    tail = newnode;

    if (head == NULL)
        head = newnode;
}

void deletebeg() {
    if (head == NULL)
        return;

    u = head;
    head = head->next;

    if (head != NULL)
        head->prev = NULL;
    else
        tail = NULL;

    free(u);
}

void deleteend() {
    if (tail == NULL)
        return;

    tail = tail->prev;

    if (tail != NULL) {
        u = tail->next;
        tail->next = NULL;
    } else {
        u = head;
        head = NULL;
    }

    free(u);
}

int main() {
    printf("CH.SC.U4CSE24119 KAVIN\n");
    create();
    create();
    create();

    insertbeg(8);
    insertend(98);

    deletebeg();
    deleteend();

    dis();
    printf("\n");
    dis1();

    return 0;
}

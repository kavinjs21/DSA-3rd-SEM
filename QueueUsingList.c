//CH.SC.U4CSE24119 Kavin.J.S

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *newnode, *head = NULL, *tail = NULL, *temp;
int n = 9;
int pos = 0;

void create() {
    int c;
    pos = 0;
    do {
        if (pos >= n) {
            printf("Overflow\n");
            break;
        }

        newnode = (struct node *)malloc(sizeof(struct node));
        if (newnode == NULL) {
            printf("Memory allocation failed\n");
            break;
        }

        printf("Enter the element: ");
        scanf("%d", &newnode->data);
        newnode->next = NULL;
        pos++;

        if (head == NULL) {
            head = tail = newnode;
        } else {
            tail->next = newnode;
            tail = newnode;
        }

        printf("Do you want to continue? (1 to continue / 0 to stop): ");
        scanf("%d", &c);

    } while (c == 1);
}

void enqueue(int a) {
    if (pos >= n) {
        printf("Overflow\n");
        return;
    }

    newnode = (struct node *)malloc(sizeof(struct node));
    if (newnode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    newnode->data = a;
    newnode->next = NULL;
    pos++;

    if (head == NULL) {
        head = tail = newnode;
    } else {
        tail->next = newnode;
        tail = newnode;
    }
}

void display() {
    temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void dequeue() {
    if (head == NULL) {
        printf("Empty\n");
    } else {
        temp = head;
        head = head->next;
        free(temp);
        pos--;
    }
}

int main() {
    printf("CH.SC.U4CSE24119 Kavin.J.S\n");
    create();
    enqueue(99);
    dequeue();
    dequeue();
    display();
    return 0;
}
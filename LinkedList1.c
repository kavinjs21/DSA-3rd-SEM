//CH.SC.U4CSE24119 Kavin.J.S
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *head, *newnode, *temp, *tail;

void create() {
    head = 0;
    int c, pos;
    do {
        newnode = (struct node *)malloc(sizeof(struct node));
        printf("Enter the element: ");
        scanf("%d", &newnode->data);
        newnode->next = 0;

        if (head == 0) {
            head = temp = tail = newnode;
        } else {
            temp->next = newnode;
            temp = tail = newnode;
        }

        printf("Do you want to continue (0/1)? ");
        scanf("%d", &c);
    } while (c == 1);
}

void display() {
    printf("\nLinked list: ");
    temp = head;
    while (temp != 0) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void insert_beg(int a) {
    newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = a;
    newnode->next = head;
    head = newnode;
    display();
}

void insert_end(int a) {
    newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = a;
    tail->next = newnode;
    tail = newnode;
    tail->next = 0;
    display();
}

void insert(int pos, int a) {
    newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = a;

    temp = head;
    int pp = 1;
    while (pp < pos - 1) {
        temp = temp->next;
        pp++;
    }

    newnode->next = temp->next;
    temp->next = newnode;
    display();
}

void del_beg() {
    temp = head;
    head = temp->next;
    free(temp);
    display();
}

void del_end() {
    temp = head;
    while (temp->next != tail) {
        temp = temp->next;
    }
    tail = temp;
    temp = temp->next;
    tail->next = 0;
    free(temp);
    display();
}

void delete_pos(int pos) {
    struct node *t;
    temp = head;
    int p = 1;
    while (p < pos - 1) {
        temp = temp->next;
        p++;
    }
    t = temp->next;
    temp->next = t->next;
    free(t);
    display();
}

void main() {
    printf("CH.SC.U4CSE24119 KAVIN\n");

    int s, n, pos;

    create();
    display();

x:
    printf("\nMenu:\n1. Insert at beginning\n2. Insert at end\n3. Insert at specific position");
    printf("\n4. Delete at beginning\n5. Delete at end\n6. Delete at specific position\n7. Exit\n");
    scanf("%d", &s);

    switch (s) {
        case 1:
            printf("Enter the element: ");
            scanf("%d", &n);
            insert_beg(n);
            goto x;
        case 2:
            printf("Enter the element: ");
            scanf("%d", &n);
            insert_end(n);
            goto x;
        case 3:
            printf("Enter the position and element: ");
            scanf("%d %d", &pos, &n);
            insert(pos, n);
            goto x;
        case 4:
            del_beg();
            goto x;
        case 5:
            del_end();
            goto x;
        case 6:
            printf("Enter the position to delete: ");
            scanf("%d", &pos);
            delete_pos(pos);
            goto x;
        case 7:
            break;
        default:
            printf("Enter correct number");
            goto x;
    }

    display();
}

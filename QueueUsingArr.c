//CH.SC.U4CSE24119 Kavin.J.S
#include <stdio.h>
#include <stdlib.h>

int a = 10;      
int *arr;
int rear = -1, front = -1;

void enqueue(int g) {
    if (front == -1) {
        front = rear = 0;
        arr[front] = g;
    }
    else if (rear == a - 1) {
        printf("overflow\n");
    }
    else {
        rear++;
        arr[rear] = g;
    }
}

void display() {
    if (front > rear || front == -1) {
        printf("queue is empty\n");
    }
    else {
        for (int i = front; i <= rear; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
}

void dequeue() {
    if (front > rear || front == -1) {
        printf("queue is empty\n");
        front = rear = -1;
    }
    else {
        front++;
    }
}

int main() {
    arr = (int *)malloc(a * sizeof(int));

    printf("CH.SC.U4CSE24119 Kavin.J.S\n");

    enqueue(0);
    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);

    dequeue();
    display();

    free(arr); 
    return 0;
}

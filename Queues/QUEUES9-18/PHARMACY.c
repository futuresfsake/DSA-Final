#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int count;
} List;

typedef struct {
    List list;
    int front;
    int rear;
} Queue;

Queue* initialize();
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
bool isFull(Queue* q);
bool isEmpty(Queue* q);
void display(Queue* q);

int main() {
    Queue regularQueue;
    regularQueue.front = -1;
    regularQueue.rear = -1;
    regularQueue.list.count = 0;

    Queue priorityQueue;
    priorityQueue.front = -1;
    priorityQueue.rear = -1;
    priorityQueue.list.count = 0;

    int val = 0;
    int choice;
    int n;

    do {
        printf("--- Pharmacy Queueing System ---\n");
        printf("1. Enter Regular Queue\n2. Enter Priority Queue\n3. Call Next Customer\n4. Display Queues\n5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                val++;
                printf("You have entered the Regular queue. Your number is %d.\n\n", val);
                enqueue(&regularQueue, val);
                break;

            case 2:
                val++;
                printf("You have entered the Priority queue. Your number is %d.\n\n", val);
                enqueue(&priorityQueue, val);
                break;

            case 3:
                if (!isEmpty(&priorityQueue)) {
                    n = dequeue(&priorityQueue);
                    printf("Calling next customer from Priority Queue. Customer number: %d\n\n", n);
                } else if (!isEmpty(&regularQueue)) {
                    n = dequeue(&regularQueue);
                    printf("Calling next customer from Regular Queue. Customer number: %d\n\n", n);
                } else {
                    printf("Both queues are empty.\n\n");
                }
                break;

            case 4:
                printf("\n-- Current Queue Status --\n");
                printf("Regular Queue: ");
                display(&regularQueue);
                printf("Priority Queue: ");
                display(&priorityQueue);
                printf("\n");
                break;
        }
    } while (choice != 5);

    printf("Exiting program. Goodbye!\n");
    return 0;
}

Queue* initialize() {
    Queue *q = malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    q->list.count = 0;
    return q;
}

void enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return;
    }

    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }

    q->list.items[q->rear] = value;
    q->list.count++;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }

    int i = q->list.items[q->front];

    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }

    q->list.count--;
    return i;
}

bool isFull(Queue* q) {
    return ((q->rear + 1) % MAX == q->front);
}

bool isEmpty(Queue* q) {
    return (q->rear == -1 && q->front == -1);
}

void display(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }

    int i = q->front;
    while (true) {
        printf("%d ", q->list.items[i]);
        if (i == q->rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

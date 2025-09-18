#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

// ===== List Struct =====
typedef struct {
    int items[MAX];
    int count;
} List;

// ===== Queue Struct =====
typedef struct {
    List list;
    int front;
    int rear;
} Queue;

// ===== Function Prototypes =====
Queue* initialize();
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
bool isFull(Queue* q);
bool isEmpty(Queue* q);
void display(Queue* q);

int main() {
    Queue regularQueue;
    Queue priorityQueue;

    int val = 0;
    int choice, n;

    // Initialize queues
    regularQueue.front = regularQueue.rear = -1;
    regularQueue.list.count = 0;
    priorityQueue.front = priorityQueue.rear = -1;
    priorityQueue.list.count = 0;

    do {
        printf("--- Pharmacy Queueing System ---\n");
        printf("1. Enter Regular Queue\n");
        printf("2. Enter Priority Queue\n");
        printf("3. Call Next Customer\n");
        printf("4. Display Queues\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // TODO: Regular enqueue
                break;
            case 2:
                // TODO: Priority enqueue
                break;
            case 3:
                // TODO: Call next customer
                break;
            case 4:
                // TODO: Display queues
                break;
        }
    } while (choice != 5);

    printf("Exiting program. Goodbye!\n");
    return 0;
}

// ===== Function Definitions =====
Queue* initialize() {
    // TODO: Allocate and initialize a new queue
    return NULL;
}

void enqueue(Queue* q, int value) {
    // TODO: Insert value into queue
}

int dequeue(Queue* q) {
    // TODO: Remove and return value from queue
    return -1;
}

bool isFull(Queue* q) {
    // TODO: Check if queue is full
    return false;
}

bool isEmpty(Queue* q) {
    // TODO: Check if queue is empty
    return true;
}

void display(Queue* q) {
    // TODO: Display contents of queue
}

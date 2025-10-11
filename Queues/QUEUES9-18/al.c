#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_QUEUE 50

// ===== Customer Struct (stored in Queue) =====
typedef struct {
    int customerId;
    char name[50];
    int serviceTime;   // minutes required
} Customer;

// ===== Array-based Queue =====
typedef struct {
    Customer arr[MAX_QUEUE];
    int front;
    int rear;
    int count;
} Queue;

// ===== Function Declarations =====
void initQueue(Queue *q) {
    
}
bool isEmpty(Queue *q);
bool isFull(Queue *q);
void enqueue(Queue *q, Customer c);
Customer dequeue(Queue *q);
Customer peek(Queue *q);
void displayQueue(Queue *q);
int totalServiceTime(Queue *q);   // special: compute total waiting time

// ===== Main Function =====
int main() {
    Queue customerQueue;
    initQueue(&customerQueue);

    Customer c1 = {101, "Alice", 5};
    Customer c2 = {102, "Bob", 3};
    Customer c3 = {103, "Charlie", 7};

    enqueue(&customerQueue, c1);
    enqueue(&customerQueue, c2);
    enqueue(&customerQueue, c3);

    printf("Customers waiting:\n");
    displayQueue(&customerQueue);

    printf("\nTotal service time required: %d minutes\n", totalServiceTime(&customerQueue));

    printf("\nServing first customer...\n");
    dequeue(&customerQueue);

    printf("\nRemaining customers:\n");
    displayQueue(&customerQueue);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#define MAX 10   // maximum size of queue

// Queue structure (Circular Array)
typedef struct {
    int arr[MAX];
    int front;
    int rear;
    int count;  // number of elements
} Queue;

// Function declarations
void initQueue(Queue *q);
int isEmpty(Queue *q);
int isFull(Queue *q);
void enqueue(Queue *q, int value);
int dequeue(Queue *q);
void displayQueue(Queue *q);

void removeDuplicates(Queue *q);  // 🔹 your function to implement


// Initialize queue
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

// Check if queue is empty
int isEmpty(Queue *q) {
    return q->count == 0;
}

// Check if queue is full
int isFull(Queue *q) {
    return q->count == MAX;
}

// Enqueue (insert element at rear)
void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX;
    q->arr[q->rear] = value;
    q->count++;
}

// Dequeue (remove element from front)
int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    int value = q->arr[q->front];
    q->front = (q->front + 1) % MAX;
    q->count--;
    return value;
}

// Display queue elements
void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("[ ");
    int i = q->front;
    for (int c = 0; c < q->count; c++) {
        printf("%d ", q->arr[i]);
        i = (i + 1) % MAX;
    }
    printf("]\n");
}

// 🔹 Remove duplicates (you will implement)
void removeDuplicates(Queue *q) {
    // TODO: implement logic

   int i = q->front;

    for(int c = 0; c < q->count; c++) {
        int current = q->arr[i];
        if (current == q->arr[c]) {
            for(int k = )
        }
       
    }
}


// Main function to test
int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 10);
    enqueue(&q, 40);

    printf("Original Queue: ");
    displayQueue(&q);

    removeDuplicates(&q);  // 🔹 call your function

    printf("Queue after removing duplicates: ");
    displayQueue(&q);

    return 0;
}

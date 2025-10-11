#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10   // capacity of queue

// Queue structure (Circular Array)
typedef struct {
    int arr[MAX];
    int front;
    int rear;
    int count;   // number of elements
} Queue;

// Function Declarations
void initQueue(Queue *q);
bool isEmpty(Queue *q);
bool isFull(Queue *q);
void displayQueue(Queue *q);

// Sorted push (insert in ascending order)
void pushSorted(Queue *q, int value);

// Normal dequeue
int dequeue(Queue *q);

int main() {
    Queue q;
    initQueue(&q);

    pushSorted(&q, 30);
    pushSorted(&q, 10);
    pushSorted(&q, 20);
    pushSorted(&q, 40);

    printf("Queue after sorted insert:\n");
    displayQueue(&q);

    return 0;
}

// Function Definitions (boilerplate only)
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

bool isEmpty(Queue *q) {
    return q->count == 0;
}

bool isFull(Queue *q) {
    return q->count == MAX;
}

void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    int i, idx;
    for (i = 0; i < q->count; i++) {
        idx = (q->front + i) % MAX;
        printf("%d ", q->arr[idx]);
    }
    printf("\n");
}

void pushSorted(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full. Cannot insert %d\n", value);
        return;
    }

    // TODO: Insert logic here
    // 1. Find correct position for value
    // 2. Shift elements (circularly) to make room
    // 3. Insert value in sorted order
    // 4. Update rear and count

  
    
    if (isEmpty(q)) {
        q->rear = 0;
        q->front = 0;
        q->arr[q->rear] = value; 
        q->count++;
        return;
       
    } 
           
    // ! finding the correct position
              int i = q->front;
              int steps = 0;
    while (i < q->count && q->arr[i] < value) {
        i = (i + 1) %MAX;
        steps++;
    }

    // ! shift the elemts from rear to pos

    int idx = (q->front + q->count -1) %MAX; // ? current rear
    q->rear = (q->rear + 1) % MAX; // ! add a new rear

    while (idx != (i - 1+ MAX) % MAX) { // * staarts at the rear // ! travel until the position
        int next = (idx + 1) % MAX; // ! the slot after current
        q->arr[next] = q->arr[idx]; // ! copy arr[idx] to arr[next], shift elements one step forward
        idx = (idx - 1 + MAX) % MAX; // ? move idx backward -1, circular style
    }
    
    q->arr[i] = value;
    q->count++;
             
            
            
     

}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return -1;
    }
    int val = q->arr[q->front];
    q->front = (q->front + 1) % MAX;
    q->count--;
    return val;
}

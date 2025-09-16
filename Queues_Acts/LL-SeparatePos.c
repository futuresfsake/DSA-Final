#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// ===== Node Structure =====
typedef struct Node {
    int data;               // Change type if needed
    struct Node *next;
} Node;

// ===== Queue Structure =====
typedef struct {
    Node *front;
    Node *rear;
} Queue;

// ===== Queue Operations =====

// Initialize a queue
void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

// Check if queue is empty
bool isEmpty(Queue *q) {
    return q->front == NULL;
}

// Enqueue: add element at the rear
bool enqueue(Queue *q, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) return false;

    newNode->data = value;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    return true;
}

// Dequeue: remove element from front
bool dequeue(Queue *q, int *value) {
    if (isEmpty(q)) return false;

    Node *temp = q->front;
    *value = temp->data;
    q->front = q->front->next;
    
    if (q->front == NULL) q->rear = NULL; // Queue becomes empty

    free(temp);
    return true;
}

// Peek: view front element
bool peek(Queue *q, int *value) {
    if (isEmpty(q)) return false;
    *value = q->front->data;
    return true;
}

// Display queue
void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    Node *temp = q->front;
    printf("Queue: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}


Queue separatePos (Queue *q) {
    Queue temporaryQueue;
    initQueue(&temporaryQueue);
    Queue negativeQueue;
    initQueue(&negativeQueue);

    

    Node *i = q->front;

    while (i != NULL) {
        if (i->data >= 0) {
            enqueue(&temporaryQueue, i->data);
           
        } else {
            enqueue(&negativeQueue, i->data);

        }
         i = i ->next;
    }
    return temporaryQueue;
    
}
// ===== Main for Testing =====
int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, -1);
    enqueue(&q, 30);
     enqueue(&q, -123);
    enqueue(&q, 239);
    enqueue(&q, -32);
    displayQueue(&q);

   
    
  

    displayQueue(&q);

    Queue positives = separatePos(&q);
    displayQueue(&positives);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

// ===== Node structure =====
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// ===== Queue structure =====
typedef struct {
    Node *front;
    Node *rear;
} Queue;

// ===== Function Declarations =====
void initQueue(Queue *q);
int isEmpty(Queue *q);
void enqueue(Queue *q, int val);
int dequeue(Queue *q);
void display(Queue *q);
void reverseQueue(Queue *q);

// ===== Function Definitions =====
void initQueue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}

int isEmpty(Queue *q) {
    return q->front == NULL && q->rear == NULL;
}

void enqueue(Queue *q, int val) {

    Node *newNode = malloc(sizeof(Node));
    if (!newNode) {
        printf("Dynamic Memory Allocation failed.\n");
        exit (1);
    }

    newNode->data = val;
    newNode->next = NULL;

    
    
    if (isEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;

    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    
    }
    

}

int dequeue(Queue *q) {
    // TODO: dequeue element
    return -1;
}

void display(Queue *q) {
    // TODO: display elements
}

void reverseQueue(Queue *q) {
    // TODO: reverse queue
}

// ===== Main Function =====
int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);

    printf("Original Queue:\n");
    display(&q);

    reverseQueue(&q);

    printf("Reversed Queue:\n");
    display(&q);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

typedef struct {
    int arr[MAX];
    int front;
    int rear;
    int size;
} Queue;

typedef struct {
    int arr[MAX];
    int top;
} Stack;

// Function declarations
void initQueue(Queue *q);
int isEmpty(Queue *q);
int isFull(Queue *q);
void enqueue(Queue *q, int value);
int dequeue(Queue *q);
int peek(Queue *q);
void display(Queue *q);



void initStack (Stack *s) { 
    s->top = -1;
    
}

bool isEmptyStack (Stack *s) {
    return s->top == -1;
}

bool isFullStack (Stack *s) {
    return s->top == MAX -1;
}


void pushStack (Stack *s, int value) {
    if (isFullStack(s)) {
        return;
    }

    s->top++;
    s->arr[s->top] = value;

}


int popStack (Stack *s) {
    if (isEmptyStack(s)) {
        return -1;
    }
    int data = s->arr[s->top];
    s->top--;
    return data;
}

// Problem function (you will implement this)
void reverseQueue(Queue *q);

// Function definitions
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

int isEmpty(Queue *q) {
    return q->size == 0;
}

int isFull(Queue *q) {
    return q->size == MAX;
}

void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX;
    q->arr[q->rear] = value;
    q->size++;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow!\n");
        return -1; // error value
    }
    int value = q->arr[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return value;
}

int peek(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1; // error value
    }
    return q->arr[q->front];
}

void display(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    int count = q->size;
    int i = q->front;
    while (count--) {
        printf("%d ", q->arr[i]);
        i = (i + 1) % MAX;
    }
    printf("\n");
}

// Main
int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);

    printf("Original Queue: ");
    display(&q);

    reverseQueue(&q);  // <-- You will implement this

    printf("Reversed Queue: ");
    display(&q);

    return 0;
}


void reverseQueue(Queue *q) {
    Stack temp;
    initStack(&temp);


    while (!isEmpty(q)) {
        pushStack(&temp, dequeue(q));
    }

    while (!isEmptyStack(&temp)) {
        enqueue(q, popStack(&temp));
    }
   
   


}


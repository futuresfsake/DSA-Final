#include <stdio.h>
#include <stdlib.h>
#define MAX 5   // maximum size of queue

// Queue structure
typedef struct {
    int arr[MAX];
    int front;
    int rear;
} QueueAL;

// Function declarations
void initQueueAL(QueueAL *q) {
    q->rear = -1;
    q->front = -1;
}        // initialize queue
int isEmptyAL(QueueAL *q) {
    return q->rear == -1 && q->front == -1;
}         // check if queue is empty
int isFullAL(QueueAL *q) {
    return (q->rear+1) % MAX == q->front;
}            // check if queue is full
void enqueueAL(QueueAL *q, int val) {
    if (isFullAL(q)) {
        return;
    } else if (isEmptyAL(q)) {
        q->front++;
        q->rear++;

        q->arr[q->rear] = val;
    } else {
        q->rear = (q->rear+1) % MAX;
        q->arr[q->rear] = val;
    }
}

// insert element
int dequeueAL(QueueAL *q) {
    if (isEmptyAL(q)) {
        return -1;
    } else if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
}          // remove element
int peekAL(QueueAL *q) {
    return q->arr[q->front];
}            // view front element
void displayAL(QueueAL *q) {

    int i = q->front;

    while (i < q->rear) {
        printf("%d ",q->arr[i]);
        i = (i+1) % MAX;
    }

    printf("%d ", q->arr[q->rear]);
}          // display all elements

int main() {
    QueueAL q;
    initQueueAL(&q);

    enqueueAL(&q,23);
    enqueueAL(&q, 54);
    enqueueAL(&q, 254);
    
    displayAL(&q);// test your functions here

    return 0;
}

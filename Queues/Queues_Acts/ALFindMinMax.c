#include <stdio.h>
#include <stdlib.h>
#define MAX 10   // maximum size of queue

// Queue structure (ArrayList style)
typedef struct {
    int arr[MAX];
    int front;
    int rear;
} QueueAL;

// Function declarations
void initQueueAL(QueueAL *q);
int isEmptyAL(QueueAL *q);
int isFullAL(QueueAL *q);
void enqueueAL(QueueAL *q, int value);
int dequeueAL(QueueAL *q);
void displayAL(QueueAL *q);

// Your task: Find minimum and maximum element in queue
int findMaxAL(QueueAL *q);   // <-- You will implement this
int findMinAL(QueueAL *q);   // <-- You will implement this

// Initialize queue
void initQueueAL(QueueAL *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if empty
int isEmptyAL(QueueAL *q) {
    return q->front == -1;
}

// Check if full
int isFullAL(QueueAL *q) {
    return (q->rear + 1) % MAX == q->front;
}

// Enqueue
void enqueueAL(QueueAL *q, int value) {
    if (isFullAL(q)) {
        printf("Queue is full!\n");
        return;
    }
    if (isEmptyAL(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }
    q->arr[q->rear] = value;
}

// Dequeue
int dequeueAL(QueueAL *q) {
    if (isEmptyAL(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    int val = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
    return val;
}

// Display queue
void displayAL(QueueAL *q) {
    if (isEmptyAL(q)) {
        printf("Queue is empty!\n");
        return;
    }
    int i = q->front;
    while (1) {
        printf("%d ", q->arr[i]);
        if (i == q->rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int findMaxAL(QueueAL *q);
int findMinAL(QueueAL *q);

// Main function
int main() {
    QueueAL q;
    initQueueAL(&q);

    enqueueAL(&q, 1000);
    enqueueAL(&q, 25);
    enqueueAL(&q, 458);
    enqueueAL(&q, 40);
    enqueueAL(&q, 855);

    printf("Queue elements: ");
    displayAL(&q);

    int maxVal = findMaxAL(&q);   // <-- You will implement this
    int minVal = findMinAL(&q);   // <-- You will implement this

    printf("Maximum element = %d\n", maxVal);
    printf("Minimum element = %d\n", minVal);

    return 0;
}



int findMaxAL(QueueAL *q) {
    
    int i = q->front;

    int num = q->arr[i];
    while (i != q->rear) {

        if (num < q->arr[i+1]) {
            num = q->arr[i+1];
        }
          i = (i+1) % MAX;
    }
    // }

    // if (i < q->arr[q->rear]) {
    //     return q->arr[q->rear];
    // }


    return num;
        
}


int findMinAL(QueueAL *q) {

    int i = q->front;
    int num = q->arr[i];
    while (i != q->rear) {
        i = (i+1) % MAX;
        if (num > q->arr[i]) {
            num = q->arr[i];
        }
        
        
    }
    return num;
}
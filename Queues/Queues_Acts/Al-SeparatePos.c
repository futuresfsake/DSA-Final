#include <stdio.h>
#include <stdlib.h>
#define MAX 50   // maximum size of queue

// Queue structure
typedef struct {
    int arr[MAX];
    int front;
    int rear;
} Queue;

// Function declarations
void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}     
int isEmpty(Queue *q) {
    return q->rear == -1 && q->front == -1;
}        
int isFull(Queue *q) {
    return (q->rear + 1) % MAX == q->front;
}         

void enqueue(Queue *q, int val) {
    if (isFull(q)) {
        return;
    } else if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
        q->arr[q->rear] = val;
    }
    else {
        q->rear = (q->rear + 1) % MAX;
        q->arr[q->rear] = val;
    }
}

int dequeue(Queue *q) {

    if (isEmpty(q)) {
        return -1;
    } 
    
    int val = q->arr[q->front];
     if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    
    }

    return val;
}        
void display(Queue *q) {
    if (isEmpty(q)) {
        return;
    }

    int i = q->front;

    while (i != q->rear) {
        printf("%d ", q->arr[i]);
        i = (i + 1) % MAX;
    }
            printf("%d", q->arr[q->rear]);
}      
void separatePosNeg(Queue *src, Queue *positiveQ, Queue *negativeQ);

// Main function
int main() {
    Queue q, posQ, negQ;
    initQueue(&q);
    initQueue(&posQ);
    initQueue(&negQ);

    // enqueue some test numbers
    enqueue(&q, 10);
    enqueue(&q, -5);
    enqueue(&q, 20);
    enqueue(&q, -15);
    enqueue(&q, 30);
    enqueue(&q, -25);

    printf("Original Queue: ");
    display(&q);

    // Separate positives and negatives
    separatePosNeg(&q, &posQ, &negQ);

    printf("\nPositive Queue: ");
    display(&posQ);

    printf("Negative Queue: ");
    display(&negQ);

    return 0;
}


// void separatePosNeg(Queue *src, Queue *positiveQ, Queue *negativeQ) {

//     int i = src->rear;
//     while (i != src->front) {
//         if (src->arr[i] >= 0) {
//             enqueue(positiveQ, dequeue(src));
//         } else if (src->arr[i] < 0 ) {
//             enqueue(negativeQ, dequeue(src));
//         }

//         i = (i + 1) % MAX;

        
//     }
// }


void separatePosNeg(Queue *src, Queue *positiveQ, Queue *negativeQ) {
    while (!isEmpty(src)) {
        int val = dequeue(src);
        if (val < 0) {
            enqueue(negativeQ, val);
        } else {
            enqueue(positiveQ, val);
        }
    }
}
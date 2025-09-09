#include <stdio.h>
#include <stdlib.h>
#define MAX 5   // maximum size of queue

// Queue structure (Circular Array)
typedef struct {
    int arr[MAX];
    int front;
    int rear;
    int count;  // number of elements
} Queue;

// Function declarations
void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
    q->count = 0;
}
int isEmpty(Queue *q) {
    return q->rear == -1 && q->front == -1;
}

int isFull(Queue *q) {
    return (q->rear +1) % MAX == q->front;
}


void enqueue(Queue *q, int val) {
    if (isFull(q)){
        return;
    } else if (isEmpty(q)) {
        q->front =0;
        q->rear=0;
        q->arr[q->rear] = val;
        q->count++;
    } else  {
        q->rear = (q->rear + 1) % MAX;
        q->arr[q->rear] = val;
        q->count++;
    }
}


int dequeue(Queue *q) {
    if (isEmpty(q)) {
        return -1;
    } else if (q->rear == q->front) {
        q->rear = -1;
        q->front = -1;
        q->count--;
    } else {
        q->front = (q->front+1) % MAX;
       q->count--;
}
}


// // ** if there is no count we can use this method
// void display(Queue *q) {
    
//     if (isEmpty(q)) {
//         return;
//     }


//     int i = q->front;
//     while (i != q->rear) {
//         printf("%d ", q->arr[i]);
//         i  = (i + 1) % MAX;
//     }

//     printf("%d ", q->arr[q->rear]);
// }

// * if theres count, we can do for loop to avoid special
// * cases in displaying rear


void display(Queue *q) {

    if (isEmpty(q)) {
        return;
    }

    int i = q->front;

    for(int c = 0; c < q->count; c++) {
        printf("%d ", q->arr[i]);
        i  = (i+1) % MAX;
    }
}


int sumOfElements(Queue *q) {

    int i = q->front;
    int sum=0;

    for(int c = 0; c < q->count; c++) {
        sum+= q->arr[i];
        i = (i+1) % MAX;
    }
    return sum;
}

int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 50);

    display(&q);
    printf("Sum of elements: %d\n", sumOfElements(&q));

    dequeue(&q);
    display(&q);
    printf("Sum of elements: %d\n", sumOfElements(&q));

    return 0;
}

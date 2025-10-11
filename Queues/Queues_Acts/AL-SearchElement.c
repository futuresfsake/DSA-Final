#include <stdio.h>
#include <stdbool.h>
#define MAX 10

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


void initQueue (Queue *q);
int isEmpty (Queue *q);
int isFull (Queue *q);
void enqueue (Queue *q, int value);
int dequeue (Queue *q);
int peek (Queue *q);
void display (Queue *q);
bool searchNum (Queue *q, int value);


int main () {
    Queue q;
    initQueue(&q);

    enqueue(&q, 58);
    enqueue(&q, 96);
    enqueue(&q, 23);
    enqueue(&q, 85);
    enqueue(&q, 59);

    printf("Original Queue: ");
    display(&q);

    int value = 5;
    if (searchNum(&q, value)) {
        printf("%d is existing in the list", value);
    } else {
        printf("%d is not existing in the list", value);
    }


}


void initQueue (Queue *q) {
    q->front = -1;
    q->rear = -1;
    q->size = 0;
}

int isEmpty (Queue *q) {
    return q->front == -1;
}


int isFull (Queue *q) {
    return ((q->rear + 1) % MAX == q->front);

}

void enqueue (Queue *q, int value) {
     if (isFull(q)) {
        return;
     } else if (isEmpty(q)) {
        q->front = 0; 
        q->rear = 0;

        q->arr[q->rear] = value;
     } else {
        q->rear = (q->rear + 1) % MAX;
        q->arr[q->rear] = value;

     }
}


int dequeue (Queue *q) {
    if (isEmpty(q)) {
        return -1;
    }

    int value = q->arr[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
}


int peek (Queue *q) {
    return q->arr[q->front];
}


void display (Queue *q) {
    if (isEmpty(q)) {
        return;
    }

    int i = q->front;
    while (i != q->rear ) {
        printf("%d ", q->arr[i]);
        i = (i+ 1) % MAX;


    }
    printf("%d", q->arr[q->rear]);
}



bool searchNum (Queue *q,int  value) {

    int i = q->front;

    while (i != q->rear) {
        if (q->arr[i] == value) {
            
            return true;   
        }
        i = (i +1 ) % MAX;
        
    }

    if (q->arr[q->rear] == value) {
        return true;
    }

    return false;
}

#include <stdio.h>
#define MAX 100

// structure for priority queue item
struct Item {
    int data;
    int priority;
};

struct PriorityQueue {
    struct Item arr[MAX];
    int size;
};

// function prototypes
void enqueue(struct PriorityQueue *pq, int data, int priority);
void dequeue(struct PriorityQueue *pq);
int peek(struct PriorityQueue pq);
void display(struct PriorityQueue pq);

int main() {
    struct PriorityQueue pq;
    pq.size = 0;

    enqueue(&pq, 10, 2);
    enqueue(&pq, 20, 5);
    enqueue(&pq, 30, 1);
    enqueue(&pq, 40, 4);

    printf("Current Queue:\n");
    display(pq);

    printf("\nPeek (highest priority element): %d\n", peek(pq));

    dequeue(&pq);
    printf("\nAfter Dequeue:\n");
    display(pq);

    return 0;
}

void enqueue(struct PriorityQueue *pq, int data, int priority) {
    if (pq->size == MAX) {
        printf("Queue overflow!\n");
        return;
    }
    pq->arr[pq->size].data = data;
    pq->arr[pq->size].priority = priority;
    pq->size++;
    printf("Enqueued: %d (Priority: %d)\n", data, priority);
}

void dequeue(struct PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("Queue underflow!\n");
        return;
    }

    int highest = 0;
    // find index of highest priority
    for (int i = 1; i < pq->size; i++) {
        if (pq->arr[i].priority > pq->arr[highest].priority)
            highest = i;
    }

    printf("Dequeued: %d (Priority: %d)\n",
           pq->arr[highest].data, pq->arr[highest].priority);

    // shift remaining elements left
    for (int i = highest; i < pq->size - 1; i++)
        pq->arr[i] = pq->arr[i + 1];

    pq->size--;
}

int peek(struct PriorityQueue pq) {
    if (pq.size == 0) {
        printf("Queue is empty!\n");
        return -1;
    }

    int highest = 0;
    for (int i = 1; i < pq.size; i++) {
        if (pq.arr[i].priority > pq.arr[highest].priority)
            highest = i;
    }
    return pq.arr[highest].data;
}

void display(struct PriorityQueue pq) {
    if (pq.size == 0) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Data\tPriority\n");
    for (int i = 0; i < pq.size; i++) {
        printf("%d\t%d\n", pq.arr[i].data, pq.arr[i].priority);
    }
}

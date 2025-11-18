#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 100
#define MAX_STR 50

// ===== Nested Struct =====
typedef struct {
    char name[MAX_STR];
    int priority;   // Lower value = higher priority
} Item;

// ===== Priority Queue Structure =====
typedef struct {
    Item heap[MAXN];
    int size;
} PriorityQueue;

// ===== Function Prototypes =====
void initQueue(PriorityQueue* pq) {
    pq->size = -1;

}
bool isEmpty(PriorityQueue* pq) {
    return pq->size == -1;

}
bool isFull(PriorityQueue* pq) {
    return pq->size == MAXN -1;

}
void swapp(Item* a, Item* b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

void enqueue(PriorityQueue* pq, Item x) {

    int child, pr;
    Item swap;

    if (pq->size == MAXN-1) {
        printf("The heap is already full!\n");
        return;
    }

    pq->size++;
    child = pq->size;
    pr = (child -1)/2;

    while (child >0 && pq->heap[pr].priority > x.priority) {
        pq->heap[child] = pq->heap[pr];
        child = pr;
        pr = (child-1) / 2;
    }

    pq->heap[child] = x;
    printf("Added successfully!\n");
}
Item dequeue(PriorityQueue* pq) {
    Item swap, root;
    int child, pr;

    if (pq->size == -1) {
        printf("Heap is empty!\n");
        exit(1);
    }


    root = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size];
    pq->size--;


    pr = 0;
    child = 1;

    while (child <= pq->size) {

        if (child +1 <= pq->size && pq->heap[child+1].priority < pq->heap[child].priority) {
            child++;
        }

        if (pq->heap[pr].priority > pq->heap[child].priority) {
            swapp(&(pq->heap[pr]), &(pq->heap[child]));
            pr = child;
         child = 2 * pr+1;   
        } else {
            break;
        }

    }
    return root;
}

void printQueue(PriorityQueue* pq) {
    printf("Priority Queue: \n");
    for (int i = 0; i <= pq->size; i++) {
        printf("Name: %s, Priority: %d\n", pq->heap[i].name, pq->heap[i].priority);
    }
}



// ===== Main (Test) =====
int main() {
    PriorityQueue pq;
    initQueue(&pq);

    Item a = {"Alice", 3};
    Item b = {"Bob", 1};
    Item c = {"Charlie", 5};
    Item d = {"Diana", 2};

    enqueue(&pq, a);
    enqueue(&pq, b);
    enqueue(&pq, c);
    enqueue(&pq, d);

    printQueue(&pq);

    printf("\nDequeuing items based on priority:\n");
    while (!isEmpty(&pq)) {
        Item x = dequeue(&pq);
        printf("Name: %s, Priority: %d\n", x.name, x.priority);
    }

    return 0;
}



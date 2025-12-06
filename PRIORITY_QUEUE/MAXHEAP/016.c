#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 20

// ================================
// PRIORITY QUEUE STRUCTURE
// ================================
typedef struct {
    int arr[MAX];
    int count;   // -1 means empty queue
} PriorityQueue;

// ================================
// FUNCTION DECLARATIONS
// ================================
void initPQ(PriorityQueue *pq);
bool isEmpty(PriorityQueue *pq);
bool isFull(PriorityQueue *pq);
void insert(PriorityQueue *pq, int value);
int deleteMax(PriorityQueue *pq);
void display(PriorityQueue *pq);
void heapSort(PriorityQueue *pq);

// ================================
// MAIN FUNCTION (TEST CASE)
// ================================
int main() {
    PriorityQueue pq;

    initPQ(&pq);

    insert(&pq, 30);
    insert(&pq, 10);
    insert(&pq, 50);
    insert(&pq, 40);
    insert(&pq, 20);

    printf("Priority Queue contents:\n");
    display(&pq);

    printf("\nDeleting max...\n");
    int removed = deleteMax(&pq);
    printf("Removed: %d\n\n", removed);

    printf("Priority Queue after delete:\n");
    display(&pq);

    printf("After sorting!");
    heapSort(&pq);
    display(&pq);

    return 0;
}


void initPQ(PriorityQueue *pq) {
    pq->count = -1;
}
bool isEmpty(PriorityQueue *pq) {
    return pq->count == -1;
}
bool isFull(PriorityQueue *pq) {
    return pq->count == MAX-1;
}
void insert(PriorityQueue *pq, int value) {

    int child, pr;

    pq->count++;
    child = pq->count;
    pr = (child-1)/2;

    while (child > 0 && pq->arr[pr] < value) {
        pq->arr[child] = pq->arr[pr];
        child = pr;
        pr = (child-1)/2;
    }

    pq->arr[child] = value;
}
int deleteMax(PriorityQueue *pq) {

    int root = pq->arr[0];
    pq->arr[0] = pq->arr[pq->count];
    pq->count--;

    int pr = 0;
    int child = 2 * pr +1;

    while (child <= pq->count) {
        if (child +1 <= pq->count && pq->arr[child+1] > pq->arr[child]) {
            child++;
        }

        if (pq->arr[pr] < pq->arr[child]) {
            int swap = pq->arr[pr];
            pq->arr[pr] = pq->arr[child];
            pq->arr[child] = swap;

            pr = child;
            child = 2 * pr +1;
        } else {
            break;
        }
    }

    return root;

}
void display(PriorityQueue *pq) {
    for(int i = 0; i <= pq->count; i++) {
        printf(" %d ", pq->arr[i]);
    }
}

void heapSort (PriorityQueue *pq) {
    
    int orig, catcher;

    orig = pq->count;
    pq->count = -1;


    for(int i = 0; i <= orig ; i++) {
        insert(pq, pq->arr[i]);
    }


    for(int i = orig; i >= 0; i--) {
        catcher = deleteMax(pq);
        pq->arr[i] = catcher;
    }

    pq->count = orig;
}

/*
==========================================
EXPECTED OUTPUT
==========================================
Priority Queue contents:
50 40 30 10 20 

Deleting max...
Removed: 50

Priority Queue after delete:
40 20 30 10 
==========================================
*/

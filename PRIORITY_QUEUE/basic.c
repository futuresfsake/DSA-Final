#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int elem[MAX];
    int lastndx;     // index of last element ( -1 means empty )
} PQueue;

// ==========================================================
// FUNCTION PROTOTYPES
// ==========================================================
void initPQ(PQueue* pq);
bool isEmpty(PQueue pq);
bool isFull(PQueue pq);
void insertPQ(PQueue* pq, int value);   // enqueue with priority
int deleteMin(PQueue* pq);              // dequeue
void displayPQ(PQueue pq);              // array level-order
void preorder(int heap[], int i, int n);
void inorder(int heap[], int i, int n);
void postorder(int heap[], int i, int n);

// ==========================================================
// MAIN
// ==========================================================
int main() {
    PQueue pq;
    initPQ(&pq);

    insertPQ(&pq, 40);
    insertPQ(&pq, 10);
    insertPQ(&pq, 30);
    insertPQ(&pq, 5);
    insertPQ(&pq, 60);

    printf("\nPriority Queue (Level Order): ");
    displayPQ(pq);

    printf("\nPreorder: ");
    preorder(pq.elem, 0, pq.lastndx + 1);

    printf("\nInorder: ");
    inorder(pq.elem, 0, pq.lastndx + 1);

    printf("\nPostorder: ");
    postorder(pq.elem, 0, pq.lastndx + 1);

    printf("\n\nDeleted Min = %d\n", deleteMin(&pq));

    printf("\nAfter delete: ");
    displayPQ(pq);

    return 0;
}

// ==========================================================
// FUNCTION DEFINITIONS (You will fill these)
// ==========================================================

void initPQ(PQueue* pq) {
    
    pq->lastndx = -1;
}
bool isEmpty(PQueue pq) {
    return pq.lastndx == -1;
}
bool isFull(PQueue pq) {
    return pq.lastndx == MAX -1;
}
void insertPQ(PQueue* pq, int value) {

    int idx, prntidx;

    if (pq->lastndx == MAX -1) {
        printf("Heap is already full\n");
        return;
    }


    pq->lastndx++;
    idx = pq->lastndx;
    prntidx = (idx -1) / 2;

    while (idx > 0 && pq->elem[prntidx] > value) {
        pq->elem[idx] = pq->elem[prntidx];
        idx = prntidx;
        prntidx = (idx -1) / 2;

    }

    pq->elem[idx] = value;


} 

int deleteMin(PQueue* pq) {

    int ret, trav, child, swap;

    // * check first if there is something to delete, check if it is empty or not

    if (pq->lastndx == -1) {
        printf("Heap is empty!\n");
        return -1;
    }


    // ! THIS IS TO SAVE AND REMOVE THE ROOT, smallest item stored in ret
    // ! last element moved to top

    ret = pq->elem[0]; // TODO return the smallest
    pq->elem[0] = pq->elem[pq->lastndx]; // TODO move last element to the root
    pq->lastndx--; // TODO shrink the heap


    // ! START TO BUBBLE-DOWN
    // * trav is the index of the current node
    // * child is its left child (2 * 0 + 1 = 1)
    trav = 0; // TODO start from the root
    child = 1; // TODO left child



    // * while a child still exsits, keep going until we reach the bottom

    while (child <= pq->lastndx) {

        // TODO : choose the smaller child
        // ! a min heap must compare the smaller of the two children

        // * child + 1 <= pq->lstindx => checks if the right child exists, this has nothing to do with the last index being smaller or bigger, it just ensures that we dont access outside the array
        // * pq->elem[child+1] < pq->elem[child] => compares right vs left, if right child is smaller than left child, we want tp consider the right child as the one to swap with the parent
        //* moves the child index from left to right, so the smaller of the two children is used in the enxt swap
        if (child + 1 <= pq->lastndx && pq->elem[child+1] < pq->elem[child]) {
            child++;
        }



        // TODO  if parent > smaller child, swap
        //* in the first traversal, if the root is greatr than the left child, we have to 
        //* to put th e left child as the root
        if (pq->elem[trav] > pq->elem[child]) {
            swap = pq->elem[trav];
            pq->elem[trav] = pq->elem[child];
            pq->elem[child] = swap;

            // ! this line is all about continuiong the bubble down process
            // * we need to continue, because the new position may still violate the heap property with its own children

            
            // ! so we need to update the indexes
            trav = child;  // TODO move downwards, now the parent is at the new position
            child = 2 * trav +1;  // TODO recompute new child,, left child of new parent

        } else {
            break;
        }


    }

    return ret; // ! ret is just a simple var, it just stores the root value, while all the traversals and condiitons
                // ! its  just a way in adjusting and ensuring the property of POT!
}          // dequeue
void displayPQ(PQueue pq);              // array level-order
void preorder(int heap[], int i, int n);
void inorder(int heap[], int i, int n);
void postorder(int heap[], int i, int n);

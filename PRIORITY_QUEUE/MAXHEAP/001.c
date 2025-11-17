#include <stdio.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int elem[MAX];
    int lastndx;
} Heap;

// ===== Function Declarations =====
void addElemMax(Heap* H, int val);
int deleteMax(Heap* H);
void displayHeap(Heap* H);
void HeapSortAsc(Heap* H);
void MaxHeapify (Heap* H);

// ===== Main =====
int main() {
    Heap H;
    H.lastndx = -1;

    // Sample insertions
    addElemMax(&H, 15);
    addElemMax(&H, 10);
    addElemMax(&H, 20);
    addElemMax(&H, 8);
    addElemMax(&H, 25);

    printf("Max-Heap (level-order): ");
    displayHeap(&H);

    printf("Deleting root: %d\n", deleteMax(&H));
    printf("After deletion: ");
    displayHeap(&H);

    printf("HeapSort Ascending:\n");
    HeapSortAsc(&H);
    displayHeap(&H);

    printf("Max Heapify: \n");

    MaxHeapify(&H);
    displayHeap(&H);

    return 0;
}

void addElemMax(Heap* H, int val) {
    
    int idx, pr;

    if (H->lastndx == MAX-1) return;

    H->lastndx++;
    idx = H->lastndx;
    pr = (idx -1) / 2;

    while (idx > 0 && H->elem[pr] < val) {
        H->elem[idx] = H->elem[pr];
        idx = pr;
        pr = (idx -1) / 2;
    }

    H->elem[idx] = val;
}


int deleteMax(Heap* H) {
    int ret, trav, child, swap;

    if (H->lastndx == -1) return -1;

    ret = H->elem[0];
    H->elem[0] = H->elem[H->lastndx];
    H->lastndx--;

    trav = 0;
    child = 1;


    while (child <= H->lastndx) {

        if (child +1 <= H->lastndx && H->elem[child+1] > H->elem[child]) {
            child++;
        }

        if (H->elem[trav] < H->elem[child]) {
            swap = H->elem[trav];
            H->elem[trav] = H->elem[child];
            H->elem[child] = swap;


            trav = child;
            child = 2 * trav +1;
        } 
        else {
            break;
        }
    }
    return ret;
}

void displayHeap(Heap* H) {
    for(int i = 0; i <=H->lastndx; i++) {
        printf("%d->", H->elem[i]);
    }
    printf("NULL\n");
}
void HeapSortAsc(Heap* H) {
    int orig, catcher;

    orig = H->lastndx;
    H->lastndx =-1;

    for(int i = 0; i <= orig; i++) {
        addElemMax(H, H->elem[i]);
    }

    for(int i = orig;i >= 0; i--) {
        catcher = deleteMax(H);
        H->elem[i] = catcher;
    }

    H->lastndx = orig;
}



void MaxHeapify (Heap* H) {

    int lowPar, down, child, swap;

    if (H->lastndx == -1) return;

    lowPar = (H->lastndx -1) / 2;

    while (lowPar >= 0) {
        down = lowPar;
        child = 2 * down +1;


        while (child <= H->lastndx) {
            if (child +1 <= H->lastndx && H->elem[child+1] > H->elem[child]) {
                child++;
            }

            if (H->elem[down] < H->elem[child]) {
                swap = H->elem[down];
                H->elem[down] = H->elem[child];
                H->elem[child] = swap;


                down = child;
                child = 2 * down + 1;
            } else {
                break;
            }
          
        }
          lowPar--;
    }
}

#include <stdio.h>
#include <stdbool.h>

#define MAX 20

// ===== Min Heap Structure =====
typedef struct {
    int elem[MAX];
    int lastndx;
} MinHeap;

// ===== Function Declarations =====
void initHeap(MinHeap* H);
void insertMin(MinHeap* H, int val);
int deleteMin(MinHeap* H);
void minHeapify(MinHeap* H);
void heapSortDescending(MinHeap* H);
void displayHeap(MinHeap* H);

// ===== Main =====
int main() {
    MinHeap H;
    initHeap(&H);

    insertMin(&H, 30);
    insertMin(&H, 15);
    insertMin(&H, 50);
    insertMin(&H, 10);
    insertMin(&H, 40);
    insertMin(&H, 20);

    printf("Min-Heap (level-order): ");
    displayHeap(&H);

    printf("Deleting min: %d\n", deleteMin(&H));

    printf("After deletion: ");
    displayHeap(&H);

    printf("Rebuilding heap using minHeapify:\n");
    minHeapify(&H);
    displayHeap(&H);

    printf("Heap Sort Descending:\n");
    heapSortDescending(&H);
    displayHeap(&H);

    return 0;
}

// ===== Function Definitions (YOU FILL IN) =====

// initialize heap
void initHeap(MinHeap* H) {

    H->lastndx = -1;

}

// insert into min-heap
void insertMin(MinHeap* H, int val) {
    

    int child, parent;

    if (H->lastndx == MAX -1) {
        printf("Heap is already full!\n");
        return;
    }

    H->lastndx++;
    child = H->lastndx;
    parent = (child -1) /2;

    while (child > 0 && H->elem[parent] > val) {
        H->elem[child] = H->elem[parent];
        child = parent;
        parent = (child -1) / 2;
    }

    H->elem[child] = val;

}

// delete minimum element (root)
int deleteMin(MinHeap* H) {
  
    int ret, pr, child, swap;

    if (H->lastndx == -1) return -1;


    ret = H->elem[0];
    H->elem[0] = H->elem[H->lastndx];
    H->lastndx--;


    pr = 0;
    child = 1;

    while (child <= H->lastndx) {

        if (child + 1 <= H->lastndx && H->elem[child+1] < H->elem[child]) {
            child++;
        }

        if (H->elem[pr] > H->elem[child]) {
            swap = H->elem[pr];
            H->elem[pr] = H->elem[child];
            H->elem[child] = swap;

            //* recompute

            pr = child;
            child = pr * 2 +1;
        }

        else {
            break;
        }
    }
    return ret;
}

// bottom-up heapify
void minHeapify(MinHeap* H) {
    
    int pr, down, child, swap;

    if (H->lastndx == -1) return;


    pr = (H->lastndx -1) /2;

    while (pr >= 0) {
        down = pr;
        child = 2 * down + 1;

        while (child <= H->lastndx) {

            if (child +1 <= H->lastndx && H->elem[child+1] < H->elem[child] ) {
                child++;
            }

            if (H->elem[down] > H->elem[child]) {
                swap = H->elem[down];
                H->elem[down] = H->elem[child];
                H->elem[child] = swap;


                down = child;
                child = (down * 2) +1;
            }
            else {
                break;

            }
        }
        pr--;
    }
}

// heap sort (ascending) using deleteMin repeatedly OR in-place heap sort
void heapSortDescending(MinHeap* H) {
    
    int orig, catcher;

    orig = H->lastndx;
    H->lastndx = -1;

    for(int i =0; i <= orig; i++) {
        insertMin(H, H->elem[i]);
    }

    for(int i = orig; i >= 0; i--) {
        catcher = deleteMin(H);
        H->elem[i] = catcher;

    }
    H->lastndx = orig;
}

// display array (level-order)
void displayHeap(MinHeap* H) {
    for(int i = 0; i <= H->lastndx; i++) {
        printf("%d->", H->elem[i]);
    }
    printf("NULL\n");
}

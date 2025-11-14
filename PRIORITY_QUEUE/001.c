#include <stdio.h>
#include <stdbool.h>


#define MAX 10

typedef struct {
    int elem[MAX];
    int lastndx;
} Heap;



void addElem (Heap* H, int elem);

void displayInorder(Heap* H, int i) {
    if (i > H->lastndx) return;   // base case

    displayInorder(H, 2*i + 1);   // left child
    printf("%d ", H->elem[i]);    // root
    displayInorder(H, 2*i + 2);   // right child
}

int main() {
    Heap H;
    H.lastndx = -1; // Initialize empty heap

    // Insert elements
    addElem(&H, 15);
    addElem(&H, 10);
    addElem(&H, 20);
    addElem(&H, 8);
    addElem(&H, 25);

     printf("Heap elements (inorder): ");
    displayInorder(&H, 0); // start at root
    printf("\n");


    return 0;
}

void addElem (Heap* H, int elem) {
    int idx; //  TODO get the last index
    int parIdx;  // TODO use for computing the parent
    

    // * 1. Check if there is still space
    if (H->lastndx == MAX -1) {
        printf("Heap is full!\n");
        return;
    }

    // * 2. Insert at last index +1
    H->lastndx++;  // ! this is the only time index is incremented in insertion
    idx = H->lastndx;  // * this means, we found a free space at the end of the heap
    parIdx = (idx -1) / 2;     // ! this is a way to compute the parent index

    // * allows changing the root, we just dont check beyond the root
    while (idx > 0 && H->elem[parIdx] > elem) {
        H->elem[idx] = H->elem[parIdx]; // * it copies the parent value down into the current position
        idx = parIdx;   // ! move to the next parent
        parIdx = (idx -1) / 2;  // ! recompute the parent
    }


    H->elem[idx] = elem;

}


#include <stdio.h>
#include <stdbool.h>


#define MAX 10

typedef struct {
    int elem[MAX];
    int lastndx;
} Heap;



void addElem (Heap* H, int elem);

void displayInorder(Heap* H) {
    for(int i = 0; i <= H->lastndx; i++) {
    
    printf("%d->", H->elem[i]);
    }
    printf("NULL\n");
}

int deleteElem(Heap* H);

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
    displayInorder(&H); // start at root
    printf("\n");

    deleteElem(&H);
    printf("After deleting the root (8):\n");
         printf("Heap elements (inorder): ");
             displayInorder(&H); // start at root




    return 0;
}

void addElem (Heap* H, int elem) {
    int idx; //  TODO get the last index
    int parIdx;  // TODO use for computing the parent
    

    // * 1. Check if there is still space
    if (H->lastndx == MAX -1) {
        printf("Heap is full!\n");
        return ;
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



int deleteElem(Heap* H) {
    int ret, child, trav, swap;


    if (H->lastndx == -1) return -1;


    ret = H->elem[0];
    H->elem[0] = H->elem[H->lastndx];
    H->lastndx--;

    trav = 0;
    child = 1;


    while (child <= H->lastndx) {

    if (child +1 <= H->lastndx && H->elem[child+1] < H->elem[child]) {
        child++;
    }

    if ( H->elem[trav] > H->elem[child]) {
        swap = H->elem[trav];
        H->elem[trav] = H->elem[child];
        H->elem[child] = swap;


        trav = child;
        child = 2*trav+ 1;
    } else {
        break;
    }



    }
    return ret;
}
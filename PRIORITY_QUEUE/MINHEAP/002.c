
//! minheap 
#include <stdio.h>
#include <stdbool.h>

#define MAX 10

//========== STRUCTURE ==========
typedef struct {
    int elem[MAX];
    int lastndx;
} Heap;


//========== FUNCTION DECLARATIONS ==========
void addElem(Heap* H, int elem);
int deleteElem(Heap* H);

void HeapSortAsc(Heap* H);
void HeapSortDesc(Heap* H);

void displayInorder(Heap* H);
void Minheapify(Heap* H);


//========== MAIN PROGRAM ==========
int main() {
    Heap H;
    H.lastndx = -1;

    // Sample insertions
    addElem(&H, 15);
    addElem(&H, 10);
    addElem(&H, 20);
    addElem(&H, 8);
    addElem(&H, 25);

    printf("Heap elements (level-order): ");
    displayInorder(&H);

    printf("\nDeleting root...\n");
    deleteElem(&H);

    printf("After deletion: ");
    displayInorder(&H);

    printf("\nHeapSort Desc:\n");
    HeapSortDesc(&H);
    displayInorder(&H);

    printf("\nHeapSort Asc:\n");
    HeapSortAsc(&H);
    displayInorder(&H);

    return 0;
}


//========== FUNCTION DEFINITIONS (EMPTY) ==========

// Insert into Min-Heap
void addElem(Heap* H, int elem) {
    // TODO: implement insertion up-heap bubbling

        //* idx to get the lastindex, and pr to compute for the parent
    int idx, pr;


    //* check if it is full or not
    if (H->lastndx == MAX -1) {
        printf("Binary heap is already full!\n");
        return;
    }

    //* if not, increment the count
    H->lastndx++;
    idx = H->lastndx; //* get the last index and store it in idx 
    pr = (idx-1) / 2;  //* compute for the parent



    while (idx >0 && H->elem[pr] >elem) { //* check if it follows the heap property
        H->elem[idx] =  H->elem[pr];  //* u put the parent first in the idx
        idx = pr;  //* u go up, by updating the index into the parent's index
        pr = (idx -1) /2;  //* recalculate the index
    }

    H->elem[idx] = elem; //* insert it 
    

}

// Delete root of Min-Heap
int deleteElem(Heap* H) {
    
    int ret, child, pr, swap;

    //* check if it is empty
    if (H->lastndx == -1) return -1;

    //* get the value, fill the root with the last element, decrement

    ret = H->elem[0]; 
    //* replace it with the last element from the last index
    H->elem[0] = H->elem[H->lastndx];
    H->lastndx--;

    //* compute for traversals, pr as parent, start in 0, start in left child as 1

    pr = 0;
    child = 1;


    //* check for the property, check for the bounds

    while (child <= H->lastndx) {

        //* check if the right child is in bounds, 
        //*and r is lesser than L, then move to the next child 

        if (child+1 <= H->lastndx && H->elem[child+1] < H->elem[child]) {
            child++; //* move to the next child
        }

        //* check if the parent child property is correct
        if (H->elem[pr] > H->elem[child]) {
            //* start to swap
            swap = H->elem[pr];
            H->elem[pr] = H->elem[child];
            H->elem[child] = swap;


            //* recompute to check the next nodes
            pr = child; //* now, go to the next index that could be a parent
            child = 2*pr +1; //* go to the right child?


        } else {
            break; //* if it satisfies the property break and return;
        }
    }

    return ret;



}

// HeapSort (Ascending)
void HeapSortDesc(Heap* H) {
    // TODO: build heap then deleteMin repeatedly (store from index 0 upward)

    int i, orig, catcher;

    orig = H->lastndx;
    H->lastndx = -1;

    for(int i = 0; i <= orig; i++) {
        addElem(H, H->elem[i]);
    }

    for(int i = orig; i >= 0; i--) {
        catcher = deleteElem(H);
        H->elem[i] = catcher;
    }

    H->lastndx = orig;

}

void HeapSortAsc(Heap* H) {
    // TODO: build heap then deleteMin repeatedly (store from index 0 upward)

    int orig, catcher,n;

    orig = H->lastndx;
    n = orig+1;
    Minheapify(H);
    int temp[MAX];

    for(int i = 0; i < n;i++) {

        temp[i] = deleteElem(H);
    }

    for(int i = 0; i < n; i++) {
        H->elem[i] = temp[i];
    }

    H->lastndx = orig;
  

}




// Display array (level order)
void displayInorder(Heap* H) {
    // TODO: just print the array from index 0 to lastndx
    for(int i = 0; i <= H->lastndx; i++) {
        printf("%d ", H->elem[i]);
    }
    printf("\n");
}


void Minheapify(Heap* H) {
    int child, pr, down, swap;

    if (H->lastndx == -1) return;


    pr = H->lastndx;

    while (pr>=0) {
        down = pr; //* use this to trav
        child = 2*down +1; //* go to the left child


        //* check if child still exists

        while (child <= H->lastndx) {

            //* check the right child exists && smaller than left

            if (child+1 <= H->lastndx && H->elem[child+1] < H->elem[child]) {
                child++;
            }

            //* if parent>child, violates property swap
            if (H->elem[down]>H->elem[child]) {
                swap = H->elem[down];
                H->elem[down] = H->elem[child];
                H->elem[child] = swap;

                down = child;
                child = 2*down +1;
            }

            else {
                break;
            }
        }
        pr--;
    }
}
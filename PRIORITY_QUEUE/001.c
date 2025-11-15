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
void HeapSortDesc(Heap* H);
void HeapSortAsc(Heap* H);


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


    HeapSortDesc(&H);
    displayInorder(&H);
    HeapSortAsc(&H);
    displayInorder(&H);



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



// void HeapSort(Heap* H) {
//     int i, orig, catcher;
//     int temp[MAX];

//     orig = H->lastndx;

//     // Step 1: copy elements to temp
//     for(i = 0; i <= orig; i++)    // * this is just a safe copy 
//         temp[i] = H->elem[i];

//     // Step 2: rebuild heap 
//     H->lastndx = -1; // * this is a way to reset heap, next insertions will rebuild the heap from scratch
//     for(i = 0; i <= orig; i++)
//         addElem(H, temp[i]); // * every insert the new element is bubbled up until heap property is resrtored

//     // Step 3: delete min repeatedly and store back //* delete the elements to sort
//     //* or in for loop u can (for(i = orig; i >= 0; i--) )
//    for(i = orig; i >= 0; i--) { //* 
//         catcher = deleteElem(H);
//         H->elem[i] = catcher;  
//         //* we start in the last index in storing the first root, for it to get descending
//     }

//     H->lastndx = orig;
// }


//* not using a temporary array, shorthand style
void HeapSortDesc (Heap* H) {
    int i, orig, catcher;

    orig = H->lastndx;   //* save the original last index
    H->lastndx= -1;  //* reset the heap
    

    for(i = 0; i <= orig; i++) {  //* add again the elem to H
        addElem(H, H->elem[i]); //* it will adjust all the elements
    } //! meaning old values are still there, but the heap is empty logically

    for(i = orig; i >= 0; i--) {  //* after deleting, it will store the root node in the last index
        catcher = deleteElem(H);
        H->elem[i] = catcher;
    }

    H->lastndx = orig; //* copy the lstindex in orig


}

void HeapSortAsc(Heap* H) {
    int i, orig, catcher;

    orig = H->lastndx;   //* save the original last index
    H->lastndx= -1;  //* reset the heap
    

    for(i = 0; i <= orig; i++) {  //* add again the elem to H
        addElem(H, H->elem[i]); //* it will adjust all the elements
    } //! meaning old values are still there, but the heap is empty logically

    for(i = 0; i <= orig; i++) {  //* after deleting, it will store the root node in the last index
        catcher = deleteElem(H);
        H->elem[i] = catcher;
    }

    H->lastndx = orig; //* copy the lstindex in orig


}
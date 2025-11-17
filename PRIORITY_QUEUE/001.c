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
void Minheapify(Heap* H);


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

    printf("Descending Order: \n");
    HeapSortDesc(&H);
    displayInorder(&H);
    printf("Ascending Order: \n");
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
    //* ret is for the value that will be returned and it stores the root data
    //* child is the one u will use for traversing
    //* trav is for the parent
    //* swap will be used if there is an error in heap property, used for swapping


    // todo check if it is empty or not
    if (H->lastndx == -1) return -1;



    //* ret, get the root value
    ret = H->elem[0];
    H->elem[0] = H->elem[H->lastndx]; //* replace the last node and put it to the root
    H->lastndx--; //* decrement

    trav = 0;  //* compute for the root, start 0 as the parent, we go down
    child = 1; //* child as 1, 1 is left child


    //* we check for the bounds
    while (child <= H->lastndx) {


//* if right child is still in bounds, and right child is lesser than left child, child++
    if (child +1 <= H->lastndx && H->elem[child+1] < H->elem[child]) {
        child++;
    }

    //* if trav (parent) is greater than the child, then swap
    if ( H->elem[trav] > H->elem[child]) {
        swap = H->elem[trav];
        H->elem[trav] = H->elem[child];
        H->elem[child] = swap;



        //* recompute
        trav = child;
        child = 2*trav+ 1; //* go to the right child
    } else {
        break;
    }
    }
    return ret;
}





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
  

     int orig = H->lastndx;
    int n = orig + 1;
    int catcher;

    Minheapify(H); // ensure it’s a min-heap

    int temp[MAX]; // temporary array to store deleted elements

    for(int i = 0; i < n; i++) {
        temp[i] = deleteElem(H); // smallest element first
    }

    // Copy back to original heap array
    for(int i = 0; i < n; i++) {
        H->elem[i] = temp[i];
    }

    H->lastndx = orig;
}    


//* u cant call maxheapify, then use the deleteElem, because its property will use the swapping condiiton using minheap condition
//* so if u want to call maxheapify, create a deleteMax function, then and call maxheapify in heapsortAsc

// void HeapSortAsc(Heap* H) {
//     int orig = H->lastndx;
//     int n = orig + 1;
//     int catcher;

//     // Step 1: make sure the array is a min-heap
//     Minheapify(H);

//     // Step 2: delete root repeatedly, store from end
//     for(int i = n-1; i >= 0; i--) {
//         catcher = deleteElem(H);
//         H->elem[i] = catcher;
//     }

//     // Step 3: reverse the array to get ascending order
//     for(int i = 0; i < n/2; i++) {
//         int tmp = H->elem[i];
//         H->elem[i] = H->elem[n-1-i];
//         H->elem[n-1-i] = tmp;
//     }

//     // restore last index
//     H->lastndx = orig;
// }


void Minheapify (Heap* H) {

    int lowpar, down, child, swap;
    //* lowpar is the index of the last parent of the heap
    //* down - the current node we are checking
    //* child - index of the child we compare
    //* swap = temp var for swapping


    // todo: check if it is empty
    if (H->lastndx == -1) return;

    //todo compute for the last parent of the heap
    lowpar = (H->lastndx -1) / 2;
     // todo check for the bounds, we go upward

     while (lowpar >=0) {
        down = lowpar; //* start pushing the parent down
        child = 2* down + 1; //* left child


        // todo: check if right child exists and it is smaller than left
        if (child +1<= H->lastndx && H->elem[child+1] < H->elem[child]) {
            child++;
        }


        if (H->elem[down] > H->elem[child]) {
            swap = H->elem[down];
            H->elem[down] = H->elem[child];
            H->elem[child] = swap;

            down = child;
            child = down*2+1;
        }

        else {
            break; //* break the inner loop, no more swap
        }

        lowpar--; //* iterative upward

     }

}
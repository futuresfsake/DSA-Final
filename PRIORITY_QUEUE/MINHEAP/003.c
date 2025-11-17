#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 20

// ===== Item structure =====
typedef struct {
    char name[30];
} Item;

// ===== MinHeap structure =====
typedef struct {
    Item elem[MAX];
    int lastndx;
} MinHeap;

// ===== Function Declarations =====
void initHeap(MinHeap* H);
void insertMin(MinHeap* H, Item X);
Item deleteMin(MinHeap* H);
void minHeapify(MinHeap* H); 
void displayHeap(MinHeap* H);
void HeapSort(MinHeap* H);

// ===== Main =====
int main() {
    MinHeap H;
    initHeap(&H);

    Item A = {"zebra"};
    Item B = {"apple"};
    Item C = {"monkey"};
    Item D = {"bear"};
    Item E = {"cat"};

    insertMin(&H, A);
    insertMin(&H, B);
    insertMin(&H, C);
    insertMin(&H, D);
    insertMin(&H, E);

    printf("Min-Heap (level-order): ");
    displayHeap(&H);

    printf("Deleting Min: %s\n", deleteMin(&H).name);

    printf("After deletion: ");
    displayHeap(&H);

    printf("Heapify again (if heap is partially damaged):\n");
    minHeapify(&H);
    displayHeap(&H);

    printf("Heap Sort: \n");
    HeapSort(&H);
     displayHeap(&H);


    return 0;
}


void initHeap(MinHeap* H) {
    H->lastndx = -1;
}
void insertMin(MinHeap* H, Item X) {

    int idx, paridx;

    if (H->lastndx == MAX -1) {
        printf("Binary Heap is already full!\n");
        return;
    }


    H->lastndx++;
    idx = H->lastndx;
    paridx = (idx -1)/2;

    while (idx >0 && strcmp(H->elem[paridx].name, X.name ) > 0) {
        H->elem[idx] = H->elem[paridx];
        idx = paridx;
        paridx = (idx -1) / 2;

    }

    H->elem[idx] = X;


}


Item deleteMin(MinHeap* H) {

    Item ret;
    int par, child;
    Item swap;

    if (H->lastndx == -1) {
        printf("Heap is empty!\n");
        exit(1);
    }

    ret = H->elem[0];
    H->elem[0] = H->elem[H->lastndx];
    H->lastndx--;


    par = 0;
    child =1;

    while (child <= H->lastndx) {


        if (child+1 <= H->lastndx && strcmp(H->elem[child+1].name, H->elem[child].name) <0) {
            child++;
        }

        if (strcmp(H->elem[par].name, H->elem[child].name)>0) {

            swap = H->elem[par];
            H->elem[par] = H->elem[child];
            H->elem[child] = swap;


            par = child;
            child = child * 2 +1;

        }

        else {
            break;
        }
    }
    return ret;



}
void minHeapify(MinHeap* H) {
    
    int lowpar, down, child;
    Item swap;


    if (H->lastndx == -1) return;

    lowpar = (H->lastndx -1)/2;

    while (lowpar >= 0) {
        down = lowpar;
        child = 2*down +1;

        while (child <= H->lastndx) {

            if (child +1 <= H->lastndx && strcmp(H->elem[child+1].name, H->elem[child].name) <0) {
                child++;
            }

            if (strcmp(H->elem[down].name, H->elem[child].name) >0) {
                swap = H->elem[down];
                H->elem[down] = H->elem[child];
                H->elem[child] = swap;

                down = child;
                child = 2 * down +1;


            }
            else {
                break;
            }

        }
        lowpar--;

    }
}


void displayHeap(MinHeap* H) {
    for(int i = 0; i <= H->lastndx; i++) {
        printf("%s ->", H->elem[i].name);
    }
    printf("NULL\n");
}


void HeapSort(MinHeap* H) {
    
    int orig;
    Item catcher;

    orig = H->lastndx;
    H->lastndx = -1;

    for(int i = 0; i <= orig; i++) {
        insertMin(H, H->elem[i]);
    }

    for(int i = orig; i >=0; i--) {
        catcher = deleteMin(H);
        H->elem[i] = catcher;
    }

    H->lastndx =orig;
}

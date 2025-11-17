#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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

    return 0;
}

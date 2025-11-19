#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_HEAP 100
#define MAX_STR 50

// ===== Nested Struct =====
typedef struct {
    char name[MAX_STR];
    int priority;   // Higher value = higher priority
} Item;

// ===== Max Heap Structure =====
typedef struct {
    Item heap[MAX_HEAP];
    int size;
} MaxHeap;

// ===== Function Declarations =====
void initHeap(MaxHeap* H);
void insertMax(MaxHeap* H, Item x);
Item deleteMax(MaxHeap* H);
void maxHeapify(MaxHeap* H);
void displayHeap(MaxHeap* H);
void heapSort(MaxHeap* H);
bool increasePriority(MaxHeap* H, char* name, int newPriority);
void mergeHeap(MaxHeap* H, MaxHeap* H2);


int main() {
    MaxHeap H1, H2;
    initHeap(&H1);
    initHeap(&H2);

    // ===== Test insertMax =====
    Item a = {"Alice", 5};
    Item b = {"Bob", 3};
    Item c = {"Charlie", 8};

    insertMax(&H1, a);
    insertMax(&H1, b);
    insertMax(&H1, c);

    printf("\nHeap H1 AFTER insertions:\n");
    displayHeap(&H1);

    // ===== Test deleteMax =====
    Item removed = deleteMax(&H1);
    printf("\nRemoved: %s with priority %d\n", removed.name, removed.priority);
    printf("\nHeap H1 AFTER deleteMax:\n");
    displayHeap(&H1);

    // ===== Test heapSort =====
    printf("\nHeap H1 BEFORE heapSort:\n");
    displayHeap(&H1);
    heapSort(&H1);
    printf("\nHeap H1 AFTER heapSort:\n");
    displayHeap(&H1);

    // ===== Test increasePriority =====
    printf("\nIncreasing priority of Bob to 15...\n");
    increasePriority(&H1, "Bob", 15);
    displayHeap(&H1);

    // ===== Test mergeHeap =====
    // Fill second heap
    Item d = {"Daniel", 10};
    Item e = {"Emma", 1};
    insertMax(&H2, d);
    insertMax(&H2, e);

    printf("\nHeap H2 BEFORE merge:\n");
    displayHeap(&H2);

    // Merge H2 into H1
    printf("\nMerging H2 into H1...\n");
    mergeHeap(&H1, &H2);
    printf("\nHeap H1 AFTER merge:\n");
    displayHeap(&H1);

    heapSort(&H1);
    printf("Heapsorting the newly merged haeps!\n");
    displayHeap(&H1);
    return 0;
}


// ===== Function Definitions =====
// Implement the logic yourself!

void initHeap(MaxHeap* H) {
    
    H->size = -1;
                                                                                                     
}

void insertMax(MaxHeap* H, Item x) {
    // TODO

    int child, pr;
    Item swap;


    if (H->size == MAX_HEAP -1) {
        printf("heap is already full!\n");
        return;
    }

    H->size++;
    child = H->size;
    pr = (child -1) / 2;


    while (child > 0 && H->heap[pr].priority < H->heap[child].priority) {
        H->heap[child] = H->heap[pr];
        child = pr;
        pr = (child -1)/2;

    }


    H->heap[child] = x;
    printf("%s Added successfully \n", x.name);
}

Item deleteMax(MaxHeap* H) {


    Item ret, swap;
    int child, pr;


    if (H->size == -1) {
        printf("Heap is empty!\n");
        exit(1);
    }


    ret = H->heap[0];
    H->heap[0] = H->heap[H->size];
    H->size--;


    pr = 0;
    child = 1;

    while (child <= H->size) {

        if (child +1 <= H->size && H->heap[child+1].priority > H->heap[child].priority) {
            child++;
        }


        if (H->heap[pr].priority < H->heap[child].priority) {
            swap = H->heap[pr];
            H->heap[pr] = H->heap[child];
            H->heap[child] = swap;

            pr = child;
            child = 2 * pr +1;
        } else {
            break;
        }
    }

    return ret;

    

}



void displayHeap(MaxHeap* H) {
    printf("Priority Queue: \n");
    
    for(int i = 0; i <= H->size; i++) {
        printf("INDEX[%d] -> [%s][%d]\n", i, H->heap[i].name, H->heap[i].priority);

    }
}

void maxHeapify(MaxHeap* H) {
    
    int pr, child, down;
    Item swap;

    if (H->size == -1) {
        printf("Nothing to sort here!\n");
        return;
    }

    pr = (H->size -1) /2;

    while (pr>= 0) {
        down = pr;
        child = down*2 +1;

        while (child <= H->size) {
            if (child +1 <= H->size && H->heap[child+1].priority > H->heap[child].priority) {
                child++;
            }

            if (H->heap[down].priority < H->heap[child].priority) {
                swap = H->heap[down];
                H->heap[down] = H->heap[child];
                H->heap[child] = swap;

                down = child;
                child = 2 * down+1;            } 
                else {
                    break;
                }
        }
        pr--;
    }



}

void heapSort(MaxHeap* H) {
    int orig; 
    Item catcher;

    orig = H->size;
    
    

    maxHeapify(H);

    for(int i = orig; i >= 0; i--) {
       catcher = deleteMax(H);
       H->heap[i] = catcher; 
    }
    H->size = orig;


}

bool increasePriority(MaxHeap* H, char* name, int newPriority) {
    // TODO
    
    int i;
    bool found = 0;
    
    for( i = 0; i <= H->size; i++) {
        if (strcmp(H->heap[i].name, name) ==0) {
            H->heap[i].priority = newPriority;
            found =true;
            break;
        }
    }

    Item temp = H->heap[i];

    if (found) {
        int child = i;
        int pr = child -1/2;

        while (child>0 && H->heap[pr].priority < H->heap[child].priority) {
              H->heap[child] = H->heap[pr];
                child = pr;
                pr = (child - 1) / 2;
        } 
        H->heap[child] = temp;
    }
    return found;
       
    }


void mergeHeap(MaxHeap* H, MaxHeap* H2) {
    
    for(int i = 0; i <= H2->size; i++) {
        insertMax(H, H2->heap[i]);
    }
}

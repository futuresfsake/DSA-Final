#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 10

// ===================== STRUCT DEFINITIONS =====================
typedef struct {
    int severity;       // 1–10 (higher = more urgent)
    int arrivalOrder;   // smaller = arrived earlier
    int age;            // older gets priority if tie
} Condition;

typedef struct {
    char name[40];
    Condition info;
} Patient;

typedef struct {
    Patient heap[MAXN];
    int last;           // index of the last element in the heap
} PatientMaxHeap;

// ===================== FUNCTION PROTOTYPES =====================

// Heap initialization & status
void initHeap(PatientMaxHeap* H);
bool isEmpty(PatientMaxHeap* H);
bool isFull(PatientMaxHeap* H);

// Heap operations
void swapPatient(Patient* a, Patient* b);
bool hasHigherPriority(Patient a, Patient b);

void insertMax(PatientMaxHeap* H, Patient x);
Patient deleteMax(PatientMaxHeap* H);
Patient peekMax(PatientMaxHeap* H);
void maxHeapify(PatientMaxHeap* H, int index);

// Display & sorting
void displayHeap(PatientMaxHeap* H);
void increaseSeverity(PatientMaxHeap* H, int index, int amount);
void heapSortPatients(PatientMaxHeap* H);

// ===================== MAIN FUNCTION =====================
int main() {
    PatientMaxHeap H;
    initHeap(&H);

    // Create patients
    Patient p1 = {"Alice",   {8,  1, 45}};
    Patient p2 = {"Bob",     {13, 2, 60}};
    Patient p3 = {"Charlie", {7, 3, 20}};
    Patient p4 = {"Diana",   {12,  4, 75}};
    Patient p5 = {"Edward",  {5, 5, 80}};

    // Insert into heap
    insertMax(&H, p1);
    insertMax(&H, p2);
    insertMax(&H, p3);
    insertMax(&H, p4);
    insertMax(&H, p5);

    // Display heap
    printf("=== Initial Heap ===\n");
    displayHeap(&H);

    // Remove highest priority
    printf("\n=== Next patient to treat ===\n");
    Patient next = deleteMax(&H);
    printf("%s (severity %d, age %d)\n",
           next.name, next.info.severity, next.info.age);

    // Increase severity of Charlie
    printf("\n=== Increasing Charlie's severity by +3 ===\n");
    increaseSeverity(&H, 2, 3);  // assuming index 2 is Charlie for now
    displayHeap(&H);
    maxHeapify(&H, 0);

    // Heap sort
    printf("\n=== Performing heap sort (descending priority) ===\n");
    heapSortPatients(&H);
    displayHeap(&H);

    return 0;
}


void initHeap(PatientMaxHeap* H) {

    H->last = -1;

}
bool isEmpty(PatientMaxHeap* H) {
    return H->last == -1;
}
bool isFull(PatientMaxHeap* H) {
    return H->last == MAXN-1;
}

// Heap operations
void swapPatient(Patient* a, Patient* b) {
    Patient temp = *a;
    *a = *b;
    *a = temp;
}

bool hasHigherPriority(Patient a, Patient b) {
    return a.info.severity > b.info.severity;
}

void insertMax(PatientMaxHeap* H, Patient x) {

    if (isFull(H)) return;

    H->last++;
    int child = H->last;
    int pr = (child-1)/2;


    while (child > 0 && H->heap[pr].info.severity < x.info.severity) {
        H->heap[child] = H->heap[pr];
        child = pr;
        pr=(child-1)/2; 
    }
    H->heap[child] = x;  
}
Patient deleteMax(PatientMaxHeap* H) {
    Patient swap, root;

    int child, pr;

    if (isEmpty(H)) exit(1);


    root = H->heap[0];
    H->heap[0] = H->heap[H->last];
    H->last--;


    pr = 0;
    child = 2 * pr +1;


    while (child <= H->last) {
        if (child+1 <= H->last && H->heap[child+1].info.severity > H->heap[child].info.severity) {
            child++;
        }

        if (H->heap[pr].info.severity < H->heap[child].info.severity) {
            swap = H->heap[pr];
            H->heap[pr] = H->heap[child];
            H->heap[child] = swap;

            pr = child;
            child = 2 * pr +1;
        } else {
            break;
        }
    }

    return root;
}
Patient peekMax(PatientMaxHeap* H) {
    return H->heap[0];
}
void maxHeapify(PatientMaxHeap* H, int index) {

    int pr = index;
    int child = pr * 2+1;

    while (child <= H->last) {
        if (child+1 <= H->last && H->heap[child+1].info.severity > H->heap[child].info.severity) {
            child++;
        }

        if (H->heap[pr].info.severity < H->heap[child].info.severity) {
            Patient swap  = H->heap[pr];
            H->heap[pr] = H->heap[child];
            H->heap[child] = swap;

            pr = child;
            child = 2 * pr +1;
        } else {
            break;
        }
    }

    
    

}

// Display & sorting
void displayHeap(PatientMaxHeap* H) {
    if (isEmpty(H)) {
        printf("[Heap is EMPTY]\n");
        return;
    }

    printf("Index | Name       | Severity | Arrival | Age\n");
    printf("-----------------------------------------------\n");
    for (int i = 0; i <= H->last; i++) {
        printf("%5d | %-10s | %8d | %7d | %3d\n",
               i,
               H->heap[i].name,
               H->heap[i].info.severity,
               H->heap[i].info.arrivalOrder,
               H->heap[i].info.age);
    }
}

void increaseSeverity(PatientMaxHeap* H, int index, int amount) {
   
     int child = index;
    int parent = (child-1)/2;

    Patient temp = H->heap[child];
    temp.info.severity+= amount;

    while (child > 0 && H->heap[parent].info.severity < temp.info.severity) {
        H->heap[child] = H->heap[parent];
        child = parent;
        parent = (child-1)/2;
    }
    H->heap[child] = temp;

}
void heapSortPatients(PatientMaxHeap* H) {

    int orig;
    Patient catcher;

    orig = H->last;
    
 

    // maxHeapify(H, 0);


   
    while (H->last != -1) {
        catcher = deleteMax(H);
        H->heap[H->last+1] = catcher;
    }
    H->last = orig;

}
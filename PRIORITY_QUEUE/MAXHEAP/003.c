
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 10

typedef struct {
    int severity;       // 1–10 (higher = more urgent)
    int arrivalOrder;   // smaller = came earlier
    int age;            // older gets priority if tie
} Condition;

typedef struct {
    char name[40];
    Condition info;
} Patient;


typedef struct {
    Patient heap[MAXN];
    int last;
} PatientMaxHeap;




void initHeap(PatientMaxHeap* H) {
    H->last = -1;

}
bool isEmpty(PatientMaxHeap* H) {
    return H->last == -1;

}
bool isFull(PatientMaxHeap* H) {
    return H->last == MAXN-1;
}

void swapPatient(Patient* a, Patient* b) {
    Patient p = *a;
    *a = *b;
    *b = p;
}

// Compare priority rules (severity → age → arrivalOrder)
bool hasHigherPriority(Patient a, Patient b);

void insertMax(PatientMaxHeap* H, Patient x);
Patient deleteMax(PatientMaxHeap* H);

void maxHeapify(PatientMaxHeap* H, int index);

void displayHeap(PatientMaxHeap* H);

// Additional Challenging Operations
Patient peekMax(PatientMaxHeap* H);          // view highest priority
void increaseSeverity(PatientMaxHeap* H, int index, int amount);
void heapSortPatients(PatientMaxHeap* H);    // descending by priority



int main() {
    PatientMaxHeap H;
    initHeap(&H);

    Patient p1 = {"Alice",   {8, 1, 45}};
    Patient p2 = {"Bob",     {10,2,60}};
    Patient p3 = {"Charlie", {10,3,20}};
    Patient p4 = {"Diana",   {7, 4,75}};
    Patient p5 = {"Edward",  {10,5,80}};  

    insertMax(&H, p1);
    insertMax(&H, p2);
    insertMax(&H, p3);
    insertMax(&H, p4);
    insertMax(&H, p5);

    printf("Heap display:\n");
    displayHeap(&H);

    printf("\nNext patient to treat:\n");
    Patient x = deleteMax(&H);
    printf("%s (severity %d)\n", x.name, x.info.severity);

    printf("\nIncreasing Charlie’s severity by +3...\n");
    increaseSeverity(&H, 2, 3);

    printf("\nHeap after update:\n");
    displayHeap(&H);

    printf("\nPerforming heap sort...\n");
    heapSortPatients(&H);
    displayHeap(&H);

    return 0;
}

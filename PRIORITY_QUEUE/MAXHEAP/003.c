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
    Patient p2 = {"Bob",     {10, 2, 60}};
    Patient p3 = {"Charlie", {10, 3, 20}};
    Patient p4 = {"Diana",   {7,  4, 75}};
    Patient p5 = {"Edward",  {10, 5, 80}};

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
    printf("\n=== Increasing Charlie’s severity by +3 ===\n");
    increaseSeverity(&H, 2, 3);  // assuming index 2 is Charlie for now
    displayHeap(&H);

    // Heap sort
    printf("\n=== Performing heap sort (descending priority) ===\n");
    heapSortPatients(&H);
    displayHeap(&H);

    return 0;
}

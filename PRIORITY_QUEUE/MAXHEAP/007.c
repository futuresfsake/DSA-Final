#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PATIENTS 50
#define NAME_LEN 50

/*
    Hospital Surgery Scheduling Queue (Max-Heap)

    Backstory:
    ----------------
    Patients waiting for surgery are scheduled based on urgency.
    Each patient has a Name, UrgencyScore (priority key), and SurgeryType.
    Higher UrgencyScore means the patient should go first.  

    All queue operations must be iterative for real-time scheduling.
*/

// ================================
// Patient Struct
// ================================
typedef struct {
    char name[NAME_LEN];
    int urgencyScore;       // higher = higher priority
    char surgeryType[NAME_LEN];
} Patient;

// ================================
// Max-Heap Struct
// ================================
typedef struct {
    Patient heap[MAX_PATIENTS];
    int size;               // last index used, initialize to -1
} SurgeryQueue;

// ================================
// Iterative Function Prototypes
// ================================

// 1. Initialize empty queue
void initSurgeryQueue(SurgeryQueue *sq) {
    sq->size = -1;
}

// 2. Check if queue is empty
bool isSurgeryQueueEmpty(SurgeryQueue *sq) {
    return sq->size == -1;
}

// 3. Insert a patient iteratively (bubble-up)
void enqueuePatient(SurgeryQueue *sq, Patient p) {
    int child, pr;

    if (sq->size == MAX_PATIENTS-1) return;

    sq->size++;
    child = sq->size;
    pr = (child-1)/2;

    while (child > 0 && sq->heap[pr].urgencyScore < p.urgencyScore) {
        sq->heap[child] = sq->heap[pr];
        child = pr;
        pr = (child-1)/2;
    }
    sq->heap[child] = p;
}

// 4. Extract the most urgent patient iteratively (bubble-down)
Patient dequeuePatient(SurgeryQueue *sq) {

    int child, pr;
    Patient root, swap;

    Patient emp = {"", -1, ""};

    if (sq->size == -1) return emp;

    root = sq->heap[0];
    sq->heap[0] = sq->heap[sq->size];
    sq->size--;

    pr = 0;
    child = 1;

    while (child <= sq->size) {
        if (child + 1 <= sq->size && sq->heap[child+1].urgencyScore > sq->heap[child].urgencyScore) {
            child++;
        }

        if (sq->heap[pr].urgencyScore < sq->heap[child].urgencyScore) {
            swap = sq->heap[pr];
            sq->heap[pr] = sq->heap[child];
            sq->heap[child] = swap;

            pr = child;
            child = (2 * pr )+1;
        } else {
            break;
        }
    }
    return root;
}

// 5. Peek at the most urgent patient
Patient peekTopPatient(SurgeryQueue *sq) {
    return sq->heap[0];
}

// 6. Heapify entire queue iteratively
void heapifySurgeryQueue(SurgeryQueue *sq) {
    int pr, down, child;
    Patient swap;

    if (sq->size == -1) return;

    pr = (sq->size-1)/2;

    while (pr >=0) {
        down = pr;
        child = (2 * down) +1;

        while (child <= sq->size) {
            if (child+1 <= sq->size && sq->heap[child+1].urgencyScore > sq->heap[child].urgencyScore) {
                child++;
            }

            if (sq->heap[pr].urgencyScore < sq->heap[child].urgencyScore) {
                swap = sq->heap[pr];
                sq->heap[pr] = sq->heap[child];
                sq->heap[child] = swap;

                down = child;
                child = (2 * down) +1;
                
            } else {
                break;
            }
        }
        pr--;
    }
}

// 7. Find a patient by name iteratively
bool findPatientByName(SurgeryQueue *sq, const char *name) {
    

    SurgeryQueue new;
    initSurgeryQueue(&new);
    bool found = false;

    while (sq->size != -1) {
        Patient test = dequeuePatient(sq);
        if (strcmp(test.name, name) == 0) {
            found = true;
            
            
        }
        enqueuePatient(&new, test);
    }

    while (new.size != -1) {
        Patient test = dequeuePatient(&new);
        enqueuePatient(sq, test);


    }
    return found;
}

// 8. Increase urgency of a patient (promote) iteratively
void promotePatient(SurgeryQueue *sq, const char *name, int newUrgency) {

    SurgeryQueue new;
    initSurgeryQueue(&new);

    while (sq->size != -1) {
        Patient p = dequeuePatient(sq);
        if (strcmp(p.name, name) == 0) {
            p.urgencyScore = newUrgency;
        }

        enqueuePatient(&new, p);
    }

    while (new.size != -1) {
        Patient p = dequeuePatient(&new);
        enqueuePatient(sq, p);
    }
    
}


// 10. Display all patients iteratively
void displaySurgeryQueue(SurgeryQueue *sq) {
    printf("\n--- Surgery Queue Status ---\n");
    
    if (sq->size == -1) {
        printf("Queue is empty.\n");
        return;
    }

    for (int i = 0; i <= sq->size; i++) {
        printf("Index %d: %s, Urgency: %d, Surgery: %s\n",
               i,
               sq->heap[i].name,
               sq->heap[i].urgencyScore,
               sq->heap[i].surgeryType);
    }
}


// 11. Count total patients iteratively
int totalPatients(SurgeryQueue *sq);

// 12. Clear queue iteratively
void clearSurgeryQueue(SurgeryQueue *sq);

// ================================
// MAIN (Sample Usage)
// ================================
int main() {
    SurgeryQueue sq;
    initSurgeryQueue(&sq);

    // Sample patients
    Patient p1 = {"Alice", 80, "Heart Surgery"};
    Patient p2 = {"Bob", 95, "Neurosurgery"};
    Patient p3 = {"Charlie", 70, "Orthopedic"};
    Patient p4 = {"Diana", 85, "Liver Transplant"};
    Patient p5 = {"Eve", 60, "Eye Surgery"};

    // Insert patients iteratively
    enqueuePatient(&sq, p1);
    enqueuePatient(&sq, p2);
    enqueuePatient(&sq, p3);
    enqueuePatient(&sq, p4);
    enqueuePatient(&sq, p5);

    // Display queue
    displaySurgeryQueue(&sq);

    // Extract most urgent patient
    Patient top = dequeuePatient(&sq);
    printf("\nPatient scheduled for surgery: %s, Urgency: %d, Surgery: %s\n", 
           top.name, top.urgencyScore, top.surgeryType);


             // Check if a patient exists
    const char *nameToFind = "Bob";
    if (findPatientByName(&sq, nameToFind)) {
        printf("%s is in the surgery queue.\n", nameToFind);
    } else {
        printf("%s is NOT in the surgery queue.\n", nameToFind);
    }

    // Another check
    nameToFind = "Diana";
    if (findPatientByName(&sq, nameToFind)) {
        printf("%s is in the surgery queue.\n", nameToFind);
    } else {
        printf("%s is NOT in the surgery queue.\n", nameToFind);
    }
    // Promote a patient
    promotePatient(&sq, "Eve",2 );

    // Display queue again
    displaySurgeryQueue(&sq);

    return 0;
}

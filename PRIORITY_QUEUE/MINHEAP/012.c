#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PATIENTS 10
#define NAME_LEN 50

/*
    ======================================================
        INTERSTELLAR MEDICAL BAY – PRIORITY QUEUE SYSTEM
    ------------------------------------------------------
    The medical bay treats patients based on priority level:
        - lower number = more urgent
    Implement all operations iteratively:
        - insert_patient
        - remove_highest_priority
        - update_priority
        - search_patient
        - display_queue
    ======================================================
*/

typedef struct {
    int patientID;
    char name[NAME_LEN];
    int priorityLevel;  // 1 = critical, 10 = minor
} Patient;

typedef struct {
    Patient queue[MAX_PATIENTS];
    int count;
} MedicalBayQueue;

// =================== PROTOTYPES ===================
void initQueue(MedicalBayQueue *mbq);
bool insertPatient(MedicalBayQueue *mbq, Patient p);
bool removeHighestPriority(MedicalBayQueue *mbq, Patient *removed);
int searchPatient(MedicalBayQueue *mbq, int patientID);
bool updatePriority(MedicalBayQueue *mbq, int patientID, int newPriority);
void displayQueue(MedicalBayQueue *mbq);


// =================== MAIN TESTER ===================
int main() {
    MedicalBayQueue mbq;
    initQueue(&mbq);

    Patient p1 = {201, "Lyra", 3};
    Patient p2 = {202, "Kael", 1};
    Patient p3 = {203, "Serin", 5};
    Patient p4 = {204, "Dorian", 2};
    Patient p5 = {205, "Astra", 4};

    insertPatient(&mbq, p1);
    insertPatient(&mbq, p2);
    insertPatient(&mbq, p3);
    insertPatient(&mbq, p4);
    insertPatient(&mbq, p5);

    printf("\n=== INITIAL QUEUE ===\n");
    displayQueue(&mbq);

    printf("\n=== REMOVE HIGHEST PRIORITY ===\n");
    Patient removed;
    removeHighestPriority(&mbq, &removed);
    printf("Removed Patient: %d (%s) Priority: %d\n",
           removed.patientID, removed.name, removed.priorityLevel);
    displayQueue(&mbq);

    // printf("\n=== UPDATE PRIORITY (Patient 203 -> Priority 1) ===\n");
    // updatePriority(&mbq, 203, 1);
    // displayQueue(&mbq);

    printf("\n=== SEARCH FOR Patient 204 ===\n");
    int idx = searchPatient(&mbq, 204);
    if (idx != -1) {
        printf("Found at index %d: %s Priority %d\n",
               idx, mbq.queue[idx].name, mbq.queue[idx].priorityLevel);
    } else {
        printf("Patient not found.\n");
    }

    return 0;
}


void initQueue(MedicalBayQueue *mbq) {
    mbq->count = -1;
}
bool insertPatient(MedicalBayQueue *mbq, Patient p) {

    int child, pr;
    if (mbq->count == MAX_PATIENTS-1) return false;

    mbq->count++;
    child = mbq->count;
    pr = (child-1)/2;

    while (child >0 && mbq->queue[pr].priorityLevel > p.priorityLevel) {
        mbq->queue[child] = mbq->queue[pr];
        child = pr;
        pr = (child-1)/2;
    }

    mbq->queue[child]=p;
    return true;
}
bool removeHighestPriority(MedicalBayQueue *mbq, Patient *removed) {
    int child, pr;
    
    if (mbq->count == -1) return false;

    *removed = (mbq->queue[0]);
    mbq->queue[0] = mbq->queue[mbq->count];
    mbq->count--;

    pr = 0;
    child = 2 * pr +1;

    while (child <= mbq->count) {
        if (child+1 <= mbq->count && mbq->queue[child+1].priorityLevel < mbq->queue[child].priorityLevel) {
            child++;
        }
        if (mbq->queue[pr].priorityLevel > mbq->queue[child].priorityLevel) {
            Patient p = mbq->queue[pr];
            mbq->queue[pr] = mbq->queue[child];
            mbq->queue[child] = p;

            pr = child;
            child = 2 * pr +1;
        } else {

        break;
        }
    }
}

int searchPatient(MedicalBayQueue *mbq, int patientID) {

    for(int i = 0; i <= mbq->count; i++) {
        if (mbq->queue[i].patientID == patientID) {
            return i;
        }
    }
    return -1;

}
// bool updatePriority(MedicalBayQueue *mbq, int patientID, int newPriority);
void displayQueue(MedicalBayQueue *mbq) {
    if (mbq->count == -1) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Index | PatientID | Name           | Priority\n");
    printf("------------------------------------------------\n");

    for (int i = 0; i <= mbq->count; i++) {
        printf("%5d | %9d | %-14s | %d\n",
               i,
               mbq->queue[i].patientID,
               mbq->queue[i].name,
               mbq->queue[i].priorityLevel);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 20
#define NAME_LEN 50

typedef struct {
    int patientID;
    char name[NAME_LEN];
    int severity;  // 1 = critical, 10 = minor
} Patient;

typedef struct {
    Patient patients[MAX_PATIENTS];
    int count;
} ERQueue;

// ================== PROTOTYPES ==================
void initQueue(ERQueue *eq);
void swap(Patient *a, Patient *b);
void heapifyUp(ERQueue *eq, int index);
void heapifyDown(ERQueue *eq, int index);
void addPatient(ERQueue *eq, Patient p);
void removeNextPatient(ERQueue *eq, Patient *p);
void updateSeverity(ERQueue *eq, int patientID, int newSeverity);
void displayQueue(ERQueue *eq);
void buildMinHeap(ERQueue *eq);
void heapSort(ERQueue *eq);

// ================== MAIN ==================
int main() {
    ERQueue eq;
    initQueue(&eq);

    Patient p1 = {101, "Alice", 5};
    Patient p2 = {102, "Bob", 2};
    Patient p3 = {103, "Charlie", 1};
    Patient p4 = {104, "Diana", 4};
    Patient p5 = {105, "Eve", 3};

    addPatient(&eq, p1);
    addPatient(&eq, p2);
    addPatient(&eq, p3);
    addPatient(&eq, p4);
    addPatient(&eq, p5);

    printf("\n=== CURRENT ER QUEUE ===\n");
    displayQueue(&eq);

    printf("\n=== NEXT PATIENT ===\n");
    printf("%d (%s) Severity: %d\n", eq.patients[0].patientID, eq.patients[0].name, eq.patients[0].severity);

    Patient removed;
    removeNextPatient(&eq, &removed);
    printf("\nRemoved patient: %d (%s) Severity: %d\n", removed.patientID, removed.name, removed.severity);

    printf("\n=== ER QUEUE AFTER REMOVAL ===\n");
    displayQueue(&eq);

    printf("\n=== UPDATE SEVERITY (Patient 104 -> Severity 1) ===\n");
    updateSeverity(&eq, 104, 1);
    displayQueue(&eq);

    printf("\n=== MINHEAPIFY / HEAPSORT QUEUE ===\n");
    heapSort(&eq);
    displayQueue(&eq);

    return 0;
}


void initQueue(ERQueue *eq) {
    eq->count = -1;
}
void swap(Patient *a, Patient *b) {
    Patient temp = *a;
    *a = *b;
    *b = temp;
}


void heapifyUp(ERQueue *eq, int index) {

    int child = index;
    int pr = (child-1)/2;


    while (child > 0 && eq->patients[pr].severity > eq->patients[child].severity) {
        Patient temp = eq->patients[pr];
        eq->patients[pr] = eq->patients[child];
        eq->patients[child]=temp;

        child = pr;
        pr = (child-1)/2;

    
    }
}
void heapifyDown(ERQueue *eq, int index) {


    int pr = index;
    int child = 2 * pr +1;

    while (child <= eq->count) {
        if (child+1 <= eq->count && eq->patients[child+1].severity < eq->patients[child].severity) {
            child++;
        }

        if (eq->patients[pr].severity > eq->patients[child].severity) {
            Patient swap = eq->patients[pr];
            eq->patients[pr] = eq->patients[child];
            eq->patients[child] = swap;


            pr = child;
            child = 2 * pr +1;
        } else {
            break;
        }
    }
}


void addPatient(ERQueue *eq, Patient p) {

    if (eq->count == MAX_PATIENTS-1) return;
    int child, pr;

    eq->count++;
    child = eq->count;
    pr = (child-1)/2;

    while (child > 0 && eq->patients[pr].severity > p.severity) {
        eq->patients[child]= eq->patients[pr];
        child = pr;
        pr = (child-1)/2;
    }

    eq->patients[child] = p;
}

void removeNextPatient(ERQueue *eq, Patient *p) {
    if (eq->count == -1) return;


    *p = eq->patients[0];
    eq->patients[0] = eq->patients[eq->count];
    eq->count--;


    int pr = 0;
    int child = 2 * pr+1;

    while (child <= eq->count) {
        if (child+1 <= eq->count && eq->patients[child+1].severity < eq->patients[child].severity) {
            child++;
        }

        if (eq->patients[pr].severity > eq->patients[child].severity) {
            Patient swap = eq->patients[pr];
            eq->patients[pr] = eq->patients[child];
            eq->patients[child] = swap;

            pr = child;
            child = 2 * pr+1;
        } else {
            break;
        }
    }
}


void updateSeverity(ERQueue *eq, int patientID, int newSeverity) {

    for(int i = 0; i <= eq->count; i++) {
        if (eq->patients[i].patientID == patientID) {
            eq->patients[i].severity = newSeverity;

            buildMinHeap(eq);

        }
    }

}
void displayQueue(ERQueue *eq) {
    if (eq->count == -1) {
        printf("<empty>\n");
        return;
    }

    printf("ER Queue (Heap Order):\n");
    for (int i = 0; i <= eq->count; i++) {
        printf("[ID:%d Name:%s Severity:%d]  \n", 
               eq->patients[i].patientID, 
               eq->patients[i].name, 
               eq->patients[i].severity);
    }
    printf("\n");
}

void buildMinHeap(ERQueue *eq) {

    int pr = (eq->count-1)/2;

    while (pr >= 0) {
        int down = pr;
        int child = 2 * down +1;

        while (child <= eq->count) {
            if(child+1 <= eq->count && eq->patients[child+1].severity < eq->patients[child].severity) {
                child++;
            }

            if (eq->patients[down].severity > eq->patients[child].severity) {
                Patient temp = eq->patients[down];
                eq->patients[down] = eq->patients[child];
                eq->patients[child] = temp;

                down = child;
                child = 2 * down +1;
            } else {
                break;
            }
        }
        pr--;
    }

}
void heapSort(ERQueue *eq) {

    int orig;
    Patient catcher;


    orig = eq->count;
    eq->count = -1;

    for(int i = 0; i <= orig; i++) {
        addPatient(eq, eq->patients[i]);
    }

    for(int i = orig; i >= 0; i--) {
        removeNextPatient(eq, &catcher);
        eq->patients[i] = catcher;
    }


    eq->count = orig;

}
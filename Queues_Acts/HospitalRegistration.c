#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_QUEUE 100

// ===== Nested Structs =====
typedef struct {
    int recordID;
    char bloodType[5];
} MedicalRecord;

typedef struct {
    char firstName[50];
    char lastName[50];
    MedicalRecord record;
} Patient;

// ===== Queue ArrayList =====
typedef struct {
    Patient patients[MAX_QUEUE];
    int front;
    int rear;
    int count;
} PatientQueue;

// ===== Basic Queue Operations =====
void initQueue(PatientQueue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

bool isEmptyQueue(PatientQueue *q) {
    return q->count == 0;
}

bool isFullQueue(PatientQueue *q) {
    return q->count == MAX_QUEUE;
}

bool enqueue(PatientQueue *q, Patient p) {
    if (isFullQueue(q)) return false;
    q->rear = (q->rear + 1) % MAX_QUEUE;
    q->patients[q->rear] = p;
    q->count++;
    return true;
}

Patient dequeue(PatientQueue *q) {
    Patient p;
    if (isEmptyQueue(q)) exit(1);
    p = q->patients[q->front];
    q->front = (q->front + 1) % MAX_QUEUE;
    q->count--;
    return p;
}

void displayQueue(PatientQueue *q) {
    if (isEmptyQueue(q)) {
        printf("No patients in the queue.\n");
        return;
    }
    int i = q->front;
    for (int cnt = 0; cnt < q->count; cnt++) {
        Patient p = q->patients[i];
        printf("Patient: %s %s | RecordID: %d | Blood Type: %s\n",
               p.firstName, p.lastName, p.record.recordID, p.record.bloodType);
        i = (i + 1) % MAX_QUEUE;
    }
}

// ===== Special Operations (Leave for user) =====
void searchPatientQueue(PatientQueue *q, int recordID) {
   int found = -1;
   
   Patient temp;

   for(int i = 0; i < q->count; i++) {
     temp = dequeue(q);

     if (temp.record.recordID == recordID) {
        found = 1;
        printf("%d is existing", recordID);
        

       
     } 
     enqueue(q, temp);
   }

 
   if (found == -1) {
    printf("%d is not found.\n", recordID);
     
   }
}
    

// find a patient by record ID
void updateBloodTypeQueue(PatientQueue *q, int recordID, char *newBloodType) {

    Patient temp;
   int found = 0; 
    for(int i = 0; i < q->count; i++) {

        temp = dequeue(q);
        if (temp.record.recordID == recordID) {
            strcpy(temp.record.bloodType, newBloodType);
            found = 1;
        }
        enqueue(q, temp);
    }

    if (!found) {
        printf("ID: %d is not existing..\n", recordID);
    }

} // update blood type



int main() {
    PatientQueue q;
    initQueue(&q);

    // Sample patients
    Patient p1 = {"Alice", "Smith", {101, "A+"}};
    Patient p2 = {"Bob", "Johnson", {102, "B-"}};
    Patient p3 = {"Charlie", "Brown", {103, "O+"}};

    // Enqueue patients
    enqueue(&q, p1);
    enqueue(&q, p2);
    enqueue(&q, p3);

    // Display initial queue
    printf("=== Initial Patient Queue ===\n");
    displayQueue(&q);

    // Try searching for a record
    printf("\n=== Searching for RecordID 102 ===\n");
    searchPatientQueue(&q, 43);

    // Try updating blood type
    printf("\n=== Updating Blood Type for RecordID 103 ===\n");
    updateBloodTypeQueue(&q, 103, "AB+");

    // Display queue after update
    printf("\n=== Updated Patient Queue ===\n");
    displayQueue(&q);

    return 0;
}

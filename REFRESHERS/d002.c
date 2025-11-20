// * Hospital Patient Management System (Dictionary - Hash Table)

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 10

// ===============================
//          STRUCTS
// ===============================

typedef struct {
    int id;
    char name[100];
    char specialization[50];
} Doctor;

typedef struct {
    int day;
    int month;
    int year;
} AdmissionDate;

typedef struct {
    int patientID;
    char name[100];
    char illness[50];
    AdmissionDate admitDate;
    float billAmount;
    Doctor attendingDoctor;
} Patient;

typedef struct node {
    Patient patient;
    struct node* next;
} PatientType, *PatientPtr;

// ===============================
//     DICTIONARY DEFINITION
// ===============================

// Dictionary is an array of PatientPtr (linked-list heads)
typedef PatientPtr DICTIONARY[MAX];


// ===============================
//     FUNCTION DECLARATIONS
// ===============================

// Initialization
void initDictionary(DICTIONARY dict) {
    for (int i = 0; i < MAX; i++) {
        dict[i] = NULL;
    }
}
void MakeNull(DICTIONARY* dict) {
    for(int i = 0; i < MAX; i++) {
        *dict[i] = NULL;
    }


}

// Hashing
int HashFunction(char doctorName[]) {
    int sum = 0;

    for(int i = 0; i < 5 && doctorName[i] != '\0'; i++) {
        sum += doctorName[i];
    }
    return sum%MAX;
}

// Core operations
void Insert(DICTIONARY* dict, Patient P) {

    bool found = 0;

    int h = HashFunction(P.attendingDoctor.name);

    PatientPtr trav = (*dict)[h];

    for(; trav != NULL; trav = trav->next ) {
        if (trav->patient.patientID== P.patientID) {
            found = true;break;
        }
    }


    if (!found) {
        PatientPtr new = malloc(sizeof(PatientType));
        if (!new) {
            printf("Dynamic memory allocation failed!\n");
        }

        new->patient = P;
        new->next = (*dict)[h];
        (*dict)[h] = new;
    }
}
bool Remove(DICTIONARY* dict, int id, char doctorName[]) {

    int index = HashFunction(doctorName);


    PatientPtr* trav = &(*dict)[index];

    for(; *trav != NULL; trav = &(*trav)->next) {
        if (strcmp((*trav)->patient.attendingDoctor.name, doctorName) ==0 && (*trav)->patient.patientID == id) {
            PatientPtr Remove = *trav;
            *trav = Remove->next;
            free(Remove);
            return true; 
        }
    }
    return false;
}
bool IsMember(DICTIONARY* dict, int id, char doctorName[]) {
 bool found = 0;

    int h = HashFunction(doctorName);

    PatientPtr trav = (*dict)[h];

    for(; trav != NULL; trav = trav->next ) {
        if (trav->patient.patientID== id && strcmp((trav)->patient.attendingDoctor.name, doctorName) ==0)  {
            return true;
        }
    }

    return false;

    
}
void Display(DICTIONARY dict) {

    for (int i = 0; i < MAX; i++) {

        printf("INDEX [%d] -> ", i);

        PatientPtr temp = dict[i];

        if (temp == NULL) {
            printf("EMPTY\n");
            continue;
        }

        while (temp != NULL) {
            printf("{ID: %d | Patient: %s | Doctor: %s} -> ",
                   temp->patient.patientID,
                   temp->patient.name,
                   temp->patient.attendingDoctor.name);

            temp = temp->next;
        }

        printf("NULL\n");  // End of chain
    }
}




// // Special operations
// void DisplayByDoctor(DICTIONARY dict, char doctorName[]);
// float ComputeTotalBillsByDoctor(DICTIONARY dict, char doctorName[]);


// ===============================
//            MAIN
// ===============================

int main() {
    DICTIONARY dict;
    initDictionary(dict);

    // Sample Patients (same as your original example)
    Patient patients[6] = {
        {1001, "Carlos Dela Cruz", "Fever", {10,10,2025}, 1500.00, {201, "Dr. Ana Cruz", "General Medicine"}},
        {1002, "Maria Santos", "Fracture", {11,10,2025}, 8500.00, {202, "Dr. Ben Ramos", "Orthopedic"}},
        {1003, "Juan Dela Rosa", "Cough", {9,10,2025}, 1200.00, {201, "Dr. Ana Cruz", "General Medicine"}},
        {1004, "Jose Lim", "Migraine", {8,10,2025}, 3200.00, {203, "Dr. Carla Tan", "Neurology"}},
        {1005, "Karla Bautista", "Asthma", {7,10,2025}, 6000.00, {201, "Dr. Gian Lax", "General Medicine"}},
        {1006, "Dan Rivera", "Bone Fracture", {6,10,2025}, 9400.00, {202, "Dr. Gian Lax", "Orthopedic"}}
    };

    // Insert all sample patients
    for (int i = 0; i < 6; i++) {
        Insert(&dict, patients[i]);
    }

    printf("\n=== INITIAL DISPLAY ===\n");
    Display(dict);

    printf("\n=== REMOVE PATIENT ===\n");
    bool res = Remove(&dict, 1005, "Dr. Gian Lax");
    if (res)
        printf("Patient removed successfully.\n");
    else
        printf("Patient not found.\n");

    printf("\n=== AFTER REMOVAL ===\n");
    Display(dict);

    printf("\n=== CHECK ISMEMBER ===\n");
    if (IsMember(&dict, 1002, "Dr. Ben Ramos"))
        printf("Patient found in List.\n");
    else
        printf("Patient not found.\n");

    
    return 0;
}

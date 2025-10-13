// * Hospital Patient Management System

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>



#define MAX 10


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

// * PatientType is a struct node
// * PatienrPtr is a struct node*

typedef PatientPtr DICTIONARY[MAX];
//* DICTIONARY IS an array of a struct node *
// ! DICTIONARY *dict is an pointer to an array of struct node *




void initDictionary(DICTIONARY dict);
int HashFunction(char doctorName[]);
void MakeNull(DICTIONARY* dict);
void Insert(DICTIONARY* dict, Patient P);
bool Remove(DICTIONARY* dict, int id, char doctorName[]);
bool IsMember(DICTIONARY* dict, int id, char doctorName[]);
void Display(DICTIONARY dict);

// // Special operations
void DisplayByDoctor(DICTIONARY dict, char doctorName[]);
float ComputeTotalBillsByDoctor(DICTIONARY dict, char doctorName[]);


int main() {
    DICTIONARY dict;
    initDictionary(dict);

    Patient patients[6] = {
        {1001, "Carlos Dela Cruz", "Fever", {10,10,2025}, 1500.00, {201, "Dr. Ana Cruz", "General Medicine"}},
        {1002, "Maria Santos", "Fracture", {11,10,2025}, 8500.00, {202, "Dr. Ben Ramos", "Orthopedic"}},
        {1003, "Juan Dela Rosa", "Cough", {9,10,2025}, 1200.00, {201, "Dr. Ana Cruz", "General Medicine"}},
        {1004, "Jose Lim", "Migraine", {8,10,2025}, 3200.00, {203, "Dr. Carla Tan", "Neurology"}},
        {1005, "Karla Bautista", "Asthma", {7,10,2025}, 6000.00, {201, "Dr. Gian Lax", "General Medicine"}},
        {1006, "Dan Rivera", "Bone Fracture", {6,10,2025}, 9400.00, {202, "Dr. Gian Lax", "Orthopedic"}}
    };

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

    printf("\n=== DISPLAY BY DOCTOR (Dr. Ana Cruz) ===\n");
    DisplayByDoctor(dict, "Dr. Ana Cruz");

    printf("\n=== COMPUTE TOTAL BILLS (Dr. Gian Lax) ===\n");
    float total = ComputeTotalBillsByDoctor(dict, "Dr. Gian Lax");
    printf("Total bills under Dr. Gian Lax: P%.2f\n", total);

    return 0;
}


// TODO : it is working
void initDictionary(DICTIONARY dict) {
    for(int i = 0; i < MAX; i++) {
        dict[i]= NULL;
    }
}


// ! a hash function that maps a 
// ! patient to a dictionary index based on the doctor's name
// ! all patients witht the same doctor are grouped in the same bucket


// int HashFunction( char doctorName[]) {
//     int doc = 0;

//     for(int i = 0; doctorName[i] != '\0'; i++) {
//         doc+=doctorName[i];
//     } 

//     int docName = strlen(doctorName);

//     return (doc*docName) % MAX;


// }

// ! this is a bad hash, does not fulfill the purpose,
// ! as there could be some instances where the sum of all the ascii characters are the same


int HashFunction(char doctorName[]) {
    unsigned int hash = 0;
    for (int i = 0; doctorName[i] != '\0'; i++) {
        hash = (hash * 31 + doctorName[i]);
    }
    return hash % MAX;
}

// ! hash * 31 + doctorName[i] == is the standard way to compute a hash string
// ! so hash gets updated as it is iterated depends on the number of characters?



void MakeNull(DICTIONARY* dict){ 
    for (int i = 0; i < MAX; i++) {
        (*dict)[i] = NULL;
    }
}


// ! insert head
void Insert(DICTIONARY* dict, Patient P) {

    if (IsMember(dict,P.patientID, P.attendingDoctor.name)) {
       printf("Unique Patient ID only...\n");
       return;
    }

    int index = HashFunction( P.attendingDoctor.name);

    PatientPtr newPatient = malloc(sizeof(PatientType));
    if (!newPatient) {
        printf("Dynamic Memory Allocation failed.\n");
        return;
    }

    newPatient->patient = P;
    newPatient->next = (*dict)[index];
    (*dict)[index] = newPatient;

}


// TODO dict is a pointer to the array of PatientPtr s
// TODO *dict is the actual array -> the actual bucket
// TODO &(*dict)[index] -> the pointer to bucket, the actual head




bool Remove(DICTIONARY* dict, int id, char doctorName[]) {

    int index = HashFunction(doctorName);
    PatientPtr* temp = &(*dict)[index];
    // * *temp is the actual head pointer
    // ! dict is a pointer eto the array *DICTIONARY
    // ! you need to dereference it
    for(; *temp != NULL; temp = &(*temp)->next) {
        if ((*temp)->patient.patientID == id && strcmp((*temp)->patient.attendingDoctor.name,  doctorName)==0) {
            PatientPtr toRemove = *temp;
            *temp = toRemove->next;
            free(toRemove);
            printf("Patint: %d under Dr. %s discharging...\n", id, doctorName);
            return true;


        }
    }

    return false;
}



bool IsMember(DICTIONARY* dict, int id, char doctorName[]) {

    // ! Check the member

    

    int index = HashFunction(doctorName);

    PatientPtr temp = (*dict)[index];

    while (temp != NULL) {
        if (temp->patient.patientID == id && strcmp((temp)->patient.attendingDoctor.name, doctorName)==0) {
            return true;
        }
        temp = temp->next;
    }
    return false;
    
}



void Display(DICTIONARY dict) {

    for(int i = 0; i < MAX; i++) {
        printf("INDEX [%d] -> ", i);

        PatientPtr temp = dict[i];


        if (temp == NULL) {
            printf("EMPTY\n");
        }


        while(temp != NULL) {
            printf(" {ID: %d || Attending Doctor: %s} ->", temp->patient.patientID, temp->patient.attendingDoctor.name);      

           
            if (temp->next == NULL) {
                printf(" NULL\n");
            }

             temp = temp->next;
        }
        
    }
}

// // Special operations
void DisplayByDoctor(DICTIONARY dict, char doctorName[]) {
    int index = HashFunction(doctorName);

    PatientPtr temp = (dict)[index];
    if (temp == NULL) {
        printf("List empty...\n");
    }

    while (temp != NULL) {
        printf("ID: %d || Patient : %s\n", temp->patient.patientID, temp->patient.name);
        temp = temp->next;


    }

    
}



float ComputeTotalBillsByDoctor(DICTIONARY dict, char doctorName[]) {

    
    int index = HashFunction(doctorName);
    float bills = 0;


    PatientPtr temp = dict[index];

    if (temp == NULL) {
        printf("Doctor not existing...\n");
        exit(1);
    }

    while (temp != NULL)  {
        bills += temp->patient.billAmount;
        temp = temp->next;
    }
    return bills;
}

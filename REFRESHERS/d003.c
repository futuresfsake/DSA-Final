#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>



#define MAX 15

typedef struct {
    char courseCode[20];   // ex: "CS101", "IT222", "ENG123"
    int units;
} Course;

typedef struct {
    int studentID;
    char name[50];
    Course course;
} Student;

typedef struct node {
    Student stud;
    struct node* next;
} Node, *NodePtr;

// Dictionary = array of linked list heads
typedef NodePtr DICTIONARY[MAX];


void initDictionary(DICTIONARY D);
int Hash(char courseCode[]);
void Insert(DICTIONARY D, Student S);
bool Remove(DICTIONARY D, int id, char courseCode[]);
bool IsMember(DICTIONARY D, int id, char courseCode[]);
void Display(DICTIONARY D);


int main() {

    DICTIONARY D;
    initDictionary(D);

    Student S[6] = {
        {101, "Alice Reyes", {"CS101", 3}},
        {102, "Mark Dizon", {"CS101", 3}},
        {103, "Jenna Cruz", {"IT222", 4}},
        {104, "Leo Santos", {"ENG123", 3}},
        {105, "Maria Chan", {"IT222", 4}},
        {106, "Paolo King", {"HUM110", 2}}
    };

    // Insert
    for (int i = 0; i < 6; i++) {
        Insert(D, S[i]);
    }

    printf("\n=== INITIAL DICTIONARY ===\n");
    Display(D);

    // Remove
    printf("\n=== REMOVE STUDENT 105 (IT222) ===\n");
    if (Remove(D, 105, "IT222"))
        printf("Removed successfully.\n");
    else
        printf("Not found.\n");

    printf("\n=== AFTER REMOVAL ===\n");
    Display(D);

    // Membership
    printf("\n=== CHECK STUDENT 101 (CS101) ===\n");
    if (IsMember(D, 101, "CS101"))
        printf("Student is enrolled.\n");
    else
        printf("Student not found.\n");

  
    return 0;
}


void initDictionary(DICTIONARY D) {
    for(int i = 0; i < MAX; i++) {
        D[i] = NULL;
    }
}
int Hash(char courseCode[]) {
    int sum = 0;
    for(int i = 0; i < 5 && courseCode[i] != '\0'; i++) {
        sum+= courseCode[i];

    }
    return sum % MAX;
}
void Insert(DICTIONARY D, Student S) {
    int index = Hash(S.course.courseCode);

    NodePtr trav = D[index];

    bool found = false;
    for(; trav != NULL; trav = trav->next) {
        if (trav->stud.studentID == S.studentID) {
            found = true;
            break;
        }
    }

    if (!found) {
        NodePtr new = malloc(sizeof(Node));
        new->stud = S;
        new->next = D[index];
        D[index]= new;
    }
    
}
bool Remove(DICTIONARY D, int id, char courseCode[]) {

    int index = Hash(courseCode);

    NodePtr* trav = &(D)[index];

    for(; *trav != NULL; trav = &(*trav)->next) {
        if ((*trav)->stud.studentID == id) {
            NodePtr Remove = *trav;
            (*trav)->next = Remove->next;
            free(Remove);
            return true;
        }
    }
    return false;
}
bool IsMember(DICTIONARY D, int id, char courseCode[]) {
    
    int index = Hash(courseCode);

    NodePtr trav = D[index];
    while (trav) {
        if (trav->stud.studentID == id) {
            return true;
        }
        trav = trav->next;
    }
    return false;
}
void Display(DICTIONARY D) {
    printf("\n===== DICTIONARY CONTENTS =====\n");

    for (int i = 0; i < MAX; i++) {
        printf("\nBucket %d:\n", i);

        if (D[i] == NULL) {
            printf("  [EMPTY]\n");
        } else {
            NodePtr trav = D[i];
            while (trav != NULL) {
                printf("  ID: %d | Name: %s | Course: %s | Units: %d\n",
                    trav->stud.studentID,
                    trav->stud.name,
                    trav->stud.course.courseCode,
                    trav->stud.course.units
                );
                trav = trav->next;
            }
        }
    }
}

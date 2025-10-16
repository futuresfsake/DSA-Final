// * University Course Enrollment System
// ! assumes that all the sets are unsorted
// ! all of my UIDS are unsorted implementation
// ! assumes that the sets contains no duplictes


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Node {
    int studentID;
    struct Node *next;
} Node;

typedef Node* Set;



void insertStudent(Set *A, int studentID);
void deleteStudent(Set *A, int studentID);
void displaySet(Set A);

Set unionSet(Set A, Set B);
Set intersectionSet(Set A, Set B);
Set differenceSet(Set A, Set B);

bool isMember(Set A, int studentID);



int main() {
    Set math = NULL;
    Set science = NULL;

    // Insert students
    insertStudent(&math, 101);
    insertStudent(&math, 102);
    insertStudent(&math, 103);
    insertStudent(&math, 109);

    insertStudent(&science, 102);
    insertStudent(&science, 103);
    insertStudent(&science, 105);

    printf("Math Students: ");
    displaySet(math);

    printf("Science Students: ");
    displaySet(science);

    // Check for membership 
    printf("Is 109 existing? ");
    bool res = isMember(math, 109);
        if (res) {
            printf("YES..\n");
        } else {
            printf("NO\n");
        }

    Set allStudents = unionSet(math, science);
    printf("\nUnion (All Students): ");
    displaySet(allStudents);

    Set common = intersectionSet(math, science);
    printf("Intersection (Both Courses): ");
    displaySet(common);

    Set diff = differenceSet(math, science);
    printf("Difference (Both Courses): ");
    displaySet(diff);

    printf("\nDeleting student 103 from Math...\n");
    deleteStudent(&math, 103);
    printf("Math after deletion: ");
    displaySet(math);

    return 0;
}

void insertStudent(Set *A, int studentID) {

    Set *trav = A;

    bool found = false;

    for(; *trav != NULL; trav = &(*trav)->next) {
        if ((*trav)->studentID == studentID) {
            found = true;
            printf("%d already exists! Duplicates not allowed!\n", studentID);
            return;
        }
    }

    if (!found) {
        Node* newStud = malloc(sizeof(Node));
        newStud->studentID = studentID;
        newStud->next = *A;
        *A = newStud;
    }


   
}


void deleteStudent(Set *A, int studentID) {

    Set* trav = A;
    for(; *trav != NULL; trav = &(*trav)->next) {
        if ((*trav)->studentID == studentID) {
            Node* temp = *trav;
            *trav = temp->next;
         printf("%d found. deleting...\n", temp->studentID);

            free(temp);
            return;

        }
    }

    printf("%d not existing...\n", studentID);
   
}


void displaySet(Set A) {
    printf("{ ");
    for (Node *curr = A; curr != NULL; curr = curr->next) {
        printf("%d -> ", curr->studentID);
    }
    printf(" NULL}\n");
}


bool isMember(Set A, int studentID) {
    Node* trav = A;

    for(; trav != NULL; trav = trav->next) {
        if (trav->studentID == studentID) {
            return true;
        }
    }
    return false;
}

// !  union unsorted
Set unionSet(Set A, Set B) {
   
    Set C = NULL;
    Set tail = NULL;

    Node* pa = A;
    Node* pb = B;


    while (pa) {
        int v = pa->studentID;
        bool inC = false;
        Set trav = C;

        for(; trav != NULL; trav = trav->next) {
            if (trav->studentID == v) {
                inC = true; break;
            }
        }


        if (!inC) {
            Node* newNode = malloc(sizeof(Node));
            newNode->studentID = v;
            newNode->next = NULL;

            if (C == NULL) {
                C = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }
        pa = pa->next;
    }


    while (pb) {
        bool inC = false;
        int v = pb->studentID;


        Set trav = C;

        for(; trav != NULL; trav = trav->next){
            if (trav->studentID == v) {
                inC = true;
                break;
            }
        }

        if (!inC) {
            Node* new = malloc(sizeof(Node));
            new->studentID = v;
            new->next = NULL;
            if (C == NULL) {
                C = new;
                tail = new;
            } else {
                tail->next = new;
                tail = new;
            }
        }
        pb = pb->next;
    }

    return C;
}


Set intersectionSet(Set A, Set B) {
    
Set C = NULL;
Set tail = NULL;

Node* pa = A;



while (pa) {
    int v = pa->studentID;
    
    Node* pb = B;
    bool inB = false;
    for(; pb != NULL; pb = pb->next) {
        if (pb->studentID == v) {
            inB = true;
            break;
        }
    }


    if (inB) { // ! if inB, it means they are the same, so try to store it
        bool inC = false;
        Node* trav = C;

        for(; trav != NULL; trav = trav->next) {
            if (trav->studentID == v) {
                inC = true;
                break;
            }

        }
        
    

    if (!inC) {
        Node* temp = malloc(sizeof(Node));
        temp->studentID = v;
        temp->next = NULL;

        if (C == NULL) {
            C = temp;
            tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }

        

         }

     }
     pa = pa->next;

}

return C;

}
   
Set differenceSet(Set A, Set B) {
      
Set C = NULL;
Set tail = NULL;

Node* pa = A;



while (pa) {
    int v = pa->studentID;
    
    Node* pb = B;
    bool inB = false;
    for(; pb != NULL; pb = pb->next) {
        if (pb->studentID == v) {
            inB = true;
            break;
        }
    }


    if (!inB) { // ! if inB, it means they are the same, so try to store it
        bool inC = false;
        Node* trav = C;

        for(; trav != NULL; trav = trav->next) {
            if (trav->studentID == v) {
                inC = true;
                break;
            }

        }
        
    

    if (!inC) {
        Node* temp = malloc(sizeof(Node));
        temp->studentID = v;
        temp->next = NULL;

        if (C == NULL) {
            C = temp;
            tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }

        

         }

     }
     pa = pa->next;

}

return C;

    


}
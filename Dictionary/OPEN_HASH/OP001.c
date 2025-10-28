/************************************************************
 🧠 OPEN HASHING (SEPARATE CHAINING) — STRING DICTIONARY
*************************************************************
📘 CONTEXT:
Implement a Dictionary using **Open Hashing** with **linked lists**.
Each node stores:
   - UID (int)
   - name (string)

Support operations:
  ✅ insert()
  ✅ search()
  ✅ delete()
  ✅ display()
  ✅ set operations: union, intersection, difference, symmetric difference
*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10
#define NAME_LEN 50

// ===============================
// 🔹 STRUCT DEFINITIONS
// ===============================
typedef struct Node {
    int UID;
    char name[NAME_LEN];
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} Bucket;

typedef struct {
    Bucket table[MAX];
} Dictionary;

// ===============================
// 🔹 FUNCTION DECLARATIONS
// ===============================
int hash(int UID) {
    return (UID) % MAX;
}


void initDictionary(Dictionary *d) {
    for(int i = 0; i < MAX; i++) {
        d->table[i].head = NULL;

    }

}


bool insert(Dictionary *d, int UID, const char *name) {

    int h = hash(UID);

        Node* trav = d->table[h].head;

        for(; trav != NULL; trav = trav->next) {
            if (trav->UID == UID) {
                return false;
            }

        }

        Node* new = malloc(sizeof(Node));
        strcpy(new->name, name);
        new->UID = UID;
        new->next = d->table[h].head;
        d->table[h].head = new;
        return true;

}


// bool search(Dictionary *d, int UID, char *result) {}
bool delete(Dictionary *d, int UID) {

    int h = hash(UID);

    Node** trav = &(d->table[h].head);

    for(; *trav != NULL; trav = &(*trav)->next) {
        if ((*trav)->UID == UID) {
            Node* toRemove = *trav;
            *trav = toRemove->next;
            free(toRemove);
            return true;
        }
    }
    return false;
}

void display(Dictionary *d) {
    for(int i = 0; i < MAX; i++) {
        printf("%d.->", i);

        Node* trav = d->table[i].head;

        if (trav == NULL) {
            printf("EMPTY\n");
        } else {
            while (trav != NULL) {
                printf("[%s, %d]->", trav->name, trav->UID);
                trav = trav->next;
            }

            printf("NULL\n");
        }


    }
}

// // --- Set operations ---
Dictionary unionDict(Dictionary *A, Dictionary *B) {

    Dictionary C;
    initDictionary(&C);

    for(int i = 0; i < MAX; i++) {
        Node* ptrA = A->table[i].head;
        
        while (ptrA) {

            unsigned int h = hash(ptrA->UID);
            bool inC = false;

            for(Node* trav = C.table[h].head; trav != NULL; trav = trav->next) {
                if (trav->UID == ptrA->UID) {
                    inC = true;
                    break;
                }
            }

            if (!inC) {
                Node* new = malloc(sizeof(Node));
                strcpy(new->name, ptrA->name);
                new->UID = ptrA->UID;
                new->next = C.table[h].head;
                C.table[h].head = new;
                
            }
            ptrA = ptrA->next;
        }
    }

    for(int j = 0; j < MAX; j++) {
        Node* ptrB = B->table[j].head;
        bool inC = false;
        

        while (ptrB) {
 bool inC = false;
        
            unsigned int h = hash(ptrB->UID);
            Node* travC = C.table[h].head;
            for(; travC != NULL; travC = travC->next) {
                if (travC->UID == ptrB->UID) {
                    inC = true;
                    break;
                }
            }

            if (!inC) {
                Node* new = malloc(sizeof(Node));
                strcpy(new->name, ptrB->name);
                new->UID = ptrB->UID;
                new->next = C.table[h].head;
                C.table[h].head = new;
            }
            


            ptrB = ptrB->next;
        }

   
}
 return C;


}
Dictionary intersectionDict(Dictionary *A, Dictionary *B) {
    Dictionary C;
    initDictionary(&C);

    for(int i = 0; i < MAX; i++) {
        Node* ptrA = A->table[i].head;
        

        while (ptrA) {
            bool inB = false;
            unsigned int h = hash(ptrA->UID);

            Node* ptrB = B->table[h].head;
            for(; ptrB != NULL; ptrB = ptrB->next) {
                if (ptrB->UID == ptrA->UID) {
                    inB = true;
                    break;
                }
            }

            if (inB) {
                
                bool inC = false;
                Node* travC = C.table[h].head;
                for(; travC != NULL; travC = travC->next) {
                    if (travC->UID == ptrA->UID) {
                        inC = true;
                        break;
                    }
                }


                if (!inC) {
                    Node* new = malloc(sizeof(Node));
                    strcpy(new->name, ptrA->name);
                    new->UID = ptrA->UID;
                    new->next = C.table[h].head;
                    C.table[h].head = new;
                }
            }

            ptrA = ptrA->next;
        }
    }

    return C;
}
Dictionary differenceDict(Dictionary *A, Dictionary *B) {
    Dictionary C;
    initDictionary(&C);

    for(int i = 0; i < MAX; i++) {
        
        Node* ptrA = A->table[i].head;

        while (ptrA) {
bool inB = false;
            unsigned int index = hash(ptrA->UID);
            Node* ptrB = B->table[index].head;
            for(; ptrB != NULL; ptrB = ptrB->next) {
                if (ptrB->UID == ptrA->UID) {
                    inB= true;
                    break;
                }
            }

            if (!inB) {

                bool inC = false;
                Node* ptrC = C.table[index].head;
                for(; ptrC != NULL; ptrC = ptrC->next) {
                    if (ptrC->UID == ptrA->UID) {
                        inC = true;
                        break;
                    }
                }

                if (!inC) {
                    Node* new = malloc(sizeof(Node));
                    strcpy(new->name, ptrA->name);
                    new->UID = ptrA->UID;
                    new->next = C.table[index].head;
                    C.table[index].head = new;
                }

            }
            ptrA = ptrA->next;
        }
    }

    return C;
}
Dictionary symmetricDiffDict(Dictionary *A, Dictionary *B) {

    Dictionary C;
    initDictionary(&C);

     for(int i = 0; i < MAX; i++) {
        
        Node* ptrA = A->table[i].head;

        while (ptrA) {
            bool inB = false;

            unsigned int index = hash(ptrA->UID);
            Node* ptrB = B->table[index].head;
            for(; ptrB != NULL; ptrB = ptrB->next) {
                if (ptrB->UID == ptrA->UID) {
                    inB= true;
                    break;
                }
            }

            if (!inB) {

                bool inC = false;
                Node* ptrC = C.table[index].head;
                for(; ptrC != NULL; ptrC = ptrC->next) {
                    if (ptrC->UID == ptrA->UID) {
                        inC = true;
                        break;
                    }
                }

                if (!inC) {
                    Node* new = malloc(sizeof(Node));
                    strcpy(new->name, ptrA->name);
                    new->UID = ptrA->UID;
                    new->next = C.table[index].head;
                    C.table[index].head = new;
                }

            }
            ptrA = ptrA->next;
        }
    }

    for(int m = 0; m < MAX; m++) {
       
        Node* ptrA = B->table[m].head;

        while (ptrA) {
 bool inB = false;
            unsigned int index = hash(ptrA->UID);
            Node* ptrB = A->table[index].head;
            for(; ptrB != NULL; ptrB = ptrB->next) {
                if (ptrB->UID == ptrA->UID) {
                    inB= true;
                    break;
                }
            }

            if (!inB) {

                bool inC = false;
                Node* ptrC = C.table[index].head;
                for(; ptrC != NULL; ptrC = ptrC->next) {
                    if (ptrC->UID == ptrA->UID) {
                        inC = true;
                        break;
                    }
                }

                if (!inC) {
                    Node* new = malloc(sizeof(Node));
                    strcpy(new->name, ptrA->name);
                    new->UID = ptrA->UID;
                    new->next = C.table[index].head;
                    C.table[index].head = new;
                }

            }
            ptrA = ptrA->next;
        }
    }


    
return C;


}

// ===============================
// 🔹 MAIN FUNCTION (Test Boilerplate)
// ===============================
int main() {
    Dictionary A, B, U, I, D, S;
    initDictionary(&A);
    initDictionary(&B);

    // Insert sample data into A
       // Insert sample data into A
    insert(&A, 101, "Alice Wonderland");
    insert(&A, 102, "Bob Marley");
    insert(&A, 103, "Charlie Puth");
    insert(&A, 104, "Diana Prince");
    insert(&A, 105, "Edward Elric");
    insert(&A, 106, "Fiona Gallagher");
    insert(&A, 107, "George Clooney");
    insert(&A, 108, "Hannah Baker");

    // Insert sample data into B
    insert(&B, 103, "Charlie Puth");
    insert(&B, 105, "Edward Elric");
    insert(&B, 109, "Isabella Swan");
    insert(&B, 110, "Jack Sparrow");
    insert(&B, 111, "Karen Page");
    insert(&B, 112, "Leo Valdez");
    insert(&B, 106, "Fiona Gallagher");


    printf("\n--- Dictionary A ---\n");
    display(&A);

    printf("\n--- Dictionary B ---\n");
    display(&B);


    // delete(&A, 101);
    // printf("After deleting 101\n");
    // display(&A);
    // // Perform Set Operations
    U = unionDict(&A, &B);
    I = intersectionDict(&A, &B);
    D = differenceDict(&A, &B);
    S = symmetricDiffDict(&A, &B);

    printf("\n--- UNION ---\n");
    display(&U);

    printf("\n--- INTERSECTION ---\n");
    display(&I);

    printf("\n--- DIFFERENCE (A - B) ---\n");
    display(&D);

    printf("\n--- SYMMETRIC DIFFERENCE ---\n");
    display(&S);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10
#define NAME_LEN   50

// ===============================
// 🔹 STRUCT DEFINITIONS
// ===============================
typedef struct Node {
    int UID;
    char name[NAME_LEN];
    struct Node* next;
} Node;

typedef struct {
    Node* buckets[MAX];
} Dictionary;


// ===============================
// 🔹 FUNCTION DECLARATIONS
// ===============================
int  hash(int uid);
void initDictionary(Dictionary* D);
void makeNull(Dictionary* D);
void display(const Dictionary* D);

// Core operations
bool insert(Dictionary* D, int uid, const char* name);
bool search(const Dictionary* D, int uid, char* outName);
bool delete(Dictionary* D, int uid);

// // UID helpers
// bool containsUID(const Dictionary* D, int uid);
// bool updateName(Dictionary* D, int uid, const char* newName);
// bool getNameByUID(const Dictionary* D, int uid, char* outName);
// int  countEntries(const Dictionary* D);

// // Set operations
Dictionary unionDict(const Dictionary* A, const Dictionary* B);
Dictionary intersectionDict(const Dictionary* A, const Dictionary* B);
Dictionary differenceDict(const Dictionary* A, const Dictionary* B);
Dictionary symmetricDiffDict(const Dictionary* A, const Dictionary* B);

// // Relations
bool isSubset(const Dictionary* A, const Dictionary* B);
bool isEqual(const Dictionary* A, const Dictionary* B);

// // Filter (functional-style)
// typedef bool (*UIDPredicate)(int uid, const char* name);
// Dictionary filterDict(const Dictionary* D, UIDPredicate pred);


// ===============================
// 🔹 MAIN FUNCTION (Testing Template)
// ===============================
int main(void) {
    Dictionary A, B;
    initDictionary(&A);
    initDictionary(&B);

    insert(&A, 101, "Alice");
    insert(&A, 102, "Bob");
    insert(&A, 103, "Charlie");

    insert(&B, 102, "Bob");
    insert(&B, 104, "David");
    insert(&B, 105, "Eve");

    printf("\n--- Dictionary A ---\n");
    display(&A);

    printf("\n--- Dictionary B ---\n");
    display(&B);


    //     printf("\n🔍 Testing SEARCH operation:\n");
    // char foundName[NAME_LEN];

    // if (search(&A, 102, foundName))
    //     printf("UID 102 found in A → Name: %s\n", foundName);
    // else
    //     printf("UID 102 not found in A.\n");

    // if (search(&A, 110, foundName))
    //     printf("UID 110 found in A → Name: %s\n", foundName);
    // else
    //     printf("UID 110 not found in A.\n");


    // printf("\n❌ Testing DELETE operation:\n");
    // if (delete(&A, 101))
    //     printf("UID 101 deleted successfully from A.\n");
    // else
    //     printf("UID 101 not found in A.\n");

    // if (delete(&A, 110))
    //     printf("UID 110 deleted successfully from A.\n");
    // else
    //     printf("UID 110 not found in A.\n");

    // printf("\n--- Dictionary A after deletion ---\n");
    // display(&A);


    Dictionary U = unionDict(&A, &B);
    Dictionary I = intersectionDict(&A, &B);
    Dictionary D = differenceDict(&A, &B);
    Dictionary S = symmetricDiffDict(&A, &B);

    printf("\n--- UNION ---\n");
    display(&U);

    printf("\n--- INTERSECTION ---\n");
    display(&I);

    printf("\n--- DIFFERENCE (A - B) ---\n");
    display(&D);

    printf("\n--- SYMMETRIC DIFFERENCE ---\n");
    display(&S);

    printf("\nIs A subset of U? %s\n", isSubset(&A, &B) ? "TRUE" : "FALSE");
    printf("Is A equal to B?  %s\n", isEqual(&A, &B) ? "TRUE" : "FALSE");

    // // Example: filter even UIDs (predicate defined below)
    // bool keepEven(int uid, const char* name);
    // Dictionary F = filterDict(&U, keepEven);
    // printf("\n--- FILTERED (even UIDs from UNION) ---\n");
    // display(&F);

    // return 0;
}

int  hash(int uid) {

    int sum = 0;
    while (uid > 0) {
        sum+=uid%100;
        uid/=10;
    }
    return sum  % MAX;
}


void initDictionary(Dictionary* D) {
    for(int i =0; i < MAX; i++) {
        D->buckets[i] = NULL;
    }
}
void makeNull(Dictionary* D) {

    for(int i = 0; i < MAX;i++) {
        Node* curr = D->buckets[i];
        while ( curr) {
            Node* temp = curr;
            curr = temp->next;
            free(temp);

        }
        D->buckets[i] = NULL;
    }
}
void display(const Dictionary* D) {
    for(int i = 0; i < MAX; i++) {
        printf("[INDEX][%d]->", i);

        Node* trav = D->buckets[i];
        if (trav == NULL) {
            printf("[EMPTY]\n");
        } else {
            while (trav) {
                printf("[%s, %d]->", trav->name, trav->UID);
                trav = trav->next;
            }
            printf("NULL\n");
        }
    }
}

// Core operations
bool insert(Dictionary* D, int uid, const char* name) {
    
    int h = hash(uid);
    bool inD = false;
    Node* trav = D->buckets[h];

    for(; trav != NULL; trav = trav->next) {
        if (trav->UID == uid) {
            inD = true;
            return false;
        }
    }

    if (!inD) {
        Node* new = malloc(sizeof(Node));
        if (!new) {
            printf("Dynamic memory allocation failed.\n");
        }
        strcpy(new->name, name);
        new->UID = uid;
        new->next = D->buckets[h];
        D->buckets[h] = new;
        return true;
    }
}


bool search(const Dictionary* D, int uid, char* outName) {

    int index = hash(uid);

    Node* ptrD = D->buckets[index];
    for(; ptrD != NULL; ptrD = ptrD->next) {
        if (ptrD->UID == uid) {
            strcpy(outName, ptrD->name);
            return true;
        }
    }
    return false;
}
bool delete(Dictionary* D, int uid) {
    
    int h = hash(uid);
    Node** trav = &(D->buckets[h]);

    for(; *trav != NULL; trav = &(*trav)->next) {
        if ((*trav)->UID == uid) {
            Node* R = *trav;
            *trav = R->next;
            free(R);
            return true;
        }
    }
    return false;
}

// // UID helpers
// bool containsUID(const Dictionary* D, int uid);
// bool updateName(Dictionary* D, int uid, const char* newName);
// bool getNameByUID(const Dictionary* D, int uid, char* outName);
// int  countEntries(const Dictionary* D);

// Set operations
Dictionary unionDict(const Dictionary* A, const Dictionary* B) {
    Dictionary C;
    initDictionary(&C);

    for(int i = 0; i < MAX; i++) {
        Node* ptrA = A->buckets[i];

        while (ptrA) {
            
            int h = hash(ptrA->UID);
            
            Node* new = malloc(sizeof(Node));
            strcpy(new->name, ptrA->name);
            new->UID = ptrA->UID;
            new->next = C.buckets[h];
            C.buckets[h] = new;

            
            ptrA = ptrA->next;
        }
    }


    for(int j = 0; j < MAX; j++) {
        Node* ptrB = B->buckets[j];

        bool inC = false;
        while (ptrB) {

            int h = hash(ptrB->UID);
            Node* travC = C.buckets[h];

            for(; travC != NULL; travC = travC->next) {
                if (travC->UID == ptrB->UID) {
                    inC = true; break;
                }
            }

            if (!inC) {
                Node* new = malloc(sizeof(Node));
                strcpy(new->name, ptrB->name);
                new->UID = ptrB->UID;
                new->next = C.buckets[h];
                C.buckets[h] = new;
            }


            
            ptrB = ptrB->next;
        }
    }
    return C;
}
Dictionary intersectionDict(const Dictionary* A, const Dictionary* B) {

    Dictionary C;
    initDictionary(&C);


    for(int i = 0; i < MAX; i++) {
        Node* ptrA = A->buckets[i];
        bool inB = false;

        while (ptrA) {

            int h = hash(ptrA->UID);
            Node* ptrB = B->buckets[h];
            for(; ptrB != NULL; ptrB = ptrB->next) {
                if (ptrB->UID == ptrA->UID) {
                    inB = true;
                    break;
                }
            }

            if (inB) {
                bool inC= false;

                Node* travC =C.buckets[h];
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
                    new->next = C.buckets[h];
                    C.buckets[h] = new;
                    break;
                }
            }
            ptrA = ptrA->next;
        }
    }
    return C;
}
Dictionary differenceDict(const Dictionary* A, const Dictionary* B) {
     Dictionary C;
    initDictionary(&C);


    for(int i = 0; i < MAX; i++) {
        Node* ptrA = A->buckets[i];
        bool inB = false;

        while (ptrA) {

            int h = hash(ptrA->UID);
            Node* ptrB = B->buckets[h];
            for(; ptrB != NULL; ptrB = ptrB->next) {
                if (ptrB->UID == ptrA->UID) {
                    inB = true;
                    break;
                }
            }

            if (!inB) {
                bool inC= false;

                Node* travC =C.buckets[h];
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
                    new->next = C.buckets[h];
                    C.buckets[h] = new;
                    break;
                }
            }
            ptrA = ptrA->next;
        }
    }
    return C;

}
Dictionary symmetricDiffDict(const Dictionary* A, const Dictionary* B) {
    Dictionary C;
    initDictionary(&C);

    for(int i = 0; i < MAX; i++) {
        Node* ptrA = A->buckets[i];
        bool inB = false;

        while (ptrA) {

            int h = hash(ptrA->UID);
            Node* ptrB = B->buckets[h];
            for(; ptrB!= NULL; ptrB = ptrB->next) {
                inB = true;
                break;
            }
            if (!inB) {
                Node* new = malloc(sizeof(Node));
                new->UID = ptrA->UID;
                strcpy(new->name, ptrA->name);
                new->next = C.buckets[h];
                C.buckets[h] = new;
                
            }
            ptrA = ptrA->next;
        }
    }



    for(int j = 0; j < MAX; j++) {
        Node* ptrB = B->buckets[j];
        bool inA = false;

        while (ptrB) {
            int h = hash(ptrB->UID);

            Node* ptrA = A->buckets[h];
            for(; ptrA != NULL; ptrA = ptrA->next) {
                if (ptrA->UID == ptrB->UID) {
                    inA = true;
                    break;
                }
            }

            if (!inA) {
                bool inC = false;
                Node* trav = C.buckets[h];
                for(; trav != NULL; trav = trav->next) {
                    if (trav->UID == ptrB->UID) {
                        inC = true;
                        break;
                    }
                }

                if (!inC) {
                    Node* new = malloc(sizeof(Node));
                    strcpy(new->name, ptrB->name);
                    new->UID = ptrB->UID;
                    new->next = C.buckets[h];
                    C.buckets[h] = new;

                }
            }
            ptrB = ptrB->next;
        }
    }
    return C;
}

// // Relations
bool isSubset(const Dictionary* A, const Dictionary* B) {
    for(int i = 0; i < MAX; i++) {
        Node* ptrA = A->buckets[i];
        
        while (ptrA) {

            bool found = false;
            int h = hash(ptrA->UID);
            Node* ptrB = B->buckets[h];
            for(; ptrB != NULL; ptrB = ptrB->next) {
                if (ptrB->UID == ptrA->UID) {
                    found = true;
                    break;

                }
            }

            if (!found) return false;

            ptrA = ptrA->next;
        }
    }
    return true;
}
bool isEqual(const Dictionary* A, const Dictionary* B) {
    return isSubset(A, B) && isSubset(B,A);
}

// // Filter (functional-style)
// typedef bool (*UIDPredicate)(int uid, const char* name);
// Dictionary filterDict(const Dictionary* D, UIDPredicate pred);


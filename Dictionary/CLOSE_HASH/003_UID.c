/************************************************************
============================================================
⚙️  CLOSE HASHING (QUADRATIC PROBING) — NESTED STRUCT SET OPS
============================================================

📘 CONTEXT:
------------
You are implementing a Dictionary using **Close Hashing**
(Open Addressing with Quadratic Probing).

Each slot stores:
   - UID (int)
   - Name (string)
   - Occupancy flags

You will also implement **Set Operations** between two dictionaries.

============================================================
📘 STRUCTURE DESIGN (Nested)
============================================================
Entry        → holds actual data (UID, name)
Slot         → wraps an Entry + flags (isOccupied, isDeleted)
Dictionary   → holds array of Slots

============================================================
📘 REQUIRED IMPLEMENTATIONS
============================================================
1️⃣ initDictionary(Dictionary *D)
2️⃣ hash(int UID)
3️⃣ insert(Dictionary *D, int UID, char *name)
4️⃣ search(Dictionary *D, int UID)
5️⃣ deleteKey(Dictionary *D, int UID)
6️⃣ display(Dictionary *D)
7️⃣ freeDictionary(Dictionary *D)

============================================================
📘 SET OPERATIONS
============================================================
- unionDict(A, B)
- intersectionDict(A, B)
- differenceDict(A, B)
- symmetricDifferenceDict(A, B)
- isSubset(A, B)
- isEqualSet(A, B)

============================================================


************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 10

// ========== NESTED STRUCTS ==========
typedef struct {
    int UID;
    char name[30];
} Entry;

typedef struct {
    Entry data;         // nested Entry
    bool isOccupied;
    bool isDeleted;
} Slot;

typedef struct {
    Slot slots[TABLE_SIZE]; // array of slots
} Dictionary;


// ========== FUNCTION DECLARATIONS ==========
int hash(int UID);
void initDictionary(Dictionary *D);
void insert(Dictionary *D, int UID, char *name);
int search(Dictionary *D, int UID);
void deleteKey(Dictionary *D, int UID);
void display(Dictionary *D);
void freeDictionary(Dictionary *D);

// ========== SET OPERATIONS ==========
Dictionary unionDict(Dictionary *A, Dictionary *B);
Dictionary intersectionDict(Dictionary *A, Dictionary *B);
Dictionary differenceDict(Dictionary *A, Dictionary *B);
Dictionary symmetricDifferenceDict(Dictionary *A, Dictionary *B);
bool isSubset(Dictionary *A, Dictionary *B);
bool isEqualSet(Dictionary *A, Dictionary *B);



// // 🧹 Remove all entries from a specific chain
// void clearChain(Dictionary *ht, int index);

// // 🔗 Find the length of the longest chain
// int getLongestChain(Dictionary *ht);

// // 💥 Count total number of collisions
// int getTotalCollisions(Dictionary *ht);


// ========== MAIN FUNCTION ==========
int main() {
    Dictionary A, B, U, I, D, SD;
    initDictionary(&A);
    initDictionary(&B);

    // === SAMPLE DATA ===
    insert(&A, 1001, "Alice");
    insert(&A, 1012, "Bob");
    insert(&A, 1044, "Diana");

    insert(&B, 1012, "Bob");
    insert(&B, 1030, "Charlie");
    insert(&B, 1055, "Eve");

    printf("\n--- DICT A ---\n");
    display(&A);

    printf("\n--- DICT B ---\n");
    display(&B);

    // === SET OPERATIONS ===
    U  = unionDict(&A, &B);
    I  = intersectionDict(&A, &B);
    D  = differenceDict(&A, &B);
    SD = symmetricDifferenceDict(&A, &B);

    printf("\n--- UNION (A ∪ B) ---\n");
    display(&U);

    printf("\n--- INTERSECTION (A ∩ B) ---\n");
    display(&I);

    printf("\n--- DIFFERENCE (A - B) ---\n");
    display(&D);

    printf("\n--- SYMMETRIC DIFFERENCE (A △ B) ---\n");
    display(&SD);

    // === COMPARISONS ===
    printf("\n--- IS A SUBSET OF B? ---\n");
    printf(isSubset(&A, &B) ? "YES\n" : "NO\n");

    printf("\n--- ARE A AND B EQUAL SETS? ---\n");
    printf(isEqualSet(&A, &B) ? "YES\n" : "NO\n");

    return 0;
}


// ========== FUNCTION DEFINITIONS (Skeletons) ==========

// 🧮 Hash Function
int hash(int UID) {
    
  return (UID % TABLE_SIZE);
}


// Initialize dictionary slots
void initDictionary(Dictionary *D){
    for(int i = 0; i < TABLE_SIZE; i++) {
        D->slots[i].isDeleted = 0;
        D->slots[i].isOccupied = 0;
    }
    
}


// Insert using Quadratic Probing
void insert(Dictionary *D, int UID, char *name) {
    int index = hash(UID);
    
    for(int j = 0; j < TABLE_SIZE; j++) {
        int i = (index + j) % TABLE_SIZE;



        if (D->slots[i].isOccupied == 1 && D->slots[i].data.UID == UID) {
            return;
        } 
        
         else if (D->slots[i].isOccupied == 0 || D->slots[i].isDeleted == 1) 
            strcpy(D->slots[i].data.name, name);
            D->slots[i].data.UID = UID;
            D->slots[i].isDeleted = 0;
            D->slots[i].isOccupied = 1;
            return;
        
    }
    return;
   
}


// Search returns index or -1 if not found
int search(Dictionary *D, int UID) {
    
    for(int i = 0; i < TABLE_SIZE; i++) {
        int h = hash(UID);
        int index = (h + i) % TABLE_SIZE;
        if (D->slots[index].data.UID == UID) {
            return i;
        }


    }
    return -1;
}


// Delete a key (mark deleted)
void deleteKey(Dictionary *D, int UID) {
    
    for(int i = 0; i < TABLE_SIZE; i++) {
        int h = hash(UID);
        int index = (h + i) % TABLE_SIZE;

        if (D->slots[index].data.UID == UID) {
            D->slots[index].isDeleted = 1;
            D->slots[index].isOccupied = 0;
            strcpy(D->slots[index].data.name, "");
            D->slots[index].data.UID = 0;
            return;

        }
    }
    
}


// Display all valid entries
void display(Dictionary *D) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        printf("%d. ->", i+1);
        if (D->slots[i].isOccupied) {
            printf("[%s, %d]\n", D->slots[i].data.name, D->slots[i].data.UID);
        } else if (D->slots[i].isDeleted) {
            printf("[DELETED]\n");
        } else {
            printf("[EMPTY]\n");
        }
    }
    printf("\n");
}


// Free dictionary (optional if static array)
void freeDictionary(Dictionary *D) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        D->slots[i].isDeleted = 0;
        D->slots[i].isOccupied = 0;
        D->slots[i].data.UID = 0;
        strcpy(D->slots[i].data.name, "");
    }
}


// ================== SET OPERATIONS ==================

// UNION (A ∪ B)
Dictionary unionDict(Dictionary *A, Dictionary *B) {
    

    Dictionary C;
    initDictionary(&C);


    for(int i = 0; i  <TABLE_SIZE; i++) {
        Slot ptra = A->slots[i];


        int h = hash(ptra.data.UID);
        for(int k = 0; k < TABLE_SIZE; k++) {
            int index = (h+k) % TABLE_SIZE;

            if (C.slots[index].isOccupied && C.slots[index].data.UID == ptra.data.UID) {
                break;
            } else if (ptra.isOccupied && C.slots[index].isOccupied == 0 || C.slots[index].isDeleted == 1) {
                C.slots[index].data.UID = ptra.data.UID;
                strcpy(C.slots[index].data.name,ptra.data.name);
                C.slots[index].isDeleted = 0;
                C.slots[index].isOccupied = 1;
                break;
            }
        }
    }


    for(int i = 0; i < TABLE_SIZE; i++) {
        Slot ptrB = B->slots[i];
        int h = hash(ptrB.data.UID);


        for(int j = 0; j < TABLE_SIZE; j++) {
            int index = (h + j) % TABLE_SIZE;

            if (C.slots[index].isOccupied && C.slots[index].data.UID == ptrB.data.UID) {
                break;
            } else if (ptrB.isOccupied && C.slots[index].isOccupied == 0 ||C.slots[index].isDeleted == 1) {
                strcpy(C.slots[index].data.name, ptrB.data.name);
                C.slots[index].data.UID = ptrB.data.UID;
                C.slots[index].isDeleted = 0;
                C.slots[index].isOccupied = 1;
                break;
            }
        }
    }

    return C;



}


// INTERSECTION (A ∩ B)
Dictionary intersectionDict(Dictionary *A, Dictionary *B) {
   

    Dictionary C;
    initDictionary(&C);

    for(int i = 0; i < TABLE_SIZE; i++) {
        Slot ptrA = A->slots[i];
        
        bool inB = false;
        for(int k = 0; k < TABLE_SIZE; k++) {
            
            if (B->slots[k].data.UID == ptrA.data.UID) {
                inB = true;
                break;
            }
        }


            if (inB) {

                int h = hash(ptrA.data.UID);
                for(int j = 0; j < TABLE_SIZE; j++) {
                    int index = (h+j) % TABLE_SIZE;

                    if (C.slots[index].isOccupied == 1 && C.slots[index].data.UID == ptrA.data.UID) {
                        break;
                    } else if (ptrA.isOccupied && C.slots[index].isOccupied == 0 || C.slots[index].isDeleted == 1) {
                        C.slots[index].data.UID = ptrA.data.UID;
                        strcpy(C.slots[index].data.name,ptrA.data.name);
                        C.slots[index].isDeleted = 0;
                        C.slots[index].isOccupied = 1;
                        break;
                    }
                }
            }
        
    }

    return C;
}




// DIFFERENCE (A - B)
Dictionary differenceDict(Dictionary *A, Dictionary *B) {
    
    Dictionary C;
    initDictionary(&C);

    for(int i = 0; i < TABLE_SIZE; i++) {
        Slot ptrA = A->slots[i];
        if (!ptrA.isOccupied || ptrA.isDeleted) continue;
        bool inB = false;


        for(int k = 0; k < TABLE_SIZE; k++) {
            if (B->slots[k].data.UID == ptrA.data.UID) {
                inB = true;
                break;
            }
        }


        if (!inB) {
            int h = hash(ptrA.data.UID);
            for(int j = 0; j < TABLE_SIZE; j++) {
                int index = (h + j) % TABLE_SIZE;

                if (C.slots[index].isOccupied && C.slots[index].data.UID == ptrA.data.UID) {
                    break;
                } else if (ptrA.isOccupied  == 1 && C.slots[index].isOccupied == 0 || C.slots[index].isDeleted == 1) {
                        C.slots[index].data.UID = ptrA.data.UID;
                        strcpy(C.slots[index].data.name,ptrA.data.name);
                        C.slots[index].isDeleted = 0;
                        C.slots[index].isOccupied = 1;
                        break;
                }
            }
        }
    }

    return C;
}


// SYMMETRIC DIFFERENCE (A △ B)
Dictionary symmetricDifferenceDict(Dictionary *A, Dictionary *B) {
    
    Dictionary C;
    initDictionary(&C);

    for(int i = 0; i < TABLE_SIZE; i++) {
        Slot ptrA = A->slots[i];


        if (!ptrA.isOccupied) continue;

        bool inB = false;

        for(int k = 0; k < TABLE_SIZE; k++) {
            if (B->slots[k].isOccupied && B->slots[k].data.UID == ptrA.data.UID) {
                inB = true;
                break;


            }

        }


        if (!inB) {

                int h = hash(ptrA.data.UID);
                for(int j = 0; j < TABLE_SIZE; j++) {
                    int index = (h+j) % TABLE_SIZE;
                    
                    if (ptrA.isOccupied && C.slots[index].isOccupied == 0 || C.slots[index].isDeleted == 1) {
                         C.slots[index].data.UID = ptrA.data.UID;
                        strcpy(C.slots[index].data.name,ptrA.data.name);
                        C.slots[index].isDeleted = 0;
                        C.slots[index].isOccupied = 1;
                        break;
                    }
                }
            
        
    }

}



    for(int m = 0; m < TABLE_SIZE; m++) {
        Slot ptrA = B->slots[m];

        if (!ptrA.isOccupied) continue;
        bool inB = false;
        for(int k = 0; k < TABLE_SIZE; k++) {
            if ( A->slots->isOccupied && A->slots[k].data.UID == ptrA.data.UID) {

                inB = true;
                break;

            }
        
        }

        if (!inB) {
                int h = hash(ptrA.data.UID);
                for(int j = 0; j < TABLE_SIZE; j++) {
                    int index = (h+j) % TABLE_SIZE;
                    
                     if (ptrA.isOccupied && C.slots[index].isOccupied == 0 || C.slots[index].isDeleted == 1) {
                         C.slots[index].data.UID = ptrA.data.UID;
                        strcpy(C.slots[index].data.name,ptrA.data.name);
                        C.slots[index].isDeleted = 0;
                        C.slots[index].isOccupied = 1;
                        break;
                    }
                }
            }

        }
        

    return C;
}


// SUBSET CHECK (A ⊆ B)
bool isSubset(Dictionary *A, Dictionary *B) {
     for(int i = 0; i < TABLE_SIZE; i++) {
        Slot a = A->slots[i];
        if (a.isDeleted == 1 || a.isOccupied ==0) continue;
        bool found = false;

        for(int j = 0; j < TABLE_SIZE; j++) {
            if (!B->slots[j].isOccupied) continue;
            if (a.data.UID == B->slots[j].data.UID) {
                found = true;
                break;
            }
        }
        if (!found)  return false;
    }
    return true;

}


// EQUALITY CHECK (A == B)
bool isEqualSet(Dictionary *A, Dictionary *B) {
     for(int i = 0; i < TABLE_SIZE; i++) {
        Slot a = A->slots[i];
        if (a.isDeleted == 1 || a.isOccupied ==0) continue;
        bool found = false;

        for(int j = 0; j < TABLE_SIZE; j++) {
            if (!B->slots[j].isOccupied) continue;
            if (a.data.UID == B->slots[j].data.UID) {
                found = true;
                break;
            }
        }
        if (!found)  return false;
    }
    return true;

   
}

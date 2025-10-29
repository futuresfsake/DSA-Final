/************************************************************
 🧠 CLOSED HASHING (LINEAR PROBING) — STRING DICTIONARY
*************************************************************
📘 CONTEXT:
Implement a Dictionary using **Closed Hashing (Open Addressing)**.
Each slot stores:
   - UID (int)
   - name (string)
   - isOccupied flag

Support operations:
  ✅ insert()
  ✅ search()
  ✅ delete()
  ✅ display()
  ✅ set operations: union, intersection, difference, symmetric difference
*************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 10
#define NAME_LEN 50

// ===============================
// 🔹 STRUCT DEFINITIONS
// ===============================
typedef struct {
    int UID;
    char name[NAME_LEN];
} Entry;

typedef struct {
    Entry data;
    bool isOccupied;
} Slot;

typedef struct {
    Slot slots[TABLE_SIZE];
} Dictionary;

// ===============================
// 🔹 FUNCTION DECLARATIONS
// ===============================
int hash(int UID);
void initDictionary(Dictionary *d);
bool insert(Dictionary *d, int UID, const char *name);
bool search(Dictionary *d, int UID, char *result);
bool delete(Dictionary *d, int UID);
void display(Dictionary *d);


Dictionary unionDict(Dictionary *A, Dictionary *B);
Dictionary intersectionDict(Dictionary *A, Dictionary *B);
Dictionary differenceDict(Dictionary *A, Dictionary *B);
Dictionary symmetricDiffDict(Dictionary *A, Dictionary *B);

// ===============================
// 🔹 MAIN FUNCTION (Test Boilerplate)
// ===============================
int main() {
    Dictionary A, B, U, I, D, S;
    initDictionary(&A);
    initDictionary(&B);

    // Insert sample data into A
    insert(&A, 101, "Alice");
    insert(&A, 102, "Bob");
    insert(&A, 103, "Charlie");

    // Insert sample data into B
    insert(&B, 102, "Bob");
    insert(&B, 104, "David");
    insert(&B, 105, "Eve");

    printf("\n--- Dictionary A ---\n");
    display(&A);
    printf("\n--- Dictionary B ---\n");
    display(&B);

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


int hash(int UID) {
    
    int sum = 0;
    
    while (UID>0) {
        sum+= (UID%100);
        UID/=100;
    }

return sum % TABLE_SIZE;
}
void initDictionary(Dictionary *d) {
    
    for(int i = 0; i < TABLE_SIZE; i++) {
        d->slots[i].isOccupied = false;
    }
    

}

bool insert(Dictionary *d, int UID, const char *name) {
    
    int h = hash(UID);
    for(int i = 0; i < TABLE_SIZE; i++) {
        int index = (h + i) % TABLE_SIZE;
        
        if(d->slots[index].isOccupied && d->slots[index].data.UID == UID) {
            return false;
        } else if (d->slots[index].isOccupied == 0) {
            strcpy(d->slots[index].data.name, name);
            d->slots[index].data.UID = UID;
            d->slots[index].isOccupied = 1;
            return true;
        }
    }
    
    return false;
    
}


bool search(Dictionary *d, int UID, char *result) {
    
    int h = hash(UID);
    for(int i = 0; i < TABLE_SIZE; i++) {
        int index = (h + i) % TABLE_SIZE;
        
        if (d->slots[index].isOccupied && d->slots[index].data.UID == UID) {
            strcpy(result, d->slots[index].data.name);
            return true;
        }
    }
    return false;
    
    
}


bool delete(Dictionary *d, int UID) {
    int h = hash(UID);
    
    for(int i = 0; i < TABLE_SIZE; i++) {
        int index = (h + i) % TABLE_SIZE;
        
        if (d->slots[index].isOccupied && d->slots[index].data.UID == UID) {
            strcpy(d->slots[index].data.name, "");
            d->slots[index].data.UID = 0;
            d->slots[index].isOccupied = 0;
            return true;
        }
    }
    return false;
}


void display(Dictionary *d) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        printf("[INDEX][%d]->", i);
        
        if (d->slots[i].isOccupied ==0) {
            printf("[EMPTY]\n");
        } else {
            printf("[%s, %d]\n", d->slots[i].data.name, d->slots[i].data.UID);
        }
    }
}


Dictionary unionDict(Dictionary *A, Dictionary *B) {
    
    Dictionary C;
    initDictionary(&C);
    
    for(int i = 0; i < TABLE_SIZE; i++) {
        Slot ptrA = A->slots[i];
        if (ptrA.isOccupied == 0) continue;
       
        int h = hash(ptrA.data.UID);
        for(int j = 0; j < TABLE_SIZE; j++) {
            int index = (h + j) % TABLE_SIZE;
            
            if (C.slots[index].isOccupied == 1 && C.slots[index].data.UID == ptrA.data.UID) {
                break;
            } else if (ptrA.isOccupied && C.slots[index].isOccupied == 0) {
                strcpy(C.slots[index].data.name, ptrA.data.name);
                C.slots[index].data.UID = ptrA.data.UID;
                C.slots[index].isOccupied = 1;
                break;
            }
        }
    }
    
    
    for(int k = 0; k < TABLE_SIZE; k++) {
        Slot ptrB = B->slots[k];
        
        if (!ptrB.isOccupied)continue;
        
        bool inC = false;
        
        for(int m = 0; m < TABLE_SIZE; m++) {
            if (C.slots[m].data.UID == ptrB.data.UID) {
                inC = true;
                break;
        }
        }
        
        if (!inC) {
            int h = hash(ptrB.data.UID);
        
        
        for(int j = 0; j < TABLE_SIZE; j++) {
            int i = (h + j) % TABLE_SIZE;
            
            if (C.slots[i].isOccupied && C.slots[i].data.UID == ptrB.data.UID) {
                break;
            } else if (ptrB.isOccupied && C.slots[i].isOccupied == 0) {
                strcpy(C.slots[i].data.name, ptrB.data.name);
                C.slots[i].data.UID = ptrB.data.UID;
                C.slots[i].isOccupied = 1;
                break;
            }
        }
        
        }
    
    
   
    
}
 return C;

}


Dictionary intersectionDict(Dictionary *A, Dictionary *B) {
    
    Dictionary C;
    initDictionary(&C);
    
    for(int i = 0; i < TABLE_SIZE; i++) {
        Slot ptrA = A->slots[i];
        
        bool inB = false;
        if (!ptrA.isOccupied) continue;
        
        for(int k = 0; k < TABLE_SIZE; k++) {
            Slot ptrB = B->slots[k];
            if (ptrA.data.UID == ptrB.data.UID) {
                inB = true;
                break;
            }
        }
        
        if (inB) {
            
            int h = hash(ptrA.data.UID);
            for(int m = 0; m < TABLE_SIZE; m++) {
                int index = (h + m) % TABLE_SIZE;
                
                if (C.slots[index].isOccupied && C.slots[index].data.UID == ptrA.data.UID) {
                    break;
                } else if (ptrA.isOccupied && C.slots[index].isOccupied == 0) {
                    strcpy(C.slots[index].data.name, ptrA.data.name);
                    C.slots[index].data.UID = ptrA.data.UID;
                    C.slots[index].isOccupied = 1;
                    break;
                }
            }
        }
    }
    
    return C;
    
}
Dictionary differenceDict(Dictionary *A, Dictionary *B) {
    Dictionary C;
    initDictionary(&C);
    
    for(int i = 0; i < TABLE_SIZE; i++) {
        Slot ptrA = A->slots[i];
        if (ptrA.isOccupied == 0) continue;
        
        bool inB = false;
        
        for(int k = 0; k < TABLE_SIZE; k++) {
            Slot ptrB = B->slots[k];
            if (ptrB.isOccupied == 0) continue;
            if (ptrA.data.UID == ptrB.data.UID) {
                inB = true;
                break;
            }
        }
        
        if (!inB) {
            
            int h = hash(ptrA.data.UID);
            for(int m = 0; m < TABLE_SIZE; m++) {
                int index = (h + m) % TABLE_SIZE;
                
                if (C.slots[index].isOccupied && C.slots[index].data.UID == ptrA.data.UID) {
                    break;
                } else if (ptrA.isOccupied && C.slots[index].isOccupied == 0) {
                    strcpy(C.slots[index].data.name, ptrA.data.name);
                    C.slots[index].data.UID = ptrA.data.UID;
                    C.slots[index].isOccupied = 1;
                    break;
                }
            }
        }
    }
    
    return C;
    
}

Dictionary symmetricDiffDict(Dictionary *A, Dictionary *B){
    
    Dictionary C;
    initDictionary(&C);
    
    for(int i = 0; i < TABLE_SIZE; i++) {
        Slot ptrA = A->slots[i];
        
        if (ptrA.isOccupied == 0) continue;
        bool inB = false;
        
        for(int j = 0; j < TABLE_SIZE; j++) {
            if (B->slots[j].data.UID == ptrA.data.UID) {
                inB = true;
                break;
            }
        }
        
        if (!inB) {
            
            int h = hash(ptrA.data.UID);
            for(int k = 0; k<TABLE_SIZE; k++) {
                int index = (h+k) % TABLE_SIZE;
                
                if ( ptrA.isOccupied && C.slots[index].isOccupied ==0) {
                    strcpy(C.slots[index].data.name, ptrA.data.name);
                    C.slots[index].data.UID = ptrA.data.UID;
                    C.slots[index].isOccupied = 1;
                    break;
                }
            }
        }
    }
    
    
    for(int j = 0; j < TABLE_SIZE; j++) {
        
        Slot ptrB = B->slots[j];
        bool inA = false;
        if (ptrB.isOccupied == 0) continue;
        for(int k = 0; k < TABLE_SIZE; k++) {
            if (A->slots[k].data.UID == ptrB.data.UID) {
                inA = true;
                break;
            }
        }
        
        if (!inA) {
            int h = hash(ptrB.data.UID);
            for(int i = 0; i < TABLE_SIZE; i++) {
                int index = (h+i) % TABLE_SIZE;
                
                if (C.slots[index].isOccupied && C.slots[index].data.UID == ptrB.data.UID) {
                    break;
                } else if (ptrB.isOccupied && C.slots[index].isOccupied == 0) {
                    strcpy(C.slots[index].data.name, ptrB.data.name);
                    C.slots[index].data.UID = ptrB.data.UID;
                    C.slots[index].isOccupied =1;
                    break;
                }
            }
        }
    }
    
    return C;
}


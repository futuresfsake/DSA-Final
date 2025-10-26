/************************************************************
 🧠 CLOSED HASHING (OPEN ADDRESSING) – PERSON DICTIONARY
*************************************************************

📘 CONTEXT:
Implement a **Dictionary** using **Closed Hashing** (Open Addressing)
with **Linear Probing**.

Each entry stores:
   - id (int)
   - name (string)
   - age (int)

*************************************************************
🔧 TASKS TO IMPLEMENT:
1️⃣ hash(int id)
2️⃣ initDictionary()
3️⃣ insert(Dictionary *D, int id, char *name, int age)
4️⃣ search(Dictionary *D, int id)
5️⃣ display(Dictionary *D)
6️⃣ delete(Dictionary *D, int id)

7️⃣ unionDict(A, B)
8️⃣ intersectDict(A, B)
9️⃣ differenceDict(A, B)

⚙️ SPECIAL FUNCTIONS:
10️⃣ clearCluster(Dictionary *D, int index)
11️⃣ getLongestCluster(Dictionary *D)
12️⃣ countTotalCollisions(Dictionary *D)

*************************************************************
🧠 GOAL:
Practice closed hashing, probing, and set operations
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 10

// ====================== STRUCTURES =========================

// Entry struct
typedef struct {
    int id;
    char name[30];
    int age;
    bool isOccupied;
    bool isDeleted;
} Entry;

// Dictionary (fixed-size table)
typedef struct {
    Entry table[TABLE_SIZE];
} Dictionary;


// ====================== FUNCTION DECLARATIONS =========================

// Core Hash Table Functions
unsigned int hash(int id);
void initDictionary(Dictionary *D);
bool insert(Dictionary *D, int id, char *name, int age);
Entry* search(Dictionary *D, int id);
bool delete(Dictionary *D, int id);
void display(Dictionary *D);

// Set-Like Operations
Dictionary unionDict(Dictionary *A, Dictionary *B);
Dictionary intersectDict(Dictionary *A, Dictionary *B);
Dictionary differenceDict(Dictionary *A, Dictionary *B);

// // Special Analytical Functions
// void clearCluster(Dictionary *D, int index);
// int getLongestCluster(Dictionary *D);
// int countTotalCollisions(Dictionary *D);


// ====================== MAIN FUNCTION =========================
int main() {
    Dictionary A, B, U, I, D;

    initDictionary(&A);
    initDictionary(&B);

    insert(&A, 185963, "Alice", 25);
    insert(&A, 785296, "Bob", 30);
    insert(&A, 458523, "Carol", 45);

    insert(&B, 458523, "Carol", 45);
    insert(&B, 197352, "David", 28);
    insert(&B, 761581, "Eva", 35);

    printf("\n=== Dictionary A ===\n");
    display(&A);

    printf("\n=== Dictionary B ===\n");
    display(&B);

    printf("\n=== UNION (A ∪ B) ===\n");
    U = unionDict(&A, &B);
    display(&U);

    printf("\n=== INTERSECTION (A ∩ B) ===\n");
    I = intersectDict(&A, &B);
    display(&I);

    printf("\n=== DIFFERENCE (A − B) ===\n");
    D = differenceDict(&A, &B);
    display(&D);

    // // 🔧 Special Tasks
    // printf("\n=== SPECIAL ANALYTICS ===\n");
    // printf("Longest cluster length: %d\n", getLongestCluster(&A));
    // printf("Total collisions: %d\n", countTotalCollisions(&A));

    return 0;
}


// ====================== FUNCTION DEFINITIONS (SKELETONS) =========================

// Hash function
unsigned int hash(int id) {
    

    int sum = 0; 
    while (id > 0) {
        sum+= id%100;
        id/=100;
    }
    return sum % TABLE_SIZE;
}


// Initialize table
void initDictionary(Dictionary *D) {
    
    
    for(int i = 0; i < TABLE_SIZE; i++) {
        D->table[i].isDeleted = false;
        D->table[i].isOccupied = false;
    }
}


// Insert record using linear probing
bool insert(Dictionary *D, int id, char *name, int age) {
    

    unsigned int h = hash(id);

    for(int i = 0; i < TABLE_SIZE; i++) {
        unsigned int index = (h+ i) % TABLE_SIZE;
    if (D->table[index].isOccupied == 1 && (D->table[index].id== id)) {
        printf("Inserting failed! %s already exists!\n", name);
        return false;
    } else if (D->table[index].isOccupied == 0 || D->table[index].isDeleted == 1) {
        strncpy(D->table[index].name, name, sizeof(D->table[index].name)-1);
        D->table[index].name[sizeof(D->table[index].name)-1] = '\0';

        D->table[index].age = age;
        D->table[index].id = id;
        D->table[index].isOccupied = 1;
        D->table[index].isDeleted = 0;

        return true;

    }

}
    return false;
}


// Search record by ID
Entry* search(Dictionary *D, int id) {
    unsigned int index = hash(id);
    
    for(int i = 0; i < TABLE_SIZE; i++) {
        if (D->table[i].id == id && D->table[index].isOccupied == 1) {
            return &(D->table[i]);


        }
    }
    return false;
}


// Delete record by ID
bool delete(Dictionary *D, int id) {
    unsigned int index = hash(id);
    
    for(int i = 0; i < TABLE_SIZE; i++) {
        if (D->table[i].id == id && D->table[index].isOccupied == 1) {
            D->table[i].age =0;
            D->table[i].id = 0;
            strcpy(D->table[i].name, "");
            D->table[i].isDeleted = 1;
            D->table[i].isOccupied = 0;
            return true;
            
            

        }

        
    }
    return false;
}


// Display all non-deleted entries
void display(Dictionary *D) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        printf("%d. ", i+1);
        if (D->table[i].isOccupied == 1) {
            printf("{%s, %d, %d}\n", D->table[i].name, D->table[i].id, D->table[i].age);
        } else if (D->table[i].isOccupied == 0 && D->table->isDeleted == 1) {
            printf("[DELETED]\n");
        } else if (D->table[i].isOccupied == 0 && D->table[i].isDeleted == 0) {
            printf("EMPTY\n");
        }

        
    }

}


// // ====================== SET OPERATIONS =========================

// Union of two dictionaries
Dictionary unionDict(Dictionary *A, Dictionary *B) {
    // 🧩 IMPLEMENT ME
    Dictionary R;
    initDictionary(&R);

    for(int i = 0; i < TABLE_SIZE; i++) {
        
        

        for(int j = 0; j < TABLE_SIZE; j++) {
            unsigned int h = hash(A->table[i].id);
            unsigned int index = (h+j) % TABLE_SIZE;

        if (R.table[index].isOccupied == 1 && R.table[index].id == A->table[i].id) {
            exit(1);
        } 
        
        
         else if ( A->table[i].isOccupied == 1 &&R.table[index].isOccupied == 0 || R.table[index].isDeleted == 1) {
            strncpy(R.table[index].name, A->table[i].name, sizeof(R.table[index].name)-1);
            R.table[index].name[sizeof(R.table[index].name) -1] = '\0';
            R.table[index].id = A->table[i].id;
            R.table[index].age = A->table[i].age;
            R.table[index].isOccupied = 1;
            R.table[index].isDeleted = 0;
            break;
        }
    
    }

    }


    for(int j = 0; j < TABLE_SIZE; j++) {
        unsigned int h = hash(B->table[j].id);

        bool isPresent = false;

        for(int hh= 0; hh < TABLE_SIZE; hh++) {
            unsigned int index = (h + hh) % TABLE_SIZE;
            if (R.table[index].id == B->table[j].id && strcmp(R.table[index].name, B->table[j].name) ==0) {
                isPresent = true;
                break;
            }
        

        if (!isPresent) {
            if ( B->table[j].isOccupied == 1 && R.table[index].isOccupied ==0 || R.table[index].isDeleted == 1) {
                strcpy(R.table[index].name, B->table[j].name);
                R.table[index].age = B->table[j].age;
                R.table[index].id = B->table[j].id;
                R.table[index].isDeleted = 0;
                R.table[index].isOccupied=1;
            }
           break;
        }
    }

}
    return R;
}


// Intersection of two dictionaries
Dictionary intersectDict(Dictionary *A, Dictionary *B) {
    // 🧩 IMPLEMENT ME
    Dictionary R;
    initDictionary(&R);
    for(int i = 0; i < TABLE_SIZE; i++) {
        Entry a = A->table[i];

        bool inB = false;

        for(int j = 0; j < TABLE_SIZE; j++) {
            Entry b = B->table[j];
            if (b.id == a.id) {
                inB = true; break;
            }
        }




        if (inB) {
            unsigned int h = hash(a.id);
            for(int k = 0; k < TABLE_SIZE; k++) {
                unsigned int index = (h + k) % TABLE_SIZE;
            
                 if (R.table[index].isOccupied == 1 && R.table[index].id == a.id) {
                    break;
                } else if (a.isOccupied == 1 && R.table[index].isOccupied == 0 || R.table[index].isDeleted == 1) {
                    strcpy(R.table[index].name, a.name);
                    R.table[index].age = a.age;
                    R.table[index].id = a.id;
                    R.table[index].isDeleted = 0;
                    R.table[index].isOccupied = 1;
                    break;
                    
                }

            }
            

        }
    }


    return R;
}


// Difference of two dictionaries (A − B)
Dictionary differenceDict(Dictionary *A, Dictionary *B) {
    
    // 🧩 IMPLEMENT ME
    Dictionary R;
    initDictionary(&R);
    for(int i = 0; i < TABLE_SIZE; i++) {
        Entry a = A->table[i];

        bool inB = false;

        for(int j = 0; j < TABLE_SIZE; j++) {
            Entry b = B->table[j];
            if (b.id == a.id) {
                inB = true; break;
            }
        }




        if (!inB) {
            unsigned int h = hash(a.id);
            for(int k = 0; k < TABLE_SIZE; k++) {
                unsigned int index = (h + k) % TABLE_SIZE;
            
                 if (R.table[index].isOccupied == 1 && R.table[index].id == a.id) {
                    break;
                } else if (a.isOccupied == 1 && R.table[index].isOccupied == 0 || R.table[index].isDeleted == 1) {
                    strcpy(R.table[index].name, a.name);
                    R.table[index].age = a.age;
                    R.table[index].id = a.id;
                    R.table[index].isDeleted = 0;
                    R.table[index].isOccupied = 1;
                    break;
                    
                }

            }
            

        }
    }


    return R;
}


    


// ====================== SPECIAL ANALYTICS =========================

// 🧹 Remove all entries in a continuous occupied cluster
void clearCluster(Dictionary *D, int index) {
    
    int start = index;

    while (start) {
        D->table[index].age = 0;
        D->table[index].id = 0;
        D->table[index].isDeleted = true;
        D->table[index].isOccupied = false;
        strcpy(D->table[index].name, "");
        start = (start+1) % TABLE_SIZE; // ! MOVE RIGHT CIRCULARLY
    }
}


// 🔗 Return the longest sequence of consecutive occupied slots
int getLongestCluster(Dictionary *D) {
    // 🧩 IMPLEMENT ME

    int count = 0;
    int longest = 0;
    for(int i = 0; i < TABLE_SIZE; i++) {
        if (D->table[i].isOccupied) {
            count++;
        if (count>longest) longest = count;
        } else {
            count = 0;
        }


    }
    return longest;
}


// 💥 Count total collisions (when probe index != hash index)
int countTotalCollisions(Dictionary *D) {

    int count = 0;
    for(int i = 0; i < TABLE_SIZE; i++) {
        if (D->table[i].isOccupied) {
            unsigned int index = hash(D->table[i].id);
            if (index != i) count++;
        }
    }
    // 🧩 IMPLEMENT ME
    return count;
}

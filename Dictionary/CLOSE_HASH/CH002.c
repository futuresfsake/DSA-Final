/************************************************************
 🎓 CLOSED HASHING (LINEAR PROBING) – STUDENT DICTIONARY
*************************************************************

📘 CONTEXT:
You will implement a **closed hashing (open addressing)**
hash table that stores **student records**.

Each record (Entry) contains:
    - studentID (int)
    - name (string)
    - grade (float)

*************************************************************
🔧 CORE FUNCTIONS:
1️⃣ hash(int id)
2️⃣ initDictionary(Dictionary *D)
3️⃣ insert(Dictionary *D, int studentID, char *name, float grade)
4️⃣ search(Dictionary *D, int studentID)
5️⃣ delete(Dictionary *D, int studentID)
6️⃣ display(Dictionary *D)

*************************************************************
🔢 SET-LIKE OPERATIONS:
7️⃣ unionDict(A, B)          → all unique students
8️⃣ intersectDict(A, B)      → students common to both
9️⃣ differenceDict(A, B)     → students in A not in B

*************************************************************
💡 SPECIAL ANALYTICS:
🔟 clearCluster(Dictionary *D, int index)
11️⃣ getLongestCluster(Dictionary *D)
12️⃣ countTotalCollisions(Dictionary *D)

*************************************************************
🎯 ADVANCED SET CHALLENGES (DIFFICULT):
13️⃣ topPerformers(Dictionary *D, float threshold)
14️⃣ mergeSameGrade(Dictionary *A, Dictionary *B)
15️⃣ symmetricDifference(Dictionary *A, Dictionary *B)

************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 15

// ====================== STRUCTURES =========================

typedef struct {
    int studentID;
    char name[40];
    float grade;
    bool isOccupied;
    bool isDeleted;
    int collisions;
} Entry;

typedef struct {
    Entry table[TABLE_SIZE];
} Dictionary;


// ====================== FUNCTION DECLARATIONS =========================

// Core Operations
unsigned int hash(int id);
void initDictionary(Dictionary *D);
bool insert(Dictionary *D, int studentID, char *name, float grade);
Entry* search(Dictionary *D, int studentID);
bool delete(Dictionary *D, int studentID);
void display(Dictionary *D);

// // Set-like Operations
Dictionary unionDict(Dictionary *A, Dictionary *B);
Dictionary intersectDict(Dictionary *A, Dictionary *B);
Dictionary differenceDict(Dictionary *A, Dictionary *B);

// // Special Analytics
// void clearCluster(Dictionary *D, int index);
// int getLongestCluster(Dictionary *D);
// int countTotalCollisions(Dictionary *D);

// // Advanced Challenges (for mastery)
// Dictionary topPerformers(Dictionary *D, float threshold);
// Dictionary mergeSameGrade(Dictionary *A, Dictionary *B);
// Dictionary symmetricDifference(Dictionary *A, Dictionary *B);


// ====================== MAIN FUNCTION =========================
int main() {
    Dictionary A, B, U, I, D, TP, M, SD;

    initDictionary(&A);
    initDictionary(&B);

    // Sample Data
    insert(&A, 1001, "Alice", 85.5);
    insert(&A, 1002, "Bob", 90.0);
    insert(&A, 1003, "Charlie", 72.0);
    insert(&A, 1004, "Diane", 88.0);

    insert(&B, 1003, "Charlie", 72.0);
    insert(&B, 1005, "Evan", 95.0);
    insert(&B, 1006, "Faith", 88.0);
    insert(&B, 1002, "Bob", 90.0);

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

    // printf("\n=== TOP PERFORMERS (>85) ===\n");
    // TP = topPerformers(&A, 85.0);
    // display(&TP);

    // printf("\n=== SYMMETRIC DIFFERENCE (A ⊕ B) ===\n");
    // SD = symmetricDifference(&A, &B);
    // display(&SD);

    // printf("\n=== LONGEST CLUSTER LENGTH ===\n");
    // printf("Cluster length: %d\n", getLongestCluster(&A));

    // printf("\n=== TOTAL COLLISIONS ===\n");
    // printf("Collisions: %d\n", countTotalCollisions(&A));

    return 0;
}


// ====================== FUNCTION DEFINITIONS (SKELETONS) =========================

// Hash function
unsigned int hash(int id) {
    unsigned int ids = id;
    unsigned int bit = 0;
    unsigned int count = 0;
    for(int i = 32-1; i>0 ; i--) {
     
        bit = (id >> i) & 1;
        if (bit) {
            count++;
        }        
    }
    int sum = 0;
    while (id>0) {
        sum+= id % 100;
        id /=100;

    }
    return (sum+count+32) % TABLE_SIZE;
}

// Initialize all slots
void initDictionary(Dictionary *D) {
   
    for(int i = 0; i < TABLE_SIZE; i++) {
        D->table[i].isDeleted = 0;
        D->table[i].isOccupied = 0;
    }
}

// Insert record (linear probing)
bool insert(Dictionary *D, int studentID, char *name, float grade) {
    
    int count = 0;

    unsigned int h = hash(studentID);
    for(int i = 0; i < TABLE_SIZE; i++) {
        unsigned int idx = (h+i) % TABLE_SIZE;

        if (D->table[idx].isOccupied && D->table[idx].studentID == studentID){
            printf("Inserting failed! %d already exists\n", studentID);
            return false;
        } else if (D->table[idx].isOccupied == 0 || D->table[idx].isDeleted ==1) {
            strncpy(D->table[idx].name, name, sizeof(D->table[idx].name) -1);
            D->table[idx].grade = grade;
            D->table[idx].isDeleted =  0;
            D->table[idx].isOccupied = 1;
            D->table[idx].collisions = count;
            D->table[idx].studentID = studentID;
            return true;
        }
        count++;
    }
    return false;
}

// Search record
Entry* search(Dictionary *D, int studentID) {
    unsigned int h = hash(studentID);
    
    for(int i = 0; i < TABLE_SIZE; i++) {
        unsigned int index = (h+i) % TABLE_SIZE;


        if (D->table[i].studentID == studentID) {
            return &(D->table[i]);
        }
    }
    return NULL;
}

// Delete record
bool delete(Dictionary *D, int studentID) {
    unsigned int h = hash(studentID);

    for(int i = 0; i < TABLE_SIZE; i++) {
        unsigned int index = (h+i) % TABLE_SIZE;

        if (D->table[index].studentID == studentID) {
            D->table[index].grade = 0;
            D->table[index].studentID = 0;
            strcpy(D->table[index].name, "");
            D->table[index].isDeleted = true;
            D->table[index].isOccupied = false;
            D->table[index].collisions = 0;
            return true;
        }
    }
    return false;
}

// Display non-deleted entries
void display(Dictionary *D) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        printf("%d. -> ", i+1);
        if (D->table[i].isOccupied == 1) {
            printf("[%s, %d]\n", D->table[i].name, D->table[i].studentID);
        } else if (D->table[i].isDeleted == 1) {
            printf("[DELETED]\n");
        } else {
            printf("[EMPTY]\n");
        }
    }
}

// ====================== SET OPERATIONS =========================
Dictionary unionDict(Dictionary *A, Dictionary *B) {
    // 🧩 IMPLEMENT ME
    Dictionary R;
    initDictionary(&R);


    for(int i = 0; i < TABLE_SIZE; i++) {
        Entry a = A->table[i];

        unsigned int h = hash(a.studentID);
        for(int j = 0; j < TABLE_SIZE; j++) {
            int count = 0;
            unsigned int index = (h+j) % TABLE_SIZE;

            if (R.table[index].isOccupied && R.table[index].studentID == a.studentID) {
                break;
            } else if (a.isOccupied && R.table[index].isOccupied == 0 || R.table[index].isDeleted == 1) {
                R.table[index].studentID = a.studentID;
                strcpy(R.table[index].name, a.name);
                R.table[index].grade = a.grade;
                R.table[index].isDeleted = 0;
                R.table[index].isOccupied = 1;
                R.table[index].collisions = count;
                break;
            }
            count++;
        }
    }

    for(int k = 0; k < TABLE_SIZE; k++) {
       
        Entry a = B->table[k];
        unsigned int h = hash(a.studentID);

        for(int i=0;i<TABLE_SIZE; i++) {
             int count = 0;
            unsigned int index = (h+i) % TABLE_SIZE;

            if (R.table[index].isOccupied && R.table[index].studentID == a.studentID) {
                break;
            } else if (a.isOccupied && R.table[index].isOccupied == 0 || R.table[index].isDeleted == 1) {
                R.table[index].studentID = a.studentID;
                strcpy(R.table[index].name, a.name);
                R.table[index].grade = a.grade;
                R.table[index].isDeleted = 0;
                R.table[index].isOccupied = 1;
                R.table[index].collisions = count;
                break;
            }
            count++;
        }

    }



    return R;
}

Dictionary intersectDict(Dictionary *A, Dictionary *B) {
    // 🧩 IMPLEMENT ME
    Dictionary R;
    initDictionary(&R);

    for(int i = 0; i < TABLE_SIZE; i++) {
        Entry a = A->table[i];
        

        bool inB = false;

        for(int k = 0; k < TABLE_SIZE; k++) {
            if (B->table[k].studentID == a.studentID) {
                inB = true; break;
            }

        }

        if (inB) {
            int count = 0;
            for(int b = 0; b < TABLE_SIZE; b++) {
                unsigned int h = hash(a.studentID);
                unsigned int index = (h+b)% TABLE_SIZE;

                if (R.table[index].isOccupied && R.table[index].studentID == a.studentID) {
                    break;
                } else if (a.isOccupied && R.table[index].isOccupied == 0|| R.table[index].isDeleted ==1 ) {
                  R.table[index].studentID = a.studentID;
                strcpy(R.table[index].name, a.name);
                R.table[index].grade = a.grade;
                R.table[index].isDeleted = 0;
                R.table[index].isOccupied = 1;
                R.table[index].collisions = count;
                break;  
                }
                count++;
            }

        }
    }
    return R;
}

Dictionary differenceDict(Dictionary *A, Dictionary *B) {
    // 🧩 IMPLEMENT ME
    Dictionary R;
    initDictionary(&R);

    for(int i = 0; i < TABLE_SIZE; i++) {
        Entry a = A->table[i];
        

        bool inB = false;
            unsigned int h = hash(a.studentID);
        for(int k = 0; k < TABLE_SIZE; k++) {
            if (B->table[k].studentID == a.studentID) {
                inB = true; break;
            }

        }

        if (!inB) {
            int count = 0;
            for(int b = 0; b < TABLE_SIZE; b++) {
                
                unsigned int index = (h+b)% TABLE_SIZE;

                if (R.table[index].isOccupied && R.table[index].studentID == a.studentID) {
                    break;
                } else if (a.isOccupied && R.table[index].isOccupied == 0|| R.table[index].isDeleted ==1 ) {
                  R.table[index].studentID = a.studentID;
                strcpy(R.table[index].name, a.name);
                R.table[index].grade = a.grade;
                R.table[index].isDeleted = 0;
                R.table[index].isOccupied = 1;
                R.table[index].collisions = count;
                break;  
                }
                count++;
            }

        }
    }
    return R;
}

// // // ====================== SPECIAL ANALYTICS =========================
// // void clearCluster(Dictionary *D, int index) {
// //     // 🧩 IMPLEMENT ME
// // }

// // int getLongestCluster(Dictionary *D) {
// //     // 🧩 IMPLEMENT ME
// //     return 0;
// // }

// // int countTotalCollisions(Dictionary *D) {
// //     // 🧩 IMPLEMENT ME
// //     return 0;
// // }

// // // ====================== ADVANCED CHALLENGES =========================

// // // 🧮 Return new dictionary of students with grade above threshold
// // Dictionary topPerformers(Dictionary *D, float threshold) {
// //     // 🧩 IMPLEMENT ME
// //     Dictionary R;
// //     initDictionary(&R);
// //     return R;
// // }

// // // 🧩 Merge two dictionaries by same grade (unique by grade value)
// // Dictionary mergeSameGrade(Dictionary *A, Dictionary *B) {
// //     // 🧩 IMPLEMENT ME
// //     Dictionary R;
// //     initDictionary(&R);
// //     return R;
// // }

// // // ⚖️ Return symmetric difference (A ⊕ B)
// // Dictionary symmetricDifference(Dictionary *A, Dictionary *B) {
// //     // 🧩 IMPLEMENT ME
// //     Dictionary R;
// //     initDictionary(&R);
// //     return R;
// // }

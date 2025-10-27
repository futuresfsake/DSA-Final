/************************************************************
 👥 ADVANCED OPEN HASHING – PERSON DIRECTORY (Nested Structs)
*************************************************************

📘 CONTEXT:
You will implement a **Person Directory** using 
**Open Hashing (Separate Chaining)** with **nested structs**.

Each record stores:
   - id (int)
   - name (string)
   - age (int)
   - city (string)

The goal is to manage this directory like a set, supporting:
   ➤ Filter (age ≥ threshold)
   ➤ Union (A ∪ B)
   ➤ Intersection (A ∩ B)
   ➤ Difference (A − B)
   ➤ Equality check (A == B)

*************************************************************
📦 STRUCTURE DESIGN (NESTED)
-------------------------------------------------------------
Person → contains id, name, age, city  
Node   → contains Person and *next  
Bucket → contains *head  
Directory → array of Buckets  

*************************************************************
🧩 TASKS TO IMPLEMENT:
1️⃣ hash(id) → maps id to index  
2️⃣ initDirectory()  
3️⃣ insertPerson()  
4️⃣ displayDirectory()  
5️⃣ freeDirectory()

6️⃣ filterByAge(A, threshold)  
7️⃣ unionDirectory(A, B)  
8️⃣ intersectDirectory(A, B)  
9️⃣ differenceDirectory(A, B)
🔟 isEqualDirectory(A, B)

*************************************************************
🏁 GOAL:
Practice nested structs, hashing, memory handling, and 
set operations on structured data.
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 10

// ====================== STRUCTURES =========================

// Person data
typedef struct {
    int id;
    char name[50];
    int age;
    char city[30];
} Person;

// Node for linked list in each bucket
typedef struct Node {
    Person data;
    struct Node *next;
} Node;

// Bucket containing a list of Persons
typedef struct {
    Node *head;
} Bucket;

// Directory – an array of buckets
typedef struct {
    Bucket buckets[TABLE_SIZE];
} Directory;


// ====================== FUNCTION DECLARATIONS =========================
unsigned int hash(int id);
void initDirectory(Directory *D);
void insertPerson(Directory *D, int id, char *name, int age, char *city);
void displayDirectory(Directory *D);
void freeDirectory(Directory *D);

Directory filterByAge(Directory *A, int threshold);
Directory unionDirectory(Directory *A, Directory *B);
Directory intersectDirectory(Directory *A, Directory *B);
Directory differenceDirectory(Directory *A, Directory *B);
bool isEqualDirectory(Directory *A, Directory *B);


// ====================== MAIN FUNCTION =========================
int main() {
    Directory A, B, F, U, I, D;
    initDirectory(&A);
    initDirectory(&B);

    // Sample people in Directory A
    insertPerson(&A, 101, "Alice", 25, "Manila");
    insertPerson(&A, 102, "Bob", 40, "Cebu");
    insertPerson(&A, 103, "Charlie", 35, "Davao");
    insertPerson(&A, 104, "Diana", 20, "Baguio");

    // // Sample people in Directory B
    insertPerson(&B, 103, "Charlie", 35, "Davao");  // same as A
    insertPerson(&B, 105, "Eve", 42, "Manila");
    insertPerson(&B, 106, "Frank", 30, "Cebu");
    insertPerson(&B, 107, "Grace", 22, "Iloilo");
    insertPerson(&B, 101, "Alice", 25, "Manila");

    

    // insertPerson(&B, 101, "Alice", 25, "Manila");
    // insertPerson(&B, 102, "Bob", 40, "Cebu");
    // insertPerson(&B, 103, "Charlie", 35, "Davao");
    // insertPerson(&B, 104, "Diana", 20, "Baguio");

    printf("\n=== Directory A ===\n");
    displayDirectory(&A);

    // printf("\n=== Directory B ===\n");
    // displayDirectory(&B);

    printf("\n=== Filter (Age ≥ 30) ===\n");
    F = filterByAge(&A, 30);
    displayDirectory(&F);

    printf("\n=== UNION (A ∪ B) ===\n");
    U = unionDirectory(&A, &B);
    displayDirectory(&U);

    printf("\n=== INTERSECTION (A ∩ B) ===\n");
    I = intersectDirectory(&A, &B);
    displayDirectory(&I);

    printf("\n=== DIFFERENCE (A − B) ===\n");
    D = differenceDirectory(&A, &B);
    displayDirectory(&D);

    printf("\n=== EQUALITY TEST (A == B) ===\n");
    printf(isEqualDirectory(&A, &B) ? "Equal\n" : "Not Equal\n");

    // // Free all memory
    freeDirectory(&A);
    freeDirectory(&B);
    freeDirectory(&F);
    freeDirectory(&U);
    freeDirectory(&I);
    freeDirectory(&D);

    return 0;
}


// ====================== FUNCTION DEFINITIONS (Skeletons) =========================

// 🧮 Hash function – use id mod TABLE_SIZE
unsigned int hash(int id) {
    
    unsigned int h = (unsigned int)id;

    h ^= (h <<13);
    h ^=(h >>17);
    h ^= (h<<23);

    return (h + 31) % TABLE_SIZE;
}

// Initialize all buckets
void initDirectory(Directory *D) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        D->buckets[i].head = NULL;
    }
}

// Insert new person (avoid duplicates)
void insertPerson(Directory *D, int id, char *name, int age, char *city) {
    

    unsigned int index = hash(id);

    Node* trav = D->buckets[index].head;
    bool inD = false;
    
    while (trav != NULL) {
        if (trav->data.id == id) {
            inD = true;
            printf("Cannot insert! Person %d already exists!\n", id);
            
        }
        trav = trav->next;
    }


    if (!inD) {

        Node* new = malloc(sizeof(Node));
        strcpy(new->data.name, name);
        new->data.id = id;
        new->data.age = age;
        strcpy(new->data.city, city);
        new->next = D->buckets[index].head;
        D->buckets[index].head = new;
        printf("Inserted successfully!\n");
    }

    
}



// Display entire directory
void displayDirectory(Directory *D) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        printf("%d. ->", i+1);

        Node* trav = D->buckets[i].head;
        if (trav == NULL) {
            printf("EMPTY!\n");
        } else {

        while (trav) {
            printf("[%s, %d, %d] ->", trav->data.name, trav->data.id, trav->data.age);
            trav = trav->next;
        }

        printf("NULL\n");

    }
    }

}

// Free all allocated memory
void freeDirectory(Directory *D) {
    
    for(int i = 0; i < TABLE_SIZE; i++) {
        Node* temp = D->buckets[i].head;

        while (temp != NULL) {
            Node* ex = temp;
            temp = ex->next;
            free(ex);
        }

        D->buckets[i].head = NULL;

    }
}

// Filter all persons with age ≥ threshold
Directory filterByAge(Directory *A, int threshold) {
    Directory C;
    initDirectory(&C);


    for(int i = 0; i < TABLE_SIZE; i++) {
        Node* ptrA = A->buckets[i].head;

        while (ptrA) {

            if (ptrA->data.age >= threshold) {
                
                

                bool inC = false;
                unsigned int h = hash(ptrA->data.id);
                Node* trav = C.buckets[h].head;


                for(; trav != NULL; trav = trav->next) {
                    if (trav->data.id == ptrA->data.id) {
                        inC = true;
                        break;
                    }
                }


                if (!inC) {
                    Node* new = malloc(sizeof(Node));
                strcpy(new->data.name, ptrA->data.name);
                strcpy(new->data.city, ptrA->data.city);
                new->data.age = ptrA->data.age;
                new->data.id = ptrA->data.id;
                    new->next = C.buckets[h].head;
                    C.buckets[h].head = new;
                }
            }
            ptrA = ptrA->next;
        }
    }
    return C;
}

// Union of two directories (A ∪ B)
Directory unionDirectory(Directory *A, Directory *B) {
    
    Directory C;
    initDirectory(&C);

    for(int i = 0; i < TABLE_SIZE; i++) {
        Node* ptrA = A->buckets[i].head;

        for(; ptrA!= NULL; ptrA = ptrA->next) {
            
            unsigned int index = hash(ptrA->data.id);
            Node* ptrC = C.buckets[index].head;
            bool inC = false;
            for(; ptrC != NULL; ptrC = ptrC->next) {
                if (ptrC->data.id == ptrA->data.id) {
                    inC = true;
                    break;
                }
            }

            if (!inC) {
                Node* new = malloc(sizeof(Node));
                strcpy(new->data.city, ptrA->data.city);
                strcpy(new->data.name, ptrA->data.name);
                new->data.age = ptrA->data.age;
                new->data.id = ptrA->data.id;
                new->next = C.buckets[index].head;
                C.buckets[index].head = new;
            }
            
        }
    }



    for(int j = 0; j < TABLE_SIZE; j++) {
        Node* ptrA = B->buckets[j].head;

        

        for(; ptrA != NULL; ptrA = ptrA->next) {
            bool inC = false;
            unsigned int h = hash(ptrA->data.id);
            
            Node* ptrC = C.buckets[h].head;
            for(; ptrC != NULL; ptrC = ptrC->next) {
                if (ptrC->data.id == ptrA->data.id) {
                    inC = true;
                    break;
                }
            }



            if (!inC) {
                Node* new = malloc(sizeof(Node));
               
                strcpy(new->data.city, ptrA->data.city);
                strcpy(new->data.name, ptrA->data.name);
                new->data.age = ptrA->data.age;
                new->data.id = ptrA->data.id;
                new->next = C.buckets[h].head;
                C.buckets[h].head = new;
            }
        }
    }




    return C;
}

// Intersection of two directories (A ∩ B)
Directory intersectDirectory(Directory *A, Directory *B) {
    

    Directory C;
    initDirectory(&C);

    for(int i = 0; i < TABLE_SIZE; i++) {
        Node* ptrA = A->buckets[i].head;

        for(; ptrA != NULL; ptrA = ptrA->next) {

        bool inB = false;

        for(int j = 0; j < TABLE_SIZE; j++) {
        Node* ptrB = B->buckets[j].head;
        for(; ptrB != NULL; ptrB = ptrB->next) {
            if (ptrB->data.id == ptrA->data.id) {
                inB = true;
                break;
            }
        }

        }

        if (inB) {
            bool inC = false;


            unsigned int h = hash(ptrA->data.id);

            Node* ptrC = C.buckets[h].head;

            for(; ptrC != NULL; ptrC = ptrC->next) {
                if (ptrC->data.id == ptrA->data.id) {
                    inC = true;
                    break;
                }
            }

            if (!inC) {
            Node* new = malloc(sizeof(Node));
            strcpy(new->data.city, ptrA->data.city);
                strcpy(new->data.name, ptrA->data.name);
                new->data.age = ptrA->data.age;
                new->data.id = ptrA->data.id;
                new->next = C.buckets[h].head;
                C.buckets[h].head = new;
        }

    }
    
    }

}
    return C;
}

// Difference of two directories (A − B)
Directory differenceDirectory(Directory *A, Directory *B) {

    
    Directory C;
    initDirectory(&C);

    for(int i = 0; i < TABLE_SIZE; i++) {
        Node* ptrA = A->buckets[i].head;

        for(; ptrA != NULL; ptrA = ptrA->next) {

        bool inB = false;

        for(int j = 0; j < TABLE_SIZE; j++) {
        Node* ptrB = B->buckets[j].head;
        for(; ptrB != NULL; ptrB = ptrB->next) {
            if (ptrB->data.id == ptrA->data.id) {
                inB = true;
                break;
            }
        }

        }

        if (!inB) {
            bool inC = false;


            unsigned int h = hash(ptrA->data.id);

            Node* ptrC = C.buckets[h].head;

            for(; ptrC != NULL; ptrC = ptrC->next) {
                if (ptrC->data.id == ptrA->data.id) {
                    inC = true;
                    break;
                }
            }

            if (!inC) {
            Node* new = malloc(sizeof(Node));
            strcpy(new->data.city, ptrA->data.city);
                strcpy(new->data.name, ptrA->data.name);
                new->data.age = ptrA->data.age;
                new->data.id = ptrA->data.id;
                new->next = C.buckets[h].head;
                C.buckets[h].head = new;
        }

    }
    
    }

}
    return C;
    

}

// Equality test (same people in both)
bool isEqualDirectory(Directory *A, Directory *B) {
    
    
    for(int i = 0; i < TABLE_SIZE; i++) {
        Node* ptrA = A->buckets[i].head;

        while (ptrA) {
            bool found = false;

            unsigned int h = hash(ptrA->data.id);
            Node* ptrB = B->buckets[h].head;
            for(; ptrB!= NULL; ptrB = ptrB->next) {
                if (ptrB->data.id == ptrA->data.id) {
                    found = true;break;
                }
            }

            if (!found) return false;

            ptrA = ptrA->next;
        }
    }



    for(int j = 0; j < TABLE_SIZE; j++) {
        Node* ptrB = B->buckets[j].head;

        bool found = false;

        while (ptrB) {
            unsigned int h = hash(ptrB->data.id);

            Node* ptrA = A->buckets[h].head;

            for(; ptrA != NULL; ptrA = ptrA->next) {
                if (ptrB->data.id == ptrA->data.id) {
                    found = true;
                    break;
                }
            }

            if (!found) return false;
            ptrB = ptrB->next;
        }

        
    }
    return true;
}

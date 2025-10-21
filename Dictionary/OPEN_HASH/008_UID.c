/**********************************************
 🧠 REMINDERS for IMPLEMENTATION — OPEN HASHING
***********************************************

1️⃣  HASH FUNCTION
    - Use: sum of ASCII values of key characters
    - Formula: (sum of chars) % TABLE_SIZE
    - Ensures keys are distributed across buckets

2️⃣  INITIALIZATION
    - Set every table[i] = NULL
    - This means all chains are initially empty

3️⃣  INSERT (with chaining)
    - Compute index using hash(key)
    - Traverse the chain:
        • If key already exists → do NOT insert again
        • Else create a new Node and append it
    - Handle collisions by linking nodes (open hashing)

4️⃣  SEARCH
    - Compute index = hash(key)
    - Traverse chain:
        • If strcmp(node->key, key) == 0 → return value
    - If not found → return -1

5️⃣  DISPLAY
    - Loop through all buckets:
        • Print the index number
        • If table[i] == NULL → [EMPTY]
        • Else print every (key, value) pair in the chain

6️⃣  FREE DICTIONARY
    - Loop through each bucket
    - Free all linked list nodes to avoid memory leaks

7️⃣  UNION (A ∪ B)
    - Create a new dictionary `U`
    - Insert all elements from A
    - Insert all elements from B (duplicates ignored)

8️⃣  DIFFERENCE (A − B)
    - Create a new dictionary `D`
    - Insert keys from A that are NOT present in B

9️⃣  SYMMETRIC DIFFERENCE (A △ B)
    - Create a new dictionary `S`
    - Insert keys that appear in EXACTLY one of A or B
    - (i.e., in A but not in B, OR in B but not in A)

🔟  EDGE CASES
    - Handle empty dictionaries
    - Avoid duplicate keys
    - Always free memory after operations

**********************************************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 10

// Node for the linked list (chain)
typedef struct Node {
    char key[30];
    int value;
    struct Node *next;
} Node;

// Dictionary structure
typedef struct {
    Node *table[TABLE_SIZE];
} Dictionary;

// ===== Function Declarations =====

// Hash function
unsigned int hash(char *key) {
    unsigned int sum = 0;
    for(int i = 0; key[i] != '\0'; i++) {
        sum +=key[i];
    }
    return (sum+32) % TABLE_SIZE;

}

// Initialization
void initDictionary(Dictionary *D) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        
        D->table[i] = NULL;
    }
}

// Insert key-value pair (using chaining)
void insert(Dictionary *D, char *key, int value) {
    unsigned int index = hash(key);
    bool flag = false;


    for(int i = 0; i < TABLE_SIZE; i++) {
        Node* temp = (D)->table[index];

        while (temp != NULL) {
            if (strcmp(temp->key, key) == 0) {
                flag = true;                
            }
            temp = temp->next;
                 
        }

        if (!flag) {
            Node* new = malloc(sizeof(Node));
        strcpy(new->key, key);
        new->value = value;
        new->next = D->table[index];
        D->table[index] = new;
        printf("Successfully Inserted!\n");
        }
        
    }
}

// Search for a key
int search(Dictionary *D, char *key) {
    unsigned int h = hash(key);

    Node* temp = D->table[h];

    for(; temp != NULL; temp = temp->next) {
        if (strcmp(temp->key, key)==0){
            return 1;

        }
    }
    return -1;
}

// Display dictionary contents
void display(Dictionary *D) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        printf("%d. ->", i+1);


        Node* trav = D->table[i];
        if (trav == NULL) {
            printf("[EMPTY]\n");
        } else {
            while (trav != NULL) {
                printf("{%s, %d}-> ", trav->key, trav->value);
                trav = trav->next;
            }
            printf("NULL\n");
            
        }
        
    }

}

// Free all allocated memory
void freeDictionary(Dictionary *D) {

   
    for(int i = 0; i < TABLE_SIZE; i++) {
        Node* temp = D->table[i];

        while (temp != NULL) {
            Node* del = temp;
            temp = temp->next;
            free(del);
        }
        D->table[i] = NULL;
    }
}


void Remove (Dictionary *D, char* key) {

    int index = hash(key);

    Node** temp = &(D)->table[index];

    for(; *temp != NULL; temp = &(*temp)->next) {
        if(strcmp((*temp)->key, key)==0) {
            Node* toRemove = *temp;
            *temp = toRemove->next;
            
            printf("%s deleting...\n", toRemove->key);
            free(toRemove);
            return;
        }
    }
    printf("%s not found..\n", key);
}
// // ===== Set Operations =====

// ! yes it worked!!!
Dictionary unionDict(Dictionary *A, Dictionary *B) {
    Dictionary C;
    Node* tail = NULL;

    for(int i = 0; i < TABLE_SIZE; i++) {
        C.table[i] = NULL;
    }



    for(int i = 0; i < TABLE_SIZE; i++) {
        Node* tempA = A->table[i];


        while (tempA != NULL) {
            unsigned int index = hash(tempA->key);
            
           

            // ! decided to append to the end, so its structure is the same
            Node* newNode =malloc(sizeof(Node));
            newNode->value = tempA->value;
            strcpy(newNode->key, tempA->key);
            newNode->next = NULL;

            if (C.table[index] == NULL) {
                C.table[index] = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }

            tempA = tempA->next;
            
        }
    }



    for(int j = 0; j < TABLE_SIZE; j++) {
        Node* tempB = B->table[j];

        while (tempB != NULL) {
            unsigned int index = hash(tempB->key);
            bool inC = false;

            for(Node* trav = C.table[index]; trav != NULL; trav = trav->next) {
                if (strcmp(trav->key, tempB->key) == 0) {
                    inC = true;
                    break;
                }
            }


                if (!inC) {
                    Node* newB = malloc(sizeof(Node));
                    newB->value = tempB->value;
                    strcpy(newB->key, tempB->key);
                    newB->next= NULL;


                    if (C.table[index] == NULL) {
                        C.table[index] = newB;
                        tail = newB;
                    } else {
                        tail->next = newB;
                        tail = newB;
                    }
                
            }

            tempB = tempB->next;
            
        }
    }
    return C;
}


// ! still appended to the end to keep the same structure

Dictionary differenceDict(Dictionary *A, Dictionary *B) {

    Dictionary C;
    for(int i = 0; i < TABLE_SIZE; i++) {
        C.table[i] = NULL;
    }
   
    for(int j = 0; j < TABLE_SIZE; j++) {
        Node* ptrA = A->table[j];
        


        while (ptrA) {
            unsigned int index = hash(ptrA->key);
            bool inB = false;

            for(Node* trav = B->table[index]; trav != NULL ; trav = trav->next) {
                if (strcmp(trav->key, ptrA->key) ==0) {
                    inB = true;
                    break;
                }
            }

            if (!inB) {
                bool inC = false;
                for(Node* trav2 = C.table[index]; trav2 != NULL; trav2= trav2->next) {
                    if (strcmp(trav2->key, ptrA->key) ==0) {
                        inC = true;
                        break;
                    }
                }
              
            if (!inC) {
                Node* newNode = malloc(sizeof(Node));
                if (newNode) {
                    Node* tail = NULL;

                  
                    newNode->value=ptrA->value;
                    strcpy(newNode->key, ptrA->key);
                    newNode->next =NULL;

                    if (C.table[index]== NULL) {
                        C.table[index] = newNode; 
                        tail = newNode;
                    } else {
                        Node* trav = C.table[index];
                        while (trav->next != NULL) {
                            trav = trav->next;
                        }
                        trav->next = newNode;
                        
                    }

                   
                }
            }
            
        }

          ptrA = ptrA->next;
        }

        
    }
    return C;
}


Dictionary IntersectDict(Dictionary *A, Dictionary *B) {

    Dictionary C;
    for(int i = 0; i < TABLE_SIZE; i++) {
        C.table[i] = NULL;
    }
   
    for(int j = 0; j < TABLE_SIZE; j++) {
        Node* ptrA = A->table[j];
        


        while (ptrA) {
            unsigned int index = hash(ptrA->key);
            bool inB = false;

            for(Node* trav = B->table[index]; trav != NULL ; trav = trav->next) {
                if (strcmp(trav->key, ptrA->key) ==0) {
                    inB = true;
                    break;
                }
            }

            if (inB) {
                bool inC = false;
                for(Node* trav2 = C.table[index]; trav2 != NULL; trav2= trav2->next) {
                    if (strcmp(trav2->key, ptrA->key) ==0) {
                        inC = true;
                        break;
                    }
                }
              
            if (!inC) {
                Node* newNode = malloc(sizeof(Node));
                if (newNode) {
                    Node* tail = NULL;

                  
                    newNode->value=ptrA->value;
                    strcpy(newNode->key, ptrA->key);
                    newNode->next =NULL;

                    if (C.table[index]== NULL) {
                        C.table[index] = newNode; 
                        tail = newNode;
                    } else {
                        Node* trav = C.table[index];
                        while (trav->next != NULL) {
                            trav = trav->next;
                        }
                        trav->next = newNode;
                        
                    }

                   
                }
            }
            
        }

          ptrA = ptrA->next;
        }

        
    }
    return C;
}


// Dictionary symDiffDict(Dictionary *A, Dictionary *B);

// ===== Main Function =====
int main() {

    Dictionary A, B, U, D, S;
    initDictionary(&A);
    initDictionary(&B);

     // Insert data into dictionary A
    insert(&A, "apple", 10);
    insert(&A, "banana", 20);
    insert(&A, "mango", 30);
    insert(&A, "orange", 40);
    insert(&A, "grape", 50);
    insert(&A, "kiwi", 60);
    insert(&A, "plum", 70);

    // Insert data into dictionary B
    insert(&B, "banana", 15);
    insert(&B, "cherry", 25);
    insert(&B, "apple", 35);
    insert(&B, "melon", 45);
    insert(&B, "peach", 55);
    insert(&B, "grape", 65);
    insert(&B, "plum", 75);


    // printf("\n--- Dictionary A ---\n");
    // display(&A);

    // printf("\n--- Dictionary B ---\n");
    // display(&B);

    // char* remove = "grape";
    // Remove(&A, "grape");
    // printf("After Removing %s...\n", remove);
    // printf("\n--- Dictionary A ---\n");
    // display(&A);



   
    printf("\n=== UNION (A ∪ B) ===\n");
     U = unionDict(&A, &B);
    display(&U);

    // Perform Difference
    printf("\n=== DIFFERENCE (A − B) ===\n");
     D = differenceDict(&A, &B);
    display(&D);

    // Perform Symmetric Difference
    printf("\n===  INTERSECT (A △ B) ===\n");
    S = IntersectDict(&A, &B);
    display(&S);

    // Cleanup memory
    freeDictionary(&A);
    freeDictionary(&B);
    freeDictionary(&U);
   

    return 0;
}

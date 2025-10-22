#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10
#define KEY_LEN 30

// ===== STRUCTURES =====
typedef struct Node {
    char key[KEY_LEN];
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *table[MAX];
} Dictionary;

// ===== FUNCTION DECLARATIONS =====

// Hashing
unsigned int hash(char *key);

// Basic dictionary operations
void initDictionary(Dictionary *D);
void insert(Dictionary *D, char *key, int value);
void display(Dictionary *D);
void freeDictionary(Dictionary *D);

// // Set operations
Dictionary unionDict(Dictionary *A, Dictionary *B);
Dictionary intersectionDict(Dictionary *A, Dictionary *B);
Dictionary differenceDict(Dictionary *A, Dictionary *B);
// Dictionary symDiffDict(Dictionary *A, Dictionary *B);

// ===== MAIN FUNCTION =====
int main() {
    Dictionary A, B, U, I, D, S;

    initDictionary(&A);
    initDictionary(&B);

    // Populate A
    insert(&A, "apple", 10);
    insert(&A, "banana", 20);
    insert(&A, "mango", 30);
    insert(&A, "peach", 55);
    insert(&A, "cherry", 45);

    // Populate B
    insert(&B, "banana", 15);
    insert(&B, "cherry", 25);
    insert(&B, "apple", 35);
    insert(&B, "plum", 75);
    insert(&B, "grape", 65);

    printf("=== DICTIONARY A ===\n");
    display(&A);
    printf("\n=== DICTIONARY B ===\n");
    display(&B);

    // Perform set operations
    printf("\n=== UNION (A ∪ B) ===\n");
    U = unionDict(&A, &B);
    display(&U);

    printf("\n=== INTERSECTION (A ∩ B) ===\n");
    I = intersectionDict(&A, &B);
    display(&I);

    printf("\n=== DIFFERENCE (A - B) ===\n");
    D = differenceDict(&A, &B);
    display(&D);

    // printf("\n=== SYMMETRIC DIFFERENCE (A △ B) ===\n");
    // S = symDiffDict(&A, &B);
    // display(&S);

    // // Cleanup
    // freeDictionary(&A);
    // freeDictionary(&B);
    // freeDictionary(&U);
    // freeDictionary(&I);
    // freeDictionary(&D);
    // freeDictionary(&S);

    // return 0;
}

unsigned int hash(char *key) {
    unsigned int  sum = 0; 

    for(int i = 0; key[i] != '\0'; i++) {
        sum+=key[i];
    }
    return (sum+31) % MAX;
}


// Basic dictionary operations
void initDictionary(Dictionary *D) {
    for(int i = 0; i < MAX; i++) {
        (D)->table[i] = NULL;
    }
}

void insert(Dictionary *D, char *key, int value) {
    
    unsigned int index = hash(key);

    Node* trav = D->table[index];
    bool found = false;

    for(; trav != NULL; trav = trav->next) { 
        if (strcmp(trav->key, key) == 0) {
            found = true;
            printf("%s already exists. No duplicates allowed.",key);
            return;
    
        }
    }

        if (!found) {
            Node* new = malloc(sizeof(Node));
            if (!new) {
                printf("Dynamic Memory allocation failed!\n");
            }
            strcpy(new->key, key);
            new->value = value;
            new->next = D->table[index];
            D->table[index] = new;


        } else {
            printf("%s Unable to insert, it is already present.\n", key);
        }

    
}

void display(Dictionary *D) {

    for(int i = 0; i < MAX; i++) {
        printf("%d.->", i+1);

        Node* trav = D->table[i];

        if (trav == NULL) {
            printf("[EMPTY]");
        }
        while (trav != NULL) {
            printf("{%s, %d}->", trav->key, trav->value);
            trav = trav->next;
            
        }
        printf("NULL\n");

    }
}
void freeDictionary(Dictionary *D) {

    Node* temp;

    for(int i = 0; i < MAX; i++) {
        temp = D->table[i];

        while (temp != NULL) {
            Node* test = temp;
            temp = temp->next;
            free(test);
        }
        D->table[i] = NULL;
    }
}

// Set operations
Dictionary unionDict(Dictionary *A, Dictionary *B) {

    Dictionary U;
    initDictionary(&U);
    Node* tail = NULL;


    for(int i = 0; i < MAX; i++) {
        
        Node* ptrA = A->table[i];

        while (ptrA) {
            unsigned int index = hash(ptrA->key);
            
            Node* new = malloc(sizeof(Node));
            if (!new) {
                printf("Dynamic Memory allocation failed.\n");
                return U;
            }
            strcpy(new->key, ptrA->key);
            new->value = ptrA->value;
            new->next = NULL;

            if (U.table[index] == NULL) {
                U.table[index] = new;
                tail = new;
            } else {
                tail->next = new;
                tail = new;
            }


            ptrA = ptrA->next;

        }   
    }


    for(int j = 0; j < MAX; j++) {
        Node* ptrB = B->table[j];

        while (ptrB) {
            unsigned int index = hash(ptrB->key);
            bool inC = false;

            Node* travU = U.table[index];

            for(; travU!= NULL; travU = travU->next) {
                if (strcmp(travU->key, ptrB->key) == 0) {
                    inC = true;
                    break;
                }
            }

            if (!inC) {
                Node* new = malloc(sizeof(Node));
                if (!new) {printf("Dynamic memory allocation failed.\n");}
                strcpy(new->key, ptrB->key);
                new->value = ptrB->value;
                new->next = NULL;

                if (U.table[index] == NULL) {
                    U.table[index] = new;
                    tail = new;
                } else {
                    tail->next = new;
                    tail = new;
                }
            }

            ptrB = ptrB->next;
            
        }
    }
    return U;

}



Dictionary intersectionDict(Dictionary *A, Dictionary *B) {
    Dictionary C;
    initDictionary(&C);

    for(int i = 0; i < MAX; i++) {
        Node* ptrA = A->table[i];


        while (ptrA) {
            unsigned int index = hash(ptrA->key);
            bool inB = false;

            Node* ptrB = B->table[index];
            for(; ptrB!= NULL; ptrB = ptrB->next) {
                if (strcmp(ptrB->key, ptrA->key) == 0) {
                    inB = true;
                    break;
                }
            }

            if (inB) {
                bool inC = false;
                Node* travU = C.table[index];
                for(; travU != NULL; travU = travU->next) {
                    if (strcmp(travU->key, ptrA->key) == 0) {
                        inC = true;
                        break;
                    }
                }

                if (!inC) {
                    Node* new = malloc(sizeof(Node));
                    strcpy(new->key, ptrA->key);
                    new->value = ptrA->value;
                    new->next = NULL;

                    if (C.table[index] == NULL) {
                        C.table[index] = new;

                    } else {
                        Node* t = C.table[index];
                        while (t->next != NULL) {
                            t = t->next;
                        }
                        t->next = new;
                    }
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
        Node* ptrA = A->table[i];


        while (ptrA) {
            unsigned int index = hash(ptrA->key);
            bool inB = false;

            Node* ptrB = B->table[index];
            for(; ptrB!= NULL; ptrB = ptrB->next) {
                if (strcmp(ptrB->key, ptrA->key) == 0) {
                    inB = true;
                    break;
                }
            }

            if (!inB) {
                bool inC = false;
                Node* travU = C.table[index];
                for(; travU != NULL; travU = travU->next) {
                    if (strcmp(travU->key, ptrA->key) == 0) {
                        inC = true;
                        break;
                    }
                }

                if (!inC) {
                    Node* new = malloc(sizeof(Node));
                    strcpy(new->key, ptrA->key);
                    new->value = ptrA->value;
                    new->next = NULL;

                    if (C.table[index] == NULL) {
                        C.table[index] = new;

                    } else {
                        Node* t = C.table[index];
                        while (t->next != NULL) {
                            t = t->next;
                        }
                        t->next = new;
                    }
                }
            }

            ptrA = ptrA->next;
        }
    }

    return C;
}

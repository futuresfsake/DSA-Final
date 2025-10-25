// ** merging is like union, you check for duplicates, 
// * ou transfer it into a destination which is also a dictionary

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 17

// === Nested Structs ===
typedef struct Entry {
    char key[30];
    int value;
    struct Entry *next;   // Linked list (for chaining)
} Entry;

typedef struct {
    Entry *head;          // Each bucket is a linked list
} Bucket;

typedef struct {
    Bucket buckets[MAX];   // Hash table of buckets
} Dictionary;

// === Function Declarations ===
void initDictionary(Dictionary *D);
unsigned int hash(char *key);
void insert(Dictionary *D, char *key, int value);
void display(Dictionary *D);
void deleteKey(Dictionary *D, char *key);
int search(Dictionary *D, char *key);
void merge(Dictionary *dest, Dictionary *src);

// === MAIN DRIVER ===
int main() {
    Dictionary D1, D2;
    initDictionary(&D1);
    initDictionary(&D2);

     // Department A
    insert(&D1, "Alice", 101);
    insert(&D1, "Bob", 102);
    insert(&D1, "Clara", 103);
    insert(&D1, "David", 104);

    // Department B
    insert(&D2, "Eve", 201);
    insert(&D2, "Frank", 202);
    insert(&D2, "Bob", 999);   // Duplicate name to test collision
    insert(&D2, "Grace", 203);


       // Class A
    insert(&D1, "Mika", 89);
    insert(&D1, "Ramon", 76);
    insert(&D1, "Kyla", 93);
    insert(&D1, "Troy", 82);

    // Class B
    insert(&D2, "Ramon", 80); // duplicate key test
    insert(&D2, "Bea", 95);
    insert(&D2, "Liam", 70);
    insert(&D2, "Yuna", 88);



    display(&D1);
    display(&D2);



    // int grade2 = search(&D1, "David");
    // if (grade2 > 0) {
    // printf("Grade of David is %d", grade2);
    // } else {
    //     printf("Student not found.\n");
    // }

    // int grade1 = search(&D1, "BebuNa");
    // if (grade1 > 0) {
    // printf("Grade of BebuNa is %d", grade1);
    // } else {
    //     printf("Student not found.\n");
    // }



   
    // printf("After deleting Bebu\n"); deleteKey(&D2, "Bebu");
    //   display(&D2);


    // TODO: Merge, search, delete tests
    merge(&D1, &D2);

    display(&D1);

    return 0;
}

// === FUNCTION DEFINITIONS (You will implement) ===

// Initialize all buckets
void initDictionary(Dictionary *D) {

    for(int i = 0; i < MAX; i++) {
        D->buckets[i].head = NULL;
    }
    printf("Successfull ");

}

// Hash function (string to index)
unsigned int hash(char *key) {

    unsigned int sum=0;

    for(int i = 0; key[i] != '\0'; i++) {
        sum += key[i] * 31;
    }

    return sum % MAX;
}

// Insert key-value pair
void insert(Dictionary *D, char *key, int value) {


    unsigned int index = hash(key);

    Entry* trav = D->buckets[index].head;


    for (;trav != NULL; trav = trav->next) {
        if (strcmp(trav->key, key) ==0) {
            printf("Key already exists!\n");
            return;
        }
    }


    Entry* newNode = malloc(sizeof(Entry));
    if (!newNode) {
        printf("Dynamic memory allocation failed!\n");
        return;
    } 
    
    strcpy(newNode->key, key);
        newNode->value = value;
        newNode->next = D->buckets[index].head;
        D->buckets[index].head = newNode;

    
    }

// Display dictionary contents (organized + formatted)
void display(Dictionary *D) {
    printf("\n=======  DICTIONARY CONTENTS =======\n");

    for (int i = 0; i < MAX; i++) {
        printf("Bucket[%02d]: ", i);   // two-digit index for alignment

        Entry *trav = D->buckets[i].head;

        if (trav == NULL) {
            printf("[EMPTY]\n");
        } else {
            while (trav != NULL) {
                printf("{%s, %d} -> ", trav->key, trav->value);
                trav = trav->next;
            }
            printf("NULL\n");
        }
    }

    printf("=====================================\n");
}


// Search for a key, return its value (or -1 if not found)
int search(Dictionary *D, char *key) {

    unsigned int i = hash(key);

    Entry* trav = D->buckets[i].head;


    for(;trav != NULL; trav = trav->next) {
        if (strcmp(trav->key, key) ==0) {
            return trav->value;
        }
    }

    return 0;
}

// Delete a key from dictionary
void deleteKey(Dictionary *D, char *key) {

    unsigned int sum = hash(key);

    for(Entry** trav = &(D->buckets[sum].head); *trav != NULL; trav = &(*trav)->next) {
        if (strcmp((*trav)->key, key) ==0) {
            Entry* toRemove = *trav;
            *trav = toRemove->next;
            printf("%s successfully deleting...\n", toRemove->key);
            free(toRemove);return;
        }

    }

    printf("%s not on the list...\n", key);
}

// Merge two dictionaries (copy src into dest)
void merge(Dictionary *dest, Dictionary *src) {

    for(int i = 0; i < MAX; i++) {
        Entry* ptrB = src->buckets[i].head;
       

        while (ptrB) {
            unsigned int index = hash(ptrB->key);

            Entry* ptrA = dest->buckets[index].head;

             bool inA = false; // ! always make sure that your flag is inside the loop so it 
             // ! will be used corfrectly durig the iterations


            

            while (ptrA != NULL) {
                if (strcmp(ptrA->key, ptrB->key) == 0) {
                    inA = true;
                    break;
                }

                ptrA = ptrA->next;
            }




            if (!inA) {
                Entry* new = malloc(sizeof(Entry));
                if (!new) {printf("Dynamic memory allocation failed!");}

                strcpy(new->key, ptrB->key);
                new->value = ptrB->value;
                new->next = dest->buckets[index].head;
                dest->buckets[index].head = new;

            }

            ptrB = ptrB->next;
               
            }
            

        }

        }
    



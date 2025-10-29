
// Instruction (in words):
// 1. Start with a buffer of 0.
// 2. For each character in the string:
//      → Shift the current buffer left by 5 bits (multiply by 32).
//      → Add the ASCII value of the current character to the buffer.
// 3. After processing all characters, take the result modulo the table size
//    to get the final hash index.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 10

typedef struct Node {
    char key[30];
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *table[TABLE_SIZE];
} Dictionary;

// FUNCTION DECLARATIONS
unsigned int hash(char *key);
void insertSorted(Dictionary *D, char *key, int value);
bool deleteKey(Dictionary *D, char *key);
void display(Dictionary D);



// MAIN FUNCTION (testing area)
int main(void) {
    // 1) Init dictionary buckets to NULL
    Dictionary D;
    for (int i = 0; i < TABLE_SIZE; i++) {
        D.table[i] = NULL;
    }

    // 2) Insert some (key, value) pairs
    insertSorted(&D, "Adele", 100);
    insertSorted(&D, "Beatles", 200);
    insertSorted(&D, "Dua Lipa", 150);
    insertSorted(&D, "Jazz", 77);
    insertSorted(&D, "Pop", 88);
    insertSorted(&D, "Rock", 99);

    printf("=== After Inserts ===\n");
    display(D);

    // 3) Delete a key and display again
    printf("\nDeleting key: Beatles\n");
    if (deleteKey(&D, "Beatles")) {
        printf("Delete success.\n");
    } else {
        printf("Delete failed (not found).\n");
    }

    printf("\n=== After Delete ===\n");
    display(D);

    // 4) Free all nodes before exit
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *curr = D.table[i];
        while (curr) {
            Node *tmp = curr;
            curr = curr->next;
            free(tmp);
        }
        D.table[i] = NULL;
    }

    return 0;
}


// Instruction (in words):
// 1. Start with a buffer of 0.
// 2. For each character in the string:
//      → Shift the current buffer left by 5 bits (multiply by 32).
//      → Add the ASCII value of the current character to the buffer.
// 3. After processing all characters, take the result modulo the table size
//    to get the final hash index.

// HASH FUNCTION (given)
unsigned int hash(char *key) {
    
    unsigned int buffer = 0;
    for(int i = 0; key[i] != '\0'; i++) {
        buffer = (buffer<<5) + key[i];
    }

    return   buffer% TABLE_SIZE;
}






void insertSorted(Dictionary *D, char *key, int value) {
    
    unsigned int h = hash(key);
    Node* ptrA = D->table[h];
    bool inD = false;

    for(; ptrA != NULL; ptrA = ptrA->next) {
        if (ptrA->key == key) {
            inD=true;
            break;
        }
    }

    Node* new = malloc(sizeof(Node));
    strcpy(new->key, key);
    new->value = value;
    new->next = D->table[h];
    D->table[h] = new;


}

bool deleteKey(Dictionary *D, char *key) {

    unsigned int index = hash(key);
    Node** ptrA = &(D->table[index]);
    for(; *ptrA != NULL; ptrA = &(*ptrA)->next) {
        if (strcmp((*ptrA)->key, key)==0) {
            Node* R = *ptrA;
            *ptrA = R->next;
            free(R);
            return true;
        }
    }
    return false;
}
void display(Dictionary D) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        printf("[INDEX][%d]->", i);

        Node* trav = D.table[i];
        if (trav == NULL) {
            printf("EMPTY\n");
        } else {
            while (trav) {
                printf("[%s, %d]->", trav->key, trav->value);
                trav = trav->next;
            }
            printf("NULL\n");
        }

    }
}


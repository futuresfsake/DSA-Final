#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 11
#define MAX_VAL_LEN 50

// ============================
//      SLOT STATE ENUM
// ============================
typedef enum {
    EMPTY,      // never used
    OCCUPIED,   // has valid data
    DELETED     // tombstone
} SlotState;

// ============================
//      HASH TABLE ENTRY
// ============================
typedef struct {
    int key;
    char value[MAX_VAL_LEN];
    SlotState state;
} Entry;

// ============================
//      HASH TABLE STRUCT
// ============================
typedef struct {
    Entry table[TABLE_SIZE];
    int count;       // active entries
    int deleted;     // tombstones
} HashTable;

// ============================
//      FUNCTION PROTOTYPES
// ============================

// initialization
void initHashTable(HashTable *ht);

// hash functions
int hash1(int key);
int hash2(int key);          // used only for double hashing

// probing step function (linear / quadratic / double)
int probe(int baseIndex, int attempt);

// core operations
bool insert(HashTable *ht, int key, const char *value);
char* search(HashTable *ht, int key);
bool deleteKey(HashTable *ht, int key);

// side operations
bool isFull(HashTable *ht);
double loadFactor(HashTable *ht);
void rehash(HashTable *ht);

// display
void displayTable(HashTable *ht);

// ============================
//      MAIN (EXAMPLE ONLY)
// ============================
int main() {
    HashTable ht;
    initHashTable(&ht);

    insert(&ht, 10, "Alice");
    insert(&ht, 21, "Bob");
    insert(&ht, 32, "Charlie");

    displayTable(&ht);

    char *res = search(&ht, 21);
    if (res)
        printf("FOUND: %s\n", res);
    else
        printf("NOT FOUND\n");

    deleteKey(&ht, 21);
    displayTable(&ht);

    return 0;
}

// ============================
//   EMPTY FUNCTION BODIES
// ============================

// initialization
void initHashTable(HashTable *ht) {
    
    for(int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i].state = 0;
    }

    ht->count = 0;
    ht->deleted = 0;
}

// basic hash
int hash1(int key) {
   
    return key % TABLE_SIZE;

}




// INSERT (CLOSED HASHING)
bool insert(HashTable *ht, int key, const char *value) {
    
    int index = hash1(key);
    for(int i = 0; i < TABLE_SIZE; i++) {
        int h = (i + index) % TABLE_SIZE;

        if (ht->table[h].state == 1 && ht->table[h].key == key) {
            printf("Key already exists!...\n");
            return false;
        }

        if (ht->table[h].state == 0) {
            ht->table[h].key = key;
            strcpy(ht->table[h].value, value);
            ht->table[h].state = 1;

            ht->count++;

            return true;
        }

        if (ht->table[h].state == 2) {
            ht->table[h].key = key;
            strcpy(ht->table[h].value, value);
            ht->table[h].state = 1;

            ht->count++;
            ht->deleted--;
            return true;
            
        }
    }
    return false;
}

// SEARCH
char* search(HashTable *ht, int key) {
    
    int index = hash1(key);
    for(int i = 0; i < TABLE_SIZE; i++) {

        int h = (i + index) % TABLE_SIZE;

        if (ht->table[h].state == 1 && ht->table[h].key == key)  {
            return ht->table[h].value;
        }
    }

    return NULL;
}

// DELETE
bool deleteKey(HashTable *ht, int key) {

    int index = hash1(key);

    for(int i = 0; i < TABLE_SIZE; i++) {
        int h = (i + index) % TABLE_SIZE;


        if (ht->table[h].state == 1 && ht->table[h].key == key) {
            ht->table[h].state = 2;
            strcpy(ht->table[h].value, "");
            ht->table[h].key = -1;

            ht->deleted++;
            return true;
        }
    }
    
    return false;
}



// display
void displayTable(HashTable *ht) {
    printf("\nHash Table Contents:\n");
    printf("-------------------\n");

    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Slot %2d: ", i);
        if (ht->table[i].state == OCCUPIED) {
            printf("Key=%d, Value=%s\n", ht->table[i].key, ht->table[i].value);
        } else if (ht->table[i].state == DELETED) {
            printf("<deleted>\n");
        } else { // EMPTY
            printf("<empty>\n");
        }
    }
    printf("\n");
}


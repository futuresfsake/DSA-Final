#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 11      // you may change this
#define MAX_VALUE_LEN 100  // fixed length for stored strings

// ============================
//       ENUM / STRUCTS
// ============================

typedef enum {
    EMPTY,
    OCCUPIED,
    DELETED
} SlotState;

typedef struct {
    int key;
    char value[MAX_VALUE_LEN];
    SlotState state;
} HashEntry;

typedef struct {
    HashEntry table[TABLE_SIZE];
    int size;
} HashTable;

// ============================
//      FUNCTION HEADERS
// ============================

// Initialization
void initHashTable(HashTable *ht) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i].state = 0;
    }
    ht->size = 0;
}

// Hash + probing
int hash(int key) {
    return key % TABLE_SIZE;
}



// Core operations (NO LOGIC)
bool insert(HashTable *ht, int key, const char *value) {

    int index = hash(key);
    for(int i = 0; i < TABLE_SIZE; i++) {
        int h = (index + i) % TABLE_SIZE;

        if (ht->table[h].state == 1 && ht->table[h].key == key) {
            return false;
        } else if (ht->table[h].state == 0 || ht->table[h].state == 2) {
            ht->table[h].state = 1;
            ht->table[h].key = key;
            strcpy(ht->table[h].value, value);
            return true;
        }
    }
    return false;
}
char* search(HashTable *ht, int key) {
    int index = hash(key);
    for(int i = 0; i < TABLE_SIZE; i++) {
        int h = (index + i) % TABLE_SIZE;

        if (ht->table[h].state == 1 && ht->table[h].key == key) {
            return (ht->table[h].value);
        }
    }
    return NULL;
}


bool delete(HashTable *ht, int key) {
    int index = hash(key);
    for(int i = 0; i <TABLE_SIZE; i++) {
        int h = (index +i) % TABLE_SIZE;

        if (ht->table[h].state == 1 && ht->table[h].key == key) {
            ht->table[h].state = 2;
            ht->table[h].key = 0;
            strcpy(ht->table[h].value, "");
            return true;
        }
    }
    return false;
}

void display(HashTable *ht) {
    printf("\n===== HASH TABLE =====\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%2d] : ", i);

        if (ht->table[i].state == EMPTY) {
            printf("EMPTY\n");
        }
        else if (ht->table[i].state == DELETED) {
            printf("DELETED\n");
        }
        else if (ht->table[i].state == OCCUPIED) {
            printf("Key=%d, Value=%s\n",
                   ht->table[i].key,
                   ht->table[i].value);
        }
    }
    printf("======================\n\n");
}

int main() {
    HashTable ht;
    initHashTable(&ht);

    // Example calls (will work after you implement them)
    insert(&ht, 10, "Alice");
    insert(&ht, 21, "Bob");
    insert(&ht, 32, "Charlie");

    display(&ht);

    char *result = search(&ht, 21);
    if (result)
        printf("Found: %s\n", result);

    delete(&ht, 21);
    display(&ht);

    return 0;
}

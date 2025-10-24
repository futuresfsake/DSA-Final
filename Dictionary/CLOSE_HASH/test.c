/*
PROBLEM: Closed Hashing Dictionary using Quadratic Probing

Implement a simple dictionary that stores (key, value) pairs in a hash table.
Use CLOSED HASHING (Open Addressing) with QUADRATIC PROBING for collision resolution.

You must implement:
  1) void initDict(Dictionary *D)
  2) int hash(char *key)
  3) bool insert(Dictionary *D, char *key, char *value)
  4) bool delete(Dictionary *D, char *key)
  5) char* search(Dictionary *D, char *key)
  6) void display(Dictionary *D)

Expected operations:
  - Collisions are resolved using: index = (hash(key) + i*i) % MAX
  - A deleted entry is marked specially to allow continued probing
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 11      // Table size (use a small prime for simplicity)
#define EMPTY 0
#define OCCUPIED 1
#define DELETED 2

// === Entry and Dictionary Structures ===
typedef struct {
    char key[100];
    char value[100];
    int status;   // EMPTY, OCCUPIED, DELETED
} Entry;

typedef struct {
    Entry table[MAX];
    int count;
} Dictionary;

// === Function Declarations ===
void initDict(Dictionary *D);
int hash(char *key);
bool insert(Dictionary *D, char *key, char *value);
bool delete(Dictionary *D, char *key);
char* search(Dictionary *D, char *key);
void display(Dictionary *D);

// === Main Driver ===
int main() {
    Dictionary D;
    initDict(&D);

    // Test inserts
   // Test inserts
insert(&D, "apple", "red");
insert(&D, "banana", "yellow");
insert(&D, "grape", "purple");
insert(&D, "lemon", "yellow");
insert(&D, "orange", "orange");
insert(&D, "cherry", "red");
insert(&D, "kiwi", "green");
insert(&D, "watermelon", "green");
insert(&D, "blueberry", "blue");   // ! not inserted
insert(&D, "peach", "pink");
insert(&D, "plum", "purple");

    printf("\n=== After Insertions ===\n");
    display(&D);

    char *val = search(&D, "banana");
    if (val != NULL) printf("\nFound 'banana': %s\n", val);
    else printf("\n'banana' not found\n");

    // Test delete
    delete(&D, "apple");

    printf("\n=== After Deletion ===\n");
    display(&D);

    return 0;
}

// === Function Definitions (You will implement these) ===

// Initialize dictionary
void initDict(Dictionary *D) {
    // TODO: mark all slots as EMPTY

    for(int i = 0; i < MAX ; i++) {
        D->table[i].status = 0;
        strcpy(D->table->value, "");
        strcpy(D->table[i].key, "");
    }

    D->count = 0;
 
}

// Simple hash function (you may change logic if desired)
int hash(char *key) {
      unsigned long hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }

    return hash % MAX;
}

// Insert key-value pair using quadratic probing
bool insert(Dictionary *D, char *key, char *value) {
    // TODO: implement quadratic probing logic

    if (D->count == MAX) {
        return false;
    }

    int h = hash(key);

    for(int i = 0; i < MAX; i++) {
        int index = (h + i * i) % MAX;


        if (D->table[index].status == 1 && strcmp(D->table[index].key, key) == 0) {
            return false;
        } else if (D->table[index].status == 0) {
            D->table[index].status = 1;
            strcpy(D->table[index].value, value);
            strcpy(D->table[index].key, key);
            D->count++;
            return true;

        } else if (D->table[index].status == 2) {
            D->table[index].status = 1;
            strcpy(D->table[index].value, value);
            strcpy(D->table[index].key, key);
            D->count++;
            return true;
        }
    }
    return false;
}

// Delete key by marking slot as DELETED
bool delete(Dictionary *D, char *key) {
    

    if (D->count == 0) {
        return false;
    }

    int h = hash(key);

    for(int i = 0; i < MAX; i++) {
        int index = (h + i * i) % MAX;


        if (D->table[index].status == 1 && strcmp(D->table[index].key, key) ==0) {
            D->table[index].status = 2;
            strcpy(D->table[index].value, "");
            strcpy(D->table[index].key, "");
            D->count --;
            return true;
        }
    }
    return false;
}

// Search key using quadratic probing
char* search(Dictionary *D, char *key) {
    

    int h = hash(key);

    for(int i = 0; i < MAX; i++) {
        int index = (h + i * i) % MAX;

        if (D->table[index].status == 1 && strcmp(D->table[index].key, key) == 0) {
            return D->table[index].key;
        }
    }

    return NULL;
}

// Display all slots with status
void display(Dictionary *D) {
    printf("\nINDEX | STATUS    | KEY       | VALUE\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < MAX; i++) {
        if (D->table[i].status == OCCUPIED)
            printf("%5d | OCCUPIED | %-9s | %s\n", i, D->table[i].key, D->table[i].value);
        else if (D->table[i].status == DELETED)
            printf("%5d | DELETED  | -         | -\n", i);
        else
            printf("%5d | EMPTY    | -         | -\n", i);
    }
}


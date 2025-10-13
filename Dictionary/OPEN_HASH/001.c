#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100

// === Dictionary Structures ===
typedef struct {
    char key[20];
    char value[50];
} Entry;

typedef struct {
    Entry data[MAX];
    int size;
} Dictionary;

// === Function Declarations ===
void initDict(Dictionary *d);
bool insert(Dictionary *d, char *key, char *value);
bool delete(Dictionary *d, char *key);
char* search(Dictionary *d, char *key);
void display(Dictionary *d);

// === Function Definitions ===

// Initialize the dictionary
void initDict(Dictionary *d) {
    // TODO: implement
}

// Insert a new key-value pair
bool insert(Dictionary *d, char *key, char *value) {
    // TODO: implement
    return false;
}

// Delete a key-value pair
bool delete(Dictionary *d, char *key) {
    // TODO: implement
    return false;
}

// Search for a key
char* search(Dictionary *d, char *key) {
    // TODO: implement
    return NULL;
}

// Display all key-value pairs
void display(Dictionary *d) {
    // TODO: implement
}

// === Example Usage ===
int main() {
    Dictionary dict;
    initDict(&dict);

    insert(&dict, "ID001", "Alice");
    insert(&dict, "ID002", "Bob");
    insert(&dict, "ID003", "Charlie");

    display(&dict);

    printf("\nSearch ID002 → %s\n", search(&dict, "ID002"));

    delete(&dict, "ID002");

    printf("\nAfter deletion:\n");
    display(&dict);

    return 0;
}

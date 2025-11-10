#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Structure for one entry in the hash table
typedef struct {
    char key[30];
    int value;
    int isOccupied;
} Entry;

// Structure for the dictionary itself
typedef struct {
    Entry table[TABLE_SIZE];
} Dictionary;

// Hash function (you can change this later)
unsigned int hash(char *key);

// Initialize dictionary (set all slots empty)
void initDictionary(Dictionary *dict);

// Insert key-value pair using open addressing (e.g., linear probing)
void insert(Dictionary *dict, char *key, int value);

// Merge two dictionaries (merge src into dest)
void mergeDictionaries(Dictionary *dest, Dictionary *src);

// Display contents for debugging
void displayDictionary(Dictionary *dict);

int main() {
    Dictionary dict1, dict2;

    initDictionary(&dict1);
    initDictionary(&dict2);

    // TODO: insert some values into dict1 and dict2

    // TODO: call mergeDictionaries(&dict1, &dict2);

    // TODO: display results
    return 0;
}

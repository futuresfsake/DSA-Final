#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Entry in the hash table
typedef struct {
    char key[30];
    int value;
    int isOccupied; // 0 = empty, 1 = occupied
} Entry;

// Dictionary structure
typedef struct {
    Entry table[TABLE_SIZE];
} Dictionary;

// Hash function
 int hash(char *key) {
    int h=0;
    for(int i = 0 ; key[i] != '\0'; i++) {
        h+= key[i];

    }
    return (h+32) % TABLE_SIZE;
}

// Initialize all slots
// ! all entries must start as unoccupied
void initDictionary(Dictionary *dict) {

    for(int i = 0; i < 10; i++) {
        (dict)->table[i].isOccupied = 0;
        strcpy(dict->table[i].key, "");
        dict->table[i].value = 0;

    }
}

// Insert key-value pair (use linear or quadratic probing)
void insert(Dictionary *dict, char *key, int value) {
    int index = hash(key);
    int idx;

    for(int i = 0; i < TABLE_SIZE; i++) {
         idx = (index + i * i) % TABLE_SIZE;
    

    if (strcmp((dict)->table[idx].key, key)==0) {
        printf("Key already exists!");
        return;           
    } else if ((dict)->table[idx].isOccupied == 0) {
        (dict)->table[idx].isOccupied = 1;
        dict->table[idx].value = value;
        strcpy(dict->table[idx].key, key);
        return;
    }

}
printf("Table full, cannot insert %s.\n", key);
}

// Search for a key and return its value
int search(Dictionary *dict, char *key) {
    int index = hash(key);
    int idx;
   

    for(int i = 0; i < TABLE_SIZE; i++) {
        idx = (index + i * i) % TABLE_SIZE;

        if (dict->table[idx].isOccupied == 1 && strcmp(dict->table[idx].key, key)==0) 
                return dict->table[idx].value;
            
        }

        return -1;
    }



// Delete  key
void deleteKey(Dictionary *dict, char *key) {
    int index = hash(key);
    int idx;

    for(int i=0; i < TABLE_SIZE; i++) {
        idx = (index + i * i) % TABLE_SIZE;

        if (dict->table[idx].isOccupied == 1 && strcmp(dict->table[idx].key, key)==0) {
            {
                dict->table[idx].isOccupied = 0;
                dict->table[idx].value = 0;
                strcpy(dict->table[idx].key, "");
                printf("Successfully deleted...");
                return;
            }
        }
    }

    printf("Key not found: %s\n", key);
   
}

// Display all non-empty entries
void displayDictionary(Dictionary *dict) {
    printf("DICTIONARY:\n");

    for(int i = 0; i < TABLE_SIZE; i++) {
        if (dict->table[i].isOccupied ==0) {
            printf("%d. [EMPTY]\n", i+1);
        } else {
        printf("%d. {%s, %d}\n", i+1, dict->table[i].key, dict->table[i].value);
        }
    }
}

int main() {
    Dictionary dict;
    initDictionary(&dict);

    insert(&dict, "apple", 10);
    insert(&dict, "banana", 20);
    insert(&dict, "grape", 30);
    insert(&dict, "orange", 40);

    printf("\nAfter insertion:\n");
    displayDictionary(&dict);

    // Search test
    char keyToSearch[] = "banana";
    int found = search(&dict, keyToSearch);
    if (found != -1)
        printf("\nKey '%s' found in dictionary!\n", keyToSearch);
    else
        printf("\nKey '%s' not found!\n", keyToSearch);

    // Delete test
    char keyToDelete[] = "apple";
    deleteKey(&dict, keyToDelete);

    printf("\n\nAfter deletion of '%s':\n", keyToDelete);
    displayDictionary(&dict);

    return 0;
}

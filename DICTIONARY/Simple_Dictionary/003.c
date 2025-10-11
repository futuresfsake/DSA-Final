#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100   // maximum number of entries

// Define an entry: key-value pair
typedef struct {
    char key[20];
    char value[50];
} Entry;

// Define the dictionary
typedef struct {
    Entry data[MAX];
    int size;
} Dictionary;

// Make the dictionary empty
void MakeNull(Dictionary *D) {
    D->size = 0;
}

// Insert a key-value pair
void Insert(Dictionary *D, char *key, char *value) {
    if (D->size >= MAX) {
        printf("Dictionary is full!\n");
        return;
    }
    strcpy(D->data[D->size].key, key);
    strcpy(D->data[D->size].value, value);
    D->size++;
}

// Remove an entry by key
void Remove(Dictionary *D, char *key) {
    int i, found = -1;
    for (i = 0; i < D->size; i++) {
        if (strcmp(D->data[i].key, key) == 0) {
            found = i;
            break;
        }
    }
    if (found == -1) {
        printf("Key not found!\n");
        return;
    }
    // Shift remaining elements
    for (i = found; i < D->size - 1; i++) {
        D->data[i] = D->data[i + 1];
    }
    D->size--;
}

// Display all entries
void Display(Dictionary *D) {
    if (D->size == 0) {
        printf("Dictionary is empty.\n");
        return;
    }
    printf("Dictionary contents:\n");
    for (int i = 0; i < D->size; i++) {
        printf("Key: %s, Value: %s\n", D->data[i].key, D->data[i].value);
    }
}

// Demo main function
int main() {
    Dictionary D;
    MakeNull(&D);

    Insert(&D, "name", "Chelsea");
    Insert(&D, "city", "Manila");
    Insert(&D, "age", "22");

    Display(&D);

    printf("\nRemoving 'city'...\n");
    Remove(&D, "city");
    Display(&D);

    return 0;
}

// * Logic for open hashing.
// * you traverse all buckets in DictB, and for each node, you insert it into DictA


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Entry {
    char key[30];
    int value;
    struct Entry* next;
} Entry;

typedef struct {
    Entry* buckets[TABLE_SIZE];
} Dictionary;

unsigned int hash(char* key) {
    unsigned int h = 0;
    for (int i = 0; key[i]; i++)
        h = h * 31 + key[i];
    return h % TABLE_SIZE;
}

void initDictionary(Dictionary* d) {
    for (int i = 0; i < TABLE_SIZE; i++)
        d->buckets[i] = NULL;
}

void insert(Dictionary* d, char* key, int value) {
    unsigned int index = hash(key);
    Entry* newEntry = malloc(sizeof(Entry));
    strcpy(newEntry->key, key);
    newEntry->value = value;
    newEntry->next = d->buckets[index];
    d->buckets[index] = newEntry;
}

void merge(Dictionary* dest, Dictionary* src) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry* current = src->buckets[i];
        while (current) {
            insert(dest, current->key, current->value);
            current = current->next;
        }
    }
}

void display(Dictionary* d) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry* current = d->buckets[i];
        if (current) {
            printf("[%d]: ", i);
            while (current) {
                printf("(%s -> %d) ", current->key, current->value);
                current = current->next;
            }
            printf("\n");
        }
    }
}

int main() {
    Dictionary d1, d2;
    initDictionary(&d1);
    initDictionary(&d2);

    insert(&d1, "apple", 10);
    insert(&d1, "banana", 20);
    insert(&d2, "cherry", 30);
    insert(&d2, "banana", 99); // collision/duplicate key handled by chaining

    printf("Before merging:\n");
    display(&d1);
    printf("\nMerging...\n\n");

    merge(&d1, &d2);

    printf("After merging:\n");
    display(&d1);

    return 0;
}

#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char word[50];
    char meaning[100];
} Entry;

typedef struct {
    Entry entries[MAX];
    int size;
} Dictionary;

// Function declarations
void makeNullDictionary(Dictionary *D);
void insertWord(Dictionary *D, char *word, char *meaning);
void searchWord(Dictionary *D, char *word);
void removeWord(Dictionary *D, char *word);
void displayDictionary(Dictionary *D);

int main() {
    Dictionary dict;
    makeNullDictionary(&dict);

    insertWord(&dict, "apple", "A sweet fruit that grows on trees.");
    insertWord(&dict, "book", "A written or printed work consisting of pages.");
    insertWord(&dict, "computer", "An electronic device for processing data.");

    printf("\n--- All Words ---\n");
    displayDictionary(&dict);

    printf("\n--- Search Word ---\n");
    searchWord(&dict, "book");

    printf("\n--- Remove Word ---\n");
    removeWord(&dict, "apple");
    displayDictionary(&dict);

    printf("\n--- Make Dictionary Empty ---\n");
    makeNullDictionary(&dict);
    displayDictionary(&dict);

    return 0;
}

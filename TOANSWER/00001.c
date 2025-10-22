#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 10
#define KEY_LEN 30

// ===== STRUCTURES =====
typedef struct Node {
    char key[KEY_LEN];
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *table[TABLE_SIZE];
} Dictionary;

// ===== FUNCTION DECLARATIONS =====

// Hashing
unsigned int hash(char *key);

// Basic dictionary operations
void initDictionary(Dictionary *D);
void insert(Dictionary *D, char *key, int value);
void display(Dictionary *D);
void freeDictionary(Dictionary *D);

// Set operations
Dictionary unionDict(Dictionary *A, Dictionary *B);
Dictionary intersectionDict(Dictionary *A, Dictionary *B);
Dictionary differenceDict(Dictionary *A, Dictionary *B);
Dictionary symDiffDict(Dictionary *A, Dictionary *B);

// ===== MAIN FUNCTION =====
int main() {
    Dictionary A, B, U, I, D, S;

    initDictionary(&A);
    initDictionary(&B);

    // Populate A
    insert(&A, "apple", 10);
    insert(&A, "banana", 20);
    insert(&A, "mango", 30);
    insert(&A, "peach", 55);
    insert(&A, "melon", 45);

    // Populate B
    insert(&B, "banana", 15);
    insert(&B, "cherry", 25);
    insert(&B, "apple", 35);
    insert(&B, "plum", 75);
    insert(&B, "grape", 65);

    printf("=== DICTIONARY A ===\n");
    display(&A);
    printf("\n=== DICTIONARY B ===\n");
    display(&B);

    // Perform set operations
    printf("\n=== UNION (A ∪ B) ===\n");
    U = unionDict(&A, &B);
    display(&U);

    printf("\n=== INTERSECTION (A ∩ B) ===\n");
    I = intersectionDict(&A, &B);
    display(&I);

    printf("\n=== DIFFERENCE (A - B) ===\n");
    D = differenceDict(&A, &B);
    display(&D);

    printf("\n=== SYMMETRIC DIFFERENCE (A △ B) ===\n");
    S = symDiffDict(&A, &B);
    display(&S);

    // Cleanup
    freeDictionary(&A);
    freeDictionary(&B);
    freeDictionary(&U);
    freeDictionary(&I);
    freeDictionary(&D);
    freeDictionary(&S);

    return 0;
}

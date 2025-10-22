/************************************************************
 🧠 DICTIONARY FILTERING (Open Hashing / Separate Chaining)
*************************************************************

📘 INSTRUCTION:
You will implement a dictionary that stores (key, value) pairs 
using **open hashing** (linked list chaining).

Implement a function called:
    ➤ `filterDictionary(Dictionary *D)` 
that returns a new dictionary containing **only entries 
that meet a specific condition**.

Examples of filter conditions:
   - Keep all entries where value > 30
   - Keep all entries whose key starts with 'a'
   - Keep all entries whose value is even

💡 GOAL:
Practice traversing buckets, filtering based on condition, 
and inserting matching elements into a new dictionary.

************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 10

// Node for chaining
typedef struct Node {
    char key[30];
    int value;
    struct Node *next;
} Node;

// Dictionary structure
typedef struct {
    Node *table[TABLE_SIZE];
} Dictionary;


// ===== Function Declarations =====
unsigned int hash(char *key);
void initDictionary(Dictionary *D);
void insert(Dictionary *D, char *key, int value);
void display(Dictionary *D);
Dictionary filterDictionary(Dictionary *D);
void freeDictionary(Dictionary *D);


// ===== MAIN FUNCTION =====
int main() {
    Dictionary D, F;
    initDictionary(&D);

    // Insert sample data
    insert(&D, "apple", 10);
    insert(&D, "banana", 20);
    insert(&D, "avocado", 35);
    insert(&D, "mango", 50);
    insert(&D, "cherry", 15);
    insert(&D, "apricot", 60);

    printf("\n--- Original Dictionary ---\n");
    display(&D);

    // 🔍 Filter dictionary (implement logic)
    F = filterDictionary(&D);

    printf("\n--- Filtered Dictionary ---\n");
    display(&F);

    // Free both dictionaries
    freeDictionary(&D);
    freeDictionary(&F);

    return 0;
}


/*
EXPECTED OUTPUT FORMAT (example if filtering value > 30):

--- Original Dictionary ---
1. -> [EMPTY]
2. -> {banana, 20} -> NULL
3. -> {apple, 10} -> {mango, 50} -> NULL
...
--- Filtered Dictionary ---
3. -> {mango, 50} -> NULL
7. -> {apricot, 60} -> {avocado, 35} -> NULL
...
*/

/*
    🧠 PROBLEM: Open Hashing (Chaining) with Sorted Insertion

    You will implement a hash table using linked lists for collision handling (open hashing).
    Each bucket stores its linked list in **sorted ascending order by key**.

    💡 VISUAL CONCEPT OF SORTED INSERTION:
        Suppose TABLE_SIZE = 10
        And we hash "apple", "banana", "avocado"

        hash("apple")   →  index 2
        hash("banana")  →  index 7
        hash("avocado") →  index 2   (collision!)

        Bucket[2] before insertion of "avocado":
            [apple | v] → NULL

        Bucket[2] after sorted insertion of "avocado":
            [apple | v] → [avocado | v] → NULL
            (since "apple" < "avocado")

        Bucket[i] lists must always stay sorted alphabetically by key.

    ✅ You must implement:
        1) void insertSorted(Dictionary *D, char *key, int value)
           → Insert the (key, value) into its correct sorted position in the bucket.
             If the key exists, update its value.

        2) bool deleteKey(Dictionary *D, char *key)
           → Delete a key if found.

        3) void display(Dictionary D)
           → Display all keys and values bucket by bucket.

    🌟 SPECIAL OPERATIONS:
        4) Dictionary merge(Dictionary *A, Dictionary *B)
           → Merge two dictionaries into one (using sorted insertion).

        5) Dictionary filter(Dictionary *A, int threshold)
           → Return a new dictionary containing only entries where value > threshold.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 10

typedef struct Node {
    char key[30];
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *table[TABLE_SIZE];
} Dictionary;

// FUNCTION DECLARATIONS
unsigned int hash(char *key);
void insertSorted(Dictionary *D, char *key, int value);
bool deleteKey(Dictionary *D, char *key);
void display(Dictionary D);

Dictionary merge(Dictionary *A, Dictionary *B);
Dictionary filter(Dictionary *A, int threshold);

// MAIN FUNCTION (testing area)
int main() {
    Dictionary D;
    for (int i = 0; i < TABLE_SIZE; i++) D.table[i] = NULL;

    // Example visual test (you will implement functions)
    // insertSorted(&D, "grape", 20);
    // insertSorted(&D, "apple", 10);
    // insertSorted(&D, "banana", 5);
    // display(D);

    /*
        Expected after sorted insertions:
        hash("apple") → bucket 2
        hash("banana") → bucket 2
        hash("grape") → bucket 2

        Bucket[2]:
        [apple|10] → [banana|5] → [grape|20] → NULL
    */

    return 0;
}

// HASH FUNCTION (given)
unsigned int hash(char *key) {
    unsigned int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return (sum + 32) % TABLE_SIZE;
}

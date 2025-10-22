/*
===========================================================
✅  CLOSE HASHING (OPEN ADDRESSING) – UID DICTIONARY SET OPS
===========================================================

📘 CONTEXT:
------------
You are implementing a Dictionary using **Close Hashing** (Open Addressing).
Each entry stores:
    - UID (int)
    - Name (string)
and supports **set operations** between two dictionaries.

📘 REQUIRED FUNCTIONS (you will implement):
-------------------------------------------
void initDictionary(Dictionary *D);
int hash(int UID);
void insert(Dictionary *D, int UID, char *name);
void display(Dictionary *D);
int search(Dictionary *D, int UID);
void deleteKey(Dictionary *D, int UID);

// 🔸 SET OPERATIONS TO IMPLEMENT 🔸
Dictionary unionDict(Dictionary *A, Dictionary *B);
Dictionary differenceDict(Dictionary *A, Dictionary *B);
Dictionary symmetricDifferenceDict(Dictionary *A, Dictionary *B);

📘 LOGIC REMINDERS:
-------------------
🟢 UNION:
    - Combine all unique entries from both A and B.
    - If UID exists in both, only insert once.

🔵 DIFFERENCE (A - B):
    - Include only entries in A that are NOT in B.

🟣 SYMMETRIC DIFFERENCE:
    - Include entries that exist in A or B, but NOT in both.

📘 CLOSE HASHING RULES:
-----------------------
- Use (hash + i) % TABLE_SIZE for linear probing.
- Mark deleted slots using isDeleted flag.
- Never insert duplicates (check using search()).
- Initialize all entries with isOccupied = false, isDeleted = false.

📘 EXPECTED OUTPUT FORMAT:
--------------------------
Example:
-----------------------------------
DICT A:
[1] UID: 1001, Name: Alice
[2] UID: 1012, Name: Bob

DICT B:
[2] UID: 1012, Name: Bob
[3] UID: 1030, Name: Charlie

UNION RESULT:
[1] UID: 1001, Name: Alice
[2] UID: 1012, Name: Bob
[3] UID: 1030, Name: Charlie

DIFFERENCE (A - B):
[1] UID: 1001, Name: Alice

SYMMETRIC DIFFERENCE:
[1] UID: 1001, Name: Alice
[3] UID: 1030, Name: Charlie
-----------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 10

typedef struct {
    int UID;
    char name[30];
    bool isOccupied;
    bool isDeleted;
} Entry;

typedef struct {
    Entry table[TABLE_SIZE];
} Dictionary;

// Function declarations
void initDictionary(Dictionary *D);
int hash(int UID);
void insert(Dictionary *D, int UID, char *name);
void display(Dictionary *D);
int search(Dictionary *D, int UID);
void deleteKey(Dictionary *D, int UID);

// Set operations
Dictionary unionDict(Dictionary *A, Dictionary *B);
Dictionary differenceDict(Dictionary *A, Dictionary *B);
Dictionary symmetricDifferenceDict(Dictionary *A, Dictionary *B);

int main() {
    Dictionary A, B, U, D, SD;
    initDictionary(&A);
    initDictionary(&B);

    // Sample data
    insert(&A, 1001, "Alice");
    insert(&A, 1012, "Bob");
    insert(&A, 1044, "Diana");

    insert(&B, 1012, "Bob");
    insert(&B, 1030, "Charlie");
    insert(&B, 1055, "Eve");

    printf("\n--- DICT A ---\n");
    display(&A);

    printf("\n--- DICT B ---\n");
    display(&B);

    // Perform operations
    U = unionDict(&A, &B);
    D = differenceDict(&A, &B);
    SD = symmetricDifferenceDict(&A, &B);

    printf("\n--- UNION ---\n");
    display(&U);

    printf("\n--- DIFFERENCE (A - B) ---\n");
    display(&D);

    printf("\n--- SYMMETRIC DIFFERENCE ---\n");
    display(&SD);

    return 0;
}

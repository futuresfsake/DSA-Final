#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Capsule {
    int capsuleID;      // unique
    int decayLevel;     // BST key
    char description[50];
} Capsule;

typedef struct Vault {
    Capsule data;
    struct Vault* left;
    struct Vault* right;
} Vault, *VaultPtr;

// ===== Function Prototypes =====
Vault* forgeCapsule(Capsule data);                      // create new capsule
Vault* insertCapsuleIterative(Vault* ledger, Capsule data); // insert capsule
bool searchCapsuleIterative(Vault* ledger, int capsuleID); // search by ID
Vault* deleteCapsuleIterative(Vault* ledger, Capsule c);
void revealVaultIterative(Vault* ledger);               // inorder traversal
void dismantleVaultIterative(Vault* ledger);           // free memory

// ===== MAIN =====
int main() {
    Vault* ledger = NULL;

    Capsule c1 = {301, 50, "Golden Hour Capsule"};
    Capsule c2 = {302, 30, "Forgotten Letter Capsule"};
    Capsule c3 = {303, 70, "Crystal Memory Capsule"};
    Capsule c4 = {304, 40, "Shadow Capsule"};
    Capsule c5 = {305, 60, "Sunken Treasure Capsule"};

    ledger = insertCapsuleIterative(ledger, c1);
    ledger = insertCapsuleIterative(ledger, c2);
    ledger = insertCapsuleIterative(ledger, c3);
    ledger = insertCapsuleIterative(ledger, c4);
    ledger = insertCapsuleIterative(ledger, c5);

    printf("\nReveal the Vault (by decayLevel):\n");
    revealVaultIterative(ledger);

    printf("\nSearching for capsule ID 304: %s\n", 
           searchCapsuleIterative(ledger, 304) ? "Found" : "Not Found");
    printf("Searching for capsule ID 999: %s\n", 
           searchCapsuleIterative(ledger, 999) ? "Found" : "Not Found");

    printf("\nDeleting capsule with ID 303...\n");
    ledger = deleteCapsuleIterative(ledger, c3);

    printf("\nReveal the Vault after deletion:\n");
    revealVaultIterative(ledger);

    dismantleVaultIterative(ledger);
    return 0;
}


Vault* forgeCapsule(Capsule data) {

    VaultPtr newV = malloc(sizeof(Vault));
    if (newV == NULL) return NULL;

    newV->data = data;
    newV->left = NULL;
    newV->right = NULL;
    return newV;
}                  // create new capsule
Vault* insertCapsuleIterative(Vault* ledger, Capsule data) {

    VaultPtr* trav =  &ledger;

    for(;*trav != NULL && (*trav)->data.capsuleID != data.capsuleID;) {
        trav = ((*trav)->data.decayLevel < data.decayLevel) ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
        Vault* new = forgeCapsule(data);
        *trav = new;
    }

    return ledger;
}

bool searchCapsuleIterative(Vault* ledger, int capsuleID) {

    if (ledger == NULL) return false;

    if (ledger->data.capsuleID == capsuleID) return true;

    return searchCapsuleIterative(ledger->left, capsuleID) || searchCapsuleIterative(ledger->right, capsuleID);
}
// search by ID
Vault* deleteCapsuleIterative(Vault* ledger, Capsule c) {

    VaultPtr* trav = &ledger;
    for(;*trav != NULL && (*trav)->data.capsuleID != c.capsuleID;) {
        trav = ((*trav)->data.decayLevel < c.decayLevel) ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) return NULL;

    VaultPtr temp = *trav;

    if((*trav)->left == NULL && (*trav)->right == NULL) {
        free(temp);
        *trav = NULL;
    } else if (!(*trav)->left) {
        *trav = (*trav)->right;
        free(temp);
    }else if (!(*trav)->right) {
        *trav = (*trav)->left;
        free(temp);
    } else {
        VaultPtr* pred = &(*trav)->left;
        while ((*pred)->right) {
            pred = &(*pred)->right;
        }

        (*trav)->data = (*pred)->data;
        deleteCapsuleIterative(*pred, (*pred)->data);
    }

    return ledger;

} // delete by ID
void revealVaultIterative(Vault* ledger) {
    Vault* stack[100];  // stack for traversal
    int top = -1;       // stack pointer
    Vault* trav = ledger;

    while (trav != NULL || top != -1) {
        // Go as left as possible
        while (trav != NULL) {
            stack[++top] = trav;
            trav = trav->left;
        }

        // Pop from stack
        trav = stack[top--];

        // Process current node
        printf("[DecayLevel] %d [Desc] %s [ID] %d\n",
               trav->data.decayLevel, trav->data.description, trav->data.capsuleID);

        // Go right
        trav = trav->right;
    }
}
void dismantleVaultIterative(Vault* ledger) {
    if (ledger ==NULL) return;

    dismantleVaultIterative(ledger->left);
    dismantleVaultIterative(ledger->right);
    free(ledger);
}          // free memory

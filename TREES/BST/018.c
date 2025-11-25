//* see how the root is passed not as a double pointer
//* you must be careful in your recursive parameters
//* when using the return value to update a tree root->left = funct() => u must 
//* always pass the start of the chain not the end of the chain
//* passing (*trav) in delete, is wrong, specific bug called as self deletion, 

//! be mindful


//todo the delete returns a root, 
//* Passing *trav: The function sees the copied value immediately and kills the root.\
//* Passing leftWing: The function skips the root (which has the copied value) and searches for the original value in the basement.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
    ===== Dragon Egg Vault (Iterative Version) =====

    BACKSTORY:
    In Eldoria, the Wizard's Guild stores rare dragon eggs in a magical vault.
    Each egg has an ID, a hatch energy (BST key), and a species. Hatch energy
    determines the order in which eggs will awaken. You must maintain the vault
    using **iterative operations only**.

    SIDE COMPLICATIONS:
    1. Each Vault node keeps track of total energy of its subtree (totalEnergy).
    2. Hatch energies are not unique; duplicates go to the right subtree.
    3. All operations (insert, search, delete, display) must be iterative.
    4. Display shows eggs in ascending hatch energy order.
*/

typedef struct Orb {
    int eggID;
    int hatchEnergy;
    char species[40];
} Orb;

typedef struct Vault {
    Orb essence;
    struct Vault* leftWing;
    struct Vault* rightWing;
    int totalEnergy; // sum of hatchEnergy of this node + subtree
} Vault;


Vault* birthEgg(Orb essence);

// Iterative BST operations
Vault* nestEggIterative(Vault* vault, Orb essence);   // insert iteratively
bool seekEggIterative(Vault* vault, Orb e);       // search by eggID iteratively
Vault* removeEggIterative(Vault* vault, Orb e);   
void purgeVaultIterative(Vault* vault);               // free all nodes iteratively

// Helper
int calculateTotalEnergy(Vault* node);               // recalc totalEnergy of subtree

void revealVaultIterative(Vault* vault) {
    Vault* stack[100];
    int top = -1;
    Vault* curr = vault;

    while (curr != NULL || top != -1) {

        while (curr != NULL) {
            stack[++top] = curr;
            curr = curr->leftWing;
        }

        curr = stack[top--];

        printf("[EggID: %d | Energy: %d | Species: %s]\n",
               curr->essence.eggID,
               curr->essence.hatchEnergy,
               curr->essence.species);

        curr = curr->rightWing;
    }
}

int main() {
    Vault* vault = NULL;

    // Sample eggs
    Orb e1 = {201, 15, "Fire Drake"};
    Orb e2 = {202, 5,  "Ice Wyrm"};
    Orb e3 = {203, 25, "Storm Serpent"};
    Orb e4 = {204, 11, "Shadow Basilisk"};
    Orb e5 = {205, 24, "Sun Phoenix"};
    Orb e6 = {206, 10, "Lava Basilisk"};

    printf("\n=== INSERTING EGGS ===\n");
    vault = nestEggIterative(vault, e1);
    vault = nestEggIterative(vault, e2);
    vault = nestEggIterative(vault, e3);
    vault = nestEggIterative(vault, e4);
    vault = nestEggIterative(vault, e5);
    vault = nestEggIterative(vault, e6);

    printf("\n=== VAULT CONTENTS (Inorder Traversal) ===\n");
    revealVaultIterative(vault);

    // SEARCH TEST
    printf("\n=== SEARCH TESTS ===\n");

    printf("Searching for eggID %d ... ", e4.eggID);
    if (seekEggIterative(vault, e4))
        printf("FOUND!\n");
    else
        printf("NOT FOUND.\n");

    Orb fake = {999, 0, ""};
    printf("Searching for eggID %d ... ", fake.eggID);
    if (seekEggIterative(vault, fake))
        printf("FOUND!\n");
    else
        printf("NOT FOUND.\n");

    // DELETE TEST
    printf("\n=== DELETING eggID %d ===\n", e1.eggID);
    vault = removeEggIterative(vault, e1);

    printf("\n=== VAULT AFTER DELETION ===\n");
    revealVaultIterative(vault);

    // CLEANUP
    printf("\n=== PURGING VAULT (FREE ALL NODES) ===\n");
    purgeVaultIterative(vault);

    printf("Vault successfully cleared.\n");

    return 0;
}


Vault* birthEgg(Orb essence) {

    Vault* new = malloc(sizeof(Vault));
    if (!new) return NULL;

    new->essence = essence;
    new->leftWing = NULL;
    new->rightWing = NULL;
    return new;
}

Vault* nestEggIterative(Vault* vault, Orb essence) {
    Vault** trav = &vault;

    for(;*trav != NULL && (*trav)->essence.eggID != essence.eggID;) {
        trav = ((*trav)->essence.hatchEnergy < essence.hatchEnergy) ? &(*trav)->rightWing : &(*trav)->leftWing;
    }

    if (*trav == NULL) {
        Vault* new = birthEgg(essence);
        *trav = new;
    }

    return vault;
}
bool seekEggIterative(Vault* vault, Orb e) {

    Vault* trav = vault;
    for(;trav != NULL;) {
        if (trav->essence.eggID == e.eggID) {
            return true;
        }
        trav = (trav->essence.hatchEnergy < e.hatchEnergy) ? trav->rightWing : trav->leftWing;
    }

    return false;

}  

void purgeVaultIterative(Vault* vault) {
    if (vault == NULL) return;
    purgeVaultIterative(vault->leftWing);
    purgeVaultIterative(vault->rightWing);
    free(vault);

}              


Vault* removeEggIterative(Vault* vault, Orb e) {

    Vault** trav = &vault;
    
    for(;*trav != NULL && (*trav)->essence.eggID != e.eggID;) {
        trav = (*trav)->essence.hatchEnergy < e.hatchEnergy ? &(*trav)->rightWing : &(*trav)->leftWing;
    }

    if (*trav == NULL) return vault;

    Vault* temp = *trav;

    if ((*trav)->rightWing == NULL && (*trav)->leftWing == NULL) {
        free(temp);
        *trav = NULL;
        
        
    } else if ((*trav)->leftWing == NULL) {
        *trav = (*trav)->rightWing;
        free(temp);
    }
    else if ((*trav)->rightWing == NULL) {
        *trav = (*trav)->leftWing;
        free(temp);
    } else {
        Vault** succ = &(*trav)->rightWing;
        while ((*succ)->leftWing) {
            succ = &(*succ)->leftWing;
        }

        (*trav)->essence = (*succ)->essence;
        (*trav)->rightWing = removeEggIterative((*trav)->rightWing, (*succ)->essence);
    }
    return vault;
}

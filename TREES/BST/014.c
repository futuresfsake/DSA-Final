#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Arcane {
    int spellID;     // unique
    int manaCost;    // BST key
    char name[40];
} Arcane;

typedef struct EnchantedTree {
    Arcane essence;
    struct EnchantedTree* leftBranch;
    struct EnchantedTree* rightBranch;
} EnchantedTree;

// ===== Function Declarations =====
EnchantedTree* forgeSpell(Arcane essence); // create new “node”
EnchantedTree* weaveLedgerIterative(EnchantedTree* ledger, Arcane essence); // insert
bool detectSpellIterative(EnchantedTree* ledger, int spellID); // search by ID
void revealLedger(EnchantedTree* ledger); // inorder traversal
void dismantleLedger(EnchantedTree* ledger);


// Deletes a spell from the ledger by its spellID
EnchantedTree* banishSpell(EnchantedTree* ledger, int spellID) {
    if (ledger == NULL) return NULL;

    ledger->leftBranch = banishSpell(ledger->leftBranch, spellID);
    ledger->rightBranch = banishSpell(ledger->rightBranch, spellID);

    if (ledger->essence.spellID == spellID) {
         EnchantedTree* temp = ledger;

        if (ledger->rightBranch == NULL && ledger->leftBranch == NULL) {
           
            free(temp);
            return NULL;
        }

        else if (ledger->rightBranch == NULL) {
           
            ledger = ledger->leftBranch;
            free(temp);
            return ledger;
        }
        else if (ledger->leftBranch == NULL) {
            
            ledger = ledger->rightBranch;
            free(temp);
            return ledger;
        } else {
            EnchantedTree* succ = ledger->rightBranch;
            while (succ->leftBranch) {
                succ = succ->leftBranch;
            }

            ledger->essence = succ->essence;
            ledger->rightBranch = banishSpell(ledger->rightBranch, succ->essence.spellID);

        }
    }
    return ledger;
}

// ===== MAIN =====
int main() {
    EnchantedTree* ledger = NULL; // don’t call it root, call it ledger!

    Arcane s1 = {101, 30, "Fireball"};
    Arcane s2 = {102, 20, "Ice Shard"};
    Arcane s3 = {103, 50, "Lightning Bolt"};
    Arcane s4 = {104, 55, "Shadow Mist"}; // same manaCost
    Arcane s5 = {105, 7, "Solar Flare"}; // same manaCost

    ledger = weaveLedgerIterative(ledger, s1);
    ledger = weaveLedgerIterative(ledger, s2);
    ledger = weaveLedgerIterative(ledger, s3);
    ledger = weaveLedgerIterative(ledger, s4);
    ledger = weaveLedgerIterative(ledger, s5);

    printf("\nReveal spell ledger (mana-cost order):\n");
    revealLedger(ledger);

    printf("\nSearching for spell ID 104: %s\n", detectSpellIterative(ledger, 104) ? "Found" : "Not Found");
    printf("Searching for spell ID 999: %s\n", detectSpellIterative(ledger, 999) ? "Found" : "Not Found");


     printf("\nBanish spell with ID 103...\n");
    ledger = banishSpell(ledger, 103);

    printf("\nReveal spell ledger after banishing:\n");
    revealLedger(ledger);

    dismantleLedger(ledger);
    return 0;
}


EnchantedTree* forgeSpell(Arcane essence) {

    EnchantedTree* newSpell = malloc(sizeof(EnchantedTree));
    if (!newSpell) return NULL;

    newSpell->essence = essence;
    newSpell->leftBranch = NULL;
    newSpell->rightBranch = NULL;

    return newSpell;
}
EnchantedTree* weaveLedgerIterative(EnchantedTree* ledger, Arcane essence) {

    EnchantedTree** trav  = &ledger;
    for(;*trav != NULL && (*trav)->essence.spellID != essence.spellID;) {
        trav = ((*trav)->essence.manaCost < essence.manaCost) ? &(*trav)->rightBranch: &(*trav)->leftBranch;
    }

    if (*trav != NULL) return NULL;

    EnchantedTree* new = forgeSpell(essence);
    *trav = new;

    return ledger;

}
bool detectSpellIterative(EnchantedTree* ledger, int spellID) {
    if (ledger == NULL) return false;


    if (ledger->essence.spellID == spellID) return true;


    return detectSpellIterative(ledger->leftBranch, spellID) || detectSpellIterative(ledger->rightBranch, spellID);
} // search by ID
void revealLedger(EnchantedTree* ledger) {

    if (ledger == NULL) return;
    revealLedger(ledger->leftBranch);
    printf("[Mana Cost] => %d [Name] => %s [SpellId] => %d \n",
    ledger->essence.manaCost,
        ledger->essence.name, ledger->essence.spellID);
        revealLedger(ledger->rightBranch);

}
void dismantleLedger(EnchantedTree* ledger) {
    if (ledger== NULL) return;
    dismantleLedger(ledger->leftBranch);
    dismantleLedger(ledger->rightBranch);
    free(ledger);
    
    }

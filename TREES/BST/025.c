#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
    Astral Bestiary Archive (Iterative BST)

    Backstory:
    ----------------
    In the Astral Realm, scholars track mystical creatures called "Celestials."
    Each Celestial has a unique ID, a PowerIndex (BST key), and a Species name.
    The archive is a Binary Search Tree organized by PowerIndex for rapid
    retrieval and management. Scholars must perform all operations iteratively
    to maintain magical balance without recursion, which can cause mana overflow.

    Your task: Implement iterative BST operations for insert, search, deletion,
    and traversals using only loops and stacks, no recursion.
*/

// ================================
// Celestial Struct
// ================================
typedef struct {
    int celestialID;       // unique ID
    int powerIndex;        // BST key
    char species[50];      // species name
} Celestial;

// ================================
// BST Node Struct
// ================================
typedef struct BeastNode {
    Celestial data;
    struct BeastNode* left;
    struct BeastNode* right;
} BeastNode;

// ================================
// Iterative Function Prototypes
// ================================

// Create a new Celestial node
BeastNode* summonCelestial(Celestial c) {

    BeastNode* new = malloc(sizeof(BeastNode));
    if (!new) return NULL;

    new->data = c;
    new->left = new->right = NULL;
    return new;
}

// Insert a Celestial iteratively
BeastNode* recordCelestialIter(BeastNode* archive, Celestial c) {

    BeastNode** trav = &archive;
    for(;*trav != NULL && (*trav)->data.celestialID != c.celestialID;) {
        trav = (*trav)->data.powerIndex < c.powerIndex ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
        *trav = summonCelestial(c);
    }
    return archive;

}

void displayCelestial(Celestial c) {
    printf("[ID: %d | Power: %d | Species: %s]\n",
           c.celestialID, c.powerIndex, c.species);
}


// Search by CelestialID iteratively
bool detectCelestialIDIter(BeastNode* archive, int celestialID) {

    if (archive == NULL) return false;

    if (archive->data.celestialID == celestialID) return true;


    return detectCelestialIDIter(archive->left, celestialID) || detectCelestialIDIter(archive->right, celestialID);
}

// Search by PowerIndex iteratively
BeastNode* detectPowerIter(BeastNode* archive, int powerIndex) {


    //* should never overwrite the tree, just root = ()
    if (archive == NULL) return archive;

    if (archive->data.powerIndex == powerIndex) return archive;

    if (archive->data.powerIndex < powerIndex) {
       archive =  detectPowerIter(archive->right, powerIndex);
    } else if (archive->data.powerIndex > powerIndex){
        archive =  detectPowerIter(archive->left, powerIndex);
    }
    

    //* unlike in insert, we must update the left or right child

    // BeastNode* trav = archive;
    // for(;trav != NULL;) {
    //     if (trav->data.powerIndex == powerIndex) {
    //         return trav;
    //     }
    //     trav = trav->data.powerIndex < powerIndex ? trav->right : trav->left;
    // }
    // return NULL;
}

// Delete a Celestial by ID iteratively
BeastNode* banishCelestialIter(BeastNode* archive, int celestialID) {

    if (archive == NULL) return archive;

    archive->left = banishCelestialIter(archive->left, celestialID);
    archive->right = banishCelestialIter(archive->right, celestialID);

    if (archive->data.celestialID == celestialID) {

        BeastNode* temp = archive;

        if (archive->right == NULL && archive->left == NULL) {
            free(temp);
            archive = NULL;
        } else if (archive->left == NULL) {
            archive = archive->right;
            free(temp);
        }else if (archive->right == NULL) {
            archive = archive->left;
            free(temp);
        } else {
            BeastNode* succ = archive->right;
            while (succ->left) {
                succ = succ->left;
            }

            archive->data = succ->data;
            archive->right = banishCelestialIter(archive->right, succ->data.celestialID);
        }

        return archive;
    }

    return archive;
}

// Inorder traversal (PowerIndex ascending)
void revealCelestialsIter(BeastNode* archive);

// Find minimum PowerIndex iteratively
BeastNode* weakestCelestialIter(BeastNode* archive) {
    if (archive == NULL) return archive;

    while (archive->left) {
        archive = archive->left;
    }
    return archive;
}

// Find maximum PowerIndex iteratively
BeastNode* strongestCelestialIter(BeastNode* archive) {
    if (archive == NULL) return archive;
    while (archive->right) {
        archive = archive->right;
    }
    return archive;
}

// Count total Celestials iteratively
int totalCelestialsIter(BeastNode* archive) {
    if (archive == NULL) return 0;

    int c = totalCelestialsIter(archive->left);
    int c2 = totalCelestialsIter(archive->right);

    return c+c2+1;
}

// Free entire BST iteratively
void dismantleArchiveIter(BeastNode* archive) {
    if (archive == NULL) return;

    dismantleArchiveIter(archive->left);
    dismantleArchiveIter(archive->right);
    free(archive);
}

// ================================
// MAIN (Sample Usage)
// ================================
int main() {
    BeastNode* archive = NULL;

    // Sample Celestials
    Celestial c1 = {301, 50, "Luminwing"};
    Celestial c2 = {302, 30, "Shadowpaw"};
    Celestial c3 = {303, 70, "Thunderfang"};
    Celestial c4 = {304, 55, "Windstrider"};
    Celestial c5 = {305, 20, "Silentclaw"};
    Celestial c6 = {306, 65, "Pyrotail"};
    Celestial c7 = {307, 45, "Glimmerscale"};

    // Insert Celestials iteratively
    archive = recordCelestialIter(archive, c1);
    archive = recordCelestialIter(archive, c2);
    archive = recordCelestialIter(archive, c3);
    archive = recordCelestialIter(archive, c4);
    archive = recordCelestialIter(archive, c5);
    archive = recordCelestialIter(archive, c6);
    archive = recordCelestialIter(archive, c7);

    // Reveal archive in-order
    printf("Celestials in ascending PowerIndex:\n");
    revealCelestialsIter(archive);

    // Detect Celestials by ID
    printf("\nDetect Celestial ID 304: %s\n",
           detectCelestialIDIter(archive, 304) ? "Found" : "Not Found");


           // Detect Celestials by ID
    printf("\nDetect Power Idx 30:\n");
        BeastNode* n = detectPowerIter(archive, 30);
        printf("Species: %s || Index: %d\n", n->data.species, n->data.powerIndex);
          
    // Find weakest and strongest Celestials
    // Find weakest and strongest Celestials
BeastNode* weakest = weakestCelestialIter(archive);
BeastNode* strongest = strongestCelestialIter(archive);

// Display results
printf("\n=== Weakest Celestial (Min PowerIndex) ===\n");
if (weakest)
    displayCelestial(weakest->data);
else
    printf("Archive is empty.\n");

printf("\n=== Strongest Celestial (Max PowerIndex) ===\n");
if (strongest)
    displayCelestial(strongest->data);
else
    printf("Archive is empty.\n");

    // Delete a Celestial iteratively
    archive = banishCelestialIter(archive, 307);
        printf("\n\nAfter Deletion of 307:\n");
    revealCelestialsIter(archive);

    // Count total remaining Celestials
    int total = totalCelestialsIter(archive);

    printf("\nTotal Celestials: %d\n", total);
   
    
    // Free memory
    dismantleArchiveIter(archive);
    printf("Exit!!\n");

    return 0;
}

void revealCelestialsIter(BeastNode* archive) {
    BeastNode* stack[100];
    int top = -1;
    BeastNode* curr = archive;

    while (curr != NULL || top != -1) {

        while (curr != NULL) {
            stack[++top] = curr;
            curr = curr->left;
        }

        curr = stack[top--];
        displayCelestial(curr->data);   // <-- PRINT HERE

        curr = curr->right;
    }
}

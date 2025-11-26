#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NAME_LEN 50

/*
    Intergalactic Library Catalog (BST - Alphabetical Order)

    Backstory:
    ----------------
    The library of the Galactic Council stores information on
    alien species. Each record has a SpeciesName, HomePlanet, 
    and AverageLifespan.  

    The library organizes species **alphabetically by SpeciesName**
    using a Binary Search Tree.  

    All operations are iterative to simulate real-time access
    in a high-security database.
*/

// ================================
// Alien Species Struct
// ================================
typedef struct {
    char speciesName[NAME_LEN];
    char homePlanet[NAME_LEN];
    int avgLifespan;
} Species;

// ================================
// BST Node Struct
// ================================
typedef struct bstNode {
    Species data;
    struct bstNode *left;
    struct bstNode *right;
} BSTNode;

// ================================
// Function Prototypes (Iterative)
// ================================

// 1. Create a new BST node
BSTNode* createSpeciesNode(Species s) {
    BSTNode* new = malloc(sizeof(BSTNode));
    if (new == NULL) return NULL;
    new->data = s;
    new->left = new->right = NULL;
    return new;
}

// 2. Insert species alphabetically (iterative)
BSTNode* insertSpecies(BSTNode *root, Species s) {

    BSTNode** trav = &root;
    for(;*trav != NULL && strcmp((*trav)->data.speciesName, s.speciesName) !=0;) {
        trav = (strcmp((*trav)->data.speciesName, s.speciesName)<0) ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
        BSTNode* new = createSpeciesNode(s);
        *trav = new;
    }
    return root;

}

// 3. Search for a species by name (iterative)
BSTNode* searchSpecies(BSTNode *root, const char *name) {
    BSTNode* trav = root;

    for(;trav != NULL;) {
        if (strcmp(trav->data.speciesName, name) == 0) {
            return trav;
        }
        trav = (strcmp(trav->data.speciesName, name)<0) ? trav->right : trav->left;

    }
    return NULL;
}


void inorderDisplay(BSTNode *root) {
    if (root == NULL) return;

    inorderDisplay(root->left);

    printf("%s | %s | %d\n",
           root->data.speciesName,
           root->data.homePlanet,
           root->data.avgLifespan);

    inorderDisplay(root->right);
}

// 6. Find minimum value node (helper for deletion)
BSTNode* findMinNode(BSTNode *node) {
    if (node == NULL) return node;

    while (node->left) {
        node = node->left;
    }
    return node;
}

// 7. Free all nodes iteratively
void freeBST(BSTNode *root) {
    if (root == NULL) return;
    freeBST(root->left);
    freeBST(root->right);
    free(root);
}

BSTNode* deleteSpecies(BSTNode* root, char* name) {

    BSTNode** trav = &root;
    for(;*trav != NULL && (strcmp((*trav)->data.speciesName, name)!=0);) {
        trav = strcmp((*trav)->data.speciesName, name) <0 ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) return root;

    BSTNode* temp = *trav;
    if ((*trav)->left == NULL && (*trav)->right == NULL) {
        free(temp);
        *trav = NULL;
    } else if ((*trav)->left == NULL) {
        *trav = (*trav)->right;
        free(temp);
        

    }else if ((*trav)->right == NULL) {
        *trav = (*trav)->left;
        free(temp);
        
    } else {
        BSTNode** succ = &(*trav)->right;
        while ((*succ)->left) {
            succ = &(*succ)->left;
        }
        (*trav)->data = (*succ)->data;
        (*trav)->right = deleteSpecies((*trav)->right, (*succ)->data.speciesName);
    }
   return root;
}

// ================================
// MAIN (Sample Usage)
// ================================
int main() {
    BSTNode *root = NULL;

    // Sample species
    Species s1 = {"Zorgon", "Xebulon", 120};
    Species s2 = {"Aelion", "Arcturus", 80};
    Species s3 = {"Mirel", "Nebulon", 200};
    Species s4 = {"Brix", "Orion", 50};
    Species s5 = {"Ylthar", "Zeta Prime", 150};

    // Insert species alphabetically
    root = insertSpecies(root, s1);
    root = insertSpecies(root, s2);
    root = insertSpecies(root, s3);
    root = insertSpecies(root, s4);
    root = insertSpecies(root, s5);

    // Display all species alphabetically
    printf("\n--- Galactic Library Catalog ---\n");
    inorderDisplay(root);

    // Search for a species
    const char *searchName = "Mirel";
    BSTNode *found = searchSpecies(root, searchName);
    if (found) {
        printf("\nFound species: %s from %s, Avg Lifespan: %d\n",
               found->data.speciesName,
               found->data.homePlanet,
               found->data.avgLifespan);
    } else {
        printf("\nSpecies %s not found in catalog.\n", searchName);
    }

    root = deleteSpecies(root, "Mirel");

    printf("\n--- Catalog after deletion (Mirel) ---\n");
    inorderDisplay(root);

    // Free all nodes
    freeBST(root);

    return 0;
}

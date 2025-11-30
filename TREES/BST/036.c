#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME 50

typedef struct {
    int artifactID;             // BST key
    char artifactName[MAX_NAME]; // Artifact name
    int powerLevel;              // Power level of artifact
} Artifact;

typedef struct ArtifactNode {
    Artifact data;
    struct ArtifactNode *left;  // Lower ID
    struct ArtifactNode *right; // Higher ID
} ArtifactNode;

typedef struct {
    ArtifactNode *root;
} Repository;

// ===================== FUNCTION PROTOTYPES =====================

// Initialize repository
void initRepo(Repository *repo);

// Insert a new artifact into BST
// Return true if inserted, false if duplicate ID
bool storeArtifact(Repository *repo, int id, char *name, int power);

// Search artifact by ID, return powerLevel or -1 if not found
ArtifactNode* findArtifactPower(ArtifactNode *root, int id);

// Boost all artifact power below threshold by amount
void enhanceArtifacts(ArtifactNode *current, int threshold, int boostAmount);

// Remove an artifact by ID (handle 0, 1, 2 children)
void removeArtifact(ArtifactNode** root, int powerlvl, int id);// Print inventory in ascending order of ID
void artifactInventory(ArtifactNode *current);


int main() {
    Repository repo;
    initRepo(&repo);

    printf("=== Storing Galactic Artifacts ===\n");

    storeArtifact(&repo, 2001, "Quantum Relic", 80);
    storeArtifact(&repo, 1999, "Nebula Gem", 55);
    storeArtifact(&repo, 2005, "Void Crystal", 30);
    storeArtifact(&repo, 2003, "Star Core", 20);
    storeArtifact(&repo, 2007, "Cosmic Orb", 10);

    printf("\n=== Full Repository ===\n");
    artifactInventory(repo.root);

    printf("\n=== Locate Artifact 2005 ===\n");
   ArtifactNode* node = findArtifactPower(repo.root, 2005);
if (node != NULL) 
    printf("Artifact 2005 found. Power Level: %d\n", node->data.powerLevel);
else
    printf("Artifact 2005 not found.\n");


    printf("\n=== Boost Artifacts with Power < 30 by +50 ===\n");
    enhanceArtifacts(repo.root, 30, 50);
    artifactInventory(repo.root);

    printf("\n=== Removing Artifact 2005 (node with tricky children) ===\n");
    removeArtifact(&repo.root, 30, 2005);
    artifactInventory(repo.root);

    return 0;
}





void initRepo(Repository *repo) {

    repo->root = NULL;

}

// Insert a new artifact into BST
// Return true if inserted, false if duplicate ID
bool storeArtifact(Repository *repo, int id, char *name, int power) {

    ArtifactNode** trav = &(repo->root);
    for(;*trav!= NULL && (*trav)->data.artifactID != id;) {
        trav = (*trav)->data.powerLevel < power ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
        Artifact d;
        d.artifactID = id;
        strcpy(d.artifactName, name);
        d.powerLevel = power;


        ArtifactNode* new = malloc(sizeof(ArtifactNode));
        if (!new) return false;
        new->data = d;
        new->left = new->right = NULL;

        *trav = new;
        return true;
    }

    return false;
}

// Search artifact by ID, return powerLevel or -1 if not found
ArtifactNode* findArtifactPower(ArtifactNode *root, int id) {

    if (root == NULL) return NULL;

    if (root->data.artifactID == id) return root;

  
    ArtifactNode* n = findArtifactPower(root->left, id);
    if (n != NULL) return n;
    ArtifactNode* n1 = findArtifactPower(root->right, id);
    if (n1 != NULL) return n1;

    return NULL;
}

// Boost all artifact power below threshold by amount
void enhanceArtifacts(ArtifactNode *current, int threshold, int boostAmount) {
    
    if (current == NULL) return;



    enhanceArtifacts(current->left, threshold, boostAmount); 
    if (current->data.powerLevel <= threshold) 
     current->data.powerLevel += boostAmount;
     enhanceArtifacts(current->right, threshold, boostAmount);
}

// Remove an artifact by ID (handle 0, 1, 2 children)
void removeArtifact(ArtifactNode** root, int powerlvl, int id ) {

  ArtifactNode** trav = root;
  for(;*trav != NULL && (*trav)->data.artifactID != id;) {
    trav = (*trav)->data.powerLevel < powerlvl ? &(*trav)->right : &(*trav)->left;
  }

  if (*trav == NULL) return;

  ArtifactNode* temp = *trav;

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
    ArtifactNode** pred = &(*trav)->left;
    while ((*pred)->right) {
        pred = &(*pred)->right;
    }

    (*trav)->data = (*pred)->data;

    ArtifactNode* delete = *pred;
    *pred = (*pred)->left;
    free(delete);
  }


    
}

// Print inventory in ascending order of ID
void artifactInventory(ArtifactNode *current) {
    if (current == NULL) return;

    // Visit left subtree
    artifactInventory(current->left);

    // Print current node
    printf("[%d] %s: %d\n", 
           current->data.artifactID, 
           current->data.artifactName, 
           current->data.powerLevel);

    // Visit right subtree
    artifactInventory(current->right);
}

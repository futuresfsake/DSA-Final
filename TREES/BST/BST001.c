#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// =======================================================
//     CRIMINAL RECORD (Node Data)
// =======================================================

typedef struct {
    int caseID;               // BST key
    char name[50];
    char crime[50];
    int threatLevel;          // 1–10
    char status[30];          // "At Large", "Captured", etc.
} CriminalRecord;


// =======================================================
//     BST NODE STRUCTURE
// =======================================================

typedef struct BSTNode {
    CriminalRecord data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;


// =======================================================
//     FUNCTION DECLARATIONS (NO LOGIC INSIDE)
// =======================================================

// Create an empty tree
BSTNode* initBST() {
    BSTNode* root = NULL;
    return root;
}

// Create a new node (allocate only)
BSTNode* createNode(CriminalRecord c) {

    BSTNode* new = malloc(sizeof(BSTNode));
    if (!new) return NULL;

    new->data = c;
    new->left = NULL;
    new->right = NULL;

    return new;

}

// Insert a record based on caseID
BSTNode* insertCase(BSTNode* root, CriminalRecord c) {

    BSTNode** trav = &root;

    for(; *trav != NULL && (*trav)->data.caseID != c.caseID;) {
        trav = ((*trav)->data.caseID < c.caseID) ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
        BSTNode* new = createNode(c);
        *trav = new;
        return root;
    }
}

// Search for a criminal by caseID
BSTNode* searchCase(BSTNode* root, int caseID) {

    BSTNode* trav = root;
    for(;trav != NULL;) {
        if (trav->data.caseID == caseID) {
            return trav;
        }
        trav = (trav->data.caseID < caseID) ? trav->right : trav->left;
    }
    return NULL;

}

// Delete a criminal record
BSTNode* deleteCase(BSTNode* root, int caseID) {

    BSTNode** trav = &root;
    
    for(;*trav != NULL && (*trav)->data.caseID != caseID;) {
        trav = ((*trav)->data.caseID < caseID) ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) return NULL;

    BSTNode* temp = *trav;

    if ((*trav)->right == NULL && (*trav)->left == NULL) {
        free(temp);
        *trav = NULL;
    }

    else if ((*trav)->left == NULL) {
        *trav = (*trav)->right;
        free(temp);
    } else if ((*trav)->right == NULL) {
        *trav = (*trav)->left;
        free(temp);
    }

    else {
        BSTNode** succ = &(*trav)->right;
        while ((*succ)->left) {
            succ = &(*succ)->left;
        }

        (*trav)->data = (*succ)->data;
        deleteCase(*succ, (*succ)->data.caseID);
    }
    return root;
}

// Find minimum node (for deletion helper)
BSTNode* findMin(BSTNode* root) {

    BSTNode* trav = root;
    while (trav->left) {
        trav = trav->left;
    }
    return trav;
}

void inorderDisplay(BSTNode* root) {
    if (root == NULL) return;

    inorderDisplay(root->left);

    printf("Case ID: %d\n", root->data.caseID);
    printf("Name: %s\n", root->data.name);
    printf("Crime: %s\n", root->data.crime);
    printf("Threat Level: %d\n", root->data.threatLevel);
    printf("Status: %s\n", root->data.status);
    printf("----------------------------\n");

    inorderDisplay(root->right);
}


// Remove all nodes (clear system)
void destroyTree(BSTNode* root) {
    
    if (root == NULL) return;
    
    free(root->left);
    free(root->right);
    free(root);

   
}


int main() {
    // Initialize empty BST
    BSTNode *root = initBST();

    // Sample criminal records
    CriminalRecord a = {1001, "Miguel Santos", "Cyber Fraud", 7, "At Large"};
    CriminalRecord b = {542, "Anna Cruz", "Money Laundering", 5, "Captured"};
    CriminalRecord c = {2010, "Jomar Reyes", "Armed Robbery", 9, "Most Wanted"};
    CriminalRecord d = {1200, "Luis Ramirez", "Fraud", 6, "At Large"};

    // Insert records
    root = insertCase(root, a);
    root = insertCase(root, b);
    root = insertCase(root, c);
    root = insertCase(root, d);

    printf("\n=== All Criminal Records (Inorder by Case ID) ===\n");
    inorderDisplay(root);

    // Search for a case
    int searchID = 1200;
    BSTNode* found = searchCase(root, searchID);
    if (found) {
        printf("\nFound case %d: %s, Crime: %s\n", found->data.caseID, found->data.name, found->data.crime);
    } else {
        printf("\nCase %d not found.\n", searchID);
    }

    // Delete a case
    int deleteID = 542;
    root = deleteCase(root, deleteID);
    printf("\n=== Records After Deleting Case %d ===\n", deleteID);
    inorderDisplay(root);

    // Clean up tree
    destroyTree(root);

    return 0;
}


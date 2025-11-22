/*
==============================================================
        BINARY SEARCH TREE (ADT STYLE BOILERPLATE)
==============================================================

Operations to implement:
1) initBST        : initialize BST
2) insertBST      : insert a new value
3) searchBST      : search for a value
4) deleteBST      : delete a value
5) findMinBST     : find minimum value
6) findMaxBST     : find maximum value
7) inorderBST     : print inorder traversal
8) preorderBST    : print preorder traversal
9) postorderBST   : print postorder traversal
==============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// BST Node Structure
typedef struct BSTNode {
    int data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

// ---------------- FUNCTION PROTOTYPES ----------------

// Initialize BST
BSTNode* initBST(); 

// Insert value into BST
BSTNode* insertBST(BSTNode* root, int value);

// Search for value in BST
BSTNode* searchBST(BSTNode* root, int value);

// Delete value from BST
BSTNode* deleteBST(BSTNode* root, int value);

// Find minimum value in BST
BSTNode* findMinBST(BSTNode* root);

// Find maximum value in BST
BSTNode* findMaxBST(BSTNode* root);

// Traversals
void inorderBST(BSTNode* root);
void preorderBST(BSTNode* root);
void postorderBST(BSTNode* root);

// Free BST
void freeBST(BSTNode* root);

// ---------------- MAIN (EXAMPLE USAGE) ----------------
int main() {
    BSTNode* root = initBST();

    root = insertBST(root, 50);
    root = insertBST(root, 30);
    root = insertBST(root, 70);
    root = insertBST(root, 20);
    root = insertBST(root, 40);
    root = insertBST(root, 60);
    root = insertBST(root, 80);

    printf("Inorder traversal: ");
    inorderBST(root);
    printf("\n");

    printf("Preorder traversal: ");
    preorderBST(root);
    printf("\n");

    printf("Postorder traversal: ");
    postorderBST(root);
    printf("\n");

    printf("Search for 40: %s\n", searchBST(root, 40) ? "Found" : "Not Found");
    printf("Search for 90: %s\n", searchBST(root, 90) ? "Found" : "Not Found");

    printf("Minimum value: %d\n", findMinBST(root)->data);
    printf("Maximum value: %d\n", findMaxBST(root)->data);

    root = deleteBST(root, 20);  // Delete leaf node
    root = deleteBST(root, 30);  // Delete node with one child
    root = deleteBST(root, 50);  // Delete node with two children

    printf("Inorder after deletions: ");
    inorderBST(root);
    printf("\n");

    freeBST(root);
    return 0;
}


// Initialize BST

//! if asked to initialize initBST => just return NULLL
BSTNode* initBST() {

   return NULL;



}

// Insert value into BST
BSTNode* insertBST(BSTNode* root, int value) {

    BSTNode** trav = &root;
    bool found = false;
    for(;*trav != NULL && (*trav)->data != value;) {
        trav = ((*trav)->data < value) ? &(*trav)->right: &(*trav)->left;
    }


    if (*trav == NULL) {

        BSTNode* new = malloc(sizeof(BSTNode));
        if (new) {
        
        (new)->data = value;
        (new)->left = NULL;
        (new)->right = NULL;
        *trav = new;
        return root;
        
        }
}

}

// Search for value in BST
BSTNode* searchBST(BSTNode* root, int value) {

    BSTNode* trav = root;
    for(; trav != NULL;) {
        if (trav->data == value) {
            return trav;
        }
        trav = trav->data < value ? trav->right : trav->left;
    }
}

BSTNode* deleteBST(BSTNode* root, int value) {

    BSTNode** trav = &(root);
    for(; *trav != NULL && (*trav)->data != value;) {
        trav = ((*trav)->data < value) ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL)  return root;

    BSTNode* remove = *trav;

    if (!(*trav)->left && !(*trav)->right) {
        free(remove);
        *trav= NULL;
    }

    else if (!(*trav)->right) {
        *trav = (*trav)->left;
        free(remove);
    }

     else if (!(*trav)->left) {
        *trav = (*trav)->right;
        free(remove);
    }


    else {
        BSTNode** pred = &(*trav)->left;
        while ((*pred)->right) {
            pred = &(*pred)->right;
        }
        (*trav)->data = (*pred)->data;
        *pred = deleteBST(*pred, (*pred)->data);
    }

    return root;
}

// Find minimum value in BST
BSTNode* findMinBST(BSTNode* root) {

    BSTNode* min = root;
    while (min->left) {
        min = min->left;

    }
    return min;
}

// Find maximum value in BST
BSTNode* findMaxBST(BSTNode* root) {
    BSTNode* max = root;
    while (max->right) {
        max = max->right;

    }
    return max;
}

void inorderBST(BSTNode* root) {
    if(root == NULL) return;
    inorderBST(root->left);
    printf("%d ", root->data);
    inorderBST(root->right);
}

void preorderBST(BSTNode* root) {
    if(root == NULL) return;
    printf("%d ", root->data);
    preorderBST(root->left);
    preorderBST(root->right);
}

void postorderBST(BSTNode* root) {
    if(root == NULL) return;
    postorderBST(root->left);
    postorderBST(root->right);
    printf("%d ", root->data);
}


void freeBST(BSTNode* root) {
    if (!root) return;
    freeBST(root->left);
    freeBST(root->right);
    free(root);
}

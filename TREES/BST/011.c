#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// =========================
//       BST STRUCTS
// =========================
typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} Node, *BSTNode;


// =========================
//   FUNCTION DECLARATIONS
// =========================

// Create new node
BSTNode createNode(int value);

// Initialize BST
BSTNode initBST();

// Insert into BST
BSTNode insertBST(BSTNode root, int value);

// Search in BST
bool searchBST(BSTNode root, int value);

// Find minimum value in BST
BSTNode findMin(BSTNode root);

// Find maximum value in BST
BSTNode findMax(BSTNode root);

// Delete a value from BST
void deleteBST(BSTNode *root, int value);

// Traversals
void inorder(BSTNode root);
void preorder(BSTNode root);
void postorder(BSTNode root);

// Free all nodes
void freeBST(BSTNode root);

// =========================
//      MAIN (Example)
// =========================
int main() {
    BSTNode root = initBST();

    root = insertBST(root, 50);
    root = insertBST(root, 30);
    root = insertBST(root, 70);
    root = insertBST(root, 20);
    root = insertBST(root, 40);
    root = insertBST(root, 60);
    root = insertBST(root, 80);

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    printf("Searching 40: %s\n", searchBST(root, 40) ? "Found" : "Not Found");

    printf("Min: %d\n", findMin(root)->data);
    printf("Max: %d\n", findMax(root)->data);

    deleteBST(&root, 30);

    printf("Inorder After Delete: ");
    inorder(root);
    printf("\n");

    return 0;
}

// =========================
// FUNCTION DEFINITIONS (EMPTY)
// =========================

BSTNode createNode(int value) {

    BSTNode new = malloc(sizeof(Node));
    if (!new) return NULL;
    new->data = value;
    new->left = NULL;
    new->right = NULL;
    return new;
    
 }

BSTNode initBST() { 

    BSTNode root = NULL;
    return root;

}

BSTNode insertBST(BSTNode root, int value) {

   
    BSTNode* trav = &root;

    for(;(*trav) != NULL && (*trav)->data != value;) {
        trav = ((*trav)->data < value) ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
        *trav = createNode(value);
    }
    return root;
}

 

bool searchBST(BSTNode root, int value) { 

    BSTNode trav = root;
    for(; trav != NULL;) {
        if (trav->data == value) {
            return true;
        }
        trav = trav->data < value ? trav->right : trav->left;

    }
    return false;
}

BSTNode findMin(BSTNode root) {

    while (root->left) {
        root = root->left;
    }

    return root;
 }

BSTNode findMax(BSTNode root) {
    BSTNode max;
    BSTNode trav= root;

    while (trav->right) {
        trav = trav->right;
    }

    return trav;
 }

void deleteBST(BSTNode *root, int value) {

    if (*root == NULL) return;

    BSTNode* trav = root;
    for(;*trav != NULL && (*trav)->data != value;) {
        trav = ((*trav)->data < value) ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) return;

    BSTNode temp = *trav;

    if ((*trav)->right == NULL && (*trav)->left == NULL) {
        
        *trav = NULL;
    }

   else  if (!(*trav)->left) {
        *trav = (*trav)->right;
       
    }

    else if (!(*trav)->right) {
        *trav = (*trav)->left;
      
    } else {

        BSTNode* pred = &(*trav)->left;
        while ((*pred)->right) {

            pred = &(*pred)->right;
        }
        (*trav)->data = (*pred)->data;
        deleteBST(pred, (*pred)->data);
        
    }
    
 }

void inorder(BSTNode root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ->", root->data);
        inorder(root->right);
    }
 }



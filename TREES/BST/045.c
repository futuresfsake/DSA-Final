#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 50

typedef struct node {
    char name[NAME_LEN];
    struct node* left;
    struct node* right;
} BSTNode;

// ==================== FUNCTION PROTOTYPES ====================
BSTNode* createNode(char* name);
BSTNode* insertNode(BSTNode* root, char* name);
BSTNode* deleteNode(BSTNode* root, char* name);
BSTNode* findMinNode(BSTNode* root);
BSTNode* searchNode(BSTNode* root, char* name);
void inorderTraversal(BSTNode* root);
void freeBST(BSTNode* root);

// ==================== MAIN FUNCTION ====================
int main() {
    BSTNode* root = NULL;

    root = insertNode(root, "Charlie");
    root = insertNode(root, "Alice");
    root = insertNode(root, "Eve");
    root = insertNode(root, "Bob");
    root = insertNode(root, "Diana");

    printf("BST in-order (ascending):\n");
    inorderTraversal(root);
    printf("\n");

    printf("\nDeleting 'Charlie'...\n");
    root = deleteNode(root, "Charlie");

    printf("BST after deletion:\n");
    inorderTraversal(root);
    printf("\n");

    BSTNode* found = searchNode(root, "Diana");
    if (found) printf("\nFound: %s\n", found->name);
    else printf("\n'Diana' not found\n");

    freeBST(root);
    return 0;
}



BSTNode* createNode(char* name) {

    BSTNode* new = malloc(sizeof(BSTNode));
    if (new == NULL) return NULL;
    strcpy(new->name, name);
    new->left = new->right = NULL;

    return new;
}


BSTNode* insertNode(BSTNode* root, char* name) {

    BSTNode** trav = &root;
    for(; *trav != NULL && strcmp((*trav)->name, name) != 0;) {
        trav = strcmp((*trav)->name, name)<0 ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
        *trav = createNode(name);
    }
    return root;
}
BSTNode* deleteNode(BSTNode* root, char* name) {

    BSTNode** trav = &root;
    for(; *trav != NULL && strcmp((*trav)->name, name) != 0;) {
        trav = strcmp((*trav)->name, name) <0 ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
        printf(" \"%s\" is not currently in the list...\n", name);
        return root;
    }


    BSTNode* temp = *trav;

    if ((*trav)->right == NULL && (*trav)->left == NULL) {
        free(temp);
        *trav = NULL;
    } else if ((*trav)->left == NULL) {
        *trav = (*trav)->right;
        free(temp);
    } else if  ((*trav)->right == NULL) {
        *trav = (*trav)->left;
        free(temp);
    } else {
        BSTNode** succ = &(*trav)->right;
         while ((*succ)->left) {
            succ = &(*succ)->left;
         }

    
         strcpy((*trav)->name, (*succ)->name);

         root->right = deleteNode(root->right, (*succ)->name);
    }
    return root;
}
BSTNode* findMinNode(BSTNode* root) {

    while (root->left) {
        root = root->left;
    }

   return root;
}
BSTNode* searchNode(BSTNode* root, char* name) {
     if (root == NULL) return NULL;
    
    BSTNode* trav = root;
    for(; trav;) {
        if (strcmp(trav->name, name) == 0) {
            return trav;
        }
    }
    return NULL;
}
void inorderTraversal(BSTNode* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    printf("%s ", root->name);
    inorderTraversal(root->right);
}

void freeBST(BSTNode* root) {
    if (root == NULL) return;

    freeBST(root->left);
    freeBST(root->right);
    free(root);
}
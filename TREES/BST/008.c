#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} Nodetype, *NodePtr, *BST;

/*==============================
    FUNCTION DECLARATIONS
==============================*/

void addElem(BST *root, int data);
bool deleteNode(BST *root, int data);

void inorder(BST root);
void preorder(BST root);
void postorder(BST root);


/*==============================
            MAIN
==============================*/

int main() {
    BST root = NULL;

    // === INSERT ELEMENTS ===
    addElem(&root, 10);
    addElem(&root, 6);
    addElem(&root, 15);
    addElem(&root, 3);
    addElem(&root, 8);
    addElem(&root, 12);
    addElem(&root, 20);

    printf("Inorder traversal: ");
    inorder(root);

    // // === DELETE TEST NODE ===
    printf("\n\nDeleting 8...\n");
    deleteNode(&root, 8);

    printf("Inorder traversal after delete: ");
    inorder(root);

    return 0;
}


/*==============================
     FUNCTION DEFINITIONS
     (YOU FILL THESE)
==============================*/

void addElem(BST *root, int data) {

    NodePtr* trav = root;
    for(;*trav != NULL && (*trav)->data != data;) {
        trav = ((*trav)->data < data) ? &(*trav)->right : &(*trav)->left;

    }

    if (*trav == NULL) {
        NodePtr new = malloc(sizeof(Nodetype));
        if (new == NULL) return;
        new->data = data;
        new->left = NULL;
        new->right = NULL;

        *trav = new;
    }
 
}
bool deleteNode(BST *root, int data) {
    BST* trav = root;
    for(;*trav != NULL && (*trav)->data != data;) {
        trav = (*trav)->data < data ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) return false;

    BST temp = *trav;
    if ((*trav)->right == NULL && (*trav)->left == NULL) {
        free(temp);
        *trav = NULL;
    } else if ((*trav)->left == NULL) {
        *trav = (*trav)->right;
        free(temp);
    } 
    else if ((*trav)->right == NULL) {
        *trav = (*trav)->left;
        free(temp);
    }  else {
        BST* succ = &(*trav)->right;
        while ((*succ)->left) {
            succ = &(*succ)->left;
        }

        (*trav)->data = (*succ)->data;
        deleteNode(succ, (*succ)->data);
    }
    return true;
}


void inorder(BST root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(BST root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(BST root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
        printf("%d ", root->data);

}




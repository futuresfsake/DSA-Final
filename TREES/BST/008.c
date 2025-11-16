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
    printf("\n\nDeleting 12...\n");
    deleteNode(&root, 12);

    printf("Inorder traversal after delete: ");
    inorder(root);

    return 0;
}


/*==============================
     FUNCTION DEFINITIONS
     (YOU FILL THESE)
==============================*/

void addElem(BST *root, int data) {

    BST* trav = root;
    for(; *trav  != NULL && (*trav)->data != data; ) {
        trav = ((*trav)->data < data) ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
        *trav = calloc(1, sizeof(Nodetype));
        if (*trav != NULL) {
            (*trav)->data = data;
        }
    }
}

bool deleteNode(BST *root, int data) {

    BST* trav = root;
    for(;*trav != NULL && (*trav)->data != data;) {
        trav = ((*trav)->data < data) ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) return -1;

    BST temp = *trav;



    if ((*trav)->left == NULL && (*trav)->right == NULL) {
        free(temp);
        *trav = NULL;
    } 

    else if ((*trav)->left == NULL) {
        *trav = (*trav)->right;
        free(temp);
    
    }

    else if ((*trav)->right == NULL) {
        *trav = (*trav)->left;  //! * do not forget to access the ACTUAL NODE, THATS WHY WE DEREFERENCED IT, SO THE BST STRUCTURE WILL CAHGNE
        free(temp); //! IF u just use the double pointer, youre just moving the local variable, this does nto change the tree, it only changes your local var's position!! THINKKK!!!
    
    }

    else  {
        BST* succ = &(*trav)->right;
        while ((*succ)->left != NULL) {
            succ = &(*succ)->left;
        }

        (*trav)->data = (*succ)->data;
        deleteNode(succ, (*succ)->data);
    }
    return 1;
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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Option 1 (Successor) → Replace 10 with 12 (smallest in right subtree).
// Option 2 (Predecessor) → Replace 10 with 8 (largest in left subtree).
// 10
// 6
// 15
// 3
// 8
// 12
// 13


typedef struct node {
    int data;
    struct node* left;
    struct node* right;
}Nodetype, *NodePtr, *BST;


void addElems(BST* list, int data) {
    BST* trav = list;


    // ! traverse until we reach a NULL child position
    for(; *trav != NULL && (*trav)->data != data;) {
        trav = ((*trav)->data < data) ? &(*trav)->right : &(*trav)->left;
    }

    // ! insert the new node at the found NULL position
    if (*trav == NULL)  {
        *trav = calloc(1,sizeof(Nodetype));
        // ! 1 means the number of elements you want to allocate, its just one node
        // ! it sets trav->data to 0, and sets right and left NULL
        if (*trav != NULL) { // ** checking if the dynamic memory allocation failed
            (*trav)->data = data;
        }
    }
}


void inorder(BST list) {
    if (list == NULL) return;

    inorder(list->left);
    printf("%d,", list->data);
    inorder(list->right);

}
void preorder (BST list) {
    if (list == NULL) return;


    printf("%d,", list->data);
    preorder(list->left); 
    preorder(list->right);

}

void postorder (BST list) {
    if (list == NULL) return;


    
    preorder(list->left); 
    preorder(list->right);
    printf("%d,", list->data);
}


bool deletenode(BST *list, int data) {
    BST *trav = list;

    // TODO  Find the node to delete
    for (; *trav != NULL && (*trav)->data != data;) {
        trav = ((*trav)->data < data) ? &(*trav)->right : &(*trav)->left;
    }

    // ! IF NODE NOT FOUND
    if (*trav == NULL) return false;


    // ! SAVE THE NODE TO BE DELETED
    BST temp = *trav;

    // TODO CASE 1: No children
    if ((*trav)->left == NULL && (*trav)->right == NULL) {
        free(temp);
        *trav = NULL; // ! set the parent pointer to null
    }

    // TODO CASE 2A: Only left child
    else if ((*trav)->right == NULL) { // ! node has left child but no right child
        *trav = (*trav)->left;         // ! replace the node with its left child by changing the parent pointer
        free(temp);                     // ! free the original node memory
    }

    // TODO CASE 2B: Only right child
    else if ((*trav)->left == NULL) { // ! node has right no left
        *trav = (*trav)->right;         // ! replace the node with its right child
        free(temp);                     // ! free the original node memory
    }

    // TODO CASE 3: Two children
    else {
        // find successor (smallest in right subtree)
        BST *succ = &(*trav)->right;    // ! find the successer or the smallest node in the right subtree
        while ((*succ)->left != NULL) { // ! traverse right once, then keep going left until null
            succ = &(*succ)->left;
        }

        // copy successor data
        (*trav)->data = (*succ)->data; // ! copy the successor into the node you want to delete

        // recursively delete successor node
        deletenode(succ, (*succ)->data);
    }

    return true;
}


int main() {

     BST root = NULL;

    addElems(&root, 10);
    addElems(&root, 6);
    addElems(&root, 15);
    addElems(&root, 3);
    addElems(&root, 8);
    addElems(&root, 12);
    addElems(&root, 20);

    printf("Inorder traversal: ");
    inorder(root);


    printf("\nDeleting 10...\n");
deletenode(&root, 10);
printf("Inorder traversal after delete: ");
inorder(root);


    return 0;
   
}
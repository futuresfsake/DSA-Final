#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} Node, *BST;

// ==========================================================
// FUNCTION PROTOTYPES
// ==========================================================
BST createNode(int data);                  // create new node
void insert(BST* root, int data);         // insert node
void inorder(BST root);                    // left-node-right
void preorder(BST root);                   // node-left-right
void postorder(BST root);                  // left-right-node
bool deleteNode(BST* root, int data);     // delete node


int searchNode(BST root, int data);
int findMax(BST root);
int findMin(BST root);
int findHeight(BST root);



// ==========================================================
// MAIN FUNCTION – TEST DRIVER
// ==========================================================
int main() {
    BST root = NULL;

    // Insert nodes
    insert(&root, 10);
    insert(&root, 5);
    insert(&root, 15);
    insert(&root, 3);
    insert(&root, 7);
    insert(&root, 12);
    insert(&root, 18);

    // Traversals
    printf("Inorder: ");
    inorder(root);
    printf("\n");

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    printf("Postorder: ");
    postorder(root);
    printf("\n");

    // Test deletion
    printf("Deleting 15...\n");
    deleteNode(&root, 15);

    printf("Inorder after deletion: ");
    inorder(root);
    printf("\n");


     // Test search
    int s = 7;
    printf("Search %d: %s\n", s, searchNode(root, s) ? "Found" : "Not Found");

    s = 20;
    printf("Search %d: %s\n", s, searchNode(root, s) ? "Found" : "Not Found");

    // Test min/max
    printf("Minimum value: %d\n", findMin(root));
    printf("Maximum value: %d\n", findMax(root));

    // Test height
    printf("Height of tree: %d\n", findHeight(root));

  
   

    return 0;
}

// ==========================================================
// FUNCTION STUBS – IMPLEMENT THESE
// ==========================================================
BST createNode(int data) {

    Node* new = malloc(sizeof(Node));
    new->data = data;
    new->left = NULL;
    new->right = NULL;

    return new;
}

void insert(BST* root, int data) {
    // TODO: insert a node maintaining BST property

    BST* trav = root;
    for(;*trav != NULL && (*trav)->data != data;) {
        trav = ((*trav)->data < data) ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
        *trav = createNode(data);
    }
}

void inorder(BST root) {
    // TODO: implement inorder traversal
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);

    }
}

void preorder(BST root) {
    // TODO: implement preorder traversal
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(BST root) {
    // TODO: implement postorder traversal
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ",root->data);
    }
}

bool deleteNode(BST* root, int data) {
    BST* trav = root;

    for(;*trav != NULL && (*trav)->data != data;) {
        trav = ((*trav)->data < data) ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) return false;

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
        *trav = (*trav)->left;
        free(temp);

    } 

    else {
        BST* succ = &(*trav)->left;
        while ((*succ)->right) {
            succ = &(*succ)->right;
        }

        (*trav)->data = (*succ)->data;

        deleteNode(succ, (*succ)->data);
    }


    return true;
}


int searchNode(BST root, int data) {

    BST trav = root;


    for(; trav != NULL; ) {
        if (trav->data == data) {
            return true;
        }
        trav =  ((trav)->data < data) ? (trav)->right : (trav)->left;
    } 

  
    return false;
    
}

int findMax(BST root) {

    BST trav = root;
    while ((trav)->right) {
        trav = (trav)->right;
    }

    return (trav)->data;
    
}
int findMin(BST root) {
    BST trav = (root);
    while ((trav)->left) {
        trav = trav->left;
    }

    return (trav)->data;
}
int findHeight(BST root) {
    if (root == NULL) return -1;

   int lc =  findHeight(root->left);
   int rc =  findHeight(root->right);


    return ((lc < rc ) ? rc : lc) +1;
}
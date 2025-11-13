// ! this problem deals with char,
// ! do strcmp


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct node {
    char data[100];
    struct node* left;
    struct node* right;
} Node, *BST;

// ==========================================================
// FUNCTION PROTOTYPES
// ==========================================================
BST createNode(char* data);                  // create new node
void insert(BST* root, char* data);         // insert node
bool searchNode(BST root, char* data);      // search node
void inorder(BST root);                    // left-node-right
void preorder(BST root);                   // node-left-right
void postorder(BST root);                  // left-right-node
bool deleteNode(BST* root, char* data);     // delete node

// ==========================================================
// MAIN FUNCTION – TEST DRIVER
int main() {
    BST root = NULL;

    // ===== Insert nodes =====
    insert(&root, "Mango");
    insert(&root, "Banana");
    insert(&root, "Lemon");
    insert(&root, "Apple");
    insert(&root, "StarApple");
    insert(&root, "Durian");
    insert(&root, "Avocado");

    // ===== Traversals =====
    printf("Inorder: ");
    inorder(root);    // should print in lexicographical order
    printf("\n");

    printf("Preorder: ");
    preorder(root);   // node-left-right
    printf("\n");

    printf("Postorder: ");
    postorder(root);  // left-right-node
    printf("\n");

    // ===== Search =====
    printf("Searching 'Lemon': %s\n", searchNode(root, "Lemon") ? "Found" : "Not Found");
    printf("Searching 'Grapes': %s\n", searchNode(root, "Grapes") ? "Found" : "Not Found");

    // ===== Delete =====
    printf("Deleting 'Banana'...\n");
    deleteNode(&root, "Banana");
    printf("Inorder after deletion: ");
    inorder(root);
    printf("\n");

    printf("Deleting 'Mango'...\n");
    deleteNode(&root, "Mango");
    printf("Inorder after deletion: ");
    inorder(root);
    printf("\n");

    printf("Deleting 'StarApple'...\n");
    deleteNode(&root, "StarApple");
    printf("Inorder after deletion: ");
    inorder(root);
    printf("\n");

    return 0;
}

// ==========================================================
// FUNCTION STUBS – IMPLEMENT THESE
// ==========================================================
BST createNode(char* data) {
    // TODO: implement node creation

    BST new = malloc(sizeof(Node));
    strcpy(new->data, data);
    new->left = NULL;
    new->right = NULL;
    return new;

    
}

void insert(BST* root, char* data) {
    // TODO: implement insertion maintaining BST property

    BST* trav = root;

    for(; *trav != NULL ;){
         if (strcmp((*trav)->data, data) == 0)  {return;}
        trav =strcmp((*trav)->data, data)<0 ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
        *trav = createNode(data);
    }


}

bool searchNode(BST root, char* data) {
   
    BST trav = root;
    for(; trav != NULL;) {
        if (strcmp(trav->data, data) == 0) {
            return true;
        }

        trav = (strcmp(trav->data, data) <0) ? trav->right : trav->left;
    }
    return false;
}

void inorder(BST root) {
    // TODO: implement inorder traversal

    if (root != NULL) {
        inorder(root->left);
        printf("%s ", root->data);
        inorder(root->right);
    }
}

void preorder(BST root) {
    // TODO: implement preorder traversal
    if (root != NULL) {
        printf("%s ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(BST root) {
    // TODO: implement postorder traversal

    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%s ", root->data);
    }
}

bool deleteNode(BST* root, char* data) {
    // TODO: implement deletion


    BST* trav = root;

    for(;(*trav)!= NULL;) {
        if (strcmp((*trav)->data, data) == 0) {
            break;
        } 
        trav = strcmp((*trav)->data, data) < 0 ? &(*trav)->right : &(*trav)->left;
        
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

        BST* succ = &(*trav)->right;
        while ((*succ)->left) {
            succ = &(*succ)->left;
        }

        strcpy((*trav)->data, (*succ)->data);

        deleteNode(succ, (*succ)->data);
    }
    return true;
}

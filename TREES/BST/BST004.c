/**
 * 
 * 
 * 
 * RECURSIVE VERSION
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ============================
//      STRUCT DEFINITIONS
// ============================

typedef struct CustomerNode {
    int cid;                        // Customer ID (key)
    char *name;                     // dynamically allocated
    struct CustomerNode *left;
    struct CustomerNode *right;
} CustomerNode;

typedef struct CustomerBST {
    CustomerNode *root;
} CustomerBST;


// ============================
//      FUNCTION DECLARATIONS
//      (RECURSIVE ONLY)
// ============================

// Tree init
void init_customer_bst(CustomerBST *tree);

// Node creation
CustomerNode* create_customer_node(int cid, const char *name);

// Recursive insertion
CustomerNode* insert_customer_recursive(CustomerNode *root, CustomerNode *newNode);

// Recursive search
CustomerNode* search_customer_recursive(CustomerNode *root, int cid);

CustomerNode* delete_customer (CustomerNode* root, int cid);

// Recursive free
void free_customer_tree(CustomerNode *root);

// Inorder display
void display_inorder(CustomerNode *root) {
    if (root == NULL) return;
    display_inorder(root->left);
    printf("CID: %d || Name: %s\n", root->cid, root->name);
    display_inorder(root->right);
}


int main() {
    CustomerBST accounts;
    init_customer_bst(&accounts);

    printf("Customer Account BST (Recursive Version)\n\n");

    // Insert nodes
    accounts.root = insert_customer_recursive(accounts.root, create_customer_node(50, "Alice"));
    accounts.root = insert_customer_recursive(accounts.root, create_customer_node(20, "Bob"));
    accounts.root = insert_customer_recursive(accounts.root, create_customer_node(70, "Charlie"));
    accounts.root = insert_customer_recursive(accounts.root, create_customer_node(10, "David"));
    accounts.root = insert_customer_recursive(accounts.root, create_customer_node(30, "Eve"));
    accounts.root = insert_customer_recursive(accounts.root, create_customer_node(60, "Frank"));

    printf("\n--- Inorder Display (Before Deletion) ---\n");
    display_inorder(accounts.root);

    // Search test
    printf("\nSearching for CID 30...\n");
    CustomerNode *found = search_customer_recursive(accounts.root, 30);
    if (found)
        printf("Found: %s\n", found->name);
    else
        printf("Not found.\n");

    // Delete example
    printf("\nDeleting CID 20...\n");
    accounts.root = delete_customer(accounts.root, 20);

    printf("\n--- Inorder Display (After Deletion) ---\n");
    display_inorder(accounts.root);

    // Cleanup
    free_customer_tree(accounts.root);
    accounts.root = NULL;

    printf("\nAll memory successfully freed.\n");
    return 0;
}


void init_customer_bst(CustomerBST *tree) {
    tree->root = NULL;
    printf("initialized succesffully!");

}

// Node creation
CustomerNode* create_customer_node(int cid, const char *name) {

    CustomerNode* new = malloc(sizeof(CustomerNode));
    if (!new) {
        return NULL;
    }

    new->cid = cid;
    new->name = malloc(strlen(name)+1);
    if (!new->name) {
        free(new);
        return NULL;
    }

    strcpy(new->name, name);

    new->left=NULL;
    new->right = NULL;
    return new;
}

// Recursive insertion
CustomerNode* insert_customer_recursive(CustomerNode *root, CustomerNode *newNode) {

    if (search_customer_recursive(root, newNode->cid)) {
        free(newNode->name);
        free(newNode);
        return root;
    }


    if (root == NULL) return newNode;

    if (root->cid < newNode->cid) {
        root->right = insert_customer_recursive(root->right, newNode);
    }
    if (root->cid > newNode->cid) {
        root->left = insert_customer_recursive(root->left, newNode);
    }

    return root;

}

// Recursive search
CustomerNode* search_customer_recursive(CustomerNode *root, int cid) {

    
    if (!root) return NULL;

    if (cid == root->cid) return root;
    if (cid > root->cid) {
        search_customer_recursive(root->right, cid);

    }if (cid < root->cid) {
        search_customer_recursive(root->left, cid);
    }

    return search_customer_recursive(root->right, cid);

    
}

CustomerNode* delete_customer (CustomerNode* root, int cid) {

    CustomerNode** trav = &root;
    for(;*trav != NULL && (*trav)->cid != cid;) {
        trav = ((*trav)->cid < cid) ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) return NULL;

    CustomerNode* temp = *trav;

    if ((*trav)->right == NULL && (*trav)->left == NULL) {
    free(temp->name);

        free(temp);
        *trav =NULL;
    }

    else if (!(*trav)->left) {
        *trav = (*trav)->right;
                free(temp->name);

        free(temp);
    }

       else if (!(*trav)->right) {
        *trav = (*trav)->left;
                free(temp->name);

        free(temp);
    } else {

        CustomerNode** succ = &(*trav)->right;
        while ((*succ)->left) {
            succ = &(*succ)->left;
        }


        free(temp->name);
        
        (*trav)->cid = (*succ)->cid;
        (*trav)->name = malloc(strlen((*succ)->name)+1);
        strcpy((*trav)->name, (*succ)->name);
        *succ = delete_customer(*succ, (*succ)->cid);

    }
    return root;

}

// Recursive free
void free_customer_tree(CustomerNode *root) {
    if (root != NULL) {
        free_customer_tree(root->left);
        free_customer_tree(root->right);
        free(root->name);
        free(root);
    }
}

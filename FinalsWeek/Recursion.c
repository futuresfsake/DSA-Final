#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * BST String Node Definition
 */
typedef struct node {
    char *key;
    struct node* LC;   // Left child
    struct node* RC;   // Right child
} Node, *BST;

/**
 * ===========================
 * Function Prototypes
 * ===========================
 */

// Insert a string key into BST
void insert(BST *root, const char *key_data) {

    BST* trav = root;
    for(; *trav != NULL && strcmp((*trav)->key, key_data)!=0;) {
        trav = (strcmp((*trav)->key,key_data) <0) ? &(*trav)->RC : &(*trav)->LC;
    }


    if (*trav == NULL) {
        Node* new = malloc(sizeof(Node));
        new->key = malloc(strlen(key_data)+1);
        strcpy(new->key, key_data);
        new->RC = new->LC = NULL;

        *trav = new;
    }
}

// Delete a node with given key from BST
BST deleteNode(BST root, const char *key_data) {

    if (root == NULL) {
        return root;
    }


    if (strcmp(root->key, key_data) < 0) {
        root->RC = deleteNode(root->RC, key_data);
    } else if (strcmp(root->key, key_data) > 0) {
        root->LC = deleteNode(root->LC, key_data);
    }

    if (strcmp(root->key, key_data) == 0) {

        if (root->RC == NULL && root->LC == NULL) {
            free(root->key);
            free(root);
            root = NULL;
            return root;
        } else if (root->LC == NULL) {
            Node* temp = root->RC;
            free(root->key);
            free(root);
            return temp;
        }else if (root->RC == NULL) {
            Node* temp = root->LC;
            free(root->key);
            free(root);
            return temp;
        } else {
            BST succ = root->RC;
            while (succ->LC) {
                succ = succ->LC;
            }

            free(root->key);
            root->key = malloc(strlen(succ->key)+1);
            strcpy(root->key, succ->key);

            root->RC = deleteNode(root->RC, succ->key);
        }
        
    }

    return root;
}

/**
 * In-order traversal (Left, Root, Right)
 */
void inorderTraversal(BST root) {
    if (root == NULL) return;

    inorderTraversal(root->LC);           // Visit left subtree
    printf("%s ", root->key);             // Visit root
    inorderTraversal(root->RC);           // Visit right subtree
}

/**
 * Destroy the BST and free memory recursively
 */
void destroyTree(BST root) {
    if (root == NULL) return;

    destroyTree(root->LC);                // Free left subtree
    destroyTree(root->RC);                // Free right subtree
    free(root->key);                      // Free string key
    free(root);                           // Free node itself
}


// // Search for a key in BST
// BST search(BST root, const char *key_data);


// // Find the minimum node in BST (helper for deletion)
// BST findMin(BST root);

// // Find the maximum node in BST (helper)
// BST findMax(BST root);

/**
 * ===========================
 * Main for Testing
 * ===========================
 */
int main() {
    BST tree = NULL;

    printf("--- Initial BST Insertion ---\n");
    insert(&tree, "Mango");
    insert(&tree, "Apple");
    insert(&tree, "Pineapple");
    insert(&tree, "Banana");
    insert(&tree, "Grape");
    insert(&tree, "Orange");
    insert(&tree, "Kiwi");

    printf("\nInitial In-Order Traversal:\n   ");
    inorderTraversal(tree);
    printf("\n");

    printf("\n--- Test 1: Delete Leaf Node (Kiwi) ---\n");
    tree = deleteNode(tree, "Kiwi");
    printf("Resulting Traversal: ");
    inorderTraversal(tree);
    printf("\n");

    printf("\n--- Test 2: Delete Node with 1 Child (Apple) ---\n");
    tree = deleteNode(tree, "Apple");
    printf("Resulting Traversal: ");
    inorderTraversal(tree);
    printf("\n");

    printf("\n--- Test 3: Delete Node with 2 Children (Mango) ---\n");
    tree = deleteNode(tree, "Mango");
    printf("Resulting Traversal: ");
    inorderTraversal(tree);
    printf("\n");

    printf("\n--- Test 4: Delete Non-Existent Node (Zebra) ---\n");
    tree = deleteNode(tree, "Zebra");
    printf("Resulting Traversal: ");
    inorderTraversal(tree);
    printf("\n");

    destroyTree(tree);
    printf("\nTree destroyed and memory freed.\n");

    return 0;
}

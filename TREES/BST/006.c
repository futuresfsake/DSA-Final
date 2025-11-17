#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// ==========================================================
// NESTED STRUCTS
// ==========================================================
typedef struct category {
    int id;
    char name[30];
} Category;

typedef struct product {
    int id;
    char name[50];
    float price;
    Category cat;    // nested struct
} Product;

// ==========================================================
// BST NODE STRUCT
// ==========================================================
typedef struct node {
    Product data;
    struct node* left;
    struct node* right;
} Node, *BST;

// ==========================================================
// FUNCTION PROTOTYPES
// ==========================================================
BST createNode(Product data);                 // create new node
void insert(BST* root, Product data);        // insert node
bool searchNode(BST root, int id);           // search by Product.id
void inorder(BST root);                       // left-node-right
void preorder(BST root);                      // node-left-right
void postorder(BST root);                     // left-right-node
bool deleteNode(BST* root, int id);          // delete node by Product.id

// ==========================================================
// MAIN FUNCTION – TEST DRIVER
// ==========================================================
int main() {
    BST root = NULL;

    Product p1 = {101, "Laptop", 999.99, {1, "Electronics"}};
    Product p2 = {55, "Mouse", 25.50, {1, "Electronics"}};
    Product p3 = {200, "Coffee Mug", 12.75, {2, "Kitchen"}};
    Product p4 = {150, "Monitor", 199.99, {1, "Electronics"}};

    insert(&root, p1);
    insert(&root, p2);
    insert(&root, p3);
    insert(&root, p4);

    printf("Inorder traversal of products:\n");
    inorder(root);
    printf("\n");

    int searchId = 200;
    printf("Search for product ID %d: %s\n", searchId, searchNode(root, searchId) ? "Found" : "Not Found");

    printf("Deleting product ID 55...\n");
    deleteNode(&root, 55);
    printf("Inorder after deletion:\n");
    inorder(root);
    printf("\n");

    return 0;
}

// ==========================================================
// FUNCTION STUBS – IMPLEMENT THESE
// ==========================================================
BST createNode(Product data) {
    // TODO: implement node creation
    return NULL;
}

void insert(BST* root, Product data) {
    // TODO: implement insertion based on Product.id
}

bool searchNode(BST root, int id) {
    // TODO: implement search by Product.id
    return false;
}

void inorder(BST root) {
    // TODO: implement inorder traversal
}

void preorder(BST root) {
    // TODO: implement preorder traversal
}

void postorder(BST root) {
    // TODO: implement postorder traversal
}

bool deleteNode(BST* root, int id) {
    // TODO: implement deletion by Product.id
    return false;
}

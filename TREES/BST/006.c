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
bool deleteNode(BST* root, int id);  
bool deleteNode(BST* root, int id); 
void testBSTDeletion() {
    BST root = NULL;

    // Create some products
    Product p1 = {101, "Laptop", 999.99, {1, "Electronics"}};
    Product p2 = {55, "Mouse", 25.50, {1, "Electronics"}};
    Product p3 = {200, "Coffee Mug", 12.75, {2, "Kitchen"}};
    Product p4 = {150, "Monitor", 199.99, {1, "Electronics"}};
    Product p5 = {75, "Keyboard", 49.99, {1, "Electronics"}};

    // Insert products
    insert(&root, p1);
    insert(&root, p2);
    insert(&root, p3);
    insert(&root, p4);
    insert(&root, p5);

    printf("Initial inorder traversal:\n");
    inorder(root);
    printf("\n");

    // Delete leaf node (p5 -> 75)
    printf("Deleting leaf node Product ID 75...\n");
    deleteNode(&root, 75);
    inorder(root);
    printf("\n");

    // Delete node with one child (p4 -> 150)
    printf("Deleting node with one child Product ID 150...\n");
    deleteNode(&root, 150);
    inorder(root);
    printf("\n");

    // Delete node with two children (p1 -> 101)
    printf("Deleting node with two children Product ID 101...\n");
    deleteNode(&root, 101);
    inorder(root);
    printf("\n");

    // Delete non-existent node
    printf("Deleting non-existent Product ID 999...\n");
    if (!deleteNode(&root, 999)) {
        printf("Product ID 999 not found!\n");
    }
    inorder(root);
    printf("\n");
}
       // delete node by Product.id

// ==========================================================
// MAIN FUNCTION – TEST DRIVER
//

int main() {
    BST root = NULL;
      testBSTDeletion();

    // Create products
    Product p1 = {101, "Laptop", 999.99, {1, "Electronics"}};
    Product p2 = {55, "Mouse", 25.50, {1, "Electronics"}};
    Product p3 = {200, "Coffee Mug", 12.75, {2, "Kitchen"}};
    Product p4 = {150, "Monitor", 199.99, {1, "Electronics"}};
    Product p5 = {75, "Keyboard", 49.99, {1, "Electronics"}};

    // Insert products into BST
    insert(&root, p1);
    insert(&root, p2);
    insert(&root, p3);
    insert(&root, p4);
    insert(&root, p5);

    // Display inorder traversal
    printf("Inorder traversal of products:\n");
    inorder(root);
    printf("\n");

    // Test searching
    int searchId = 200;
    printf("Search for product ID %d: %s\n", searchId, searchNode(root, searchId) ? "Found" : "Not Found");
    searchId = 999;
    printf("Search for product ID %d: %s\n", searchId, searchNode(root, searchId) ? "Found" : "Not Found");

    // Test deletion
    printf("\nDeleting product ID 55...\n");
    deleteNode(&root, 55);
    printf("Inorder after deletion:\n");
    inorder(root);
    printf("\n");

    printf("Deleting product ID 101...\n");
    deleteNode(&root, 101);
    printf("Inorder after deletion:\n");
    inorder(root);
    printf("\n");

    printf("Deleting product ID 200...\n");
    deleteNode(&root, 200);
    printf("Inorder after deletion:\n");
    inorder(root);
    printf("\n");

    return 0;
}


// ==========================================================
// FUNCTION STUBS – IMPLEMENT THESE
// ==========================================================
BST createNode(Product data) {

    BST newProds = malloc(sizeof(Node));
    if (!newProds) return NULL;

    newProds->data = data;
    newProds->left = NULL;
    newProds->right = NULL;

    return newProds;
}

void insert(BST* root, Product data) {
    // TODO: implement insertion based on Product.id

    BST* trav = root;
    for(; *trav != NULL && (*trav)->data.id != data.id;) {
        trav = (*trav)->data.id < data.id ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav != NULL) return;

    BST new = createNode(data);

    *trav = new;
}

bool searchNode(BST root, int id) {
    // TODO: implement search by Product.id
    BST trav = root;
    for(; trav != NULL; ) {
        if (trav->data.id == id) {
            return true;
        }
        trav = trav->data.id < id ? trav->right : trav->left;
    }
    return false;
}


void inorder(BST root) {
    if (root == NULL) return;

    // Traverse left subtree
    inorder(root->left);

    // Display current node's data
    printf("Product ID: %d, Name: %s, Price: %.2f, Category: %s (ID: %d)\n",
           root->data.id,
           root->data.name,
           root->data.price,
           root->data.cat.name,
           root->data.cat.id);

    // Traverse right subtree
    inorder(root->right);
}



bool deleteNode(BST* root, int id) {
    
    BST* trav = root;
    for(;*trav != NULL && (*trav)->data.id != id;) {
        trav = (*trav)->data.id < id ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL)return false;

    BST temp = *trav;

    if ((*trav)->right == NULL && (*trav)->left == NULL) {
        free(temp);
        *trav = NULL;
    }

    else if ((*trav)->right == NULL) {
        *trav = (*trav)->left;
        free(temp);
    }

    else if ((*trav)->left == NULL) {
        *trav = (*trav)->right;
        free(temp);
    } else {
        BST* succ = &(*trav)->right;
        while ((*succ)->left) {
            succ = &(*succ)->left;
        }

        (*trav)->data = (*succ)->data;

        deleteNode(succ, (*succ)->data.id);

    }
    
    return true;
 }

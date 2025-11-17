/**
 * BINARY SEARCH TREE - Complete Implementation in C
 * 
 * Includes all common operations:
 * 1. Insert
 * 2. Search
 * 3. Delete
 * 4. Validate BST (with recursive boundary tracking)
 * 5. Inorder Traversal (sorted output)
 * 6. Find Min/Max
 * 7. Find Height
 * 8. Count Nodes
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// Node structure
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// ==================== CREATE NEW NODE ====================
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ==================== INSERT ====================
TreeNode* insert(TreeNode* root, int data) {
    // TODO: Implement insert operation
    // Base case: if tree is empty, create new node
    
    // If data is less than root, go left
    
    // If data is greater than root, go right
    
    return root;
}

// ==================== SEARCH ====================
bool search(TreeNode* root, int data) {
    // TODO: Implement search operation
    // Base case: if root is NULL, return false
    
    // If found, return true
    
    // If data is less than root, search left
    
    // If data is greater than root, search right
    
    return false;
}

// ==================== FIND MINIMUM ====================
TreeNode* findMin(TreeNode* root) {
    // TODO: Find minimum value node
    // Hint: Keep going left until you can't
    
    return NULL;
}

// ==================== FIND MAXIMUM ====================
TreeNode* findMax(TreeNode* root) {
    // TODO: Find maximum value node
    // Hint: Keep going right until you can't
    
    return NULL;
}

// ==================== DELETE ====================
TreeNode* deleteNode(TreeNode* root, int data) {
    // TODO: Implement delete operation
    // Base case: if root is NULL, return NULL
    
    // Find the node to delete
    
    // Case 1: Node with no children (leaf node)
    
    // Case 2: Node with one child
    
    // Case 3: Node with two children
    // Replace with inorder successor (minimum in right subtree)
    
    return root;
}

// ==================== VALIDATE BST (BOUNDARY TRACKING) ====================
bool validateBSTHelper(TreeNode* node, int min, int max) {
    // TODO: Implement BST validation with boundary tracking
    // This is the KEY recursive function!
    
    // Base case: empty tree is valid
    
    // Check if current node violates BST property
    // (node->data must be > min AND < max)
    
    // Recursively validate left subtree (update max boundary)
    
    // Recursively validate right subtree (update min boundary)
    
    return true;
}

bool isValidBST(TreeNode* root) {
    // TODO: Call helper function with initial boundaries
    return validateBSTHelper(root, INT_MIN, INT_MAX);
}

// ==================== INORDER TRAVERSAL ====================
void inorderTraversal(TreeNode* root) {
    // TODO: Implement inorder traversal (Left -> Root -> Right)
    // This should print values in sorted order for a valid BST
    
}

// ==================== PREORDER TRAVERSAL ====================
void preorderTraversal(TreeNode* root) {
    // TODO: Implement preorder traversal (Root -> Left -> Right)
    
}

// ==================== POSTORDER TRAVERSAL ====================
void postorderTraversal(TreeNode* root) {
    // TODO: Implement postorder traversal (Left -> Right -> Root)
    
}

// ==================== FIND HEIGHT ====================
int height(TreeNode* root) {
    // TODO: Find height of tree
    // Height = longest path from root to leaf
    
    return 0;
}

// ==================== COUNT NODES ====================
int countNodes(TreeNode* root) {
    // TODO: Count total number of nodes
    
    return 0;
}

// ==================== FREE TREE ====================
void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// ==================== MAIN - TEST CASES ====================
int main() {
    TreeNode* root = NULL;
    
    printf("=== Binary Search Tree Operations ===\n\n");
    
    // Test Insert
    printf("Inserting: 50, 30, 70, 20, 40, 60, 80\n");
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    
    // Test Traversals
    printf("\nInorder Traversal (should be sorted): ");
    inorderTraversal(root);
    printf("\n");
    
    printf("Preorder Traversal: ");
    preorderTraversal(root);
    printf("\n");
    
    printf("Postorder Traversal: ");
    postorderTraversal(root);
    printf("\n");
    
    // Test Search
    printf("\nSearch for 40: %s\n", search(root, 40) ? "Found" : "Not Found");
    printf("Search for 100: %s\n", search(root, 100) ? "Found" : "Not Found");
    
    // Test Min/Max
    TreeNode* minNode = findMin(root);
    TreeNode* maxNode = findMax(root);
    printf("\nMinimum value: %d\n", minNode ? minNode->data : -1);
    printf("Maximum value: %d\n", maxNode ? maxNode->data : -1);
    
    // Test Height and Count
    printf("\nHeight of tree: %d\n", height(root));
    printf("Total nodes: %d\n", countNodes(root));
    
    // Test Validate BST
    printf("\nIs Valid BST? %s\n", isValidBST(root) ? "YES" : "NO");
    
    // Test Delete
    printf("\nDeleting node 20...\n");
    root = deleteNode(root, 20);
    printf("Inorder after deletion: ");
    inorderTraversal(root);
    printf("\n");
    
    printf("\nDeleting node 30...\n");
    root = deleteNode(root, 30);
    printf("Inorder after deletion: ");
    inorderTraversal(root);
    printf("\n");
    
    printf("\nDeleting node 50 (root)...\n");
    root = deleteNode(root, 50);
    printf("Inorder after deletion: ");
    inorderTraversal(root);
    printf("\n");
    
    // Validate after deletions
    printf("\nIs still Valid BST? %s\n", isValidBST(root) ? "YES" : "NO");
    
    // Test invalid BST
    printf("\n=== Testing Invalid BST ===\n");
    TreeNode* invalidRoot = createNode(5);
    invalidRoot->left = createNode(1);
    invalidRoot->right = createNode(4);
    invalidRoot->right->left = createNode(3);
    invalidRoot->right->right = createNode(6);
    
    printf("Invalid tree inorder: ");
    inorderTraversal(invalidRoot);
    printf("\n");
    printf("Is Valid BST? %s\n", isValidBST(invalidRoot) ? "YES" : "NO");
    
    // Clean up
    freeTree(root);
    freeTree(invalidRoot);
    
    return 0;
}

/* 
 * EXPECTED OUTPUT:
 * =================
 * Inorder Traversal: 20 30 40 50 60 70 80 (sorted)
 * Minimum: 20
 * Maximum: 80
 * Height: 2
 * Is Valid BST: YES
 * After deletions, tree should remain valid BST
 * Invalid tree should return: NO
 */
// The Rule of Thumb:

// Pre-order deletion (check first): Use when you want to delete the first matching node you encounter
// Post-order deletion (recurse first): Use when you want to delete ALL matching nodes (rare, usually not what you want)

// In your case, you correctly used pre-order checking because you want to delete exactly ONE artifact with the given ID and stop searching!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
    ===== LIBRARY ARCHIVE SYSTEM (RECURSIVE BST) =====
    
    BACKSTORY:
    ----------------
    The library stores ancient scrolls. Each scroll has:
      - scrollID (unique)
      - title
      - author

    BST RULES:
    ----------------
    1. Scrolls are organized ALPHABETICALLY by title.
    2. Titles that are equal go to the LEFT (rare duplicates).
    3. All operations are **recursive** for practice.
*/

typedef struct Scroll {
    int scrollID;
    char title[50];
    char author[50];
} Scroll;

typedef struct Node {
    Scroll data;
    struct Node* left;
    struct Node* right;
} Node;

// === PROTOTYPES ===

// Create a new node
Node* createNode(Scroll data);

// Insert scroll recursively
Node* insertScroll(Node* root, Scroll data);

// Search scroll recursively by title
bool searchScroll(Node* root, const char* title);

// Delete scroll recursively by title
Node* deleteScroll(Node* root, const char* title);

// Print scrolls in-order (alphabetically)
void displayArchive(Node* root);

// Free entire archive recursively
void clearArchive(Node* root) {
    if (root == NULL) return;
    clearArchive(root->left);
    clearArchive(root->right);
    free(root);
}

// === MAIN DRIVER ===
int main() {
    Node* root = NULL;

    Scroll s1 = {101, "Astronomy Basics", "Dr. Nova"};
    Scroll s2 = {102, "Zoology Compendium", "Prof. Fauna"};
    Scroll s3 = {103, "Botany Guide", "Dr. Green"};
    Scroll s4 = {104, "Astronomy Basics", "Dr. Vega"}; // Duplicate title
    Scroll s5 = {105, "Chemistry Notes", "Dr. Molecule"};

    root = insertScroll(root, s1);
    root = insertScroll(root, s2);
    root = insertScroll(root, s3);
    root = insertScroll(root, s4);
    root = insertScroll(root, s5);

    printf("\n=== LIBRARY ARCHIVE ===\n");
    displayArchive(root);

    // Search example
    const char* searchTitle = "Botany Guide";
    if (searchScroll(root, searchTitle))
        printf("\nFound scroll: %s\n", searchTitle);
    else
        printf("\nScroll not found: %s\n", searchTitle);

    // Delete example
    root = deleteScroll(root, "Astronomy Basics");
    printf("\n=== ARCHIVE AFTER DELETION ===\n");
    displayArchive(root);

    // // Clear archive
    // clearArchive(root);
    // root = NULL;

    // return 0;
}

// === FUNCTION SKELETONS ===

Node* createNode(Scroll data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insertScroll(Node* root, Scroll data) {

    if (root == NULL ) {
        return createNode(data);
    }

    if (root->data.scrollID == data.scrollID) return root;

    if (root->data.scrollID < data.scrollID) {
        root->right = insertScroll(root->right, data);
    } else {
        root->left = insertScroll(root->left, data);
    }

    return root;
    

}

bool searchScroll(Node* root, const char* title) {
    // TODO: Recursive search by title

    if (root == NULL) return false;

    if (strcmp(root->data.title, title) == 0) {
        return true;
    }
    return searchScroll(root->left, title) || searchScroll(root->right, title);
}

Node* deleteScroll(Node* root, const char* title) {
    
    if (root == NULL) return root;

   

    if (strcmp(root->data.title, title) == 0) {
        Node* temp = root;
        
        
        if (root->left == NULL && root->right == NULL) {
            free(temp);
           return NULL;

        } else if (root->left == NULL) {
            root = root->right;
            free(temp);
            return root;
        }
        else if (root->right == NULL) {
            root = root->left;
            free(temp);
            return root;
        } else {
            Node* succ = root->right;
            while (succ->left) {
                succ = succ->left;
            }
          
            root->data = succ->data;
            root->right = deleteScroll(root->right, succ->data.title);
             return root;
            
        }
       
        
    }

    //* only recurse if it is not the right
    
    return root;
}

// Print scrolls in alphabetical order (in-order traversal)
void displayArchive(Node* root) {
    if (root == NULL) return;

    // Visit left subtree
    displayArchive(root->left);

    // Print current node
    printf("ScrollID: %d, Title: %s, Author: %s\n",
           root->data.scrollID,
           root->data.title,
           root->data.author);

    // Visit right subtree
    displayArchive(root->right);
}



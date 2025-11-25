#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
    Mystic Library Archive (Binary Search Tree)

    Backstory:
    ----------------
    The Mystic Library stores enchanted books, each with a unique BookID
    and a MagicLevel. The BST organizes books based on their MagicLevel
    for quick retrieval and magical audits.

    Your task is to implement recursive BST operations to manage the library:
    insertions, searches, deletions, traversals, and analytical queries.
*/

// ================================
// Book Struct
// ================================
typedef struct Book {
    int bookID;           // unique ID
    int magicLevel;       // BST key
    char title[50];       // book title
    char author[30];      // author of the book
} Book;

// ================================
// BST Node Struct
// ================================
typedef struct BSTNode {
    Book data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;



// Count total number of books
int countBooks(BSTNode* root) {

    if (root == NULL) return 0;

    int c = countBooks(root->left);
    int c2 = countBooks(root->right);

    return (c + c2) +1;
}

// Find height of BST
int heightBST(BSTNode* root) {

    if (root == NULL) return 0;

    int h = heightBST(root->left);
    int h2 = heightBST(root->right);

    return (h < h2 ? h2 : h) +1;
}

// Find minimum magic-level book
BSTNode* findMinBook(BSTNode* root) {

    if (root == NULL) return NULL;


   while (root->left) {
    root = root->left;
   }
    
   return root;
}

// Find maximum magic-level book
BSTNode* findMaxBook(BSTNode* root) {
    if (root == NULL) return NULL;


   while (root->right) {
    root = root->right;
   }
    
   return root;
}

// Free entire BST recursively
void freeLibrary(BSTNode* root) {
    freeLibrary(root->left);
    freeLibrary(root->right);
    free(root);
    return;
}

// Create a new book node
BSTNode* createBookNode(Book b) {
    BSTNode* new = malloc(sizeof(BSTNode));
    if (!new) return NULL;

    new->data = b;
    new->left = new->right = NULL;
    return new;
}

// Inorder traversal (ascending MagicLevel)
void inorderBooks(BSTNode* root) {
    if (root == NULL) return; // base case: empty subtree

    // 1. Traverse left subtree
    inorderBooks(root->left);

    // 2. Visit current node
    printf("BookID: %d | MagicLevel: %d | Title: %s | Author: %s\n",
           root->data.bookID,
           root->data.magicLevel,
           root->data.title,
           root->data.author);

    // 3. Traverse right subtree
    inorderBooks(root->right);
}


// Insert a book (recursive)
BSTNode* insertBookRecursive(BSTNode* root, Book b) {
    if (root == NULL)  {
        return createBookNode(b);
    }
    if (root->data.bookID == b.bookID) return root;

    if (root->data.magicLevel < b.magicLevel) {
        root->right = insertBookRecursive(root->right, b);
    } else{
        root->left = insertBookRecursive(root->left, b);
    }

    return root;
    
}

// Search for a book by ID (recursive)
bool searchBookByID(BSTNode* root, int bookID) {
    if (root == NULL) return false;

    if (root->data.bookID == bookID) return true;


    return searchBookByID(root->left, bookID) || searchBookByID(root->right, bookID);
} 

// Search for a book by MagicLevel (recursive)
BSTNode* searchBookByMagicLevel(BSTNode* root, int magicLevel) {
    if (root == NULL) return NULL;

    if (root->data.magicLevel == magicLevel) return root;

    BSTNode* result = searchBookByMagicLevel(root->left, magicLevel);
    if (result != NULL) return result;

    return searchBookByMagicLevel(root->right, magicLevel);
}



// Delete a book by ID (recursive)
BSTNode* deleteBookRecursive(BSTNode* root, int bookID) {

    if (root == NULL) return NULL;

    root->left = deleteBookRecursive(root->left, bookID);
    root->right = deleteBookRecursive(root->right, bookID);

    if (root->data.bookID == bookID) {

        BSTNode* temp = root;
        

        if (root->left == NULL && root->right == NULL) {
            free(temp);
            
        
        } else if (root->left == NULL) {
            root = root->right;
            free(temp);
            

        }
        else if (root->right == NULL) {
            root = root->left;
            free(temp);
            

        } else {
            BSTNode* succ = root->right;
            while (succ->left) {
                succ = succ->left;
            }
            root->data = succ->data;
            root->right = deleteBookRecursive(root->right, succ->data.bookID);
        }
        return root;
        
    }

    return root;

}



int main() {
    BSTNode* library = NULL;

    // Sample books
    Book books[] = {
        {201, 50, "Grimoire of Flames", "Merlin"},
        {202, 30, "Scroll of Shadows", "Morgana"},
        {203, 70, "Tome of Lightning", "Zephyr"},
        {204, 55, "Codex of Winds", "Aero"},
        {205, 20, "Book of Silence", "Luna"},
        {206, 65, "Ring of Fire", "Pyra"},
        {207, 45, "Helmet of Insight", "Orion"}
    };

    // Insert books
    for (int i = 0; i < 7; i++) {
        library = insertBookRecursive(library, books[i]);
    }

    // Display BST
    printf("Inorder Traversal (MagicLevel Ascending):\n");
    inorderBooks(library);

    // Count books
    int totalBooks = countBooks(library);
    printf("\nTotal books in library: %d\n", totalBooks);

    // BST height
    int h = heightBST(library);
    printf("Height of BST: %d\n", h);

    // Min & Max magic-level books
    BSTNode* minBook = findMinBook(library);
    BSTNode* maxBook = findMaxBook(library);
    if (minBook) printf("Minimum MagicLevel Book: %s (%d)\n", minBook->data.title, minBook->data.magicLevel);
    if (maxBook) printf("Maximum MagicLevel Book: %s (%d)\n", maxBook->data.title, maxBook->data.magicLevel);

    // Search by ID
    int searchID = 204;
    printf("\nSearching for Book ID %d: %s\n", searchID,
           searchBookByID(library, searchID) ? "Found" : "Not Found");

    // Search by MagicLevel
    int searchMagic = 55;
    BSTNode* magicBook = searchBookByMagicLevel(library, searchMagic);
    if (magicBook) 
        printf("Book with MagicLevel %d found: %s by %s\n", searchMagic, magicBook->data.title, magicBook->data.author);
    else 
        printf("Book with MagicLevel %d not found\n", searchMagic);

    // Delete a book
    printf("\nDeleting Book ID 203 (Tome of Lightning)...\n");
    library = deleteBookRecursive(library, 203);

    // Traverse again
    printf("Inorder Traversal after deletion:\n");
    inorderBooks(library);

    // Free memory
    printf("freeing");
    freeLibrary(library);

    return 0;
}
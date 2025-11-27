#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ===============================
// Type Definitions
// ===============================
typedef struct Book {
    int id;
    char *title;   // Dynamically allocated
    char *author;  // Dynamically allocated
    float price;
    int year;
} Book;

typedef struct BSTNode {
    Book *data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;


Book* create_book(int id, const char* title, const char* author, float price, int year);
BSTNode* insert_book(BSTNode* root, Book* b);
Book* search_book(BSTNode* root, int id);
BSTNode* delete_book(BSTNode* root, int id);
void inorder_traversal(BSTNode* root) {
    if (root == NULL) return;
    inorder_traversal(root->left);
    printf("Title: [%s], ID: [%d]\n",
    root->data->title, root->data->id);
    inorder_traversal(root->right);
}
void free_bst(BSTNode* root);
void update_book(BSTNode* root, int id, const char* new_title, float new_price);

int main() {
    BSTNode *library = NULL;

    printf("=== Library Book Catalog BST ===\n");

    // Create sample books
    Book *b1 = create_book(101, "The C Programming Language", "K&R", 45.5, 1978);
    Book *b2 = create_book(205, "Clean Code", "Robert C. Martin", 37.0, 2008);
    Book *b3 = create_book(310, "Design Patterns", "Gamma et al.", 50.0, 1994);
    Book *b4 = create_book(402, "The Pragmatic Programmer", "Andrew Hunt", 42.0, 1999);
    Book *b5 = create_book(507, "Introduction to Algorithms", "Cormen et al.", 60.0, 2009);

    // Insert books
    library = insert_book(library, b1);
    library = insert_book(library, b2);
    library = insert_book(library, b3);
    library = insert_book(library, b4);
    library = insert_book(library, b5);

    // Display all books in-order
    printf("\n--- In-order Traversal ---\n");
    inorder_traversal(library);

    // Search for a book
    int search_id = 310;
    Book *found = search_book(library, search_id);
    if (found) {
        printf("\n[Search] Found book ID %d: '%s' by %s\n",
              found->id, found->title, found->author);
    } else {
        printf("\n[Search] Book ID %d not found.\n", search_id);
    }

    // Update a book
    update_book(library, 205, "Clean Code (Updated Edition)", 40.0);
    printf("\n--- After Update ---\n");
    inorder_traversal(library);

    // Delete a book
    library = delete_book(library, 310);
    printf("\n--- After Deletion (ID 310) ---\n");
    inorder_traversal(library);

    // Free all memory
    free_bst(library);
    printf("\nAll memory successfully freed.\n");

    return 0;
}



Book* create_book(int id, const char* title, const char* author, float price, int year) {

    Book* book = malloc(sizeof(Book));
    if (book == NULL) {
        free(book);
        return NULL;
    }

    book->id = id;
    book->title =(char*) malloc(strlen(title)+1);
    strcpy(book->title, title);
    book->author = (char*)malloc(strlen(author)+1);
    strcpy(book->author, author);
    book->price = price;
    book->year = year;
    return book;


}
BSTNode* insert_book(BSTNode* root, Book* b) {
    
    BSTNode** trav = &root;
    for(;*trav != NULL && (*trav)->data->id != b->id;) {
        trav = strcmp((*trav)->data->title, b->title)<0 ? &(*trav)->right: &(*trav)->left;
    }
    
    if (*trav == NULL) {
        BSTNode* new = malloc(sizeof(BSTNode));
        new->data = b;
        new->left = new->right = NULL;
        *trav = new;
    }
    return root;
}

Book* search_book(BSTNode* root, int id) {
    if (root == NULL) return NULL;
    
    if (root->data->id == id) return root->data;
    
    Book* f1 = search_book(root->left, id);
    if (f1 != NULL) return f1;
    
    Book* f2 = search_book(root->right, id);
    if (f2 != NULL) return f2;
    
    return NULL;
    
}
BSTNode* delete_book(BSTNode* root, int id) {
    
    if (root == NULL) return root;
    
    
    if (root->data->id == id) {
        BSTNode* temp = root;
        
        if (root->left == NULL && root->right == NULL) {
            free(temp);
            root = NULL;
        } else if (root->left == NULL) {
            root = root->right;
            free(temp);
            
        }else if (root->right == NULL) {
            root = root->left;
            free(temp);
            
        } else {
            BSTNode* pred = root->left;
            while (pred->right) {
                pred = pred->right;
            }
            
            root->data = pred->data;
            root->left = delete_book(root->left, pred->data->id);
        }
        return root;
        
    }
    
    root->left = delete_book(root->left, id);
    root->right = delete_book(root->right, id);
    return root;
}

void free_bst(BSTNode* root) {
    if (root == NULL) return;
    free_bst(root->left);
    free_bst(root->right);
    free(root);
}

void update_book(BSTNode* root, int id, const char* new_title, float new_price) {
    
    if (root == NULL) return;
    
    if (root->data->id == id) {
        
        root->data->title =(char*) malloc(strlen(new_title)+1);
        strcpy(root->data->title, new_title);
        root->data->price = new_price;
        insert_book(root, root->data);
    }
    
    update_book(root->left, id, new_title, new_price);
    update_book(root->right, id, new_title, new_price);
    
}

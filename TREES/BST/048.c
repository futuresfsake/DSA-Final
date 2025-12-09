#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* title;       // BST key
    int copies;        // value
} Book;

typedef struct node {
    Book data;
    struct node* left;
    struct node* right;
} BST;

// ===================== PROTOTYPES =====================
BST* insertBST(BST* root, const char* title, int copies);
BST* deleteBST(BST* root, const char* title);
BST* searchBST(BST* root, const char* title);

void inorder(BST* root);
int countNodes(BST* root);
void freeAll(BST* root);

// ===================== MAIN =====================
void testLibrary() {
    BST* catalog = NULL;

    // Insert books
    catalog = insertBST(catalog, "The Hobbit", 5);
    catalog = insertBST(catalog, "1984", 3);
    catalog = insertBST(catalog, "Dune", 7);
    catalog = insertBST(catalog, "Pride and Prejudice", 4);
    catalog = insertBST(catalog, "Foundation", 6);

    printf("=== Library Catalog (Inorder) ===\n");
    inorder(catalog);

    // Search for some books
    const char* searchTitles[] = {"Dune", "Hamlet"};
    for(int i=0;i<2;i++){
        BST* b = searchBST(catalog, searchTitles[i]);
        if(b) printf("Found '%s' with %d copies\n", b->data.title, b->data.copies);
        else printf("Book '%s' not found\n", searchTitles[i]);
    }

    // Delete a book
    printf("\nDeleting '1984'...\n");
    catalog = deleteBST(catalog, "1984");
    printf("Catalog after deletion:\n");
    inorder(catalog);

    printf("\nTotal books in catalog: %d\n", countNodes(catalog));

    freeAll(catalog);
    printf("\nAll memory freed.\n");
}


void testTwoChildrenDeletion() {
    BST* catalog = NULL;

    // Create a BST with nodes that will form a node with 2 children
    catalog = insertBST(catalog, "Moby Dick", 3);       // root
    catalog = insertBST(catalog, "Alice in Wonderland", 5); // left child
    catalog = insertBST(catalog, "War and Peace", 4);   // right child
    catalog = insertBST(catalog, "Don Quixote", 2);     // left of right child
    catalog = insertBST(catalog, "Hamlet", 6);          // right of right child

    printf("=== Catalog before deletion (Inorder) ===\n");
    inorder(catalog);

    // Delete "War and Peace" (node with two children: "Don Quixote" and "Hamlet")
    printf("\nDeleting 'Moby Dick' (node with two children)...\n");
    catalog = deleteBST(catalog, "Moby Dick");

    printf("Catalog after deletion:\n");
    inorder(catalog);

    // Clean up
    freeAll(catalog);
    printf("\nMemory freed.\n");
}


int main() {
    // testLibrary();
    testTwoChildrenDeletion();
    return 0;
}


BST* insertBST(BST* root, const char* title, int copies) {
    if (root == NULL)  {
        BST* node = malloc(sizeof(BST));
        node->data.title = malloc(strlen(title)+1);
        strcpy(node->data.title, title);
        node->data.copies = copies;

        node->left = NULL;
        node->right = NULL;

        return node;
    }

    if (strcmp(root->data.title, title) ==0) {
        return root;
    }


    if (strcmp(root->data.title, title) < 0) {
        root->right = insertBST(root->right, title, copies);
    } else if (strcmp(root->data.title, title) > 0) {
        root->left = insertBST(root->left, title, copies);
    }


    return root;
}


BST* deleteBST(BST* root, const char* title) {

    
    if (root == NULL) return NULL;

    if (strcmp(root->data.title, title) < 0) {
        root->right = deleteBST(root->right, title);
    } else if (strcmp(root->data.title, title) > 0) {
        root->left = deleteBST(root->left, title);
    }


    if (strcmp(root->data.title, title) == 0) {
        if (root->left == NULL && root->right == NULL) {
            free(root->data.title);
            free(root);
            return NULL;   
        } else if (root->right ==NULL) {
            BST* temp = root->left;
            free(root->data.title);
            free(root);
            return temp;
        } else if (root->left == NULL) {
            BST* temp = root->right;
            free(root->data.title);
            free(root);
            return temp;
        } else {
            BST* succ = root->right;
            while (succ->left) {
                succ = succ->left;
            }

            free(root->data.title);
            root->data.title = malloc(strlen(succ->data.title)+1);
            strcpy(root->data.title, succ->data.title);
            root->data.copies = succ->data.copies;

            root->right = deleteBST(root->right, succ->data.title);
        }
    }
    return root;
}


BST* searchBST(BST* root, const char* title) {

    if (root == NULL) return NULL;

    if (strcmp(root->data.title, title) ==0) return root;

    BST* left = searchBST(root->left, title);
    if (left != NULL) return left;

    BST* right = searchBST(root->right, title);
    if (right != NULL) return right;

    

    return NULL;

} 

void inorder(BST* root) {
    if (root == NULL) return;

    inorder(root->left);
    printf("Title: %s | Copies; %d \n", root->data.title, root->data.copies);
    inorder(root->right);
}


int countNodes(BST* root) {

    if (root == NULL) return 0;

    int left = countNodes(root->left);
    int right = countNodes(root->right);

    return left+right+1;
}
void freeAll(BST* root) {

    if (root == NULL) return;

    freeAll(root->left);
    freeAll(root->right);
    free(root->data.title);
    free(root);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NAME_LEN 50

// =================== STRUCT DEFINITIONS ===================
typedef struct Book {
    int bookID;
    char title[NAME_LEN];
    struct Book *left;
    struct Book *right;
} Book;

typedef struct {
    Book* stack[100];
    int top;
}Stack;



void push(Stack* s, Book* node);
Book* pop(Stack* s);
// =================== FUNCTION PROTOTYPES ===================
Book* insertBook(Book* root, int bookID, char* title);
Book* deleteBook(Book* root, int bookID);
Book* searchBook(Book* root, int bookID);
void inorderTraversal(Book* root);
void preorderTraversal(Book* root);
void postorderTraversal(Book* root);
void bfs(Book* root) {

    Book* queue[100];
    int front = 0;
    int rear = 0;


    queue[rear++] = root;

    while (front < rear) {
        Book* trav = queue[front++];
     printf("ID: %d | Title: %s\n", trav->bookID, trav->title);

     if (trav->left) queue[rear++] = trav->left;
     if (trav->right) queue[rear++] = trav->right;

    }


}

// =================== MAIN ===================
int main() {
    Book* catalog = NULL;

    catalog = insertBook(catalog, 101, "Moby Dick");
    catalog = insertBook(catalog, 50, "Alice in Wonderland");
    catalog = insertBook(catalog, 200, "War and Peace");
    catalog = insertBook(catalog, 75, "Don Quixote");
    catalog = insertBook(catalog, 25, "Hamlet");

    printf("=== Inorder Traversal (Sorted by ID) ===\n");
    inorderTraversal(catalog);

    printf("\n=== Preorder Traversal ===\n");
    preorderTraversal(catalog);

    printf("\n=== Postorder Traversal ===\n");
    postorderTraversal(catalog);

    printf("\n=== BFS ===\n");
    bfs(catalog);

    printf("\n=== Searching for Book ID 75 ===\n");
    Book* found = searchBook(catalog, 75);
    if(found) printf("Found: %d - %s\n", found->bookID, found->title);
    else printf("Book not found.\n");

    printf("\n=== Deleting Book ID 50 ===\n");
    catalog = deleteBook(catalog, 50);
    printf("Inorder after deletion:\n");
    inorderTraversal(catalog);

    return 0;
}


Book* insertBook(Book* root, int bookID, char* title) {

    if (root == NULL) {
        Book* node = malloc(sizeof(Book));
        if(node == NULL) return NULL;

        node->bookID = bookID;
        strcpy(node->title, title);
        node->left = node->right = NULL;

        return node;
    }


    if (strcmp(root->title,title) == 0) {
        return root;
    }




    if (strcmp(root->title, title) < 0) {
        root->right = insertBook(root->right, bookID, title);
    } else if (strcmp(root->title, title) > 0) {
        root->left = insertBook(root->left, bookID, title);
    }

    return root;
}


Book* deleteBook(Book* root, int bookID) {

    if (root == NULL) return NULL;

    root->left = deleteBook(root->left, bookID);
    root->right = deleteBook(root->right, bookID);

    if (root->bookID == bookID) {

        if (root->left == NULL && root->right == NULL) {
            free(root);
            root=NULL;
            return root;
        } else if (root->left == NULL) {
            Book* temp = root->right;
            free(root);
            return temp;
        }  else if (root->right == NULL) {
            Book* temp = root->left;
            free(root);
            return temp;
        } else {
            Book* succ = root->right;
            while (succ->left) {
                succ = succ->left;
            }

            root->bookID = succ->bookID;
            strcpy(root->title, succ->title);


        root->right = deleteBook(root->right, succ->bookID);    
        }
    }

    
    return root;
}
Book* searchBook(Book* root, int bookID) {

    if (root==NULL) return NULL;

    if (root->bookID == bookID) return root;

    Book* left = searchBook(root->left, bookID);
    if (left != NULL) return left;

    Book* right = searchBook(root->right, bookID);
    if (right != NULL) return right;

    return NULL;

}


void inorderTraversal(Book* root) {

    Stack s;
    s.top = -1;
    Book* trav = root;

    while (trav || s.top != -1) {
        while (trav) {
            push(&s, trav);

            trav = trav->left;
        }

        trav = pop(&s);
        printf("ID: %d | Title: %s\n", trav->bookID, trav->title);
        trav = trav->right;
    }
}


void preorderTraversal(Book* root) {
    Stack s;
    s.top=-1;

    push(&s, root);
    while (s.top != -1) {
        Book* trav = pop(&s);
    printf("ID: %d | Title: %s\n", trav->bookID, trav->title);

    if (trav->right) push(&s, trav->right);
    if (trav->left) push(&s, trav->left);

        
    }
}

void postorderTraversal(Book* root) {
    

    Stack s1,s2;

    s1.top = -1;
    s2.top = -1;

    push(&s1, root);

    while (s1.top != -1) {

        Book* trav = pop(&s1);
        push(&s2, trav);


        if (trav->left) push(&s1, trav->left);
        if (trav->right) push(&s1, trav->right);
    }

    while (s2.top != -1) {
        Book* trav = pop(&s2);
      printf("ID: %d | Title: %s\n", trav->bookID, trav->title);

    }
}



void push(Stack* s, Book* node) {
    s->stack[++s->top] = node;
}
Book* pop(Stack* s) {
    return s->stack[s->top--];
}
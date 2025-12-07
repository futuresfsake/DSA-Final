#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================== NESTED STRUCT DEFINITIONS ====================

// 1. The Inner Struct (The Data)
typedef struct {
    char name[50];   // <--- BASIS OF ORDERING (String)
    int id;
    float gpa;
} Student;

// 2. The Outer Struct (The Node)
typedef struct node {
    Student data;           // Nested struct stored here
    struct node *left;
    struct node *right;
} BSTNode;

// ==================== PROTOTYPES ====================

typedef struct {
    BSTNode* stack[100];
    int top;
}Stack;

/* Stack Operations*/ 
void push(Stack *s, BSTNode* node);
BSTNode* pop(Stack* s);
/* --- Core Operations --- */
// Note: Insert now takes the full Student struct
BSTNode* createNode(Student data);
BSTNode* insert(BSTNode* root, Student data); 

// Search now takes a string (name) instead of an int
BSTNode* search(BSTNode* root, char* name); 


/* --- Traversals --- */
void inorderTraversal(BSTNode* root); // Should print names alphabetically
void preorderTraversal(BSTNode* root);
void postorderTraversal(BSTNode* root);

/* --- Helper Operations --- */
Student findMin(BSTNode* root); // Returns student with "smallest" name (e.g., Aaron)
Student findMax(BSTNode* root); // Returns student with "largest" name (e.g., Zelda)
void freeTree(BSTNode* root);

// ==================== MAIN FUNCTION ====================
int main() {
    BSTNode *root = NULL;

    // 1. Setup Dummy Data
    Student s1 = {"Charlie", 101, 3.5};
    Student s2 = {"Alice", 102, 3.9};
    Student s3 = {"Bob", 103, 2.8};
    Student s4 = {"David", 104, 3.2};
    Student s5 = {"Zelda", 105, 4.0}; // Added to test Max

    // 2. Test Insert
    printf("--- 1. INSERTION ---\n");
    printf("Inserting Charlie, Alice, Bob, David, Zelda...\n");
    root = insert(root, s1);
    root = insert(root, s2);
    root = insert(root, s3);
    root = insert(root, s4);
    root = insert(root, s5);

    // 3. Test Search
    printf("\n--- 2. SEARCH ---\n");
    char* target = "Bob";
    printf("Searching for '%s'...\n", target);
    BSTNode* result = search(root, target);
    if (result != NULL) {
        printf(" [FOUND] Name: %s | ID: %d | GPA: %.2f\n", 
               result->data.name, result->data.id, result->data.gpa);
    } else {
        printf(" [NOT FOUND] %s is not in the tree.\n", target);
    }

    // 4. Test Min/Max
    printf("\n--- 3. MIN / MAX ---\n");
    Student minStudent = findMin(root);
    Student maxStudent = findMax(root);
    printf("Min (Alphabetically First): %s\n", minStudent.name);
    printf("Max (Alphabetically Last):  %s\n", maxStudent.name);

    // 5. Test Traversals
    printf("\n--- 4. TRAVERSALS ---\n");
    
    printf("Preorder (Iterative): ");
    preorderTraversal(root);
    printf("\n");

    printf("Inorder (Iterative):  ");
    inorderTraversal(root);
    printf("\n");

    printf("Postorder (Recursive):");
    postorderTraversal(root);
    printf("\n");

    // 6. Test Free
    printf("\n--- 5. CLEANUP ---\n");
    printf("Freeing tree memory...\n");
    freeTree(root);
    printf("Tree freed successfully.\n");

    return 0;
}

void push(Stack* s, BSTNode* node) {
    s->stack[++s->top] = node;
}
BSTNode* pop(Stack* s) {

    return s->stack[s->top--];
}


BSTNode* createNode(Student data) {

    BSTNode* new = malloc(sizeof(BSTNode));
    if (new == NULL) return NULL;
    
    new->data = data;
    new->left = new->right = NULL;
    
    return new;
}

BSTNode* insert(BSTNode* root, Student data) {

    BSTNode** trav = &root;
    for(; *trav != NULL && strcmp((*trav)->data.name, data.name) != 0;) {
        trav = strcmp((*trav)->data.name, data.name) < 0 ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
        BSTNode* new = createNode(data);
        *trav = new;
    }

    return root;

}

BSTNode* search(BSTNode* root, char* name) {
    Stack s;
    s.top = -1;

    push(&s, root);
    while (s.top != -1) {
        BSTNode* trav = pop(&s);
        if (strcmp(trav->data.name, name) == 0) {
            return trav;
        }

        
        if (trav->right) push(&s, trav->right);
        if (trav->left) push(&s, trav->left);
    
    }

   

    return NULL;
}



void inorderTraversal(BSTNode* root) {

    Stack s;
    s.top = -1;

    BSTNode* trav = root;

    while (trav || s.top != -1) {
        while (trav) {
            push(&s, trav);
            trav = trav->left;
        }

        trav = pop(&s);
        printf("%s ", trav->data.name);
        trav = trav->right;
    }
}


void preorderTraversal(BSTNode* root) {

    Stack s;
    s.top = -1;

    push(&s, root);
    
    while (s.top != -1) {
        BSTNode* trav = pop(&s);
        printf("%s ", trav->data.name);

        if (trav->right) push(&s, trav->right);
        if (trav->left) push (&s, trav->left);
    }
}


void postorderTraversal(BSTNode* root) {
    Stack s1, s2;

    s1.top = -1;
    s2.top = -1;

    push(&s1, root);

    while (s1.top != -1) {
        BSTNode* trav = pop(&s1);
        push(&s2, trav);
        if (trav->left) push(&s1, trav->left);

        if (trav->right) push(&s1, trav->right);
    }

    while (s2.top != -1) {
        BSTNode* trav = pop(&s2);
        printf("%s ", trav->data.name);
    }
}


Student findMin(BSTNode* root) {
    Student dummy = {0};

    if (root == NULL) return dummy;

    while (root->left) {
        root = root->left;
    }
    return root->data;
}

Student findMax(BSTNode* root) {
    Student dummy = {0};
    if (root == NULL) return dummy;

    while (root->right) {
        root = root->right;
    }
    return root->data;
}


void freeTree(BSTNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
    
}
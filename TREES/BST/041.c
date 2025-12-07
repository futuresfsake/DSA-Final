#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} BSTNode;


typedef struct {
    BSTNode* stack[100];
    int top;
}Stack;

void push(Stack* s, BSTNode* node) {

    s->stack[++s->top] = node;
}
BSTNode* pop(Stack *s) {
    return s->stack[s->top--];

}
// 1. Insert a value into BST
BSTNode* insertNode(BSTNode *root, int val) {
    BSTNode** trav = &root;

    for(; *trav != NULL && (*trav)->value != val;) {
        trav = (*trav)->value < val ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
    
    BSTNode* new = malloc(sizeof(BSTNode));
    new->value = val;
    new->left = NULL;
    new->right = NULL;

    *trav = new;

    }
    return root;
}







// Utility functions
void inorderDisplay(BSTNode *root) {

    Stack s;
    s.top = -1;
    BSTNode* trav = root;

    while (trav || s.top != -1) {
        while (trav) {
            push(&s, trav);
            trav = trav->left;

        }
        trav = pop(&s);
        printf("%d ", trav->value);
        trav = trav->right;
    }
}
void preorderDisplay(BSTNode *root) {
    if (root == NULL) return;

    Stack s1;
    s1.top = -1;
    push(&s1, root);

    while (s1.top != -1) {
        BSTNode* trav = pop(&s1);
        printf("%d ", trav->value);


        if (trav->right) push(&s1, trav->right);
        if (trav->left) push(&s1, trav->left);

    }
}
void postderDisplay(BSTNode *root) {
    if (root == NULL) return;

    Stack s1, s2;
    s1.top = -1;
    s2.top = -1;

    push(&s1, root);
    while (s1.top != -1) {
        BSTNode* trav = pop(&s1);
        push(&s2, trav);

        if (trav->left) push (&s1, trav->left);
        if (trav->right) push(&s1, trav->right);
        
    }

    while (s2.top != -1) {
        BSTNode* trav = pop(&s2);
        printf("%d ", trav->value);
    }
}

void BFS (BSTNode* root) {

    if (root == NULL) return;

    BSTNode* queue[100];
    int front = 0;
    int rear = 0;

    queue[rear++] = root;


    while (front < rear) {
        BSTNode* trav = queue[front++];

        printf("%d ", trav->value);
        if (trav->left) queue[rear++] = trav->left;
        if (trav->right) queue[rear++] = trav->right;
    }
}


void freeBST(BSTNode *root) {
    if (root == NULL) return;
    freeBST(root->left);
    freeBST(root->right);
    free(root);
}



int main() {
    BSTNode *root = NULL;

    // ===== Insert values into BST =====
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        root = insertNode(root, values[i]);
    }

    // ===== Display Traversals =====
    printf("Inorder (should be sorted): ");
    inorderDisplay(root);
    printf("\n");

    printf("Preorder: ");
    preorderDisplay(root);
    printf("\n");

    printf("Postorder: ");
    postderDisplay(root);
    printf("\n");

    printf("BFS / Level-order: ");
    BFS(root);   // BFS prints nothing in your code, so let's modify it to print
    printf("\n");

    // Fix BFS printing:
    printf("BFS (Printed): ");
    // Temporary BFS printing block
    {
        BSTNode* queue[100];
        int front = 0, rear = 0;
        queue[rear++] = root;

        while (front < rear) {
            BSTNode* trav = queue[front++];
            printf("%d ", trav->value);
            if (trav->left) queue[rear++] = trav->left;
            if (trav->right) queue[rear++] = trav->right;
        }
    }
    printf("\n");

    // ===== Cleanup =====
    freeBST(root);

    return 0;
}

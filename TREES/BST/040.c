#include <stdio.h>
#include <stdlib.h>

// ==================== STRUCT DEFINITION ====================
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
    s->stack[++(s->top)] = node;
}
BSTNode* pop(Stack* s) {
    return s->stack[s->top--];
}

// ==================== FUNCTION DECLARATIONS ====================
BSTNode* insertNode(BSTNode *root, int val) {

    BSTNode** trav = &root;
    for(; *trav != NULL && (*trav)->value != val; ) {
        trav = (*trav)->value < val ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
        BSTNode* new = malloc(sizeof(BSTNode));
        new->value = val;
        new->left = new->right = NULL;

        *trav = new;
    }
    return root;
}

int sumNodes(BSTNode *root) {
    if (root == NULL) return 0;

   
    int left = sumNodes(root->left);
    
    int right =sumNodes(root->right);

    return left + right + root->value;
}
int height(BSTNode *root) {
    if (root == NULL) return -1;

    int h1 = height(root->left);
    int h2 = height(root->right);

    return (h1 < h2 ? h2 : h1)+1;
}
int countLeaves(BSTNode *root) {
    if (root == NULL) return 0;

    int c = countLeaves(root->left);
    int c2 = countLeaves(root->right);
    return c+c2+1;
}
void inorderDisplay(BSTNode *root);
void freeBST(BSTNode *root) {
    if (root == NULL) {
        return;
    }

    freeBST(root->left);
    freeBST(root->right);
    free(root);
}


void preorder(BSTNode* root) {
    
    if (root == NULL) return;

    Stack s;
    s.top = -1;
    push(&s, root);

    while (s.top != -1) {
        BSTNode* trav = pop(&s);
        printf("%d ", trav->value);

        if (trav->right) push(&s, trav->right);
        if (trav->left) push(&s, trav->left);
    }

}

void postorder (BSTNode* root) {

    if (root == NULL) return;

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
        printf("%d ", trav->value);
    }
}


void BFS(BSTNode* root) {

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
// ==================== MAIN FUNCTION ====================
int main() {
    BSTNode *root = NULL;

    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values)/sizeof(values[0]);

    // Insert nodes into BST
    for(int i=0; i<n; i++) {
        root = insertNode(root, values[i]);
    }

    // Display BST in-order
    printf("\nBST in-order: ");
    inorderDisplay(root);
    printf("\nBST preorder:\n");
    preorder(root);
    printf("\nBST postorder:\n");
    postorder(root);
    printf("\nBFS:\n");
    BFS(root);
    // Recursive computations
    printf("\nSum of all nodes: %d\n", sumNodes(root));
    printf("Height of BST: %d\n", height(root));
    printf("Number of leaves: %d\n", countLeaves(root));

    // Free memory
    freeBST(root);
    return 0;
}

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


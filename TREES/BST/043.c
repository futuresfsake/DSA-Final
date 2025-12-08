#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ==================== STRUCT DEFINITIONS ====================
typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} BSTNode;

// ==================== PROTOTYPES ====================

typedef struct {
    BSTNode* stack[100];
    int top;
}Stack;

void push(Stack* s, BSTNode* Node) {
    s->stack[++s->top] = Node;
}
BSTNode* pop(Stack* s) {
    return s->stack[s->top--];
}

/* --- Core Operations --- */
BSTNode* createNode(int value);
BSTNode* insert(BSTNode* root, int value);
BSTNode* deleteNode(BSTNode* root, int value);
bool search(BSTNode* root, int value);

/* --- DFS Traversals (Recursive or Iterative) --- */
void preorderTraversal(BSTNode* root);
void inorderTraversal(BSTNode* root);
void postorderTraversal(BSTNode* root);

/* --- BFS Traversal --- */
void levelOrderTraversal(BSTNode* root);

/* --- 5 Additional Operations --- */
int findMin(BSTNode* root);               // Returns minimum value
int findMax(BSTNode* root);               // Returns maximum value
int getHeight(BSTNode* root);             // Returns max depth (edges)
int countLeaves(BSTNode* root);           // Returns count of leaf nodes
int sumNodes(BSTNode* root);              // Returns sum of all values

// ==================== MAIN FUNCTION ====================
int main() {
    BSTNode *root = NULL;

    // 1. Test Core Operations
    printf("Inserting nodes...\n");
    int values[] = {50, 30, 20, 40, 70, 60, 80};
    for(int i = 0; i < 7; i++) {
        root = insert(root, values[i]);
    }

    if (search(root, 60)) printf("Value 60 found!\n");
    else printf("Value 60 not found.\n");

    // 2. Test DFS Traversals
    printf("\n--- DFS Traversals ---\n");
    printf("Preorder: ");
    preorderTraversal(root);
    printf("\nInorder:  ");
    inorderTraversal(root);
    printf("\nPostorder: ");
    postorderTraversal(root);
    printf("\n");

    // 3. Test BFS Traversal
    printf("\n--- BFS Traversal ---\n");
    printf("Level Order: ");
    levelOrderTraversal(root);
    printf("\n");

    // // 4. Test Additional Operations
    printf("\n--- Statistics ---\n");
    printf("Minimum Value: %d\n", findMin(root));
    printf("Maximum Value: %d\n", findMax(root));
    printf("Tree Height: %d\n", getHeight(root));
    printf("Leaf Count: %d\n", countLeaves(root));
    printf("Sum of Nodes: %d\n", sumNodes(root));

    // 5. Test Deletion
    printf("\nDeleting 20 (Leaf)...\n");
    root = deleteNode(root, 20);
    printf("Inorder after delete: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}


BSTNode* createNode(int value) {
    BSTNode* new = malloc(sizeof(BSTNode));
    if (new==NULL) return NULL;
    new->value = value;
    new->left = new->right = NULL;
    return new;
}


BSTNode* insert(BSTNode* root, int value) {

    BSTNode** trav = &root;
    for(; *trav != NULL && (*trav)->value != value;) {
        trav = (*trav)->value < value ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
        *trav = createNode(value);
        return root;
    }
    return root;
}


BSTNode* deleteNode(BSTNode* root, int value) {

    BSTNode** trav = &root;

    for(; *trav != NULL && (*trav)->value != value;) {
        trav = (*trav)->value < value ? &(*trav)->right : &(*trav)->left;
    }


    if (*trav == NULL) {
        printf("%d is nonexistent...\n", value);
        return root;
    }


    BSTNode* temp = *trav;

    if ((*trav)->left == NULL && (*trav)->right == NULL) {
        free(temp);
        *trav = NULL;
       
        

    }

    else if ((*trav)->left == NULL) {
        *trav = (*trav)->right;
        free(temp);
        
    } else if ((*trav)->right == NULL) {
        *trav = (*trav)->left;
        free(temp);
    } else {
        BSTNode** succ = &(*trav)->right;
        while ((*succ)->left) {
            succ = &(*succ)->left;
        }

        (*trav)->value = (*succ)->value;

    //    root->right = deleteNode(root->right, (*succ)->value);

    BSTNode* target = *succ;
    *succ = target->right;
    free(target);

    }


    return root;
}
bool search(BSTNode* root, int value) {
    BSTNode* trav = root;
    for(; trav != NULL;) {
        if (trav->value == value) {
            return true;
        }
        trav = trav->value < value ? trav->right : trav->left;
    }

    return false;
}

void preorderTraversal(BSTNode* root) {

    Stack s;
    s.top = -1;
    push(&s, root);

    while (s.top != -1) {
        BSTNode* node = pop(&s);
        printf("%d ", node->value);

        if (node->right) push(&s, node->right);
        if (node->left) push(&s, node->left);
    }
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
        printf("%d ", trav->value);
        trav = trav->right;
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
        printf("%d ",trav->value);
    }
}

void levelOrderTraversal(BSTNode* root) {

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


int findMin(BSTNode* root) {
    
    BSTNode* trav = root;

    while (trav->left) {
        trav = trav->left;
    }

    return trav->value;



}            
int findMax(BSTNode* root) {
    BSTNode* trav = root;

    while (trav->right) {
        trav = trav->right;
    }
    return trav->value;
}
int getHeight(BSTNode* root) {

    if (root == NULL) return -1;
    int c = getHeight(root->left);
    int c1 = getHeight(root->right);

    return (c < c1 ? c1 : c) +1; 
}
int countLeaves(BSTNode* root) {

    if (root == NULL) return 0;

    if (root->left == NULL && root->right == NULL) {
        return 1;
    }

    int c = countLeaves(root->left);
    int c2 = countLeaves(root->right);

    return c+c2;
}
int sumNodes(BSTNode* root) {

    if (root == NULL) return 0;


 
    return sumNodes(root->left)+sumNodes(root->right)+root->value;
}
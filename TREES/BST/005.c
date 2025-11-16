#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ==========================================================
// BST NODE
// ==========================================================
typedef struct node {
    char data;
    struct node* left;
    struct node* right;
} Node, *BST;

// ==========================================================
// QUEUE NODE (FOR BFS)
// ==========================================================
typedef struct qnode {
    BST data;
    struct qnode* next;
} Qnode;

typedef struct {
    Qnode* front;
    Qnode* rear;
} Queue;

// ==========================================================
// FUNCTION PROTOTYPES
// ==========================================================
BST createNode(char data);
void insert(BST* root, char data);
void inorder(BST root);
bool searchNode(BST root, char data);
bool deleteNode(BST* root, char data);

void initQueue(Queue* Q);
bool isEmpty(Queue* Q);
void Enqueue(Queue* Q, BST data);
BST Dequeue(Queue* Q);
void BFS(BST root);

// ==========================================================
// MAIN
// ==========================================================
int main() {
    BST root = NULL;

    insert(&root, 'M');
    insert(&root, 'F');
    insert(&root, 'T');
    insert(&root, 'A');
    insert(&root, 'H');
    insert(&root, 'R');
    insert(&root, 'Z');

    printf("BFS Traversal: ");
    BFS(root);

    printf("\n\nSearching 'H': %s\n", searchNode(root, 'H') ? "Found" : "Not Found");
    printf("Searching 'X': %s\n", searchNode(root, 'X') ? "Found" : "Not Found");

    printf("\nDeleting 'F'...\n");
    deleteNode(&root, 'F');

    printf("Inorder after deletion: ");
    inorder(root);
    printf("\n");

    return 0;
}

// ==========================================================
// BST FUNCTIONS
// ==========================================================
BST createNode(char data) {
    BST new = malloc(sizeof(Node));
    new->data = data;
    new->left = new->right = NULL;
    return new;
}

void insert(BST* root, char data) {
    BST* trav = root;

    while (*trav != NULL) {
        if (data == (*trav)->data) return; // no duplicates
        trav = (data > (*trav)->data) ? &(*trav)->right : &(*trav)->left;
    }

    *trav = createNode(data);
}

void inorder(BST root) {
    if (!root) return;
    inorder(root->left);
    printf("%c ", root->data);
    inorder(root->right);
}

bool searchNode(BST root, char data) {
    while (root != NULL) {
        if (root->data == data) return true;
        root = (data > root->data) ? root->right : root->left;
    }
    return false;
}

bool deleteNode(BST* root, char data) {
    BST* trav = root;

    while (*trav != NULL && (*trav)->data != data) {
        trav = (data > (*trav)->data) ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) return false;

    BST temp = *trav;

    // Case 1: Leaf
    if (temp->left == NULL && temp->right == NULL) {
        *trav = NULL;
        free(temp);
    }
    // Case 2: One right child
    else if (temp->left == NULL) {
        *trav = temp->right;
        free(temp);
    }
    // Case 3: One left child
    else if (temp->right == NULL) {
        *trav = temp->left;
        free(temp);
    }
    // Case 4: Two children
    else {
        BST* pred = &temp->left;
        while ((*pred)->right != NULL) {
            pred = &(*pred)->right;
        }

        temp->data = (*pred)->data;
        deleteNode(pred, (*pred)->data);
    }

    return true;
}

// ==========================================================
// QUEUE FUNCTIONS FOR BFS
// ==========================================================
// ==========================================================
// QUEUE IMPLEMENTATION FOR BFS (LEVEL-ORDER TRAVERSAL)
// ==========================================================

// Initialize queue so both pointers are NULL
void initQueue(Queue* Q) {
    Q->front = Q->rear = NULL;
}

// Return true if queue has no elements
bool isEmpty(Queue* Q) {
    return Q->front == NULL;
}

// Add a BST node to the queue (enqueue)
void Enqueue(Queue* Q, BST data) {

    // Create a new queue node
    Qnode* new = malloc(sizeof(Qnode));
    new->data = data;   // store BST pointer
    new->next = NULL;

    // Case 1: queue is empty
    if (Q->rear == NULL) {
        Q->front = Q->rear = new;
    } 
    // Case 2: queue already has elements
    else {
        Q->rear->next = new;  // attach to end
        Q->rear = new;        // move rear pointer
    }
}

// Remove a node (dequeue) and return its BST pointer
BST Dequeue(Queue* Q) {
    if (isEmpty(Q)) return NULL;

    Qnode* temp = Q->front;   // node to remove
    BST val = temp->data;     // value to return
    //* the data inside the queue is not an int, its a pointer to a BST node, refer to the

    // Move front pointer to next
    Q->front = temp->next;

    // If queue becomes empty, reset rear too
    if (Q->front == NULL)
        Q->rear = NULL;

    free(temp);  // delete old front
    return val;
}

// ==========================================================
// BFS (LEVEL ORDER TRAVERSAL)
// ==========================================================
void BFS(BST root) {
    if (!root) return;

    Queue q;
    initQueue(&q);       // create empty queue

    Enqueue(&q, root);   // start with root

    // Keep processing until queue becomes empty
    while (!isEmpty(&q)) {

        // Remove front node from queue
        BST cur = Dequeue(&q);

        // Visit the node
        printf("%c ", cur->data);

        // Enqueue children (left then right)
        if (cur->left) 
            Enqueue(&q, cur->left);

        if (cur->right) 
            Enqueue(&q, cur->right);
    }
}

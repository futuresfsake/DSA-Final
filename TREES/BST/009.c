#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ==========================================================
// BST NODE
// ==========================================================
typedef struct node {
    int data;
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
// BST operations
BST createNode(int data);
void insert(BST* root, int data);
void inorder(BST root);
bool searchNode(BST root, int data);
bool deleteNode(BST* root, int data);

// Queue operations for BFS
void initQueue(Queue* Q);
bool isEmpty(Queue* Q);
void Enqueue(Queue* Q, BST data);
BST Dequeue(Queue* Q);

// BFS traversal
void BFS(BST root);

// ==========================================================
// MAIN FUNCTION – TEST DRIVER
// ==========================================================
int main() {
    BST root = NULL;

    // Insert integers
    insert(&root, 50);
    insert(&root, 30);
    insert(&root, 70);
    insert(&root, 20);
    insert(&root, 40);
    insert(&root, 60);
    insert(&root, 80);

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    printf("BFS Traversal: ");
    BFS(root);
    printf("\n");

    printf("Searching 40: %s\n", searchNode(root, 40) ? "Found" : "Not Found");
    printf("Searching 90: %s\n", searchNode(root, 90) ? "Found" : "Not Found");

    printf("\nDeleting 30...\n");
    deleteNode(&root, 30);

    printf("Inorder after deletion: ");
    inorder(root);
    printf("\n");

    return 0;
}


BST createNode(int data) {
    BST new = malloc(sizeof(Node));
    if (new) {
        new->data = data;
        new->right = NULL;
        new->left = NULL;
    }
    return new;

}
void insert(BST* root, int data) {
    BST* trav = root;
    for(;*trav != NULL && (*trav)->data != data;) {
        trav = (*trav)->data < data? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
    *trav = createNode(data);
    }
}


void inorder(BST root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);

}

bool searchNode(BST root, int data) {
    BST trav = root;

    for(;trav != NULL;) {
        if (trav->data == data) {
            return 1;
        }

        trav = (trav->data < data) ? trav->right : trav->left;
    }
    return 0;
}
bool deleteNode(BST* root, int data) {

    BST* trav = root;
    for(;(*trav) != NULL && (*trav)->data != data;) {
        trav = ((*trav)->data < data) ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) return false;

    BST temp = *trav;

    if ((*trav)->left == NULL && (*trav)->right == NULL) {
        free(temp);
        *trav = NULL;
    }

    else if ((*trav)->left == NULL) {
        *trav = (*trav)->right;
        free(temp);
    }
    
    else if ((*trav)->right == NULL) {
        *trav = (*trav)->left;
        free(temp);

    }

    else {
        BST* pred = &(*trav)->left;
        while ((*pred)->right) {
            pred = &(*pred)->right;
        }

        (*trav)->data = (*pred)->data;
        deleteNode(pred, (*pred)->data);
    }
}


// Queue operations for BFS
void initQueue(Queue* Q) {
    Q->front = NULL;
    Q->rear = NULL;
}
bool isEmpty(Queue* Q) {
    return (Q->front == NULL && Q->rear == NULL);
}
void Enqueue(Queue* Q, BST data) {
    Qnode* new = malloc(sizeof(Qnode));
    if (new) {
        new->data = data;
        new->next = NULL; 
    }


    if (Q->front == NULL && Q->rear == NULL) {
        Q->front = new;
        Q->rear = new;
    } else {
        Q->rear->next = new;
        Q->rear = new;
    }

}
BST Dequeue(Queue* Q) {

    if (Q->front == NULL && Q->rear == NULL) return NULL;

    BST data = Q->front->data;
    Qnode* temp = Q->front;

    Q->front = temp->next;


    
    if (Q->front == NULL) {
        Q->rear = NULL;
    }
    free(temp);

    return data;
    
}


void BFS(BST root) {

    if (!root) return;
     Queue Q;
    initQueue(&Q);


    Enqueue(&Q, root);


    while (!isEmpty(&Q)) {

        BST current = Dequeue(&Q);

       printf("%d->", current->data);

        if (current->left) {
            Enqueue(&Q, current->left);
        }

        if (current->right) {
            Enqueue(&Q, current->right);
        }




        

    }
    

}

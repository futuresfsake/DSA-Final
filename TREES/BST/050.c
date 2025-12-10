#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100
#define QUEUE_SIZE 100

/*
    =========================================================
        GALACTIC SPACEPORT – ALIEN SHIP DOCKING SYSTEM
    ---------------------------------------------------------
    The Galactic Spaceport manages incoming and docked alien ships.
    Each ship has a unique ID and a name. The Spaceport uses a 
    Binary Search Tree (BST) to efficiently organize ships for 
    docking, maintenance, and departure scheduling.

    TASK:
        - Implement all BST operations ITERATIVELY.
        - Use dynamic memory for ship names.
        - Traversals: inorder, preorder, postorder, BFS.
        - Support search, insert, delete operations.
    =========================================================
*/

typedef struct Ship {
    int shipID;
    char* name;
    struct Ship* left;
    struct Ship* right;
} Ship;

typedef struct {
    Ship* arr[STACK_SIZE];
    int top;
} Stack;

typedef struct {
    Ship* arr[QUEUE_SIZE];
    int front, rear;
} Queue;

// ================== STACK FUNCTIONS ==================
void push(Stack* s, Ship* node);
Ship* pop(Stack* s);
int isEmptyStack(Stack* s);

// ================== QUEUE FUNCTIONS ==================
void enqueue(Queue* q, Ship* node);
Ship* dequeue(Queue* q);
int isEmptyQueue(Queue* q);

// ================== BST OPERATIONS ==================
Ship* createShip(int shipID, const char* name);
Ship* insertShip(Ship* root, int shipID, const char* name); // iterative
Ship* searchShip(Ship* root, const char* name);              // iterative
Ship* deleteShip(Ship* root, const char* name);              // iterative

void inorder(Ship* root);    // iterative
void preorder(Ship* root);   // iterative
void postorder(Ship* root);  // iterative
void bfs(Ship* root);        // iterative

// ================== MAIN ==================
int main() {
    Ship* dock = NULL;

    dock = insertShip(dock, 301, "Zyphor Cruiser");
    dock = insertShip(dock, 102, "Orion Scout");
    dock = insertShip(dock, 450, "Nebula Freighter");
    dock = insertShip(dock, 220, "Cosmic Explorer");
    dock = insertShip(dock, 75, "Quantum Shuttle");

    printf("=== Inorder Traversal ===\n");
    inorder(dock);

    printf("\n=== Preorder Traversal ===\n");
    preorder(dock);

    printf("\n=== Postorder Traversal ===\n");
    postorder(dock);

    printf("\n=== BFS Traversal ===\n");
    bfs(dock);

    printf("\nSearching 'Nebula Freighter':\n");
    Ship* found = searchShip(dock, "Nebula Freighter");
    if (found) printf("Found: %d | %s\n", found->shipID, found->name);
    else printf("Not found\n");

    printf("\nDeleting 'Orion Scout'\n");
    dock = deleteShip(dock, "Orion Scout");
    inorder(dock);
    printf("\n=== BFS Traversal ===\n");

    bfs(dock);

    // Free dynamically allocated names (your deleteShip should also free names)
    return 0;
}

// ================== STACK FUNCTIONS ==================
void push(Stack* s, Ship* node) {
    s->arr[++s->top] = node;

}
Ship* pop(Stack* s) { 
    return s->arr[s->top--];
}
int isEmptyStack(Stack* s) { 
    if (s->top == -1) {
        return 1;
    } else {
        -1;
    }
 }

// ================== QUEUE FUNCTIONS ==================
void enqueue(Queue* q, Ship* node) {
    q->arr[q->rear++] = node;
}
Ship* dequeue(Queue* q) {
    return q->arr[q->front++];
}
int isEmptyQueue(Queue* q) { 
    return q->front == q->rear;
 }

// ================== BST OPERATIONS ==================
Ship* createShip(int shipID, const char* name) { 
    
    Ship* new = malloc(sizeof(Ship));
    new->name = malloc(strlen(name)+1);
    strcpy(new->name, name);
    new->shipID = shipID;
    new->left = new->right = NULL;

    return new;
 }
Ship* insertShip(Ship* root, int shipID, const char* name) {
    
    Ship** trav = &root;
    for(; *trav != NULL && strcmp((*trav)->name, name) != 0; ) {
        trav = (strcmp((*trav)->name, name) < 0) ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {

        Ship* new =createShip (shipID, name);
        *trav = new;
    }

    return root;
}

Ship* searchShip(Ship* root, const char* name) { 
    
    Ship* trav = root;

    for(; trav != NULL;) {
        if (strcmp(trav->name, name) == 0) {
            return trav;
        }
        trav = (strcmp(trav->name, name) < 0) ? trav->right : trav->left;
    }

    return NULL;
 }
Ship* deleteShip(Ship* root, const char* name) { 
    
    Ship** trav = &root;
    for(; *trav != NULL && (strcmp((*trav)->name, name)!=0);) {
        trav = (strcmp((*trav)->name, name) < 0) ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
        printf("\"%s\" is not existing...\n", name);
        return root;
    }



    Ship* temp = *trav;

    if ((*trav)->left == NULL && (*trav)->right == NULL) {
        free((temp)->name);
        free(temp);
        *trav = NULL;
        
    } else if ((*trav)->left == NULL) {
        *trav = (*trav)->right;
        free((temp)->name);
        free(temp);
    } else if ((*trav)->right == NULL) {
        *trav = (*trav)->left;
        free(temp->name);
        free(temp);
    } else {
        Ship** succ = &(*trav)->right;
        while ((*succ)->left) {
            succ = &(*succ)->left;
        }

        free((*trav)->name);
        (*trav)->name = malloc(strlen((*succ)->name)+1);
        strcpy((*trav)->name, (*succ)->name);
        (*trav)->shipID = (*succ)->shipID;

        Ship* target = *succ;
        *succ = target->right;
        free(target->name);
        free(target);

    }
    return root;
}

void inorder(Ship* root) {
    Stack s;
    s.top =-1;

    Ship* trav = root;
    while (trav || s.top != -1) {
        while (trav) {
            push(&s, trav);
            trav = trav->left;
        }

        trav = pop(&s);
        printf("ID: %d | Ship Name: %s \n", trav->shipID, trav->name);
        trav = trav->right;
    } 
}
void preorder(Ship* root) {
    Stack s;
    s.top = -1;

    push(&s, root);

    while (s.top != -1) {
        Ship* trav = pop(&s);
    printf("ID: %d | Ship Name: %s \n", trav->shipID, trav->name);
         if (trav->right) push(&s, trav->right);
        if (trav->left) push(&s, trav->left);


    }
}
void postorder(Ship* root) {

    Stack s1,s2;
    s1.top = -1;
    s2.top = -1;

    push(&s1, root);

    while (s1.top != -1) {
        Ship* trav = pop(&s1);
        push(&s2, trav);


        if (trav->left) push(&s1, trav->left);
        if (trav->right) push(&s1, trav->right);
        
    }

    while (s2.top != -1) {
        Ship* trav = pop(&s2);
            printf("ID: %d | Ship Name: %s \n", trav->shipID, trav->name);

        
    }
}
void bfs(Ship* root) {

   Queue q;
   q.rear = 0;
   q.front = 0;


   q.arr[q.rear++] = root;

   while (q.front < q.rear) {
    Ship* trav = q.arr[q.front++];
        printf("ID: %d | Ship Name: %s \n", trav->shipID, trav->name);

        if (trav->left) q.arr[q.rear++] = trav->left;
        if (trav->right) q.arr[q.rear++] = trav->right;
   }
}

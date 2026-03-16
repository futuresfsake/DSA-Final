#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 10
#define ROOT_NODE -1
#define INVALID_NODE -2

typedef int Node;

typedef struct ChildNode {
    Node childIndex;
    struct ChildNode *next;
} ChildNode;

typedef struct {
    Node rootIndex;
    ChildNode* children[MAX_NODES];
} Tree;


typedef struct {
    Node stack[100];
    int top;
} Stack;


void push(Stack* s, Node node) {
    s->stack[++s->top] = node;
}
Node pop(Stack* s) {
    return s->stack[s->top--];
}

// Function declarations
void initializeTree(Tree *T);
void makeRoot(Tree *T, Node r);
void addChild(Tree *T, Node parent_index, Node child_index);
int countDescendants(const Tree *T, Node n);
void printTree(const Tree *T);
void freeTree(Tree *T);

void display(const Tree* T) {
    int i;
    ChildNode* trav;


    for(i = 0; i < MAX_NODES; i++) {
    trav = T->children[i];

    printf("INDEX[%d]: -> ", i);

    if (trav == NULL) {
        printf("EMPTY\n");
    } else {
        while (trav) {
            printf("%d-> ", trav->childIndex);
            trav = trav->next;
        }
        printf("NULL\n");
    }
 
 
  

}
}

int main() {
    Tree myTree;
    initializeTree(&myTree);

   makeRoot(&myTree, 0);

// Level 1 children
addChild(&myTree, 0, 1);
addChild(&myTree, 0, 2);
addChild(&myTree, 0, 3);

// Level 2 children
addChild(&myTree, 1, 4);
addChild(&myTree, 1, 5);
addChild(&myTree, 2, 6);

// Level 3 children
addChild(&myTree, 5, 7);


    int total = countDescendants(&myTree, 0);
    printf("Total descendants of Node 0: %d\n", total);

    printTree(&myTree);
     display(&myTree);
    freeTree(&myTree);
    return 0;
}

// Function declarations
void initializeTree(Tree *T) {
    T->rootIndex = INVALID_NODE;

    for(int i = 0; i < MAX_NODES; i++) {
        T->children[i] = NULL;
    }
}



void makeRoot(Tree *T, Node r) {
    T->rootIndex = r;
}
void addChild(Tree *T, Node parent_index, Node child_index) {

    ChildNode* trav = T->children[parent_index];
    bool found = false;

    while (trav != NULL) {
        if (trav->childIndex == child_index) {
            found = true;
        }
        trav = trav->next;
    }


    if (!found) {
        ChildNode* new = malloc(sizeof(ChildNode));
        new->childIndex = child_index;
        new->next = T->children[parent_index];
        T->children[parent_index] = new;
    }
}


int countDescendants(const Tree *T, Node n) {

    int count = 0;

    ChildNode* trav = T->children[n];
    while (trav) {
        count++;

        count+= countDescendants(T, trav->childIndex);
        trav = trav->next;
    }
    return count;
}


void printTree(const Tree *T) {
    Stack s;
    s.top = -1;

    // 1) Start from the root node
    if (T->rootIndex == INVALID_NODE) return;
    push(&s, T->rootIndex);

    // 2) DFS using stack (Last-In-First-Out)
    while (s.top != -1) {
        Node current = pop(&s);
        printf("%d ",current);

        // 3) Push current node's children
        ChildNode* trav = T->children[current];
        while (trav != NULL) {
            push(&s, trav->childIndex);
            trav = trav->next;
        }
    }

    printf("\n");
}



void preorder (const Tree* T, Node n) {
    if (n == -1) return;

    printf("%d ", n);
    ChildNode* trav = T->children[n];

    while (trav) {
        preorder(T, trav->childIndex);
        trav = trav->next;
    }
}


void postorder (const Tree* T, Node n) {
    if (n == -1) return;

    printf("%d ", n);
    ChildNode* trav = T->children[n];

    while (trav) {
        postrder(T, trav->childIndex);
        trav = trav->next;
    }
        printf("%d ", n);

}


void bfs (const Tree* T) {
    if (T->rootIndex == -1) return;
    
    Node* Queue[100];
    int front = 0;
    int rear = 0;

    Queue[rear++] = T->rootIndex;

    while (front < rear) {
        Node trav = Queue[front++];
        printf("%D ", trav);

        ChildNode* curr = T->children[trav];
        while (curr) {
            Queue[rear++] = curr->childIndex;
            curr = curr->next;
        }
    }
}


 void freeTree(Tree *T) {
    
    for(int i = 0; i < MAX_NODES; i++) {
        ChildNode* curr = T->children[i];
        while (curr) {
            ChildNode* temp = curr;
            curr = curr->next;
            free(temp);
        }

        T->children[i] = NULL;
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 10
#define ROOT_NODE -1
#define INVALID_NODE -2

typedef int Node;

// Linked list node for children
typedef struct ChildNode {
    Node childIndex;
    struct ChildNode *next;
} ChildNode;

// Tree structure
typedef struct {
    Node rootIndex;
    ChildNode* children[MAX_NODES];
} Tree;


// =========================
// INITIALIZATION
// =========================
void initializeTree(Tree *T) {
    for (int i = 0; i < MAX_NODES; i++) {
        T->children[i] = NULL;
    }
    T->rootIndex = INVALID_NODE;
}


// =========================
// SET ROOT
// =========================
void makeRoot(Tree *T, Node r) {
    if (T->rootIndex != INVALID_NODE) {
        printf("Root is already set.\n");
        return;
    }
    T->rootIndex = r;
    printf("Successfully initialized root!\n");
}


// =========================
// ADD CHILD
// =========================
void addChild(Tree *T, Node parent_index, Node child_index) {
    ChildNode *newChild = malloc(sizeof(ChildNode));
    if (!newChild) {
        printf("Memory allocation failed!\n");
        return;
    }

    newChild->childIndex = child_index;
    newChild->next = NULL;

    ChildNode *trav = T->children[parent_index];

    // First child
    if (trav == NULL) {
        T->children[parent_index] = newChild;
    } 
    else {
        // Go to end of linked list
        while (trav->next != NULL) {
            trav = trav->next;
        }
        trav->next = newChild;
    }

    printf("Child %d added to parent %d\n", child_index, parent_index);
}


// =========================
// FIND PARENT OF A NODE
// =========================
Node parent(Node n, const Tree *T) {
    if (n == T->rootIndex)
        return ROOT_NODE;

    // Search all parent indices
    for (int i = 0; i < MAX_NODES; i++) {
        ChildNode *trav = T->children[i];
        while (trav != NULL) {
            if (trav->childIndex == n) {
                return i;
            }
            trav = trav->next;
        }
    }

    return INVALID_NODE;
}


// =========================
// LEFTMOST NODE
// =========================
Node left(const Tree *T) {
    if (T->rootIndex == INVALID_NODE)
        return INVALID_NODE;

    // Smallest valid index is always the root
    return T->rootIndex;
}


// =========================
// RIGHTMOST NODE
// =========================
Node right(const Tree *T) {
    int rightmost = T->rootIndex;

    for (int i = MAX_NODES - 1; i >= 0; i--) {
        ChildNode *trav = T->children[i];

        // If a parent index exists and is larger
        if (trav != NULL && i > rightmost)
            rightmost = i;

        // Check its children
        while (trav != NULL) {
            if (trav->childIndex > rightmost)
                rightmost = trav->childIndex;
            trav = trav->next;
        }
    }

    return rightmost;
}


// =========================
// PRINT TREE
// =========================
void printTree(const Tree *T) {
    printf("\n--- Tree Children List Representation ---\n");
    printf("Root Index: %d\n", T->rootIndex);
    printf("Parent | Children\n");
    printf("--------|-----------------\n");

    for (int i = 0; i < MAX_NODES; i++) {
        printf("%5d | ", i);
        ChildNode *trav = T->children[i];

        if (trav == NULL) {
            printf("(None)\n");
        } else {
            while (trav != NULL) {
                printf("%d -> ", trav->childIndex);
                trav = trav->next;
            }
            printf("NULL\n");
        }
    }
    printf("-----------------------------------------\n");
}


// =========================
// FREE MEMORY
// =========================
void freeTree(Tree *T) {
    for (int i = 0; i < MAX_NODES; i++) {
        ChildNode *current = T->children[i];
        ChildNode *next;

        while (current != NULL) {
            next = current->next;
            free(current);
            current = next;
        }

        T->children[i] = NULL;
    }

    printf("\nTree memory cleaned up.\n");
}


// =========================
// MAIN (Demo)
// =========================
int main() {
    Tree myTree;
    initializeTree(&myTree);

    // Build sample tree
    makeRoot(&myTree, 0);

    addChild(&myTree, 0, 1);
    addChild(&myTree, 0, 2);

    addChild(&myTree, 1, 3);
    addChild(&myTree, 1, 4);

    addChild(&myTree, 2, 5);

    addChild(&myTree, 5, 8);
    addChild(&myTree, 5, 9);

    printTree(&myTree);

    printf("\n--- Testing ADT Operations ---\n");

    // parent()
    printf("Parent of 5: %d\n", parent(5, &myTree));  // Expected: 2
    printf("Parent of 0: %d (root)\n", parent(0, &myTree)); 
    printf("Parent of 7: %d (invalid)\n", parent(7, &myTree));

    // left()
    printf("Leftmost node: %d\n", left(&myTree));   // Expected: 0

    // right()
    printf("Rightmost node: %d\n", right(&myTree)); // Expected: 9

    freeTree(&myTree);

    return 0;
}

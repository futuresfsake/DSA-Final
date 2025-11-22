#include <stdio.h>
#include <stdlib.h>

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

void initializeTree(Tree *T);
void makeRoot(Tree *T, Node r);
void addChild(Tree *T, Node parent, Node child);
Node parent(Node n, Tree *T);
Node left(Tree *T);
Node right(Tree *T);
void printTree(Tree *T);
void freeTree(Tree *T);


int main() {
    Tree myTree;
    initializeTree(&myTree);

    makeRoot(&myTree, 0);
    addChild(&myTree, 0, 1);
    addChild(&myTree, 0, 2);
    addChild(&myTree, 1, 3);
    addChild(&myTree, 1, 4);
    addChild(&myTree, 2, 5);
    addChild(&myTree, 5, 8);
    addChild(&myTree, 5, 9);

    printTree(&myTree);

    printf("Parent of 5: %d\n", parent(5, &myTree)); // Expected: 2
    printf("Parent of 0: %d\n", parent(0, &myTree)); // Expected: -1 (ROOT_NODE)
    printf("Leftmost node: %d\n", left(&myTree));    // Expected: 0
    printf("Rightmost node: %d\n", right(&myTree));  // Expected: 9

    freeTree(&myTree);
    return 0;
}

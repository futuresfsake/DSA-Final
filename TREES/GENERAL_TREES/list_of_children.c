/*
    GENERAL TREE — LIST OF CHILDREN REPRESENTATION
    ------------------------------------------------
    Each node index (0..N-1) has a pointer (index) to the
    start of a linked list containing all its children.

    Structures:
      - child[] : array of child nodes (each node holds index of child and next sibling)
      - head[]  : array where head[i] = index of the first child of node i, or -1 if none

    Example (based on your diagram):
        Node 5 has children 0 → 6 → 2
        Node 0 has children 4 → 7
        Node 2 has child 8
        Node 6 has children 3 → 1
*/

#include <stdio.h>

#define MAXN  10
#define MAXC  20
#define NONE  -1   // marks empty link

// Structure for each child link
struct ChildNode {
    int child;   // index of child node
    int next;    // next child in list (linked list index)
};

// Global arrays
int head[MAXN];               // head[i] = index of first child node
struct ChildNode child[MAXC]; // store all child links
int avail = 0;                // next free position in child[] array

// ──────────────────────────────────────────────────────────────
// FUNCTIONS
// ──────────────────────────────────────────────────────────────

// initialize all heads to NONE
void init_tree(int n) {
    for (int i = 0; i < n; i++)
        head[i] = NONE;
    avail = 0;
}

// add a child under parent
void addChild(int parent, int c) {
    // create new link
    child[avail].child = c;
    child[avail].next = NONE;

    // insert at end of parent's child list
    if (head[parent] == NONE) {
        head[parent] = avail;             // first child
    } else {
        int temp = head[parent];
        while (child[temp].next != NONE)  // go to last child
            temp = child[temp].next;
        child[temp].next = avail;
    }
    avail++;
}

// display the children of a node
void showChildren(int parent) {
    printf("Children of node %d: ", parent);
    if (head[parent] == NONE) {
        printf("none\n");
        return;
    }
    int p = head[parent];
    while (p != NONE) {
        printf("%d ", child[p].child);
        p = child[p].next;
    }
    printf("\n");
}

// display entire tree representation
void displayListOfChildren(int n) {
    printf("\nLIST OF CHILDREN REPRESENTATION:\n");
    for (int i = 0; i < n; i++) {
        printf("%d | ", i);
        int p = head[i];
        while (p != NONE) {
            printf("%d -> ", child[p].child);
            p = child[p].next;
        }
        printf("NULL\n");
    }
}

// breadth-first traversal example using list of children
void breadthFirst(int root, int n) {
    printf("\nBreadth-First Traversal: ");
    int queue[MAXN], front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        int node = queue[front++];
        printf("%d ", node);

        // enqueue all its children
        int p = head[node];
        while (p != NONE) {
            queue[rear++] = child[p].child;
            p = child[p].next;
        }
    }
    printf("\n");
}

// ──────────────────────────────────────────────────────────────
// MAIN DEMO
// ──────────────────────────────────────────────────────────────
int main() {
    int N = 9; // total nodes (0..8)
    init_tree(N);

    /*  Build same structure as your diagram
            0 → 4 → 7
            2 → 8
            5 → 0 → 6 → 2
            6 → 3 → 1
    */
    addChild(0, 4);
    addChild(0, 7);
    addChild(2, 8);
    addChild(5, 0);
    addChild(5, 6);
    addChild(5, 2);
    addChild(6, 3);
    addChild(6, 1);

    // Display all lists
    displayListOfChildren(N);

    // Show specific children
    showChildren(5);
    showChildren(6);
    showChildren(0);

    // Do BFS starting from root 5
    breadthFirst(5, N);

    return 0;
}

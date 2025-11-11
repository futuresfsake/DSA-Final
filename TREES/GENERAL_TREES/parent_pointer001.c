#include <stdio.h>

#define MAX_NODES 100
#define NIL -1

typedef char ElemType;   // change to int/struct/etc if needed

typedef struct {
    ElemType data;
    int parent;   // index of parent in array; -1 if root
    int used;     // 1 = slot occupied, 0 = free
} GTNode;

typedef struct {
    GTNode nodes[MAX_NODES];
    int root;     // index of root; -1 if empty
    int count;    // number of used nodes
} GenTree;

/* ================== UTILITY / CORE HELPERS ================== */

// Initialize tree: mark all slots free
void initTree(GenTree *T) {
    int i;
    for (i = 0; i < MAX_NODES; i++) {
        T->nodes[i].used = 0;
        T->nodes[i].parent = NIL;
    }
    T->root = NIL;
    T->count = 0;
}

// Is tree empty?
int isEmpty(GenTree T) {
    return (T.count == 0);
}

// Find first free index in array; -1 if full
int getFreeIndex(GenTree *T) {
    int i;
    for (i = 0; i < MAX_NODES; i++) {
        if (!T->nodes[i].used) {
            return i;
        }
    }
    return -1; // no space
}

// Create root (only if empty)
int addRoot(GenTree *T, ElemType x) {
    if (!isEmpty(*T)) {
        printf("addRoot error: tree already has a root.\n");
        return NIL;
    }

    int idx = getFreeIndex(T);
    if (idx == -1) {
        printf("addRoot error: no space.\n");
        return NIL;
    }

    T->nodes[idx].data = x;
    T->nodes[idx].parent = NIL;
    T->nodes[idx].used = 1;
    T->root = idx;
    T->count++;

    return idx;
}

// Linear search a node by value (simple for demo)
int findNodeIndex(GenTree T, ElemType x) {
    int i;
    for (i = 0; i < MAX_NODES; i++) {
        if (T.nodes[i].used && T.nodes[i].data == x) {
            return i;
        }
    }
    return NIL;
}

/* ================== BASIC ADT OPERATIONS ================== */

// Get root index
int getRoot(GenTree T) {
    return T.root;
}

// Get parent index of given node index
int getParentIndex(GenTree T, int nodeIdx) {
    if (nodeIdx < 0 || nodeIdx >= MAX_NODES || !T.nodes[nodeIdx].used) {
        return NIL;
    }
    return T.nodes[nodeIdx].parent;
}

// Return index of leftmost (first) child of parentIdx
int getLeftmostChildIndex(GenTree T, int parentIdx) {
    if (parentIdx == NIL) return NIL;

    int i;
    for (i = 0; i < MAX_NODES; i++) {
        if (T.nodes[i].used && T.nodes[i].parent == parentIdx) {
            return i; // first found = leftmost (by storage order)
        }
    }
    return NIL; // no children
}

// Return index of "right sibling" of nodeIdx (next child of same parent)
int getRightSiblingIndex(GenTree T, int nodeIdx) {
    if (nodeIdx == NIL || !T.nodes[nodeIdx].used) return NIL;

    int parentIdx = T.nodes[nodeIdx].parent;
    if (parentIdx == NIL) return NIL; // root has no siblings (in this sense)

    int i;
    // Find a used node with same parent and index > nodeIdx
    for (i = nodeIdx + 1; i < MAX_NODES; i++) {
        if (T.nodes[i].used && T.nodes[i].parent == parentIdx) {
            return i;
        }
    }
    return NIL;
}

// Add child given parent index
int addChildByIndex(GenTree *T, int parentIdx, ElemType x) {
    if (parentIdx < 0 || parentIdx >= MAX_NODES || !T->nodes[parentIdx].used) {
        printf("addChild error: invalid parent index.\n");
        return NIL;
    }

    int idx = getFreeIndex(T);
    if (idx == -1) {
        printf("addChild error: no space.\n");
        return NIL;
    }

    T->nodes[idx].data = x;
    T->nodes[idx].parent = parentIdx;
    T->nodes[idx].used = 1;
    T->count++;

    return idx;
}

// Add child by searching parent value (convenience)
int addChildByValue(GenTree *T, ElemType parentVal, ElemType childVal) {
    int pIdx = findNodeIndex(*T, parentVal);
    if (pIdx == NIL) {
        printf("addChildByValue error: parent value not found.\n");
        return NIL;
    }
    return addChildByIndex(T, pIdx, childVal);
}

// Check if a node is a leaf (no children)
int isLeaf(GenTree T, int nodeIdx) {
    if (nodeIdx < 0 || nodeIdx >= MAX_NODES || !T.nodes[nodeIdx].used) {
        return 0;
    }

    int i;
    for (i = 0; i < MAX_NODES; i++) {
        if (T.nodes[i].used && T.nodes[i].parent == nodeIdx) {
            return 0; // has at least one child
        }
    }
    return 1; // no children
}

/* ============ DELETE LEAF (PARENT POINTER VERSION) ============ */
// Only deletes if leaf; marks slot free. No compaction.

void deleteLeaf(GenTree *T, int nodeIdx) {
    if (nodeIdx < 0 || nodeIdx >= MAX_NODES || !T->nodes[nodeIdx].used) {
        printf("deleteLeaf error: invalid index.\n");
        return;
    }

    if (!isLeaf(*T, nodeIdx)) {
        printf("deleteLeaf error: node is not a leaf.\n");
        return;
    }

    // If it's the root and only node
    if (nodeIdx == T->root) {
        T->nodes[nodeIdx].used = 0;
        T->nodes[nodeIdx].parent = NIL;
        T->count = 0;
        T->root = NIL;
        return;
    }

    // Otherwise just free it
    T->nodes[nodeIdx].used = 0;
    T->nodes[nodeIdx].parent = NIL;
    T->count--;
}

/* ================== TRAVERSALS ================== */
/* Note: General tree traversals here are defined using:
   - first child = getLeftmostChildIndex
   - next sibling = getRightSiblingIndex
*/

// Preorder: visit node, then its subtree children left-to-right
void preorderHelper(GenTree T, int nodeIdx) {
    if (nodeIdx == NIL || !T.nodes[nodeIdx].used) return;

    printf("%c ", T.nodes[nodeIdx].data);

    int child = getLeftmostChildIndex(T, nodeIdx);
    while (child != NIL) {
        preorderHelper(T, child);
        child = getRightSiblingIndex(T, child);
    }
}

void preorder(GenTree T) {
    if (T.root != NIL)
        preorderHelper(T, T.root);
    printf("\n");
}

// Postorder: visit children first, then node
void postorderHelper(GenTree T, int nodeIdx) {
    if (nodeIdx == NIL || !T.nodes[nodeIdx].used) return;

    int child = getLeftmostChildIndex(T, nodeIdx);
    while (child != NIL) {
        postorderHelper(T, child);
        child = getRightSiblingIndex(T, child);
    }

    printf("%c ", T.nodes[nodeIdx].data);
}

void postorder(GenTree T) {
    if (T.root != NIL)
        postorderHelper(T, T.root);
    printf("\n");
}

// Level-order (BFS) using simple array queue of indices
void levelOrder(GenTree T) {
    if (T.root == NIL) {
        printf("Tree is empty.\n");
        return;
    }

    int queue[MAX_NODES];
    int front = 0, rear = 0;

    queue[rear++] = T.root;

    while (front < rear) {
        int curr = queue[front++];

        if (!T.nodes[curr].used) continue;

        printf("%c ", T.nodes[curr].data);

        int child = getLeftmostChildIndex(T, curr);
        while (child != NIL) {
            queue[rear++] = child;
            child = getRightSiblingIndex(T, child);
        }
    }
    printf("\n");
}

/* ================== DEBUG / VISUAL HELPERS ================== */

void displayAsParentArray(GenTree T) {
    int i;
    printf("Idx | Data | ParentIdx | Used\n");
    printf("--------------------------------\n");
    for (i = 0; i < MAX_NODES; i++) {
        if (T.nodes[i].used) {
            printf("%3d |  %c   |    %3d    |  %d\n",
                   i, T.nodes[i].data, T.nodes[i].parent, T.nodes[i].used);
        }
    }
    printf("Root index: %d\n", T.root);
    printf("Count: %d\n", T.count);
}

/* ================== SAMPLE MAIN (TEST) ================== */

int main() {
    GenTree T;
    initTree(&T);

    int r = addRoot(&T, 'A');
    int b = addChildByIndex(&T, r, 'B');
    int c = addChildByIndex(&T, r, 'C');
    int d = addChildByIndex(&T, r, 'D');
    addChildByIndex(&T, b, 'E');
    addChildByIndex(&T, b, 'F');
    addChildByIndex(&T, c, 'G');

    printf("Parent-array representation:\n");
    displayAsParentArray(T);

    printf("\nPreorder: ");
    preorder(T);

    printf("Postorder: ");
    postorder(T);

    printf("Level-order: ");
    levelOrder(T);

    // Example delete
    if (isLeaf(T, d)) {
        printf("\nDeleting leaf node D at index %d...\n", d);
        deleteLeaf(&T, d);
    }

    printf("\nAfter deletion:\n");
    displayAsParentArray(T);

    return 0;
}

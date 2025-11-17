/* =======================
 * Parent-Pointer General Tree (static array)
 * ADT operations + demo
 * ======================= */

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES   100
#define ROOT        -1     /* means: this node is the root (no parent) */
#define NONEXISTENT -2     /* means: there is no node at this index */

/* ----------------------- Data Structure ----------------------- */

typedef struct {
    int parent[MAX_NODES];  /* parent[i] = index of parent of node i */
    int count;              /* number of existing nodes */
} ParentPointerTree;

/* ----------------------- Core Helpers ------------------------- */

void initTree(ParentPointerTree *T) {
    for (int i = 0; i < MAX_NODES; ++i) T->parent[i] = NONEXISTENT;
    T->count = 0;
}

int existsNode(const ParentPointerTree *T, int node) {
    return (node >= 0 && node < MAX_NODES && T->parent[node] != NONEXISTENT);
}

int isRoot(const ParentPointerTree *T, int node) {
    return (existsNode(T, node) && T->parent[node] == ROOT);
}

/* Find the unique root (first cell whose value == ROOT), or NONEXISTENT */
int findRoot(const ParentPointerTree *T) {
    for (int i = 0; i < MAX_NODES; ++i)
        if (T->parent[i] == ROOT) return i;
    return NONEXISTENT;
}

/* ----------------------- ADT Operations ----------------------- */

/* Create/declare a root at `node` (fails if a root already exists or node taken) */
int setRoot(ParentPointerTree *T, int node) {
    if (node < 0 || node >= MAX_NODES) return 0;
    if (existsNode(T, node)) return 0;
    if (findRoot(T) != NONEXISTENT) return 0; /* only one root allowed */

    T->parent[node] = ROOT;
    T->count++;
    return 1;
}

/* Insert a new node with given parent index.
   parent == ROOT means: create a new root (only if none exists). */
int insertNode(ParentPointerTree *T, int node, int parent) {
    if (node < 0 || node >= MAX_NODES) return 0;

    if (T->parent[node] != NONEXISTENT) {
        /* A node already exists at this index — prevent duplicates */
        return 0;
    }

    if (parent == ROOT) {
        /* behave like setRoot */
        if (findRoot(T) != NONEXISTENT) return 0;
        T->parent[node] = ROOT;
        T->count++;
        return 1;
    }

    /* parent must exist (unless it’s ROOT case handled above) */
    if (!existsNode(T, parent)) return 0;

    T->parent[node] = parent;
    T->count++;
    return 1;
}

/* Return parent index of node, or NONEXISTENT if node invalid/not present */
int getParent(const ParentPointerTree *T, int node) {
    if (node < 0 || node >= MAX_NODES) return NONEXISTENT;
    return T->parent[node];
}

/* Collect all children of `parentNode` into `out[]`.
   Returns the number of children placed in out[]. */
int getChildren(const ParentPointerTree *T, int parentNode, int out[], int outCap) {
    int k = 0;
    for (int i = 0; i < MAX_NODES; ++i) {
        if (T->parent[i] == parentNode) {
            if (k < outCap) out[k] = i;
            k++;
        }
    }
    return (k > outCap ? outCap : k);  /* we fill at most outCap items */
}

/* Depth (root has depth 0). Returns -1 if node invalid/nonexistent. */
int depthOf(const ParentPointerTree *T, int node) {
    if (!existsNode(T, node)) return -1;
    int d = 0, cur = node;
    while (T->parent[cur] != ROOT) {
        cur = T->parent[cur];
        if (!existsNode(T, cur)) return -1; /* inconsistent tree */
        d++;
    }
    return d;
}

/* Is `ancestor` an ancestor of `node`? (True/False: 1/0) */
int isAncestor(const ParentPointerTree *T, int ancestor, int node) {
    if (!existsNode(T, ancestor) || !existsNode(T, node)) return 0;
    int cur = node;
    while (cur != ROOT && existsNode(T, cur)) {
        cur = T->parent[cur];
        if (cur == ancestor) return 1;
    }
    return 0;
}

/* Delete `node` and its entire subtree (recursively). */
void deleteSubtree(ParentPointerTree *T, int node) {
    if (!existsNode(T, node)) return;

    /* delete children first */
    for (int i = 0; i < MAX_NODES; ++i) {
        if (T->parent[i] == node) deleteSubtree(T, i);
    }

    /* then delete this node */
    T->parent[node] = NONEXISTENT;
    T->count--;
}

/* ----------------------- Display / Debug ---------------------- */

void printArrayView(const ParentPointerTree *T) {
    printf("\nIndex : ");
    for (int i = 0; i < MAX_NODES; ++i) {
        if (existsNode(T, i) || T->parent[i] == ROOT) {
            printf("%2d ", i);
        }
    }
    printf("\nParent: ");
    for (int i = 0; i < MAX_NODES; ++i) {
        if (existsNode(T, i) || T->parent[i] == ROOT) {
            printf("%2d ", T->parent[i]);
        }
    }
    printf("\n(count=%d)\n", T->count);
}

void printEdges(const ParentPointerTree *T) {
    printf("\nEdges (parent -> child):\n");
    int root = findRoot(T);
    if (root != NONEXISTENT) printf("[ROOT] %d\n", root);

    for (int i = 0; i < MAX_NODES; ++i) {
        if (existsNode(T, i) && T->parent[i] != ROOT) {
            printf("%d -> %d\n", T->parent[i], i);
        }
    }
}

/* Print the path from node up to root */
void printPathToRoot(const ParentPointerTree *T, int node) {
    if (!existsNode(T, node)) {
        printf("Node %d does not exist.\n", node);
        return;
    }
    printf("Path to root from %d: ", node);
    int cur = node;
    while (existsNode(T, cur) && T->parent[cur] != ROOT) {
        printf("%d -> ", cur);
        cur = T->parent[cur];
    }
    if (existsNode(T, cur)) printf("%d -> ", cur);
    int r = findRoot(T);
    if (r != NONEXISTENT) printf("%d", r);
    printf("\n");
}

/* --------------------------- Demo ----------------------------- */

int main(void) {
    ParentPointerTree T;
    initTree(&T);

    /* Recreate your example:
       Index:  0  1  2  3  4  5  6  7  8  9
       Value:  5  6  5  6  1 -1  5  1  2 -2
       Meaning: node 5 is root; node 9 is NONEXISTENT.
    */
    setRoot(&T, 5);                   /* node 5 is root */
    insertNode(&T, 0, 5);
    insertNode(&T, 1, 6);             /* 6 must exist first, so add 6 next */
    insertNode(&T, 2, 5);
    insertNode(&T, 3, 6);
    insertNode(&T, 4, 1);
    insertNode(&T, 6, 5);
    insertNode(&T, 7, 1);
    insertNode(&T, 8, 2);

    printArrayView(&T);
    printEdges(&T);

    /* Query parent */
    int p = getParent(&T, 2);
    printf("\nParent of 2: %d\n", p);  /* expected: 5 */

    /* List children of a node */
    int kids[16];
    int k = getChildren(&T, 5, kids, 16);
    printf("Children of 5 (%d): ", k);
    for (int i = 0; i < k; ++i) printf("%d ", kids[i]);
    printf("\n");

    /* Depth / ancestor checks */
    printf("Depth of node 8: %d\n", depthOf(&T, 8));      /* 2 -> 5 -> root */
    printf("Is 5 ancestor of 8? %s\n", isAncestor(&T, 5, 8) ? "yes" : "no");

    /* Path to root */
    printPathToRoot(&T, 8);

    /* Delete a subtree (e.g., delete node 2 and its children) */
    printf("\nDeleting subtree rooted at 2...\n");
    deleteSubtree(&T, 2);
    printArrayView(&T);
    printEdges(&T);

    return 0;
}

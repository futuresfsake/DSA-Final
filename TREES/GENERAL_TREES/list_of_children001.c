/* ================================
 * General Tree (List of Children)
 * - Each node is an index [0..MAX_NODES-1]
 * - For each index i, we keep a linked list of its children’s indices.
 * ADT ops: init, setRoot, insertChild, getChildren, findParent,
 *          deleteSubtree, removeChildEdge, display
 * ================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES   100
#define ROOT        -1
#define NONEXISTENT -2

/* ---------- child list node ---------- */
typedef struct Child {
    int idx;               /* child's index */
    struct Child *next;
} Child;

/* ---------- tree structure ---------- */
typedef struct {
    Child *head[MAX_NODES];  /* head[i] = linked list of children of node i */
    int exists[MAX_NODES];   /* 1 if node i exists, 0 otherwise */
    int root;                /* root index or NONEXISTENT */
    int count;               /* number of existing nodes */
} ChildListTree;

/* ================== helpers ================== */

static Child *makeChild(int idx) {
    Child *c = (Child*)malloc(sizeof(Child));
    c->idx = idx;
    c->next = NULL;
    return c;
}

void initTree(ChildListTree *T) {
    for (int i = 0; i < MAX_NODES; ++i) {
        T->head[i] = NULL;
        T->exists[i] = 0;
    }
    T->root = NONEXISTENT;
    T->count = 0;
}

int existsNode(const ChildListTree *T, int node) {
    return node >= 0 && node < MAX_NODES && T->exists[node];
}

int setRoot(ChildListTree *T, int node) {
    if (node < 0 || node >= MAX_NODES) return 0;
    if (T->root != NONEXISTENT) return 0;      /* only one root */
    if (T->exists[node]) return 0;             /* must be unused slot */
    T->exists[node] = 1;
    T->root = node;
    T->count++;
    return 1;
}

/* Avoid duplicate child entries under the same parent. */
static int alreadyChild(const ChildListTree *T, int parent, int child) {
    for (Child *p = T->head[parent]; p; p = p->next)
        if (p->idx == child) return 1;
    return 0;
}

/* Insert child under parent. If child index not yet used, it becomes a new node. */
int insertChild(ChildListTree *T, int parent, int child) {
    if (!existsNode(T, parent)) return 0;
    if (child < 0 || child >= MAX_NODES) return 0;

    if (!T->exists[child]) {           /* create node if new */
        T->exists[child] = 1;
        T->count++;
    }
    if (alreadyChild(T, parent, child)) return 0;  /* prevent duplicate edge */

    /* append at end to preserve insertion order like your diagram */
    Child *n = makeChild(child);
    if (!T->head[parent]) {
        T->head[parent] = n;
    } else {
        Child *p = T->head[parent];
        while (p->next) p = p->next;
        p->next = n;
    }
    return 1;
}

/* Collect children of `parent` into out[]; returns number copied (<= outCap). */
int getChildren(const ChildListTree *T, int parent, int out[], int outCap) {
    if (!existsNode(T, parent) || outCap <= 0) return 0;
    int k = 0;
    for (Child *p = T->head[parent]; p; p = p->next) {
        if (k < outCap) out[k] = p->idx;
        k++;
    }
    return (k > outCap ? outCap : k);
}

/* O(n + edges) scan to find parent of `child`. ROOT if child is root.
   Returns NONEXISTENT if child doesn’t exist. */
int findParent(const ChildListTree *T, int child) {
    if (!existsNode(T, child)) return NONEXISTENT;
    if (T->root == child) return ROOT;
    for (int i = 0; i < MAX_NODES; ++i) {
        if (!T->exists[i]) continue;
        for (Child *p = T->head[i]; p; p = p->next)
            if (p->idx == child) return i;
    }
    return NONEXISTENT; /* should not happen for a well-formed tree */
}

/* Remove the single edge parent -> child (does not delete nodes). */
int removeChildEdge(ChildListTree *T, int parent, int child) {
    if (!existsNode(T, parent)) return 0;
    Child **pp = &T->head[parent];
    while (*pp) {
        if ((*pp)->idx == child) {
            Child *dead = *pp;
            *pp = (*pp)->next;
            free(dead);
            return 1;
        }
        pp = &((*pp)->next);
    }
    return 0;
}

/* Recursively delete subtree rooted at `node`.
   Frees child lists and marks nodes as non-existent.
   NOTE: If you also want to detach the node from its parent, call removeChildEdge()
   before calling this, or use deleteNodeAndDetach(). */
void deleteSubtree(ChildListTree *T, int node) {
    if (!existsNode(T, node)) return;

    /* delete all children first */
    Child *p = T->head[node];
    while (p) {
        int ch = p->idx;
        p = p->next;
        deleteSubtree(T, ch);
    }

    /* free this node’s list head */
    p = T->head[node];
    while (p) {
        Child *n = p->next;
        free(p);
        p = n;
    }
    T->head[node] = NULL;

    /* mark node gone */
    T->exists[node] = 0;
    T->count--;

    /* if it was root, clear root marker */
    if (T->root == node) T->root = NONEXISTENT;
}

/* Convenience: detach from parent then delete subtree. */
int deleteNodeAndDetach(ChildListTree *T, int node) {
    if (!existsNode(T, node)) return 0;
    int par = findParent(T, node);
    if (par >= 0) removeChildEdge(T, par, node);
    deleteSubtree(T, node);
    return 1;
}

/* Pretty-print each index and its children list. */
void display(const ChildListTree *T) {
    printf("\nTree (List of Children): count=%d, root=%d\n", T->count, T->root);
    for (int i = 0; i < MAX_NODES; ++i) {
        if (!T->exists[i]) continue;
        printf("%2d: ", i);
        Child *p = T->head[i];
        if (!p) { printf("•\n"); continue; }
        while (p) {
            printf("[%d]%s", p->idx, p->next ? " -> " : "");
            p = p->next;
        }
        printf("\n");
    }
}

/* ================== demo ================== */
int main(void) {
    ChildListTree T;
    initTree(&T);

    /* Build the exact structure from your diagram:
       - root at 5
       - children(5) = 0, 6, 2
       - children(1) = 4, 7
       - children(2) = 8
       - children(6) = 3, 1
    */
    setRoot(&T, 5);

    /* ensure all mentioned nodes exist before linking (optional; insertChild will create) */
    T.exists[0] = T.exists[1] = T.exists[2] = T.exists[3] =
    T.exists[4] = T.exists[6] = T.exists[7] = T.exists[8] = 1;
    T.count += 8;

    insertChild(&T, 5, 0);
    insertChild(&T, 5, 6);
    insertChild(&T, 5, 2);

    insertChild(&T, 1, 4);
    insertChild(&T, 1, 7);

    insertChild(&T, 2, 8);

    insertChild(&T, 6, 3);
    insertChild(&T, 6, 1);

    display(&T);

    /* Query: children of 5 */
    int kids[16]; int k = getChildren(&T, 5, kids, 16);
    printf("\nChildren of 5 (%d): ", k);
    for (int i = 0; i < k; ++i) printf("%d%s", kids[i], i+1<k?", ":"");
    printf("\n");

    /* Query: parent of 8 */
    int par = findParent(&T, 8);
    printf("Parent of 8: %d\n", (par == ROOT ? -1 : par));

    /* Example delete: remove subtree rooted at 2 (and detach from 5) */
    printf("\nDeleting subtree rooted at 2...\n");
    deleteNodeAndDetach(&T, 2);
    display(&T);

    return 0;
}

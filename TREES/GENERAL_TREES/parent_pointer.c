/*
   GENERAL TREE — Static Parent-Pointer Representation
   ---------------------------------------------------
   - Each node is an index 0..N-1.
   - parent[i] holds the index of i's parent.
   - ROOT is -1; NONEXISTENT is -2 (slot unused / deleted).

   Provided Operations:
     • init_tree(parent, N)                       – fill with NONEXISTENT
     • set_root(parent, r)                        – mark r as root
     • set_parent(parent, child, par)             – attach child under par
     • is_valid(parent, i)                        – is node index active?
     • is_root(parent, i)                         – is node a root?
     • get_parent(parent, i)                      – parent index (or ROOT/-2)
     • degree(parent, N, i)                       – number of children
     • list_children(parent, N, i, out, *k)       – fill children of i
     • depth(parent, i)                           – distance (edges) root→i
     • height_tree(parent, N)                     – max depth of any node
     • is_ancestor(parent, a, b)                  – is a an ancestor of b?
     • print_path_to_root(parent, i)              – i → … → root
     • bfs_level_order(parent, N, root)           – breadth-first print
     • delete_subtree(parent, N, i)               – mark i & descendants -2

   Demo uses your sample array:
     index:   0  1  2  3  4  5  6  7  8  9
     parent:  5  6  5  6  1 -1  5  1  2 -2
*/
#include <stdio.h>

#define MAXN  100
#define ROOT        -1
#define NONEXISTENT -2

/* ───── helpers / basic ops ───── */

void init_tree(int parent[], int n) {
    for (int i = 0; i < n; ++i) parent[i] = NONEXISTENT;
}

void set_root(int parent[], int r) { parent[r] = ROOT; }

void set_parent(int parent[], int child, int par) { parent[child] = par; }

int is_valid(int parent[], int i) { return parent[i] != NONEXISTENT; }

int is_root(int parent[], int i)  { return parent[i] == ROOT; }

int get_parent(int parent[], int i) { return parent[i]; }

/* count children of node i (linear scan) */
int degree(int parent[], int n, int i) {
    int cnt = 0;
    for (int v = 0; v < n; ++v)
        if (parent[v] == i) ++cnt;
    return cnt;
}

/* list children of i into out[]; returns via *k how many */
void list_children(int parent[], int n, int i, int out[], int *k) {
    int t = 0;
    for (int v = 0; v < n; ++v)
        if (parent[v] == i) out[t++] = v;
    *k = t;
}

/* depth = number of edges from root to i (ROOT has depth 0) */
int depth(int parent[], int i) {
    int d = 0;
    while (parent[i] != ROOT) {
        i = parent[i];
        ++d;
    }
    return d;
}

/* height(tree) = max depth among all valid nodes */
int height_tree(int parent[], int n) {
    int h = 0;
    for (int i = 0; i < n; ++i)
        if (is_valid(parent, i) && parent[i] != ROOT) {
            int di = depth(parent, i);
            if (di > h) h = di;
        }
    return h;
}

/* is a an ancestor of b ? */
int is_ancestor(int parent[], int a, int b) {
    int cur = b;
    while (parent[cur] != ROOT) {
        cur = parent[cur];
        if (cur == a) return 1;
    }
    return 0;
}

/* print i -> ... -> root */
void print_path_to_root(int parent[], int i) {
    printf("%d", i);
    while (parent[i] != ROOT) {
        i = parent[i];
        printf(" -> %d", i);
    }
    printf(" (root)\n");
}

/* breadth-first (level order) starting at root index r */
void bfs_level_order(int parent[], int n, int r) {
    if (!is_valid(parent, r) || !is_root(parent, r)) return;

    int q[MAXN], front = 0, rear = 0;
    q[rear++] = r;

    while (front < rear) {
        int u = q[front++];
        printf("%d ", u);

        /* enqueue children of u by scanning parent[] */
        for (int v = 0; v < n; ++v)
            if (parent[v] == u) q[rear++] = v;
    }
    printf("\n");
}

/* delete node i and its entire subtree (mark as NONEXISTENT) */
void delete_subtree(int parent[], int n, int i) {
    if (!is_valid(parent, i)) return;

    /* delete children first (post-order over parent array) */
    for (int v = 0; v < n; ++v)
        if (parent[v] == i) delete_subtree(parent, n, v);

    parent[i] = NONEXISTENT;
}

/* pretty print parent array */
void print_parent_array(int parent[], int n) {
    printf("index : ");
    for (int i = 0; i < n; ++i) printf("%3d", i);
    printf("\nparent: ");
    for (int i = 0; i < n; ++i) printf("%3d", parent[i]);
    printf("\n");
}

/* ───── demo ───── */

int main(void) {
    /* Use your sample: Tree B */
    const int N = 10;
    int parent[MAXN];

    init_tree(parent, N);
    /* index:   0  1  2  3  4  5  6  7  8  9
       parent:  5  6  5  6  1 -1  5  1  2 -2 */
    int init_vals[10] = {5, 6, 5, 6, 1, -1, 5, 1, 2, -2};
    for (int i = 0; i < N; ++i) parent[i] = init_vals[i];

    printf("PARENT-POINTER ARRAY (ROOT=%d, NONEXISTENT=%d)\n", ROOT, NONEXISTENT);
    print_parent_array(parent, N);

    /* Basic queries */
    printf("\nBasic queries:\n");
    printf("Parent of node 2 is %d\n", get_parent(parent, 2));   // expect 5
    printf("Is node 5 root? %s\n", is_root(parent, 5) ? "yes" : "no");
    printf("Depth of node 4: %d\n", depth(parent, 4));           // 4->1->6->5->ROOT (depth 4)? wait check array: 4's parent=1, 1's parent=6, 6's parent=5, 5 is ROOT → depth 3
    printf("Tree height (max depth): %d\n", height_tree(parent, N));

    /* Children & degree */
    int kids[MAXN], k = 0;
    list_children(parent, N, 5, kids, &k);
    printf("\nChildren of node 5: ");
    for (int i = 0; i < k; ++i) printf("%d ", kids[i]);
    printf("(degree=%d)\n", degree(parent, N, 5));

    /* Path sample */
    printf("\nPath node 4 to root: ");
    print_path_to_root(parent, 4);

    /* Ancestor test */
    printf("Is 6 an ancestor of 4? %s\n", is_ancestor(parent, 6, 4) ? "yes" : "no");

    /* Level-order (needs the root index; here 5) */
    printf("\nBFS (level-order) from root 5: ");
    bfs_level_order(parent, N, 5);

    /* Deletion demo: delete subtree rooted at node 1 */
    printf("\nDelete subtree at node 1\n");
    delete_subtree(parent, N, 1);
    print_parent_array(parent, N);

    /* Attach a new node 9 under 5 (reusing NONEXISTENT slot or leaving as is) */
    set_parent(parent, 9, 5);
    printf("\nAfter attaching node 9 under 5:\n");
    print_parent_array(parent, N);

    return 0;
}

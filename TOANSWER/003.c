/*
PROBLEM: Unsorted Linked-List SET (Manual Dedupe Practice)

You will implement a SET ADT where the underlying list is **unsorted**.
All operations must enforce **set semantics** (no duplicates in results),
but inputs may contain duplicates. Practice scanning and pointer-to-pointer
for insertion/removal.

Implement:
  1) bool insertHeadUnique(SET *S, int x)   // O(n) check-then-head-insert (use p** for practice)
  2) bool removeValue(SET *S, int x)        // O(n), pointer-to-pointer delete
  3) SET  unionSet(SET A, SET B)            // O(|A|·|C| + |B|·|C|), check C before insert
  4) SET  intersectSet(SET A, SET B)        // O(|A|·|B| + |A|·|C|)
  5) SET  differenceSet(SET A, SET B)       // O(|A|·|B| + |A|·|C|)
  6) void freeSet(SET *S)

Notes:
- For union/intersect/difference, results must be duplicate-free even if inputs have duplicates.
- Order does NOT matter (head-insert is fine).
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *link;
} Node, *NodePtr;

typedef NodePtr SET;

/* ---------- Display helper (given) ---------- */
static void displaySet(SET S) {
    for (NodePtr p = S; p != NULL; p = p->link) {
        printf("%d", p->data);
        if (p->link) printf(" -> ");
    }
    printf(" -> NULL\n");
}

/* ---------- TODO: implement these ---------- */

// 1) Insert x at head IF x is not already in S. Return true if inserted.
//    Practice: do a membership scan, then head-insert via pointer-to-pointer (*S).
bool insertHeadUnique(SET *S, int x) {
    // TODO:
    // for (NodePtr p = *S; p; p = p->link) if (p->data == x) return false;
    // NodePtr n = malloc(...); n->data = x; n->link = *S; *S = n; return true;
    (void)S; (void)x;
    return false;
}

// 2) Remove x if present; pointer-to-pointer delete; return true if removed.
bool removeValue(SET *S, int x) {
    // TODO (same technique as in sorted version)
    (void)S; (void)x;
    return false;
}

// 3) C = A ∪ B (unsorted). Build C by scanning C before each insert (to keep it unique).
SET unionSet(SET A, SET B) {
    // TODO:
    // SET C = NULL;
    // for pa in A: if (not in C) head-insert
    // for pb in B: if (not in C) head-insert
    (void)A; (void)B;
    return NULL;
}

// 4) C = A ∩ B (unsorted). For each a in A, if exists in B and not in C, head-insert.
SET intersectSet(SET A, SET B) {
    // TODO:
    (void)A; (void)B;
    return NULL;
}

// 5) C = A \ B (unsorted). For each a in A, if NOT in B and not in C, head-insert.
SET differenceSet(SET A, SET B) {
    // TODO:
    (void)A; (void)B;
    return NULL;
}

// 6) Free all nodes.
void freeSet(SET *S) {
    // TODO:
    (void)S;
}

/* ---------- Demo / test main ---------- */
int main(void) {
    SET A = NULL, B = NULL;

    // Build A with duplicates mixed in
    insertHeadUnique(&A, 5);
    insertHeadUnique(&A, 1);
    insertHeadUnique(&A, 9);
    insertHeadUnique(&A, 5);  // dup, should not insert
    insertHeadUnique(&A, 7);

    // Build B with duplicates mixed in
    insertHeadUnique(&B, 3);
    insertHeadUnique(&B, 7);
    insertHeadUnique(&B, 10);
    insertHeadUnique(&B, 3);  // dup
    insertHeadUnique(&B, 2);

    printf("A: "); displaySet(A);   // order arbitrary
    printf("B: "); displaySet(B);   // order arbitrary

    SET U = unionSet(A, B);
    SET I = intersectSet(A, B);
    SET D = differenceSet(A, B);

    printf("A ∪ B: "); displaySet(U);   // should contain 1,2,3,5,7,9,10 (order arbitrary)
    printf("A ∩ B: "); displaySet(I);   // should contain {7} (and maybe others if present)
    printf("A \\ B: "); displaySet(D);  // should contain {1,5,9}

    printf("Remove 7 from A...\n");
    removeValue(&A, 7);
    printf("A: "); displaySet(A);

    freeSet(&A); freeSet(&B);
    freeSet(&U); freeSet(&I); freeSet(&D);
    return 0;
}

/*
PROBLEM: Sorted Linked-List SET (Pointer-to-Pointer Practice)

You will implement a SET ADT using a singly linked list of ints that is
kept in **sorted ascending order** with **no duplicates**. You MUST use
pointer-to-pointer where indicated (insertion, deletion, etc.).

Implement these operations (all assume sorted inputs and produce sorted, deduped outputs):
  1) bool insertSorted(SET *S, int x)         // O(n), keep sorted, no dups (use p**)
  2) bool removeValue(SET *S, int x)          // O(n), remove if present (use p**)
  3) SET  unionSet(SET A, SET B)              // O(n+m), merge-style
  4) SET  intersectSet(SET A, SET B)          // O(n+m), merge-style
  5) SET  differenceSet(SET A, SET B)         // O(n+m), A \ B, merge-style
  6) void freeSet(SET *S)                     // O(n), free all nodes (use p** or normal)

RULES:
- Use ONLY the Node/NodePtr/SET typedefs provided below.
- Do NOT reorder to unsorted; preserve ascending order always.
- Do NOT insert duplicates.
- Hints are left as comments in TODOs.
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

//    MUST use pointer-to-pointer traversal: NodePtr *pp = &head; ...
bool insertSorted(SET *S, int x) {
    
    NodePtr* temp = S;

    for(; *temp != NULL && (*temp)->data < x; temp = &(*temp)->link) {}
        if ( *temp != NULL && (*temp)->data == x) {
        return false;
    }

    
    

    NodePtr new = malloc(sizeof(Node));
    if (!new) {
        printf("Dynamic Memory allocation failed.\n");
        return false;
    }
    new->data = x;

    new->link= *temp; // ! temp is the new node that will come after hte new node
    *temp = new; // ! make the previous pointer now point to new
   
    return true;
}
//    MUST use pointer-to-pointer so you can delete head/middle uniformly.
bool removeValue(SET *S, int x) {

    SET* trav = S;
    for(; *trav != NULL; trav = &(*trav)->link) {
        if ((*trav)->data == x) {
            NodePtr toRemove = *trav;
            *trav = (*trav)->link;
            free(toRemove);
            return true;
        }
    }
    return false;
   
}

// 3) A ∪ B (sorted, deduped). Use two cursors pa/pb and one tail pointer (or p** tail).
SET unionSet(SET A, SET B) {
    
    SET C = NULL;
    SET tail = NULL;
    NodePtr pa = A;
    NodePtr pb = B;

    while (pa && pb) { 
        int v;
        if (pa->data < pb->data) {
            v = pa->data;
            pa = pa->link;
        } else if (pa->data > pb->data) {
            v = pb->data;
            pb = pb->link;
        } else if (pa->data == pb->data) {
            v = pa->data;
            pa = pa->link;
            pb = pb->link;
        }


        NodePtr new = malloc(sizeof(Node));
        if (!new) {printf("Dynamic Memory Allocation failed.\n");}
        new->data = v;
        new->link = NULL;

        if (C == NULL) {
            C = new;
            tail = new;
        
        } else {
            tail->link = new;
            tail = new;
        }

    }



    while (pa) {
        int v = pa->data;
        
          NodePtr new = malloc(sizeof(Node));
        if (!new) {printf("Dynamic Memory Allocation failed.\n");}
        new->data = v;
        new->link = NULL;

        if (C == NULL) {
            C = new;
            tail = new;
        
        } else {
            tail->link = new;
            tail = new;
        }
        pa = pa->link;
    }


    while (pb) {
        int v = pb->data;

        
          NodePtr new = malloc(sizeof(Node));
        if (!new) {printf("Dynamic Memory Allocation failed.\n");}
        new->data = v;
        new->link = NULL;

        if (C == NULL) {
            C = new;
            tail = new;
        
        } else {
            tail->link = new;
            tail = new;
        }
        pb = pb->link;
    }
    return C;
}

// 4) A ∩ B (sorted, deduped). Linear time; append each common value once.
SET intersectSet(SET A, SET B) {


    SET C = NULL;
    SET tail = NULL;
    NodePtr pa = A;
    NodePtr pb = B;


    while (pa && pb) {
        if (pa->data < pb->data) {
            pa = pa->link;
        } else if(pa->data > pb->data) {
            pb = pb->link;
        } else if (pa->data == pb->data) {
            NodePtr new = malloc(sizeof(Node));
            if (!new) {printf("Allocation failed.\n");
            return C;}
            new->data = pa->data;
            new->link = NULL;

            if (C == NULL) {
                C = new;
                tail = new;
            } else {
                tail->link = new;
                tail = new;
            }
            

            pa = pa->link;
            pb = pb->link;
        }
    }

    return C;

}

// 5) A \ B (sorted, deduped). Output values that appear in A but not in B.
SET differenceSet(SET A, SET B) {
    
    SET C = NULL;
    SET tail = NULL;
    NodePtr pa = A;
    NodePtr pb = B;

    while (pa && pb) {
        int v;
        if (pa->data < pb->data) {
            v = pa->data;
            NodePtr new = malloc(sizeof(Node));
        new->data = v;
        new->link = NULL;
        if (C == NULL) {
            C = new;
            tail = new;
        } else {
            tail->link = new;
            tail = new;
        }
            pa = pa->link;
        } else if (pa->data > pb->data) {
            pb = pb->link;
        } else if (pa->data == pb->data) {
            pa = pa->link;
            pb = pb->link;
        }

        

    }



    while (pa) {
        int v = pa->data;
         NodePtr new = malloc(sizeof(Node));
        new->data = v;
        new->link = NULL;
        if (C == NULL) {
            C = new;
            tail = new;
        } else {
            tail->link = new;
            tail = new;
        }
        pa = pa->link;

    }
    return C;
}

// 6) Free all nodes; leave *S == NULL at end.
void freeSet(SET *S) {
    

    SET temp;
    while (*S != NULL) { // ! while set is not empty, store the current head node, move the head to the next ndoe, then free the old head node
        temp = *S;
        *S = (*S)->link;
        free(temp);
    }

    *S = NULL;
}

/* ---------- Demo / test main ---------- */
int main(void) {
    SET A = NULL, B = NULL;

    /* Build A: 1,3,5,7,9 */
    insertSorted(&A, 5);
    insertSorted(&A, 1);
    insertSorted(&A, 9);
    insertSorted(&A, 7);
    insertSorted(&A, 3);
    insertSorted(&A, 3);   // duplicate (should not insert)

    /* Build B: 2,3,6,7,10 */
    insertSorted(&B, 7);
    insertSorted(&B, 2);
    insertSorted(&B, 10);
    insertSorted(&B, 6);
    insertSorted(&B, 3);

    printf("A: "); displaySet(A);
    printf("B: "); displaySet(B);

    SET U = unionSet(A, B);
    SET I = intersectSet(A, B);
    SET D = differenceSet(A, B);

    printf("A union B: "); displaySet(U);   // expected: 1 2 3 5 6 7 9 10
    printf("A intersect B: "); displaySet(I);   // expected: 3 7
    printf("A difference B: "); displaySet(D);  // expected: 1 5 9

    printf("Remove 7 from A...\n");
    removeValue(&A, 7);
    printf("A: "); displaySet(A);       // expected: 1 3 5 9

    freeSet(&A); freeSet(&B);
    freeSet(&U); freeSet(&I); freeSet(&D);
    return 0;
}

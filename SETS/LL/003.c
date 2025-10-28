#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *link;
} Node, *NodePtr;

typedef NodePtr SET;

/* ---------- Function Declarations ---------- */
bool insertHeadUnique(SET *S, int x) {
    NodePtr trav = *S;


for(; trav != NULL; trav = trav->link) {
    if (trav->data == x) {
        return false;
    }
}

NodePtr new = malloc(sizeof(Node));
new->data = x;
new->link = *S;
*S = new;
return true;

}


bool removeValue(SET *S, int x) {
    NodePtr* trav = (S);

    for(; *trav != NULL; trav = &(*trav)->link) {
        if ((*trav)->data == x) {
            NodePtr toRemove = *trav;
            *trav = toRemove->link;
            free(trav);
            return true;
        }
    }
    return false;
}


SET unionSet(SET A, SET B) {
    Node* ptrA = A;
    Node* ptrB = B;

    SET C = NULL;

    while (ptrA) {
        
        Node* new = malloc(sizeof(Node));
        new->data = ptrA->data;
        new->link = C;
        C = new;
        ptrA = ptrA->link;
    }


    while (ptrB) {
        bool inC = false;

        Node* trav = C;
        while (trav) {
            if (trav->data == ptrB->data) {
                inC = true;break;
            }
            trav = trav->link;
        }

        if (!inC) {
            Node* new = malloc(sizeof(Node));
            new->data = ptrB->data;
            new->link = C;
            C = new;
        }


        ptrB = ptrB->link;
    }
    return C;
}
SET intersectSet(SET A, SET B) {

    SET C = NULL;

    Node* ptrA = A;
    Node* ptrB = B;

    while (ptrA) {

        bool inB= false;
        for(; ptrB != NULL; ptrB = ptrB->link) {
            if (ptrB->data == ptrA->data) {
                inB = true;
                break;
            }
        }


        if (inB) {
            Node* new = malloc(sizeof(Node));
            new->data = ptrA->data;
            new->link = C;
            C = new;
        }
        ptrA = ptrA ->link;
    }
    return C;
}


SET differenceSet(SET A, SET B) {
    SET C = NULL;

    NodePtr ptrA = A;
    NodePtr ptrB = B;

    while (ptrA) {

        bool inB = false;

        for(; ptrB != NULL; ptrB = ptrB->link) {
            if (ptrB->data == ptrA->data) {
                inB = true;
                break;
            }
        }

        if (!inB) {
            Node* new = malloc(sizeof(Node));
            new->data = ptrA->data;
            new->link = C;
            C = new;
        }
        ptrA = ptrA->link;
    }

    return C;
}
void freeSet(SET *S) {
    Node* temp;

    while (*S) {
        temp = *S;
        *S = temp->link;
        free(temp);
    }
    S = NULL;
}
void displaySet(SET S) {
    Node* temp = S;


    while (temp) {
        printf("%d", temp->data);

        if (temp->link != NULL) {
            printf("->");
        }
        temp = temp->link;
    }
}

/* ---------- Main ---------- */
int main(void) {
    SET A = NULL, B = NULL;

    insertHeadUnique(&A, 5);
    insertHeadUnique(&A, 1);
    insertHeadUnique(&A, 9);
    insertHeadUnique(&A, 5);
    insertHeadUnique(&A, 7);

    insertHeadUnique(&B, 3);
    insertHeadUnique(&B, 7);
    insertHeadUnique(&B, 10);
    insertHeadUnique(&B, 3);
    insertHeadUnique(&B, 2);

    printf("A: "); displaySet(A);
    printf("\n");
    printf("B: "); displaySet(B);printf("\n");

    SET U = unionSet(A, B);
    SET I = intersectSet(A, B);
    SET D = differenceSet(A, B);

    printf("A ∪ B: "); displaySet(U);printf("\n");
    printf("A ∩ B: "); displaySet(I);printf("\n");
    printf("A \\ B: "); displaySet(D);printf("\n");
printf("\n");
    printf("Remove 7 from A...\n");
    removeValue(&A, 7);
    printf("A: "); displaySet(A);printf("\n");

    freeSet(&A);
    freeSet(&B);
    freeSet(&U);
    freeSet(&I);
    freeSet(&D);
    return 0;
}

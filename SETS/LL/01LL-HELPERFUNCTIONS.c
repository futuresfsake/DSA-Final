#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ===============================
// STRUCT DEFINITIONS
// ===============================
typedef struct {
    char name[30];
    int id;
} Item;

typedef struct Node {
    Item item;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} Set;

// ===============================
// FUNCTION DECLARATIONS
// ===============================
void initSet(Set *S) {
    S->head = NULL;
}
void insert(Set *S, char *name, int id) {
    

    Node* new = malloc(sizeof(Node));
    new->item.id = id;
    strcpy(new->item.name, name);
    new->next = S->head;
    S->head = new;
}

void displaySet(Set *S) {

    Node* trav = S->head;
    while (trav != NULL) {
        printf("[%s, %d]->", trav->item.name, trav->item.id);
        trav = trav->next;
    }
    printf("NULL\n");
}

// ✨ YOU WILL IMPLEMENT THESE ✨
void removeDuplicates(Set *S) {
    


    Node* ptrA = S->head;

    while (ptrA) {

        Node** ptrB = &(ptrA->next);

        for(; *ptrB != NULL;) {
            if ((*ptrB)->item.id == ptrA->item.id) {
                Node* toRemove = *ptrB;
                *ptrB = toRemove->next;
                free(toRemove);
            } else {
                ptrB = &(*ptrB)->next;
            }
        }
        ptrA =ptrA->next;

        }

}


int countCommonElements(Set *A, Set *B) {
    Node* ptrA = A->head;
    int count = 0;


    while (ptrA) {
        
        
        Node* ptrB = B->head;

        for(; ptrB!= NULL; ptrB = ptrB->next) {
            if (ptrA->item.id == ptrB->item.id) {
                count++;
            }
        }
        ptrA = ptrA->next;
    }

    return count;
}


void mergeIfSubset(Set *A, Set *B) {

    Node* ptrB = B->head;

    while (ptrB) {
        bool inA = false;

      


        Node* ptrA = A->head;
        for(; ptrA != NULL; ptrA = ptrA->next) {
            if (ptrA->item.id == ptrB->item.id) {
                inA = true;
                break;
                
            }
        }

        if (!inA) {
              Node* new = malloc(sizeof(Node));
        strcpy(new->item.name, ptrB->item.name);
        new->item.id = ptrB->item.id;
            new->next = A->head;
            A->head = new;
            break;
            
        }

        ptrB = ptrB->next;
    }

   
}

// ===============================
// MAIN FUNCTION (for testing)
// ===============================
int main() {
    Set A, B;
    initSet(&A);
    initSet(&B);

    printf("Inserting elements into Set A:\n");
    insert(&A, "Pen", 101);
    insert(&A, "Notebook", 102);
    insert(&A, "Eraser", 103);
    insert(&A, "Ruler", 104);
    insert(&A, "Ruler", 104);  // duplicate to test

    printf("\nSet A:\n");
    displaySet(&A);

    printf("\nInserting elements into Set B:\n");
    insert(&B, "Notebook", 102);
    insert(&B, "Ruler", 104);
    insert(&B, "Stapler", 105);

    printf("\nSet B:\n");
    displaySet(&B);

    printf("\nRemoving duplicates from A...\n");
    removeDuplicates(&A);
    displaySet(&A);

    printf("\nCounting common elements between A and B...\n");
    int common = countCommonElements(&A, &B);
    printf("Common elements: %d\n", common);

    printf("\nMerging if B is subset of A...\n");
    mergeIfSubset(&A, &B);
    displaySet(&A);

    return 0;
}

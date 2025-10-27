/************************************************************
 🧠 LINKED LIST BASED SET (DOUBLE POINTER + STRUCTURED ITEMS)
*************************************************************

📘 CONTEXT:
------------
We are upgrading the Set ADT to:
  - Use **double pointers** (`Node **head`) for more flexible operations.
  - Store **structured items**:
        { int id; char name[50]; }
  - Represent **school supplies** (unique by name or ID).
  - Perform **set operations**: union, intersection, difference, etc.
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



// === Item Definition ===
typedef struct {
    int id;
    char name[50];
} Supply;

// === Node and Set Definitions ===
typedef struct node {
    Supply item;
    struct node *next;
} Node;

typedef struct {
    Node *head;
} Set;

// === Function Prototypes ===

// --- Basic Operations ---
void initSet(Set *S);
bool insert(Set *S, int id, char *name);
bool delete(Set *S, int id);
bool isMember(Set *S, int id);
void display(Set *S);

// --- Set Operations ---
Set setUnion(Set *A, Set *B);
Set setIntersection(Set *A, Set *B);
Set setDifference(Set *A, Set *B);

// // --- Special / Advanced Operations ---
// void removeDuplicates(Set *S);
// int countCommonElements(Set *A, Set *B);
// void mergeIfSubset(Set *A, Set *B);

// === Helper Function (Optional) ===
Node *createNode(int id, char *name);


// === MAIN FUNCTION ===
int main() {
    Set A, B, U, I, D;
    initSet(&A);
    initSet(&B);

    printf(" Inserting school supplies into Set A:\n");
    insert(&A, 101, "Pencil");
    insert(&A, 102, "Notebook");
    insert(&A, 103, "Eraser");
    insert(&A, 108, "YellowPad");
    display(&A);

    printf("\n Inserting school supplies into Set B:\n");
    insert(&B, 104, "Crayon");
    insert(&B, 105, "Ruler");
    insert(&B, 103, "Eraser");
    insert(&B, 108, "YellowPad"); 
    insert(&B, 111, "Stapler"); // common item
    display(&B);


    // printf("Testing deleting Pencil..\n");
    // delete(&A, 101);

    // display(&A);

    // printf("Testing if ID 120 Exists? ");
    // if(isMember(&B, 120)) {printf("Yes\n");} else {printf("No\n");}
    printf("\n🧮 Performing Set Operations...\n");

    U = setUnion(&A, &B);
    printf("\nUnion (A ∪ B):\n");
    display(&U);

    I = setIntersection(&A, &B);
    printf("\nIntersection (A ∩ B):\n");
    display(&I);

    D = setDifference(&A, &B);
    printf("\nDifference (A - B):\n");
    display(&D);

    // printf("\n🔁 Counting Common Elements: %d\n", countCommonElements(&A, &B));

    // printf("\n🧹 Removing Duplicates in A (if any)...\n");
    // removeDuplicates(&A);
    // display(&A);

    // printf("\n🧩 Merging B into A if B ⊆ A...\n");
    // mergeIfSubset(&A, &B);
    // display(&A);

    return 0;
}

// ============================================================
// 🧱 STRUCTURE: Function Definitions (You Implement These)
// ============================================================
void initSet(Set *S) {

  S->head = NULL;

}

Node *createNode(int id, char *name) {
  Node* new = malloc(sizeof(Node));
  if (!new) {
    printf("Dynamic memory allocation failed!");
  }

  strcpy(new->item.name, name);
  new->item.id = id;
  new->next = NULL;
  return new;

}

bool insert(Set *S, int id, char *name) {
  
  Node* trav = S->head;

  for(; trav != NULL; trav = trav->next) {
    if (trav->item.id == id && strcmp(trav->item.name, name) ==0) {
      printf("Item already exists! Failed to insert.\n");
      return false;
    }  
  }


  Node* new = createNode(id, name);
  

  Node** temp = &(S->head);
  for(; *temp != NULL && (*temp)->item.id < id; temp = &(*temp)->next) {}
  new->next = *temp;
  *temp = new;

  return true;
}



bool delete(Set *S, int id) {

  Node** trav = &(S->head);

  for(; *trav != NULL; trav = &(*trav)->next) {
    if ((*trav)->item.id == id) {
      Node* toRemove = *trav;
      *trav = toRemove->next;
      free(toRemove);
      return true;
    }
  }
  return false;
}
bool isMember(Set *S, int id) {
  Node* trav = S->head;

  for(; trav != NULL ; trav = trav->next) {
    if (trav->item.id == id) {
      return true;
    }
  }
  return false;
}
void display(Set *S) {
  
printf("List\n\n");
  Node* trav = S->head;
  while (trav) {
    printf(" [%s,%d] -> ", trav->item.name, trav->item.id);
    trav = trav->next;
  }
  printf(" NULL\n");
}

// --- Set Operations ---
Set setUnion(Set *A, Set *B) {
  
Set C;
initSet(&C);
  Node* trav1 = A->head;
  Node* trav2 = B->head;

  while (trav1) {

    
    bool inC = false;


    Node** trav = &(C.head);
    
      for(; *trav != NULL &&  (*trav)->item.id < trav1->item.id; trav = &(*trav)->next) {}
      if (*trav != NULL && (*trav)->item.id == trav1->item.id) { inC = true; }
      
      if (!inC) {
      Node* new = createNode(trav1->item.id, trav1->item.name);


      new->next = *trav;
      *trav = new;

      }

      trav1 = trav1->next;
    }
    
  



    while (trav2) {

      bool inC = false;

      Node** temp = &(C.head);
      for(; *temp != NULL && (*temp)->item.id < trav2->item.id; temp = &(*temp)->next) {}
      if (*temp != NULL && (*temp)->item.id == trav2->item.id) {inC = true; }

      if (!inC) {
        Node* new = createNode(trav2->item.id, trav2->item.name);

        new->next = *temp;
        *temp = new;
      }




      trav2=trav2->next;
    }
  return C;
}
Set setIntersection(Set *A, Set *B) {

  Set C;
  initSet(&C);
  Node* ptrA = A->head;


  while (ptrA) {

    bool inB = false;
    Node* ptrB = B->head;
    for(; ptrB != NULL; ptrB = ptrB->next) {
      if (ptrB->item.id == ptrA->item.id) {
        inB = true;
        break;
      }
    }


    if (inB) {
      bool inC = false;
      Node** ptrC = &(C.head);
      for(; *ptrC != NULL && (*ptrC)->item.id < ptrA->item.id; ptrC = &(*ptrC)->next) {}
      if (*ptrC != NULL && (*ptrC)->item.id == ptrA->item.id) {

        inC = true;
      }


      if (!inC) {
        Node* new = createNode(ptrA->item.id, ptrA->item.name);
        new->next = *ptrC;
        *ptrC = new;
      }
    }

    ptrA = ptrA->next;

  }

  return C;
}
Set setDifference(Set *A, Set *B) {

  Set C;
  initSet(&C);


  Node* ptrA = A->head;

  while (ptrA) {

    bool inB = false;

    Node* ptrB = B->head;

    for(; ptrB != NULL; ptrB = ptrB->next) {
      if (ptrB->item.id == ptrA->item.id) {
        inB = true;
        break;
      }
    }


    if (!inB) {
      bool inC = false;
      Node** ptrC = &(C.head);


      for(; *ptrC != NULL && (*ptrC)->item.id < ptrA->item.id; ptrC = &(*ptrC)->next) {}
        if ( *ptrC != NULL && (*ptrC)->item.id == ptrA->item.id) {
          inC = true;
          
        }
      


      if (!inC) {
        Node* new = createNode(ptrA->item.id, ptrA->item.name);
        new->next = *ptrC;
        *ptrC = new;
      }
    }



    ptrA = ptrA->next;
  }

  return C;
}

// --- Special / Advanced Operations ---
void removeDuplicates(Set *S) {

  Node* ptrA = S->head;

  while (ptrA) {
    Node** ptrB = &(ptrA->next);

    for(; *ptrB != NULL; ) {
      if ((*ptrB)->item.id == ptrA->item.id) {
        Node* Remove = *ptrB;
        *ptrB = Remove->next;
        free(Remove);
      } else {
        ptrB = &(*ptrB)->next;
      }
    }

    ptrA = ptrA->next;  //! go to the next outer poitener
  }
}
// int countCommonElements(Set *A, Set *B);
// void mergeIfSubset(Set *A, Set *B);

// // === Helper Function (Optional) ===

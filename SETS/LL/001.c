// ! we do not need to predefine the capacity unlike arrays
// ! this is just unsorted insertion
// ! we assume that the set is unsorted
// ! no duplicates allowed, insert implementation prevents duplciates
// ! dynamic memory allocation


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    
    struct Node *link;
} Node,*NodePtr;

typedef NodePtr SET;

void displaySet(SET A);
void insertSet(SET *A, int elem);
SET CreateSet();
SET unionSet(SET A, SET B);
SET intersectSet(SET A, SET B);
SET difference(SET A, SET B);
bool RemoveDate(SET *A, int value);
bool IsMember(SET *A, int value);
bool FreeMem(SET *A);

int main() {
    // Create two empty sets
    SET A = CreateSet();
    SET B = CreateSet();

    // Insert elements into Set A
    insertSet(&A, 9);
    insertSet(&A, 10);
    insertSet(&A, 8);
    insertSet(&A, 9);   // duplicate — should be ignored

    // Insert elements into Set B
    insertSet(&B, 10);
    insertSet(&B, 12);
    insertSet(&B, 123);

    // Display the original sets
    printf("Set A: ");
    displaySet(A);

    printf("Set B: ");
    displaySet(B);

    // Perform and display the UNION of A and B
    SET C = unionSet(A, B);
    printf("Union (A and B): ");
    displaySet(C);

    // Perform and display the INTERSECTION of A and B
    SET D = intersectSet(A, B);
    printf("Intersection (A ∩ B): ");
    displaySet(D);

    // Perform and display the DIFFERENCE of A and B
    SET E = difference(A, B);
    printf("Difference (A - B): ");
    displaySet(E);

    // Example of removing an element from A
    printf("\nRemoving 10 from Set A...\n");
    RemoveDate(&A, 10);
    printf("Updated Set A: ");
    displaySet(A);

    // Example of checking membership
    int checkVal = 9;
    if (IsMember(&A, checkVal))
        printf("%d is a member of Set A.\n", checkVal);
    else
        printf("%d is NOT a member of Set A.\n", checkVal);

    // Optional: free memory
    FreeMem(&A);
    FreeMem(&B);
    FreeMem(&C);
    // FreeMem(&D);
    // FreeMem(&E);

    return 0;
}


SET CreateSet() {
    SET new;

    new = NULL;
 
    return new;
}

bool RemoveDate(SET *A, int value) {

    NodePtr* temp = A;

    for(; (*temp) != NULL; temp = &(*temp)->link) {
        if ((*temp)->data == value) {
            NodePtr toRemove = *temp;
            *temp = (*temp)->link;
            free(toRemove);
           
            return true;
        }
    }

    return false;
}


bool IsMember(SET *A, int value) {

    NodePtr* temp = A;

    for(; (*temp) != NULL; temp = &(*temp)->link) {
        if ((*temp)->data == value) {
            return true;
        }
    }
    return false;
}


bool FreeMem(SET *A) {

    NodePtr* temp;

    while (*A != NULL){
    temp = A;
    *A = (*A)->link;
    free(temp);

    }
    return true;
}





void displaySet(SET A) {

    NodePtr temp = A;

    while (temp != NULL) {
        printf("%d->", temp->data);
        temp = temp->link;

    }

    printf("NULL\n");
    
}


// ! this assumes that the set is not sorted
void insertSet(SET *A, int elem) {
    // Purpose: Insert a new element into the set in sorted order,
    //           ensuring no duplicate elements are inserted.

    bool found = false;
    NodePtr temp = *A;

    while (temp != NULL) {
        if ((temp)->data == elem) {
            printf("%d already exists!.\n", elem);
            found = true;
            break; // ! put a break, so it will stop looping
        }
        temp = (temp)->link;
    }


        if (!found) {
    NodePtr newNode = malloc(sizeof(Node));
    if (!newNode) {
        printf("Dynamic Memory allocation failed.\n");
        exit(1);
    }

    newNode->data = elem;
    newNode->link = (*A); // ? do not forget to link the first node of the list, and update the original set
    *A = newNode; // ! update the head

    printf("%d Successfully inserted.\n" ,elem);
    
}
}


// SET intersectSet(SET A, SET B) {
//     // Purpose: Return a new set that contains only the elements 
//     //           that are common between sets A and B.


//     SET newSet = CreateSet();

//     NodePtr forA = A;
//     NodePtr forB = B;

//     int found = false;

    
//     while (forA != NULL) {

//         while (forB!= NULL) {
//         if (forA->data == forB->data) {
//             forB = forB->link;
//             found = true;
//             break;
//         }
        
    
        
//     }

//     if (found) {
//         NodePtr new = malloc(sizeof(Node));
//         new->data = forA->data;
//         new->link = newSet;
//         newSet = new;
//     }

//     forA = forA->link;
    

    
// }

//     return newSet;


    

// }

SET intersectSet(SET A, SET B) {
    // Purpose: Return a new set that contains only the elements 
    //           that are common between sets A and B.

    SET newSet = CreateSet();
    NodePtr forA = A;
    NodePtr forB;

    while (forA != NULL) {
        bool found = false;  // reset for each A node
        forB = B;            // reset B to head for each new A

        while (forB != NULL) {
            if (forA->data == forB->data) {
                found = true;
                break; // match found, no need to continue inner loop
            }
            forB = forB->link;
        }

        if (found) {
            // Insert into new set
            NodePtr newNode = malloc(sizeof(Node));
            newNode->data = forA->data;
            newNode->link = newSet;
            newSet = newNode;
        }

        forA = forA->link;
    }

    return newSet;


}

SET unionSet(SET A, SET B) {
    // Purpose: Return a new set that contains all unique elements 
    //           from both sets A and B (no duplicates).

    SET C = NULL;   // ? initialize the newSet first
   
    

    NodePtr forA = A;  // ! assign the temporary nodeptr to traverse through the original set
    NodePtr forB = B;


    while (forA != NULL) { // ! for set A, automatically store it in C
        NodePtr new = malloc(sizeof(Node));
        new->data = forA->data;
        new->link = C;
        C = new;
        forA = forA->link;
       
    }


    while (forB != NULL) {    // ! forB, you have to check if it is a member before you store it
        bool found = false;
        NodePtr temp = C;

        while (temp != NULL) {
            if (temp->data == forB->data) {
                found = true;
                break;
            }
            temp = temp->link;
        }

        if (!found) {
            NodePtr newB = malloc(sizeof(Node));
            newB->data = forB->data;
            newB->link = C;
            C = newB;
        }
        forB = forB->link;
    }
    return C;

}



SET difference(SET A, SET B) {
    // Purpose: Return a new set that contains only the elements 
    //           that are common between sets A and B.

    SET newSet = CreateSet();
    NodePtr forA = A;
    NodePtr forB;

    while (forA != NULL) {
        bool found = false;  // reset for each A node
        forB = B;            // reset B to head for each new A

        while (forB != NULL) {
            if (forA->data == forB->data) {
                found = true;
                break; // match found, no need to continue inner loop
            }
            forB = forB->link;
        }

        if (!found) {
            // Insert into new set
            NodePtr newNode = malloc(sizeof(Node));
            newNode->data = forA->data;
            newNode->link = newSet;
            newSet = newNode;
        }

        forA = forA->link;
    }

    return newSet;


}
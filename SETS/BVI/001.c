// * -> a SET ADT implemented as a bit-vector (boolean array)

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef enum {FALSE, TRUE} Boolean;
typedef int SET[MAX];

SET *initSet();
void displayBits(SET A);
void displayElems(SET A);
void insertBit(SET *A, int pos);
void deleteBit(SET *A, int pos);
SET *unionSet(SET A, SET B);
SET *intersectionSet(SET A, SET B);
SET *differenceSet(SET A, SET B);
Boolean isMember(SET A, int pos);
Boolean isSubset(SET A, SET B);



int main()
{
    SET *mySet, *yourSet;

    //initialize set
    mySet = initSet();
    yourSet = initSet();
   
   
    
    insertBit(mySet, 1);
    insertBit(mySet, 2);
    insertBit(mySet, 3);
    insertBit(mySet, 4);
    insertBit(mySet, 5);
    
    displayBits(*mySet);
    
    
    insertBit(yourSet, 1);
    insertBit(yourSet, 2);
    insertBit(yourSet, 3);
    insertBit(yourSet, 4);
    insertBit(yourSet, 5);
    insertBit(yourSet, 9);
   
    displayBits(*yourSet);
    

    //union of two sets
    printf("\nUNION SETS\n");
    SET *newSet = unionSet(*mySet, *yourSet);
    displayBits(*newSet);

     //union of two sets
    printf("\nINTERSECTION SETS\n");
    SET *newSet1 = intersectionSet(*mySet, *yourSet);
    displayBits(*newSet1);

     printf("\nDIFFERENCE SETS\n");
    SET *newSet2 = differenceSet(*mySet, *yourSet);
    displayBits(*newSet2);
    

    if (isSubset(*mySet, *yourSet)) {
        printf("it is a subset! yey!");
    } else {
        printf("Aint a subset bitch!");
    }
    return 0;
}


SET *initSet() {
    // Purpose: Allocate memory for a new set and initialize all bits to 0.
     SET* mySet = malloc(sizeof(SET)); // ! i chose to malloc the set, so it will point to a storage
    for(int i = 0; i < MAX; i++) {
        (*mySet)[i] = 0;
    }
    return mySet;
}

void displayBits(SET A) {
    // Purpose: Display all bits (0s and 1s) of the set for visualization.
    for(int i = 0; i < MAX; i++) {
        printf("%d", A[i]);
        
    }
    printf("\n");
}

void displayElems(SET A) {
    // Purpose: Display only the elements that are present in the set (where bit = 1).
    
    for(int i = 0; i < MAX; i++) {
        
        if (A[i] == 1) {
        printf("%d", i);
        } else {
            printf("0");
        }
    }
    printf("\n");
}

void insertBit(SET *A, int pos) {
    // Purpose: Insert an element into the set by setting bit at position `pos` to 1.
    if (pos < MAX && pos >=0) {
        if ((*A)[pos] ==0) {
            (*A)[pos] = 1; // * it is essential to dereferenc A, for us to access the Actual set A
        }
    }
}

void deleteBit(SET *A, int pos) {
    // Purpose: Remove an element from the set by setting bit at position `pos` to 0.
    if (pos >= 0 && pos < MAX) {
        if ((*A)[pos] == 1) {
            (*A)[pos] = 0;
        }
    }
}

SET *unionSet(SET A, SET B) {
    // Purpose: Return a new set that is the union of sets A and B (elements in A OR B).
    SET*  newSet = initSet();

    for(int i = 0; i < MAX ; i++) {
        int a = A[i];
        int b = B[i];

        (*newSet)[i] = a | b;
    }
    return newSet;
}

SET *intersectionSet(SET A, SET B) {
    // Purpose: Return a new set that is the intersection of sets A and B (elements in both A AND B).
    SET *newSet = initSet();

    for(int i = 0; i < MAX; i++) {
        int a = A[i];
        int b = B[i];

        (*newSet)[i] = a & b;
    }
    return newSet;
}

SET *differenceSet(SET A, SET B) {
    // Purpose: Return a new set that contains elements in A but not in B.
    SET *newSet = initSet();
    for(int i = 0; i < MAX; i++) {
        int a = A[i];
        int b = B[i];

        (*newSet)[i] = a & (~b);
    }

    return newSet;
}

Boolean isMember(SET A, int pos) {
    // Purpose: Check if an element exists in the set (if bit at position `pos` is 1).
    if (pos>0 ||  pos < MAX) {
        return A[pos] ? 0 : 1;

    }
}

Boolean isSubset(SET A, SET B) {
    // Purpose: Determine if set A is a subset of set B (if all elements of A are in B).
    for(int i = 0; i < MAX; i++) {
        if (A[i] == 1 && B[i] == 0) {
            return 0;
        }
    }
    return 1;
}

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 10
// === STRUCT DEFINITION ===
typedef struct {
    bool *arr;   // Pointer to boolean array
    int size;    // Size of the array
} BoolArray;


// === FUNCTION DECLARATIONS ===
void initArray(BoolArray *set, int size);
void setBit(BoolArray *set, int index);
void removeBit(BoolArray *set, int index);
bool isMember(BoolArray *set, int index);
void makeNULL(BoolArray *set);
BoolArray unionSets(BoolArray *set1, BoolArray *set2);
BoolArray differenceSets(BoolArray *set1, BoolArray *set2);
BoolArray intersectSets(BoolArray *set1, BoolArray *set2);
BoolArray asymmetricDifferenceSets(BoolArray *set1, BoolArray *set2);
bool isSubset(BoolArray *set1, BoolArray *set2);
bool isEqual(BoolArray *set1, BoolArray *set2);
int findMin(BoolArray *set);
int findMax(BoolArray *set);


void display(BoolArray *set) {

    for(int i = 0; i < MAX; i++) {
        if (set->arr[i] == 1) {
        printf("%d ", i );
    }
}
}
int main() {
    BoolArray setA, setB, U, D, I, AD;

    // Initialize
    initArray(&setA, 10);
    initArray(&setB, 10);

    // Fill Set A: {2, 4, 7}
    setBit(&setA, 2);
    setBit(&setA, 4);
    setBit(&setA, 7);

    // Fill Set B: {4, 6, 8}
    setBit(&setB, 4);
    setBit(&setB, 6);
    setBit(&setB, 8);

    printf("\n--- SET CONTENTS ---\n");
    printf("Set A: ");
    for (int i = 0; i < 10; i++) if (setA.arr[i]) printf("%d ", i);
    printf("\nSet B: ");
    for (int i = 0; i < 10; i++) if (setB.arr[i]) printf("%d ", i);
    printf("\n");

    // === OPERATIONS ===
    printf("\n--- UNION ---\n");
    U = unionSets(&setA, &setB);
    printf("A union B = "); display(&U);
   

    printf("\n--- DIFFERENCE ---\n");
    D = differenceSets(&setA, &setB);
    printf("A & B = "); display(&D);

    printf("\n--- INTERSECTION ---\n");
    I = intersectSets(&setA, &setB);
    printf("A ∩ B = "); display(&I);

    printf("\n--- ASYMMETRIC DIFFERENCE ---\n");
    AD = asymmetricDifferenceSets(&setA, &setB);
    printf("AsymDiff (A not in B) = "); display(&AD);

    printf("\n--- SUBSET & EQUALITY ---\n");
    printf("Is A subset of B? %s\n", isSubset(&setA, &setB) ? "TRUE" : "FALSE");
    printf("Are A and B equal? %s\n", isEqual(&setA, &setB) ? "TRUE" : "FALSE");

    printf("\n--- MIN & MAX ---\n");
    printf("Min of A: %d\n", findMin(&setA));
    printf("Max of A: %d\n", findMax(&setA));
    printf("Min of B: %d\n", findMin(&setB));
    printf("Max of B: %d\n", findMax(&setB));

    printf("\n--- REMOVE TEST ---\n");
    removeBit(&setA, 4);
    printf("After removing 4 from A: ");
    for (int i = 0; i < 10; i++) if (setA.arr[i]) printf("%d ", i);
    printf("\n");

    printf("\n--- makeNULL TEST ---\n");
    makeNULL(&setB);
    printf("After makeNULL on B: ");
    for (int i = 0; i < 10; i++) if (setB.arr[i]) printf("%d ", i);
    printf("[should be empty]\n");

    return 0;
}



// === FUNCTION DEFINITIONS ===
// Implement these yourself ↓↓↓

void initArray(BoolArray *set, int size) {
    // TODO: Allocate memory for 'arr' and initialize elements to 0
    set->arr = malloc(size * sizeof(bool));

    for(int i = 0; i < MAX; i++) {
        set->arr[i] = false;
    }
    set->size = 0;
    

}

void setBit(BoolArray *set, int index) {
    // TODO: Mark index as member of the set

    if (index >= 0 && index < MAX) {
        set->arr[index]  = 1;
    }
    set->size++;
}

void removeBit(BoolArray *set, int index) {
    // TODO: Remove index from the set

    if (index >= 0 && index < MAX) {
        set->arr[index] = 0;
    }
    set->size--;
}

bool isMember(BoolArray *set, int index) {
    // TODO: Return true if index is present

    if (index>=0 && index < MAX) 
         return set->arr[index] ? 1 : 0;
    
    
}

void makeNULL(BoolArray *set) {
    // TODO: Reset all bits to 0 and clear size if needed
    for(int i = 0; i < MAX; i++) {
        set->arr[i] = 0;

    }
}

BoolArray unionSets(BoolArray *set1, BoolArray *set2) {
    // TODO: Return union of two sets
    BoolArray result;
    
    initArray(&result, MAX);

    for(int i = 0; i < MAX; i++) {
        int a = set1->arr[i];
        int b = set2->arr[i];


        result.arr[i] = a | b;
    }


    return result;
}

BoolArray differenceSets(BoolArray *set1, BoolArray *set2) {
    // TODO: Return difference (A - B)
    BoolArray result;
   
    initArray(&result, MAX);

    for(int i = 0; i < MAX; i++) {
        int a = set1->arr[i];
        int b = set2->arr[i];
       

        result.arr[i] = a & ~b ;
    }
    return result;
}

BoolArray intersectSets(BoolArray *set1, BoolArray *set2) {
    // TODO: Return intersection of sets
    BoolArray result;
  
    initArray(&result, MAX);


    for(int i  = 0; i < MAX; i++) {
        
        int a = set1->arr[i];
        int b = set2->arr[i];

        result.arr[i] = a & b;
    }
    return result;
}

BoolArray asymmetricDifferenceSets(BoolArray *set1, BoolArray *set2) {
    // TODO: Return elements in A not in B
    BoolArray result;

    initArray(&result, MAX);


    for(int i  = 0; i < MAX; i++) {
        
        int a = set1->arr[i];
        int b = set2->arr[i];


        
        result.arr[i] = a & !b;
    }


    return result;

}



bool isSubset(BoolArray *set1, BoolArray *set2) {
    // TODO: Return true if set1 ⊆ set2

    if (set1->size > set2->size) {
        return false;
    }

    int size = (set1->size> set2->size) ? set1->size : set2->size;


    for(int i = 0; i < size; i++) {
        if (set1->arr[i] != set2->arr[i]) {
            return false;
        }

    }
        return true;
    
    
}

bool isEqual(BoolArray *set1, BoolArray *set2) {
    // TODO: Return true if both sets are equal
    if (set1->size != set2->size) {
    return false;
}

   int size = (set1->size> set2->size) ? set1->size : set2->size;


    for(int i = 0; i < size;i++ ) {
        if (set1->arr[i] != set2->arr[i]) {
            return false;
        }
    }


    return true;

}

int findMin(BoolArray *set) {
    

    for(int i = 0; i < MAX; i++) {
        if (set->arr[i] == 1) {
            return i;
            break;
        }
    }
    return -1;
}

int findMax(BoolArray *set) {
    // TODO: Find the largest index with value 1

    for(int i = MAX-1;  i >=0; i--) {
        if (set->arr[i] == 1) 
            return i;
        
    }
    return -1;
}


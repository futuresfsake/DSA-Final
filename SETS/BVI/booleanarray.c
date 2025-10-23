#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent a Boolean array
typedef struct {
    bool *arr;      // Pointer to the array
    int size;       // Size of the array
} BoolArray;

// Function prototypes
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


int main() {
    // Create two sets
    BoolArray set1, set2;
    initArray(&set1, 10);
    initArray(&set2, 8);

    // Test the functions by manipulating the sets
    setBit(&set1, 2);
    setBit(&set1, 0);
    setBit(&set1, 7);
    setBit(&set1, 9);
    setBit(&set1, 4);
    setBit(&set1, 1);
    

    setBit(&set2, 3);
    setBit(&set2, 4);
    setBit(&set2, 3);
    setBit(&set2, 2);
    setBit(&set1, 5);
    
    
    

    // Test equality of the sets
    printf("Set 1 and Set 2 are equal: %d\n", isEqual(&set1, &set2));

    // Test union operation
    BoolArray unionResult = unionSets(&set1, &set2);
    printf("Union of Set 1 and Set 2: ");
    for (int i = 0; i < unionResult.size; i++) {
        printf("%d ", unionResult.arr[i]);
    }
    printf("\n");

    // Test difference operation
    BoolArray diffResult = differenceSets(&set1, &set2);
    printf("Difference of Set 1 and Set 2: ");
    for (int i = 0; i < diffResult.size; i++) {
        printf("%d ", diffResult.arr[i]);
    }
    printf("\n");

    // Test intersection operation
    BoolArray intersectResult = intersectSets(&set1, &set2);
    printf("Intersection of Set 1 and Set 2: ");
    for (int i = 0; i < intersectResult.size; i++) {
        printf("%d ", intersectResult.arr[i]);
    }
    printf("\n");

    // Test asymmetric difference operation
    BoolArray asymDiffResult = asymmetricDifferenceSets(&set1, &set2);
    printf("Asymmetric Difference of Set 1 and Set 2: ");
    for (int i = 0; i < asymDiffResult.size; i++) {
        printf("%d ", asymDiffResult.arr[i]);
    }
    printf("\n");

    // Test subset check
    printf("Set 1 is a subset of Set 2: %d\n", isSubset(&set1, &set2));

    // Test finding the minimum and maximum
    printf("Min index in Set 1: %d\n", findMin(&set1));
    printf("Max index in Set 1: %d\n", findMax(&set1));

    // Clean up
  
    return 0;
}



void initArray(BoolArray *set, int size) {
    set->arr = malloc(size* sizeof(bool));
    set->size = size;
    for(int i = 0; i < set->size; i++) {
        set->arr[i] = 0;
    }
    
 
}


void setBit(BoolArray *set, int index) {

   
    if (index>=0 && index < set->size) {
        set->arr[index] = 1;
    
    }
}

void removeBit(BoolArray *set, int index) {
    if (index >= 0 && index <  set->size) {
        set->arr[index] = 0;
    }
}


bool isMember(BoolArray *set, int index) {

    if (index >0 && index < set->size) {
    return set->arr[index];
    }
}

void makeNULL(BoolArray *set) {
    for(int i = 0; i < set->size; i++) {
        set->arr[i] =0;
        
    }
    set->size = 0;
}


BoolArray unionSets(BoolArray *set1, BoolArray *set2) {
    int max = (set1->size > set2->size) ? set1->size : set2->size;
    BoolArray newSet;
    initArray(&newSet, max);

    for(int i = 0; i < max; i++) {
        int a = set1->arr[i];
        int b = set2->arr[i];

        newSet.arr[i] = a | b;
    }
    return newSet;
}


BoolArray differenceSets(BoolArray *set1, BoolArray *set2) {
    int max = (set1->size > set2->size) ? set1->size : set2->size;
    BoolArray newSet;
    initArray(&newSet, max);

    for(int i = 0; i < max; i++) {
        int a = set1->arr[i];
        int b = set2->arr[i];

        newSet.arr[i] = a & (~b);
    }
    return newSet;
}


BoolArray intersectSets(BoolArray *set1, BoolArray *set2) {
    int max = (set1->size > set2->size) ? set1->size : set2->size;
    BoolArray newSet;
    initArray(&newSet, max);

    for(int i = 0; i < max ; i++) {
        int a = set1->arr[i];
        int b = set2->arr[i];
        
        newSet.arr[i] = a & b;
    }
    return newSet;    
}

BoolArray asymmetricDifferenceSets(BoolArray *set1, BoolArray *set2) {
    int max = (set1->size > set2->size) ? set1->size : set2->size;
    BoolArray newSet;
    initArray(&newSet, max);

    for(int i = 0; i < max; i++) {
        int a = set1->arr[i];
        int b = set2->arr[i];

        if (a == 1 && b ==0) {


        newSet.arr[i] = a;
        }
    }

    return newSet;
}


bool isSubset(BoolArray *set1, BoolArray *set2) {

    if (set2->size<set1->size) {
        return false;
    }

    int max = (set1->size > set2->size) ? set1->size : set2->size;

    for(int i = 0; i < max; i++) {
        if (set1->arr[i] != set2->arr[i]) {
            return false;
        }
        
    }
    return true;
}


bool isEqual(BoolArray *set1, BoolArray *set2) {
    if (set1->size != set2->size) {
        return false;
    }

    for(int i = 0; i < set1->size; i++) {
        if (set1->arr[i] != set2->arr[i]) {
            return false;
        }
    }

    return true;
}


int findMin(BoolArray *set) {
    for(int i = 0; i < set->size; i++) {
        if (set->arr[i] == 1) {
            return i;
        }
    }
}


int findMax(BoolArray *set) {
    for(int i = set->size -1; i > 0; i--) {
        if (set->arr[i] ==1) {
            return i;
        }
    }
}
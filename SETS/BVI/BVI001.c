#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10  // universe size (0..9)

// Structure to represent a Boolean array
typedef struct {
    bool arr[SIZE];
    int size;
} BoolArray;

// Function declarations
void initArray(BoolArray *set);
void setBit(BoolArray *set, int index);
void removeBit(BoolArray *set, int index);
bool isMember(BoolArray *set, int index);
void displaySet(BoolArray *set);
BoolArray unionSets(BoolArray *set1, BoolArray *set2);
BoolArray intersectSets(BoolArray *set1, BoolArray *set2);
BoolArray differenceSets(BoolArray *set1, BoolArray *set2);
BoolArray symmetricDiffSets(BoolArray *set1, BoolArray *set2);
bool isSubset(BoolArray *set1, BoolArray *set2);
int findMin(BoolArray *set);
int findMax(BoolArray *set);

int main() {
    BoolArray A, B;
    initArray(&A);
    initArray(&B);

    // Build sets with literal indices
    setBit(&A, 0);
    setBit(&A, 2);
    setBit(&A, 4);
    setBit(&A, 7);

    setBit(&B, 1);
    setBit(&B, 2);
    setBit(&B, 4);
    setBit(&B, 5);

    printf("Set A: "); displaySet(&A);
    printf("Set B: "); displaySet(&B);

    BoolArray U = unionSets(&A, &B);
    printf("A ∪ B: "); displaySet(&U);

    BoolArray I = intersectSets(&A, &B);
    printf("A ∩ B: "); displaySet(&I);

    BoolArray D = differenceSets(&A, &B);
    printf("A \\ B: "); displaySet(&D);

    BoolArray S = symmetricDiffSets(&A, &B);
    printf("A △ B: "); displaySet(&S);

    printf("Is A subset of B? %s\n", isSubset(&A, &B) ? "Yes" : "No");
    printf("Min index in A: %d\n", findMin(&A));
    printf("Max index in A: %d\n", findMax(&A));

    return 0;
}

void initArray(BoolArray *set) {
    set->size = 0;
    for(int i = 0; i < SIZE;i++) {
        set->arr[i] = false;
    }
}

void setBit(BoolArray *set, int index) {
    if (index >= SIZE || index < 0) return; // fix: use >=, not >

    if (!set->arr[index]) { // increment size only if bit was 0
        set->arr[index] = true;
        set->size++;
    }
}

void removeBit(BoolArray *set, int index) {
    if (index >= SIZE || index < 0) return; // fix: use >=, not >
    
    if (set->arr[index]) { // decrement size only if bit was 1
        set->arr[index] = false;
        set->size--;
    }
}


bool isMember(BoolArray *set, int index) {
    if (index < 0 || index >= SIZE) return false; // bounds check
    return set->arr[index];
}

void displaySet(BoolArray *set) {
    printf("{");
    for(int i = 0; i < SIZE;i++) {
        if (set->arr[i]) {
        printf("%d ", i);
    }
}
printf("}\n");
}


BoolArray unionSets(BoolArray *set1, BoolArray *set2) {

    BoolArray C;
    initArray(&C);
    for(int i = 0; i < SIZE; i++) {
        C.arr[i] = set1->arr[i] | set2->arr[i];

    }
    return C;
}

BoolArray intersectSets(BoolArray *set1, BoolArray *set2) {
    BoolArray C;
    initArray(&C);

    for(int i = 0; i < SIZE; i++) {
        C.arr[i] = set1->arr[i] & set2->arr[i];
    }
    return C;
}

BoolArray differenceSets(BoolArray *set1, BoolArray *set2) {
    BoolArray C;
    initArray(&C);
    for(int i =0; i < SIZE; i++) {

        int a = set1->arr[i];
        int b = set2->arr[i];
        C.arr[i] =  a & (~b);
    }
    return C;
}

BoolArray symmetricDiffSets(BoolArray *set1, BoolArray *set2) {
    BoolArray C;
    initArray(&C);
    for(int i = 0; i < SIZE; i++) {
        C.arr[i] = set1->arr[i] ^ set2->arr[i]; // symmetric difference = XOR
    }
    return C;
}
bool isSubset(BoolArray *set1, BoolArray *set2) {
    for(int i =0; i < SIZE; i++ ) {
        if (set1->arr[i] && !set2->arr[i]) {
            return false;
        }
    }
    return true;
}
int findMin(BoolArray *set) {
    for(int i = 0; i < SIZE; i++) {
        if (set->arr[i] == 1) {
            return i;
        }
    }
    return -1;
}
int findMax(BoolArray *set) {
    for(int i = SIZE-1; i>=0 ; i--) {
        if (set->arr[i] == 1) {
            return i;
        }
    }
    return -1;
}


/* ======= Fixes/Improvements =======
1. Corrected boundary checks in setBit/removeBit (use >=, not >)
2. Increment/decrement size only when actual change occurs
3. Added bounds check in isMember
4. Fixed symmetric difference using XOR instead of old logic
5. isSubset now correctly checks only 1-bits in set1
6. findMax corrected to start from SIZE-1
*/
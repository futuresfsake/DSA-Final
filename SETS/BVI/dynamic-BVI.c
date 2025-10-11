#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    unsigned int *data;  // packed bits
    int size;            // number of words allocated
    int capacity;        // total number of bits
} BitSet;

// === Basic BitSet Functions ===
BitSet* createSet(int numBits);
void freeSet(BitSet *s);
void insert(BitSet *s, int x);
void delete(BitSet *s, int x);
bool isMember(BitSet *s, int x);
void resizeSet(BitSet *s, int newSize);
void printSet(BitSet *s);

// === Set Operations ===
BitSet* unionSet(BitSet *a, BitSet *b);
BitSet* intersectSet(BitSet *a, BitSet *b);
BitSet* differenceSet(BitSet *a, BitSet *b);
BitSet* symmetricDiffSet(BitSet *a, BitSet *b);
bool isSubset(BitSet *a, BitSet *b);
bool isEqual(BitSet *a, BitSet *b);
int findMin(BitSet *s);
int findMax(BitSet *s);

// === Main Function to Test ===
int main() {
    BitSet *A = createSet(20);
    BitSet *B = createSet(20);

    insert(A, 2);
    insert(A, 5);
    insert(A, 10);

    insert(B, 5);
    insert(B, 7);
    insert(B, 15);

    printf("Set A: ");
    printSet(A);
    printf("Set B: ");
    printSet(B);

    BitSet *U = unionSet(A, B);
    printf("A ∪ B: ");
    printSet(U);

    BitSet *I = intersectSet(A, B);
    printf("A ∩ B: ");
    printSet(I);

    BitSet *D = differenceSet(A, B);
    printf("A − B: ");
    printSet(D);

    BitSet *S = symmetricDiffSet(A, B);
    printf("A Δ B: ");
    printSet(S);

    printf("Is A subset of B? %d\n", isSubset(A, B));
    printf("Are A and B equal? %d\n", isEqual(A, B));

    printf("Min of A: %d\n", findMin(A));
    printf("Max of A: %d\n", findMax(A));

    freeSet(A);
    freeSet(B);
    freeSet(U);
    freeSet(I);
    freeSet(D);
    freeSet(S);

    return 0;
}

#include <stdio.h>
#include <stdbool.h>

typedef unsigned char Set;
#define MAX_BITS 8

// Initialize set
void initialize(Set *s) {
    *s = 0;

}

// Insert element
void insert(Set *s, int element) {
    if (element > MAX_BITS || element < 0) return;

    *s |= (1U << element);

}

// Delete element
void deleteElem(Set *s, int element) {
    if (element > MAX_BITS || element < 0) return;
    *s &= ~(1U << element);

}

// Find element
bool find(Set s, int element) {
    if (element > MAX_BITS || element < 0) return false;

    return (((s>>element)& 1U)!= 0);
}

// Union
Set unionSet(Set A, Set B) {
    return A |B;
}

// Intersection
Set intersectionSet(Set A, Set B) {
    return A & B;
}

// Difference
Set differenceSet(Set A, Set B) {
    return A &(~B);
}

// Check if A is subset of B
bool isSubset(Set A, Set B) {
    return ((A & (~B)) == 0);
}

// Display elements
void display(Set s) {

    printf("{");
    int first = 1;
    for(int i = 0; i < MAX_BITS; i++) {
        if ((s>>i) &1U) {
            if (!first) printf(",");
            printf("%d", i);
            first = 0;
        }

    }
    printf("}");

}

// Print binary
void printBinary(Set s) {
    printf(" (");

    for(int i = MAX_BITS -1; i >=0; i--) {
        printf("%d", ((s>>i) & 1U)? 1 : 0);
    }

    printf(")\n");
}



int main() {
    Set A, B, C;

    printf("===== TWO-SET BIT VECTOR PROBLEM =====\n\n");

    // Initialize both sets
    initialize(&A);
    initialize(&B);

    // Set A = {1, 3, 5}
    insert(&A, 1);
    insert(&A, 3);
    insert(&A, 5);

    // Set B = {3, 4, 5, 6}
    insert(&B, 3);
    insert(&B, 4);
    insert(&B, 5);
    insert(&B, 6);

    printf("Set A = "); display(A); printf("\n");
    printf("Set B = "); display(B); printf("\n\n");

    // Union
    C = unionSet(A, B);
    printf("A ∪ B = "); display(C); printBinary(C); printf("\n");

    // Intersection
    C = intersectionSet(A, B);
    printf("A ∩ B = "); display(C); printBinary(C); printf("\n");

    // Difference
    C = differenceSet(A, B);
    printf("A − B = "); display(C); printBinary(C);("\n\n");

    // Subset check
    if (isSubset(A, B))
        printf("A is a subset of B\n");
    else
        printf("A is NOT a subset of B\n");

    printf("\n===== END OF PROGRAM =====\n");
    return 0;
}

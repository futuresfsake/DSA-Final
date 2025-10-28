#include <stdio.h>
#include <stdbool.h>

typedef unsigned char Set;   // bit-vector (8 bits)
#define MAX_BITS 8

// Initialize set
void initialize(Set *s) {
    *s = 0;

}

// Insert element
void insert(Set *s, int element) {

    *s |= (1U<<element);

}

// Delete element
void deleteElem(Set *s, int element) {
    *s &= ~(1U << element);

}

// Find element
bool find(Set s, int element) {
    return ((s >> element) & 1U) !=0;
}

// Union
Set unionSet(Set A, Set B) {
    return A | B;
}

// Intersection
Set intersectionSet(Set A, Set B) {
    return A & B;
}

// Difference
Set differenceSet(Set A, Set B) {
    return A & (~B);
}

// Display elements
void display(Set s) {
    
    printf("{");
    int first = 1;
    for (int i = 0; i < MAX_BITS; i++) {
        if ((s >> i) & 1U) {
            if (!first) printf(",");
            printf("%d ", i); 
            
            first = 0; // just print the index if bit = 1
        }
        
    }
    printf("}");
}

// Print binary representation
void printBinary(Set s) {
    printf("(");
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        printf("%d", (((s >> i) & 1U) ? 1 : 0));
    }
    printf(")");
}

int main() {
    Set A, B, C;

    printf("===== BIT VECTOR SET TEST =====\n\n");

    // 1️⃣ Initialize both sets
    initialize(&A);
    initialize(&B);

    printf("After initialize:\n");
    printf("A = 0 (00000000) {}\n");
    printf("B = 0 (00000000) {}\n\n");

    // 2️⃣ Insert elements into A
    insert(&A, 1);
    printf("insert(&A, 1);\n");
    printf("Expected: A = 2 (00000010) {1}\n\n");

    insert(&A, 6);
    printf("insert(&A, 6);\n");
    printf("Expected: A = 66 (01000010) {1, 6}\n\n");

    // 3️⃣ Delete elements from A
    deleteElem(&A, 6);
    printf("deleteElem(&A, 6);\n");
    printf("Expected: A = 2 (00000010) {1}\n\n");

    deleteElem(&A, 1);
    printf("deleteElem(&A, 1);\n");
    printf("Expected: A = 0 (00000000) {}\n\n");

    // 4️⃣ Insert into B
    insert(&B, 3);
    insert(&B, 6);
    insert(&B, 7);
    printf("After inserting into B:\n");
    printf("Expected: B = 200 (11001000) {3, 6, 7}\n\n");

    // 5️⃣ Re-insert into A
    insert(&A, 1);
    insert(&A, 6);
    printf("Re-insert A:\n");
    printf("Expected: A = 66 (01000010) {1, 6}\n\n");

    // 6️⃣ UNION
    C = unionSet(A, B);
    printf("Union = A ∪ B\n");
    printf("Expected: C = 202 (11001010) {1, 3, 6, 7}\n\n");

    // 7️⃣ INTERSECTION
    C = intersectionSet(A, B);
    printf("Intersection = A ∩ B\n");
    printf("Expected: C = 64 (01000000) {6}\n\n");

    // 8️⃣ DIFFERENCE
    C = differenceSet(A, B);
    printf("Difference = A - B\n");
    printf("Expected: C = 2 (00000010) {1}\n\n");

    // 9️⃣ FIND
    printf("find(A, 1) -> Expected: true (1)\n");
    printf("find(A, 5) -> Expected: false (0)\n\n");

    // 🔟 Display
    printf("Display sets using display():\n");
    printf("A = "); display(A); printf("\n");
    printf("B = "); display(B); printf("\n");
    printf("C = "); display(C); printf("\n\n");

    // 11️⃣ Binary display
    printf("Binary forms:\n");
    printf("A = "); printBinary(A); printf("\n");
    printf("B = "); printBinary(B); printf("\n");
    printf("C = "); printBinary(C); printf("\n");

    printf("\n===== END OF TEST =====\n");
    return 0;
}


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define COMPUTER_WORD_SIZE 32  // Set the size of the computer word (e.g., 32-bit word)

// Structure for representing a Computer Word (Bit Vector)
typedef struct {
    unsigned int bits;  // Use an unsigned int to store the bits
} ComputerWord;

// Function prototypes for operations
void setBit(ComputerWord *cw, int pos, bool value);  // Set bit at position `pos` to `value`
bool isMember(ComputerWord *cw, int pos);             // Check if bit at position `pos` is set
bool getBit(ComputerWord *cw, int pos);               // Get bit at position `pos`
void deleteBit(ComputerWord *cw, int pos);            // Delete (clear) the bit at position `pos`
bool isEqual(ComputerWord *cw1, ComputerWord *cw2);    // Check if two computer words are equal
int count1s(ComputerWord *cw);                        // Count number of 1 bits
int convertInt(ComputerWord *cw);                     // Convert ComputerWord to an integer
ComputerWord unionCW(ComputerWord *cw1, ComputerWord *cw2);   // Union of two ComputerWords
ComputerWord differenceCW(ComputerWord *cw1, ComputerWord *cw2); // Difference of two ComputerWords (cw1 - cw2)
ComputerWord intersectCW(ComputerWord *cw1, ComputerWord *cw2); // Intersection of two ComputerWords

// Function to print a ComputerWord
void printComputerWord(ComputerWord *cw);

int main() {
    ComputerWord cw1 = {0};  // Initially all bits are 0
    ComputerWord cw2 = {0};  // Initially all bits are 0
    ComputerWord result;     // For storing operation results

    // === INSERT ELEMENTS ===
    printf("Setting bits in cw1 and cw2...\n");
    setBit(&cw1, 1, true);
    setBit(&cw1, 3, true);
    setBit(&cw1, 5, true);

    setBit(&cw2, 3, true);
    setBit(&cw2, 4, true);
    setBit(&cw2, 6, true);

    // === DISPLAY INITIAL VALUES ===
    printf("cw1 bits: ");
    printComputerWord(&cw1);
    printf("cw2 bits: ");
    printComputerWord(&cw2);
    printf("\n");

    // === UNION ===
    result = unionCW(&cw1, &cw2);
    printf("Union (cw1 ∪ cw2): ");
    printComputerWord(&result);

    // === INTERSECTION ===
    result = intersectCW(&cw1, &cw2);
    printf("Intersection (cw1 ∩ cw2): ");
    printComputerWord(&result);

    // === DIFFERENCE ===
    result = differenceCW(&cw1, &cw2);
    printf("Difference (cw1 - cw2): ");
    printComputerWord(&result);
    printf("\n");

    // === MEMBERSHIP TEST ===
    int checkPos = 3;
    printf("Is bit %d set in cw1? %s\n", checkPos, isMember(&cw1, checkPos) ? "Yes" : "No");
    printf("Is bit %d set in cw2? %s\n", checkPos, isMember(&cw2, checkPos) ? "Yes" : "No");
    printf("\n");

    // === COUNT ===
    printf("Number of 1s in cw1: %d\n", count1s(&cw1));
    printf("Number of 1s in cw2: %d\n", count1s(&cw2));
    printf("\n");

    // === DELETE BIT ===
    printf("Deleting bit 3 from cw1...\n");
    deleteBit(&cw1, 3);
    printf("cw1 after deletion: ");
    printComputerWord(&cw1);
    printf("\n");

    // === EQUALITY TEST ===
    printf("cw1 == cw2 ? %s\n", isEqual(&cw1, &cw2) ? "Yes" : "No");
    printf("\n");

    // === INTEGER CONVERSION ===
    printf("cw1 as integer: %d\n", convertInt(&cw1));
    printf("cw2 as integer: %d\n", convertInt(&cw2));

    return 0;
}


// --- Implement the functions below ---

// Set the bit at position `pos` to `value` (true or false)
void setBit(ComputerWord *cw, int pos, bool value) {
    
  
    if (value) {
        cw->bits |= (1U<<pos);
    } else {
        cw->bits &= ~(1U<<pos);
    }
}

// Check if the bit at position `pos` is set (i.e., is 1)
bool isMember(ComputerWord *cw, int pos) {
    
   return ((cw->bits & (1U<<pos)) != 0);
}

// Get the bit at position `pos`
bool getBit(ComputerWord *cw, int pos) {
    return ((cw->bits & (1U<<pos)) != 0);
}

// Delete (clear) the bit at position `pos`
void deleteBit(ComputerWord *cw, int pos) {
    
    cw->bits &= ~(1U<<pos);
}

// Check if two ComputerWords are equal
bool isEqual(ComputerWord *cw1, ComputerWord *cw2) {
    return cw1->bits == cw2->bits;
}

// Count the number of 1s in the ComputerWord
int count1s(ComputerWord *cw) {
    
    unsigned int count = 0;
    unsigned int bitss = cw->bits;

    while (bitss) {
        count+=(bitss & 1U);
        bitss>>=1;

    }
    return count;
}

// Convert the ComputerWord to an integer
int convertInt(ComputerWord *cw) {
    // Implement this
    return cw->bits;
}

// Perform the union (OR) of two ComputerWords
ComputerWord unionCW(ComputerWord *cw1, ComputerWord *cw2) {
    // Implement this
    ComputerWord new;
    new.bits = cw1->bits | cw2->bits;
    return new;
}

// Perform the difference (AND NOT) of two ComputerWords (cw1 - cw2)
ComputerWord differenceCW(ComputerWord *cw1, ComputerWord *cw2) {
    // Implement this
    ComputerWord result = {0};

    result.bits = cw1->bits & ~(cw2->bits);
    return result;
}

// Perform the intersection (AND) of two ComputerWords
ComputerWord intersectCW(ComputerWord *cw1, ComputerWord *cw2) {
    // Implement this
    ComputerWord result = {0};
    result.bits = cw1->bits & cw2->bits;
    return result;
}

// Print the ComputerWord as a binary string
void printComputerWord(ComputerWord *cw) {
    // Implement this
    for (int i = COMPUTER_WORD_SIZE - 1; i >= 0; i--) {
        printf("%d", (cw->bits & (1U << i)) ? 1 : 0);
    }
    printf("\n");
}

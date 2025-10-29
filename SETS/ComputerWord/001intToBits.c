/************************************************************
 🧠 BIT VECTOR ↔ BOOLEAN ARRAY CONVERSION (BOILERPLATE)
*************************************************************
📘 CONTEXT:
Convert between a compact bit vector (unsigned int)
and a boolean array representation.

Implement the following functions:
    - intToBoolArray()
    - boolArrayToInt()
    - printBoolArray()
************************************************************/

#include <stdio.h>
#include <stdbool.h>

#define NUM_BITS 8  // You can change this to 16 or 32
int count = 0;

// === Function Declarations ===
void intToBoolArray(unsigned int num, bool bits[NUM_BITS]) {
    for(int i = 0; i < 8; i++) {
        bits[i] = ((num>>i) &1U);
        if (bits[i] == 1) {
            count++;
        }
        
    }

}
unsigned int boolArrayToInt(bool bits[NUM_BITS]) {
    unsigned int bitss = 0;
    
    for(int i = 0; i < 8; i++) {
        if (bits[i] == 1) {
        bitss|= (1U << i) ;
    } 
}
return bitss;
}
void printBoolArray(bool bits[NUM_BITS]) {
    for(int i = 9; i >= 0; i--) {
        printf("%d ", bits[i]);
    }
}

// === Main Demo ===
int main() {
    unsigned int number = 13; // Binary: 00001101
    bool bits[NUM_BITS];

    printf("Original number: %u\n", number);

    intToBoolArray(number, bits);
    printBoolArray(bits);

    // Example modification
    bits[2] = !bits[2];

    unsigned int reconstructed = boolArrayToInt(bits);
    printf("Reconstructed number: %u\n", reconstructed);

    return 0;
}

// === Function Definitions (implement below) ===

#include <stdio.h>
#include <limits.h>  // For CHAR_BIT (number of bits per byte)

// This program converts an integer to its bit (binary) representation
// and counts how many bits are 1 and how many are 0.
int main() {
    unsigned int num;  // Use unsigned so shifting is well-defined
    printf("Enter an integer: ");
    scanf("%u", &num);

    int totalBits = sizeof(num) * CHAR_BIT;  // usually 32 bits on most systems
    int countOnes = 0;   // counter for 1 bits
    int countZeros = 0;  // counter for 0 bits

    printf("\nBinary representation: ");

    // Loop from most significant bit (leftmost) to least (rightmost)
    for (int i = totalBits - 1; i >= 0; i--) {
        // Extract the bit at position i using shift and mask
        unsigned int bit = (num >> i) & 1;

        // Print each bit (either 0 or 1)
        printf("%u", bit);

        // Count the bit
        if (bit == 1)
            countOnes++;
        else
            countZeros++;

        // Optional: add a space every 8 bits for readability
        if (i % 8 == 0)
            printf(" ");
    }

    // Display the results
    printf("\n\nTotal bits   : %d\n", totalBits);
    printf("Number of 1s : %d\n", countOnes);
    printf("Number of 0s : %d\n", countZeros);

    return 0;
}

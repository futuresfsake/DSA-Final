#include <stdio.h>
#define MAX 10

typedef enum {FALSE, TRUE} Boolean;
typedef unsigned char SET;

void displayBits(SET A);
void displayElements(SET A);
SET insertBit(SET A, int pos);
SET deleteBit(SET A, int pos);
SET unionBit(SET A, SET B);
SET intersectionBit(SET A, SET B);
SET differenceBit(SET A, SET B);
Boolean isMember(SET A, int pos);
Boolean isASubset(SET A, SET B);

int main()
{
    SET mySet = 7;
    SET challengeSet = 80;
    displayBits(mySet);

    printf("\n");
    mySet = insertBit(mySet, 3);
    displayBits(mySet);

    printf("\n\n");
    displayElements(challengeSet);
    printf("\n");
    displayBits(challengeSet);

    printf("\n%d", isASubset(mySet, challengeSet));

    return 0;
}

/* ============================================
   FUNCTION DEFINITIONS (Empty with Purposes)
   ============================================ */

void displayBits(SET A) {
    // Purpose: Display the binary representation (bits) of the set.
}

SET insertBit(SET A, int pos) {
    // Purpose: Insert an element into the set by setting the bit at position `pos` to 1.
}

SET deleteBit(SET A, int pos) {
    // Purpose: Remove an element from the set by clearing the bit at position `pos` (set to 0).
}

SET unionBit(SET A, SET B) {
    // Purpose: Return a new set that is the union of A and B (bits set in either A or B).
}

SET intersectionBit(SET A, SET B) {
    // Purpose: Return a new set that is the intersection of A and B (bits set in both A and B).
}

SET differenceBit(SET A, SET B) {
    // Purpose: Return a new set containing elements in A but not in B.
}

Boolean isMember(SET A, int pos) {
    // Purpose: Check whether an element (bit at position `pos`) is a member of the set.
}

void displayElements(SET A) {
    // Purpose: Display all element positions (bit indices) where the bit is set to 1.
}

Boolean isASubset(SET A, SET B) {
    // Purpose: Check if set A is a subset of set B (all bits set in A are also set in B).
}

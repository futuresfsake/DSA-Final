/************************************************************
 ⚙️  BIT VECTORS – FEATURE FLAGS SYSTEM (BOILERPLATE)
*************************************************************
📘 CONTEXT:
Each bit in an unsigned int represents a **feature toggle**
(e.g., enabled/disabled).  

Implement the following:
    1️⃣ setFeature()         → Turn a feature ON or OFF
    2️⃣ checkFeature()       → Check if a feature is ON
    3️⃣ displayFeatures()    → Show all enabled features
    4️⃣ intToBoolArray()     → Convert integer to bool array
    5️⃣ boolArrayToInt()     → Convert bool array back to integer
************************************************************/

#include <stdio.h>
#include <stdbool.h>

#define NUM_FEATURES 8  // bits 0–7

// === Function Declarations ===
void setFeature(unsigned int *flags, int index, bool value);
bool checkFeature(unsigned int flags, int index);
void displayFeatures(unsigned int flags);
void intToBoolArray(unsigned int flags, bool bits[NUM_FEATURES]);
unsigned int boolArrayToInt(bool bits[NUM_FEATURES]);
int main() {
    unsigned int featureFlags = 0;   // all off
    bool bits[NUM_FEATURES];

    // Example: toggle some features
    setFeature(&featureFlags, 0, true);  // Enable feature 0
    setFeature(&featureFlags, 3, true);  // Enable feature 3
    setFeature(&featureFlags, 5, true);  // Enable feature 5

    printf("Current feature flags (as int): %u\n", featureFlags);
    displayFeatures(featureFlags);

    // Convert to boolean array
    intToBoolArray(featureFlags, bits);

    // Modify array form
    bits[2] = true;
    bits[5] = false;

    unsigned int updated = boolArrayToInt(bits);
    printf("\nAfter modification:\n");
    displayFeatures(updated);

    return 0;
}
// === Function Definitions (implement these) ===
void setFeature(unsigned int *flags, int index, bool value) {
    // TODO: Use bitwise OR / AND to toggle a feature ON or OFF

    if (value) {
        *flags|= (1U<<index);

    } else {
        *flags&= ~(1U<<index);
    }
}

bool checkFeature(unsigned int flags, int index) {
    
    return (((flags >>index) & 1U) != 0);
}

void displayFeatures(unsigned int flags) {
    printf("{");

    
    for(int i = 0; i<8; i++) {
        if (((flags>>i) & 1U) == 1) {
        printf("%d ",i);
        
        }

    }
    printf("}");
}

void intToBoolArray(unsigned int flags, bool bits[NUM_FEATURES]) {

    for(int i = 0; i < 9; i++) {
        bits[i] = (flags>>i) & 1U;
    }

}

unsigned int boolArrayToInt(bool bits[NUM_FEATURES]) {
    unsigned int b = 0;

    for(int i = 0; i < NUM_FEATURES; i++) {

        if (bits[i] == 1) {
        b |=(1U<<i);
        
        }
    }


    
    return b;
}

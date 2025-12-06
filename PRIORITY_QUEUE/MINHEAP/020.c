#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LANDERS 50
#define NAME_LEN 40

/*
    ================================================================
        CELESTIAL LANDING BAY — PRIORITY LANDING QUEUE SYSTEM
    ----------------------------------------------------------------
    Lower distressLevel = higher priority for emergency landing.

    Required Operations (all iterative):
        - requestLanding
        - clearMostCritical
        - updateDistress
        - verify_landing_protocols
    ================================================================
*/

typedef struct {
    char callSign[NAME_LEN];   // Lander name
    int distressLevel;         // Lower = more urgent
    float fuelRemaining;       // Fuel percentage
} Lander;

typedef struct {
    Lander bay[MAX_LANDERS];
    int count;
} LandingBay;


// ========================== FUNCTION DECLARATIONS ==========================

// Insert a new lander into the min-heap
void requestLanding(LandingBay *lb, Lander ln);

// Remove and return the lander with HIGHEST priority (lowest distress)
Lander clearMostCritical(LandingBay *lb);

// Update distress level of lander at index, then restore heap order
void updateDistress(LandingBay *lb, int index, int newDistress);

// Verify min-heap property (must keep your while loop style)
bool verify_landing_protocols(LandingBay *lb);


void displayLandingBay(LandingBay *lb) {
    printf("\n=== LANDING BAY STATUS (%d landers) ===\n", lb->count);

    for (int i = 0; i < lb->count; i++) {
        printf("[%d] %s | distress=%d | fuel=%.1f%%\n",
               i,
               lb->bay[i].callSign,
               lb->bay[i].distressLevel,
               lb->bay[i].fuelRemaining);
    }

    printf("=======================================\n");
}


// =============================== MAIN PROGRAM ===============================

int main() {

    LandingBay lb;
    lb.count = 0;

    // Add 4 spacecraft landers
    requestLanding(&lb, (Lander){ "Aquila-7", 5, 73.2 });
    requestLanding(&lb, (Lander){ "Nebula-3", 2, 40.1 });
    requestLanding(&lb, (Lander){ "Orion-11", 9, 22.5 });
    requestLanding(&lb, (Lander){ "Solaris-1", 4, 60.0 });


    displayLandingBay(&lb);

    printf("Protocols intact? %s\n",
        verify_landing_protocols(&lb) ? "YES" : "NO");

    // Remove highest-priority (lowest distress)
    Lander critical = clearMostCritical(&lb);
    printf("\nCleared for landing: %s\n", critical.callSign);

    displayLandingBay(&lb);

    // Update distress of a lander (index may change depending on your insert logic)
    updateDistress(&lb, 2, 1);
    displayLandingBay(&lb);

    printf("Protocols intact after update? %s\n",
        verify_landing_protocols(&lb) ? "YES" : "NO");

    return 0;
}


void requestLanding(LandingBay *lb, Lander ln) {
    
    if (lb->count == MAX_LANDERS) return;

    int child = lb->count;
    int pr = (child-1)/2;


    while (child > 0 && lb->bay[pr].distressLevel > ln.distressLevel) {
        lb->bay[child] = lb->bay[pr];
        child = pr;
        pr = (child-1)/2;
    }

    lb->bay[child] = ln;
    lb->count++;
}

// Remove and return the lander with HIGHEST priority (lowest distress)
Lander clearMostCritical(LandingBay *lb) {

    Lander emp, root;

    if (lb->count == 0) return emp;


    root = lb->bay[0];
    lb->bay[0] = lb->bay[lb->count-1];
    lb->count--;

    int pr = 0;
    int child = 2 * pr +1;

    while (child < lb->count) {
        if (child+1 < lb->count && lb->bay[child+1].distressLevel < lb->bay[child].distressLevel) {
            child++;
        }

        if (lb->bay[pr].distressLevel > lb->bay[child].distressLevel) {
            Lander swap = lb->bay[pr];
            lb->bay[pr] = lb->bay[child];
            lb->bay[child]  = swap;

            pr = child;
            child = pr * 2+1;

        } else {
            break;
        }
    }
    return root;
}

// Update distress level of lander at index, then restore heap order
void updateDistress(LandingBay *lb, int index, int newDistress) {

    lb->bay[index].distressLevel = newDistress;



    int pr = 0;
    int child = 2 * pr +1;


    while (child < lb->count) {
        if (child+1 < lb->count && lb->bay[child+1].distressLevel < lb->bay[child].distressLevel) {
            child++;
        }

        if (lb->bay[pr].distressLevel > lb->bay[child].distressLevel) {
            Lander swap = lb->bay[pr];
            lb->bay[pr] = lb->bay[child];
            lb->bay[child] = swap;

            pr = child;
            child = 2 * pr +1;
        } else {
            break;
        }
    }
}
// Verify min-heap property (must keep your while loop style)
bool verify_landing_protocols(LandingBay *lb) {
    if (lb->count == 0) return false;


    for(int i = 0; i < lb->count; i++) {
        int left = 2 * i +1;
        int right = 2 * i +2;


        if (left < lb->count && lb->bay[left].distressLevel <lb->bay[i].distressLevel) {
            return false;
        }

        if (right < lb->count && lb->bay[right].distressLevel < lb->bay[i].distressLevel) {
            return false;
        }
    }

    return true;
}

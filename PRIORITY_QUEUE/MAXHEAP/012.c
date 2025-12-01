#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CRIMINALS 30
#define ALIAS_LEN 60

/*
    ============================================================
           GALACTIC BOUNTY BOARD – DANGER PRIORITY QUEUE
    ------------------------------------------------------------
    MAX-HEAP is used: Higher bounty = higher threat
    Parent bounty >= child bounty

    Operations implemented:
        - initBoard
        - addBounty
        - captureMostDangerous
        - searchCriminal
        - updateBounty
        - displayBoard
        - sortBoard (heap sort)
    ============================================================
*/

typedef struct {
    int criminalID;
    char alias[ALIAS_LEN];
    int bountyCredits;
} BountyEntry;

typedef struct {
    BountyEntry heap[MAX_CRIMINALS];
    int count;
} BountyBoard;

// ================== FUNCTION PROTOTYPES ==================
void initBoard(BountyBoard *bb);
bool addBounty(BountyBoard *bb, BountyEntry be);
bool captureMostDangerous(BountyBoard *bb, BountyEntry *captured);
int searchCriminal(BountyBoard *bb, int criminalID);
bool updateBounty(BountyBoard *bb, int criminalID, int newBounty);
void displayBoard(BountyBoard *bb);
void sortBoard(BountyBoard *bb);

// ================== HELPER FUNCTION ==================
void heapifyDown(BountyBoard *bb, int index, int size);
void heapifyUp(BountyBoard *bb, int index);

// ================== MAIN FUNCTION ==================
int main() {
    BountyBoard bb;
    initBoard(&bb);

    addBounty(&bb, (BountyEntry){101, "Shadow Reaper", 50000});
    addBounty(&bb, (BountyEntry){102, "Nebula Phantom", 120000});
    addBounty(&bb, (BountyEntry){103, "Crimson Serpent", 75000});
    addBounty(&bb, (BountyEntry){104, "Iron Howler", 30000});
    addBounty(&bb, (BountyEntry){105, "Void Warlord", 200000});

    printf("\n=== INITIAL MAX HEAP (Bounty Board) ===\n");
    displayBoard(&bb);

    printf("\n=== CAPTURE MOST DANGEROUS CRIMINAL ===\n");
    BountyEntry captured;
    captureMostDangerous(&bb, &captured);
    printf("Captured: %s (ID %d) with bounty %d\n",
           captured.alias, captured.criminalID, captured.bountyCredits);
    displayBoard(&bb);

    printf("\n=== UPDATE BOUNTY (Criminal 103 -> 250000) ===\n");
    updateBounty(&bb, 103, 250000);
    displayBoard(&bb);

    printf("\n=== SORTED BOARD (DESCENDING BOUNTY) ===\n");
    sortBoard(&bb);
    displayBoard(&bb);

    return 0;
}

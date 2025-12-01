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
bool searchCriminal(BountyBoard *bb, int criminalID);
bool updateBounty(BountyBoard *bb, int criminalID, int newBounty);
void displayBoard(BountyBoard *bb) {
    if (bb->count < 0) {
        printf("The bounty board is empty.\n");
        return;
    }

    printf("Current Bounty Board (Count: %d):\n", bb->count + 1);
    printf("-------------------------------------------------\n");
    printf("| ID   | Alias                  | Bounty       |\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i <= bb->count; i++) {
        printf("| %-4d | %-22s | %-11d |\n",
               bb->heap[i].criminalID,
               bb->heap[i].alias,
               bb->heap[i].bountyCredits);
    }

    printf("-------------------------------------------------\n");
}
void sortBoard(BountyBoard *bb);

void maxheapify(BountyBoard *bb);

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


    if (searchCriminal(&bb, 101)) {
        printf("It is found. ID: 101\n");
    } else {
        printf("Not found ID 101");
    }



       displayBoard(&bb);
       printf("Max heapify as it is disrupted\n");
       maxheapify(&bb);
       displayBoard(&bb);


    printf("\n\n=== UPDATE BOUNTY (Criminal 103 -> 250000) ===\n");
    updateBounty(&bb, 103, 250000);
    displayBoard(&bb);
    printf("\n\n");

    printf("\n=== SORTED BOARD (DESCENDING BOUNTY) ===\n");
    sortBoard(&bb);
    displayBoard(&bb);

    return 0;
}

void initBoard(BountyBoard *bb) {

    bb->count = -1;
}

bool addBounty(BountyBoard *bb, BountyEntry be) {

    int child, pr;

    if (bb->count == MAX_CRIMINALS-1) return false;

    bb->count++;
    child = bb->count;
    pr = (child-1)/2;


    while (child>0 && bb->heap[pr].bountyCredits <  be.bountyCredits) {

        bb->heap[child] = bb->heap[pr];
        child = pr;
        pr = (child-1)/2;
    }

    bb->heap[child] = be;
    return true;
}

bool captureMostDangerous(BountyBoard *bb, BountyEntry *captured) {
    int child, pr;

    if (bb->count == -1) return false;

    *captured = bb->heap[0];
    bb->heap[0] = bb->heap[bb->count];
    bb->count--;

    pr = 0;
    child = 2 * pr+1;

    while (child <= bb->count) {
        if (child+1 <= bb->count && bb->heap[child+1].bountyCredits > bb->heap[child].bountyCredits) {
            child++;
        }

        if (bb->heap[pr].bountyCredits < bb->heap[child].bountyCredits) {
            BountyEntry swap = bb->heap[pr];
            bb->heap[pr] = bb->heap[child];
            bb->heap[child] = swap;

            pr = child;
            child = 2 * pr +1;
        } else {
            break;
        }
    }
    return true;




}


bool searchCriminal(BountyBoard *bb, int criminalID) {
    
    // BountyBoard temp;
    // initBoard(&temp);


    // bool found = false;
    // while (bb->count != -1) {
    //     BountyEntry removed;
    //     captureMostDangerous(bb, &removed);
    //     if (removed.criminalID == criminalID) {
    //         found = true;
    //     }
    //     addBounty(&temp, removed);
    // }


    // while (temp.count != -1) {
    //     BountyEntry removed;
    //     captureMostDangerous(&temp, &removed);
    //     addBounty(bb, removed);
    // }

    for(int i = 0; i <= bb->count; i++) {
        if (bb->heap[i].criminalID == criminalID) {
            return true;
        }
    }
    return false;
}


void sortBoard(BountyBoard *bb) {

    BountyEntry catcher;
    int orig;

    orig = bb->count;
    maxheapify(bb);

    while (bb->count != -1) {
        captureMostDangerous(bb, &catcher);
        bb->heap[bb->count+1] = catcher;
    }

    bb->count = orig;
}

void maxheapify(BountyBoard *bb) {

   

    int pr = (bb->count -1)/2;

    while (pr >= 0) {
        int down = pr;
        int child = 2 * down +1;
        while (child <= bb->count) {
            if (child+1 <= bb->count && bb->heap[child+1].bountyCredits > bb->heap[child].bountyCredits) {
                child++;
            }

            if (bb->heap[down].bountyCredits < bb->heap[child].bountyCredits) {
                BountyEntry swap = bb->heap[down];
                bb->heap[down] = bb->heap[child];
                bb->heap[child] = swap;

                down = child;
                child = down * 2+1;
            } else {
                break;
            }
        }
        pr--;
    }
}


bool updateBounty(BountyBoard *bb, int criminalID, int newBounty) {

    for(int i = 0; i <= bb->count; i++) {
        if (bb->heap[i].criminalID == criminalID) {
            bb->heap[i].bountyCredits = newBounty;
            maxheapify(bb);
            return true;
        }
    }
    return false;
}

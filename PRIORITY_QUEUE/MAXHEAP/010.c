#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
    int handleID;
    char *aliasName;
    char *countryOrigin;
    float strengthIndex;
    int threatRank;   // IMPORTANT: priority
} ThreatNode;

typedef struct {
    ThreatNode *rack;   // dynamic array storing heap
    int used;           // last valid index (starts at -1)
    int maxSlots;       // capacity
} ThreatHeap;

void initThreatHeap(ThreatHeap *th, int cap);
void freeThreatHeap(ThreatHeap *th);

bool addThreat(ThreatHeap *th, ThreatNode t);
bool pullMostDangerous(ThreatHeap *th, ThreatNode *removed);

void siftUpMax(ThreatHeap *th);
void siftDownMax(ThreatHeap *th);

int locateThreat(ThreatHeap *th, int handleID);

bool raiseThreatRank(ThreatHeap *th, int handleID, int newRank);
bool lowerThreatRank(ThreatHeap *th, int handleID, int newRank);

bool adjustStrength(ThreatHeap *th, int handleID, float newStrength);
bool relocateOrigin(ThreatHeap *th, int handleID, const char *newOrigin);

bool eraseThreat(ThreatHeap *th, int handleID);

void rebuildThreatHeap(ThreatHeap *th);

void displayThreats(ThreatHeap *th);

void swapNodes(ThreatNode *a, ThreatNode *b);

int main() {
    ThreatHeap vault;
    initThreatHeap(&vault, 25);

    ThreatNode t1 = {3001, strdup("RedDagger"), strdup("Russia"), 91.2, 17};
    ThreatNode t2 = {3002, strdup("NightWasp"), strdup("Iran"),   75.0, 29};
    ThreatNode t3 = {3003, strdup("GhostJackal"), strdup("China"), 44.8, 10};
    ThreatNode t4 = {3004, strdup("IronHydra"), strdup("North Korea"), 82.6, 33};
    ThreatNode t5 = {3005, strdup("BlackSerpent"), strdup("Brazil"), 50.9, 15};

    addThreat(&vault, t1);
    addThreat(&vault, t2);
    addThreat(&vault, t3);
    addThreat(&vault, t4);
    addThreat(&vault, t5);

    printf("\n=== INITIAL THREAT LIST ===\n");
    displayThreats(&vault);

    printf("\n=== MOST DANGEROUS REMOVED ===\n");
    ThreatNode out;
    pullMostDangerous(&vault, &out);
    printf("Removed: %d (%s) – Rank %d\n",
           out.handleID, out.aliasName, out.threatRank);
    displayThreats(&vault);

    printf("\n=== RAISE RANK (increase priority) ===\n");
    raiseThreatRank(&vault, 3003, 50);
    displayThreats(&vault);

    printf("\n=== LOWER RANK (decrease priority) ===\n");
    lowerThreatRank(&vault, 3005, 3);
    displayThreats(&vault);

    // printf("\n=== ADJUST STRENGTH ===\n");
    // adjustStrength(&vault, 3001, 12.75);
    // displayThreats(&vault);

    // printf("\n=== RELOCATE ORIGIN ===\n");
    // relocateOrigin(&vault, 3002, "Singapore");
    // displayThreats(&vault);

    printf("\n=== ERASE THREAT ID: 3003 ===\n");
    eraseThreat(&vault, 3003);
    displayThreats(&vault);

    printf("\n=== REBUILD MAX HEAP ===\n");
    rebuildThreatHeap(&vault);
    displayThreats(&vault);

    freeThreatHeap(&vault);
    return 0;
}


/* ----------------------------------------------------
      INITIALIZATION & CLEANUP
   ---------------------------------------------------- */

/*
 * Initializes a ThreatHeap with a given capacity.
 * Allocates memory for the dynamic array and sets
 * used = -1 (meaning empty).
 */
void initThreatHeap(ThreatHeap *th, int cap) {
    th->rack = malloc(sizeof(ThreatNode)*cap);
    if (th->rack == NULL) return;
    
    
    
    th->used = -1;
    th->maxSlots = cap;
}

/*
 * Frees all allocated memory in the heap:
 *   - frees each aliasName and countryOrigin
 *   - frees the rack array
 */
void freeThreatHeap(ThreatHeap *th) {

    for(int i = 0; i <= th->used; i++) {
        free(th->rack[i].aliasName);
        free(th->rack[i].countryOrigin);
    }
    free(th->rack);
    th->used = -1;
    th->maxSlots = -1;


}


/* ----------------------------------------------------
      CORE HEAP OPERATIONS
   ---------------------------------------------------- */

/*
 * Inserts a new ThreatNode into the heap.
 * Returns true if successful, false if heap is full.
 * Uses siftUpMax() to restore heap order.
 */
bool addThreat(ThreatHeap *th, ThreatNode t) {
    int child, pr;

    if (th->used == th->maxSlots -1) return false;

    th->used++;
    child = th->used;
   pr = (child-1)/2;

   while (child > 0 && th->rack[pr].threatRank < t.threatRank) {
    th->rack[child] = th->rack[pr];
    child = pr;
    pr = (child-1)/2;
   }

   th->rack[child] = t;


return true;
}

/*
 * Removes the threat with the **highest threatRank**
 * (max-heap root at index 0).
 * Stores removed node in *removed.
 * Uses siftDownMax() to restore heap order.
 */
bool pullMostDangerous(ThreatHeap *th, ThreatNode *removed) {

    int child, pr;
    ThreatNode swap;

    if (th->used == -1) return false;


    *removed = th->rack[0];
    th->rack[0] = th->rack[th->used];
    th->used--;

    pr = 0;
    child = 2 * pr +1;


    while (child <= th->used) {

        if (child+1 <= th->used && th->rack[child+1].threatRank > th->rack[child].threatRank) {
            child++;
        }

        if (th->rack[pr].threatRank < th->rack[child].threatRank) {
            swap = th->rack[pr];
            th->rack[pr] = th->rack[child];
            th->rack[child] = swap;
            pr = child;
            child = pr * 2+1;
        } else {
            break;
        }
    }

    return true;
}


/* ----------------------------------------------------
      HEAP FIXING (INTERNAL)
   ---------------------------------------------------- */

/*
 * Moves the last inserted node upward until the
 * max-heap property is restored.
 */
void siftUpMax(ThreatHeap *th) {

    
    

  int child = th->used;
  int down = (child-1)/2;
  ThreatNode swap;

            while (child <= th->used) {

            if (th->rack[down].threatRank < th->rack[child].threatRank) {
                swap = th->rack[down];
                th->rack[down] = th->rack[child];
                th->rack[child] = swap;

                child = down;
                down = (child-1)/2;
            } else {
                break;
            }
        }

    }


/*
 * Pushes down a node from the root until the
 * max-heap property is restored.
 */
void siftDownMax(ThreatHeap *th) {

   int down = 0;
   int child = 2 * down +1;
   ThreatNode swap;



   while (child <= th->used) {
            if (child+1 <= th->used && th->rack[child+1].threatRank > th->rack[child].threatRank) {
                child++;
            }

            if (th->rack[down].threatRank < th->rack[child].threatRank) {
                swap = th->rack[down];
                th->rack[down] = th->rack[child];
                th->rack[child] = swap;

                down = child;
                child = 2 * down+1;
            } else {
                break;
            }
}

}

/* ----------------------------------------------------
      SEARCH & MODIFY
   ---------------------------------------------------- */

/*
 * Returns the index of a threat with the given handleID.
 * Returns -1 if not found.
 */
int locateThreat(ThreatHeap *th, int handleID) {

    for(int i = 0; i <= th->used; i++) {
        if (th->rack[i].handleID == handleID) {return i;}
    }

    return -1;
}

/*
 * Increases the threatRank of a given handleID.
 * Calls siftUpMax() because priority increased.
 * Returns true if updated, false if not found.
 */
bool raiseThreatRank(ThreatHeap *th, int handleID, int newRank) {

    for(int i = 0; i <= th->used; i++) {
        if (th->rack[i].handleID == handleID) {
            int temp = th->rack[i].threatRank;
            th->rack[i].threatRank += newRank;

            rebuildThreatHeap(th);
            

            return true;
        }
    }

    return false;
}

/*
 * Decreases the threatRank of a given handleID.
 * Calls siftDownMax() because priority lowered.
 * Returns true if updated, false if not found.
 */
bool lowerThreatRank(ThreatHeap *th, int handleID, int newRank) {
    
    for(int i = 0; i <= th->used; i++) {
        if (th->rack[i].handleID == handleID) {
            int temp = th->rack[i].threatRank;
            th->rack[i].threatRank -= newRank;


            
            
              rebuildThreatHeap(th);
            

            

            return true;
        }
    }

    return false;
}

/*
 * Adjusts the strengthIndex of a specific threat.
 * Does NOT affect heap ordering (strength is not priority).
 * Returns true if updated.
 */
bool adjustStrength(ThreatHeap *th, int handleID, float newStrength) {

    for(int i = 0; i <= th->used; i++) {
        if (th->rack[i].handleID == handleID) {
            th->rack[i].strengthIndex = newStrength;
            return true;
        }
    }
    return false;
}
/*
 * Replaces the countryOrigin of a given threat.
 * Frees the old string and assigns a duplicate of newOrigin.
 * Returns true if updated.
 */
bool relocateOrigin(ThreatHeap *th, int handleID, const char *newOrigin) {
    for(int i = 0; i <= th->used; i++) {
        if (th->rack[i].handleID == handleID) {
            strcpy(th->rack[i].countryOrigin, newOrigin);
            return true;
        }
    }

    return false;
}

/*
 * Completely removes a threat from the heap by:
 *   - finding the index
 *   - replacing it with the last node
 *   - restoring heap property depending on rank
 * Returns true if successful.
 */
bool eraseThreat(ThreatHeap *th, int handleID) {

    int index = -1;
    for(int i =0; i <= th->used; i++) {
        if (th->rack[i].handleID == handleID) {
            index = i;th->rack[index] = th->rack[th->used];
        th->used--;



            
        return true;
            
        }
    }


  
    if (index == -1) return false;
}


/* ----------------------------------------------------
      FULL HEAP REBUILD
   ---------------------------------------------------- */

/*
 * Rebuilds the heap from scratch using heapify.
 * Useful if many ranks were edited manually.
 */
void rebuildThreatHeap(ThreatHeap *th) {


    
    int pr, down, child;
    ThreatNode swap;

    pr = (th->used-1)/2;

    while (pr >= 0) {
        down = pr;
        child = 2*down +1;

        while (child <= th->used) {
            if (child+1 <= th->used && th->rack[child+1].threatRank > th->rack[child].threatRank) {
                child++;
            }

            if (th->rack[down].threatRank < th->rack[child].threatRank) {
                swap = th->rack[down];
                th->rack[down] = th->rack[child];
                th->rack[child] = swap;

                down = child;
                child = 2 * down+1;
            } else {
                break;
            }
        }

        pr--;
    }

}


/* ----------------------------------------------------
      DISPLAY & UTILITY
   ---------------------------------------------------- */

/*
 * Prints all threat nodes in the heap in array order.
 * (NOT in priority-sorted order)
 */
void displayThreats(ThreatHeap *th) {
    if (th->used == -1) {
        printf("[Vault is EMPTY]\n");
        return;
    }

    printf("Index | HandleID | Alias          | Origin          | Strength | Rank\n");
    printf("-----------------------------------------------------------------------\n");

    for (int i = 0; i <= th->used; i++) {
        printf("%5d | %8d | %-14s | %-14s | %8.2f | %4d\n",
               i,
               th->rack[i].handleID,
               th->rack[i].aliasName,
               th->rack[i].countryOrigin,
               th->rack[i].strengthIndex,
               th->rack[i].threatRank);
    }
}

void swapNodes(ThreatNode *a, ThreatNode *b) {
    ThreatNode swap = *a;
    *a = *b;
    *b = swap;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CHEAP 50   // heap capacity

typedef struct Fighter {
    int badgeID;
    char *alias;
    char *combatStyle;
    float winRate;      // PRIORITY (MAX HEAP)
} Fighter;

typedef struct ArenaHeap {
    Fighter *hill;      // dynamic array of Fighters
    int fill;           // last index (starts at -1)
    int limit;          // capacity
} ArenaHeap;

// ========================================================
// FUNCTION PROTOTYPES (15 total) WITH PURPOSE COMMENTS
// ========================================================

// 1. Initialize an empty heap
// Purpose: Allocates the array, sets fill = -1, sets limit.
void initArena(ArenaHeap *A, int cap);

// 2. Allocate a Fighter dynamically
// Purpose: Creates a Fighter with malloc'ed strings.
Fighter makeFighter(int id, const char *name, const char *style, float rate);

// 3. Insert a Fighter into the max heap
// Purpose: Places new fighter at bottom, heapify upward (MAX HEAP).
void admitFighter(ArenaHeap *A, Fighter f);

// 4. Bubble-up / sift-up procedure
// Purpose: Fixes the heap upward when a new Fighter is inserted.
void elevateFighter(ArenaHeap *A, int idx);

// 5. Remove the top fighter (max winRate)
// Purpose: Swaps top with last, decreases size, heapify-down.
Fighter expelChampion(ArenaHeap *A);

// 6. Heapify-down procedure
// Purpose: Fixes heap downward after deletion from the root.
void descendFighter(ArenaHeap *A, int idx);

// 7. Build heap from raw array
// Purpose: Converts all elements in A->hill into a valid MAX HEAP.
void forgeArena(ArenaHeap *A);

// 8. Return the number of fighters
// Purpose: Returns how many fighters currently in heap.
int countFighters(ArenaHeap *A);

// 9. Check if heap is empty
// Purpose: Returns true if fill == -1.
bool hallEmpty(ArenaHeap *A);

// 10. Check if heap is full
// Purpose: Returns true if fill == limit-1.
bool hallFull(ArenaHeap *A);

// 11. Peek the strongest fighter
// Purpose: Returns the root (without removing).
Fighter viewChampion(ArenaHeap *A);

// 12. Search fighter by badgeID
// Purpose: Linearly scans the heap and returns index or -1.
int locateBadge(ArenaHeap *A, int badge);

// 13. Expand alias string (dynamic manipulation)
// Purpose: Realloc alias to append a word (tests realloc skills).
void extendAlias(Fighter *f, const char *addon);

// 14. Replace champion’s winRate
// Purpose: Updates winRate and re-heapifies to maintain max-heap
void reviseRate(ArenaHeap *A, int id, float newRate);

// 15. Free all dynamic allocations
// Purpose: Frees all strings and the array safely.
void purgeArena(ArenaHeap *A);

// ========================================================
//                       MAIN
// ========================================================
int main() {

    ArenaHeap arena;
    initArena(&arena, MAX_CHEAP);

    // Test makeFighter + admitFighter + elevateFighter
    admitFighter(&arena, makeFighter(101, "Blitz", "ShockFist", 89.1));
    admitFighter(&arena, makeFighter(203, "RogueWitch", "HexMage", 95.4));
    admitFighter(&arena, makeFighter(150, "StoneOgre", "BruteForce", 74.3));
    admitFighter(&arena, makeFighter(322, "NightLancer", "ShadowBlade", 97.8));

    printf("\nCurrent Champion: %s\n", viewChampion(&arena).alias);

    // Test locateBadge
    int idx = locateBadge(&arena, 203);
    if (idx != -1) printf("Found RogueWitch at index %d\n", idx);

    // Test reviseRate (forces heap reordering)
    reviseRate(&arena, 150, 99.5);
    printf("New Champion after updating StoneOgre: %s\n",
           viewChampion(&arena).alias);

    // Test extendAlias
    extendAlias(&arena.hill[0], "_Alpha");
    printf("Top alias modified: %s\n", arena.hill[0].alias);

    // Test countFighters
    printf("Fighters in arena: %d\n", countFighters(&arena));

    // Test expelChampion + descendFighter
    Fighter eliminated = expelChampion(&arena);
    printf("Eliminated: %s (%.1f)\n", eliminated.alias, eliminated.winRate);
    free(eliminated.alias);
    free(eliminated.combatStyle);

    // Test hallEmpty / hallFull
    printf("Arena empty? %s\n", hallEmpty(&arena) ? "YES" : "NO");
    printf("Arena full?  %s\n", hallFull(&arena) ? "YES" : "NO");

    // Final cleanup test
    purgeArena(&arena);

    return 0;
}

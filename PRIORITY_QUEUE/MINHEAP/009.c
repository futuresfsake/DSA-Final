#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CREW 10
#define NAME_LEN 50
#define DEPT_LEN 30

/*
    Starship Command Priority Queue

    Backstory:
    ----------------
    The interstellar fleet maintains a command queue for crew members.
    Each crew member has a Name, RankIndex (priority key), and a Division.
    The RankIndex is lower for higher priority (0 = Admiral).  

    All queue operations must be iterative to simulate real-time decision making
    during space missions, avoiding recursion that can trigger critical
    system errors.
*/

// ================================
// Crew Member Struct
// ================================
typedef struct {
    char name[NAME_LEN];
    int rankIndex;          // lower = higher priority
    char division[DEPT_LEN];
} Crew;

// ================================
// Min-Heap Struct
// ================================
typedef struct {
    Crew heap[MAX_CREW];
    int size; // last index used, initialize to -1
} CommandQueue;

// ================================
// Iterative Function Prototypes
// ================================

// 1. Initialize empty queue
void initQueue(CommandQueue *q);

// 2. Check if queue is empty
bool isQueueEmpty(CommandQueue *q);

// 3. Insert a crew member iteratively
void enqueueCrew(CommandQueue *q, Crew c);

// 4. Extract the highest-priority crew member iteratively
Crew dequeueCrew(CommandQueue *q);

// 5. Peek at the top crew member without removing
Crew peekTopCrew(CommandQueue *q);

// 6. Iteratively heapify entire queue
void heapifyQueue(CommandQueue *q);

// 7. Find a crew member by name iteratively
int findCrewByName(CommandQueue *q, const char *name);

// 8. Increase priority of a crew member iteratively (decrease rankIndex)
void promoteCrew(CommandQueue *q, const char *name, int newRank);

// 9. Decrease priority of a crew member iteratively (increase rankIndex)
void demoteCrew(CommandQueue *q, const char *name, int newRank);

// 10. Display all crew members iteratively
void displayQueue(CommandQueue *q);

// 11. Count total crew iteratively
int totalCrew(CommandQueue *q);

// 12. Clear queue iteratively
void clearQueue(CommandQueue *q);

// ================================
// MAIN (Sample Usage)
// ================================
int main() {
    CommandQueue cq;
    initQueue(&cq);

    // Sample crew members
    Crew c1 = {"Zara", 2, "Navigation"};
    Crew c2 = {"Kiro", 0, "Command"};
    Crew c3 = {"Luma", 3, "Engineering"};
    Crew c4 = {"Vex", 1, "Science"};
    Crew c5 = {"Nyra", 4, "Medical"};

    // Insert crew members iteratively
    enqueueCrew(&cq, c1);
    enqueueCrew(&cq, c2);
    enqueueCrew(&cq, c3);
    enqueueCrew(&cq, c4);
    enqueueCrew(&cq, c5);

    // Display queue
    displayQueue(&cq);

    // // Extract top priority crew member
    // Crew top = dequeueCrew(&cq);
    // printf("\nTop priority extracted: %s, Rank: %d, Division: %s\n",
    //        top.name, top.rankIndex, top.division);

    // // Promote a crew member
    // promoteCrew(&cq, "Nyra", 1);

    // // Demote a crew member
    // demoteCrew(&cq, "Luma", 5);

    // // Display queue after changes
    // displayQueue(&cq);

    // // Find crew by name
    // int idx = findCrewByName(&cq, "Vex");
    // if(idx != -1) printf("\nVex is at index %d in the queue.\n", idx);

    // // Peek top crew
    // Crew peek = peekTopCrew(&cq);
    // printf("Current top crew: %s, Rank: %d\n", peek.name, peek.rankIndex);

    // // Count total crew
    // printf("Total crew in queue: %d\n", totalCrew(&cq));

    // // Heapify queue
    // heapifyQueue(&cq);

    // // Clear queue
    // clearQueue(&cq);

    return 0;
}


// 1. Initialize empty queue
void initQueue(CommandQueue *q) {
    q->size = -1;
}

// 2. Check if queue is empty
bool isQueueEmpty(CommandQueue *q) {
    return q->size == -1;
}

// 3. Insert a crew member iteratively
void enqueueCrew(CommandQueue *q, Crew c) {
    int child, pr;

    if (q->size == MAX_CREW -1) {
        printf("Heap is already full\n");
        return;
    }

    q->size++;
    child = q->size;
    pr = (child-1)/2;

    while (child >= 0 && q->heap[pr].rankIndex > c.rankIndex) {
        q->heap[child] = q->heap[pr];
        child = pr;
        pr = (child-1)/2;
    }
    q->heap[child] = c;


}

// 4. Extract the highest-priority crew member iteratively
Crew dequeueCrew(CommandQueue *q);

// 5. Peek at the top crew member without removing
Crew peekTopCrew(CommandQueue *q);

// 6. Iteratively heapify entire queue
void heapifyQueue(CommandQueue *q);

// 7. Find a crew member by name iteratively
int findCrewByName(CommandQueue *q, const char *name);

// 8. Increase priority of a crew member iteratively (decrease rankIndex)
void promoteCrew(CommandQueue *q, const char *name, int newRank);

// 9. Decrease priority of a crew member iteratively (increase rankIndex)
void demoteCrew(CommandQueue *q, const char *name, int newRank);

void displayQueue(CommandQueue *q) {
    printf("\n--- Command Queue Status ---\n");
    
    if (q->size == -1) {
        printf("Queue is empty.\n");
        return;
    }

    for (int i = 0; i <= q->size; i++) {
        printf("Index %d: %s, Rank: %d, Division: %s\n",
               i,
               q->heap[i].name,
               q->heap[i].rankIndex,
               q->heap[i].division);
    }
}

// 11. Count total crew iteratively
int totalCrew(CommandQueue *q);

// 12. Clear queue iteratively
void clearQueue(CommandQueue *q);

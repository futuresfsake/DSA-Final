#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_DRAGONS 15
#define NAME_LEN 50

/*
    ======================================================
        AETHERIA KINGDOM – DRAGON RESCUE DISPATCH CENTER
    ------------------------------------------------------
    The kingdom receives emergency reports about dragons 
    stuck, injured, or trapped in dangerous places.

    A MIN-HEAP is used to determine which rescue operation 
    should be responded to FIRST.

    PRIORITY RULE:
        - Lower priority number = more urgent
        - 1 = Critical rescue
        - 10 = Minor issue

    OPERATIONS YOU MUST IMPLEMENT:
        ✔ initQueue
        ✔ insertRescueRequest
        ✔ removeHighestPriority
        ✔ updatePriority
        ✔ searchDragon
        ✔ displayQueue

    HELPER FUNCTIONS (10 total):
        ✔ peekHighestPriority
        ✔ isQueueFull
        ✔ isQueueEmpty
        ✔ countDragons
        ✔ getParentIndex
        ✔ getLeftChildIndex
        ✔ getRightChildIndex
        ✔ swapDragons
        ✔ bubbleUp
        ✔ bubbleDown

    A full main() is provided to test all functions.
    ======================================================
*/

typedef struct {
    int dragonID;
    char dragonName[NAME_LEN];
    int priorityLevel;  // 1 = critical, 10 = minor
} RescueRequest;

typedef struct {
    RescueRequest heap[MAX_DRAGONS];
    int count;
} RescueQueue;

// =================== FUNCTION PROTOTYPES ===================

void initQueue(RescueQueue *rq);
bool insertRescueRequest(RescueQueue *rq, RescueRequest rr);
bool removeHighestPriority(RescueQueue *rq, RescueRequest *removed);
bool updatePriority(RescueQueue *rq, int dragonID, int newPriority);
int searchDragon(RescueQueue *rq, int dragonID);
void displayQueue(RescueQueue *rq) {
    
    for(int i = 0; i <= rq->count; i++) {
        printf("Priority: %d | ID: %d  | Name: %s \n", rq->heap[i].priorityLevel, rq->heap[i].dragonID, rq->heap[i].dragonName);
    }
}

// Helper / Utility
RescueRequest peekHighestPriority(RescueQueue *rq);
bool isQueueFull(RescueQueue *rq);
bool isQueueEmpty(RescueQueue *rq);
int countDragons(RescueQueue *rq);
int getParentIndex(int i);
int getLeftChildIndex(int i);
int getRightChildIndex(int i);
void swapDragons(RescueRequest *a, RescueRequest *b);
void bubbleUp(RescueQueue *rq, int index);
void bubbleDown(RescueQueue *rq, int index);

// =================== MAIN TESTER ===================

int main() {
    RescueQueue rq;
    initQueue(&rq);

    // Sample rescue calls
    RescueRequest r1 = {501, "Pyraxis the Red", 5};
    RescueRequest r2 = {502, "Zephyron the Blue", 2};
    RescueRequest r3 = {503, "Glimscale the Tiny", 1};
    RescueRequest r4 = {504, "Drakar the Fierce", 4};
    RescueRequest r5 = {505, "Moonclaw the Ancient", 3};

    printf("\n=== ADD RESCUE REQUESTS ===\n");
    insertRescueRequest(&rq, r1);
    insertRescueRequest(&rq, r2);
    insertRescueRequest(&rq, r3);
    insertRescueRequest(&rq, r4);
    insertRescueRequest(&rq, r5);
    displayQueue(&rq);

    printf("\n=== NEXT DRAGON TO RESCUE ===\n");
    RescueRequest next = peekHighestPriority(&rq);
    printf("Next: %d (%s) Priority: %d\n", next.dragonID, next.dragonName, next.priorityLevel);

    printf("\n=== REMOVE HIGHEST PRIORITY ===\n");
    RescueRequest removed;
    removeHighestPriority(&rq, &removed);
    printf("Rescued: %d (%s) Priority: %d\n", removed.dragonID, removed.dragonName, removed.priorityLevel);
    displayQueue(&rq);

    printf("\n=== UPDATE PRIORITY (Dragon 504 -> Priority 1) ===\n");
    updatePriority(&rq, 504, 1);
    displayQueue(&rq);

    printf("\n=== SEARCH Dragon 505 ===\n");
    int idx = searchDragon(&rq, 505);
    if (idx != -1)
        printf("Found at index %d: %s Priority %d\n", idx, rq.heap[idx].dragonName, rq.heap[idx].priorityLevel);
    else
        printf("Dragon not found.\n");

    printf("\n=== QUEUE STATUS ===\n");
    printf("Queue empty? %s\n", isQueueEmpty(&rq) ? "Yes" : "No");
    printf("Queue full? %s\n", isQueueFull(&rq) ? "Yes" : "No");
    printf("Dragons waiting: %d\n", countDragons(&rq));

    printf("\n=== HELPER FUNCTION TESTS ===\n");
    printf("Parent of index 2: %d\n", getParentIndex(2));
    printf("Left child of index 0: %d\n", getLeftChildIndex(0));
    printf("Right child of index 0: %d\n", getRightChildIndex(0));

    return 0;
}

// =================== FUNCTION SKELETONS (fill these in) ===================

void initQueue(RescueQueue *rq) {
    // TODO: rq->count = -1;

    rq->count = -1;
}

bool insertRescueRequest(RescueQueue *rq, RescueRequest rr) {
    // TODO

    if (rq->count == MAX_DRAGONS-1) return false;


    int child, pr;


    rq->count++;
    child = rq->count;
    pr = (child-1)/2;
    
    while (child > 0 && rq->heap[pr].priorityLevel >rr.priorityLevel) {
        rq->heap[child] = rq->heap[pr];
        child = pr;
        pr = (child-1)/2;
    }
    
    rq->heap[child] = rr;

}

bool removeHighestPriority(RescueQueue *rq, RescueRequest *removed) {

    
    if (rq->count == -1) return false;
    
    int child, pr;
    RescueRequest swap;
    
    
    
    *removed = rq->heap[0];
    rq->heap[0] = rq->heap[rq->count];
    rq->count--;
    
    
    pr = 0;
    child = 2 * pr +1;
    
    
    while (child <= rq->count) {
        if (child+1 <= rq->count && rq->heap[child+1].priorityLevel < rq->heap[child].priorityLevel) {
            child++;
        }
        
        if (rq->heap[pr].priorityLevel > rq->heap[child].priorityLevel) {
            swap = rq->heap[pr];
            rq->heap[pr] = rq->heap[child];
            rq->heap[child]=swap;
            
            pr = child;
            child = 2 * pr +1;
        } else {
            break;
        }
    }
}

bool updatePriority(RescueQueue *rq, int dragonID, int newPriority) {
    
    
    for(int i = 0; i <= rq->count; i++) {
        if (rq->heap[i].dragonID == dragonID) {
            rq->heap[i].priorityLevel = newPriority;
            
            
            // bubbleUp(rq, i);
            bubbleDown(rq, 0);
        }
    }
}

int searchDragon(RescueQueue *rq, int dragonID) {
    // TODO
    if (rq->count == -1) return -1;
    
    for(int i = 0; i <= rq->count; i++) {
        if (rq->heap[i].dragonID == dragonID) {
            return i;
        }
    }
    
    return -1;
}



// // =================== HELPER FUNCTIONS ===================

RescueRequest peekHighestPriority(RescueQueue *rq) {
    // TODO
    RescueRequest blank = {0};
    
    if (rq->count == -1) {
        return blank;
    } 
    
    
    
    return rq->heap[0];
}

bool isQueueFull(RescueQueue *rq) {
    // TODO
    return rq->count == MAX_DRAGONS-1;
}

bool isQueueEmpty(RescueQueue *rq) {
    // TODO
    return rq->count == -1;
}

int countDragons(RescueQueue *rq) {
    // TODO
    return rq->count+1;
}

int getParentIndex(int i) {
    // TODO
    int p = (i-1)/2;
    return p;
}

int getLeftChildIndex(int i) {
    // TODO
    return 2 * i +1;
}

int getRightChildIndex(int i) {
    // TODO
    return 2 * i +2;
}

void swapDragons(RescueRequest *a, RescueRequest *b) {
    
    RescueRequest swap = *a;
    *a = *b;
    *b = swap;
    
}

void bubbleUp(RescueQueue *rq, int index) {
    // TODO
    
    int child = index;
    int pr = (child-1)/2;
    
    
    while (child > 0 && rq->heap[pr].priorityLevel > rq->heap[child].priorityLevel) {
        swapDragons(&rq->heap[pr], &rq->heap[child]);
        
        child = pr;
        pr = (child-1)/2;
    }
}

void bubbleDown(RescueQueue *rq, int index) {
    
    int pr = index;
    int child = 2 *pr+1;
    
    
    while (child <= rq->count) {
        if (child+1 <= rq->count && rq->heap[child+1].priorityLevel < rq->heap[child].priorityLevel) {
            child++;
        }
        if (rq->heap[pr].priorityLevel > rq->heap[child].priorityLevel) {
            RescueRequest swap = rq->heap[pr];
            rq->heap[pr] = rq->heap[child];
            rq->heap[child] = swap;
            
            pr = child;
            child = 2 * pr +1;
            } else {
                break;
            }
    }
}

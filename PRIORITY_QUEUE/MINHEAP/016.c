#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PLANES 12
#define NAME_LEN 50

/*
    ======================================================
        TERRA INTERNATIONAL AIRPORT – LANDING PRIORITY SYSTEM
    ------------------------------------------------------
    This airport manages incoming aircraft using a 
    MIN-HEAP based priority queue.

    PRIORITY RULE:
        - Lower priority number = lands earlier
        - 1 = Emergency landing
        - 10 = Normal landing

    OPERATIONS (you must implement these iteratively):
        ✔ initQueue
        ✔ insertLandingRequest
        ✔ removeHighestPriority
        ✔ updatePriority
        ✔ searchPlane
        ✔ displayQueue

    UTILITY / HELPER FUNCTIONS (10 total):
        ✔ peekHighestPriority
        ✔ isQueueFull
        ✔ isQueueEmpty
        ✔ countPlanes
        ✔ getParentIndex
        ✔ getLeftChildIndex
        ✔ getRightChildIndex
        ✔ swapPlanes
        ✔ bubbleUp
        ✔ bubbleDown

    Your task is to implement ALL of these.
    The main() already performs a full test.
    ======================================================
*/

typedef struct {
    int planeID;
    char airline[NAME_LEN];
    int priorityLevel; // 1 = emergency, 10 = normal
} LandingRequest;

typedef struct {
    LandingRequest heap[MAX_PLANES];
    int count; // current number of planes stored
} LandingQueue;

// =================== FUNCTION PROTOTYPES ===================

void initQueue(LandingQueue *lq);
bool insertLandingRequest(LandingQueue *lq, LandingRequest lr);
bool removeHighestPriority(LandingQueue *lq, LandingRequest *removed);
bool updatePriority(LandingQueue *lq, int planeID, int newPriority);
int searchPlane(LandingQueue *lq, int planeID);
void displayQueue(LandingQueue *lq);

// Helper / Utility
LandingRequest peekHighestPriority(LandingQueue *lq);
bool isQueueFull(LandingQueue *lq);
bool isQueueEmpty(LandingQueue *lq);
int countPlanes(LandingQueue *lq);
int getParentIndex(int i);
int getLeftChildIndex(int i);
int getRightChildIndex(int i);
void swapPlanes(LandingRequest *a, LandingRequest *b);
void bubbleUp(LandingQueue *lq, int index);
void bubbleDown(LandingQueue *lq, int index);

// =================== MAIN TESTER ===================

int main() {
    LandingQueue lq;
    initQueue(&lq);

    // Create sample landing requests
    LandingRequest p1 = {101, "SkyJet 400", 5};
    LandingRequest p2 = {102, "AeroDyn 777", 2};
    LandingRequest p3 = {103, "Nimbus A200", 1};
    LandingRequest p4 = {104, "CloudWing 320", 4};
    LandingRequest p5 = {105, "StormRider X5", 3};

    printf("\n=== ADD LANDING REQUESTS ===\n");
    insertLandingRequest(&lq, p1);
    insertLandingRequest(&lq, p2);
    insertLandingRequest(&lq, p3);
    insertLandingRequest(&lq, p4);
    insertLandingRequest(&lq, p5);
    displayQueue(&lq);

    printf("\n=== NEXT PLANE TO LAND ===\n");
    LandingRequest top = peekHighestPriority(&lq);
    printf("Next: %d (%s) Priority: %d\n", top.planeID, top.airline, top.priorityLevel);

    printf("\n=== REMOVE HIGHEST PRIORITY ===\n");
    LandingRequest removed;
    removeHighestPriority(&lq, &removed);
    printf("Landed: %d (%s) Priority: %d\n", removed.planeID, removed.airline, removed.priorityLevel);
    displayQueue(&lq);

    printf("\n=== UPDATE PRIORITY (Plane 104 -> Priority 1) ===\n");
    updatePriority(&lq, 104, 1);
    displayQueue(&lq);

    printf("\n=== SEARCH Plane 105 ===\n");
    int idx = searchPlane(&lq, 105);
    if (idx != -1)
        printf("Found at index %d: %s Priority %d\n", idx, lq.heap[idx].airline, lq.heap[idx].priorityLevel);
    else
        printf("Plane not found.\n");

    printf("\n=== QUEUE STATUS ===\n");
    printf("Queue empty? %s\n", isQueueEmpty(&lq) ? "Yes" : "No");
    printf("Queue full? %s\n", isQueueFull(&lq) ? "Yes" : "No");
    printf("Planes waiting: %d\n", countPlanes(&lq));

    printf("\n=== HELPER FUNCTION TESTS ===\n");
    printf("Parent of index 2: %d\n", getParentIndex(2));
    printf("Left child of index 0: %d\n", getLeftChildIndex(0));
    printf("Right child of index 0: %d\n", getRightChildIndex(0));

    return 0;
}

// =================== FUNCTIONS TO IMPLEMENT ===================
// (You write all logic; these are skeletons)

// Initialize the queue (set count to 0)
void initQueue(LandingQueue *lq) {
    // TODO: lq->count = 0;

    lq->count = -1;
}

// Insert a new plane into the min-heap
bool insertLandingRequest(LandingQueue *lq, LandingRequest lr) {
    
    if (lq->count == MAX_PLANES-1) return false;

    int child, pr;

    lq->count++;
    child = lq->count;
    lq->heap[child] = lr;

    bubbleUp(lq, child);
    return true;
}

void displayQueue(LandingQueue *lq) {
    if (lq->count == -1) {
        printf("The landing queue is empty.\n");
        return;
    }

    printf("\n=====================================================\n");
    printf("       TERRA INTERNATIONAL – LANDING QUEUE\n");
    printf("=====================================================\n");
    printf("Index | Plane ID | Airline                 | Priority\n");
    printf("-----------------------------------------------------\n");

    for (int i = 0; i <= lq->count; i++) {
        printf("%5d | %-8d | %-22s | %-8d\n",
               i,
               lq->heap[i].planeID,
               lq->heap[i].airline,
               lq->heap[i].priorityLevel);
    }

    printf("=====================================================\n");
}


// Remove the highest priority plane (root)
bool removeHighestPriority(LandingQueue *lq, LandingRequest *removed) {
    // TODO:
    // 1. Check empty
    // 2. Save root
    // 3. Move last element to root
    // 4. count--
    // 5. bubbleDown
    

    if (lq->count == -1) return false;

    int child, pr;
    LandingRequest swap;


    *removed = lq->heap[0];
    lq->heap[0] = lq->heap[lq->count];
    lq->count--;

    bubbleDown(lq, 0);
    return true;
}

// Change a plane's priority
bool updatePriority(LandingQueue *lq, int planeID, int newPriority) {
    // TODO:
    // 1. searchPlane()
    // 2. replace priority
    // 3. bubbleUp + bubbleDown
    

    for(int i = 0; i <= lq->count ; i++) {
        if (lq->heap[i].planeID == planeID) {
            lq->heap[i].priorityLevel = newPriority;
            

            bubbleUp(lq, i);
            bubbleDown(lq, i);

            return true;
        }
    }
    return false;
}

// Find plane by planeID (linear scan)
int searchPlane(LandingQueue *lq, int planeID) {
    // TODO:

    for(int i = 0; i <= lq->count; i++) {
        if (lq->heap[i].planeID == planeID) {
            return i;
        }
    }

    return -1;
}


// // Helper functions below: implement all of them

LandingRequest peekHighestPriority(LandingQueue *lq) {
    // TODO: return root (heap[0])
    LandingRequest blank = {0};
    if (lq->count == -1) {
    return blank; }

    return lq->heap[0];

}

bool isQueueFull(LandingQueue *lq) { 
    return lq->count == MAX_PLANES-1;
 }
bool isQueueEmpty(LandingQueue *lq) { 
    return lq->count == -1;
 }
int countPlanes(LandingQueue *lq) { 
    return lq->count +1;
 }

int getParentIndex(int i) { 
    return (i-1)/2;
 }

int getLeftChildIndex(int i) { 
    return i * 2+1;
 }
int getRightChildIndex(int i) { 
    return i * 2+2;
}

void swapPlanes(LandingRequest *a, LandingRequest *b) {
    // TODO: swap values of 2 structs

    LandingRequest swap = *a;
    
    *a = *b;
    *b = swap;
}

void bubbleUp(LandingQueue *lq, int index) {
    // TODO: push element upward until heap rule satisfied

    int child, pr;

    child = index;
    pr = (child-1)/2;

    while (child > 0 && lq->heap[pr].priorityLevel > lq->heap[child].priorityLevel) {
        LandingRequest swap = lq->heap[pr];
        lq->heap[pr] = lq->heap[child];
        lq->heap[child] = swap;

        child = pr;
        pr = (child-1)/2;
    }
}

void bubbleDown(LandingQueue *lq, int index) {
    // TODO: push element downward until heap rule satisfied

    int pr = index;
   int  child = 2 * pr +1;

    while (child <= lq->count) {
        if (child+1 <= lq->count && lq->heap[child+1].priorityLevel < lq->heap[child].priorityLevel) {
            child++;
        }

        if (lq->heap[pr].priorityLevel > lq->heap[child].priorityLevel) {
            LandingRequest swap = lq->heap[pr];
            lq->heap[pr] = lq->heap[child];
            lq->heap[child] = swap;

            pr = child;
            child = 2 * pr +1;
        } else {
            break;
        }
    }
}

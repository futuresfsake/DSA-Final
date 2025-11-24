#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXPQ 100
#define MAX_NAME 50
#define MAX_LOC 50

// =======================================================
//          STRUCT: Emergency Call Record
// =======================================================

typedef struct {
    char callerName[MAX_NAME];
    char location[MAX_LOC];
    int urgencyLevel;    // 1 = highest priority
    int timestamp;       // arrival time (used for tie-breaking)
} EmergencyCall;


// =======================================================
//          PRIORITY QUEUE (MIN-HEAP)
// =======================================================

typedef struct {
    EmergencyCall heap[MAXPQ];
    int size;
} PriorityQueue;


// =======================================================
//          PRIORITY QUEUE FUNCTION PROTOTYPES
// =======================================================

// Initialize the priority queue
void initPQ(PriorityQueue *pq);

// Insert an emergency call into the heap
void insertCall(PriorityQueue *pq, EmergencyCall call);

// Return the highest-priority call (without removing)
EmergencyCall peekCall(PriorityQueue *pq);

// Remove and return the highest-priority call
EmergencyCall extractMin(PriorityQueue *pq);

// Heapify-down operation (used after deletion)
void heapifyDown(PriorityQueue *pq, int index);

// Heapify-up operation (used after insertion)
void heapifyUp(PriorityQueue *pq, int index);

// Check if the priority queue is empty
bool isEmpty(PriorityQueue *pq);

// Display the heap in array order (NOT sorted)
void displayPQ(PriorityQueue *pq);

// Increase urgencyLevel of a call at index
void increaseUrgency(PriorityQueue *pq, int index, int newUrgency);

// Decrease urgencyLevel of a call at index
void decreaseUrgency(PriorityQueue *pq, int index, int newUrgency);

// Clear / reset the priority queue
void clearPQ(PriorityQueue *pq);


// =======================================================
//          FUNCTION HEADERS (NO LOGIC)
// =======================================================

// Initialize the priority queue
void initPQ(PriorityQueue *pq) {
    pq->size = -1;
}

// Insert an emergency call into the heap
void insertCall(PriorityQueue *pq, EmergencyCall call) {

    if (pq->size == MAXPQ -1) {
        printf("Queue is full!\n");
        return;
    }
    
    pq->size++;
    int child = pq->size;

    pq->heap[child] =  call;
    
    heapifyUp(pq, child);
  




}

// Return the highest-priority call (min)
// but DO NOT remove it
EmergencyCall peekCall(PriorityQueue *pq) {
    if (pq->size == -1) exit(1);
    return pq->heap[0];
}

// Remove and return the highest-priority call
EmergencyCall extractMin(PriorityQueue *pq) {

    if (pq->size == -1) exit(1);

    EmergencyCall root;
    root = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size];
    pq->size--;

    // heapifyUp(pq, pq->size);
    
    heapifyDown(pq, 0);
    //! always pass 0 as index, because it is heapify down, we 
    //! start at the parent

    return root;
}

// Heapify down (used after deletion)
void heapifyDown(PriorityQueue *pq, int index) {
    int pr, child;
    EmergencyCall swap;

    pr = index;
    child = pr * 2 +1;

    while (child <=pq->size) {

        if (child +1 <= pq->size && pq->heap[child+1].urgencyLevel < pq->heap[child].urgencyLevel) {
            child++;
        }

        if (pq->heap[pr].urgencyLevel > pq->heap[child].urgencyLevel) {
            swap = pq->heap[pr];
            pq->heap[pr] = pq->heap[child];
            pq->heap[child] = swap;

            pr = child;
            child = 2 * pr +1;
        } else {
            break;
        }
    }


}

// Heapify up (used after insertion)
void heapifyUp(PriorityQueue *pq, int index) {

    int child = index;
    int pr = (child - 1) / 2;


    while (child > 0 && pq->heap[pr].urgencyLevel > pq->heap[child].urgencyLevel ) {
        EmergencyCall swap = pq->heap[pr];
        pq->heap[pr] = pq->heap[child];
        pq->heap[child] = swap;

        child = pr;
        pr = (child - 1) / 2;


    }
}

// Check if empty
bool isEmpty(PriorityQueue *pq) {
    return pq->size == -1;
}

void displayPQ(PriorityQueue *pq) {
    printf("\n--- CURRENT PRIORITY QUEUE (heap order) ---\n");

    for (int i = 0; i <= pq->size; i++) {
        printf("[%d] Caller: %s | Location: %s | Urgency: %d | Time: %d\n",
               i,
               pq->heap[i].callerName,
               pq->heap[i].location,
               pq->heap[i].urgencyLevel,
               pq->heap[i].timestamp);
    }

    printf("-------------------------------------------\n");
}
// Extra operations for practice
void increaseUrgency(PriorityQueue *pq, int index, int newUrgency) {
   int oldUrgency = pq->heap[index].urgencyLevel;  // save old value
pq->heap[index].urgencyLevel = newUrgency;

if (newUrgency < oldUrgency) {       // more urgent → bubble up
    heapifyUp(pq, index);
} else if (newUrgency > oldUrgency) { // less urgent → bubble down
    heapifyDown(pq, index);
}

}

void clearPQ(PriorityQueue *pq) {
    pq->size = -1;
}


// =======================================================
//     MAIN DEMO (NO LOGIC INSIDE — YOU WILL FILL)
// =======================================================


int main() {

    PriorityQueue pq;
    initPQ(&pq);

    // Sample emergency calls
    EmergencyCall a = {"Maria Lopez", "Barangay 12", 1, 1001};
    EmergencyCall b = {"David Cruz", "North Avenue", 3, 1002};
    EmergencyCall c = {"Sarah Lim", "Eastwood", 2, 1003};

    // === INSERT SAMPLE CALLS ===
    insertCall(&pq, a);
    insertCall(&pq, b);
    insertCall(&pq, c);

    // === DISPLAY THE PQ STATE ===
    displayPQ(&pq);

    // === EXTRACT THE HIGHEST PRIORITY CALL ===
    EmergencyCall top = extractMin(&pq);

    printf("\nExtracted Call:\n");
    printf("Caller: %s | Location: %s | Urgency: %d | Time: %d\n",
           top.callerName,
           top.location,
           top.urgencyLevel,
           top.timestamp);

    // Display again after extraction
    displayPQ(&pq);



    // ------------------------------------------------------
    // TEST: Increase urgency of a lower-priority call
    // ------------------------------------------------------
    printf("\n== INCREASING URGENCY OF INDEX 2 (Sarah) TO 5 ==\n");
    increaseUrgency(&pq, 1, 5);

    displayPQ(&pq);

    // ------------------------------------------------------
    // Extract to confirm the heap is correct
    // ------------------------------------------------------
    printf("\n== EXTRACTING MIN (HIGHEST PRIORITY) ==\n");
    EmergencyCall top1 = extractMin(&pq);

    printf("Extracted: %s | Urgency: %d\n\n",
           top1.callerName, top1.urgencyLevel);

    displayPQ(&pq);

    return 0;
}
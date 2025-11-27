#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EVENTS 5

// ===========================================
//        EMERGENCY EVENT STRUCTURE
// ===========================================

typedef struct {
    int emergency_id;       // Unique emergency identifier
    int severity_level;     // Lower = more critical
    char *description;      // Dynamically allocated
} EmergencyEvent;


// ===========================================
//        PRIORITY QUEUE STRUCTURE
// ===========================================

typedef struct {
    EmergencyEvent *heap[MAX_EVENTS];  // Min-heap array
    int size;                          // Number of active events
} PriorityQueue;


// ===========================================
//     FUNCTION DECLARATIONS + PURPOSES
// ===========================================

// Initialize the priority queue
// Purpose: Set size to 0; prepare empty heap.
void initQueue(PriorityQueue *pq) {
    pq->size = -1;
}

// Create a new emergency event node
// Purpose: Allocate and populate event fields.
EmergencyEvent* create_event(int id, int severity, const char *desc) {

    EmergencyEvent* new = malloc(sizeof(EmergencyEvent));
    if (new == NULL) return NULL;

    new->emergency_id = id;
    new->severity_level = severity;
    new->description = malloc(strlen(desc)+1);
    strcpy(new->description, desc);

    return new;
}

void heapify_up(PriorityQueue *pq, int index);

// Insert event into min-heap priority queue (enqueue)
// Purpose: Add event at end, then bubble UP according to severity.
bool enqueue_event(PriorityQueue *pq, EmergencyEvent *event) {
    int child, pr;

    if (pq->size == MAX_EVENTS -1) return false;

    // pq->size++;
    // child = pq->size;
    // pr = (child -1)/2;

    // while (child > 0 && pq->heap[pr]->severity_level > event->severity_level) {
    //     pq->heap[child] = pq->heap[pr];
    //     child = pr;
    //     pr = (child-1)/2;
    // }

    // pq->heap[child] = event;


    //todo: if using a helper function, u need to do is to
    // todo: insert it first, then call

    pq->size++;
    child = pq->size;
    pq->heap[child] = event;

    heapify_up(pq, child);
    return true;

}


// Display all emergency events currently in the priority queue
// Purpose: Show index, ID, severity, and description (for tracing heap state).
void display_queue(PriorityQueue *pq) {

    if (pq->size == -1) {
        printf("\n[DISPLAY] Priority Queue is EMPTY.\n");
        return;
    }

    printf("\n[DISPLAY] Current Min-Heap State (index-order):\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i <= pq->size; i++) {
        printf("Index %d -> ID: %d | Severity: %d | Desc: %s\n",
               i,
               pq->heap[i]->emergency_id,
               pq->heap[i]->severity_level,
               pq->heap[i]->description
        );
    }

    printf("--------------------------------------------------\n");
}

// Peek at highest-priority event without removing
// Purpose: Return pointer to heap[0] if exists.
EmergencyEvent* peek_event(PriorityQueue *pq) {
    return pq->heap[0];
}

// Swap two event pointers inside the heap
// Purpose: Utility for percolation and tracing.
void swap_events(EmergencyEvent **a, EmergencyEvent **b) {
    EmergencyEvent* temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble-up operation after insertion
// Purpose: Move event upward until heap property satisfied.
void heapify_up(PriorityQueue *pq, int index) {
    int child, pr;
    EmergencyEvent* swap;

    // if (child < 0 ) return; 

    child = index;
    pr = (child -1)/2;

    while (child > 0 && pq->heap[pr]->severity_level > pq->heap[child]->severity_level) {
        swap = pq->heap[pr];
        pq->heap[pr] = pq->heap[child];
        pq->heap[child]=swap;

        child = pr;
        pr = (child-1)/2;
    }


}

void heapify_down(PriorityQueue *pq, int index);
// Remove highest-priority event (dequeue → min severity)
// Purpose: Return root (min), replace with last element, bubble DOWN.
EmergencyEvent* dequeue_event(PriorityQueue *pq) {
    EmergencyEvent* root, swap;
    
    if (pq->size == -1) return NULL;

    root = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size];
    pq->size--;

    heapify_down(pq, 0);
    return root;


}


// Bubble-down operation after removal
// Purpose: Restore min-heap structure from root downward.
void heapify_down(PriorityQueue *pq, int index) {
    

    int pr = index;
    int child = 2 * pr +1;
    

    EmergencyEvent* swap;

    
    while (child <= pq->size) {
        if (child+1 <= pq->size && pq->heap[child+1]->severity_level < pq->heap[child]->severity_level) {
            child++;
        }

        if (pq->heap[pr]->severity_level>pq->heap[child]->severity_level) {
            swap = pq->heap[pr];
            pq->heap[pr]= pq->heap[child];
            pq->heap[child]= swap;
            pr = child;

            child = 2*pr +1;

        }else {
            break;
        }
    }



}

// Free ALL events in the priority queue
// Purpose: Deallocate strings and event structs.
void free_all_events(PriorityQueue *pq) {
    
    for(int i = 0; i <= pq->size; i++) {
        free(pq->heap[i]->description);
        free(pq->heap[i]);
    }
    pq->size = -1;
}


// ===========================================
//                MAIN PROGRAM
// ===========================================

int main() {

    PriorityQueue pq;
    initQueue(&pq);

    printf("Interstellar Emergency Dispatch System (Min-Heap Priority Queue)\n");
    printf("---------------------------------------------------------------\n");

    // Initial Enqueue Tests
    // EVENTS ARE PURPOSEFULLY OUT OF ORDER TO CHALLENGE TRACING
    printf("\n[ENQUEUE] Emergency 301 (severity 9)\n");
    enqueue_event(&pq, create_event(301, 9, "Colony oxygen farm malfunction"));

    printf("[ENQUEUE] Emergency 112 (severity 3)\n");
    enqueue_event(&pq, create_event(112, 3, "Hull breach detected"));

    printf("[ENQUEUE] Emergency 420 (severity 15)\n");
    enqueue_event(&pq, create_event(420, 15, "Medical supply shortage"));

    printf("[ENQUEUE] Emergency 250 (severity 5)\n");
    enqueue_event(&pq, create_event(250, 5, "Radiation deck overload"));

    printf("[ENQUEUE] Emergency 199 (severity 1)\n");
    enqueue_event(&pq, create_event(199, 1, "Cryo-pod catastrophic failure"));

    // Challenge: Predict heap structure BEFORE running.
    // Good tracing practice.

    printf("[STATE] AFTER ALL ENQUEUES\n");
    display_queue(&pq);


    // Peek Test
    printf("\n[PEEK] Checking highest-priority emergency...\n");
    EmergencyEvent *top = peek_event(&pq);
    printf("Highest Priority [%d] | Desc: %s\n", top->severity_level, top->description);

    // Dequeue Tests (Heapify DOWN tracing challenge)
    printf("\n[DEQUEUE] Processing event...\n");
    EmergencyEvent *ev1 = dequeue_event(&pq);

    
    printf("[DEQUEUE] Processing event...\n");
    EmergencyEvent *ev2 = dequeue_event(&pq);

  printf("[STATE] AFTER DEQUEUES\n");
  display_queue(&pq);

    // Free all dynamic memory
    printf("\nCleaning up...\n");
    free_all_events(&pq);

    printf("Shutdown complete.\n");
    return 0;
}

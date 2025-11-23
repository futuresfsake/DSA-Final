//* initialize it as 1, so the count appears accurately
//* when it is initialized as 0, increment in the last part,
//* consider the bounds checking



//* in deleting
//**** we do pq->heap[0] = pq->heap[pq->size-1] , because we did 0 based indexing, that is to check the bounds*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_HEAP 10
#define MAX_STR 100

// ========================================
//        COMPLEX NESTED STRUCTS
// ========================================

// Optional victim data
typedef struct {
    int injuredCount;
    int criticalCount;
    bool requiresAmbulance;
} VictimData;

// Core emergency incident
typedef struct {
    int incidentID;
    char incidentType[MAX_STR];        // fire, medical, structural
    char location[MAX_STR];            // e.g., "Runway 3"
    int severity;                      // Priority (10 highest)
    char timestamp[MAX_STR];           // "2025-11-22 14:00"

    VictimData victims;                // Nested structure
} EmergencyIncident;

// ========================================
//         PRIORITY QUEUE STRUCTURE
// ========================================
typedef struct {
    EmergencyIncident heap[MAX_HEAP];
    int size;                          // Current number of items
} EmergencyPQ;


// ========================================
//       FUNCTION DECLARATIONS
// ========================================

// ----------- CORE OPERATIONS ------------
void initPQ(EmergencyPQ* pq) {
    pq->size = 0;
}

bool isEmpty(EmergencyPQ* pq) {
    return pq->size == 0;
}
bool isFull(EmergencyPQ* pq) {
    return pq->size == MAX_HEAP;
}

// Insert new incident
void pqInsert(EmergencyPQ* pq, EmergencyIncident item) {

    int child, pr;

    if (pq->size == MAX_HEAP) return;

    
    child = pq->size;
    pr = (child-1) /2;
    pq->size++;

    while (child > 0 && pq->heap[pr].severity < item.severity) {
        pq->heap[child] = pq->heap[pr];
        child = pr;
        pr = (child-1) /2;
    }

    pq->heap[child] = item;




}

// Remove highest priority (max severity)
EmergencyIncident pqRemoveMax(EmergencyPQ* pq) {

    int pr, child;
    EmergencyIncident swap;
    EmergencyIncident root;


    if (isEmpty(pq)) exit(1);

    root = pq->heap[0];
    //* check for out of bounds
    pq->heap[0] = pq->heap[pq->size-1];
    pq->size--;

    pr = 0;
    child = 1;

    while (child < pq->size) {

        if (child +1 < pq->size && pq->heap[child+1].severity > pq->heap[child].severity) {
            child++;
        }

        if (pq->heap[pr].severity < pq->heap[child].severity) {
            swap = pq->heap[pr];
            pq->heap[pr] = pq->heap[child];
            pq->heap[child] = swap;

            pr = child;
            child = 2 * pr +1;
        } else {
            break;
        }
    }
    return root;
}

// Peek highest priority incident (no remove)
EmergencyIncident pqGetMax(EmergencyPQ* pq) {
    return pq->heap[0];
}

// Restore heap upward
void heapifyUp(EmergencyPQ* pq, int index) {

    int child = index;
    int pr = (child -1)/2;
    EmergencyIncident swap;

    while (child <pq->size && pq->heap[pr].severity < pq->heap[child].severity) {
        swap = pq->heap[pr];
        pq->heap[pr] = pq->heap[child];
        pq->heap[child] = swap;

        child = pr;
        pr = (child-1) /2;

    }
}

// Restore heap downward
void heapifyDown(EmergencyPQ* pq, int index) {

    int pr = index;
    int child = pr * 2 +1;

    while (child < pq->size) {
        if (child +1 < pq->size && pq->heap[child+1].severity > pq->heap[child].severity) {
            child++;
        }

        if (pq->heap[pr].severity < pq->heap[child].severity) {
            EmergencyIncident swap = pq->heap[pr];
            pq->heap[pr] = pq->heap[child];
            pq->heap[child] = swap;

            pr = child;
            child = pr * 2+1;
        } else {
            break;
        }
    }

}

void pqDisplay(EmergencyPQ* pq) {
    if (isEmpty(pq)) {
        printf("Priority Queue is empty.\n");
        return;
    }

    printf("Size: %d\n", pq->size);
    printf("-----------------------------\n");

    for (int i = 0; i < pq->size; i++) {
        EmergencyIncident e = pq->heap[i];
        printf("Incident ID: %d\n", e.incidentID);
        printf("Type: %s\n", e.incidentType);
        printf("Location: %s\n", e.location);
        printf("Severity: %d\n", e.severity);
        printf("Timestamp: %s\n", e.timestamp);
        printf("Victims - Injured: %d, Critical: %d, Ambulance Required: %s\n",
               e.victims.injuredCount, e.victims.criticalCount,
               e.victims.requiresAmbulance ? "Yes" : "No");
        printf("-----------------------------\n");
    }
}

// ----------- COMMON EXTRA OPERATIONS ------------

// 1️⃣ Increase severity of an incident
void increaseSeverity(EmergencyPQ* pq, int incidentID, int amount) {
    for(int i = 0; i < MAX_HEAP; i++) {
        if (pq->heap[i].incidentID == incidentID) {
            pq->heap[i].severity += amount;
            heapifyUp(pq, i);
            break;
        }
    }
}


// 3️⃣ Search incident by ID
EmergencyIncident* pqSearch(EmergencyPQ* pq, int incidentID) {

    for(int i = 0; i < MAX_HEAP; i++) {
        if (pq->heap[i].incidentID == incidentID) {
            return &(pq->heap[i]);
        }
    }
    return NULL;
}

// 4️⃣ Delete a specific incident by ID
bool pqDeleteByID(EmergencyPQ* pq, int incidentID) {
    int index = -1;
    for(int i = 0; i < pq->size; i++) {
        if (pq->heap[i].incidentID == incidentID) {
            index = i;
            break;
        }
    }

    if (index == -1) return false;


//! replace with the last element
//* pq->size -1, checking for bounds, since we used 0based index
    pq->heap[index] = pq->heap[pq->size-1];
    pq->size--;
    

    heapifyUp(pq, index);
    heapifyDown(pq, index);
    return true;
}



int main() {
    EmergencyPQ pq;
    initPQ(&pq);

    // Sample incidents
    EmergencyIncident a = {101, "Fire", "Runway 3", 8, "2025-11-22 14:00", {2, 1, true}};
    EmergencyIncident b = {102, "Medical", "Hangar 5", 5, "2025-11-22 14:15", {0, 2, true}};
    EmergencyIncident c = {103, "Structural", "Terminal 2", 9, "2025-11-22 14:30", {1, 0, false}};
    EmergencyIncident d = {104, "Fire", "Runway 3", 7, "2025-11-22 15:00", {3, 1, true}};
    EmergencyIncident e = {105, "Medical", "Terminal 1", 6, "2025-11-22 15:30", {0, 0, false}};

    // Insert incidents into PQ
    pqInsert(&pq, a);
    pqInsert(&pq, b);
    pqInsert(&pq, c);
    pqInsert(&pq, d);
    pqInsert(&pq, e);

    // Display the queue
    printf("\n=== Emergency Priority Queue ===\n");
    pqDisplay(&pq);

    // Peek highest severity incident
    EmergencyIncident maxIncident = pqGetMax(&pq);
    printf("\nHighest severity incident: ID %d, Type: %s, Severity: %d\n", 
            maxIncident.incidentID, maxIncident.incidentType, maxIncident.severity);

    // Search for an incident by ID
    int searchID = 104;
    EmergencyIncident* found = pqSearch(&pq, searchID);
    if (found) {
        printf("\nIncident %d found: Type: %s, Location: %s\n", 
                found->incidentID, found->incidentType, found->location);
    } else {
        printf("\nIncident %d not found.\n", searchID);
    }

    // Increase severity of an incident
    increaseSeverity(&pq, 102, 4); // ID 102 severity increases by 4
    printf("\nAfter increasing severity of incident 102:\n");
    pqDisplay(&pq);

    if (pqDeleteByID(&pq, 105)) { 
     printf("\nIncident 105 deleted successfully.\n"); 
      } else { printf("\nIncident 105 not found.\n");  }
       pqDisplay(&pq);
 

   
   

    // Clean up (optional for static array PQ)
    return 0;
}

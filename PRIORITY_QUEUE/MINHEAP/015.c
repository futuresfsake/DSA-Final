#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SHIPS 12
#define NAME_LEN 50

/*
    ======================================================
        ORION SPACEPORT – DOCKING QUEUE PRIORITY SYSTEM
    ------------------------------------------------------
    Docking requests are processed based on priority:
        - lower number = higher priority
    ======================================================
*/

typedef struct {
    int shipID;
    char shipName[NAME_LEN];
    int priorityLevel; // 1 = emergency, 10 = normal
} DockingRequest;

typedef struct {
    DockingRequest queue[MAX_SHIPS];
    int count; // number of elements in the heap
} DockingQueue;

// =================== FUNCTION PROTOTYPES ===================

// Core operations
void initQueue(DockingQueue *dq);
bool insertDockingRequest(DockingQueue *dq, DockingRequest dr);
bool removeHighestPriority(DockingQueue *dq, DockingRequest *removed);
bool updatePriority(DockingQueue *dq, int shipID, int newPriority);
bool searchShip(DockingQueue *dq, int shipID);
void displayQueue(DockingQueue *dq);

// Extra helper functions
DockingRequest peekHighestPriority(DockingQueue *dq);
bool isQueueFull(DockingQueue *dq);
bool isQueueEmpty(DockingQueue *dq);
int getParentIndex(int i);
int getLeftChildIndex(int i);
int getRightChildIndex(int i);
void swapShips(DockingRequest *a, DockingRequest *b);
void bubbleUp(DockingQueue *dq, int index);
void bubbleDown(DockingQueue *dq, int index);
int countShips(DockingQueue *dq);
void heapSort (DockingQueue* dq);


// =================== MAIN TESTER ===================
int main() {
    DockingQueue dq;
    initQueue(&dq);

    DockingRequest d1 = {301, "Star Voyager", 5};
    DockingRequest d2 = {302, "Galactic Falcon", 2};
    DockingRequest d3 = {303, "Nebula Runner", 1};
    DockingRequest d4 = {304, "Cosmo Cruiser", 4};
    DockingRequest d5 = {305, "Solar Hawk", 3};

    printf("\n=== INSERTING DOCKING REQUESTS ===\n");
    insertDockingRequest(&dq, d1);
    insertDockingRequest(&dq, d2);
    insertDockingRequest(&dq, d3);
    insertDockingRequest(&dq, d4);
    insertDockingRequest(&dq, d5);
    displayQueue(&dq);

    printf("\n=== PEEK HIGHEST PRIORITY ===\n");
    DockingRequest top = peekHighestPriority(&dq);
    printf("Next Ship: %d (%s) Priority: %d\n", top.shipID, top.shipName, top.priorityLevel);

    printf("\n=== REMOVE HIGHEST PRIORITY ===\n");
    DockingRequest removed;
    removeHighestPriority(&dq, &removed);
    printf("Removed Ship: %d (%s) Priority: %d\n", removed.shipID, removed.shipName, removed.priorityLevel);
    displayQueue(&dq);
    printf("\n=== UPDATE PRIORITY (Ship 304 -> Priority 1) ===\n");
    updatePriority(&dq, 304, 1);
    displayQueue(&dq);

    printf("\n=== SEARCH FOR Ship 305 ===\n");
    bool found = searchShip(&dq, 305);
    if (found) {
        printf("Ship 305 was found in the queue.\n");
    } else {
        printf("Ship 305 was not found in the queue.\n");
    }

    printf("\n=== QUEUE STATUS CHECKS ===\n");
    printf("Queue empty? %s\n", isQueueEmpty(&dq) ? "Yes" : "No");
    printf("Queue full? %s\n", isQueueFull(&dq) ? "Yes" : "No");
    printf("Number of ships: %d\n", countShips(&dq));

    printf("\n=== HELPER FUNCTIONS TEST ===\n");
    printf("Parent index of 2: %d\n", getParentIndex(2));
    printf("Left child of 0: %d\n", getLeftChildIndex(0));
    printf("Right child of 0: %d\n", getRightChildIndex(0));

    printf("\n=== HEAP SORT TEST ===\n");
    heapSort(&dq);
    displayQueue(&dq);

    return 0;

    return 0;
}

void initQueue(DockingQueue *dq) {

    dq->count = -1;
}
bool insertDockingRequest(DockingQueue *dq, DockingRequest dr) {
    int child, pr;
    if (dq->count == MAX_SHIPS -1) return false;

    dq->count++;
    child = dq->count;
    pr = (child-1)/2;

    while (child > 0 && dq->queue[pr].priorityLevel> dr.priorityLevel) {
        dq->queue[child] = dq->queue[pr];
        child = pr;
        pr = (child-1)/2;
    }

    dq->queue[child] = dr;

}
bool removeHighestPriority(DockingQueue *dq, DockingRequest *removed) {
    
    int child, pr;
    DockingRequest swap;

    if (dq->count == -1) return false;

    *removed = dq->queue[0];
    dq->queue[0] = dq->queue[dq->count];
    dq->count--;

    pr = 0;
    child = 2 * pr+1;

    while (child <= dq->count) {
        if (child+1 <= dq->count && dq->queue[child+1].priorityLevel < dq->queue[child].priorityLevel) {
            child++;
        }
        if (dq->queue[pr].priorityLevel > dq->queue[child].priorityLevel) {
            swap = dq->queue[pr];
            dq->queue[pr] = dq->queue[child];
            dq->queue[child] = swap;

            pr = child;
            child = 2 *pr+1;
        } else {
            break;
        }
    }
    return true;
}
bool updatePriority(DockingQueue *dq, int shipID, int newPriority) {

    for(int i = 0; i <= dq->count; i++) {
        if (dq->queue[i].shipID == shipID) {
            int temp = dq->queue[i].priorityLevel;
            dq->queue[i].priorityLevel = newPriority;

            if (temp < newPriority) {
                bubbleUp(dq, i);
            } else {
                bubbleDown(dq, 0);
            }


            return true;
        }
    }

    return false;
}
bool searchShip(DockingQueue *dq, int shipID) {

    DockingQueue temp;
    initQueue(&temp);

    int found = -1;
    while (dq->count != -1) {

        DockingRequest b;
        removeHighestPriority(dq, &b);
        if (b.shipID == shipID) {
            found = 1;
            
        }
        insertDockingRequest(&temp, b);
    }


    while (temp.count != -1) {
        DockingRequest b;
        removeHighestPriority(&temp, &b);
        insertDockingRequest(dq, b);
    }

    return found;

}
void displayQueue(DockingQueue *dq) {
    if (dq->count == -1) {
        printf("The docking queue is empty.\n");
        return;
    }

    printf("Index | ShipID | Ship Name          | Priority\n");
    printf("------------------------------------------------\n");
    for (int i = 0; i <= dq->count; i++) {
        printf("%5d | %6d | %-18s | %8d\n",
               i,
               dq->queue[i].shipID,
               dq->queue[i].shipName,
               dq->queue[i].priorityLevel);
    }
}


DockingRequest peekHighestPriority(DockingQueue *dq) {
    if (dq->count == -1) exit(1);
    return dq->queue[0];
}

bool isQueueFull(DockingQueue *dq) {

    return dq->count == MAX_SHIPS -1;
}

bool isQueueEmpty(DockingQueue *dq) {
    return dq->count == -1;
}

int getParentIndex(int i) {
    if (i >MAX_SHIPS-1 || i <0) return -1;
    int child = i;

    return (child-1)/2;
}

int getLeftChildIndex(int i) {
      if (i >MAX_SHIPS-1 || i <0) return -1;

      return 2 * i +1;

}

int getRightChildIndex(int i) {
    if (i >MAX_SHIPS-1 || i <0) return -1;

      return 2 * i +2;

}


void swapShips(DockingRequest *a, DockingRequest *b) {
    DockingRequest temp = *a;
    *a = *b;
    *a = temp;
}


void bubbleUp(DockingQueue *dq, int index) {

    int child, pr;

    child = index;
    pr = (child-1)/2;

    while (child > 0 && dq->queue[pr].priorityLevel > dq->queue[child].priorityLevel) {
        DockingRequest swap = dq->queue[pr];
        dq->queue[pr] = dq->queue[child];
        dq->queue[child] = swap;

        child = pr;
        pr = (child-1)/2;
    }


}

void bubbleDown(DockingQueue *dq, int index) {

    

    int pr = index;
    int child = 2 * pr +1;


    while (child <= dq->count) {
        if (child+1 <= dq->count && dq->queue[child+1].priorityLevel < dq->queue[child].priorityLevel) {
            child++;
        }
        if (dq->queue[pr].priorityLevel > dq->queue[child].priorityLevel) {
            DockingRequest swap = dq->queue[pr];
            dq->queue[pr] = dq->queue[child];
            dq->queue[child]=swap;

            pr= child;
            child = 2 * pr+1;
        } else {
            break;
        }
    }
}



int countShips(DockingQueue *dq) {
    return dq->count+1;
}

void heapSort (DockingQueue* dq) {
    int orig;

    orig = dq->count;
    dq->count = -1;

    for(int i = 0; i <=orig; i++) {
        insertDockingRequest(dq, dq->queue[i]);
    }

    for(int i = orig; i >= 0; i--) {
        DockingRequest b;
        removeHighestPriority(dq, &b);
        insertDockingRequest(dq, b);
    }

    dq->count = orig;
}

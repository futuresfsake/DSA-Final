#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SHIPS 20
#define NAME_LEN 50

/*
    ======================================================
        INTERSTELLAR AIRPORT – RUNWAY LANDING QUEUE
    ------------------------------------------------------
    Ships are queued for landing based on priority:
        - lower number = higher priority
    Iterative operations:
        - insertLandingRequest
        - removeHighestPriority
        - updatePriority
        - searchShip
        - displayQueue
    ======================================================
*/

typedef struct {
    int shipID;
    char shipName[NAME_LEN];
    int priorityLevel; // 1 = emergency, 10 = routine
} LandingRequest;

typedef struct {
    LandingRequest queue[MAX_SHIPS];
    int count;
} RunwayQueue;

// ================== PROTOTYPES ==================
void initQueue(RunwayQueue *rq);
bool insertLandingRequest(RunwayQueue *rq, LandingRequest lr);
bool removeHighestPriority(RunwayQueue *rq, LandingRequest *removed);
int searchShip(RunwayQueue *rq, int shipID);
bool updatePriority(RunwayQueue *rq, int shipID, int newPriority);
void displayQueue(RunwayQueue *rq);

// ================== MAIN TESTER ==================
int main() {
    RunwayQueue rq;
    initQueue(&rq);

    LandingRequest l1 = {501, "Starliner", 4};
    LandingRequest l2 = {502, "Nebula Express", 2};
    LandingRequest l3 = {503, "Cosmic Voyager", 1};
    LandingRequest l4 = {504, "Galaxy Rider", 3};
    LandingRequest l5 = {505, "Solar Falcon", 5};

    insertLandingRequest(&rq, l1);
    insertLandingRequest(&rq, l2);
    insertLandingRequest(&rq, l3);
    insertLandingRequest(&rq, l4);
    insertLandingRequest(&rq, l5);

    printf("\n=== INITIAL LANDING QUEUE ===\n");
    displayQueue(&rq);

    printf("\n=== REMOVE HIGHEST PRIORITY SHIP ===\n");
    LandingRequest removed;
    removeHighestPriority(&rq, &removed);
    printf("Removed Ship: %d (%s) Priority: %d\n",
           removed.shipID, removed.shipName, removed.priorityLevel);
    displayQueue(&rq);

    printf("\n=== UPDATE PRIORITY (Ship 505 -> Priority 1) ===\n");
    updatePriority(&rq, 505, 1);
    displayQueue(&rq);

    printf("\n=== SEARCH FOR Ship 504 ===\n");
    int idx = searchShip(&rq, 504);
    if (idx != -1) {
        printf("Found at index %d: %s Priority %d\n",
               idx, rq.queue[idx].shipName, rq.queue[idx].priorityLevel);
    } else {
        printf("Ship not found.\n");
    }

    return 0;
}


void initQueue(RunwayQueue *rq) {
    

    rq->count = -1;
}
bool insertLandingRequest(RunwayQueue *rq, LandingRequest lr) {
    int child, pr;

    if (rq->count == MAX_SHIPS-1) return false;

    rq->count++;
    child = rq->count;
    pr = (child-1)/2;

    while (child > 0 && rq->queue[pr].priorityLevel > lr.priorityLevel) {
        rq->queue[child] = rq->queue[pr];
        child = pr;
        pr = (child-1)/2;
        
    }
    rq->queue[child] = lr;
    return true;
}
bool removeHighestPriority(RunwayQueue *rq, LandingRequest *removed) {

    int child, pr;
    LandingRequest swap;

    if (rq->count == -1) return false;

    *removed = rq->queue[0];
    rq->queue[0] = rq->queue[rq->count];
    rq->count--;


    pr = 0;
    child = pr * 2 +1;

    while (child <= rq->count) {
        if (child+1 <= rq->count && rq->queue[child+1].priorityLevel < rq->queue[child].priorityLevel) {
            child++;
        }
        if (rq->queue[pr].priorityLevel > rq->queue[child].priorityLevel) {
            swap = rq->queue[pr];
            rq->queue[pr] = rq->queue[child];
            rq->queue[child] = swap;

            pr = child;
            child = 2 * pr +1;

        } else {
            break;
        }
    }

}
int searchShip(RunwayQueue *rq, int shipID) {
    for(int i = 0; i <= rq->count; i++) {
        if (rq->queue[i].shipID == shipID) {
            return i;
        }
    }
    return -1;
}
bool updatePriority(RunwayQueue *rq, int shipID, int newPriority) {
    int index = -1;
    for(int i = 0; i < rq->count; i++) {
        if (rq->queue[i].shipID == shipID) {
            index = i;
            rq->queue[i].priorityLevel = newPriority;
            break;
        }

    }


    if (index != -1) {

        int pr;
        int child;
        LandingRequest swap;
        int down;

        pr = (rq->count-1)/2;

        while (pr >= 0) {
            down = pr;
            child = 2 * down +1;

            while (child <= rq->count) {
                if (child+1 <= rq->count && rq->queue[child+1].priorityLevel < rq->queue[child].priorityLevel) {
                    child++;
                }if (rq->queue[down].priorityLevel > rq->queue[child].priorityLevel) {
                    LandingRequest swap = rq->queue[down];
                    rq->queue[down] = rq->queue[child];
                    rq->queue[child] = swap;

                    down = child;
                    child = 2 * down+1;
                } else {
                    break;
                }
            }
            pr--;
        }
        


    }

}
void displayQueue(RunwayQueue *rq) {
    if (rq->count == 0) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Index | Ship ID | Ship Name          | Priority\n");
    printf("-----------------------------------------------\n");

    for (int i = 0; i <=rq->count; i++) {
        printf("%-5d | %-7d | %-18s | %d\n",
               i,
               rq->queue[i].shipID,
               rq->queue[i].shipName,
               rq->queue[i].priorityLevel);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ROBOTS 15
#define NAME_LEN 50

/*
    ======================================================
        TITAN ROBOTICS FACTORY – MAINTENANCE QUEUE
    ------------------------------------------------------
    Robots are maintained based on priority:
        - lower number = more urgent
    Operations (iterative):
        - insertRobot
        - removeHighestPriority
        - updatePriority
        - searchRobot
        - displayQueue
    ======================================================
*/

typedef struct {
    int robotID;
    char model[NAME_LEN];
    int priorityLevel; // 1 = critical, 10 = minor
} Robot;

typedef struct {
    Robot queue[MAX_ROBOTS];
    int count;
} MaintenanceQueue;

// ================== PROTOTYPES ==================
void initQueue(MaintenanceQueue *mq);
bool insertRobot(MaintenanceQueue *mq, Robot r);
bool removeHighestPriority(MaintenanceQueue *mq, Robot *removed);
int searchRobot(MaintenanceQueue *mq, int robotID);
bool updatePriority(MaintenanceQueue *mq, int robotID, int newPriority);
void displayQueue(MaintenanceQueue *mq);
void heapifyDown(MaintenanceQueue *mq);

// ================== MAIN TESTER ==================
int main() {
    MaintenanceQueue mq;
    initQueue(&mq);

    Robot r1 = {401, "XR-Alpha", 3};
    Robot r2 = {402, "XR-Beta", 1};
    Robot r3 = {403, "XR-Gamma", 5};
    Robot r4 = {404, "XR-Delta", 2};
    Robot r5 = {405, "XR-Omega", 4};

    insertRobot(&mq, r1);
    insertRobot(&mq, r2);
    insertRobot(&mq, r3);
    insertRobot(&mq, r4);
    insertRobot(&mq, r5);

    printf("\n=== INITIAL MAINTENANCE QUEUE ===\n");
    displayQueue(&mq);

    printf("\n=== REMOVE HIGHEST PRIORITY ROBOT ===\n");
    Robot removed;
    removeHighestPriority(&mq, &removed);
    printf("Removed Robot: %d (%s) Priority: %d\n",
           removed.robotID, removed.model, removed.priorityLevel);
    displayQueue(&mq);


    return 0;
}

void initQueue(MaintenanceQueue *mq) {
    mq->count = -1;
}

bool insertRobot(MaintenanceQueue *mq, Robot r) {
    int child, pr;

    if (mq->count == MAX_ROBOTS-1) return false;
    
    mq->count++;
    child =mq->count;
    pr = (child-1)/2;

    while (child > 0 && mq->queue[pr].priorityLevel> r.priorityLevel) {
        mq->queue[child] = mq->queue[pr];
        child = pr;
        pr = (child-1)/2;
    }

    mq->queue[child] = r;
    return true;

}
bool removeHighestPriority(MaintenanceQueue *mq, Robot *removed) {
    int child, pr;
    if (mq->count == -1) return false;

    *removed = mq->queue[0];
    mq->queue[0] = mq->queue[mq->count];
    mq->count--;

    pr = 0;
    child = 2 * pr +1;

    while (child <= mq->count) {
        if (child+1 <= mq->count && mq->queue[child+1].priorityLevel<mq->queue[child].priorityLevel) {
            child++;
        }
        if (mq->queue[pr].priorityLevel > mq->queue[child].priorityLevel) {
            Robot swap = mq->queue[pr];
            mq->queue[pr] = mq->queue[child];
            mq->queue[child] = swap;

            pr = child;
            child = 2 * pr+1;

        } else {
            break;
        }
    }
  
}
void displayQueue(MaintenanceQueue *mq) {
    if (mq->count == -1) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Index | RobotID | Model        | Priority\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i <= mq->count; i++) {
        printf("%5d | %7d | %-12s | %d\n",
               i,
               mq->queue[i].robotID,
               mq->queue[i].model,
               mq->queue[i].priorityLevel);
    }
}



void heapifyDown(MaintenanceQueue *mq) {
    int child, pr;
    int down;

    if (mq->count == -1) return;

    pr = (mq->count-1)/2;

    while (pr > 0) {
        down = pr;
        child = 2* pr +1;

        while (child <= mq->count) {
            if (child+1 <= mq->count && mq->queue[child+1].priorityLevel < mq->queue[child].priorityLevel) {
                child++;
            }
            if (mq->queue[down].priorityLevel > mq->queue[child].priorityLevel) {
                Robot swap = mq->queue[pr];
                mq->queue[pr] = mq->queue[child];
                mq->queue[child] = swap;

                down = child;
                child = 2 * down +1;
            } else {
                break;
            }
        }
        pr--;
    }

}
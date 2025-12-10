#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TASKS 20
#define NAME_LEN 50

/*
    ======================================================
        CYBERCITY – ROBOT TASK SCHEDULER
    ------------------------------------------------------
    The city manages robot tasks in a min-heap priority queue.
    Tasks with lower priority numbers are handled first.

    PRIORITY RULE:
        - Lower number = higher urgency
        - 1 = Critical task
        - 10 = Normal task

    OPERATIONS:
        ✔ initQueue
        ✔ insertTask
        ✔ removeHighestPriority
        ✔ updatePriority
        ✔ searchTask
        ✔ displayQueue

    SPECIAL FUNCTION:
        ✔ minHeapify(int pq[], int size, int index)
*/

typedef struct {
    int taskID;
    char description[NAME_LEN];
    int priority;
} RobotTask;

typedef struct {
    RobotTask tasks[MAX_TASKS];
    int count;
} TaskQueue;

// ================== FUNCTION PROTOTYPES ==================

void initQueue(TaskQueue *tq);
bool insertTask(TaskQueue *tq, RobotTask t);
bool removeHighestPriority(TaskQueue *tq, RobotTask *removed);
bool updatePriority(TaskQueue *tq, int taskID, int newPriority);
int searchTask(TaskQueue *tq, int taskID);
void displayQueue(TaskQueue *tq);

void minHeapify(TaskQueue *tq);

// ================== MAIN TESTER ==================

int main() {
    TaskQueue tq;
    initQueue(&tq);

    RobotTask t1 = {201, "Repair power grid", 4};
    RobotTask t2 = {202, "Deliver medical supplies", 2};
    RobotTask t3 = {203, "Inspect bridges", 5};
    RobotTask t4 = {204, "Clear debris", 3};
    RobotTask t5 = {205, "Patrol city streets", 1};

    printf("\n=== ADD TASKS ===\n");
    insertTask(&tq, t1);
    insertTask(&tq, t2);
    insertTask(&tq, t3);
    insertTask(&tq, t4);
    insertTask(&tq, t5);
    displayQueue(&tq);

    printf("\n=== NEXT TASK TO EXECUTE ===\n");
    printf("Task %d (%s) Priority: %d\n", tq.tasks[0].taskID, tq.tasks[0].description, tq.tasks[0].priority);

    printf("\n=== REMOVE HIGHEST PRIORITY ===\n");
    RobotTask removed;
    removeHighestPriority(&tq, &removed);
    printf("Executed: %d (%s) Priority: %d\n", removed.taskID, removed.description, removed.priority);
    displayQueue(&tq);

    printf("\n=== UPDATE PRIORITY (Task 203 -> Priority 1) ===\n");
    updatePriority(&tq, 203, 1);
    displayQueue(&tq);

    printf("\n=== SEARCH Task 204 ===\n");
    int idx = searchTask(&tq, 204);
    if (idx != -1)
        printf("Found at index %d: %s Priority %d\n", idx, tq.tasks[idx].description, tq.tasks[idx].priority);
    else
        printf("Task not found.\n");

        
    minHeapify(&tq);

    printf("\n=== TASK QUEUE AFTER MINHEAPIFY ===\n");
    displayQueue(&tq);

    return 0;
}


void initQueue(TaskQueue *tq) {
    tq->count = -1;
}
bool insertTask(TaskQueue *tq, RobotTask t) {

    int child, pr;

    if (tq->count == MAX_TASKS-1) return false;

    tq->count++;
    child = tq->count;
    pr = (child-1)/2;

    while (child > 0 && tq->tasks[pr].priority > t.priority) {
        tq->tasks[child] = tq->tasks[pr];
        child = pr;
        pr = (child-1)/2;

    }


    tq->tasks[child] = t;

    return true;


}
bool removeHighestPriority(TaskQueue *tq, RobotTask *removed) {
    if (tq->count == -1) return false;


    int child, pr;

    *removed = tq->tasks[0];
    tq->tasks[0] = tq->tasks[tq->count];
    tq->count--;

    pr = 0;
    child = 2 * pr +1;


    while (child <= tq->count) {
        if (child+1 <= tq->count && tq->tasks[child+1].priority < tq->tasks[child].priority) {
            child++;
        }

        if (tq->tasks[pr].priority > tq->tasks[child].priority) {
            RobotTask swap = tq->tasks[pr];
            tq->tasks[pr] = tq->tasks[child];
            tq->tasks[child] = swap;

            pr = child;
            child = 2 * pr +1;
        } else {
            break;
        }
    }
    return true;
}


bool updatePriority(TaskQueue *tq, int taskID, int newPriority) {
    for(int i = 0; i <= tq->count; i++) {
        if (tq->tasks[i].taskID == taskID) {
            tq->tasks[i].priority = newPriority;
            minHeapify(tq);
            return true;
        }
    }

    return false;
}
int searchTask(TaskQueue *tq, int taskID) {
     for(int i = 0; i <= tq->count; i++) {
        if (tq->tasks[i].taskID == taskID) {
          
            return i;
        }
    }
    return -1;

}


void displayQueue(TaskQueue *tq) {
    for(int i = 0; i <= tq->count; i++) {
        printf("Priority: %d | ID: %d   \n", tq->tasks[i].priority, tq->tasks[i].taskID);
    }
}

void minHeapify(TaskQueue *tq) {




    int pr = (tq->count -1)/2;


    while (pr >= 0) {

        int down = pr;
        int child = 2 * pr +1;


        while (child <= tq->count) {
            if (child+1 <= tq->count && tq->tasks[child+1].priority < tq->tasks[child].priority) {
                child++;
            }


            if (tq->tasks[down].priority > tq->tasks[child].priority) {
                RobotTask swap = tq->tasks[down];
                tq->tasks[down] = tq->tasks[child];
                tq->tasks[child] = swap;

                down = child;
                child = 2 * down +1;


            } else {
                break;
            }
        }
        pr--;
    }
}
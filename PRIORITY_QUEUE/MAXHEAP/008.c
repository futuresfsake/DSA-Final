#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TASKS 50
#define NAME_LEN 50

/*
    Space Station Maintenance Task Queue (Max-Heap)

    Backstory:
    ----------------
    In a massive orbital station, maintenance tasks must be scheduled
    based on urgency. Each task has a Name, CriticalityScore (priority key),
    and Module (location in the station).

    Higher CriticalityScore means the task is more urgent and should
    be handled first.

    All queue operations must be iterative. Only the root of the heap
    can be dequeued at a time to simulate strict priority discipline.
*/

// ================================
// Task Struct
// ================================
typedef struct {
    char name[NAME_LEN];
    int criticalityScore;       // higher = higher priority
    char module[NAME_LEN];
} Task;

// ================================
// Max-Heap Struct
// ================================
typedef struct {
    Task heap[MAX_TASKS];
    int size;                   // last index used, initialize to -1
} TaskQueue;

void initTaskQueue(TaskQueue *tq);
bool isTaskQueueEmpty(TaskQueue *tq);
void enqueueTask(TaskQueue *tq, Task t);
Task dequeueTask(TaskQueue *tq);
Task peekTopTask(TaskQueue *tq);
void heapifyTaskQueue(TaskQueue *tq);
bool findTaskByNameDiscipline(TaskQueue *tq, const char *name);
void displayTaskQueue(TaskQueue *tq);
int totalTasks(TaskQueue *tq);
void clearTaskQueue(TaskQueue *tq);


int main() {

    TaskQueue tq;
    initTaskQueue(&tq);

    printf("\n=== SPACE STATION MAINTENANCE TASK QUEUE TEST ===\n");

    // -----------------------------------------
    // Create sample tasks
    // -----------------------------------------
    Task t1 = {"Air Filter Replacement", 50, "Life Support"};
    Task t2 = {"Solar Panel Alignment", 90, "Energy Module"};
    Task t3 = {"Hull Breach Inspection", 100, "Outer Hull"};
    Task t4 = {"Communications Check", 60, "Comm Module"};
    Task t5 = {"Cooling System Repair", 80, "Engine Module"};

    printf("\n[TEST] Enqueuing tasks...\n");
    enqueueTask(&tq, t1);
    enqueueTask(&tq, t2);
    enqueueTask(&tq, t3);
    enqueueTask(&tq, t4);
    enqueueTask(&tq, t5);

    printf("\n[STATE] Current Max-Heap:\n");
    displayTaskQueue(&tq);

    // -----------------------------------------
    // Peek Test
    // -----------------------------------------
    printf("\n[TEST] Peeking at top priority task...\n");
    Task top = peekTopTask(&tq);
    printf("TOP: %s | Criticality %d | Module: %s\n",
           top.name, top.criticalityScore, top.module);

    // -----------------------------------------
    // Dequeue Test
    // -----------------------------------------
    printf("\n[TEST] Dequeuing highest priority task...\n");
    Task removed = dequeueTask(&tq);
    printf("Dequeued: %s | Criticality %d | Module: %s\n",
           removed.name, removed.criticalityScore, removed.module);

    printf("\n[STATE] Heap after dequeue:\n");
    displayTaskQueue(&tq);

    // -----------------------------------------
    // Search Test (Strict PQ Discipline)
    // -----------------------------------------
    printf("\n[TEST] Searching for \"Cooling System Repair\"...\n");

    if (findTaskByNameDiscipline(&tq, "Cooling System Repair"))
        printf("Result: FOUND (under PQ rules)\n");
    else
        printf("Result: NOT FOUND (root only access)\n");

    // -----------------------------------------
    // Total Count Test
    // -----------------------------------------
    printf("\n[TEST] Total tasks left: %d\n", totalTasks(&tq));

    // -----------------------------------------
    // Heapify Test
    // (demonstrate rebuilding heap from arbitrary order)
    // -----------------------------------------
    printf("\n[TEST] Rebuilding heap using heapifyTaskQueue()...\n");

    // scramble internal heap to simulate disorder
    Task temp = tq.heap[0];
    tq.heap[0] = tq.heap[2];
    tq.heap[2] = temp;

    printf("[STATE] Before heapify:\n");
    displayTaskQueue(&tq);

    heapifyTaskQueue(&tq);

    printf("[STATE] After heapify:\n");
    displayTaskQueue(&tq);

    // -----------------------------------------
    // Clear Queue Test
    // -----------------------------------------
    printf("\n[TEST] Clearing queue...\n");
    clearTaskQueue(&tq);

    printf("[STATE] After clear:\n");
    displayTaskQueue(&tq);

    printf("\n=== TEST COMPLETE ===\n");
    return 0;
}


// 1. Initialize empty queue
void initTaskQueue(TaskQueue *tq) {
    tq->size = -1;
}

// 2. Check if queue is empty
bool isTaskQueueEmpty(TaskQueue *tq) {
    return tq->size == -1;
}

// 3. Insert a task iteratively (bubble-up)
void enqueueTask(TaskQueue *tq, Task t) {
    int child, pr;

    if (tq->size == MAX_TASKS-1) {
        printf("Lists of task fill\n");
        exit(1);
    }


    tq->size++;
    child = tq->size;
    pr = (child-1)/2;

    while (child > 0 && tq->heap[pr].criticalityScore < t.criticalityScore) {
        tq->heap[child] = tq->heap[pr];
        child = pr;
        pr = (child-1)/2;

    }
    
    tq->heap[child] = t;
}

// 4. Extract the most urgent task iteratively (bubble-down)
Task dequeueTask(TaskQueue *tq) {

    int child, pr;
    Task swap, root;
    Task emp = {"", -1, ""};

    if (tq->size == -1) return emp;


    root = tq->heap[0];
    tq->heap[0] = tq->heap[tq->size];
    tq->size--;

    pr = 0;
    child = (2 * pr)+1;

    while (child <= tq->size) {
        if (child+1 <= tq->size && tq->heap[child+1].criticalityScore > tq->heap[child].criticalityScore) {
            child++;
        }

        if (tq->heap[pr].criticalityScore < tq->heap[child].criticalityScore) {
            swap = tq->heap[pr];
            tq->heap[pr] = tq->heap[child];
            tq->heap[child] = swap;

            pr = child;
            child = (2 * pr) +1;
        } else {
            break;
        }
    }

    return root;
}

// 5. Peek at the most urgent task
Task peekTopTask(TaskQueue *tq) {
    
    if (tq->size == -1) exit;

    return tq->heap[0];
}

// 6. Heapify entire queue iteratively
void heapifyTaskQueue(TaskQueue *tq) {
    int pr, child, down;
    Task swap;


    pr = (tq->size -1)/2;

    while (pr >=0) {
        down = pr;
        child = 2 * down +1;

        while (child <= tq->size) {
            if (child+1 <= tq->size && tq->heap[child+1].criticalityScore > tq->heap[child].criticalityScore) {
                child++;
            }

            if (tq->heap[down].criticalityScore < tq->heap[child].criticalityScore) {
                swap = tq->heap[down];
                tq->heap[down] = tq->heap[child];
                tq->heap[child] = swap;

                down = child;
                child = 2 * down+1;
            } else {
                break;
            }
        }
        pr--;
    }
}

// 7. Search task by name (strict PQ discipline: only root can be accessed)
bool findTaskByNameDiscipline(TaskQueue *tq, const char *name) {

    TaskQueue tempQ;
    initTaskQueue(&tempQ);
    bool flag = false;

    while (tq->size != -1)  {
        Task t  = dequeueTask(tq);
        if (strcmp(t.name, name) == 0) {
            flag = true;
            
        }
        enqueueTask(&tempQ, t);
    }

    while (tempQ.size != -1) {
        Task t = dequeueTask(&tempQ);
        enqueueTask(tq, t);
    }

    return flag;
}

void displayTaskQueue(TaskQueue *tq) {
    if (tq->size == -1) {
        printf("[DISPLAY] Task queue is EMPTY.\n");
        return;
    }

    printf("[DISPLAY] Current Task Queue (Max-Heap Order, index-wise):\n");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i <= tq->size; i++) {
        printf("Index %d -> Task: %s | Criticality: %d | Module: %s\n",
               i,
               tq->heap[i].name,
               tq->heap[i].criticalityScore,
               tq->heap[i].module);
    }

    printf("--------------------------------------------------------\n");
}

// 9. Count total tasks iteratively
int totalTasks(TaskQueue *tq) {
    return tq->size +1;
}

// 10. Clear queue iteratively
void clearTaskQueue(TaskQueue *tq) {

    tq->size = -1;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_HEAP_SIZE 20  // Maximum number of tasks the scheduler can hold

// ===============================
// Type Definitions
// ===============================
typedef struct Task {
    int id;
    char *description;  // Dynamically allocated
    int priority;       // Lower value = higher priority
} Task;

typedef struct PriorityQueue {
    Task **heap_array;  // Array of pointers to Task
    int size;           // Current number of tasks
    int capacity;       // Maximum capacity (MAX_HEAP_SIZE)
} PriorityQueue;

// ===============================
// Function Prototypes
// ===============================
void init_queue(PriorityQueue *pq);
Task *create_task(int id, const char *desc, int priority);
bool insert_task(PriorityQueue *pq, Task *task);
Task *extract_min_task(PriorityQueue *pq);
Task *peek_min_task(PriorityQueue *pq);
void free_queue(PriorityQueue *pq);
void display_queue(PriorityQueue *pq);


int get_parent_index(int i) {
    
   if (i > 0 && i < MAX_HEAP_SIZE) {
    return (i-1)/2;
   }
}
int get_left_child_index(int i) {
    if (i > 0 && i < MAX_HEAP_SIZE) {
    return (i * 2)+1;
   }
}
int get_right_child_index(int i) {
    if (i > 0 && i < MAX_HEAP_SIZE) {
    return (i * 2)+2;
   }
    
}


void display_queue(PriorityQueue *pq) {
    if (pq->size == -1) {
        printf("[DISPLAY] Priority Queue is EMPTY.\n");
        return;
    }

    printf("[DISPLAY] Current Priority Queue (Min-Heap Order, index-wise):\n");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i <= pq->size; i++) {
        printf("Index %d: Task ID %d | Priority %d | Description: %s\n",
               i,
               pq->heap_array[i]->id,
               pq->heap_array[i]->priority,
               pq->heap_array[i]->description);
    }

    printf("-----------------------------------------------------------\n");
}


// ===============================
// Main Function for Testing
// ===============================
int main() {
    PriorityQueue scheduler;
    init_queue(&scheduler);

    printf("=== Cloud Task Scheduler (Min-Heap Priority Queue) ===\n");

    // Create sample tasks
    Task *t1 = create_task(101, "Critical Backend DB Sync", 1);
    Task *t2 = create_task(205, "User Profile Update", 5);
    Task *t3 = create_task(310, "Background Log Cleanup", 10);
    Task *t4 = create_task(402, "Frontend Asset Compile", 2);
    Task *t5 = create_task(507, "Analytics Report Generation", 7);

    // Insert tasks
    insert_task(&scheduler, t1);
    insert_task(&scheduler, t2);
    insert_task(&scheduler, t3);
    insert_task(&scheduler, t4);
    insert_task(&scheduler, t5);

    // Display current queue
    printf("\n--- Current Scheduler Queue ---\n");
    display_queue(&scheduler);


  

    // Peek highest priority task
    Task *top = peek_min_task(&scheduler);
    if (top) {
        printf("\n[Peek] Task ID %d ('%s') with Priority %d is at the top.\n",
                top->id, top->description, top->priority);
    }

    // Extract tasks one by one
    printf("\n--- Extracting tasks in priority order ---\n");
    while (scheduler.size >= 0) {
        Task *extracted = extract_min_task(&scheduler);
        if (extracted) {
            printf("Task ID %d ('%s') with Priority %d extracted.\n",
                    extracted->id, extracted->description, extracted->priority);
            free(extracted->description);
            free(extracted);
        }
    }


    // Cleanup
    free_queue(&scheduler);
    printf("\nAll memory successfully freed.\n");

    return 0;
}

void init_queue(PriorityQueue *pq) {
    // TODO: Allocate memory for heap_array and initialize size/capacity

    pq->heap_array = malloc(sizeof(Task*) * MAX_HEAP_SIZE);
    if (pq->heap_array == NULL) return;

    pq->size = -1;
    pq->capacity = MAX_HEAP_SIZE;

   
}

Task *create_task(int id, const char *desc, int priority) {
    

    Task* task = malloc(sizeof(Task));
    if (!task) return NULL;
    task->description = malloc(strlen(desc)+1);
    if (!task->description) return NULL;
    strcpy(task->description, desc);
    task->id = id;
    task->priority = priority;

    return task;

}

bool insert_task(PriorityQueue *pq, Task *task) {
    // TODO: Insert task into min-heap and heapify_up

    int child, pr;

    if (pq->size == pq->capacity-1) return false;

    pq->size++;
    child = pq->size;
    pr = (child-1)/2;

    while (child>0 && pq->heap_array[pr]->priority > task->priority) {
        pq->heap_array[child] = pq->heap_array[pr];
        child = pr;
        pr = (child-1)/2;
    }
    pq->heap_array[child] = task;
    return true;
}

Task *extract_min_task(PriorityQueue *pq) {
    
    int child, pr;
    Task* temp = create_task(-1, "", -1);
    Task* root;
    Task* swap;
    
    if (pq->size == -1) return temp;
    
    
    root = pq->heap_array[0];
    pq->heap_array[0] = pq->heap_array[pq->size];
    pq->size--;
    
    pr = 0;
    child = (2 * pr) +1;
    
    while (child <= pq->size) {
        if (child+1 <= pq->size && pq->heap_array[child+1]->priority < pq->heap_array[child]->priority) {
            child++;
        }
        if (pq->heap_array[pr]->priority > pq->heap_array[child]->priority) {
            swap = pq->heap_array[pr];
            pq->heap_array[pr] = pq->heap_array[child];
            pq->heap_array[child] = swap;
            
            pr = child;
            child = (pr * 2)+1;
        } else {
            break;
        }
    }
    
    return root;
}

Task *peek_min_task(PriorityQueue *pq) {
    // TODO: Return pointer to root task
    return pq->heap_array[0];
}

void free_queue(PriorityQueue *pq) {
    // TODO: Free all tasks and the heap array
    for(int i = 0; i <= pq->size ; i++) {
        free(pq->heap_array[i]->description);
        free(pq->heap_array[i]);
    }
    free(pq->heap_array);
    pq->capacity = -1;
    pq->size = -1;
}


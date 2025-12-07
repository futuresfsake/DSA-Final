#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPACITY 100

// Structure representing a Task
typedef struct {
    int task_id;
    int priority; // Higher value means higher priority
} Task;

// Structure representing the Priority Queue
typedef struct {
    Task elements[MAX_CAPACITY];
    int size;
} MaxHeap;

// Function Prototypes
void initHeap(MaxHeap* heap);
void insert(MaxHeap* heap, int task_id, int priority);
Task extractMax(MaxHeap* heap);
void displayHeap(MaxHeap* heap);
void heapifySort( Task arr[], int n, int i);
int isEmpty(MaxHeap* heap);
void heapSort (Task arr[], int n);


int main() {
    MaxHeap scheduler;
    initHeap(&scheduler);

    printf("=== CPU Task Scheduler Simulation ===\n\n");

    // 1. Insert tasks with varying priorities
    // Note: ID 103 has the highest priority (90), ID 101 has the lowest (10)
    printf("--- Inserting Tasks ---\n");
    insert(&scheduler, 101, 10);
    insert(&scheduler, 102, 50);
    insert(&scheduler, 103, 90);
    insert(&scheduler, 104, 30);
    insert(&scheduler, 105, 70);

    displayHeap(&scheduler);

    // // 2. Process tasks (Extract Max)
    // printf("--- Processing Tasks (ExtractMax) ---\n");
    
    // while (!isEmpty(&scheduler)) {
    //     Task t = extractMax(&scheduler);
    //     printf("Processing Task ID: %d | Priority: %d\n", t.task_id, t.priority);
    // }

    // printf("\n--- Final Check ---\n");
    // displayHeap(&scheduler);

     printf("\n--- HeapSort ---\n");
    heapSort(scheduler.elements, scheduler.size+1);
    displayHeap(&scheduler);

    return 0;
}

void initHeap(MaxHeap* heap) {
    heap->size = -1;
}

void insert(MaxHeap* heap, int task_id, int priority) {

    int child, pr;
    if (heap->size == MAX_CAPACITY-1) return;

    heap->size++;
    child = heap->size;
    pr = (child-1)/2;

    while (child > 0 && heap->elements[pr].priority > priority) {
        heap->elements[child] = heap->elements[pr];
        child = pr;
        pr = (child-1)/2;
    }

    heap->elements[child].task_id = task_id;
    heap->elements[child].priority = priority;


}

Task extractMax(MaxHeap* heap) {

    int child, pr;

    Task task = {0};
    if (heap->size == -1) return task;


    Task root, swap;

    root = heap->elements[0];
    heap->elements[0] = heap->elements[heap->size];
    heap->size--;

    pr = 0;
    child = 2 * pr +1;

    while (child <= heap->size) {
        if (child + 1 <= heap->size && heap->elements[child+1].priority < heap->elements[child].priority) {
            child++;
        }

        if (heap->elements[pr].priority > heap->elements[child].priority) {
            swap = heap->elements[pr];
            heap->elements[pr] = heap->elements[child];
            heap->elements[child] = swap;

            pr = child;
            child = 2 * pr+1;
        } else {
            break;
        }
    }
    return root;
}

void displayHeap(MaxHeap* heap) {

    for(int i = 0; i <= heap->size; i++) {
        printf("Priority: %d   || Task Id: %d \n", heap->elements[i].priority, heap->elements[i].task_id);
    }

    
}
int isEmpty(MaxHeap* heap) {

    if (heap->size == -1) {
        return 1;
    } else {
        return 0;
    }
}


void heapSort (Task arr[], int n) {

    for(int i = (n-2)/2; i >= 0; i--) {
        heapifySort(arr,n, i);
    }
     for(int i = n-1; i >= 0; i--) {
        Task swap = arr[0];
        arr[0] = arr[i];
        arr[i] = swap;
        heapifySort(arr,i, 0);
    }
}
void heapifySort( Task arr[], int n, int i) {

    int pr = i;
    int child = 2 * pr +1;

    while (child < n) {
        if (child +1 < n && arr[child+1].priority < arr[child].priority) {
            child++;
        }
        if (arr[pr].priority > arr[child].priority) {
            Task swap = arr[pr];
            arr[pr] = arr[child];
            arr[child] = swap;

            pr = child;
            child = 2 * pr +1;

        } else {
            break;
        }
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXPQ 5
#define MAX_NAME 50
#define MAX_DEPT 30

// ================================
// Nested Structs: Employee and Department
// ================================
typedef struct {
    char deptName[MAX_DEPT];
    int floor;
} Department;

typedef struct {
    char empName[MAX_NAME];
    int priorityLevel; // 1 = highest
    Department dept;   // nested struct
} Employee;

// ================================
// Priority Queue (Min-Heap)
// ================================
typedef struct {
    Employee heap[MAXPQ];
    int size; // last index used, init to -1
} PriorityQueue;

// ================================
// Function Prototypes
// ================================
void initPQ(PriorityQueue *pq);
void insertEmployee(PriorityQueue *pq, Employee emp);
Employee extractTop(PriorityQueue *pq);
bool isEmpty(PriorityQueue *pq);
void displayPQ(PriorityQueue *pq);


void displayPQ(PriorityQueue *pq) {
    printf("\nPriority Queue (Heap Order):\n");
    for (int i = 0; i <= pq->size; i++) {
        printf("[%d] Employee: %s | Priority: %d | Dept: %s | Floor: %d\n",
               i,
               pq->heap[i].empName,
               pq->heap[i].priorityLevel,
               pq->heap[i].dept.deptName,
               pq->heap[i].dept.floor);
    }
}

void buildMinHeap(PriorityQueue *pq) {
    
    int pr, down, child;
    Employee swap;

    if (pq->size == -1) exit(1);

   
    pr = (pq->size-1)/2;

    while (pr >= 0) {
        down = pr;
        child = down * 2 +1;

        while (child <= pq->size) {
            if (child +1 <=pq->size && pq->heap[child+1].priorityLevel < pq->heap[child].priorityLevel) {
                child++;
            }

            if (pq->heap[down].priorityLevel > pq->heap[child].priorityLevel) {
                swap = pq->heap[down];
                pq->heap[down] = pq->heap[child];
                pq->heap[child]=swap;

                down = child;
                child = 2 * down+1;


            } else {
                break;
            }
        }
        pr--;

    }

}


int main() {
    PriorityQueue pq;
    initPQ(&pq);

    Employee e1 = {"Alice", 2, {"HR", 3}};
    Employee e2 = {"Bob", 1, {"Finance", 5}};
    Employee e3 = {"Charlie", 3, {"IT", 2}};
    Employee e4 = {"Diana", 4, {"Marketing", 1}};
    Employee e5 = {"Ethan", 9, {"Operations", 4}};

     insertEmployee(&pq, e5);

    insertEmployee(&pq, e1);
    insertEmployee(&pq, e2);
    insertEmployee(&pq, e3);
    insertEmployee(&pq, e4);
    

    displayPQ(&pq);

    Employee top = extractTop(&pq);
    printf("\nExtracted Employee: %s | Priority: %d | Dept: %s\n",
           top.empName, top.priorityLevel, top.dept.deptName);

    displayPQ(&pq);
    printf("After min heapifying the queue:\n");
    buildMinHeap(&pq);
        displayPQ(&pq);

    
    


    return 0;
}


void initPQ(PriorityQueue *pq) {
    pq->size = -1;
}
void insertEmployee(PriorityQueue *pq, Employee emp) {

    int child, pr;

    if (pq->size == MAXPQ -1) exit(1);

    pq->size++;
    child = pq->size;
    pr = (child -1)/2;

    while (child > 0 && pq->heap[pr].priorityLevel > emp.priorityLevel ) {
        pq->heap[child] = pq->heap[pr];
        child = pr;
        pr = (child-1)/2;
    }

    pq->heap[child] = emp;
}
Employee extractTop(PriorityQueue *pq) {
    Employee swap;
    Employee root;

    int child, pr;

    if (pq->size == -1) exit(1);


    root = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size];
    pq->size--;

    pr = 0;
    child = pr * 2 +1;

    while (child <= pq->size) {
        if (child+1 <= pq->size && pq->heap[child+1].priorityLevel < pq->heap[child].priorityLevel) {
            child++;
        }

        if (pq->heap[pr].priorityLevel > pq->heap[child].priorityLevel) {
            swap = pq->heap[pr];
            pq->heap[pr] = pq->heap[child];
            pq->heap[child] = swap;

            pr = child;
            child = pr * 2 +1;
        } else {
            break;
        }
    }

    return root;


}



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CREW 10
#define NAME_LEN 50
#define DEPT_LEN 30

// ================================
// Crew Member Struct
// ================================
typedef struct {
    char name[NAME_LEN];
    int rankIndex; // lower = higher priority
    char division[DEPT_LEN];
} Crew;

// ================================
// Min-Heap Struct
// ================================
typedef struct {
    Crew heap[MAX_CREW];
    int size; // last index used, initialize to -1
} CommandQueue;

void initQueue(CommandQueue *q) {
    q->size = -1;
}

// 2. Check if queue is empty
bool isQueueEmpty(CommandQueue *q) {
    return q->size == -1;
}

// 3. Insert a crew member iteratively
void enqueueCrew(CommandQueue *q, Crew c) {
   
   int child, pr;
   
   if (q->size == MAX_CREW -1) return;
   
   q->size++;
   child = q->size;
   pr = (child-1)/2;
   
   while (child > 0 && q->heap[pr].rankIndex > c.rankIndex) {
       q->heap[child] = q->heap[pr];
       child = pr;
       pr = (child-1)/2;
   }
   
   q->heap[child] = c;
}


Crew dequeueCrew(CommandQueue *q) {
    
    int child, pr;
    Crew root, swap;
    
     Crew emp = {"", -1, ""};
    
    if (q->size == -1) return emp;
    
    
    root = q->heap[0];
    q->heap[0] = q->heap[q->size];
    q->size--;
    
    
    pr = 0;
    child = 1;
    
    while (child <= q->size) {
        if (child +1 <= q->size && q->heap[child+1].rankIndex < q->heap[child].rankIndex) {
            child++;
            
        }
        
        if (q->heap[pr].rankIndex > q->heap[child].rankIndex) {
            swap  = q->heap[pr];
            q->heap[pr] = q->heap[child];
            q->heap[child] = swap;
            
            pr = child;
            child  = (2 * pr) +1;
        } else {
            break;
        }
    }
    return root;
}
Crew peekTopCrew(CommandQueue *q) {
    return q->heap[0];
}
void heapifyQueue(CommandQueue *q) {
    int pr, child, down;
    Crew swap;
    
    
    pr = (q->size-1) / 2;
    
    while (pr >= 0) {
        
        down = pr;
        child = (pr * 2) +1;
        
        while (child <= q->size) {
            if (child+1 <= q->size && q->heap[child+1].rankIndex > q->heap[child].rankIndex) {
                child++;
            }
            if (q->heap[pr].rankIndex> q->heap[child].rankIndex) {
                swap = q->heap[pr];
                q->heap[pr] = q->heap[child];
                q->heap[child] = swap;
                
                pr = child;
                child = (pr * 2) +1;
            } else {
                break;
            }
        }
        pr--;
        
    }
}
int findCrewByName(CommandQueue *q, const char *name) {
    for(int i = 0; i <= q->size; i++) {
        if (strcmp(q->heap[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}
void promoteCrew(CommandQueue *q, const char *name, int newRank) {
    for(int i = 0; i <= q->size; i++) {
        if (strcmp(q->heap[i].name, name) == 0) {
            q->heap[i].rankIndex = newRank;
            break;
        }
    }
    heapifyQueue(q);
}
void demoteCrew(CommandQueue *q, const char *name, int newRank) {
    for(int i = 0; i <= q->size; i++) {
        if (strcmp(q->heap[i].name, name) == 0) {
            q->heap[i].rankIndex = newRank;
            break;
        }
    }
    heapifyQueue(q);
}
int totalCrew(CommandQueue *q) {
    return q->size +1;
}
void clearQueue(CommandQueue *q) {
   
    q->size = -1;
}


// 10. Display all crew members iteratively
void displayQueue(CommandQueue *q) {
    printf("\n--- Command Queue Status ---\n");
    if (isQueueEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    for (int i = 0; i <= q->size; i++) {
        printf("Index %d: %s, Rank: %d, Division: %s\n",
               i, q->heap[i].name, q->heap[i].rankIndex, q->heap[i].division);
    }
}


// ================================
// MAIN (Sample Usage)
// ================================
int main() {
    CommandQueue cq;
    initQueue(&cq);

    Crew c1 = {"Zara", 2, "Navigation"};
    Crew c2 = {"Kiro", 0, "Command"};
    Crew c3 = {"Luma", 3, "Engineering"};
    Crew c4 = {"Vex", 1, "Science"};
    Crew c5 = {"Nyra", 4, "Medical"};

    enqueueCrew(&cq, c1);
    enqueueCrew(&cq, c2);
    enqueueCrew(&cq, c3);
    enqueueCrew(&cq, c4);
    enqueueCrew(&cq, c5);

    displayQueue(&cq);

    Crew top = dequeueCrew(&cq);
    printf("\nTop priority extracted: %s, Rank: %d, Division: %s\n",
          top.name, top.rankIndex, top.division);
        //   displayQueue(&cq);

    promoteCrew(&cq, "Nyra", 1);
    demoteCrew(&cq, "Luma", 5);

    displayQueue(&cq);

    int idx = findCrewByName(&cq, "Vex");
    if (idx != -1) printf("\nVex is at index %d in the queue.\n", idx);

    Crew peek = peekTopCrew(&cq);
    printf("Current top crew: %s, Rank: %d\n", peek.name, peek.rankIndex);

    printf("Total crew in queue: %d\n", totalCrew(&cq));

    heapifyQueue(&cq);

    clearQueue(&cq);

    return 0;
}

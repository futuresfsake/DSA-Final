#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
#define MAX_SIGNALS 30
#define NAME_LEN 50

typedef struct {
    int signalID;               // Unique SOS signal ID
    char planetName[NAME_LEN];  // Name of the planet sending SOS
    int threatLevel;            // 1 = mild, 10 = catastrophic
} Signal;

typedef struct {
    Signal heap[MAX_SIGNALS];   // The max-heap array
    int count;                  // Number of active signals
} SignalHeap;

typedef struct {
    int arr[100];   // BFS queue storing ARRAY INDICES
    int front;
    int rear;
} IndexQueue;


void enqueue(IndexQueue *q, int idx) {
    q->arr[q->rear++] = idx;
}
int dequeue(IndexQueue *q) {
    return q->arr[q->front++];
}

void BFS(SignalHeap *sh) {

    if (sh->count == -1) {
    printf("Heap is empty.\n");
    return;
}

    IndexQueue qq;
    qq.front = 0;
    qq.rear = 0;

    enqueue(&qq, 0);

    while (qq.front < qq.rear) {
        int i = dequeue(&qq);

        printf("ID: %d | %s \n", sh->heap[i].signalID, sh->heap[i].planetName);

        int left = 2 * i +1;
        int right = 2 * i + 2;

        if (left <= sh->count) enqueue(&qq, left);
        if (right <= sh->count) enqueue(&qq, right);
    }
    
}

void initHeap(SignalHeap *sh);
void insertSignal(SignalHeap *sh, Signal s);
void extractMax(SignalHeap *sh, Signal *removed);
void updateThreat(SignalHeap *sh, int signalID, int newThreat);
void maxHeapify(SignalHeap *sh, int index);
void heapSort(SignalHeap *sh);
void displayHeap(SignalHeap *sh);



int main() {
    SignalHeap sh;
    initHeap(&sh);

    Signal s1 = {301, "Xerion", 7};
    Signal s2 = {302, "Nebulon", 3};
    Signal s3 = {303, "Cryon-5", 10};
    Signal s4 = {304, "Aetheria", 6};
    Signal s5 = {305, "Vortiga", 2};

    insertSignal(&sh, s1);
    insertSignal(&sh, s2);
    insertSignal(&sh, s3);
    insertSignal(&sh, s4);
    insertSignal(&sh, s5);

    printf("\n=== CURRENT DISTRESS SIGNAL HEAP (MAX-HEAP) ===\n");
    displayHeap(&sh);

    printf("\n=== HIGHEST PRIORITY SIGNAL ===\n");
    printf("%d (%s) Threat Level: %d\n",
           sh.heap[0].signalID,
           sh.heap[0].planetName,
           sh.heap[0].threatLevel);

    Signal removed;
    extractMax(&sh, &removed);

    printf("\nRemoved signal (responded to first): %d (%s)\n",
           removed.signalID, removed.planetName);

    printf("\n=== HEAP AFTER REMOVAL ===\n");
    displayHeap(&sh);

    printf("\n=== BFS TRAVERSAL OF HEAP ===\n");
    BFS(&sh);

    printf("\n=== UPDATE THREAT (Signal 304 -> Level 10) ===\n");
    updateThreat(&sh, 304,101);
    displayHeap(&sh);

    printf("\n=== HEAPIFY + HEAPSORT (Descending Threat) ===\n");
    heapSort(&sh);
    displayHeap(&sh);

    

    return 0;
}
void displayHeap(SignalHeap *sh) {
    printf("SignalHeap (Max-Heap Order by Threat):\n");

    for (int i = 0; i <= sh->count; i++) {
        printf("[ID:%d Planet:%s Threat:%d]\n",
               sh->heap[i].signalID,
               sh->heap[i].planetName,
               sh->heap[i].threatLevel);
    }
}


void initHeap(SignalHeap *sh) {
    sh->count = -1;
}
void insertSignal(SignalHeap *sh, Signal s) {

    if (sh->count == MAX_SIGNALS-1) return;

    int child, pr;

    sh->count++;
    child = sh->count;
    pr = (child-1)/2;

    while (child > 0 && sh->heap[pr].signalID < s.signalID) {
        sh->heap[child] = sh->heap[pr];
        child = pr;
        pr = (child-1)/2;
    }


    sh->heap[child] = s;
    printf("%d successfully inserted!\n", s.signalID);
}


void extractMax(SignalHeap *sh, Signal *removed) {

    if (sh->count == -1) return;

    *removed = sh->heap[0];
    sh->heap[0] = sh->heap[sh->count];
    sh->count--;

    int pr = 0;
    int child = 2 * pr +1;


    while (child <= sh->count) {
        if (child+1 <= sh->count && sh->heap[child+1].signalID > sh->heap[child].signalID) {
            child++;
        }

        if (sh->heap[pr].signalID < sh->heap[child].signalID) {
            Signal swap = sh->heap[pr];
            sh->heap[pr] = sh->heap[child];
            sh->heap[child] = swap;

            pr = child;
            child = 2 * pr +1;
        } else {
            break;
        }
    }
}


void updateThreat(SignalHeap *sh, int signalID, int newID) {

    for(int i = 0; i <= sh->count; i++) {
        if (sh->heap[i].signalID == signalID) {
            sh->heap[i].signalID = newID;

            maxHeapify(sh, 0);
        }
    }
}
void maxHeapify(SignalHeap *sh, int index) {

    int pr = index;
    int child = 2 * pr +1;

    while (child <= sh->count) {
        if (child+1 <= sh->count && sh->heap[child+1].signalID > sh->heap[child].signalID) {
            child++;

        }

        if (sh->heap[pr].signalID < sh->heap[child].signalID) {
            Signal swap = sh->heap[pr];
            sh->heap[pr] = sh->heap[child];
            sh->heap[child] = swap;

            pr = child;
            child = 2 * pr +1;
        } else {
            break;
        }
    }
}
void heapSort(SignalHeap *sh) {

    int orig;
    Signal catcher;

    orig = sh->count;
    sh->count = -1;

    for(int i=0; i <= orig; i++) {
        insertSignal(sh, sh->heap[i]);
    }

    for(int i = orig; i>= 0; i--) {
        extractMax(sh, &catcher);
        sh->heap[i] = catcher;
    }

    sh->count = orig;

}
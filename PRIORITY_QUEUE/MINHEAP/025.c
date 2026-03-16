#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEAP 100

typedef struct {
    char flight_number[10];
    int fuel_percentage;    
    int is_emergency;       
} Plane;

typedef struct {
    Plane arr[MAX_HEAP];
    int size;
} PriorityQueue;

// ===================== FUNCTION DEFINITIONS =====================

void initQueue(PriorityQueue *pq) {
    pq->size = 0;
}

/**
 * Priority Logic:
 * Returns > 0 if 'a' has higher priority than 'b'
 * 1. Emergency (is_emergency == 1) always wins.
 * 2. If both are same emergency status, lower fuel wins.
 */
int comparePlane(Plane a, Plane b) {
    if (a.is_emergency != b.is_emergency) {
        return a.is_emergency - b.is_emergency; 
    }
    // If emergency status is same, the one with LESS fuel is higher priority
    return b.fuel_percentage - a.fuel_percentage;
}

void swap(Plane *a, Plane *b) {
    Plane temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(PriorityQueue *pq, int index) {
    int parent = (index - 1) / 2;
    if (index > 0 && comparePlane(pq->arr[index], pq->arr[parent]) > 0) {
        swap(&pq->arr[index], &pq->arr[parent]);
        heapifyUp(pq, parent);
    }
}

void heapifyDown(PriorityQueue *pq, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size && comparePlane(pq->arr[left], pq->arr[largest]) > 0)
        largest = left;

    if (right < pq->size && comparePlane(pq->arr[right], pq->arr[largest]) > 0)
        largest = right;

    if (largest != index) {
        swap(&pq->arr[index], &pq->arr[largest]);
        heapifyDown(pq, largest);
    }
}

void insertPlane(PriorityQueue *pq, Plane p) {
    if (pq->size >= MAX_HEAP) return;
    
    pq->arr[pq->size] = p;
    heapifyUp(pq, pq->size);
    pq->size++;
}

Plane extractHighestPriority(PriorityQueue *pq) {
    Plane top = pq->arr[0];
    pq->arr[0] = pq->arr[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);
    return top;
}

void printQueue(PriorityQueue *pq) {
    for (int i = 0; i < pq->size; i++) {
        printf("[%d] %s (Fuel: %d%%, Emg: %d)\n", 
                i, pq->arr[i].flight_number, pq->arr[i].fuel_percentage, pq->arr[i].is_emergency);
    }
}

// ===================== MAIN =====================

int main() {
    PriorityQueue pq;
    initQueue(&pq);

    Plane a = {"AA101", 30, 0};
    Plane b = {"DL202", 10, 0};
    Plane c = {"UA303", 50, 1}; // Emergency!
    Plane d = {"CX404", 15, 1}; // Emergency + Low Fuel!
    Plane e = {"QF505", 10, 0};

    insertPlane(&pq, a);
    insertPlane(&pq, b);
    insertPlane(&pq, c);
    insertPlane(&pq, d);
    insertPlane(&pq, e);

    printf("\n--- Queue Contents (Heap Structure) ---\n");
    printQueue(&pq);

    printf("\nExtracting planes in priority order:\n");
    while (pq.size > 0) {
        Plane next = extractHighestPriority(&pq);
        printf("Landing: %s | Emergency: %d | Fuel: %d%%\n",
                next.flight_number,
                next.is_emergency,
                next.fuel_percentage);
    }

    return 0;
}
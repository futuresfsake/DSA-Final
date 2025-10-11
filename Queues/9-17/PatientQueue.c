#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100

// ------------------ Patient Structure ------------------
typedef struct {
    int patientID;
    char name[20];
    int priority;  // 1 = critical, 2 = serious, 3 = mild
    int age;
} Patient;

// ------------------ Queue Structure ------------------
typedef struct {
    Patient arr[MAX];
    int front;
    int rear;
} Queue;

// ------------------ Queue Functions ------------------

// Initialize queue
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
}

// Check if queue is empty
bool isEmpty(Queue *q) {
    return q->rear < q->front;
}

// Check if queue is full
bool isFull(Queue *q) {
    return q->rear == MAX - 1;
}

// Standard enqueue (add at rear)
void enqueue(Queue *q, Patient p) {
    if (!isFull(q)) {
        q->arr[++q->rear] = p;
    } else {
        printf("Queue is full!\n");
    }
}

// Standard dequeue (remove at front)
Patient dequeue(Queue *q) {
    Patient dummy = {-1, "", -1, -1};
    if (!isEmpty(q)) {
        return q->arr[q->front++];
    } else {
        printf("Queue is empty!\n");
        return dummy;
    }
}

// ------------------ Enqueue Sorted ------------------
// TODO: Insert patient p in sorted order by priority
// 1. Create a temporary queue
// 2. Traverse the original queue
// 3. Insert p before the first patient with higher priority
// 4. Copy remaining patients
// 5. If not inserted, enqueue p at the end
void enqueueSorted(Queue *q, Patient p) {
    
    Queue tempQueue;
    initQueue(&tempQueue);
    bool insert = false;


    for(int i = q->front ; i != (q->rear +1) % MAX; i = (i+1) % MAX) {
        Patient c = q->arr[i];

        if (!insert && p.priority  < c.priority) {
            enqueue(&tempQueue, p);
            insert = true;
        } 
        enqueue(&tempQueue, c);


    }

    if (!insert) {
        enqueue(&tempQueue, p);
    }

    *q = tempQueue;
}

// ------------------ Display Traversal ------------------
// TODO: Traverse queue and print each patient’s info
void displayTraversal(Queue q) {

    for(int i = q.front; i != (q.rear+1) % MAX; i  =(i+1) % MAX)
     {
        printf("Name: %s || Priority: %d\n", q.arr[i].name, q.arr[i].priority);
     }
}

// ------------------ Main Function ------------------
// TODO: 
// 1. Initialize queue
// 2. Create some sample patients
// 3. Call enqueueSorted for each
// 4. Display final queue
int main() {
    
    Queue q;
    initQueue(&q);

            Patient P1 = {001, "Gran", -1, 32};
                
            Patient P2 = {003, "GodZ", 2, 45};
            Patient P4 = {00432, "Cheska", -1, 47};
            Patient P3= {004321, "Maya", 3, 15};
            Patient P5 = {001324, "Ard", 2, 4};
            

            enqueueSorted(&q, P1);
            enqueueSorted(&q, P2);
             enqueueSorted(&q, P3);
            enqueueSorted(&q, P4);
             enqueueSorted(&q, P5);


             displayTraversal(q);
            
    return 0;
}

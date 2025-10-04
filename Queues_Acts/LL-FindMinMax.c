#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===== Nested Structs =====
typedef struct {
    int id;
    char name[50];
} Data;

typedef struct Link {
    Data info;
    struct Link *next;
} Link;

typedef struct {
    Link *front;
    Link *rear;
} Queue;

// ===== Function Declarations =====
Queue* initQueue() {
    Queue *temp;
    temp->front = NULL;
    temp->rear =NULL;

    return temp;

}
int isEmpty(Queue *q) {
    return q->rear == NULL && q->front == NULL;
}

void enqueue(Queue **q, Data d) {
    Link *newNode = malloc(sizeof(Link));
    if (!newNode) {
        printf("Dynamic memory alloc failed.\n");
        exit(1);
    }

    newNode->info = d;

    if (!isEmpty(*q)) {
        (*q)->rear = newNode;
        (*q)->front = newNode;
        printf("%s successfully added.\n", d.name);
    } else {
        (*q)->rear->next = newNode;
        (*q)->rear = newNode;
    }

    printf("%s successfully added.\n", d.name);
}
Data dequeue(Queue **q) {
   Link *toRemove;
   Data d;


   if ((*q)->front == (*q)->rear) {
    toRemove = (*q)->front;
    d = toRemove->info;
    free(toRemove);

    (*q)->front = NULL;
    (*q)->rear = NULL;
    return d;
    
   } else {
    toRemove = (*q)->front;
    (*q)->front = toRemove->next;
    d = toRemove->info;
    free(toRemove);
    return d;
   
   }

    
}


// void displayQueue(Queue *q) {

// }
// Data findMin(Queue *q);   // Find min by ID
// Data findMax(Queue *q);   // Find max by ID

// ===== Main Function =====
int main() {
    Queue *q = initQueue();

    Data d1 = {10, "Alice"};
    Data d2 = {5, "Bob"};
    Data d3 = {20, "Charlie"};

    enqueue(&q, d1);
    enqueue(&q, d2);
    enqueue(&q, d3);

    Data d = dequeue(&q);
    printf("%s removed", d.name);

    // printf("Queue contents:\n");
    // displayQueue(q);



    // Data minData = findMin(q);
    // Data maxData = findMax(q);

    // printf("\nMin ID: %d, Name: %s\n", minData.id, minData.name);
    // printf("Max ID: %d, Name: %s\n", maxData.id, maxData.name);

    return 0;
}

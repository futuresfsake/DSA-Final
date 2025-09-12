#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ===== Delivery Time Struct =====
typedef struct {
    int hours;
    int minutes;
} DeliveryTime;

// ===== Package Struct =====
typedef struct {
    int id;
    char sender[50];
    char receiver[50];
    float weight;
    DeliveryTime eta;  // Estimated time of arrival
} Package;

// ===== Node for Queue =====
typedef struct Node {
    Package data;
    struct Node *next;
} Node;

// ===== Queue Struct =====
typedef struct {
    Node *front;
    Node *rear;
} PackageQueue;

// ===== Core Queue Functions =====
void initQueue(PackageQueue *q) {
    q->front = NULL;
    q->rear = NULL;
}

int isQueueEmpty(PackageQueue q) {
    return q.front == NULL && q.rear == NULL;
}

void enqueuePackage(PackageQueue *q, Package p) {
    Node *temp = malloc(sizeof(struct Node)); // ! before it was 
    // !Package *temp = malloc(sizeof(Node));
    // ! now, i changed it to Node *temp = malloc(sizeof(struct node)); // ! and it still // errored. Now, I changed it to, Node *temp = malloc(sizeof(Node));
    if (!temp) {
        printf("Dynamic memory allocation failed.\n");
        exit(1);
    }
    temp->data = p;
    temp->next = NULL;

    if (isQueueEmpty(*q)) {
        q->front = temp;
        q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
    
    printf("Package ID: %d is successfully queued!\n", p.id);
}

Package dequeuePackage(PackageQueue *q) {
    if (isQueueEmpty(*q)) {
        exit(1);
    } 

    Node *temp;
    Package data;

    if (q->front == q->rear) {
    temp = q->front;
    data = q->front->data;
    q->front = NULL;
    q->rear = NULL;
    free(temp);
    } else {
        temp = q->front;
        q->front = temp->next;
        data = temp->data;
        free(temp);
    }

    return data;


}
Package peekQueue(PackageQueue q) {
    return q.rear->data;
}
void displayQueue(PackageQueue q) {

    if(isQueueEmpty(q)) {
        exit(1);
    }

    Node *i = q.front;

    while (i != NULL) {
        printf("\nID: %d, Sender: %s, Receiver:%s", i->data.id, i->data.sender, i->data.receiver);
        i = i->next;
    }
}

// ===== Special Operation =====
// Find the heaviest package in the queue
Package findHeaviestPackage(PackageQueue q) {

    
    
   
    Node *i = q.front;
     Package max = i->data;
    
    while (i != NULL) {
        
        if (i->data.weight > max.weight) {
            max = i->data;  
               
        }
        i = i->next;

    }
    return max;

}
int main() {
    PackageQueue q;
    initQueue(&q);

    // Sample packages
    Package p1 = {1, "Alice", "Bob", 2.5, {10, 30}};
    Package p2 = {2, "Charlie", "Diana", 5.0, {11, 15}};
    Package p3 = {3, "Eve", "Frank", 3.2, {12, 45}};

    // Enqueue
    enqueuePackage(&q, p1);
    enqueuePackage(&q, p2);
    enqueuePackage(&q, p3);

    // Peek (rear package)
    Package last = peekQueue(q);
    printf("Rear Package -> ID: %d, %s -> %s, Weight: %.2fkg\n",
           last.id, last.sender, last.receiver, last.weight);

    // Display all
    printf("\nAll Packages in Queue:\n");
    displayQueue(q);

    // Special Operation
    Package heavy = findHeaviestPackage(q);
    printf("\nHeaviest Package -> ID: %d, %.2fkg from %s to %s\n",
            heavy.id, heavy.weight, heavy.sender, heavy.receiver);

    return 0;
}

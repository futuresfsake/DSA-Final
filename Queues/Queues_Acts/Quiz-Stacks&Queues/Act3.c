
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
    int hours;
    int minutes;
} Time;

typedef struct {
    int id;
    char origin[50];
    char destination[50];
    Time departure_time;
    Time arrival_time;
} Flight;


typedef struct Node {
    Flight data;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} FlightQueue;


void initQueue(FlightQueue *q) {
    q->front = NULL;
    q->rear = NULL;
}
int isQueueEmpty(FlightQueue q) {
    return q.front == NULL && q.rear == NULL;
}


void enqueueFlight(FlightQueue *q, Flight f) {
    Node *newNode = malloc(sizeof(Node));
    if (!newNode) {
        printf("Dynamic Memory Allocation failed.\n");
        return;
    }
    newNode->data = f;
    newNode-> next = NULL;

    if (isQueueEmpty(*q)) {
        q->front = newNode;
        q->rear = newNode;        
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

Flight dequeueFlight(FlightQueue *q) {
    if (isQueueEmpty(*q)) {
        printf("Queue is empty.\n");
        exit(1);
    }

    Node *toRemove;
    Flight data;

    if (q->front == q->rear) {

        toRemove = q->front;
        data = q->front->data;
        q->front = NULL;
        q->rear;
        free(toRemove);
        return data;
    } else {
        toRemove = q->front;
        q->front = q->front->next;
        data = q->front->data;
        free(toRemove);
        return data;
    }

    
}
Flight peekQueue(FlightQueue q) {
    return q.rear->data;

}

void display(FlightQueue *q) {

    Node *i = q->front;
    while (i != NULL) {
        printf("ID: %d, Destination: %s, Origin: %s\n", i->data.id, i->data.destination, i->data.origin);

      
        i = i->next;
    
    }
}



    int main() {
    FlightQueue q;
    initQueue(&q);

    // Create sample flights
    Flight f1 = {1, "Cebu", "Manila", {8, 30}, {10, 45}};
    Flight f2 = {2, "Manila", "Davao", {11, 15}, {13, 30}};
    Flight f3 = {3, "Davao", "Cebu", {14, 00}, {15, 45}};

    // Enqueue flights
    enqueueFlight(&q, f1);
    enqueueFlight(&q, f2);
    enqueueFlight(&q, f3);

    // Peek at the last flight in the queue
    Flight last = peekQueue(q);
    printf("Rear Flight (peek) -> ID: %d, %s to %s, Departure: %02d:%02d, Arrival: %02d:%02d\n",
           last.id, last.origin, last.destination,
           last.departure_time.hours, last.departure_time.minutes,
           last.arrival_time.hours, last.arrival_time.minutes);

    
    display(&q);

    return 0;
}






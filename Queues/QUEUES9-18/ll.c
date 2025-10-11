#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ===== Task Struct (stored in Queue) =====
typedef struct {
    int taskId;
    char description[100];
    int priority;   // higher = more urgent
} Task;

// ===== Node for Linked List Queue =====
typedef struct Link {
    Task info;
    struct Link *next;
} Link;

typedef struct {
    Link *front;
    Link *rear;
} Queue;

// ===== Function Declarations =====
Queue* initQueue();
bool isEmpty(Queue *q);
void enqueue(Queue *q, Task newTask);
Task dequeue(Queue *q);
Task peek(Queue *q);
void displayQueue(Queue *q);
void processHighPriority(Queue *q);   // special: dequeue only highest priority task

// ===== Main Function =====
int main() {
    Queue *taskQueue = initQueue();

    Task t1 = {1, "Fix server issue", 3};
    Task t2 = {2, "Deploy update", 2};
    Task t3 = {3, "Database backup", 1};
    Task t4 = {4, "Security patch", 5};

    enqueue(taskQueue, t1);
    enqueue(taskQueue, t2);
    enqueue(taskQueue, t3);
    enqueue(taskQueue, t4);

    printf("All tasks in queue:\n");
    displayQueue(taskQueue);

    printf("\nProcessing highest priority task:\n");
    processHighPriority(taskQueue);

    printf("\nRemaining tasks in queue:\n");
    displayQueue(taskQueue);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ================= STRUCT DEFINITIONS =================
typedef struct {
    int id;
    char name[50];
    int priority;   // 1 = High, 2 = Medium, 3 = Low
    int age;        // tie-breaker: older comes first
} Task;

typedef struct node {
    Task info;
    struct node *next;
} NodeType, *NodePtr;

typedef struct {
    NodePtr front;
    NodePtr rear;
    int count;
} TaskQueue;

// ================= FUNCTION DECLARATIONS =================
void initQueue(TaskQueue *q) {
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
}
bool isEmpty(TaskQueue q) {
    return q.front == NULL;
}

Task peek(TaskQueue *q) {
    return q->front->info;
}

Task dequeue(TaskQueue *q) {

    NodePtr toRemove = q->front;
    q->front = toRemove->next;
    free(toRemove);    
    
    
}

void enqueue(TaskQueue *q, Task t) {
    NodePtr Person = malloc(sizeof(NodeType));
    Person->info = t;
    Person->next = NULL;


    if (q->front == NULL) {
        q->front = Person;
        q->rear = Person;
        
    } else {
        q->rear->next = Person;
        q->rear = Person;
    }

    q->count++;
}
// Sorted enqueue (conditions below)

void visualize(TaskQueue q) {

    TaskQueue tempQueue;
    initQueue(&tempQueue);
    while (q.front != NULL) {
        Task p = peek(&q);
        printf("Name: %s || Priority: %d || Age: %d || ID: %d ", p.name, p.priority, p.age, p.id);
        dequeue(&q);
        enqueue(&tempQueue, p);

    }


    q = tempQueue;


}


bool enqueueSorted(TaskQueue *q, Task t) {

    TaskQueue temp;
    initQueue(&temp);

    NodePtr person = NULL;
    while (q->front != NULL) {
        person = q->front;

        if (person->info.priority > t.priority) {
            enqueue(&temp, t);
        }

         else {
            enqueue(&temp, person->info);
        }

    
    


         if (person->info.priority == t.priority) {
            if (person->info.age < t.age ) {
                enqueue(&temp, t);
            } else {
                enqueue(&temp, person->info);
            }
        }
        
            if (person->info.priority == t.priority && person->info.age == t.age) {
                if (person->info.id < t.id) {
                    enqueue(&temp, t);
                } else {
                    enqueue(&temp, person->info);
                }
            }



    }

    *q = temp;

}

// Dequeue from front


// ================= MAIN DEMO =================
int main() {
    TaskQueue q;
    initQueue(&q);

    Task T1 = {101, "Backup DB", 2, 45};
    Task T2 = {102, "System Update", 1, 30};
    Task T3 = {103, "Log Cleanup", 3, 50};
    Task T4 = {104, "Security Patch", 1, 60};
    Task T5 = {105, "Report Generation", 2, 25};

    enqueueSorted(&q, T1);
    visualize(q);

    enqueueSorted(&q, T2);
    visualize(q);

    enqueueSorted(&q, T3);
    visualize(q);

    enqueueSorted(&q, T4);
    visualize(q);

    enqueueSorted(&q, T5);
    visualize(q);

    printf("\nDequeuing one task...\n");
    Task served = dequeue(&q);
    printf("Dequeued: [%d] %s\n", served.id, served.name);
    visualize(q);

    return 0;
}

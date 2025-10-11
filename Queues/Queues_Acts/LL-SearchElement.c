#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// ===== Example Data Type =====
typedef struct {
    int id;
    char name[50];
    // add more fields if needed
} Data;

// ===== Node & Queue Definitions =====
typedef struct Node {
    Data data;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} Queue;

// ===== Queue Core =====
void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

bool isQueueEmpty(Queue *q) {
    return (q->front == NULL);
}

bool enqueue(Queue *q, Data d) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        return false;
    }
    newNode->data = d;
    newNode->next = NULL;
    if (q->rear == NULL) {
        // queue is empty
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    return true;
}

bool dequeue(Queue *q, Data *d_out) {
    if (isQueueEmpty(q)) {
        return false;
    }
    Node *temp = q->front;
    *d_out = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return true;
}

// ===== Search Function =====
// Returns a pointer to the node containing matching data, or NULL if not found.
// You decide what “matching” means.

Node* searchQueue (Queue *q, int search) {
    Node *i = q->front;
    Node *found;

    while (i != NULL) {
        if (i->data.id == search) {
            return i;
            break;

        }
        i = i->next;

    }
    found->data.id = -1;
    return found;
    
}
// ===== Display (for testing) =====
void displayQueue(Queue *q) {
    Node *curr = q->front;
    if (curr == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue contents:\n");
    while (curr != NULL) {
        printf("  ID: %d, Name: %s\n", curr->data.id, curr->data.name);
        curr = curr->next;
    }
}

// ===== Main for Testing =====
int main(void) {
    Queue q;
    initQueue(&q);

    Data d1 = {1, "Alice"};
    Data d2 = {2, "Bob"};
    Data d3 = {3, "Charlie"};

    enqueue(&q, d1);
    enqueue(&q, d2);
    enqueue(&q, d3);

    displayQueue(&q);

    int search_id = 2;
    Node *found = searchQueue(&q, search_id);
    if (found) {
        printf("Found element with ID %d: Name = %s\n", found->data.id, found->data.name);
    } else {
        printf("Element with ID %d not found in queue.\n", search_id);
    }

    return 0;
}

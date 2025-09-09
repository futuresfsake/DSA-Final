#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10   // circular array size

// ==== Node Definition ====
typedef struct node {
    int data;
    struct node *next;
} Node, *NodePtr;

// ==== Linked List Queue ====
typedef struct {
    NodePtr front;
    NodePtr rear;
    int count;
} QueueLLType, *QueueLLPtr, **QueueLL;

// ==== Circular Array Queue ====
typedef struct {
    int arr[MAX];
    int front;
    int rear;
    int count;
} QueueCA;

// ==== Linked List Queue Functions ====
void initQueueLL(QueueLL q) {
    (*q)->front = NULL;
    (*q)->rear = NULL;
    (*q)->count = 0;
}

bool isEmptyLL(QueueLLPtr q) {
    return (q->rear == NULL && q->front == NULL);
}
void enqueueLL(QueueLL q, int value) {
    NodePtr temp = malloc(sizeof(Node));
    if (!temp) {
        printf("Dynamic Memory allocation failed.\n");
        return;
    }

    temp->data = value;
    temp->next = NULL;


    if (isEmptyLL(*q)) { // ! &q, is just a pointer, you need to pass a double pointer, you dereference it?
        
        // (*q) = temp; // * you are trying to assign a QueueLLType to a nodePtr, incompatible pointer
        (*q)->front = temp;
        (*q)->rear = temp;
        (*q)->count++;
        printf("%d is successfully inserted first item", value);
    } else {
        (*q)->rear->next = temp; 
        (*q)->rear = temp;
        
        (*q)->count++;
        printf("%d is successfully inserted, filled the second condtition", value);
    }
}

int dequeueLL(QueueLL q) {
    
    if (isEmptyLL(*q)) { // ! it is a double pointer, now an emptyLL will only accept a pointer, so you dereference the double pointer
        return -1;
    }
    int data;
    if ((*q)->front == (*q)->rear) {
        NodePtr temp = (*q)->front;
        data = (*q)->front->data;
        free(temp);
         (*q)->front = NULL;
        (*q)->rear = NULL;
        (*q)->count--;
         data = (*q)->front->data;
         

    }
        else {
            NodePtr temp = (*q)->front;
            (*q)->front = temp->next;
             data = temp->data;
            free(temp);
             (*q)->count--;
        }
        
        return data;

    }


void displayQueueLL(QueueLLPtr q) {
    
    NodePtr i = q->front;

    while (i != NULL ) {
        printf("%d ", i->data);
        i = i->next;
    }
}


int main() {
    QueueLLPtr llq = malloc(sizeof(QueueLLType)); // allocate the struct
    if (!llq) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    initQueueLL(&llq);  // pass pointer-to-pointer

    enqueueLL(&llq, 10);
    enqueueLL(&llq, 20);
    enqueueLL(&llq, 30);

    printf("Linked List Queue:\n");
    displayQueueLL(llq);

    free(llq); // cleanup
    return 0;
}

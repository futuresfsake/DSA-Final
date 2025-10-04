#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100   // maximum size for ArrayList

// ----------------- Linked List -----------------
typedef struct node {
    int data;
    struct node *next;
} NodeType, *NodePtr, *LinkedList;

// ----------------- ArrayList -----------------
typedef struct {
    int arr[MAX];
    int size;
} ArrayList;

// ----------------- Linked List Functions -----------------
void initList(LinkedList *list);
bool isEmpty(LinkedList *list);
void insertFront(LinkedList *list, int data);
void insertEnd(LinkedList *list, int data);
void displayList(LinkedList *list);

// ----------------- ArrayList Functions -----------------
void initArrayList(ArrayList *al);
void displayArrayList(ArrayList *al);

// ----------------- Conversion Function -----------------
ArrayList listToArrayList(LinkedList *list);

// ----------------- Main -----------------
int main() {
    LinkedList mylist;
    initList(&mylist);

    insertEnd(&mylist, 10);
    insertEnd(&mylist, 20);
    insertEnd(&mylist, 30);

    printf("Linked List:\n");
    displayList(&mylist);

    ArrayList myAL = listToArrayList(&mylist);

    printf("\nArrayList:\n");
    displayArrayList(&myAL);

    return 0;
}

// ----------------- Linked List Implementation -----------------
void initList(LinkedList *list) {
    *list = NULL;
}

bool isEmpty(LinkedList *list) {
    return *list == NULL;
}

void insertFront(LinkedList *list, int data) {
    NodePtr temp = malloc(sizeof(NodeType));
    if (!temp) {
        printf("Memory allocation failed!\n");
        return;
    }
    temp->data = data;
    temp->next = *list;
    *list = temp;
}

void insertEnd(LinkedList *list, int data) {
    NodePtr temp = malloc(sizeof(NodeType));
    if (!temp) {
        printf("Memory allocation failed!\n");
        return;
    }
    temp->data = data;
    temp->next = NULL;

    if (*list == NULL) {
        *list = temp;
    } else {
        NodePtr trav = *list;
        while (trav->next != NULL) {
            trav = trav->next;
        }
        trav->next = temp;
    }
}

void displayList(LinkedList *list) {
    NodePtr trav = *list;
    while (trav != NULL) {
        printf("%d -> ", trav->data);
        trav = trav->next;
    }
    printf("NULL\n");
}

// ----------------- ArrayList Implementation -----------------
void initArrayList(ArrayList *al) {
    al->size = 0;
}

void displayArrayList(ArrayList *al) {
    for (int i = 0; i < al->size; i++) {
        printf("%d ", al->arr[i]);
    }
    printf("\n");
}


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *link;
} NodeType, *NodePtr, *List;

void initialize(List *list) {
    *list = NULL;
}

void display(List list) {
    for (NodePtr trav = list; trav != NULL; trav = trav->link) {
        printf("%d ", trav->data);
    }
    printf("\n");
}

bool insertFront(List *list, int data) {
    NodePtr newNode = malloc(sizeof(NodeType));
    if (newNode == NULL) return false;
    newNode->data = data;
    newNode->link = *list;
    *list = newNode;
    return true;
}

bool insertLast(List *list, int data) {
    NodePtr newNode = malloc(sizeof(NodeType));
    if (newNode == NULL) return false;
    newNode->data = data;
    newNode->link = NULL;
    if (*list == NULL) {
        *list = newNode;
    } else {
        NodePtr trav;
        for (trav = *list; trav->link != NULL; trav = trav->link);
        trav->link = newNode;
    }
    return true;
}

bool insertAt(List *list, int pos, int data) {
    NodePtr *trav = list;
    for (int i = 0; *trav != NULL && i < pos; i++, trav = &(*trav)->link);
    NodePtr newNode = malloc(sizeof(NodeType));
    if (newNode == NULL) return false;
    newNode->data = data;
    newNode->link = *trav;
    *trav = newNode;
    return true;
}

bool insertSorted(List *list, int data) {
    NodePtr *trav = list;
    for (; *trav != NULL && (*trav)->data < data; trav = &(*trav)->link);
    NodePtr newNode = malloc(sizeof(NodeType));
    if (newNode == NULL) return false;
    newNode->data = data;
    newNode->link = *trav;
    *trav = newNode;
    return true;
}

bool deleteFront(List *list) {
    if (*list == NULL) return false;
    NodePtr temp = *list;
    *list = (*list)->link;
    free(temp);
    return true;
}

bool deleteLast(List *list) {
    if (*list == NULL) return false;
    NodePtr *trav = list;
    for (; (*trav)->link != NULL; trav = &(*trav)->link);
    free(*trav);
    *trav = NULL;
    return true;
}

bool deleteItem(List *list, int item) {
    NodePtr *trav = list;
    for (; *trav != NULL && (*trav)->data != item; trav = &(*trav)->link);
    if (*trav == NULL) return false;
    NodePtr temp = *trav;
    *trav = (*trav)->link;
    free(temp);
    return true;
}

bool deleteAllItem(List *list, int data) {
    bool deleted = false;
    NodePtr *trav = list;
    for (; *trav != NULL;) {
        if ((*trav)->data == data) {
            NodePtr temp = *trav;
            *trav = (*trav)->link;
            free(temp);
            deleted = true;
        } else {
            trav = &(*trav)->link;
        }
    }
    return deleted;
}

int search(List *list, int item) {
    int index = 0;
    for (NodePtr trav = *list; trav != NULL; trav = trav->link, index++) {
        if (trav->data == item) return index;
    }
    return -1;
}

bool isFound(List list, int data) {
    for (NodePtr trav = list; trav != NULL; trav = trav->link) {
        if (trav->data == data) return true;
    }
    return false;
}

bool isEmpty(List list) {
    return list == NULL;
}

void SortList(List *list) {
    if (*list == NULL) return;
    for (NodePtr i = *list; i->link != NULL; i = i->link) {
        for (NodePtr j = i->link; j != NULL; j = j->link) {
            if (i->data > j->data) {
                int temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

int main() {
    List L;
    initialize(&L);
    insertFront(&L, 30);
    insertFront(&L, 20);
    insertLast(&L, 40);
    insertAt(&L, 1, 25);
    insertSorted(&L, 35);
    display(L);
    deleteFront(&L);
    deleteLast(&L);
    deleteItem(&L, 25);
    insertLast(&L, 50);
    insertLast(&L, 10);
    insertLast(&L, 60);
    deleteAllItem(&L, 50);
    display(L);
    SortList(&L);
    display(L);
    printf("Found 35 at index: %d\n", search(&L, 35));
    printf("isFound 60: %d\n", isFound(L, 60));
    printf("isEmpty: %d\n", isEmpty(L));
}

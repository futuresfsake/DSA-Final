#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} ArrayList;

// Function Declarations
void initList(ArrayList *list, int capacity);
void insertLast(ArrayList *list, int value);
void deleteLast(ArrayList *list);
void displayList(ArrayList *list);
void insertFront(ArrayList *list, int value);

int main() {
    ArrayList cart;
    initList(&cart, 5);

    insertLast(&cart, 501);
    insertFront(&cart, 502);
    insertLast(&cart, 503);

    printf("Cart before removing:\n");
    displayList(&cart);

    deleteLast(&cart);

    printf("\nCart after removing last item:\n");
    displayList(&cart);

    return 0;
}

void initList(ArrayList *list, int capacity) {
    list->data = malloc(sizeof(int) * capacity);
    if (list->data == NULL) {
        printf("Dynamic Memory Allocation failed.\n");
        exit(-1);
    }

    list->size = 0;
    list->capacity = capacity;
}

void insertLast(ArrayList *list, int value) {
    if (list->size == list->capacity) {
        return;
    }

    list->data[list->size] = value;
    list->size++;
}


void deleteLast(ArrayList *list) {
    if (list->size == 0) {
        return;
    }

    list->size--;
}
void displayList(ArrayList *list) {
    for(int i = 0; i < list->size;i++) {
        printf("%d", list->data[i]);
        if (i < list->size-1) {
            printf(", ");
        }

    }
}


void insertFront(ArrayList *list, int value) {
    if (list->size == list->capacity) {
        return;
    }

    for(int i = list->size; i > 0; --i) {
        list->data[i] = list->data[i-1];
    }

    list->data[0] = value;
    list->size++;

}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} ArrayList;

// Function Declarations
void resize (ArrayList *list, int newCap) {

    int *temp = realloc(list->data, newCap * sizeof(int));
    if (!temp) {
        printf("Dynamic Memory Allocation failed.\n");
        return;
    }

    list->capacity *= 2;
    list->data = temp;

}
void initList(ArrayList *list, int capacity) {

    list->data = malloc(sizeof(int) * capacity);
    list->size = 0;
    list->capacity = capacity;

}
void insertFr(ArrayList *list, int value) {
    if (list->size == list->capacity) {
        resize(list, 2);
    }

    for (int i = list->size; i > 0; i--) {
        list->data[i] = list->data[i -1];
    }
    list->data[0] = value;

    list->size++;
}


void displayList(ArrayList *list) {
    printf("Data: { ");
    for(int i = 0; i < list->size; i++ ) {
        printf(" %d", list->data[i]);      
    }

    printf("}");
}

int main() {
    ArrayList attendance;
    initList(&attendance, 5);

    insertFr(&attendance, 101);
    insertFr(&attendance, 105);
    insertFr(&attendance, 110);

    printf("Students Present Today:\n");
    displayList(&attendance);

    return 0;
}

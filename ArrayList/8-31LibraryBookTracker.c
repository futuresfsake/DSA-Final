#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} ArrayList;

// Function Declarations


void initList(ArrayList *list, int capacity) {
    list->data = malloc(sizeof(int) * capacity);
    list->size = 0;
    list->capacity = capacity;
}

void resize (ArrayList *list) {
    int *temp = realloc(list->data, sizeof(int) * 2);

    list->capacity *= 2;
    list->data = temp;
}

void insertAt(ArrayList *list, int pos, int value) {

    if (list->size == list->capacity) {
        resize (list);
    }

    if (pos < 0 || pos > list->size) {
        printf("Invalid position");
        return;
    }

    for(int i = list->size -1; i >= pos; i--) {
        list->data[i+1] = list->data[i];
    }

    list->data[pos] = value;
    list->size++;
}




void deleteAt(ArrayList *list, int pos) {

    for(int i = pos; i < list->size; i++) {
        list->data[i] = list->data[i+1];
    }

    list->size--;

}
void displayList(ArrayList *list) {
    printf("Data: \n");
    for(int i = 0; i < list->size; i++) {
        printf("%d ", list->data[i]);
    }
}

int main() {
    ArrayList books;
    initList(&books, 10);

    insertAt(&books, 0, 2001);
    insertAt(&books, 1, 2002);
    insertAt(&books, 2, 2003);
    insertAt(&books, 1, 1999);  // Returned book placed at index 1

    printf("Books in Library:\n");
    displayList(&books);

    deleteAt(&books, 2);  // Remove book at index 2

    printf("\nBooks after removal:\n");
    displayList(&books);

    return 0;
}

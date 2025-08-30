#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} ArrayList;

// ===== Function Declarations =====
void initList(ArrayList *list, int capacity) {
    list->data = malloc(capacity * sizeof(int));
    list->size = 0;
    list->capacity = capacity;
}

void insertLast(ArrayList *list, int value) {
    
    if (list->size == list->capacity) {
        int *temp = realloc(list->data, 2 * sizeof(int));
        if (!temp) {printf("Dynamic Memory Allocation failed.\n"); exit(1);}

        list->capacity *= 2;
    }

    list->data[list->size] = value;
    list->size++;

}
void deleteAt(ArrayList *list, int pos) {
    if (pos < 0 || pos >= list->size) {
        printf("Invalid index");
        return;
    }

    for(int i = pos; i < list->size; i++) {
        list->data[i] = list->data[i+1];
    }
    list->size--;
}

void display(ArrayList *list) {
    printf("Scores: { ");
    for(int i = 0; i < list->size; i++) {
        printf("%d ", list->data[i]);
    }

    printf("}");
}
int main() {
    ArrayList books;
    initList(&books, 5);

    insertLast(&books, 1001);  // Book ID 1001
    insertLast(&books, 1002);  // Book ID 1002
    insertLast(&books, 1003);  // Book ID 1003
    insertLast(&books, 1004);  // Book ID 1004

    printf("Books in library:\n");
    display(&books);

    deleteAt(&books, 2);  // Remove book at position 2 (ID 1003)

    printf("\nAfter removing damaged book:\n");
    display(&books);

    return 0;
}

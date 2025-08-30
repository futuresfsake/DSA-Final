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
    if (!temp) {
        printf("Failed Memory Allocation!");
        exit(1);
    }

    list->capacity *= 2;

}

    list->data[list->size] = value;
    list->size++;

}

void display(ArrayList *list) {
    printf("Scores: { ");
    for(int i = 0; i < list->size; i++) {
        printf("%d ", list->data[i]);
    }

    printf("}");
}

int main() {
    ArrayList scores;
    initList(&scores, 3);

    insertLast(&scores, 85);
    insertLast(&scores, 90);
    insertLast(&scores, 78);

    printf("Student Scores:\n");
    display(&scores);

    return 0;
}

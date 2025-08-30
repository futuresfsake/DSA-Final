#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} ArrayList;

// ===== Function Declarations =====
void initList(ArrayList *list, int capacity) {
    list->data = malloc(sizeof(int)*capacity);
    if (!list->data) {
        printf("Dynamic Memory Allocation failed!");
        return;
    }
    list->size = 0;
    list->capacity = capacity;
}
void insertLast(ArrayList *list, int value) {

    if (list->size == list->capacity) {
        int *temp = realloc(list->data, 2 * sizeof(int));
        list->capacity *= 2;
    }


    list->data[list->size] = value;
    list->size++;

}
void insertFront(ArrayList *list, int value) {

      if (list->size == list->capacity) {
        int *temp = realloc(list->data, 2 * sizeof(int));
        list->capacity *= 2;
    }

    for(int i = list->size; i > 0; i--) {
        list->data[i] = list->data[i-1];
    }

    list->data[0] = value;
    
    
    list->size++;


}


void deleteAt(ArrayList *list, int pos) {

    if (list->size == 0) {return;}

    for(int i = pos; i < list->size; i++) {
        list->data[i] = list->data[i+1];
    }
    list->size--;
    

}

void display(ArrayList *list) {
    printf("Data: \n");
    for(int i = 0; i < list->size; i++) {
        printf("%d ", list->data[i]);
    }
}

int main() {
    ArrayList attendance;
    initList(&attendance, 5);

    insertLast(&attendance, 12);   // Student #12 came late
    insertLast(&attendance, 13);   // Student #13 came late
    insertFront(&attendance, 11);  // Student #11 is the earliest, must be at front

    printf("Attendance List:\n");
    display(&attendance);

    deleteAt(&attendance, 1);  // Teacher removes wrong entry (student #12)
    printf("\nAfter correcting mistake:\n");
    display(&attendance);

    return 0;
}

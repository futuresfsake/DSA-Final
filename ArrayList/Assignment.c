#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} ArrayList;

void initialize(ArrayList *list, int cap) {
    list->data = malloc(sizeof(int) * cap);
    if (list->data == NULL) {
        printf("Dynamic Memory Allocation failed.\n");
        exit(1);
    }
    list->size = 0;
    list->capacity = cap;
}

void display(ArrayList list) {
    printf("Data: { ");
    for (int i = 0; i < list.size; i++) {
        printf("%d", list.data[i]);
        if (i < list.size - 1) printf(", ");
    }
    printf(" }\n");
}

void resize(ArrayList *list) {
    int *temp = realloc(list->data, sizeof(int) * list->capacity * 2);
    if (!temp) {
        printf("Dynamic Memory Allocation failed.\n");
        exit(1);
    }
    list->data = temp;
    list->capacity *= 2;
}

bool insertFront(ArrayList *list, int data) {
    if (list->size == list->capacity) resize(list);

    for (int i = list->size; i > 0; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[0] = data;
    list->size++;
    return true;
}

bool insertLast(ArrayList *list, int data) {
    if (list->size == list->capacity) resize(list);

    list->data[list->size] = data;
    list->size++;
    return true;
}

bool insertAt(ArrayList *list, int pos, int data) {
    if (pos < 0 || pos > list->size) return false;
    if (list->size == list->capacity) resize(list);

    for (int i = list->size; i >= pos; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[pos] = data;
    list->size++;
    return true;
}

bool insertSorted(ArrayList *list, int data) {
    if (list->size == list->capacity) resize(list);

    int i;
    for (i = list->size; i > 0 && list->data[i - 1] > data; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[i] = data;
    list->size++;
    return true;
}

bool deleteFront(ArrayList *list) {
    if (list->size == 0) return false;

    for (int i = 1; i < list->size; i++) {
        list->data[i - 1] = list->data[i];
    }
    list->size--;
    return true;
}

bool deleteLast(ArrayList *list) {
    if (list->size == 0) return false;
    list->size--;
    return true;
}

bool deleteItem(ArrayList *list, int item) {
    int found = -1;
    for (int i = 0; i < list->size; i++) {
        if (list->data[i] == item) {
            found = i;
            break;
        }
    }
    if (found == -1) return false;

    for (int i = found; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->size--;
    return true;
}

bool deleteAllItem(ArrayList *list, int data) {
    int newSize = 0;
    for (int i = 0; i < list->size; i++) {
        if (list->data[i] != data) {
            list->data[newSize++] = list->data[i];
        }
    }
    bool deleted = (newSize != list->size);
    list->size = newSize;
    return deleted;
}

int search(ArrayList *list, int item) {
    for (int i = 0; i < list->size; i++) {
        if (list->data[i] == item) {
            return i; // return index
        }
    }
    return -1; // not found
}

bool isFound(ArrayList list, int data) {
    for (int i = 0; i < list.size; i++) {
        if (list.data[i] == data) return true;
    }
    return false;
}

bool isEmpty(ArrayList list) {
    return list.size == 0;
}

bool isFull(ArrayList list) {
    return list.size == list.capacity;
}

void SortList(ArrayList *list) {
    for (int i = 0; i < list->size - 1; i++) {
        for (int j = 0; j < list->size - i - 1; j++) {
            if (list->data[j] > list->data[j + 1]) {
                int temp = list->data[j];
                list->data[j] = list->data[j + 1];
                list->data[j + 1] = temp;
            }
        }
    }
}

int main() {
    ArrayList list;
    initialize(&list, 5);

    printf("=== Insert Operations ===\n");
    insertLast(&list, 10);
    insertLast(&list, 20);
    insertLast(&list, 30);
    display(list);

    insertFront(&list, 5);
    display(list);

    insertAt(&list, 2, 15);
    display(list);

    insertSorted(&list, 25);
    display(list);

    printf("\n=== Delete Operations ===\n");
    deleteFront(&list);
    display(list);

    deleteLast(&list);
    display(list);

    deleteItem(&list, 15);
    display(list);

    deleteAllItem(&list, 10);
    display(list);

    printf("\n=== Search & Status ===\n");
    int pos = search(&list, 25);
    if (pos != -1) {
        printf("Item found at index %d\n", pos);
    } else {
        printf("Item not found\n");
    }

    printf("List is %s\n", isEmpty(list) ? "Empty" : "Not Empty");
    printf("List is %s\n", isFull(list) ? "Full" : "Not Full");

    printf("\n=== Sorting ===\n");
    SortList(&list);
    display(list);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ===== ArrayList Definition =====
typedef struct {
    int *data;       // dynamically allocated array
    int size;        // current number of elements
    int capacity;    // total capacity
} ArrayList;

// ===== Function Declarations =====

// Create / Initialize
void initList(ArrayList *list, int initialCapacity) {
    // ArrayList* list = malloc(sizeof(ArrayList)); 

    // ! do not shadow the parameter, the caller already provides &list, no need to
    // ! allocate the arraylist, just initialize its fields

    list->data = malloc(initialCapacity * sizeof(int));
    list->size = 0;
    list->capacity = initialCapacity;

}

// Basic Operations
bool isEmpty(ArrayList *list) {
    if (list->size == 0) {
        return true;
    }

    return false;
}


int getSize(ArrayList *list) {
    return list->size;

}

// Internal Helper
void resize(ArrayList *list, int newCapacity) {

    // ! must realloc the dynamic array, not the "list", you just allocate the structure 
    
    int *temp = realloc(list->data, newCapacity * sizeof(int));
    if (!temp){
        printf("Realloc Failed.\n");
        free(list->data);
        exit(1);
    }
    list->data = temp;
    list->capacity = newCapacity;

} // grow/shrink dynamically

// Insertion
void insertAt(ArrayList *list, int index, int value) {

    if (list->size == list->capacity) {
        resize(list, list->capacity * 2); // ! be mindful of the parameters of the helper functions
    }
    
    if (index < 0 || index > list->size) {
        printf("Invalid index");
        return;
    }

    for(int i = list->size - 1; i >= index; i--) {
        list->data[i+1] = list->data[i];
    }

    list->data[index] = value;
    list->size++;
    
}
void insertFront(ArrayList *list, int value) {
    // ! shift to the left

     if (list->size == list->capacity) {
        resize(list, list->capacity * 2); // ! be mindful of the parameters of the helper functions
    }

    int i;
    for(i = list->size; i > 0; i--) {
        list->data[i] = list->data[i-1];
    }

    list->data[0] = value;
    list->size++;
    
}

void insertBack(ArrayList *list, int value) {

     if (list->size == list->capacity) {
        resize(list, list->capacity * 2); // ! be mindful of the parameters of the helper functions
    }

   


    list->data[list->size] = value;
    list->size++;
}


// Deletion
void deleteAt(ArrayList *list, int index) {
    if (list->size == 0) {
        printf("List is empty!");
        return;
    }

    if (index  < 0 || index >= list->size) {
        printf("Invalid index\n");
        return;
    }

    for(int i = index; i < list->size -1; i++) {
        list->data[i] = list->data[i+1];
    }

    list->size--;

}
void deleteFront(ArrayList *list) {
    for(int i = 1; i < list->size; i++) {
        list->data[i-1] = list->data[i];
    }
    list->size--;
}
void deleteBack(ArrayList *list) {

    list->size--;

}

// Access / Get
int getAt(ArrayList *list, int index) {
    if (index < 0 || index > list->size) {
        return -1;
    }

    return list->data[index];

}
int getFront(ArrayList *list) {
    
    if (list->size == 0) {
        return -1;
    }

    return list->data[0];
}
int getBack(ArrayList *list) {
     
    if (list->size == 0) {
        return -1;
    }

    return list->data[list->size-1];
}

// Update
void setAt(ArrayList *list, int index, int value) {
      if (index < 0 || index >= list->size) {
        return;
    }


    list->data[index] = value;
}

// Searching
int find(ArrayList *list, int value) {

    for(int i = 0; i < list->size; i++) {
        if (list->data[i] == value) {
            return i;
        
        } 
    }
    return -1;
}  // return index, -1 if not found

// Utility
void display(ArrayList *list) {
    printf("Data: \n");
    for(int i = 0; i < list->size; i++) {
        printf("%d ", list->data[i]);
    }
}

void clear(ArrayList *list) {
    free(list->data);
    list->size = 0;
    list->capacity = 0;
}        // remove all elements
void freeList(ArrayList *list) {
    free(list);
}      // free memory
int main() {
    ArrayList list;
    initList(&list, 4);   // start with capacity 4

    printf("=== Insert Operations ===\n");
    insertBack(&list, 10);
    insertBack(&list, 20);
    insertBack(&list, 30);
    insertFront(&list, 5);       // [5, 10, 20, 30]
    insertAt(&list, 2, 15);      // [5, 10, 15, 20, 30]
    display(&list);

    printf("\n\n=== Get & Set Operations ===\n");
    printf("Element at index 2: %d\n", getAt(&list, 2));   // 15
    printf("First element: %d\n", getFront(&list));        // 5
    printf("Last element: %d\n", getBack(&list));          // 30

    setAt(&list, 2, 99);          // [5, 10, 99, 20, 30]
    printf("After setting index 2 to 99:\n");
    display(&list);

    printf("\n\n=== Search ===\n");
    int idx = find(&list, 20);
    if (idx != -1)
        printf("Found 20 at index %d\n", idx);
    else
        printf("20 not found\n");

    idx = find(&list, 123);
    if (idx != -1)
        printf("Found 123 at index %d\n", idx);
    else
        printf("123 not found\n");

    printf("\n\n=== Delete Operations ===\n");
    deleteFront(&list);           // remove 5 → [10, 99, 20, 30]
    deleteBack(&list);            // remove 30 → [10, 99, 20]
    deleteAt(&list, 1);           // remove 99 → [10, 20]
    display(&list);

    printf("\n\n=== Clear ===\n");
    clear(&list);
    display(&list);

    freeList(&list);
    return 0;
}

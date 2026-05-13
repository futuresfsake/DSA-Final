#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void heapify(char *arr[], int n, int i);
void heapSort(char *arr[], int n);
void swap(char **a, char **b);
void printArray(char *arr[], int n);

int main() {
    char *arr[] = {"Charlie", "Alice", "Bob", "Eve", "David", "Frank"};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array of names: ");
    printArray(arr, n);

    heapSort(arr, n);

    printf("Sorted array of names:   ");
    printArray(arr, n);

    return 0;
}

// Swap two pointers to strings
void swap(char **a, char **b) {
    // TODO: implement swap

    char* temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify function
void heapify(char *arr[], int n, int i) {
    // TODO: implement heapify

    int pr = i;
    int child = 2 * pr +1;

    while (child < n) {
        if (child+1 < n && strcmp(arr[child+1], arr[child])>0) {
            child++;
        }

        if (strcmp(arr[pr], arr[child])>0) {
            char* temp = arr[pr];
            arr[pr] = arr[child];
            arr[child] = temp;
            pr = child;
            child = pr * 2+1;
        } else {
            break;
        }
    }
}

// Heap sort function
void heapSort(char *arr[], int n) {
    // TODO: implement heap sort

    for(int i = (n-2)/2; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for(int i = (n-1) ; i>= 0; i--) {
        heapify(arr, i, 0);
    }
}

// Utility function to print array of strings
void printArray(char *arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s ", arr[i]);
    }
    printf("\n");
}

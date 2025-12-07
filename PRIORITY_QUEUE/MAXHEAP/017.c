#include <stdio.h>

// Function Prototypes
void swap(int* a, int* b);
void heapify(int arr[], int n, int i);
void heapSort(int arr[], int n);
void printArray(int arr[], int n);

int main() {
    // Test Data
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    // Perform Sort
    heapSort(arr, n);

    printf("Sorted array:\n");
    printArray(arr, n);

    return 0;
}

// --- IMPLEMENT LOGIC BELOW ---

void swap(int* a, int* b) {
    // TODO: Implement swap logic

    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i) {
    // TODO: Implement Max Heapify logic
    // n is size of heap, i is index of root

    int pr = i;
    int child = 2 * pr +1;

    while (child < n) {
        if (child+1 < n && arr[child+1] < arr[child]) {
            child++;
        }

        if (arr[pr] > arr[child]) {
            int temp = arr[pr];
            arr[pr] = arr[child];
            arr[child] = temp;

            pr = child;
            child = 2 * pr +1;
        } else {
            break;
        }
    }
}

void heapSort(int arr[], int n) {
    // TODO: Implement Heapsort logic

    for(int i = (n-2)/2; i>= 0; i--) {
        heapify(arr, n, i);
    }

    for(int i = (n-1); i>= 0; i--) {
        heapify(arr, i, 0);
    }
}

// Utility function to help you debug
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}
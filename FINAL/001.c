#include <stdio.h>
#include <stdlib.h>


// refresher: 
//todo: the name of the array numbers, is already a pointer to its first element, just pass numbers
// * pass the address of max and min, so we can modify the original var in main
//* it is pass by reference, in main, pass the address, in parameter, use the pointer type, and inside the function body, use dereference

void maxmin (int *max, int *min, int size,  int arr[]) {

    *max = arr[0];
    *min = arr[0];

    for(int i = 0; i < size; i++) {
        if (*max < arr[i]) {
            *max = arr[i];

        }
    }


    for(int j = 0; j < size; j++) {
        if (*min > arr[j]) {
            *min = arr[j];
        }
    }
}
float findAve (int arr[], int size) {
    int sum = 0;
    for(int i = 0; i < size; i++) {
        
        sum += arr[i];
    }

    return sum/size;
}

int main() {

    int numbers[] = {15, 42, 7, 89, 23, 56, 1, 99, 4, 30};
    int size = 10;
    int max, min;
   
    maxmin(&max, &min, size, numbers);
    float avg = findAve(numbers, size);


    printf("Min is : %d\n", min);
    printf("Max is : %d\n", max);
    printf("Average is %.2f\n", avg);

}


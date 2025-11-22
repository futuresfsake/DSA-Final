#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int arr[MAX];
    int size;
} MaxHeap;

// ---- Function Prototypes ----
void init(MaxHeap *h);
bool isEmpty(MaxHeap *h);
int size(MaxHeap *h);
int getMax(MaxHeap *h);
void display(MaxHeap *h);
void insert(MaxHeap *h, int value);
int extractMax(MaxHeap *h);
void heapifyUp(MaxHeap *h, int index);
void heapifyDown(MaxHeap *h, int index);

// ---- MAIN ----
int main() {
    MaxHeap h;
    init(&h);

    insert(&h, 50);
    insert(&h, 20);
    insert(&h, 30);
    insert(&h, 10);
    insert(&h, 60);

    printf("Heap elements: ");
    display(&h);

    printf("Max element: %d\n", getMax(&h));
    printf("Extracted: %d\n", extractMax(&h));

    // printf("Heap after extract: ");
    // display(&h);

    return 0;
}

void init(MaxHeap *h) {
    
    h->size = -1;

}
bool isEmpty(MaxHeap *h) {
    return h->size == -1;
}
int size(MaxHeap *h) {
    return h->size;
}
int getMax(MaxHeap *h) {

    return h->arr[0];
}
void display(MaxHeap *h) {
    for(int i = 0; i <= h->size; i++) {
        printf("%d->", h->arr[i]);
    }
    printf("NULL\n");
}

void insert(MaxHeap *h, int value) {

    int child, pr;

    if (h->size == MAX-1) {
        printf("Heap is already full!\n");
        return;
    }

    h->size++;
    child = h->size;
    pr = (child-1) /2;

    // while (child > 0 && h->arr[pr] < value) {
    //     h->arr[child] = h->arr[pr];
    //     child = pr;
    //     pr = (child -1) /2;
    // }
    

    h->arr[child] = value;
    heapifyUp(h, child);
}


int extractMax(MaxHeap *h) {
    

    int root, swap, child, pr;

    if (h->size == -1)return -1;

    root = h->arr[0];
    h->arr[0] = h->arr[h->size];
    h->size--;

    pr = 0;
    child = 1;

    heapifyDown(h, 0);

    return root;

}
void heapifyUp(MaxHeap *h, int index) {

    int child = index;
    int pr = (child -1)/2;

    while ( child > 0 && h->arr[pr] < h->arr[child]) {

        int temp = h->arr[pr];
        h->arr[pr] = h->arr[child];
        h->arr[child] = temp;
        child = pr;
        pr = (child -1) /2;
    }


}
void heapifyDown(MaxHeap *h, int index) {
    int down, child, swap, pr;

    pr = 0;
    child = pr * 2  + 1;


        while (child <=h->size) {
        if(child +1 <= h->size && h->arr[child+1] > h->arr[child]) {
            child++;
        }

        if (h->arr[pr] < h->arr[child]) {
            swap = h->arr[pr];
            h->arr[pr] = h->arr[child];
            h->arr[child] = swap;

            pr = child;
            child = pr * 2 +1;
        }else {
            break;
        }

    }
    
    }



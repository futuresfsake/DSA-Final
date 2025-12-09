#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// --- Nested Data Structures ---

// Inner struct: Holds the string used for ordering
typedef struct {
    char username[50]; // This is the basis for priority/ordering
    char email[50];
} UserProfile;

// Outer struct: The actual element in the heap
typedef struct {
    int id;
    UserProfile profile; // Nested struct
} UserNode;

// The Heap Structure
typedef struct {
    UserNode elements[MAX_SIZE];
    int size;
} MaxHeap;

// --- Function Prototypes ---

void initHeap(MaxHeap* pq);
void swap(UserNode* a, UserNode* b);
void heapifyUp(MaxHeap* pq, int index);
void heapifyDown(MaxHeap* pq, int index);
void insert(MaxHeap* pq, int id, const char* username, const char* email);
UserNode extractMax(MaxHeap* pq);
int isEmpty(MaxHeap* pq);
void printHeap(MaxHeap* pq);

// --- Main Driver Code ---

int main() {
    MaxHeap pq;
    initHeap(&pq);

    printf("=== MaxHeap PQ (Nested Struct + String Ordering) ===\n\n");

    // Test Data: "Zoe" should be top priority in a MaxHeap (Z > A)
    // "Alice" should be lowest priority.
    printf("Inserting users...\n");
    insert(&pq, 101, "Charlie", "charlie@test.com");
    insert(&pq, 102, "Alice", "alice@test.com");
    insert(&pq, 103, "Zoe", "zoe@test.com");
    insert(&pq, 104, "Bob", "bob@test.com");
    insert(&pq, 105, "Xavier", "xavier@test.com");

    printHeap(&pq);

    printf("\nProcessing Queue (ExtractMax - Alphabetical Descending):\n");
    while (!isEmpty(&pq)) {
        UserNode processed = extractMax(&pq);
        printf("Processed ID: %d | User: %s\n", processed.id, processed.profile.username);
    }

    return 0;
}

// --- IMPLEMENT LOGIC BELOW ---

void initHeap(MaxHeap* pq) {
    // TODO: Initialize heap size

    pq->size = -1;
}

void swap(UserNode* a, UserNode* b) {
    // TODO: Swap two UserNode elements

    UserNode temp = *a;
    *a = *b;
    *b = temp;

}

void heapifyUp(MaxHeap* pq, int index) {
    // TODO: Maintain MaxHeap property upwards
    // Hint: Use strcmp(child.profile.username, parent.profile.username) > 0

    int child, pr;

    child = index;
    pr = (child-1)/2;


    while (child > 0 && strcmp(pq->elements[pr].profile.username, pq->elements[child].profile.username) < 0) {
        swap(&pq->elements[pr], &pq->elements[child]);

        child = pr;
        pr = (child-1)/2;
    }

}

void heapifyDown(MaxHeap* pq, int index) {
    // TODO: Maintain MaxHeap property downwards
    // Hint: Compare strings to find the largest child

    int pr = index;
    int child = 2 * pr +1;

    while (child <= pq->size) {
        if (child + 1<= pq->size && strcmp(pq->elements[child+1].profile.username, pq->elements[child].profile.username) > 0) {
            child++;
        }

        if(strcmp(pq->elements[pr].profile.username, pq->elements[child].profile.username)<0) {
            swap(&pq->elements[pr], &pq->elements[child]);
            pr = child;
            child = 2 * pr +1;
        } else {
            break;
        }
 
    }
}

void insert(MaxHeap* pq, int id, const char* username, const char* email) {
    // TODO: 
    // 1. Check for overflow
    // 2. Add new UserNode at the end (populate nested fields)
    // 3. Call heapifyUp

    int child, pr;

    pq->size++;
    child = pq->size;

    pq->elements[child].id = id;
    strcpy(pq->elements[child].profile.username, username);
    strcpy(pq->elements[child].profile.email, email);


    heapifyUp(pq, child);


    


}

UserNode extractMax(MaxHeap* pq) {
    // TODO:
    // 1. Check for underflow (return a dummy/empty node)
    // 2. Save the root (index 0)
    // 3. Move last element to root
    // 4. Decrease size
    // 5. Call heapifyDown
    // 6. Return saved root

    UserNode dummy = {0}; // Placeholder return
    
    if (pq->size == -1) {
        return dummy;
    }

    int child, pr;

    UserNode root, swap;

    root = pq->elements[0];
    pq->elements[0] = pq->elements[pq->size];
    pq->size--;

    heapifyDown(pq, 0);
    return root;


}

int isEmpty(MaxHeap* pq) {
    // TODO: Return 1 if empty, 0 otherwise
    if (pq->size == -1) {
        return 1;
    } else {
        return 0;
    }
}

void printHeap(MaxHeap* pq) {
    // Optional: Print array state for debugging
    // You can implement this to see the array structure

    int queue[MAX_SIZE];
    int front = 0;
    int rear = 0;

    queue[rear++] = 0;

   while (front < rear) {
        int i = queue[front++];


        printf("UName: %s | Id: %d \n", pq->elements[i].profile.username, pq->elements[i].id);


        int left = 2 * i +1;
        if (left<= pq->size) {
            queue[rear++] =left;
        }

        int right = 2 * i +2;
        if (right <= pq->size) {
            queue[rear++] = right;
        }
    }
}
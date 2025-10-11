#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10
typedef char String[30];

// =================== DATA DEFINITIONS ===================
typedef struct {
    int prodID;
    String prodName;
    int prodQty;
} Product;

// =================== ARRAYLIST QUEUE DEFINITIONS ===================
typedef struct {
    Product items[MAX];
    int front;  // index of the first element
    int rear;   // index of the last element
    int size;   // number of elements
} ProductQueue;

// =================== FUNCTION DECLARATIONS ===================
void initializeQueue(ProductQueue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

bool isEmpty(ProductQueue *q) {
    return q->size == 0;
}

bool isFull(ProductQueue *q) {
    return q->size == MAX;
}

void enqueue(ProductQueue *q, Product p) {
    
    if (isFull(q)) {
        exit(1);
    }

    if (q->front == -1 && q->rear == -1) {
        q->front = (q->front + 1) % MAX;
        q->rear = (q->rear + 1) % MAX;
        q->items[q->rear] = p;

    } 
    
    else {
        q->rear = (q->rear + 1) % MAX;
        q->items[q->rear] = p;

    }

    q->size ++;
    
}

Product dequeue(ProductQueue *q) {

    if (isEmpty(q)) {
        exit(1);

    }

    Product p;
    if (q->front == q->rear) {
         p = q->items[q->front];
        q->front = -1;
        q->rear = -1;
        
    }
    else {
     p = q->items[q->front];
    q->front = (q->front+1) % MAX;
    }
    q->size--;
    return p;
    
}

Product peekFront(ProductQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        exit(1);
    }
    return q->items[q->front];
}

void displayQueue(ProductQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue contents:\n");

    ProductQueue temp;
    initializeQueue(&temp);


    while (!isEmpty(q)) {
        Product p = dequeue((q));
        printf("Prod Name: %15s || Qty: %d\n", p.prodName, p.prodQty);
        enqueue(&temp, p);
    }

    while (!isEmpty(&temp)) {
        enqueue(q, dequeue(&temp));
    }
}

// =================== ENQUEUE SORTED ===================
// Insert a product into the queue while maintaining a sorted order
// You can sort by prodQty (descending or ascending) or by prodID.
void enqueueSorted(ProductQueue *q, Product p) {
    // TODO: Implement insertion logic to maintain sorted order


    ProductQueue temp;
    initializeQueue(&temp);

    bool insert = false;
    while (!isEmpty(q)) {
        Product curr = dequeue(q);
        
        
        if (!insert && p.prodQty > curr.prodQty ) {
            enqueue(&temp, p);
            insert = true;
        }   
        enqueue(&temp, curr);
        
    }


    if (!insert) {
        enqueue(&temp, p);
    }

    while (!isEmpty(&temp)) {
        enqueue(q, dequeue(&temp));
    }

}

// =================== MAIN ===================
int main() {
    ProductQueue inventory;
    initializeQueue(&inventory);

    // Example products
    Product p1 = {101, "Paracetamol", 50};
    Product p2 = {102, "Amoxicillin", 30};
    Product p3 = {103, "Vitamin C", 100};

    // Add using normal enqueue
    // enqueue(&inventory, p1);
    // enqueue(&inventory, p2);
    // enqueue(&inventory, p3);

    displayQueue(&inventory);

    printf("\nSort\n");
    enqueueSorted(&inventory, p1);
    enqueueSorted(&inventory, p2);
    enqueueSorted(&inventory, p3);
    displayQueue(&inventory);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// =================== DATA DEFINITIONS ===================
typedef char String[30];

typedef struct {
    int month, day, year;
} Date;

typedef struct {
    int prodID;
    String prodName;
    int prodQty;
    Date expiry;
    Date manufacture;
} Product;

// =================== LINKED LIST QUEUE DEFINITIONS ===================
typedef struct node {
    Product prod;
    struct node *next;
} Node, *NodePtr;

typedef struct {
    Node *front;   // points to first node
    Node *rear;    // points to last node
    int size;      // number of items
} ProductQueue;

// =================== FUNCTION DECLARATIONS ===================
void initializeQueue(ProductQueue *q) {
    q->front = NULL;
    q->rear = NULL;

    q->size = 0;
}
bool isEmpty(ProductQueue *q) {
    return q->front == NULL && q->rear == NULL;
}

void enqueue(ProductQueue *q, Product p) {

    NodePtr new = malloc(sizeof(Node));
    if (!new) {
        printf("Dynamic memory allocation failed.");
    }

    new->prod = p;
    new->next = NULL;


    if (isEmpty(q)) {
        q->front = new;
        q->rear = new;
        
    } else {


        q->rear->next = new;
        q->rear = new;
    }


    q->size++;


}


 Product dequeue(ProductQueue *q) {
   

    if (isEmpty(q)) {
        exit(1);
    }

    NodePtr toRemove;
    Product p;

    if (q->front == q->rear) {
       
        toRemove= q->front;
        p = toRemove->prod;
        q->front = NULL;
        q->rear = NULL;
        free(toRemove);


    } else {
         toRemove = q->front;
        q->front = toRemove->next;
        p = toRemove->prod;
        free(toRemove);
      
    }
      q->size--;
        return p;
}




Product peekFront(ProductQueue *q) {
    return q->front->prod;
}

void displayQueue(ProductQueue *q) {
    
    ProductQueue temp;
    initializeQueue(&temp);

    while (!isEmpty(q)) {
        Product P = dequeue(q);
        printf("Product: %20s || Product Quantity: %10d || Product ID: %10d\n", P.prodName, P.prodQty, P.prodID);
        enqueue(&temp, P);

    }

    while (!isEmpty(&temp)) {
        enqueue(q, dequeue(&temp));
    }


}

int searchProductByID(ProductQueue *q, int id) {
 ProductQueue temp;

 initializeQueue(&temp);
 int pid = -1;


    while (!isEmpty(q)) {
        Product p = dequeue(q);
        if (p.prodID == id) {
            pid = p.prodID;
        } 
        enqueue(&temp, p);
    }

    while (!isEmpty(&temp)) {
        enqueue(q, dequeue(&temp));
    }
    return pid;

}

void pushSorted(ProductQueue *q, Product p) {

    ProductQueue temp;
    initializeQueue(&temp);
    bool insert = false;


    while (!isEmpty(q)) {
        Product curr = dequeue(q);

        if (!insert && p.prodQty > curr.prodQty) {
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


ProductQueue AddBasedOnQuantity(ProductQueue *q, int limit);

// =================== MAIN ===================
int main() {
    ProductQueue inventory;
    initializeQueue(&inventory);

    // Create 6 products
    Product p1 = {101, "Paracetamol",   50, {12,12,2025}, {12,12,2023}};
    Product p2 = {102, "Amoxicillin",   30, { 1, 5,2026}, { 1, 5,2024}};
    Product p3 = {103, "Vitamin C",    100, { 7, 7,2027}, { 7, 7,2024}};
    Product p4 = {104, "Cough Syrup",   25, { 3, 9,2025}, { 3, 9,2023}};
    Product p5 = {105, "Ibuprofen",     40, {10, 1,2026}, {10, 1,2024}};
    Product p6 = {106, "Antihistamine", 60, { 5, 4,2026}, { 5, 4,2024}};


    

    // Insert using pushSorted (sorted by quantity, descending)
    pushSorted(&inventory, p1);
    pushSorted(&inventory, p2);
    pushSorted(&inventory, p3);
    pushSorted(&inventory, p4);
    pushSorted(&inventory, p5);
    pushSorted(&inventory, p6);

    printf("\n-----------------------------\n");
    printf("Sorted Queue by Quantity:\n");
    displayQueue(&inventory);

    printf("\n-----------------------------\n");
    Product removed = dequeue(&inventory);
    printf("Dequeued: %s (Qty %d)\n", removed.prodName, removed.prodQty);

    printf("\n-----------------------------\n");
    Product peeked = peekFront(&inventory);
    printf("Peek Front: %s (Qty %d)\n", peeked.prodName, peeked.prodQty);

    printf("\n-----------------------------\n");
    int found = searchProductByID(&inventory, 105);
    if (found > 0) {
        printf("Product with ID %d found!\n", found);
    } else {
        printf("Product with ID %d not found.\n", 105);
    }

    printf("\n-----------------------------\n");
    printf("New Queue (limit = 150 total qty):\n");
    ProductQueue limited = AddBasedOnQuantity(&inventory, 300);
    displayQueue(&limited);

    return 0;
}

ProductQueue AddBasedOnQuantity(ProductQueue *q, int limit) {
    ProductQueue temp;
    ProductQueue orig;
    initializeQueue(&temp);
    initializeQueue(&orig);

    int totalQty = 0;

    while (!isEmpty(q)) {
        
        Product p = dequeue(q);
        printf("Adding %s...", p.prodName);

        if (totalQty+p.prodQty <= limit) {
            enqueue(&orig, p);
            totalQty+= p.prodQty;
            printf("Success!\n");
            

        } else {
            printf("Failed...\n");
        }

        enqueue(&temp, p);
    }


    while (!isEmpty(&temp)) {
        enqueue(q, dequeue(&temp));
    }



    return orig;

   

}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// =================== DATA DEFINITIONS ===================
typedef char String[30];

typedef struct {
    int month;
    int day;
    int year;
} Date;

typedef struct {
    int prodID;
    String prodName;
    int prodQty;
    Date expiry;
    Date manufacture;
} Product;

typedef struct {
    Product prods[100];  // acts as an ArrayList of products
    int count;           // total products stored
} ProductList;

// =================== QUEUE DEFINITIONS ===================
typedef struct {
    ProductList list; // underlying arraylist of products
    int front;        // points to first element
    int rear;         // points to last element
    int size;         // current number of products in queue
    int capacity;     // maximum capacity
} ProductQueue;



void initializeQueue(ProductQueue* q, int capacity);
bool isEmpty(ProductQueue* q);
bool isFull(ProductQueue* q);
void enqueue(ProductQueue* q, Product p);
Product dequeue(ProductQueue* q);
Product peekFront(ProductQueue* q);

void displayQueue(ProductQueue* q);
int searchProductByID(ProductQueue* q, int id);


void pushSorted(ProductQueue *q, Product p);
ProductQueue AddBasedOnQuantity (ProductQueue *q); 


int main() {
    ProductQueue inventory;
    initializeQueue(&inventory, 15);

    Product p1  = {101, "Paracetamol",   50, {12, 12, 2025}, {12, 12, 2023}};
    Product p2  = {102, "Amoxicillin",   30, {1,  5,  2026}, {1,  5,  2024}};
    Product p3  = {103, "Vitamin C",    100, {7,  7,  2027}, {7,  7,  2024}};
    Product p4  = {104, "Cough Syrup",   25, {3,  9,  2025}, {3,  9,  2023}};
    Product p5  = {105, "Ibuprofen",     40, {10, 1,  2026}, {10, 1,  2024}};
    Product p6  = {106, "Antihistamine", 60, {5,  4,  2026}, {5,  4,  2024}};
    Product p7  = {107, "Loperamide",    35, {8,  2,  2025}, {8,  2,  2023}};
    Product p8  = {108, "Aspirin",       45, {9,  6,  2026}, {9,  6,  2024}};
    Product p9  = {109, "Multivitamins", 80, {2, 11, 2027}, {2, 11, 2024}};
    Product p10 = {110, "Antacid",       55, {6,  3,  2025}, {6,  3,  2023}};
    Product p11 = {111, "Hydrocortisone",20, {7,  8,  2026}, {7,  8,  2024}};
    Product p12 = {112, "Insulin",       15, {1, 12, 2025}, {1, 12, 2023}};
    Product p13 = {113, "Saline Soln",   70, {11, 5,  2026}, {11, 5,  2024}};
    Product p14 = {114, "Oral Rehydration",90,{3,  7,  2027}, {3,  7,  2024}};
    Product p15 = {115, "Eye Drops",     22, {4,  10, 2025}, {4, 10, 2023}};

    // === Enqueue all 15 products ===
    pushSorted(&inventory, p1);
    pushSorted(&inventory, p2);
    pushSorted(&inventory, p3);
    pushSorted(&inventory, p4);
    pushSorted(&inventory, p5);
    pushSorted(&inventory, p6);
    pushSorted(&inventory, p7);
    pushSorted(&inventory, p8);
    pushSorted(&inventory, p9);
    pushSorted(&inventory, p10);
    pushSorted(&inventory, p11);
    pushSorted(&inventory, p12);
    pushSorted(&inventory, p13);
    pushSorted(&inventory, p14);
    pushSorted(&inventory, p15);

      printf("\n-----------------------------\n");
    printf("Sort by Quantity\n");
    displayQueue(&inventory);


    printf("\n-----------------------------\n");
      Product p = dequeue(&inventory);
    printf("First product in the list is removed: %s \n", p.prodName);
    

    printf("\n-----------------------------\n");
    Product pp = peekFront(&inventory);
    printf("Peek Product is: %s\n", pp.prodName);

    
    printf("\n-----------------------------\n");
    int n = searchProductByID(&inventory, 78);
    if (n > 0) {
        printf("ID: %d is existing...\n", n);
    } else {
        printf("ID: %d is not existing...\n");
    }

    
    printf("\n-----------------------------\n");
    printf("\n--Add Base On Quantity--\n");
     
     ProductQueue new = AddBasedOnQuantity(&inventory);
    displayQueue(&new);

    // display(&inventory);
   

}

// =================== FUNCTION DECLARATIONS ===================
void initializeQueue(ProductQueue* q, int capacity) {
    q->front = -1;
    q->rear = -1;
    q->capacity = capacity;
    q->size=0;
}
bool isEmpty(ProductQueue* q) {
    return q->front == -1 && q->rear == -1;
}
bool isFull(ProductQueue* q) {
    return q->size == q->capacity;
}


void enqueue(ProductQueue* q, Product p) {
    if (q->size == q->capacity) {
        printf("Queue is full\n");
        exit(1);
    }



    if (isEmpty(q)) {
        q->front = (q->front+ 1 )% q->capacity;
        q->rear = (q->rear + 1 )% q->capacity;
        q->list.prods[q->rear] = p;
        
        
    } else {
        q->rear = (q->rear + 1 )% q->capacity;
        q->list.prods[q->rear] = p;
    }

    q->size++;

    
}


Product dequeue(ProductQueue* q) {

    if (q->front == -1 && q->rear == -1) {
        printf("List is empty.\n");
        exit(1);
    }
   
    Product p;
    if (q->front == q->rear) {
        p = q->list.prods[q->front];
        q->front = -1;
        q->rear = -1;
        
        
    } else {
        p = q->list.prods[q->front];
        q->front = (q->front + 1) % q->capacity;
        
    }
    q->size--;


    return p;
}

Product peekFront(ProductQueue* q) {
    return q->list.prods[q->front];
}

void displayQueue(ProductQueue* q) {
    ProductQueue temp;
    initializeQueue(&temp, q->capacity);


    while (!isEmpty(q)) {
        Product p = dequeue(q);
        printf("Product Name: %20s || Quantity: %5d || ID: %5d\n", p.prodName, p.prodQty, p.prodID);
        enqueue(&temp, p);
    }


    while (!isEmpty(&temp)) {
        enqueue(q, dequeue(&temp));
    }
}

ProductQueue AddBasedOnQuantity(ProductQueue *q) 
{
    ProductQueue orig, temp;
    initializeQueue(&orig, q->capacity);
    initializeQueue(&temp, q->capacity);

    int totalQty = 0;
    int limit = 400;


    while (!isEmpty(q)) {
        Product p = dequeue(q);

        if (totalQty + p.prodQty <=limit) {
            enqueue(&orig, p);
            totalQty+= p.prodQty;
            printf("%s successfully enqueued.\n", p.prodName);
        } else {
            printf("%s Limit exceeded.\n", p.prodName);

        }

        enqueue(&temp, p);
    }

    while (!isEmpty(&temp)) {
        enqueue(q, dequeue(&temp));

    }
    return orig;
}
int searchProductByID(ProductQueue* q, int id) {

    ProductQueue temp;
    initializeQueue(&temp, q->capacity);
    int pid = -1;

    while (!isEmpty(q)) {
        Product p = dequeue(q);
        if (p.prodID == id ) {
            pid = p.prodID;
        } 
        enqueue(&temp, p);

    }


        while (!isEmpty(&temp)) {
            enqueue(q, dequeue(&temp));
        }
    return pid;
}



void  pushSorted(ProductQueue *q, Product p)
 {
    ProductQueue temp;
    initializeQueue(&temp, q->capacity);
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
 


    
    








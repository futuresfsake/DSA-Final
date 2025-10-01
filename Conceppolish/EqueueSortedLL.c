#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef char String[30];

// =================== DATA DEFINITIONS ===================
typedef struct {
    int prodID;
    String prodName;
    int prodQty;
} Product;

// =================== LINKED LIST QUEUE DEFINITIONS ===================
typedef struct node {
    Product prod;
    struct node *next;
} Node, *NodePtr;

typedef struct {
    Node *front;  // points to first node
    Node *rear;   // points to last node
    int size;     // number of items
} ProductQueue;

// =================== FUNCTION DECLARATIONS ===================
void initializeQueue(ProductQueue *q) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

bool isEmpty(ProductQueue *q) {
    return q->front == NULL;
}

// Normal enqueue
void enqueue(ProductQueue *q, Product p) {

    NodePtr temp = malloc(sizeof(Node));
    if (!temp) {
        printf("Dynamic memory allocation failed.\n");
        exit(1);
    }
    temp->prod = p;
    temp->next = NULL;
   
    if (isEmpty(q)) {
        q->front = temp;
        q->rear = temp;
        q->size++;
        
    } else {
        q->rear->next = temp;
        q->rear = temp;
        q->size++;
        
    }
    printf("%s success!\n", p.prodName);
    
}

// Normal dequeue
Product dequeue(ProductQueue *q) {
   
    if(isEmpty(q)) {
        printf("Underflow\n");
        exit(1);
    }

    Product p;
    NodePtr remove;

    
    if (q->front == q->rear) {
        remove = q->front;
        p = remove->prod;
        q->front = NULL;
        q->rear = NULL;
        q->size--;
        
    } else {



        remove = q->front;
        q->front = remove->next;
        p = remove->prod;
        
        q->size--;
       
    }

    free(remove);
        return p;
}

// Peek front
Product peekFront(ProductQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        exit(1);
    }
    return q->front->prod;
}

// Display queue
void displayQueue(ProductQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }

    NodePtr current = q->front;
    printf("Queue contents:\n");
    while (current) {
        printf("ID: %d | Name: %s | Qty: %d\n",
               current->prod.prodID,
               current->prod.prodName,
               current->prod.prodQty);
        current = current->next;
    }
}

// =================== ENQUEUE SORTED ===================
// Insert a product into the queue while maintaining sorted order
void enqueueSorted(ProductQueue *q, Product p) {

   
   ProductQueue qq;
   initializeQueue(&qq);
   bool flag = false;
   
   while (!isEmpty(q)) {
       Product pp = dequeue(q);
       
       if (!flag && p.prodQty > pp.prodQty) {
           enqueue(&qq, p);
           flag = true;
       } 
       enqueue(&qq, pp);
   }
   
   
   if (!flag){
       enqueue(&qq, p);
   }
   
   while (!isEmpty(&qq)) {
       enqueue(q, dequeue(&qq));
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
    enqueueSorted(&inventory, p1);
    enqueueSorted(&inventory, p2);
    enqueueSorted(&inventory, p3);

    displayQueue(&inventory);

    // TODO: Test enqueueSorted here

    return 0;
}

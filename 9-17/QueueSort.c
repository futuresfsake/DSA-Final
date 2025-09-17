#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 10

typedef struct {
    int date;
    int month;
    int year;
} Date;

typedef struct {
    int prodID;
    char prodName[20];
    Date prodExp;
    float prodPrice;
    int prodQty;
} Product;

typedef struct {
    Product prods[MAX];
    int front;
    int rear;
} Queue;

typedef Product ProductStk[MAX];

void populateStack(ProductStk s);
Product createProduct(int id, char name[], Date dexp, float price, int qty);

int isLeap(int year);
int countDays(Date d);
int dateDifference(Date d1, Date d2);
void displayDate(Date d);

Queue createQueue();
bool enqueue(Queue *q, Product p);
Product dequeue(Queue *q);
Product front(Queue q);
bool isEmpty(Queue q);
bool isFull(Queue q);

void displayTravesal(Queue q);

// 🔹 Function you will implement: sorted enqueue
void enqueueSorted(Queue *q, Product p) {
    // Step 1: Check if queue is full
    // Step 2: Create a temporary queue
    // Step 3: Traverse the original queue with a for loop
    // Step 4: Compare expiry dates using countDays()
    // Step 5: Insert product p at correct position
    // Step 6: Copy everything back to the original queu
    

    if (isFull(*q)) return;

    Queue temp = createQueue();
    bool inserted = false;

    for (int i = q->front; i != (q->rear + 1) % MAX; i = (i + 1) % MAX) {
        Product cur = q->prods[i];

        if (!inserted && countDays(p.prodExp) < countDays(cur.prodExp)) {
            enqueue(&temp, p);
            inserted = true;
        }
        enqueue(&temp, cur);
    }

    if (!inserted) {
        enqueue(&temp, p);
    }

    *q = temp;
}

int main() {
  

    // ! create Queue, Stac;
    // ! populate

    Queue q  = createQueue();
     ProductStk prodStk;
    populateStack(prodStk);



    // Step 1: Loop through stack items (from 1 to prodStk[0].prodID)
    for(int i = 0; i < prodStk[0].prodID; i++) {
        enqueueSorted(&q, prodStk[i]);
    }
    // Step 2: Call enqueueSorted(&prodQ, prodStk[i]) to insert into queue

    displayTravesal(q);
    // Step 3: Display queue using displayTravesal(prodQ)

    return 0;
}

int isLeap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int countDays(Date d) {
    static int monthDays[12] = {31, 28, 31, 30, 31, 30,
                                31, 31, 30, 31, 30, 31};
    int days = d.year * 365 + d.date;

    for (int i = 0; i < d.month - 1; i++)
        days += monthDays[i];

    days += d.year / 4 - d.year / 100 + d.year / 400;

    if (isLeap(d.year) && d.month > 2)
        days += 1;

    return days;
}

int dateDifference(Date d1, Date d2) {
    return countDays(d2) - countDays(d1);
}

void displayDate(Date d) {
    char monthName [12][5] = {"Jan", "Feb", "Mar",
        "Apr", "May", "Jun",
        "Jul", "Aug", "Sep",
        "Oct", "Nov", "Dec",
    };
    
    printf("%02d %s %d", d.date, monthName[d.month], d.year);
}

Queue createQueue() {
    Queue q;
    
    q.front = 0;
    q.rear = MAX - 1;
    
    return q;
}

bool enqueue(Queue *q, Product p) {
    if(isFull(*q)) {
        return false;
    }
    
    q->rear = (q->rear + 1) % MAX;
    q->prods[q->rear] = p;
    
    return true;
}

Product dequeue(Queue *q) {
    Product p = q->prods[q->front];
    q->front = (q->front + 1) % MAX;
   
    return p;
}

Product front(Queue q) {
    return q.prods[q.front];
}

bool isEmpty(Queue q) {
    return (q.rear + 1) % MAX == q.front;    
}

bool isFull(Queue q) {
    return (q.rear + 2) % MAX == q.front;    
}

void displayTravesal(Queue q) {
    Product p;
    printf("%10s | %10s | %11s | %10s | %s\n", "ID", "NAME", "DATE EXPIRY", "PRICE", "QTY");

    for (int i = q.front; i != (q.rear + 1) % MAX; i = (i + 1) % MAX) {
        p = q.prods[i];
        printf("%10d | %10s | ", p.prodID, p.prodName);
        displayDate(p.prodExp);
        printf(" | Php %6.2f | %d\n", p.prodPrice, p.prodQty);
    }

    printf("\n");
}

Date createDate(int date, int month, int year) {
    Date d;
    
    d.date = date;
    d.month = month;
    d.year = year;
    
    return d;
}

Product createProduct(int id, char name[], Date dexp, float price, int qty) {
    Product p;
    
    p.prodID = id;
    strcpy(p.prodName, name);
    p.prodExp = dexp;
    p.prodPrice = price;
    p.prodQty = qty;
    
    return p;
}

void populateStack(ProductStk s) {
    s[0] = createProduct(3, "", createDate(0, 0, 0), 0.0, 0);
    s[1] = createProduct(1005, "Binangkal", createDate(15, 6, 2026), 12.50, 40);
    s[2] = createProduct(1010, "Bingka", createDate(12, 7, 2027), 20.00, 5);
    s[3] = createProduct(1020, "Budbud", createDate(12, 7, 2027), 20.00, 5);
}

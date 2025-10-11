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

// =================== STACK DEFINITIONS ===================
typedef struct node {
    Product prod;
    struct node *link;
} NodeType, *NodePtr;

typedef struct {
    NodePtr top;
    int currQty;
} Inventory;

// =================== STACK FUNCTIONS ===================
void initInventory(Inventory *i) {
    i->top = NULL;
    i->currQty = 0;
}

bool isEmpty(Inventory i) {
    return i.top == NULL;
}

// =================== DATE UTILITIES ===================
int daysInMonth(int month, int year) {
    switch(month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2:
            if ((year%4==0 && year%100!=0) || (year%400==0)) return 29;
            return 28;
        default: return -1;
    }
}

int dateDifference(Date d1, Date d2) {
    int days1 = d1.day + (d1.month - 1) * daysInMonth(d1.month, d1.year) + d1.year * 365;
    int days2 = d2.day + (d2.month - 1) * daysInMonth(d2.month, d2.year) + d2.year * 365;
    return days2 - days1;
}

// =================== DISPLAY ===================
void displayDate(Date d) {
    char *months[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    printf("%02d %s %4d", d.day, months[d.month-1], d.year);
}

void displayProduct(Product p) {
    printf("%03d | %-25s | %-5d | ", p.prodID, p.prodName, p.prodQty);
    displayDate(p.expiry);
    printf(" | ");
    displayDate(p.manufacture);
    printf("\n");
}

void visualize(Inventory i) {
    NodePtr trav = i.top;
    while(trav != NULL) {
        displayProduct(trav->prod);
        trav = trav->link;
    }
    printf("Count: %d\n", i.currQty);
}

// =================== ADD PRODUCT BASED ON EXPIRY ===================
// Expired or near-expiry products must be placed on TOP
// Total inventory capacity = 100 qty
bool addProductBaseOnExpiry(Inventory *inv, Product p, Date today) {
    if (inv->currQty + p.prodQty > 100) {
        printf("Adding %s (%d): Fail\n", p.prodName, p.prodQty);
        return false;
    }

    // determine if product is expired or near expiry (<= 365 days)
    int diff = dateDifference(today, p.expiry);

    NodePtr newNode = (NodePtr) malloc(sizeof(NodeType));
    newNode->prod = p;
    newNode->link = NULL;

    if (diff <= 365) {
        // expired/near expiry -> always push to top
        newNode->link = inv->top;
        inv->top = newNode;
    } else {
        // not near expiry -> insert at bottom
        if (inv->top == NULL) {
            inv->top = newNode;
        } else {
            NodePtr trav = inv->top;
            while(trav->link != NULL) {
                trav = trav->link;
            }
            trav->link = newNode;
        }
    }

    inv->currQty += p.prodQty;
    printf("Adding %s (%d): Success\n", p.prodName, p.prodQty);
    return true;
}

// =================== MAIN DEMO ===================
int main() {
    Inventory inv;
    initInventory(&inv);

    Date today = {9, 17, 2025};

    Product P1 = {15, "Basi", 16, {9, 21, 2024}, {4, 20, 2020}};
    Product P2 = {16, "San Miguel Beer", 4, {11, 12, 2024}, {3, 20, 2021}};
    Product P3 = {17, "Royal tru", 12, {5, 10, 2026}, {1, 20, 2023}};
    Product P4 = {18, "Sarsi", 28, {5, 7, 2026}, {7, 20, 2020}};
    Product P5 = {19, "Jaz Cola", 32, {5, 14, 2026}, {10, 20, 2020}};
    Product P6 = {20, "Pop Cola", 64, {5, 18, 2026}, {11, 20, 2020}};
    Product P7 = {21, "Cheers", 21, {5, 21, 2026}, {4, 20, 2020}};
    Product P8 = {22, "Lemo Lime", 3, {5, 12, 2026}, {3, 20, 2021}};

    addProductBaseOnExpiry(&inv, P1, today);
    visualize(inv);
    addProductBaseOnExpiry(&inv, P2, today);
    visualize(inv);
    addProductBaseOnExpiry(&inv, P3, today);
    visualize(inv);
    addProductBaseOnExpiry(&inv, P4, today);
    visualize(inv);
    addProductBaseOnExpiry(&inv, P5, today);
    visualize(inv);
    addProductBaseOnExpiry(&inv, P6, today);
    visualize(inv);
    addProductBaseOnExpiry(&inv, P7, today);
    visualize(inv);
    addProductBaseOnExpiry(&inv, P8, today);
    visualize(inv);

    return 0;
}

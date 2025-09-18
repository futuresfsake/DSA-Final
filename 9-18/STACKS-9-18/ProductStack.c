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
    Product prods[100];
    int count;
} ProductList;

// =================== STACK DEFINITIONS ===================
typedef struct node {
    Product prod;
    struct node *link;
} NodeType, *NodePtr;

typedef struct {
    NodePtr top;
    int currQty;
} Inventory;

// =================== FUNCTION DECLARATIONS ===================
Date createDate(int month, int day, int year);
Product createProduct(int prodID, String prodName, int prodQty, Date expiry, Date manufacture);
void displayDate(Date d);
void displayProduct(Product p);
int daysInMonth(int month, int year);
int dateDifference(Date d1, Date d2);
void createAndPopulate(ProductList *prod, int selection, int n);

void initInventory(Inventory *i);
bool isEmpty(Inventory i);
bool push(Inventory *i, Product p);
bool pop(Inventory *i);
Product peek(Inventory i);
void visualize(Inventory i);

bool addProductBaseOnExpiry(Inventory *i, Product p);

// =================== DATA FUNCTIONS ===================
Date createDate(int month, int day, int year) {
    Date d;
    d.month = month;
    d.day = day;
    d.year = year;
    return d;
}

Product createProduct(int prodID, String prodName, int prodQty, Date expiry, Date manufacture) {
    Product p;
    p.prodID = prodID;
    strcpy(p.prodName, prodName);
    p.prodQty = prodQty;
    p.expiry = expiry;
    p.manufacture = manufacture;
    return p;
}

void displayDate(Date d) {
    const char *months[12] = {
        "Jan","Feb","Mar","Apr","May","Jun",
        "Jul","Aug","Sep","Oct","Nov","Dec"
    };
    printf("%02d %s %4d", d.day, months[d.month-1], d.year);
}

void displayProduct(Product p) {
    printf("%03d | %-25s | %-5d | ", p.prodID, p.prodName, p.prodQty);
    displayDate(p.expiry);
    printf(" | ");
    displayDate(p.manufacture);
    printf("\n");
}

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

void createAndPopulate(ProductList *prod, int selection, int n) {
    Product prods[28];

    prods[0] = createProduct(1, "Sago't Gulaman", 30, createDate(1, 20, 2025), createDate(1, 20, 2022));
    prods[1] = createProduct(2, "Guinumis", 24, createDate(5, 12, 2024), createDate(7, 15, 2023));
    prods[2] = createProduct(3, "Calamansi Juice", 60, createDate(10, 1, 2024), createDate(5, 12, 2023));
    prods[3] = createProduct(4, "Mango Juice", 15, createDate(12, 25, 2024), createDate(6, 6, 2022));
    prods[4] = createProduct(5, "Melon Juice", 18, createDate(7, 31, 2025), createDate(8, 1, 2021));
    prods[5] = createProduct(6, "Guyabano Juice", 49, createDate(1, 1, 2025), createDate(1, 1, 2022));
    prods[6] = createProduct(7, "Buko Juice", 5, createDate(5, 23, 2025), createDate(9, 10, 2022));
    prods[7] = createProduct(8, "Buko Pandan Drink", 25, createDate(6, 21, 2024), createDate(6, 6, 2022));
    prods[8] = createProduct(9, "Kapeng Barako", 12, createDate(1, 11, 2026), createDate(1, 15, 2024));
    prods[9] = createProduct(10, "Salabat", 8, createDate(7, 15, 2029), createDate(3, 12, 2024));
    prods[10] = createProduct(11, "Lambanog", 26, createDate(9, 10, 2024), createDate(1, 20, 2023));
    prods[11] = createProduct(12, "Tuba", 12, createDate(7, 7, 2024), createDate(7, 20, 2020));
    prods[12] = createProduct(13, "Bignay Wine", 4, createDate(11, 14, 2023), createDate(10, 20, 2020));
    prods[13] = createProduct(14, "Tapuy", 13, createDate(12, 18, 2026), createDate(11, 20, 2020));
    prods[14] = createProduct(15, "Basi", 16, createDate(9, 21, 2024), createDate(4, 20, 2020));
    prods[15] = createProduct(16, "San Miguel Beer", 4, createDate(11, 12, 2024), createDate(3, 20, 2021));
    prods[16] = createProduct(17, "Royal tru", 12, createDate(5, 10, 2026), createDate(1, 20, 2023));
    prods[17] = createProduct(18, "Sarsi", 28, createDate(5, 7, 2026), createDate(7, 20, 2020));
    prods[18] = createProduct(19, "Jaz Cola", 32, createDate(5, 14, 2026), createDate(10, 20, 2020));
    prods[19] = createProduct(20, "Pop Cola", 64, createDate(5, 18, 2026), createDate(11, 20, 2020));
    prods[20] = createProduct(21, "Cheers", 21, createDate(5, 21, 2026), createDate(4, 20, 2020));
    prods[21] = createProduct(22, "Lemo Lime", 3, createDate(5, 12, 2026), createDate(3, 20, 2021));
    prods[22] = createProduct(23, "RC Cola", 5, createDate(6, 10, 2026), createDate(1, 20, 2023));
    prods[23] = createProduct(24, "Lift", 6, createDate(8, 7, 2026), createDate(7, 20, 2020));
    prods[24] = createProduct(25, "Teem", 8, createDate(4, 14, 2026), createDate(10, 20, 2020));
    prods[25] = createProduct(26, "Zest-O", 12, createDate(3, 18, 2026), createDate(11, 20, 2020));
    prods[26] = createProduct(27, "Yacult", 5, createDate(3, 21, 2026), createDate(4, 20, 2020));
    prods[27] = createProduct(28, "Milk Tea", 4, createDate(4, 12, 2026), createDate(3, 20, 2021));

    n = (n > 28)? 28 : n;
    bool flag = false;
    prod->count = 0;

    for(int i = 0; i < 28 && prod->count < n; ++i) {
        switch(selection) {
            case 1:
                prod->prods[(prod->count)++] = prods[i];
                break;
            case 2:
                prod->prods[(prod->count)++] = prods[i];
                ++i;
                break;
            case 3:
                ++i;
                prod->prods[(prod->count)++] = prods[i];
                break;
            case 4:
                if(!flag) { i = 14; flag = true; }
                prod->prods[(prod->count)++] = prods[i];
                break;
            case 5:
                if(!flag) { i = 14; flag = true; }
                prod->prods[(prod->count)++] = prods[i];
                ++i;
                break;
            case 6:
                if(!flag) { i = 14; flag = true; }
                ++i;
                prod->prods[(prod->count)++] = prods[i];
                break;
        }
    }
}

// =================== STACK FUNCTIONS ===================
void initInventory(Inventory *i) {
    i->top = NULL;
    i->currQty = 0;
}

bool isEmpty(Inventory i) {
    return i.top == NULL;
}

bool push(Inventory *i, Product p) {
    NodePtr temp = malloc(sizeof(NodeType));
    if (!temp) return false;
    temp->prod = p;
    temp->link = i->top;
    i->top = temp;
    i->currQty += p.prodQty;
    return true;
}

bool pop(Inventory *i) {
    if (isEmpty(*i)) return false;
    NodePtr temp = i->top;
    i->top = temp->link;
    i->currQty -= temp->prod.prodQty;
    free(temp);
    return true;
}

Product peek(Inventory i) {
    return i.top->prod;
}

void visualize(Inventory i) {
    NodePtr trav = i.top;
    while(trav) {
        displayProduct(trav->prod);
        trav = trav->link;
    }
    printf("Count: %d\n", i.currQty);
}

// =================== ADD PRODUCT BASED ON EXPIRY ===================
// Stack discipline: your original logic
bool addProductBaseOnExpiry(Inventory *i, Product p) {
   Inventory tempStack;
   tempStack.top = NULL;
   tempStack.currQty = 0;

   NodePtr tempHolder = NULL;


   NodePtr newProduct = malloc(sizeof(NodeType));
   if (!newProduct) {
    printf("Dynamic Memory allocation failed.\n");
    return false;
   }

   newProduct->prod = p;
   newProduct->link = NULL;


   if (i->currQty + p.prodQty > 100) {
    
    return false;
   }

   while (i->top != NULL && dateDifference(i->top->prod.expiry, p.expiry) >= 0) {
    tempHolder = i->top;
    i->top = tempHolder->link;

    tempHolder->link = tempStack.top;
    tempStack.top = tempHolder;
   }



   newProduct->link = i->top;
   i->top = newProduct;
   
   i->currQty += p.prodQty;


   while (tempStack.top != NULL) {
    tempHolder = tempStack.top;
    tempStack.top = tempHolder->link;

    tempHolder->link = i->top;
    i->top = tempHolder;
   }
   


   return true;
}

// =================== MAIN ===================
int main() {
    ProductList myProd;
    int numCount, selection;

    printf("Enter sequence or selection: (1-6): ");
    scanf("%d", &selection);
    printf("Enter the number of data: ");
    scanf("%d", &numCount);

    createAndPopulate(&myProd, selection, numCount);

    Inventory myInventory;
    initInventory(&myInventory);

    printf("\nORIGINAL PRODUCT:\n");
    for(int i = 0; i < myProd.count; ++i) {
        displayProduct(myProd.prods[i]);
    }
    
    for(int i = 0; i < myProd.count; ++i) {
        printf("\n[%d.] Adding %s (%d): %s\n", i+1, myProd.prods[i].prodName,
               myProd.prods[i].prodQty,
               addProductBaseOnExpiry(&myInventory, myProd.prods[i]) ? "Success":"Fail");
        visualize(myInventory);
    }

    printf("\nUSING ADD PRODUCT:\n");
    visualize(myInventory);

    return 0;
}

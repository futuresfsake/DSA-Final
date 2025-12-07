#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITEMS 200

// ================= STRUCTS =================
typedef struct {
    int quantity;
    char aisle_loc[10];
} StockInfo;

typedef struct {
    char sku_code[20]; // e.g. "XR-500", "AB-100"
    StockInfo info;
} InventoryItem;

typedef struct {
    InventoryItem data[MAX_ITEMS];
    int total; // zero-based index of last element
} InventoryHeap;

// ================= PROTOTYPES =================
// Heap Core
void createInventory(InventoryHeap* h);
void addItem(InventoryHeap* h, char* sku, int qty, char* loc);
InventoryItem scanHighestSKU(InventoryHeap* h);
void fixUp(InventoryHeap* h, int k);
void fixDown(InventoryHeap* h, int k);
bool isEmpty(InventoryHeap* h);

// HeapSort
void heapSortInventory(InventoryItem arr[], int n);
void siftDownSort(InventoryItem arr[], int n, int i);

// Display
void printInventory(InventoryItem arr[], int n);


// ================= MAIN =================
int main() {
    InventoryHeap wh;
    createInventory(&wh);

    printf("=== Warehouse SKU Audit (MaxHeap: Z-A) ===\n");

    addItem(&wh, "AB-100", 50, "A1");
    addItem(&wh, "XR-500", 10, "Z9"); // "Largest" string
    addItem(&wh, "MM-300", 25, "M5");
    addItem(&wh, "BB-200", 40, "B2");

    printf("\n--- MaxHeap Contents ---\n");
    printInventory(wh.data, wh.total);

    printf("\n--- Scanning Highest SKU ---\n");
    InventoryItem item = scanHighestSKU(&wh);
    printf("Auditing Item: %s (Qty: %d)\n", item.sku_code, item.info.quantity);

    printf("\n--- Heap After Removing Max ---\n");
    printInventory(wh.data, wh.total);

    // =====================
    // HEAPSORT DEMO
    // =====================
    printf("\n--- HeapSort Demo (Descending SKU) ---\n");
    heapSortInventory(wh.data, wh.total);
    printInventory(wh.data, wh.total);

    return 0;
}


void createInventory(InventoryHeap* h) {
    h->total = 0;
}
void addItem(InventoryHeap* h, char* sku, int qty, char* loc) {

    
    if (h->total == MAX_ITEMS) {
        printf("Items are already full!\n");
        return;
    }

    int child = h->total;
    int pr = (child-1)/2;

    while (child > 0 && strcmp(h->data[pr].sku_code, sku) < 0) {
        h->data[child] = h->data[pr];
        child = pr;
        pr = (child-1)/2;
    }

    strcpy(h->data[child].info.aisle_loc, loc);
    h->data[child].info.quantity= qty;
    strcpy(h->data[child].sku_code, sku);

    h->total++;
}


InventoryItem scanHighestSKU(InventoryHeap* h) {

    InventoryItem root, swap, dummy;

    if (h->total == 0) return dummy;

    

    int child, pr;

    root = h->data[0];
    h->data[0] = h->data[h->total-1];
    h->total--;


    pr = 0;
    child = 2 * pr +1;

    while (child < h->total) {
        if (child+1 < h->total && strcmp(h->data[child+1].sku_code, h->data[child].sku_code) > 0) {
            child++;
        }

        if (strcmp(h->data[pr].sku_code, h->data[child].sku_code) < 0) {
            swap = h->data[pr];
            h->data[pr] = h->data[child];
            h->data[child] = swap;

            pr = child;
            child = 2 * pr +1;
        } else {
            break;
        }
    }

    return root;

}

void fixUp(InventoryHeap* h, int k) {

    int child = k;
    int pr = (child-1)/2;


    while (child > 0 && strcmp(h->data[pr].sku_code, h->data[child].sku_code) < 0) {
        InventoryItem swap = h->data[pr];
        h->data[pr] = h->data[child];
        h->data[child] = swap;

        child = pr;
        pr= (child-1)/2;
    }
}


void fixDown(InventoryHeap* h, int k) {

    int pr = k;
    int child = (2 * pr +1);

    while (child < h->total) {
        if (child+1 < h->total && strcmp(h->data[child+1].sku_code, h->data[child].sku_code) > 0) {
            child++;
        }

        if (strcmp(h->data[pr].sku_code, h->data[child].sku_code) < 0) {
            InventoryItem swap = h->data[pr];
        h->data[pr] = h->data[child];
        h->data[child] = swap;

        pr = child;
        child = 2 * pr +1;
        }
    }

}


bool isEmpty(InventoryHeap* h) {
    return h->total == 0;
}

// // HeapSort
void heapSortInventory(InventoryItem arr[], int n) {

    
    for(int i = (n-2)/2; i>= 0; i--) {
        siftDownSort(arr, n, i);
    }

    for(int i = n-1; i>= 0; i--) {
        InventoryItem swap = arr[0];
        arr[0] = arr[i];
        arr[i] = swap;
        siftDownSort(arr, i, 0);
    }
}
void siftDownSort(InventoryItem arr[], int n, int i) {


   int pr = i;
    int child = 2 * pr +1;


    while (child < n) {
        if (child +1 < n && strcmp(arr[child+1].sku_code, arr[child].sku_code) > 0) {
            child++;
        }

        if (strcmp(arr[pr].sku_code, arr[child].sku_code) < 0) {
            InventoryItem swap = arr[pr];
            arr[pr] = arr[child];
            arr[child] = swap;

            pr = child;
            child = 2 * pr +1;
        } else {
            break;
        }
    }
}

// // Display
void printInventory(InventoryItem arr[], int n) {
    printf("=== Inventory List ===\n");

    for (int i = 0; i <n; i++) {
        printf("SKU: %s | Quantity: %d | Location: %s\n",
               arr[i].sku_code,
               arr[i].info.quantity,
               arr[i].info.aisle_loc);
    }
    printf("\n");
}

#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define MAX_LOGS 10

// ================= STRUCTS =================
typedef struct {
    char ip_addr[16];
    int severity_code;
} LogDetails;

typedef struct {
    char timestamp[25];   // YYYY-MM-DD HH:MM:SS
    LogDetails details;
} LogEntry;

typedef struct {
    LogEntry entries[MAX_LOGS];
    int size;
} LogHeap;


// ================= PROTOTYPES =================
// Heap Core
void initLog(LogHeap* h);
void pushLog(LogHeap* h, const char* time, const char* ip, int sev);
LogEntry popOldestLog(LogHeap* h);
void siftUp(LogHeap* h, int i);
void siftDown(LogHeap* h, int i);
bool isEmpty(LogHeap* h);

// HeapSort
void heapSortLogs(LogEntry arr[], int n);
void heapSortLogs(LogEntry arr[], int n);
// Display
void printLogs(LogEntry arr[], int n);


// ================= MAIN =================
int main() {
    LogHeap logs;
    initLog(&logs);

    printf("=== Security Log Processor (MinHeap: Oldest First) ===\n");

    pushLog(&logs, "2025-12-01 10:00:00", "192.168.1.5", 1);
    pushLog(&logs, "2025-11-30 23:59:59", "10.0.0.1", 3);
    pushLog(&logs, "2025-12-01 10:00:01", "172.16.0.5", 2);

    // printf("\n--- Processing Timeline (POP) ---\n");
    // while (!isEmpty(&logs)) {
    //     LogEntry l = popOldestLog(&logs);
    //     printf("[%s] Source: %s\n", l.timestamp, l.details.ip_addr);
    // }

    printf("Sorting..\n");
    heapSortLogs(logs.entries, logs.size + 1);
    // Print sorted logs
    printLogs(logs.entries, logs.size + 1);

    // printf("\n--- Processing Timeline (POP) ---\n");
    // while (!isEmpty(&logs)) {
    //     LogEntry l = popOldestLog(&logs);
    //     printf("[%s] Source: %s\n", l.timestamp, l.details.ip_addr);
    // }


    // =====================
    // HEAPSORT DEMO
    // =====================
    // printf("\n=== HEAPSORT DEMO ===\n");

    // LogEntry arr[5] = {
    //     {"2025-12-01 08:10:00", {"1.1.1.1", 1}},
    //     {"2025-11-30 20:00:00", {"2.2.2.2", 2}},
    //     {"2025-12-01 12:00:00", {"3.3.3.3", 3}},
    //     {"2025-10-31 15:45:30", {"4.4.4.4", 1}},
    //     {"2025-12-01 08:10:01", {"5.5.5.5", 4}}
    // };

    // int n = 5;

    // printf("\nBefore Sorting:\n");
    // printLogs(arr, n);

    // heapSortLogs(arr, n);

    // printf("\nAfter HeapSort (Oldest First):\n");
    // printLogs(arr, n);

    return 0;
}


// ================= IMPLEMENTATION =================
// NOTE: YOU will implement these.
//       They are intentionally empty.

void initLog(LogHeap* h) {
    h->size = -1;
}

void pushLog(LogHeap* h, const char* time, const char* ip, int sev) {

    if (h->size == MAX_LOGS-1) {
        printf("Log is already full!\n");
        return;
    }

    int child, pr;

    h->size++;
    child = h->size;
    pr = (child-1)/2;

    while (child > 0 && strcmp(h->entries[pr].timestamp, time) > 0) {
        h->entries[child] = h->entries[pr];
        child = pr;
        pr = (child-1)/2;
    }

    strcpy(h->entries[child].timestamp, time);
    strcpy(h->entries[child].details.ip_addr, ip);
    h->entries[child].details.severity_code = sev;
}

LogEntry popOldestLog(LogHeap* h) {
    LogEntry dummy = {0};

    if (isEmpty(h)) {
    return dummy;
    }


    LogEntry root, swap;

    int child, pr;

    root = h->entries[0];
    h->entries[0] = h->entries[h->size];
    h->size--;

    pr = 0;
    child = 2 * pr+1;

    while (child <= h->size) {
        if (child+1 <= h->size && strcmp(h->entries[child+1].timestamp, h->entries[child].timestamp)<0) {
            child++;
        }

        if (strcmp(h->entries[pr].timestamp, h->entries[child].timestamp) > 0) {
            swap = h->entries[pr];
            h->entries[pr] = h->entries[child];
            h->entries[child] = swap;

            pr = child;
            child = 2 * pr +1;
        } else {
            break;
        }
    }

    return root;
}

void siftUp(LogHeap* h, int i) {

    int child = i;
    int pr = (child-1)/2;


    while (child > 0 && strcmp(h->entries[pr].timestamp, h->entries[child].timestamp)>0) {
        LogEntry swap = h->entries[pr];
        h->entries[pr]= h->entries[child];
        h->entries[child] = swap;
        child = pr;
        pr = (child-1)/2;
    }
}

void siftDownSort(LogEntry arr[], int n, int i) {
    int child, pr;
    pr = i;
    child = 2 * pr +1;

    while (child < n) {
        if (child+1 <n && strcmp(arr[child+1].timestamp,arr[child].timestamp)<0) {
            child++;
        }

        if (strcmp(arr[pr].timestamp, arr[child].timestamp)>0) {
            LogEntry swap = arr[pr];
           arr[pr] =arr[child];
           arr[child] = swap;
            pr = child;
            child = pr * 2 +1;
        } else{
            break;
        }
    }

}

void siftDown(LogHeap* h, int i) {
     
    int child, pr;
    pr = i;
    child = 2 * pr +1;

    while (child <= h->size) {
        if (child+1 <= h->size && strcmp(h->entries[child+1].timestamp, h->entries[child].timestamp)<0) {
            child++;
        }

        if (strcmp(h->entries[pr].timestamp, h->entries[child].timestamp)>0) {
            LogEntry swap = h->entries[pr];
            h->entries[pr] = h->entries[child];
            h->entries[child] = swap;
            pr = child;
            child = pr * 2 +1;
        } else{
            break;
        }
    }
}

bool isEmpty(LogHeap* h) {
   return h->size == -1;
}

void heapSortLogs(LogEntry arr[], int n) {

    for(int i = (n-2)/2; i >= 0; i--) {
        siftDownSort(arr, n, i);
    }

    for(int i = (n-1); i >= 0; i--) {
        LogEntry temp = arr[0];
    arr[0] = arr[i];
    arr[i] = temp;

        siftDownSort(arr, i,0);
    }
}

void printLogs(LogEntry arr[], int n) {
     
    for(int i = 0; i < n; i++) {
        printf("[%s] Source: %s\n", arr[i].timestamp, arr[i].details.ip_addr);
    }

}

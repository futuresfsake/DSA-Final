#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_AIRSPACE 100

// --- Nested Data Structures ---

typedef struct {
    char flight_number[10]; // e.g., "AA123"
    int fuel_percentage;    // Lower fuel might mean higher priority logic elsewhere
    int is_emergency;       // 1 = Yes, 0 = No
} FlightInfo;

typedef struct {
    int priority_score;     // Calculated value (Higher = Land Sooner)
    FlightInfo info;
} PlaneNode;

typedef struct {
    PlaneNode queue[MAX_AIRSPACE];
    int count;
} ATCHeap;

// --- Function Prototypes (10 Functions) ---

// Core Heap Operations
void initATC(ATCHeap* atc);
void requestLanding(ATCHeap* atc, int score, char* flight_num, int fuel, int emergency);
PlaneNode approveLanding(ATCHeap* atc);
void heapifyUp(ATCHeap* atc, int index);   // Helper for Insert/IncreaseKey
void heapifyDown(ATCHeap* atc, int index); // Helper for Extract/Delete

// Utility/Situational Operations
PlaneNode peekNextPlane(ATCHeap* atc);
void declareEmergency(ATCHeap* atc, char* flight_num, int new_high_score);
void cancelRequest(ATCHeap* atc, char* flight_num);
int getQueueSize(ATCHeap* atc);
int isAirspaceFull(ATCHeap* atc);
void printRadar(ATCHeap* atc);

// --- Main Driver Code ---
void heapSortMax(PlaneNode arr[], int n);

//** test for sorting  */
void heapifyMax(PlaneNode arr[], int n, int i) {

    int pr = i;
    int child = 2 * pr +1;

    while (child < n) {
        if (child+1 < n && arr[child+1].priority_score > arr[child].priority_score) {
            child++;
        }

        if (arr[pr].priority_score < arr[child].priority_score) {
            PlaneNode swap = arr[pr];
            arr[pr] = arr[child];
            arr[child] = swap;
            pr= child;
            child = 2 * pr +1;

        } else {
            break;
        }
    }

   
}


void heapSortMax(PlaneNode arr[], int n) {

    for(int i = (n-2)/2; i>= 0; i--) {
        heapifyMax(arr, n, i);
    }
     for(int i = n-1; i>= 0; i--) {
        PlaneNode swap = arr[0];
        arr[0] = arr[i];
        arr[i] = swap;
        
        heapifyMax(arr, i,0);
       
     }

}


int main() {
    ATCHeap heathrow;
    initATC(&heathrow);

    printf("=== ATC Landing Control System ===\n\n");

    // 1. Initial Requests
    printf("--- Planes entering airspace ---\n");
    requestLanding(&heathrow, 50, "BA101", 60, 0);
    requestLanding(&heathrow, 20, "FR222", 80, 0);
    requestLanding(&heathrow, 80, "UA999", 10, 1); // Low fuel, high priority
    requestLanding(&heathrow, 40, "LH404", 55, 0);

    printRadar(&heathrow);

    // // 2. Situational Event: Emergency
    // printf("--- ALERT: BA101 declares medical emergency! ---\n");
    // declareEmergency(&heathrow, "BA101", 100); // Priority jumps to 100

    // printf("Checking if it updated:\n");
    //     printRadar(&heathrow);

    
    // printf("Next plane to land: %s (Score: %d)\n\n", 
    //        peekNextPlane(&heathrow).info.flight_number, 
    //        peekNextPlane(&heathrow).priority_score);

    // // 3. Situational Event: Diversion
    // printf("--- UPDATE: LH404 diverting to alternate airport ---\n");
    // cancelRequest(&heathrow, "LH404");

    // printRadar(&heathrow);

    // // 4. Process Landings
    // printf("--- Approving Landings ---\n");
    // while (getQueueSize(&heathrow) > 0) {
    //     PlaneNode p = approveLanding(&heathrow);
    //     printf("LANDED: Flight %s [Pri: %d | Fuel: %d%%]\n", 
    //            p.info.flight_number, p.priority_score, p.info.fuel_percentage);
    // }


    heapSortMax(heathrow.queue, heathrow.count);
    printRadar(&heathrow);

    return 0;
}



void initATC(ATCHeap* atc) {
    atc->count = 0;

}

void requestLanding(ATCHeap* atc, int score, char* flight_num, int fuel, int emergency) {
    
    int child, pr;
    if (atc->count == MAX_AIRSPACE) return;
    
    child = atc->count;
    pr = (child-1)/2;

    while (child > 0 && atc->queue[pr].priority_score < score) {
        atc->queue[child] = atc->queue[pr];
        child = pr;
        pr = (child-1)/2;
    }

    atc->queue[child].priority_score = score;
    atc->queue[child].info.fuel_percentage = fuel;
    atc->queue[child].info.is_emergency = emergency;
    strcpy(atc->queue[child].info.flight_number, flight_num);

    atc->count++;
}


PlaneNode approveLanding(ATCHeap* atc) {

    PlaneNode dummy = {0};
    if (atc->count == 0) {
        return dummy;
    }

    PlaneNode root, swap;

    root = atc->queue[0];
    atc->queue[0] = atc->queue[atc->count-1];
    atc->count--;

    heapifyDown(atc, 0);

    return root;
}


void heapifyDown(ATCHeap* atc, int index) {
    
    int child, pr;

    pr = index;
    child = 2 * pr +1;

    while (child < atc->count) {
        if (child + 1< atc->count && atc->queue[child+1].priority_score> atc->queue[child].priority_score) {
            child++;
        }

        if (atc->queue[pr].priority_score < atc->queue[child].priority_score) {
            PlaneNode swap = atc->queue[pr];
            atc->queue[pr] = atc->queue[child];
            atc->queue[child] = swap;

            pr = child;
            child = (2 * pr +1);
        } else {
            break;
        }
    }
}
void HeapifyUp(ATCHeap* atc, int index) {

   int child, pr;

    child = index;
    pr = (child-1)/2;

    while (child >0 && atc->queue[pr].priority_score <atc->queue[child].priority_score) {
        PlaneNode swap = atc->queue[pr];
        atc->queue[pr] = atc->queue[child];
        atc->queue[child] =swap;

        child = pr;
        pr = (child-1)/2;
    }
    
}

// Utility/Situational Operations
PlaneNode peekNextPlane(ATCHeap* atc) {
    return atc->queue[0];
}
void declareEmergency(ATCHeap* atc, char* flight_num, int new_high_score) {

    for(int i = 0; i < atc->count; i++) {
        if (strcmp(atc->queue[i].info.flight_number, flight_num)==0) {
            atc->queue[i].priority_score = new_high_score;




            int pr = 0;
            int child = 2 * pr +1;

            while (child < atc->count) {
                if (child+1 < atc->count && atc->queue[child+1].priority_score > atc->queue[child].priority_score) {
                    child++;
                }

                if (atc->queue[pr].priority_score < atc->queue[child].priority_score) {
                    PlaneNode swap = atc->queue[pr];
                    atc->queue[pr] = atc->queue[child];
                    atc->queue[child] = swap;

                    pr = child;
                    child = 2 * pr +1;
                } else {
                    break;
                }
            }
        }
    }
}


void cancelRequest(ATCHeap* atc, char* flight_num) {

    for(int i = 0; i < atc->count; i++) {
        if (strcmp(atc->queue[i].info.flight_number, flight_num) ==0) {

            atc->queue[i] = atc->queue[atc->count-1];
            atc->count--;

            heapifyDown(atc, 0);
        }
    }
}


int getQueueSize(ATCHeap* atc) {
    return atc->count;
}
int isAirspaceFull(ATCHeap* atc) {
    if (atc->count == MAX_AIRSPACE) return 1;
    
    else return -1;
}
void printRadar(ATCHeap* atc) {

    printf("[ RADAR SCREEN ]\n");

    for (int i = 0; i < atc->count; i++) {
        printf("%-7s | Pri: %-3d | Fuel: %d%% | EMG: %d\n",
            atc->queue[i].info.flight_number,
            atc->queue[i].priority_score,
            atc->queue[i].info.fuel_percentage,
            atc->queue[i].info.is_emergency
        );
    }

    printf("-------------------------------\n\n");
}

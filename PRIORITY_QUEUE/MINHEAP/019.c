#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Ship {
    int transponder_id;
    int fuel_percent;       // PRIORITY KEY (Lowest lands first)
    bool is_emergency;      // Secondary flag
} Ship;

typedef struct {
    Ship *runway_queue;     // Dynamic Array
    int count;
    int max_slots;
} AirTrafficControl;

// ======================== PROTOTYPES ========================

/* 1. INIT: Alloc array. */
void open_airspace(AirTrafficControl *atc, int slots) {

    atc->runway_queue = malloc(sizeof(Ship)*(slots));
    if (atc->runway_queue == NULL) return;
    atc->count = -1;
    atc->max_slots = slots;
}

/* 2. INSERT (SWIM UP - MIN HEAP):
 * Add to end. If child < parent, SWAP.
 */
void request_landing(AirTrafficControl *atc, int id, int fuel) {

    if (atc->count == atc->max_slots -1) return;
    
    int child, pr;
    
    atc->count++;
    child = atc->count;
    pr = (child-1)/2;
    
    while (child>0 && atc->runway_queue[pr].fuel_percent > fuel) {
        atc->runway_queue[child] = atc->runway_queue[pr];
        child = pr;
        pr = (child-1)/2;
    }

    atc->runway_queue[child].transponder_id = id;
    atc->runway_queue[child].fuel_percent = fuel;
    
}

/* 3. EXTRACT MIN (SINK DOWN - MIN HEAP):
 * Return root (lowest fuel). Move last to root. 
 * Swap with SMALLEST child.
 */
Ship clear_runway(AirTrafficControl *atc) {
    
    if (atc->count == -1) exit(1);
    
    int child, pr;
    Ship root, swap;
    
    root = atc->runway_queue[0];
    atc->runway_queue[0] = atc->runway_queue[atc->count];
    atc->count--;
    
    
    pr = 0;
    child = 2 * pr +1;
    
    
    while (child <= atc->count) {
        if (child+1 <= atc->count && atc->runway_queue[child+1].fuel_percent < atc->runway_queue[child].fuel_percent) {
            child++;
        }
        if (atc->runway_queue[pr].fuel_percent > atc->runway_queue[child].fuel_percent) {
            swap = atc->runway_queue[pr];
            atc->runway_queue[pr] = atc->runway_queue[child];
            atc->runway_queue[child]= swap;
            
            pr = child;
            child = 2 * pr +1;
        } else {
            break;
        }
    }
    return root;
}

/* 4. LOGIC TEST: FUEL LEAK (Update Key).
 * Find ship. Reduce fuel amount. 
 * Since value Decreased in a Min-Heap, you must SWIM UP.
 */
void report_fuel_leak(AirTrafficControl *atc, int id, int damage) {
    
    for(int i = 0; i <= atc->count; i++) {
        if (atc->runway_queue[i].transponder_id == id) {
           int dif = atc->runway_queue[i].fuel_percent-damage;
           atc->runway_queue[i].fuel_percent = dif;
            
            
            int child = i;
            int pr = (child-1)/2;
            
            while (child > 0 && atc->runway_queue[pr].fuel_percent> atc->runway_queue[child].fuel_percent ) {
                Ship swap = atc->runway_queue[pr];
                atc->runway_queue[pr] = atc->runway_queue[child];
                atc->runway_queue[child] = swap;
                
                
                child = pr;
                pr = (child-1)/2;
            }
            
            return;
            
        }
    }
}

/* 5. LOGIC TEST: AERIAL REFUELING (Update Key).
 * Find ship. Increase fuel amount.
 * Since value Increased in a Min-Heap, you must SINK DOWN.
 */
void refuel_in_flight(AirTrafficControl *atc, int id, int amount) {
    
    for(int i = 0; i <= atc->count; i++) {
        if (atc->runway_queue[i].transponder_id == id) {
            atc->runway_queue[i].fuel_percent += amount;
            
            
            int pr = i;
            int child = 2 * pr +1;
            
            while (child <= atc->count) {
                if (child+1 <= atc->count && atc->runway_queue[child+1].fuel_percent < atc->runway_queue[child].fuel_percent) {
                    child++;
                }
                
                
                if (atc->runway_queue[pr].fuel_percent > atc->runway_queue[child].fuel_percent) {
                    Ship swap = atc->runway_queue[pr];
                    atc->runway_queue[pr] = atc->runway_queue[child];
                    atc->runway_queue[child] = swap;
                    
                    pr = child;
                    child = pr * 2+1;
                } else {
                    break;
                }
                
                
            }
        }
    }
    
}



/* 7. DIAGNOSTIC: VALIDATOR.
 * Recursive or Iterative check.
 * Verify that for every i, fuel[i] <= fuel[2*i+1] and fuel[2*i+2].
 */
bool verify_safety_protocols(AirTrafficControl *atc) {
    
    
    for(int i = 0; i <= atc->count; i++) {
        int left = i * 2 + 1;
        int right = i * 2 +2;
        
        
        if (left<= atc->count && atc->runway_queue[i].fuel_percent>atc->runway_queue[left].fuel_percent) {
            return false;
        }
        
        if (right<= atc->count && atc->runway_queue[i].fuel_percent > atc->runway_queue[right].fuel_percent) {
            return false;
        }
    }
    return true;
}

/* 8. CLEANUP. */
void close_airspace(AirTrafficControl *atc) {
    free(atc->runway_queue);
    atc->count = -1;
    atc->max_slots = -1;
}


/* DIAGNOSTIC: VIEW HEAP CONTENTS */
void display_runway(const AirTrafficControl *atc) {
    printf("\n--- RUNWAY QUEUE (MIN-HEAP VIEW) ---\n");
    if (atc->count == -1) {
        printf("[EMPTY]\n");
        return;
    }

    for (int i = 0; i <= atc->count; i++) {
        printf("Index %d -> Ship %d | Fuel %d\n",
               i,
               atc->runway_queue[i].transponder_id,
               atc->runway_queue[i].fuel_percent);
    }
    printf("------------------------------------\n");
}


// Maintain the min-heap property at a given index
void minheapify(Ship *arr, int n, int i) {
    
    
   
    
    
        int down = i;
        int child = 2 * down + 1;
        
        
        while (child < n) {
            
            
            if (child+1 < n && arr[child+1].fuel_percent < arr[child].fuel_percent) {
                child++;
            }
            
            if (arr[down].fuel_percent > arr[child].fuel_percent) {
                Ship swap = arr[down];
                arr[down] = arr[child];
                arr[child] = swap;
                
                
                down = child;
                child =  2 * down+1;
            } else {
                break;
            }
          
            
        
    }
    
    
}

// Perform heap sort on an array of Ships
void heapsort(Ship *arr, int n) {
    

    // 1. Build min-heap
    for (int i = (n - 2) / 2; i >= 0; i--) {
        minheapify(arr, n, i);
    }

    // 2. Sort in-place
    for (int i = n - 1; i > 0; i--) {
        // Swap root (min) with last element
        Ship tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;

        // Heapify reduced heap
        minheapify(arr, i, 0); // heap size reduced to i
    }
}


// ======================== MAIN TESTER ========================
int main() {
    AirTrafficControl aegis;
    open_airspace(&aegis, 15);

    printf("=== PHASE 1: INCOMING TRAFFIC ===\n");
    request_landing(&aegis, 501, 40);
    request_landing(&aegis, 502, 10); // Swap to root
    request_landing(&aegis, 503, 90);
    request_landing(&aegis, 504, 25); 
    
    
    
    
    
    printf("The Sort\n");
    


heapsort(aegis.runway_queue, aegis.count + 1);
display_runway(&aegis); // Now the array is sorted by fuel

    
    

    // // Current Min: 10
    // printf("Next to land: Ship %d (Fuel %d)\n", aegis.runway_queue[0].transponder_id, aegis.runway_queue[0].fuel_percent);

    // printf("\n=== PHASE 2: EMERGENCIES ===\n");
    // // Ship 503 (90 fuel) gets hit. Fuel drops by 85 -> becomes 5.
    // // It is currently deep in the heap. It needs to Swim to Root.
    // report_fuel_leak(&aegis, 503, 85);
    
    // printf("New Emergency: Ship %d (Fuel %d)\n", aegis.runway_queue[0].transponder_id, aegis.runway_queue[0].fuel_percent);
    // display_runway(&aegis);


        
    //     printf("\n=== PHASE 4: REFUELING TEST ===\n");
        
    //     // Example: Refuel ship 504 by +50 (will become 75 and must sink down!)
    //     refuel_in_flight(&aegis, 504, 50);
        
    //     display_runway(&aegis);
        
    //     if(verify_safety_protocols(&aegis)) 
    //         printf("Refuel Test: Heap OK.\n");
    //     else 
    //         printf("Refuel Test: Heap CORRUPTED.\n");
            

    // printf("\n=== PHASE 3: LANDING ===\n");
    // Ship landed = clear_runway(&aegis); // Should be 503 (5 fuel)
    // printf("Landed: %d\n", landed.transponder_id);
    //   printf("\n\n");
    // display_runway(&aegis);
  

    
    // landed = clear_runway(&aegis); // Should be 502 (10 fuel)
    // printf("Landed: %d\n", landed.transponder_id);
    //   printf("\n\n");
    // display_runway(&aegis);

    // printf("\n=== PHASE 4: SAFETY CHECK ===\n");
    // if(verify_safety_protocols(&aegis)) printf("Heap Integrity OK.\n");
    // else printf("Heap Corrupted!\n");

    close_airspace(&aegis);
    return 0;
}

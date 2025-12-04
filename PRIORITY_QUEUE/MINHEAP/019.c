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
void open_airspace(AirTrafficControl *atc, int slots);

/* 2. INSERT (SWIM UP - MIN HEAP):
 * Add to end. If child < parent, SWAP.
 */
void request_landing(AirTrafficControl *atc, int id, int fuel);

/* 3. EXTRACT MIN (SINK DOWN - MIN HEAP):
 * Return root (lowest fuel). Move last to root. 
 * Swap with SMALLEST child.
 */
Ship clear_runway(AirTrafficControl *atc);

/* 4. LOGIC TEST: FUEL LEAK (Update Key).
 * Find ship. Reduce fuel amount. 
 * Since value Decreased in a Min-Heap, you must SWIM UP.
 */
void report_fuel_leak(AirTrafficControl *atc, int id, int damage);

/* 5. LOGIC TEST: AERIAL REFUELING (Update Key).
 * Find ship. Increase fuel amount.
 * Since value Increased in a Min-Heap, you must SINK DOWN.
 */
void refuel_in_flight(AirTrafficControl *atc, int id, int amount);

/* 6. LOGIC TEST: K-TH DESPERATE SHIP.
 * Return the fuel level of the 3rd most desperate ship (index 0 is 1st).
 * Do NOT extract them. Just look at the array structure.
 * (Note: The 3rd smallest isn't necessarily at index 2. It could be index 2 or 3).
 * You might need to copy the heap and pop twice to find it safely.
 */
int check_third_priority(AirTrafficControl *atc);

/* 7. DIAGNOSTIC: VALIDATOR.
 * Recursive or Iterative check.
 * Verify that for every i, fuel[i] <= fuel[2*i+1] and fuel[2*i+2].
 */
bool verify_safety_protocols(AirTrafficControl *atc);

/* 8. CLEANUP. */
void close_airspace(AirTrafficControl *atc);


// ======================== MAIN TESTER ========================
int main() {
    AirTrafficControl aegis;
    open_airspace(&aegis, 15);

    printf("=== PHASE 1: INCOMING TRAFFIC ===\n");
    request_landing(&aegis, 501, 40);
    request_landing(&aegis, 502, 10); // Swap to root
    request_landing(&aegis, 503, 90);
    request_landing(&aegis, 504, 25); 

    // Current Min: 10
    printf("Next to land: Ship %d (Fuel %d)\n", aegis.runway_queue[0].transponder_id, aegis.runway_queue[0].fuel_percent);

    printf("\n=== PHASE 2: EMERGENCIES ===\n");
    // Ship 503 (90 fuel) gets hit. Fuel drops by 85 -> becomes 5.
    // It is currently deep in the heap. It needs to Swim to Root.
    report_fuel_leak(&aegis, 503, 85);
    
    printf("New Emergency: Ship %d (Fuel %d)\n", aegis.runway_queue[0].transponder_id, aegis.runway_queue[0].fuel_percent);

    printf("\n=== PHASE 3: LANDING ===\n");
    Ship landed = clear_runway(&aegis); // Should be 503 (5 fuel)
    printf("Landed: %d\n", landed.transponder_id);
    
    landed = clear_runway(&aegis); // Should be 502 (10 fuel)
    printf("Landed: %d\n", landed.transponder_id);

    printf("\n=== PHASE 4: SAFETY CHECK ===\n");
    if(verify_safety_protocols(&aegis)) printf("Heap Integrity OK.\n");
    else printf("Heap Corrupted!\n");

    close_airspace(&aegis);
    return 0;
}

// ====================== IMPLEMENTATIONS ======================
// TODO: Implement all 8 functions.
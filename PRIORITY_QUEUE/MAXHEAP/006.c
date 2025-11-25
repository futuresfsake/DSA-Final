#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ===== DATA STRUCTURES (OBFUSCATED) =====
   
   Hint: 
   - 'Echo' is the item being stored.
   - 'shatter_index' is the Priority (Key).
   - 'FluxContainer' is the Priority Queue itself.
   - 'stream' is the Heap Array.
*/

typedef struct {
    int shatter_index;   // The Priority Value (High = Urgent)
    int fragment_id;     // The Data
} Echo;

typedef struct {
    Echo* stream;             // The dynamic array acting as the heap
    int current_instability;  // Current number of elements (size)
    int max_threshold;        // Maximum capacity
} FluxContainer;


/* ==========================================
   FUNCTION PROTOTYPES (YOU IMPLEMENT THESE)
   ========================================== */

// 1. Initialize the container
// Allocates memory for 'stream' based on 'capacity'.
FluxContainer* ignite_reactor(int capacity) {
    FluxContainer* container = malloc(sizeof(FluxContainer));
    if (container == NULL) return NULL;

    container->stream = malloc(sizeof(Echo) * capacity);
    if (container->stream == NULL) {
        return NULL;
    }

    container->current_instability = -1;
    container->max_threshold = capacity;
    return container;
}

// 2. Enqueue (Push)
// Adds a new Echo. Must maintain the Max-Heap property by "bubbling up"
// iteratively.
// Returns true if successful, false if full.
bool inject_echo(FluxContainer* fc, int priority, int id) {

    int child, pr;

    if (fc->current_instability == fc->max_threshold-1) return false;

    fc->current_instability++;
    child = fc->current_instability;
    pr = (child-1) / 2;

    while (child >0 && fc->stream[pr].shatter_index < priority) {
        fc->stream[child] = fc->stream[pr];
        child = pr;
        pr = (child-1) / 2;
    }

    fc->stream[child].fragment_id = id;
    fc->stream[child].shatter_index = priority;
    return true;
}

// 3. Dequeue (Pop Max)
// Removes the Echo with the HIGHEST shatter_index.
// Must replace root with the last element and "sink down" iteratively.
// Returns an Echo with shatter_index -1 if empty.
Echo extract_anomaly(FluxContainer* fc) {

    int child, pr;
    Echo swap;
    Echo root;
    if (fc->current_instability == -1) exit(1);

    root = fc->stream[0];
    fc->stream[0] = fc->stream[fc->current_instability];
    fc->current_instability--;

    pr = 0;
    child = 1;

    while (child <= fc->current_instability) {
        if (child +1 <= fc->current_instability && fc->stream[child+1].shatter_index > fc->stream[child].shatter_index) {
            child++;
        }

          if (fc->stream[pr].shatter_index < fc->stream[child].shatter_index) {
            swap = fc->stream[pr];
            fc->stream[pr] = fc->stream[child];
            fc->stream[child] = swap;

            pr = child;
            child = pr * 2 + 1;
        } else {
            break;
        }
    }

    return root;


}

// 4. Peek
// Returns the highest priority Echo without removing it.
Echo scan_core(FluxContainer* fc) {
    return fc->stream[0];
}

// 5. Cleanup
// Frees all memory.
void collapse_field(FluxContainer* fc) {
    free(fc->stream);
    fc->current_instability = 0;
    fc->max_threshold = 0;
    free(fc);
    return;
}
// 6. Display the entire heap (for debugging/tracing)
void display_flux(FluxContainer* fc) {
    if (fc->current_instability == -1) {
        printf("[FluxContainer Empty]\n");
        return;
    }

    printf("\n[CURRENT HEAP STATE]\n");
    for (int i = 0; i <= fc->current_instability; i++) {
        printf("Index %d: Priority %d | ID %d\n",
               i, fc->stream[i].shatter_index, fc->stream[i].fragment_id);
    }
}



/* ==========================================
               MAIN DRIVER
   ========================================== */

int main() {
    // Initialize with capacity for 10 pulses
    FluxContainer* core = ignite_reactor(10);

    printf("=== SYSTEM: REACTOR IGNITED ===\n");

    // SCENARIO: Pulses arrive in random order
    // inject_echo(container, priority, data_id)
    
    printf("Injecting Pulse A (Priority 20)...\n");
    inject_echo(core, 20, 101);

    printf("Injecting Pulse B (Priority 85)...\n");
    inject_echo(core, 85, 102); // Should float to top

    printf("Injecting Pulse C (Priority 40)...\n");
    inject_echo(core, 40, 103);

    printf("Injecting Pulse D (Priority 99)...\n");
    inject_echo(core, 99, 104); // Should become new root

    printf("Injecting Pulse E (Priority 10)...\n");
    inject_echo(core, 10, 105);

       printf("\n=== DISPLAYING HEAP ===\n");
display_flux(core);

    // TRACE CHECK 1: Who is at index 0? (Should be 99)
    Echo top = scan_core(core);
    printf("\n[CORE SCAN] Highest Threat: Priority %d | ID %d\n", 
           top.shatter_index, top.fragment_id);

    printf("\n=== PROCESSING ANOMALIES (Extraction Phase) ===\n");
    
    // We expect them to come out in order: 99, 85, 40, 20, 10
    // Regardless of insertion order.
    
//     int safety_limit = 5;
   

// // Correct Loop Condition:
// while(core->current_instability >=0 && safety_limit-- > 0) {
//     Echo e = extract_anomaly(core);
//     printf("Stabilized: Priority %d [ID: %d]\n", e.shatter_index, e.fragment_id);
// }

    Echo e = extract_anomaly(core);
    printf("Max heap: Priority [%d], ID [%d] \n", e.shatter_index, e.fragment_id);

    printf("\n=== DISPLAYING HEAP ===\n");
display_flux(core);



    collapse_field(core);
    printf("\n=== SYSTEM: REACTOR COOLED ===\n");

    return 0;
}


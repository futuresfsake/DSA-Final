#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The Node
typedef struct Reagent {
    int atomic_weight;       // Key
    float potency;           // Value
    struct Reagent* bond;    // Next Pointer
} Reagent;

// The Table (Dynamic Array Wrapper)
typedef struct {
    Reagent** cauldrons;     // Array of pointers (Dynamic!)
    int cauldron_count;      // Current size of array
    int total_reagents;      // Total items (to track load factor)
} Solution;

// ------------------------------------------------------------------

/* * MISSION: Allocation.
 * Allocate the 'Solution' struct.
 * Allocate the 'cauldrons' array to the 'initial_size'.
 * Initialize all pointers to NULL.
 */
Solution* brew_init(int initial_size);

/* * MISSION: Hash Function.
 * Returns atomic_weight % cauldron_count.
 */
int calc_reaction_index(Solution* sol, int weight);

/* * MISSION: Standard Insert.
 * 1. Check if reagent exists. If yes, update potency.
 * 2. If no, create new Reagent.
 * 3. HEAD INSERT into the correct cauldron.
 * 4. Increment total_reagents.
 */
void add_ingredient(Solution* sol, int weight, float potency);

/* * MISSION: The Dynamic Logic Test.
 * 1. Allocate a NEW array of size (cauldron_count * 2).
 * 2. Iterate through the OLD array and every Reagent chain.
 * 3. Re-hash every Reagent using the NEW size.
 * 4. Move the Reagent nodes to the NEW array (Do not malloc new nodes, just move pointers).
 * 5. Free the old array and update the struct.
 */
void sublimate_solution(Solution* sol);

/* * MISSION: Conditional Delete.
 * Remove all Reagents where potency < threshold.
 * This requires traversing lists and deleting nodes from the middle 
 * while maintaining the chain integrity.
 */
void filter_impurities(Solution* sol, float threshold);

/* * MISSION: Cleanup.
 * Free every node in every chain, then free the array, then the struct.
 */
void dispose_waste(Solution* sol) {
    

    for(int i = 0; i < sol->total_reagents;i++) {
        Reagent* head = sol->cauldrons[i];

        while (head) {
            Reagent* temp = head;
            head = temp->bond;
            free(temp);
        }
        free(sol->cauldrons);
    free(sol);
    }
}




int main() {
    // ----------------------
    // 1. Initialize solution
    // ----------------------
    Solution* sol = brew_init(20); // start with 3 cauldrons
    printf("Initial cauldron count: %d\n", sol->cauldron_count);

    // ----------------------
    // 2. Add ingredients
    // ----------------------
    add_ingredient(sol, 10, 5.5);
    add_ingredient(sol, 4, 7.2);
    add_ingredient(sol, 7, 3.3);
    add_ingredient(sol, 10, 6.6); // update existing weight 10
    add_ingredient(sol, 15, 2.2);
    printf("\nAfter adding ingredients:\n");
    for (int i = 0; i < sol->cauldron_count; i++) {
        printf("Cauldron %d: ", i);
        Reagent* curr = sol->cauldrons[i];
        while (curr) {
            printf("[Weight: %d, Potency: %.1f] -> ", curr->atomic_weight, curr->potency);
            curr = curr->bond;
        }
        printf("NULL\n");
    }

   

    // ----------------------
    // 4. Filter impurities (potency < 5)
    // ----------------------
    filter_impurities(sol, 5.0);
    printf("\nAfter filtering impurities (potency < 5.0):\n");
    for (int i = 0; i < sol->cauldron_count; i++) {
        printf("Cauldron %d: ", i);
        Reagent* curr = sol->cauldrons[i];
        while (curr) {
            printf("[Weight: %d, Potency: %.1f] -> ", curr->atomic_weight, curr->potency);
            curr = curr->bond;
        }
        printf("NULL\n");
    }

    // ----------------------
    // 5. Dispose waste (cleanup)
    // ----------------------
    dispose_waste(sol);
    printf("\nAll reagents disposed.\n");

    return 0;
}

// ==================== PROTOTYPES ====================

/* Initialize a Solution struct with a given initial size */
Solution* brew_init(int initial_size) {

    Solution* s = malloc(sizeof(Solution));
    if (s == NULL) return NULL;
    
    s->cauldrons = malloc(sizeof(Reagent) * initial_size);
    for (int i = 0; i < initial_size; i++)
    s->cauldrons[i] = NULL;
    if (s->cauldrons == NULL) {
        return NULL;
    } 

    s->cauldron_count = initial_size;
    s->total_reagents = 0;
    return s;
}

/* Compute the hash index for a given atomic_weight */
int calc_reaction_index(Solution* sol, int weight) {

    return weight % sol->cauldron_count;
}

/* Insert a Reagent into the Solution (head insert). Update potency if weight exists */
void add_ingredient(Solution* sol, int weight, float potency) {

    int index = calc_reaction_index(sol, weight);

    Reagent* trav = sol->cauldrons[index];

    while (trav) {
        if (trav->atomic_weight == weight) {
            trav->potency = potency;
            return;
        }
        trav= trav->bond;
    }


    Reagent* new = malloc(sizeof(Reagent));
    new->atomic_weight = weight;
    new->potency = potency;
    new->bond = sol->cauldrons[index];
    sol->cauldrons[index] = new;

    sol->total_reagents++;

}


/* Remove all Reagents with potency below the given threshold */
void filter_impurities(Solution* sol, float threshold) {


   

    for(int i = 0; i < sol->cauldron_count; i++) {
    Reagent** trav = &sol->cauldrons[i];
        
    for(; *trav != NULL; ) {
        if ((*trav)->potency < threshold) {
        Reagent* temp = *trav;
        *trav = temp->bond;
        free(temp);
        sol->total_reagents--;
    } else {
    (trav) = &(*trav)->bond;
    }
}
}
}

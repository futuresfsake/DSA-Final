#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_DESC 64

/*
    =====================================================================
       PROJECT: CHRONOS PROTOCOL (BST ARCHITECTURE)
    ---------------------------------------------------------------------
    You are monitoring the Time Stream. Events are Nodes.
    
    STRUCTURAL RULES:
    1. 'past_link' -> Events that happened BEFORE the current node (Left).
    2. 'future_link' -> Events that happened AFTER the current node (Right).
    3. Years are unique.
    =====================================================================
*/


typedef struct {
    int year;                   // The Key
    char description[MAX_DESC];
    int stability_rating;  
}Info;


typedef struct EventParadox {
    Info info;     // Data (0-100). Lower = More Dangerous.
    
    struct EventParadox *past_link;     // Left Child
    struct EventParadox *future_link;   // Right Child
} EventParadox;

// The Timeline Wrapper
typedef struct {
    EventParadox *origin_point; // Root pointer
} TimeStream;


// ======================== PROTOTYPES ========================

/* * Initialize origin_point to NULL. */
void open_channel(TimeStream *ts);

/* * INSERT EVENT:
 * Create new Paradox.
 * Navigate: If year < current->year, go past_link. Else go future_link.
 */
EventParadox* trigger_event(EventParadox *root, int year, char *desc, int stability);

/* * DELETE EVENT:
 * Remove an event by Year.
 * Handle Leaf, One-Child, and Two-Child (Successor) cases.
 */
EventParadox* correct_timeline(EventParadox *root, int year);

/* * SEARCH:
 * Binary Search for a specific year. Return pointer or NULL.
 */
EventParadox* jump_to_moment(EventParadox *root, int year);

/* * TRAVERSAL (In-Order):
 * View timeline from earliest year to latest year.
 */
void view_continuum(EventParadox *root) {
    if (root == NULL) return;

    // Visit past events first (left)
    view_continuum(root->past_link);

    // Print the current event
    printf("Year %d | %-20s | Stability %d\n",
           root->info.year,
           root->info.description,
           root->info.stability_rating);

    // Visit future events next (right)
    view_continuum(root->future_link);
}

/* * FILTER FUNCTION (Requested):
 * Traverse the entire tree.
 * Print events where 'stability_rating' is LESS THAN 'critical_threshold'.
 * (These are the events about to collapse reality).
 */
void report_glitches(EventParadox *root, int critical_threshold);

/* * LOGIC TEST: THE END OF TIME
 * Iteratively find the event with the LARGEST year.
 * (Keep going to the future_link until you hit the wall).
 */
EventParadox* find_chronological_end(EventParadox *root);

/* * LOGIC TEST: COUNT ONE-WAY BRANCHES
 * Count how many nodes have EXACTLY ONE child (either just past or just future).
 * These are "Unstable Forks" in time.
 */
int count_unstable_forks(EventParadox *root);

/* * LOGIC TEST: GLOBAL TIME SHIFT
 * Visit EVERY node. Add 'years_to_add' to the 'year' variable.
 * (Note: Since we add the same amount to everything, BST order remains valid).
 */
void offset_entire_timeline(EventParadox *root, int years_to_add);

/* * LOGIC TEST: ACCUMULATE DAMAGE
 * Recursively sum up the 'stability_rating' of all nodes in the tree.
 * Returns the total stability score of the continuum.
 */
int calculate_total_stability(EventParadox *root);

/* * CLEANUP:
 * Free memory (Post-Order).
 */
void close_loop(EventParadox *root);


// ======================== MAIN TESTER ========================
int main() {
    TimeStream timeline;
    open_channel(&timeline);

    printf("=== PHASE 1: TRIGGERING EVENTS ===\n");
    // Tree Visualization:
    //          2050
    //        /      \
    //     1990      3000
    //    /    \     /
    //  1945   2020 2500
    
    timeline.origin_point = trigger_event(timeline.origin_point, 2050, "AI Awakening", 80);
    timeline.origin_point = trigger_event(timeline.origin_point, 1990, "Web Launch", 95);
    timeline.origin_point = trigger_event(timeline.origin_point, 3000, "Sun Expansion", 10); // Critical!
    timeline.origin_point = trigger_event(timeline.origin_point, 1945, "Atomic Age", 40);
    timeline.origin_point = trigger_event(timeline.origin_point, 2020, "Global Lockdown", 30); // Critical!
    timeline.origin_point = trigger_event(timeline.origin_point, 2500, "Mars Colony", 70);

    printf("Current Timeline (Sorted):\n");
    view_continuum(timeline.origin_point);

    // printf("\n=== PHASE 2: REPORT GLITCHES (Stability < 50) ===\n");
    // // Should print: Sun Expansion (10), Atomic Age (40), Global Lockdown (30)
    // report_glitches(timeline.origin_point, 50);

    
   
  
    // int total_stab = calculate_total_stability(timeline.origin_point);
    // printf("Total Continuum Stability: %d\n", total_stab);

    printf("\n=== PHASE 4: TIME SHIFT (+100 Years) ===\n");
    offset_entire_timeline(timeline.origin_point, 100);
    view_continuum(timeline.origin_point);
    // 2050 becomes 2150, etc.

    printf("\n=== PHASE 5: CORRECTING TIMELINE (Delete 1990 - 2 Children) ===\n");
    // 1990 (now 2090) has two children. Logic must swap with successor/predecessor.
    // Note: The years are now shifted, so you must delete the *new* year value.
    int target_year = 1990 + 100 ; 
    timeline.origin_point = correct_timeline(timeline.origin_point, target_year);
    
    printf("Timeline after deletion:\n");
    view_continuum(timeline.origin_point);

    printf("\n=== PHASE 6: CLOSE LOOP ===\n");
    close_loop(timeline.origin_point);
    printf("Paradox resolved.\n");

    return 0;
}


// ====================== FUNCTION IMPLEMENTATIONS ======================

void open_channel(TimeStream *ts) {
    // TODO: Set origin_point to NULL

    ts->origin_point = NULL;
}

EventParadox* trigger_event(EventParadox *root, int year, char *desc, int stability) {
    // TODO: Recursive Insert.
    // If year < root->year -> past_link. Else -> future_link.

    EventParadox** trav = &root;

    for(; *trav != NULL && (*trav)->info.year != year; ){
        trav = (*trav)->info.year < year ? &(*trav)->future_link : &(*trav)->past_link;
    }

    if (*trav == NULL) {
        
        EventParadox* new = malloc(sizeof(EventParadox));
        if (new == NULL) return NULL;

        new->info.year = year;
        new->info.stability_rating = stability;
        strcpy(new->info.description, desc);

        new->past_link = NULL;
        new->future_link = NULL;


        *trav = new;
        return root;
    }


    return root; 
}

EventParadox* correct_timeline(EventParadox *root, int year) {
    // TODO: Recursive Delete.
    // 1. Leaf: Free.
    // 2. One Link: Return the active link.
    // 3. Two Links: Replace with Successor data, delete Successor.


    EventParadox** trav = &root;
    for(; *trav != NULL && (*trav)->info.year != year;) {
        trav = (*trav)->info.year < year ? &(*trav)->future_link : &(*trav)->past_link;
    }

    if (*trav == NULL) return root;


    EventParadox* temp = *trav;


    if ((*trav)->past_link == NULL && (*trav)->future_link == NULL) {
        free(temp);
        *trav = NULL;
    } else if ((*trav)->past_link == NULL) {
        *trav = (*trav)->future_link;
        free(temp);
    } else if ((*trav)->future_link == NULL) {
        *trav = (*trav)->past_link;
        free(temp);
    } else {
        EventParadox** succ = &(*trav)->future_link;
        while ((*succ)->past_link) {
            succ = &(*succ)->past_link;
        }

        (*trav)->info = (*succ)->info;

        EventParadox* target = *succ;
        *succ = target->future_link;
        free(target);
        return root;
    }
    return root;
}

EventParadox* jump_to_moment(EventParadox *root, int year) {
    // TODO: Binary Search.
    EventParadox* trav = root;
    for(; trav != NULL;) {
        if (trav->info.year == year) {
            return trav;
        }
    }
    return NULL;
}


void report_glitches(EventParadox *root, int critical_threshold) {
    // TODO: Traversal (any order). 
    // If stability_rating < critical_threshold, print details.

    if (root == NULL) return;
    report_glitches(root->past_link, critical_threshold);
    if (root->info.stability_rating < critical_threshold) {
          printf("Year %d | %-20s | Stability %d\n",
           root->info.year,
           root->info.description,
           root->info.stability_rating);
    }
    report_glitches(root->future_link, critical_threshold);
}




void offset_entire_timeline(EventParadox *root, int years_to_add) {
    // TODO: Traversal (Pre-order suggested).
    // root->year += years_to_add.
    // recurse past and future.

    if (root == NULL) return;
    offset_entire_timeline(root->past_link, years_to_add);
    root->info.year+= years_to_add;
    offset_entire_timeline(root->future_link, years_to_add);



}

int calculate_total_stability(EventParadox *root) {
    // TODO: Return root->stability + sum(past) + sum(future).

    if (root == NULL) return 0;


   

    int c =  calculate_total_stability(root->past_link);
    int c2 =  calculate_total_stability(root->future_link);
    
    
    return c+c2+root->info.stability_rating;
}

void close_loop(EventParadox *root) {
    // TODO: Post-Order Free.

    if (root == NULL) return;

    close_loop(root->past_link);
    close_loop(root->future_link);
    free(root);
}
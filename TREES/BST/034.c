#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SPECIES 64

/*
    =====================================================================
       PROJECT: ABYSSAL TRENCH (BST ARCHITECTURE)
    ---------------------------------------------------------------------
    You are mapping a bioluminescent ecosystem.
    
    STRUCTURAL RULES:
    1. 'dim_stream' leads to organisms with LOWER Frequency (Left).
    2. 'bright_stream' leads to organisms with HIGHER Frequency (Right).
    3. Frequencies are unique identifiers.
    =====================================================================
*/

typedef struct {
    int freq_hz;                      // Key (unique frequency)
    char species_name[MAX_SPECIES];    // Species Name
    int lumens;                        // Brightness intensity
} Info;

typedef struct Organism {
    Info info;
    struct Organism *dim_stream;       // Left child
    struct Organism *bright_stream;    // Right child
} Organism;

typedef struct {
    Organism *reef_core;               // Root pointer
} Ecosystem;

// ======================== PROTOTYPES ========================

// --- BASIC OPERATIONS ---
void init_ecosystem(Ecosystem *e);
Organism* discover_specimen(Organism *root, int hz, char *name, int lumens);
Organism* extinction_event(Organism *root, int hz);
Organism* scan_depths(Organism *root, int hz);
void collapse_ecosystem(Organism *root);

// --- ADVANCED OPERATIONS ---
void census_by_lumens(Organism *root, int min_brightness);
int calculate_total_energy(Organism *root);
Organism* find_apex_predator(Organism *root);



// FULL SURVEY (Display all organisms sorted by frequency)
void full_survey(Organism *root) {
    if (root == NULL) return;

    // Traverse left (dim_stream)
    full_survey(root->dim_stream);

    // Print current node
    printf("[%d Hz] %s (Lumens: %d)\n", root->info.freq_hz, root->info.species_name, root->info.lumens);

    // Traverse right (bright_stream)
    full_survey(root->bright_stream);
}


// ======================== MAIN TESTER ========================
int main() {
    Ecosystem trench;
    init_ecosystem(&trench);

    printf("=== PHASE 1: DISCOVERY (Populating the Trench) ===\n");
    trench.reef_core = discover_specimen(trench.reef_core, 500, "GhostShark", 1200);
    trench.reef_core = discover_specimen(trench.reef_core, 300, "ViperFish", 800);
    trench.reef_core = discover_specimen(trench.reef_core, 700, "AnglerFish", 1500);
    trench.reef_core = discover_specimen(trench.reef_core, 100, "JellyBlob", 200);
    trench.reef_core = discover_specimen(trench.reef_core, 400, "FlashEel", 950);
    trench.reef_core = discover_specimen(trench.reef_core, 600, "NeonSquid", 1100);
    trench.reef_core = discover_specimen(trench.reef_core, 900, "StarWhale", 5000);

    printf("Full Survey (Sorted by Hz):\n");
    full_survey(trench.reef_core);

    printf("\n=== PHASE 2: FILTER CENSUS (Lumens > 1000) ===\n");
    census_by_lumens(trench.reef_core, 1000);


    printf("\n=== PHASE 3: ENERGY CALCULATION ===\n");
    int total_energy = calculate_total_energy(trench.reef_core);
    printf("Total Ecosystem Energy: %d lumens\n", total_energy);

    printf("\n=== PHASE 4: FIND APEX PREDATOR ===\n");
    Organism* apex = find_apex_predator(trench.reef_core);
    if (apex)
        printf("Apex Specimen: %s (%d Hz)\n", apex->info.species_name, apex->info.freq_hz);

    printf("\n=== PHASE 5: EXTINCTION EVENT (Removing 300 - Two Children) ===\n");
    trench.reef_core = extinction_event(trench.reef_core, 300);
    printf("Survey After Extinction:\n");
    full_survey(trench.reef_core);

    printf("\n=== PHASE 6: COLLAPSE ===\n");
    collapse_ecosystem(trench.reef_core);
    printf("Trench is silent.\n");

    return 0;
}

// ====================== FUNCTION IMPLEMENTATIONS ======================

// Initialize the ecosystem
void init_ecosystem(Ecosystem *e) {
    e->reef_core = NULL;
}

// DISCOVERY (BST Insert)
Organism* discover_specimen(Organism *root, int hz, char *name, int lumens) {
    // TODO: Implement recursive insert


    Organism** trav = &root;
    for(;*trav != NULL && (*trav)->info.freq_hz != hz;) {
        trav = (*trav)->info.freq_hz < hz ? &(*trav)->bright_stream : &(*trav)->dim_stream;
    }

    if (*trav == NULL) {
        Organism* new = malloc(sizeof(Organism));
        new->info.freq_hz = hz;
        strcpy(new->info.species_name, name);
        new->info.lumens = lumens;

        new->bright_stream = NULL;
        new->dim_stream = NULL;

        *trav = new;
    }
    return root;
}

// EXTINCTION EVENT (BST Delete)
Organism* extinction_event(Organism *root, int hz) {
    

    if (root == NULL) return NULL;

    Organism** trav = &root;
    for(;*trav != NULL && (*trav)->info.freq_hz != hz;) {
        trav = (*trav)->info.freq_hz < hz ? &(*trav)->bright_stream : &(*trav)->dim_stream;
    }


    if (*trav == NULL) return root;

    Organism* temp = *trav;

    if ((*trav)->dim_stream == NULL && (*trav)->bright_stream == NULL) {
        free(temp);
        *trav = NULL;
    } else if ((*trav)->dim_stream == NULL) {
        *trav = (*trav)->bright_stream;
        free(temp);
    } else if ((*trav)->bright_stream == NULL) {
        *trav = (*trav)->dim_stream;
        free(temp);
    } else {
        Organism** succ = &(*trav)->bright_stream;
        while ((*succ)->dim_stream != NULL) {
            succ = &(*succ)->dim_stream;
        }

        (*trav)->info = (*succ)->info;

        Organism* target = *succ;
        *succ = (*succ)->bright_stream;
        free(target);
    }
    return root;
}

// SCAN (BST Search)
Organism* scan_depths(Organism *root, int hz) {
    // TODO: Implement BST search
    if (root == NULL)
    return NULL;



    Organism* trav = root;
    for(;trav != NULL;) {
        if (trav->info.freq_hz == hz) {
            return trav;
        }

        trav = trav->info.freq_hz < hz ? trav->bright_stream : trav->dim_stream;
    }

    return NULL;
}



// FILTER BY LUMENS
void census_by_lumens(Organism *root, int min_brightness) {
    // TODO: Visit every node and print if lumens > min_brightness

    if (root == NULL) return;

    census_by_lumens(root->dim_stream, min_brightness);
    if (root->info.lumens > min_brightness) {
     printf("[%d Hz] %s (Lumens: %d)\n", root->info.freq_hz, root->info.species_name, root->info.lumens);
    }
    census_by_lumens(root->bright_stream, min_brightness);


}

// CALCULATE TOTAL ENERGY (Sum of Lumens)
int calculate_total_energy(Organism *root) {
    // TODO: Base case: return 0 if root NULL
    // Return root->lumens + energy(dim_stream) + energy(bright_stream)

    if (root == NULL) return 0;
    
    

    int c = calculate_total_energy(root->dim_stream);
    int c2 = calculate_total_energy(root->bright_stream);
    return root->info.lumens+c +c2;
}

// FIND APEX PREDATOR (Highest Frequency)
Organism* find_apex_predator(Organism *root) {
    // TODO: Traverse bright_stream until end
    if (root == NULL)
    return NULL;

    while (root->bright_stream) {
        root = root->bright_stream;
    }

    return root;
}

// COLLAPSE ECOSYSTEM (Free memory)
void collapse_ecosystem(Organism *root) {
    // TODO: Post-order free

    if (root == NULL) return;
    collapse_ecosystem(root->dim_stream);
    collapse_ecosystem(root->bright_stream);
    free(root);
}

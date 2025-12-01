#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SPELL_NAME 50

/*
    =====================================================================
       THE ARCANE GRIMOIRE (BST IMPLEMENTATION)
    ---------------------------------------------------------------------
    You are the keeper of the "Mind Palace." You store spell memories 
    in a crystalline structure.
    
    STRUCTURAL RULES:
    1. 'void_link' leads to weaker Arcane IDs (Left).
    2. 'solar_link' leads to stronger Arcane IDs (Right).
    3. No duplicate IDs.
    =====================================================================
*/
typedef struct {
    int arcane_id;                    // The Key
    char spell_name[MAX_SPELL_NAME];  // Spell Name
    int mana_cost;                     // Mana required
} Info;

typedef struct MemoryShard {
    Info info;
    struct MemoryShard *void_link;    // Left child
    struct MemoryShard *solar_link;   // Right child
} MemoryShard;

typedef struct {
    MemoryShard *core_memory;         // Root pointer
} Grimoire;

// ======================== PROTOTYPES ========================

// --- BASIC OPERATIONS ---
void init_grimoire(Grimoire *g);
MemoryShard* inscription_ritual(MemoryShard *root, int id, char *name, int mana);
MemoryShard* banish_shard(MemoryShard *root, int id);
MemoryShard* find_weakest_link(MemoryShard *root);
MemoryShard* recall_memory(MemoryShard *root, int id);
void channel_stream(MemoryShard *root);
void mental_shutdown(MemoryShard *root);

// --- ADVANCED OPERATIONS ---
int measure_mental_depth(MemoryShard *root);
int count_unstable_fragments(MemoryShard *root);
void detect_mana_flux(MemoryShard *root, int min_mana, int max_mana);
bool trace_lineage(MemoryShard *root, int target_id);
void mirror_dimension(MemoryShard *root);

// ======================== MAIN TESTER ========================
int main() {
    Grimoire my_mind;
    init_grimoire(&my_mind);

    printf("=== PHASE 1: INSCRIPTION (Building the Tree) ===\n");
    my_mind.core_memory = inscription_ritual(my_mind.core_memory, 100, "Fireball", 50);
    my_mind.core_memory = inscription_ritual(my_mind.core_memory, 50,  "IceShard", 20);
    my_mind.core_memory = inscription_ritual(my_mind.core_memory, 150, "Thunder", 80);
    my_mind.core_memory = inscription_ritual(my_mind.core_memory, 25,  "Light", 10);
    my_mind.core_memory = inscription_ritual(my_mind.core_memory, 75,  "Shadow", 30);
    my_mind.core_memory = inscription_ritual(my_mind.core_memory, 125, "Heal", 40);
    my_mind.core_memory = inscription_ritual(my_mind.core_memory, 175, "Meteor", 90);

    printf("Grimoire Content (Sorted): ");
    printf("\n");
    channel_stream(my_mind.core_memory); 
    printf("\n");

    printf("\n=== PHASE 2: STRUCTURAL ANALYSIS ===\n");
    printf("Mental Depth (Height): %d\n", measure_mental_depth(my_mind.core_memory));
    printf("Unstable Fragments (Leaves): %d\n", count_unstable_fragments(my_mind.core_memory));

    printf("\n=== PHASE 3: MANA FLUX (Range 25-45) ===\n");
    detect_mana_flux(my_mind.core_memory, 25, 45);

    printf("\n=== PHASE 4: LINEAGE TRACE (Target: 75) ===\n");
    trace_lineage(my_mind.core_memory, 75);

    printf("\n=== PHASE 5: BANISHMENT (Deleting Node 50 - Two Children) ===\n");
    my_mind.core_memory = banish_shard(my_mind.core_memory, 50);
    printf("After Banishment: \n");
    channel_stream(my_mind.core_memory);
    printf("\n");

    printf("\n=== PHASE 6: MIRROR DIMENSION (Inverting Tree) ===\n");
    mirror_dimension(my_mind.core_memory);
    printf("Mirrored Output (Should be Reverse Sorted): \n");
    channel_stream(my_mind.core_memory);
    printf("\n");

    printf("\n=== PHASE 7: SHUTDOWN ===\n");
    mental_shutdown(my_mind.core_memory);
    printf("Mind Palace collapsed.\n");

    return 0;
}

// ====================== FUNCTION IMPLEMENTATIONS ======================

void init_grimoire(Grimoire *g) {
    g->core_memory = NULL;
}

MemoryShard* inscription_ritual(MemoryShard *root, int id, char *name, int mana) {
    // TODO: Implement recursive BST insert

    MemoryShard** trav = &root;

    for(;*trav  != NULL && (*trav)->info.arcane_id != id;) {
        trav = (*trav)->info.arcane_id < id ? &(*trav)->solar_link : &(*trav)->void_link;
    }

    if (*trav == NULL) {

        MemoryShard* new = malloc(sizeof(MemoryShard));
        if (new == NULL) return root;

        new->info.arcane_id = id;
        new->info.mana_cost = mana;
        strcpy(new->info.spell_name, name);
        new->solar_link = NULL;
        new->void_link = NULL;


        *trav = new;
        return root;

    }


    return root;

}

MemoryShard* banish_shard(MemoryShard *root, int id) {
    // TODO: Implement recursive BST delete

    if (root == NULL) return NULL;
    MemoryShard** trav = &root;
    for(;*trav != NULL && (*trav)->info.arcane_id != id;) {
        trav = (*trav)->info.arcane_id < id ? &(*trav)->solar_link : &(*trav)->void_link;
    }


    if (*trav == NULL) return root;

    MemoryShard* temp = *trav;

    if ((*trav)->void_link == NULL && (*trav)->solar_link == NULL) {
        free(temp);
        *trav = NULL;
    } else if ((*trav)->void_link == NULL) {
        *trav = (*trav)->solar_link;
        free(temp);
    }else if ((*trav)->solar_link == NULL) {
        *trav = (*trav)->void_link;
        free(temp);
    } else {
        MemoryShard** succ = &(*trav)->solar_link;
        while ((*succ)->void_link)  {
            succ = &(*succ)->void_link;
        }
        (*trav)->info = (*succ)->info;

        // (*trav)->solar_link = banish_shard(*trav, id);
        
        MemoryShard* target = *succ;
        *succ = (*succ)->solar_link;
        free(target);
    }
    return root;
}

MemoryShard* find_weakest_link(MemoryShard *root) {
    // TODO: Traverse leftmost nodes
    if (root == NULL) return NULL;

    while (root->void_link) {
        root = root->void_link;
    }

    return root;
}

MemoryShard* recall_memory(MemoryShard *root, int id) {
    // TODO: Implement BST search
    

    if (root == NULL) return NULL;

    MemoryShard* trav = root;
    for(; trav != NULL;) {
        if (trav->info.arcane_id == id) {
            return trav;
        }
        trav = trav->info.arcane_id < id ? (trav)->solar_link : trav->void_link;
    }

    return NULL;
}

void channel_stream(MemoryShard *root) {

    if (root == NULL) 
        return;
    

    // First, traverse the left subtree (void_link)
    channel_stream(root->void_link);


    // Then, visit the current node
    printf("[%d] %s (Mana: %d) \n ", root->info.arcane_id, root->info.spell_name, root->info.mana_cost);

    // Finally, traverse the right subtree (solar_link)
    channel_stream(root->solar_link);
}


void mental_shutdown(MemoryShard *root) {
    // TODO: Post-order free

    if (root == NULL) return;
    
    mental_shutdown(root->void_link);
    mental_shutdown(root->solar_link);
    free(root);
}

int measure_mental_depth(MemoryShard *root) {
    // TODO: Return max depth
    if (root == NULL) return -1;

    int c = measure_mental_depth(root->void_link);
    int c1 = measure_mental_depth(root->solar_link);

    return (c < c1  ? c1 : c) +1;
    
    return 0;
}

int count_unstable_fragments(MemoryShard *root) {
    // TODO: Return count of leaves

    if (root == NULL) return -1;
    int c;
    

    if (root->void_link == NULL && root->solar_link == NULL) 
    return 1;

     int left = count_unstable_fragments(root->void_link);
   
     int right = count_unstable_fragments(root->solar_link);

    return left + right;
}

void detect_mana_flux(MemoryShard *root, int min_mana, int max_mana) {
    // TODO: Traverse and print spells within mana range

    if (root == NULL) return;
    detect_mana_flux(root->void_link, min_mana, max_mana);
    if (root->info.mana_cost > min_mana && root->info.mana_cost < max_mana) {
        printf("[%d] %s (Mana: %d) \n ", root->info.arcane_id, root->info.spell_name, root->info.mana_cost);

    }
        detect_mana_flux(root->solar_link, min_mana, max_mana);

}

bool trace_lineage(MemoryShard *root, int target_id) {
    // TODO: Print path and return true if found

    MemoryShard* trav = root;
    while (trav) {
        if (trav->info.arcane_id == target_id) {
            printf("Existing... Valid Lineage\n");
            return true;
        }
        trav = trav->info.arcane_id < target_id ? trav->solar_link : trav->void_link;
    }
    return false;
}

void mirror_dimension(MemoryShard *root) {
    // TODO: Swap left and right recursively

    if (root == NULL) return;

    MemoryShard* temp = root->void_link;
    root->void_link = root->solar_link;
    root->solar_link = temp;


    mirror_dimension(root->void_link);
    mirror_dimension(root->solar_link);


}

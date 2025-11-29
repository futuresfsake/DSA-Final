#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define POCKETS 7

// The Node
typedef struct Artifact {
    int item_id;              // Key
    char name[30];            // Data
    struct Artifact* chain;   // Next Pointer
} Artifact;

// The Table
typedef struct {
    Artifact* pockets[POCKETS];
} Backpack;

// ------------------------------------------------------------------

/* * MISSION: Init. 
 */
void equip_backpack(Backpack* pack);

/* * MISSION: Upsert (Update or Insert).
 * Calculate pocket index.
 * Search list. 
 * If item_id found -> update 'name'.
 * If not found -> Insert at HEAD.
 */
void loot_item(Backpack* pack, int id, char* name);

/* * MISSION: The Deep Copy Logic Test.
 * Return a pointer to a BRAND NEW Backpack.
 * The new backpack must contain new Artifact nodes.
 * They must contain the same data as the source pack.
 * Modifying the new pack should NOT affect the old pack.
 */
Backpack* save_game_state(Backpack* source_pack);

/* * MISSION: List Reversal (Logic Test).
 * Go to a specific pocket index.
 * Reverse the order of the linked list in that pocket.
 * (Standard interview question applied to a hash bucket).
 */
void rummage_pocket(Backpack* pack, int pocket_index);

/* * MISSION: Deletion by ID.
 * Standard removal. Handle head, middle, and tail cases.
 */
void discard_item(Backpack* pack, int id, char* name);

/* * MISSION: Print.
 * Show the contents of the pack.
 */
void check_inventory(Backpack* pack);
int hashKey(int id, char* name);
void destroy_backpack (Backpack* pack);

int main() {
    // 1. MISSION: Init
    printf("--- MISSION 1: EQUIP BACKPACK ---\n");
    Backpack myPack;
    equip_backpack(&myPack);
    printf("Backpack initialized.\n\n");

    // 2. MISSION: Upsert (Loot)
    // POCKETS is 5. Key % 5 determines index.
    printf("--- MISSION 2: LOOT ITEMS ---\n");
    loot_item(&myPack, 10, "Rusty Sword");    // Index 0 (10%5)
    loot_item(&myPack, 5, "Old Coin");        // Index 0 (Collision!)
    loot_item(&myPack, 1, "Health Potion");   // Index 1
    loot_item(&myPack, 6, "Mana Potion");     // Index 1 (Collision!)
    loot_item(&myPack, 2, "Map");             // Index 2
    
    // Test Update (Upsert) logic
    loot_item(&myPack, 10, "Shiny Sword");    // Update Rusty Sword to Shiny Sword
    
    check_inventory(&myPack);

    // 3. MISSION: Deep Copy
    printf("\n--- MISSION 3: SAVE GAME STATE (DEEP COPY) ---\n");
    Backpack* savedPack = save_game_state(&myPack);
    
    printf(">> Modifying ORIGINAL pack (Adding 'Gold Bar' to Index 0)...\n");
    loot_item(&myPack, 0, "Gold Bar"); 
    
    printf(">> Checking ORIGINAL Pack:\n");
    check_inventory(&myPack);
    
    printf(">> Checking SAVED Pack (Should NOT have Gold Bar):\n");
    check_inventory(savedPack);

  
    // 5. MISSION: Deletion
    printf("\n--- MISSION 5: DISCARD ITEM ---\n");
    printf("Discarding item ID 6 (Mana Potion)...\n");
    discard_item(&myPack, 6, "Mana Potion");
    check_inventory(&myPack);

    // Cleanup
    destroy_backpack(&myPack); // Cleans list nodes
    destroy_backpack(savedPack); 
    free(savedPack); // Free the struct itself since it was malloc'd

    return 0;
}

void equip_backpack(Backpack* pack) {
    for(int i = 0; i < POCKETS; i++) {
        pack->pockets[i] = NULL;

    }
}

int hashKey(int id, char* name) {
    int sum = 0;
    
    for(int i = 0; name[i] != '\0'; i++) {
        sum+= name[i];
    }

    int h = sum + id;

    return h % POCKETS;

}
void loot_item(Backpack* pack, int id, char* name) {

    int idx = hashKey(id, name);

   Artifact* trav = pack->pockets[idx];
   bool found = false;

   while (trav != NULL) {
    if (strcmp(trav->name, name) == 0 && trav->item_id == id) {
        found = true;
        strcpy(trav->name, name);


   }
           trav = trav->chain;

   }

   if (!found)  {

   Artifact* new = malloc(sizeof(Artifact));
   if (!new) return;
   new->item_id = id;
   strcpy(new->name, name);
   new->chain = pack->pockets[idx];
   pack->pockets[idx] = new;
   }

}

Backpack* save_game_state(Backpack* source_pack) {

   Backpack* new = (Backpack*)malloc(sizeof(Backpack));
    equip_backpack(new);
    for(int i = 0; i < POCKETS; i++) {
        Artifact* trav= source_pack->pockets[i];

        while (trav) {

            loot_item(new,trav->item_id, trav->name);

            trav = trav->chain;
        }
    }
    return new;

}

void discard_item(Backpack* pack, int id, char* name) {

    int idx = hashKey(id, name);
    Artifact** trav = &(pack->pockets[idx]);

    for(; *trav != NULL ; trav= &(*trav)->chain) {
        if (strcmp((*trav)->name, name) == 0 && (*trav)->item_id == id) {
            Artifact* temp = *trav;
            *trav = temp->chain;
            free(temp);
            printf("%s Successfully deleted...\n", name);
            return;
        }
    }
}


void check_inventory(Backpack* pack) {

    for(int i = 0; i < POCKETS; i++) {
        Artifact* trav = pack->pockets[i];

        printf("INDEX: %d => ", i);

        if (trav == NULL) {
            printf("EMPTY\n");
        } else {
            while (trav != NULL) {
                printf("[Name: %s, ID: %d] => ", trav->name, trav->item_id);
                trav = trav->chain;
            }
            printf("NULL\n");
        }
    }
}


void destroy_backpack (Backpack* pack) {

    for(int i = 0; i  < POCKETS; i++) {
        Artifact* curr = pack->pockets[i];

        while (curr) {
            Artifact* temp = curr;
            curr = curr->chain;
            free(temp);
        }

        pack->pockets[i] = NULL;
    }

    printf("Destroyed succesfully!\n");
}
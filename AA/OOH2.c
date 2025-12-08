#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



#define SECTOR_COUNT 7  // The size of the primary array

// ------------------------------------------------------------------
// DATA STRUCTURES
// ------------------------------------------------------------------




// This represents a single piece of stolen data (The Linked List Element)
typedef struct Fragment {
    int signal_id;              // The unique identifier (Key)
    char encrypted_payload[64]; // The data (Value)
    struct Fragment* uplink;    // Pointer to the next piece of data
} Fragment;

// This represents your storage device (The Hash Table)
typedef struct {
    // An array of pointers to Fragments.
    // Each index represents a "Sector" in the grid.
    Fragment* sectors[SECTOR_COUNT]; 
} CyberDeck;

// ------------------------------------------------------------------
// PROTOTYPES
// ------------------------------------------------------------------

void boot_system(CyberDeck* deck);
int compute_sector_offset(int signal_id);
void upload_packet(CyberDeck* deck, int signal_id, char* payload);
char* retrieve_intel(CyberDeck* deck, int signal_id);
void purge_trace(CyberDeck* deck, int signal_id);
void visualize_matrix(CyberDeck* deck);


/*
 * MISSION: Initialize the CyberDeck.
 * Ensure all sectors are initially wiped clean (set to NULL).
 */
void boot_system(CyberDeck* deck) {
    for(int i= 0; i < SECTOR_COUNT; i++) {
        deck->sectors[i] = NULL;
    }
}

/*
 * MISSION: Determine the Sector Index.
 * Logic: Return (signal_id modulo SECTOR_COUNT).
 */
int compute_sector_offset(int signal_id) {

    return signal_id % SECTOR_COUNT;
}

/*
 * MISSION: Store a new Fragment into the Deck.
 * 1. Create a new Fragment.
 * 2. Calculate the sector index.
 * 3. Insert at the BEGINNING of that sector's chain (Head Insertion).
 * (This is faster than traversing to the end).
 */
void upload_packet(CyberDeck* deck, int signal_id, char* payload) {

    int index = compute_sector_offset(signal_id);

    Fragment* trav = deck->sectors[index];
    bool found = false;

    while (trav) {
        if (trav->signal_id == signal_id) {
            found = true;
            break;
        }
        trav = trav->uplink;
    }


    if (found==false) {
        Fragment* new = malloc(sizeof(Fragment));
        if (new == NULL) return;
        new->signal_id = signal_id;
        strcpy(new->encrypted_payload, payload);
        new->uplink = deck->sectors[index];
        deck->sectors[index] = new;
    }


    
}

/*
 * MISSION: Find specific intel.
 * Search the specific sector chain for the signal_id.
 * Return the payload if found, or NULL if not found.
 */
char* retrieve_intel(CyberDeck* deck, int signal_id) {

    int index = compute_sector_offset(signal_id);

    Fragment* trav = deck->sectors[index];

    while (trav ) {
        if (trav->signal_id == signal_id) {
            return trav->encrypted_payload;
        }
        trav = trav->uplink;
    }

    return NULL;
}

/*
 * MISSION: Remove evidence.
 * Find the Fragment with the matching signal_id and remove it 
 * from the chain. Free the memory.
 * Handle cases: Head deletion vs Middle/End deletion.
 */
void purge_trace(CyberDeck* deck, int signal_id) {

    int index = compute_sector_offset(signal_id);

    Fragment** trav = &(deck->sectors[index]);

    for(; *trav != NULL; trav = &(*trav)->uplink) {
        if ((*trav)->signal_id == signal_id) {
            Fragment* temp = *trav;
            *trav = temp->uplink;
            free(temp);
            printf("%d succesffully deleted...\n", signal_id);
            return;
        }
    }
}

/*
 * MISSION: Visualize the Grid.
 * Print every sector and the chain of fragments within it.
 * Format: [Sector 0]: [ID: 14 | Data] -> [ID: 7 | Data] -> NULL
 */
void visualize_matrix(CyberDeck* deck) {


    for(int i = 0; i < SECTOR_COUNT;i++) {
        Fragment* trav = deck->sectors[i];

        printf("[Sector %d]: ", i);
        if (trav == NULL) {
            printf("NULL\n");
        } else {
        while (trav) {
            printf("[ID: %d | %s]-> ", trav->signal_id, trav->encrypted_payload);
            trav = trav->uplink;

        }

        printf("NULL\n");
    }
    }
}

// ------------------------------------------------------------------
// MAIN EXECUTION
// ------------------------------------------------------------------

int main() {
    CyberDeck my_deck;

    // 1. Initialize
    boot_system(&my_deck);

    printf("--- SYSTEM ONLINE ---\n");

    // 2. Upload Data (Insertions)
    // Note: Trace how these IDs map to the SECTOR_COUNT (7)
    upload_packet(&my_deck, 14, "CorpSecrets_Alpha"); // 14 % 7 = 0
    upload_packet(&my_deck, 22, "BioData_V2");        // 22 % 7 = 1
    upload_packet(&my_deck, 7,  "Admin_Pass");        // 7  % 7 = 0 (Collision!)
    upload_packet(&my_deck, 29, "Firewall_Key");      // 29 % 7 = 1 (Collision!)
    upload_packet(&my_deck, 5,  "Credits_Wallet");    // 5  % 7 = 5

    // 3. Visualize
    printf("\n[Current Grid Status]:\n");
    visualize_matrix(&my_deck);

    // 4. Retrieve Data (Search)
    printf("\n[Decrypting Signal 22]: %s\n", retrieve_intel(&my_deck, 22));
    printf("[Decrypting Signal 99]: %s\n", retrieve_intel(&my_deck, 99)); // Should be null

    // 5. Delete Data (Deletion)
    printf("\n[Purging Trace 7 (Admin_Pass)]...\n");
    purge_trace(&my_deck, 7); // Head of list at index 0

    printf("\n[Final Grid Status]:\n");
    visualize_matrix(&my_deck);

    return 0;
}

// ------------------------------------------------------------------
// IMPLEMENTATIONS (Your Mission)
// ------------------------------------------------------------------

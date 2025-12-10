#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
===========================================================
    NASA TELEMETRY PACKET CACHE (OPEN HASHING DICTIONARY)
===========================================================

Story:
------
Due to budget cuts, NASA decided to outsource their telemetry 
caching system to you (a broke C programmer). Your mission: 
Build an OPEN HASHING dictionary that stores spacecraft 
telemetry packets.

Each packet arrives as a PACKET ID string (ex: "PKT-ALPHA-42")
and must be cached with its decoded telemetry data string.

Core Operations:
----------------
1. lookup_packet()   → Check if a packet already exists.
2. insert_packet()   → Insert a packet (or skip if existing).
3. simulate_ground_station_fetch()
        Simulates expensive ground station decoding.
        Returns dynamically allocated string.

You must implement all functions at the bottom.
===========================================================
*/

#define HASH_BUCKETS 100

// ================= STRUCT DEFINITIONS ====================

typedef struct TelemetryEntry {
    char *packet_id;            // Dynamically allocated
    char *decoded_data;         // Dynamically allocated
    struct TelemetryEntry *next;
} TelemetryEntry;

typedef struct {
    TelemetryEntry *buckets[HASH_BUCKETS];
} TelemetryTable;


// ================= FUNCTION PROTOTYPES ====================

unsigned int hash_packet(const char *str);
void init_table(TelemetryTable *table);
char *lookup_packet(TelemetryTable *table, const char *key);
bool insert_packet(TelemetryTable *table, const char *key);
char *simulate_ground_station_fetch(const char *packet_id);
void free_table(TelemetryTable *table);
void print_packet(const char *packet_id, const char *data);

void run_test(TelemetryTable *table, int test_id);


// ==================== HASH FUNCTION ========================
// Simple DJB2 hash
unsigned int hash_packet(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % HASH_BUCKETS;
}


// ==================== TEST CASES ===========================

void run_test(TelemetryTable *table, int test_id) {
    char *data = NULL;
    const char *packet = NULL;
    bool status;

    switch (test_id) {
        case 1:
            printf("\n--- Test 1: New Packet Insertion (PKT-ALPHA-42) ---\n");
            packet = "PKT-ALPHA-42";

            data = lookup_packet(table, packet);
            if (data == NULL) {
                printf("  [Lookup] MISS → Decoding at ground station...\n");
                status = insert_packet(table, packet);
                if (status)
                    printf("  [Insert] SUCCESS: Packet cached.\n");
                else
                    printf("  [Insert] FAILED: No data returned.\n");
                data = lookup_packet(table, packet);
            }
            print_packet(packet, data);
            break;

        case 2:
            printf("\n--- Test 2: Lookup Existing Packet (PKT-ALPHA-42) ---\n");
            packet = "PKT-ALPHA-42";

            data = lookup_packet(table, packet);
            if (data != NULL)
                printf("  [Lookup] HIT → Returning cached telemetry.\n");
            else
                printf("  [Lookup] MISS (ERROR: Run Test 1 first!)\n");

            print_packet(packet, data);
            break;

        case 3:
            printf("\n--- Test 3: Redundant Insertion Check ---\n");
            packet = "PKT-ALPHA-42";
            status = insert_packet(table, packet);
            if (status)
                printf("  [Insert] SKIPPED (Packet already cached).\n");
            else
                printf("  [Insert] ERROR: Something went wrong.\n");

            print_packet(packet, lookup_packet(table, packet));
            break;

        case 4:
            printf("\n--- Test 4: New Packet Insertion (PKT-BRAVO-99) ---\n");
            packet = "PKT-BRAVO-99";

            data = lookup_packet(table, packet);
            if (data == NULL) {
                printf("  [Lookup] MISS → Decoding in progress...\n");
                insert_packet(table, packet);
                data = lookup_packet(table, packet);
            }
            print_packet(packet, data);
            break;

        case 5:
            printf("\n--- Test 5: Failing Packet (PKT-ERROR-404) ---\n");
            packet = "PKT-ERROR-404";

            data = lookup_packet(table, packet);

            if (data == NULL) {
                printf("  [Lookup] MISS → Attempting to decode...\n");
                status = insert_packet(table, packet);
                if (!status)
                    printf("  [Insert] FAILED (Ground station returned NULL)\n");
            }
            print_packet(packet, lookup_packet(table, packet));
            break;

        default:
            printf("Invalid choice.\n");
    }
}


// ==================== MAIN ===============================

int main() {
    TelemetryTable table;
    init_table(&table);

    int choice = -1;

    printf("NASA Telemetry Cache Simulation (Open Hashing)\n");
    printf("-----------------------------------------------------\n");

    while (choice != 0) {
        printf("\nChoose test case:\n");
        printf("1. Insert new packet (PKT-ALPHA-42)\n");
        printf("2. Lookup existing packet\n");
        printf("3. Redundant insertion test\n");
        printf("4. Insert second new packet (PKT-BRAVO-99)\n");
        printf("5. Simulate failing packet (PKT-ERROR-404)\n");
        printf("0. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
            continue;
        }

        if (choice != 0)
            run_test(&table, choice);
    }

    free_table(&table);
    return 0;
}


// =================================================================
//  YOU MUST IMPLEMENT THESE FUNCTIONS BELOW (EMPTY IMPLEMENTATIONS)
// =================================================================

// Initialize table (set all buckets to NULL)
void init_table(TelemetryTable *table) {
    // IMPLEMENT HERE

    for(int i = 0; i < HASH_BUCKETS; i++) {
        table->buckets[i] = NULL;
    }
}

// Search for packet ID
char *lookup_packet(TelemetryTable *table, const char *key) {
    
    int index = hash_packet(key);

    TelemetryEntry* trav = table->buckets[index];

    while (trav) {
        if (strcmp(trav->packet_id, key) == 0) {
            return trav->decoded_data;
        }
        trav = trav->next;
    }

    return NULL;
}

// Insert packet (call simulate_ground_station_fetch if new)
bool insert_packet(TelemetryTable *table, const char *key) {
  

    int index = hash_packet(key);

    TelemetryEntry* trav = table->buckets[index];
    while (trav) {
        if (strcmp(trav->packet_id, key) == 0) {
            return true;
        }
        trav=trav->next;
    }


    TelemetryEntry* new = malloc(sizeof(TelemetryEntry));
    if (new == NULL) return false;

    char* fetch = simulate_ground_station_fetch(key);
    if (fetch == NULL) return false;

    new->decoded_data = malloc(strlen(fetch)+1);
    strcpy(new->decoded_data, fetch);
    new->packet_id = malloc(strlen(key)+1);
    strcpy(new->packet_id, key);

    new->next = table->buckets[index];
    table->buckets[index] = new;
    return true;


}


// Free all memory in table
void free_table(TelemetryTable *table) {
    // IMPLEMENT HERE

    for(int i = 0; i < HASH_BUCKETS; i++) {
        TelemetryEntry* head = table->buckets[i];

        while (head) {
            TelemetryEntry* temp = head;
            head = temp->next;
            free(temp);
        }

        table->buckets[i] = NULL;
    }
}

// Pretty print
void print_packet(const char *packet_id, const char *data) {
    if (data == NULL) {
        printf("  [Data] No cached telemetry for '%s'\n", packet_id);
        return;
    }
    printf("  Cached telemetry for '%s':\n", packet_id);
    printf("    %.60s...\n", data);
}

char *simulate_ground_station_fetch(const char *packet_id) {
    // 1. If packet is the error code → simulate failure
    if (strcmp(packet_id, "PKT-ERROR-404") == 0) {
        return NULL;
    }

    // 2. Simulate expensive fetch delay
    // (This does nothing meaningful, just burns time)
    for (volatile long i = 0; i < 50000000; i++);

    // 3. Create a “fetched” message dynamically
    const char *prefix = "GroundStationData:";
    size_t size = strlen(prefix) + strlen(packet_id) + 1;

    char *result = malloc(size);
    if (!result) return NULL;

    strcpy(result, prefix);
    strcat(result, packet_id);

    return result;
}
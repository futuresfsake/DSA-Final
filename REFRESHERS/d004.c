/*
==============================================================
     CYBERSEC THREAT INTELLIGENCE DICTIONARY (OPEN HASHING)
==============================================================

STORY:
You are tasked to maintain a Threat Intelligence HashTable system
for SentinelCyber. Each threat reported to the system is identified
by a unique signature string (key). When a threat is first seen,
the system automatically fetches its intelligence report from an
external API (simulated by fetch_threat_intel).

The system tracks:
 - description
 - severity (1 to 10)
 - number of detections (hits)

Special rules:
 - When a threat is detected >5 times, it's automatically severity 10.
 - Certain updates require conditions.
 - Some threats can be blacklisted and removed.
 - All operations are performed using OPEN HASHING (SEPARATE CHAINING).

You must implement the dictionary operations below.
Teacher test cases call these functions.
==============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// =============================================================
//                        CONSTANTS
// =============================================================
#define BUCKETS 103   // Prime number for better hash distribution

// =============================================================
//                     STRUCT DEFINITIONS
// =============================================================
typedef struct ThreatEntry {
    char *signature;       // Key
    char *description;     // Value
    int severity;          // 1–10 scale
    int hits;              // Number of times detected
    struct ThreatEntry *next;
} ThreatEntry;

typedef struct {
    ThreatEntry *buckets[BUCKETS];
} ThreatTable;

// =============================================================
//                   FUNCTION PROTOTYPES
// =============================================================
void init_table(ThreatTable *t);
ThreatEntry *lookup_threat(ThreatTable *t, const char *signature);
bool report_threat(ThreatTable *t, const char *signature);
bool update_severity(ThreatTable *t, const char *signature, int new_sev);

void remove_blacklisted(ThreatTable *t);   // HARD OPERATION
void auto_decay_severity(ThreatTable *t);  // HARD OPERATION

unsigned int hash(const char *s);
char *fetch_threat_intel(const char *signature);  // Provided
void run_simulation(ThreatTable *t, int test_id); // Provided
void print_table(ThreatTable *t);                 // Provided
void free_all(ThreatTable *t);

// =============================================================
//                   FUNCTION IMPLEMENTATIONS
//                  (YOU FILL IN ALL EMPTY PARTS)
// =============================================================

void init_table(ThreatTable *t) {

    // implement here

    for(int i = 0; i < BUCKETS; i++) {
        t->buckets[i] = NULL;
    }

}

ThreatEntry *lookup_threat(ThreatTable *t, const char *signature) {

    int index = hash(signature);

    ThreatEntry* trav = t->buckets[index];
    for(; trav != NULL; trav = trav->next) {
        if(strcmp(trav->signature, signature)==0) {
            return trav;
        }
    }

    return NULL;
}

bool report_threat(ThreatTable *t, const char *signature) {
    

    

    int index = hash(signature);

    //! searching

    ThreatEntry* trav = t->buckets[index];
    for(; trav != NULL; trav = trav->next) {
        if (strcmp(trav->signature, signature)==0) {
            trav->hits++;
            if (trav->hits>5) {
                trav->severity = 10;
               
            }
            return true;
        }
    }

    char* fetch = fetch_threat_intel(signature);
    if (!fetch) return false;

    ThreatEntry* new = malloc(sizeof(ThreatEntry));
    if (!new) {
        return false;
    }

    new->signature = malloc(strlen(signature)+1);
    new->description = malloc(strlen(fetch)+1);

    strcpy(new->signature, signature);
    strcpy(new->description, fetch);
    new->severity = 1;
    new->hits = 1;

    new->next = t->buckets[index];
    t->buckets[index] = new;



    

    return true;
}

bool update_severity(ThreatTable *t, const char *signature, int new_sev) {

    
    int index = hash(signature);
    
    if (lookup_threat(t,signature)) {
        ThreatEntry* trav  = t->buckets[index];
        for(; trav != NULL; trav = trav->next) {
            if (strcmp(trav->signature, signature) == 0) {
                
               if (new_sev == 7 && trav->severity < new_sev) {
                trav->severity = new_sev;
                return true;

               }
            }
        }

    }

    return false;
}

void remove_blacklisted(ThreatTable *t) {

    for(int i = 0; i < BUCKETS; i++) {

        ThreatEntry** trav = &(t->buckets[i]);


        for(; *trav != NULL; trav = &(*trav)->next) {
            if ((*trav)->severity == 10 && (*trav)->hits >=10) {
                ThreatEntry* Remove = *trav;
                *trav = Remove->next;
                free(Remove);
            }
        }
    }
}



    void auto_decay_severity(ThreatTable *t) {
    if (!t) return;

    for (int i = 0; i < BUCKETS; i++) {
        ThreatEntry *curr = t->buckets[i];
        while (curr != NULL) {
            if (curr->hits < 3) {
                curr->severity -= 2;
            } else {
                curr->severity -= 1;
            }

            // Ensure severity does not go below 1
            if (curr->severity < 1) {
                curr->severity = 1;
            }

            curr = curr->next;
        }
    }
}



unsigned int hash(const char *s) {
    unsigned long h = 5381;
    int c;
    while ((c = *s++)) {
        h = ((h << 5) + h) + c;  // h * 33 + c
    }
    return h % BUCKETS;
}

void free_all(ThreatTable *t) {

    // implement here

}

// =============================================================
//      BELOW ARE UTILITIES AND TEST CASES PROVIDED BY TEACHER
// =============================================================

char *fetch_threat_intel(const char *signature) {
    char *res = malloc(100);
    sprintf(res, "Fetched intelligence for threat: %s", signature);
    return res;
}

void print_table(ThreatTable *t) {
    printf("\n======= Threat Intelligence Table =======\n");
    for (int i = 0; i < BUCKETS; i++) {
        ThreatEntry *trav = t->buckets[i];
        if (trav != NULL) {
            printf("[Bucket %d]\n", i);
            while (trav != NULL) {
                printf("  %s | Sev: %d | Hits: %d\n",
                       trav->signature, trav->severity, trav->hits);
                trav = trav->next;
            }
        }
    }
    printf("=========================================\n\n");
}

void run_simulation(ThreatTable *t, int test_id) {
    if (test_id == 1) {
        printf("[TEST 1] Basic report test\n");
        report_threat(t, "SPYWARE-X1");
        report_threat(t, "SPYWARE-X1");
        print_table(t);
    }
    else if (test_id == 2) {
        printf("[TEST 2] Auto severity raise\n");
        for (int i = 0; i < 7; i++)
            report_threat(t, "RANSOM-777");
        print_table(t);
    }
    else if (test_id == 3) {
        printf("[TEST 3] Blacklisting removal\n");
        for (int i = 0; i < 12; i++)
            report_threat(t, "BOTNET-99");
        remove_blacklisted(t);
        print_table(t);
    }
    else if (test_id == 4) {
        printf("[TEST 4] Severity decay\n");
        report_threat(t, "LOW-LEVEL");
        update_severity(t, "LOW-LEVEL", 5);
        auto_decay_severity(t);
        print_table(t);
    }
}

int main() {
    ThreatTable t;
    init_table(&t);

    // teacher chooses test case
    run_simulation(&t, 1);

    free_all(&t);
    return 0;
}

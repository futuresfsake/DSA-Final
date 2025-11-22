#include <stdio.h>
#include <stdlib.h>

#include <string.h>


#include <stdbool.h>

#define HASH_BUCKETS 100

// Structure for a single entry in the cache (a Node in the linked list)
typedef struct CacheEntry {
    char *url;                   // The URL string (dynamically allocated key)
    char *content;               // The web page content (dynamically allocated value)
    struct CacheEntry *next;     // Pointer for separate chaining (Open Hashing)
} CacheEntry;

// Structure for the entire Hash Table
typedef struct {
    CacheEntry *buckets[HASH_BUCKETS];
} HashTable;

// --- Function Prototypes ---
void init_cache(HashTable *table);
char *lookup_cache(HashTable *table, const char *key);
bool insert_cache(HashTable *table, const char *key);

unsigned int hash(const char *str);
void free_cache(HashTable *table);
char *simulate_web_request(const char *url);
void cleanup_fetched_results(char **results);
void print_content(const char *url, const char *content);
void run_test_case(HashTable *cache, int test_id);


void run_test_case(HashTable *cache, int test_id) {
    char *fetched_content = NULL;
    const char *url_to_test = NULL;
    bool insertion_success = false;

    // Note: Tests 2 and 3 depend on test 1 being run first.
    // Tests 4 and 5 depend on tests 1-3 having run.

    switch (test_id) {
        case 1:
            // --- Test 1: New URL (Cache MISS -> Insert calls Web Request -> Cache INSERT) ---
            printf("\n--- Test 1: New URL Insertion (https://www.google.com/cse_blog) ---\n");
            url_to_test = "https://www.google.com/cse_blog";

            fetched_content = lookup_cache(cache, url_to_test);

            if (fetched_content == NULL) {
                printf("  [Lookup Status] URL '%s' MISS. Attempting to fetch and insert (WEB REQUEST in progress)...\n", url_to_test);

                insertion_success = insert_cache(cache, url_to_test);

                if (insertion_success) {
                    printf("  [Insert Status] Insertion successful (Content fetched and cached).\n");
                } else {
                    printf("  [Insert Status] Insertion failed (Web request returned no content).\n");
                }

                fetched_content = lookup_cache(cache, url_to_test);
            } else {
                printf("  [Lookup Status] URL '%s' HIT. Returning cached results (ERROR: Should have been a MISS).\n", url_to_test);
            }
            print_content(url_to_test, fetched_content);
            break;

        case 2:
            // --- Test 2: Existing URL (Expected Cache HIT) ---
            printf("\n--- Test 2: Existing URL Lookup (https://www.google.com/cse_blog) ---\n");
            url_to_test = "https://www.google.com/cse_blog";

            // Lookup (Should be a HIT now, if Test 1 was run)
            fetched_content = lookup_cache(cache, url_to_test);

            if (fetched_content != NULL) {
                printf("  [Lookup Status] URL '%s' HIT. Returning cached content.\n", url_to_test);
            } else {
                 printf("  [Lookup Status] URL '%s' MISS (ERROR: Test 1 must be run first).\n", url_to_test);
            }
            print_content(url_to_test, fetched_content);
            break;

        case 3:
            // --- Test 3: Redundant Insertion Test (Expected Skip) ---
            printf("\n--- Test 3: Redundant Insertion Test (https://www.google.com/cse_blog) ---\n");
            url_to_test = "https://www.google.com/cse_blog";

            insertion_success = insert_cache(cache, url_to_test);

            if (insertion_success) {
                printf("  [Insert Status] Insertion was logically skipped because URL '%s' already exists.\n", url_to_test);
            } else {
                printf("  [Insert Status] Error: Insertion failed for existing URL.\n");
            }

            printf("  Note: No web request occurred. Cache content is unchanged.\n");

            fetched_content = lookup_cache(cache, url_to_test);
            print_content(url_to_test, fetched_content);
            break;

        case 4:
            // --- Test 4: Another New URL (Cache MISS -> Insert calls Web Request -> Cache INSERT) ---
            printf("\n--- Test 4: Second New URL Insertion (https://api.google.com/api/v1/earnings) ---\n");
            url_to_test = "https://api.google.com/api/v1/earnings";

            fetched_content = lookup_cache(cache, url_to_test);

            if (fetched_content == NULL) {
                printf("  [Lookup Status] URL '%s' MISS. Attempting to fetch and insert (WEB REQUEST in progress)...\n", url_to_test);

                insertion_success = insert_cache(cache, url_to_test);

                if (insertion_success) {
                    printf("  [Insert Status] Insertion successful (Content fetched and cached).\n");
                } else {
                    printf("  [Insert Status] Insertion failed (Web request returned no content).\n");
                }

                fetched_content = lookup_cache(cache, url_to_test);
            } else {
                printf("  [Lookup Status] URL '%s' HIT. Returning cached content (ERROR: Should have been a MISS).\n", url_to_test);
            }
            print_content(url_to_test, fetched_content);
            break;

        case 5:
            // --- Test 5: Failing URL (Cache MISS -> Web Request Fails) ---
            printf("\n--- Test 5: Failing URL (http://404.example.com) ---\n");
            url_to_test = "http://404.example.com/notfound";

            fetched_content = lookup_cache(cache, url_to_test);

            if (fetched_content == NULL) {
                printf("  [Lookup Status] URL '%s' MISS. Attempting to fetch and insert (WEB REQUEST in progress)...\n", url_to_test);

                insertion_success = insert_cache(cache, url_to_test);

                if (insertion_success) {
                    printf("  [Insert Status] Error: This should not happen. Insertion successful.\n");
                } else {
                    printf("  [Insert Status] Insertion aborted because web request returned no valid content (simulated 404).\n");
                }

                fetched_content = lookup_cache(cache, url_to_test);
            } else {
                printf("  [Lookup Status] URL '%s' HIT. Returning cached results (ERROR: URL should not exist).\n", url_to_test);
            }
            print_content(url_to_test, fetched_content);
            break;

        default:
            printf("\nInvalid choice. Please enter a number between 1 and 5 (or 0 to exit).\n");
            break;
    }
}




// ---------------------------
// Hash function (DJB2)
// ---------------------------
unsigned int hash(const char *str) {
    unsigned long h = 5381;
    int c;
    while ((c = *str++)) {
        h = ((h << 5) + h) + c; // h * 33 + c
    }
    return h % HASH_BUCKETS;
}

// ---------------------------
// Initialize cache
// ---------------------------
void init_cache(HashTable *table) {
    for (int i = 0; i < HASH_BUCKETS; i++) {
        table->buckets[i] = NULL;
    }
}

// ---------------------------
// Lookup cache
// ---------------------------
char *lookup_cache(HashTable *table, const char *url) {
    unsigned int idx = hash(url);
    CacheEntry *trav = table->buckets[idx];
    while (trav) {
        if (strcmp(trav->url, url) == 0) {
            return trav->content; // Cache HIT
        }
        trav = trav->next;
    }
    return NULL; // Cache MISS
}

// ---------------------------
// Insert into cache
// ---------------------------
bool insert_cache(HashTable *table, const char *url) {
    // if (!url) return false;
    unsigned int idx = hash(url);

    // Check duplicates
    CacheEntry *trav = table->buckets[idx];
    while (trav) {
        if (strcmp(trav->url, url) == 0) {
            return true; // URL already exists → logical skip
        }
        trav = trav->next;
    }

    // Fetch from "web"
    char *fetched = simulate_web_request(url);
    if (!fetched) return false; // Web request failed

    // Allocate new node
    CacheEntry *node = malloc(sizeof(CacheEntry));
    if (!node) {
        free(fetched);
        return false;
    }

    node->url = malloc(strlen(url)+1);
    node->content = malloc(strlen(fetched)+1);
    

    strcpy(node->url, url);
    strcpy(node->content, fetched);

    free(fetched); // free temporary buffer

    // Insert at head of linked list
    node->next = table->buckets[idx];
    table->buckets[idx] = node;

    return true;
}

// ---------------------------
// Free cache memory
// ---------------------------
void free_cache(HashTable *table) {
    for (int i = 0; i < HASH_BUCKETS; i++) {
        CacheEntry *trav = table->buckets[i];
        while (trav) {
            CacheEntry *tmp = trav;
            trav = trav->next;
            free(tmp->url);
            free(tmp->content);
            free(tmp);
        }
        table->buckets[i] = NULL;
    }
}

// ---------------------------
// Simulate web request
// ---------------------------
char *simulate_web_request(const char *url) {
    if (!url) return NULL;
    if (strstr(url, "404") != NULL) return NULL; // simulate failure

    // simulate content
    char *content = malloc(256);
    if (!content) return NULL;
    snprintf(content, 256, "<html><title>%s</title><body>Simulated Content</body></html>", url);
    return content;
}

// ---------------------------
// Print content snippet
// ---------------------------
void print_content(const char *url, const char *content) {
    if (!content) {
        printf("  Content for URL '%s' not available.\n", url);
        return;
    }
    printf("Cached content for URL '%s':\n", url);
    printf("  Content snippet (first 60 chars): '%.60s'\n", content);
}

int main() {
    HashTable search_cache;
    init_cache(&search_cache);
    int choice = -1;

    printf("Google Web Content Cache Simulation (Open Hashing)\n");
    printf("----------------------------------------------------\n");
    printf("Cache Key: URL | Cache Value: Page Content String\n");
    printf("Note: Test Cases 2 and 3 require Test 1 to be run first.\n");

    while (choice != 0) {
        printf("\nSelect a test case to run:\n");
        printf("1. Run Test 1: New URL Insertion (https://www.google.com/cse_blog)\n");
        printf("2. Run Test 2: Existing URL Lookup (Expected HIT)\n");
        printf("3. Run Test 3: Redundant Insertion (Expected SKIP)\n");
        printf("4. Run Test 4: Second New URL Insertion (https://api.google.com/api/v1/earnings)\n");
        printf("5. Run Test 5: Failing URL (Web Request Fails)\n");
        printf("0. Exit and Free Memory\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number.\n");
            while (getchar() != '\n'); // flush input
            choice = -1;
            continue;
        }

        if (choice == 0) break;

        run_test_case(&search_cache, choice);
    }

    free_cache(&search_cache);
    printf("\n--- Cache memory successfully freed. ---\n");
    return 0;
}

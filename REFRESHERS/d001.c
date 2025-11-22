#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define HASH_BUCKETS 50

// ---------------------------
// Cache structures
// ---------------------------
typedef struct GradeEntry {
    char *student_id;           // Key
    char *grade;                // Value
    struct GradeEntry *next;    // Separate chaining
} GradeEntry;

typedef struct {
    GradeEntry *buckets[HASH_BUCKETS];
} GradeCache;

// ---------------------------
// Function prototypes
// ---------------------------
void init_cache(GradeCache *cache);
char *lookup_cache(GradeCache *cache, const char *student_id);
bool insert_cache(GradeCache *cache, const char *student_id);
unsigned int hash(const char *str);
void free_cache(GradeCache *cache);
char *simulate_db_fetch(const char *student_id);
void print_grade(const char *student_id, const char *grade);
void run_test_case(GradeCache *cache, int test_id);

// ---------------------------
// Hash function (DJB2)
// ---------------------------
unsigned int hash(const char *str) {
    unsigned long h = 5381;
    int c;
    while ((c = *str++)) {
        h = ((h << 5) + h) + c;
    }
    return h % HASH_BUCKETS;
}

// ---------------------------
// Initialize cache
// ---------------------------
void init_cache(GradeCache *cache) {
    for (int i = 0; i < HASH_BUCKETS; i++)
        cache->buckets[i] = NULL;
}

// ---------------------------
// Lookup cache
// ---------------------------
char *lookup_cache(GradeCache *cache, const char *student_id) {
    unsigned int idx = hash(student_id);
    GradeEntry *trav = cache->buckets[idx];
    while (trav) {
        if (strcmp(trav->student_id, student_id) == 0)
            return trav->grade;
        trav = trav->next;
    }
    return NULL;
}

// ---------------------------
// Insert into cache
// ---------------------------
bool insert_cache(GradeCache *cache, const char *student_id) {
    if (!student_id) return false;
    unsigned int idx = hash(student_id);

    GradeEntry *trav = cache->buckets[idx];
    while (trav) {
        if (strcmp(trav->student_id, student_id) == 0)
            return true; // Logical skip
        trav = trav->next;
    }

    char *fetched = simulate_db_fetch(student_id);
    if (!fetched) return false;

    GradeEntry *node = malloc(sizeof(GradeEntry));
    if (!node) { free(fetched); return false; }

    node->student_id = malloc(strlen(student_id)+1);
    node->grade = malloc(strlen(fetched)+1);

    strcpy(node->student_id, student_id);
    strcpy(node->grade, fetched);

    free(fetched);

    node->next = cache->buckets[idx];
    cache->buckets[idx] = node;

    return true;
}

// ---------------------------
// Free cache
// ---------------------------
void free_cache(GradeCache *cache) {
    for (int i = 0; i < HASH_BUCKETS; i++) {
        GradeEntry *trav = cache->buckets[i];
        while (trav) {
            GradeEntry *tmp = trav;
            trav = trav->next;
            free(tmp->student_id);
            free(tmp->grade);
            free(tmp);
        }
        cache->buckets[i] = NULL;
    }
}

// ---------------------------
// Simulate database fetch
// ---------------------------
char *simulate_db_fetch(const char *student_id) {
    if (!student_id || strstr(student_id, "INVALID") != NULL) return NULL;

    char *grade = malloc(4);
    if (!grade) return NULL;

    const char *possible_grades[] = {"A", "B", "B+", "C", "C+", "D", "F"};
    int n = sizeof(possible_grades) / sizeof(possible_grades[0]);
    snprintf(grade, 4, "%s", possible_grades[rand() % n]);
    return grade;
}

// ---------------------------
// Print grade
// ---------------------------
void print_grade(const char *student_id, const char *grade) {
    if (!grade)
        printf("Grade for student '%s' not available.\n", student_id);
    else
        printf("Cached grade for student '%s': %s\n", student_id, grade);
}

// ---------------------------
// Run test cases
// ---------------------------
void run_test_case(GradeCache *cache, int test_id) {
    const char *student_id;
    char *grade;
    bool success;

    switch (test_id) {
        case 1:
            student_id = "S12345";
            printf("\nTest 1: Insert new student %s\n", student_id);
            grade = lookup_cache(cache, student_id);
            if (!grade) {
                printf("  Cache MISS. Fetching grade...\n");
                success = insert_cache(cache, student_id);
                if (success) printf("  Insertion successful.\n");
            }
            grade = lookup_cache(cache, student_id);
            print_grade(student_id, grade);
            break;

        case 2:
            student_id = "S12345";
            printf("\nTest 2: Lookup existing student %s\n", student_id);
            grade = lookup_cache(cache, student_id);
            print_grade(student_id, grade);
            break;

        case 3:
            student_id = "S12345";
            printf("\nTest 3: Redundant insertion of student %s\n", student_id);
            success = insert_cache(cache, student_id);
            if (success) printf("  Logical skip (already exists).\n");
            grade = lookup_cache(cache, student_id);
            print_grade(student_id, grade);
            break;

        case 4:
            student_id = "S54321";
            printf("\nTest 4: Insert second student %s\n", student_id);
            success = insert_cache(cache, student_id);
            grade = lookup_cache(cache, student_id);
            print_grade(student_id, grade);
            break;

        case 5:
            student_id = "INVALID001";
            printf("\nTest 5: Insert invalid student %s\n", student_id);
            success = insert_cache(cache, student_id);
            grade = lookup_cache(cache, student_id);
            print_grade(student_id, grade);
            break;

        default:
            printf("\nInvalid test case.\n");
            break;
    }
}

// ---------------------------
// Main function
// ---------------------------
int main() {
    srand(time(NULL));

    GradeCache cache;
    init_cache(&cache);

    int choice = -1;
    while (choice != 0) {
        printf("\nSelect a test case to run:\n");
        printf("1. Insert new student\n");
        printf("2. Lookup existing student\n");
        printf("3. Redundant insertion\n");
        printf("4. Insert second student\n");
        printf("5. Invalid student ID\n");
        printf("0. Exit\nEnter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');
            choice = -1;
            continue;
        }

        if (choice != 0) run_test_case(&cache, choice);
    }

    free_cache(&cache);
    printf("\nCache memory freed.\n");
    return 0;
}

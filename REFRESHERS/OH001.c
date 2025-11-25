

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_BUCKETS 50
#define MAX_STR 100
#define MAX_ACTORS 10

// ===============================
// Complex Nested Structs
// ===============================

// Composite Key
typedef struct {
    int movieID;               
    char title[MAX_STR];       
} MovieKey;

// Movie statistdicics
typedef struct {
    int views;
    int likes;
    double avgWatchTime;
} MovieStats;

// Movie metadata
typedef struct {
    char genre[30];
    int releaseYear;
    double rating;
    char actors[MAX_ACTORS][MAX_STR];
    int actorCount;
    MovieStats stats;          
} MovieInfo;

// ===============================
// Node (Open Hashing)
// ===============================
typedef struct MovieNode {
    MovieKey key;
    MovieInfo value;
    struct MovieNode* next;    
} MovieNode;

// ===============================
// Hash Table
// ===============================
typedef struct {
    MovieNode* buckets[MAX_BUCKETS];
    int size;
} MovieDictionary;

// ===============================
// Function Declarations
// ===============================

// Core operations
void initDictionary(MovieDictionary* dict);
int hashKey(MovieKey key);
bool keysEqual(MovieKey a, MovieKey b);
void dictInsert(MovieDictionary* dict, MovieKey key, MovieInfo value);
MovieInfo* dictSearch(MovieDictionary* dict, MovieKey key);
bool dictDelete(MovieDictionary* dict, MovieKey key);
void dictDisplay(MovieDictionary* dict);


void clearDictionary(MovieDictionary* dict) {
    
    for(int i = 0; i < MAX_BUCKETS; i++) {
        MovieNode* temp = dict->buckets[i];

        while (temp) {
            MovieNode* curr = temp;
            temp = temp->next;
            free(curr);
        }
    }
    dict->size = 0;
    return;
}


int main() {
    MovieDictionary dict1, dict2;
    initDictionary(&dict1);
    initDictionary(&dict2);

    // ---------- Sample Movies ----------
    MovieKey k1 = {101, "Interstellar"};
    MovieInfo v1 = {.genre="Sci-Fi", .releaseYear=2014, .rating=8.6, .actorCount=2};
    strcpy(v1.actors[0], "Matthew McConaughey");
    strcpy(v1.actors[1], "Anne Hathaway");
    v1.stats.views = 5000; v1.stats.likes = 4500; v1.stats.avgWatchTime = 120.5;

    MovieKey k2 = {102, "Inception"};
    MovieInfo v2 = {.genre="Sci-Fi", .releaseYear=2010, .rating=8.8, .actorCount=2};
    strcpy(v2.actors[0], "Leonardo DiCaprio");
    strcpy(v2.actors[1], "Joseph Gordon-Levitt");
    v2.stats.views = 6000; v2.stats.likes = 5500; v2.stats.avgWatchTime = 110.2;

    MovieKey k3 = {103, "The Dark Knight"};
    MovieInfo v3 = {.genre="Action", .releaseYear=2008, .rating=9.0, .actorCount=2};
    strcpy(v3.actors[0], "Christian Bale");
    strcpy(v3.actors[1], "Heath Ledger");
    v3.stats.views = 7000; v3.stats.likes = 6800; v3.stats.avgWatchTime = 130.0;

    MovieKey k4 = {104, "Titanic"};
    MovieInfo v4 = {.genre="Romance", .releaseYear=1997, .rating=7.8, .actorCount=2};
    strcpy(v4.actors[0], "Leonardo DiCaprio");
    strcpy(v4.actors[1], "Kate Winslet");
    v4.stats.views = 8000; v4.stats.likes = 7500; v4.stats.avgWatchTime = 140.0;

    // ---------- Insert Movies ----------
    dictInsert(&dict1, k1, v1);
    dictInsert(&dict1, k2, v2);
    dictInsert(&dict1, k3, v3);
    dictInsert(&dict1, k4, v4);

    // printf("=== All Movies in Dictionary 1 ===\n");
    // dictDisplay(&dict1);

    // // ---------- Search ----------
    printf("\nSearching for 'Inception':\n");
    MovieInfo* found = dictSearch(&dict1, k2);
    if(found) printf("Found: %s, Genre: %s, Likes: %d\n", k2.title, found->genre, found->stats.likes);
    else printf("Movie not found.\n");

    // ---------- Delete ----------
    printf("\nDeleting 'Titanic'...\n");
    dictDelete(&dict1, k4);
    dictDisplay(&dict1);

    
    // ---------- Clear ----------
    clearDictionary(&dict1);
    printf("\nAfter clearing Dictionary 1:\n");
    dictDisplay(&dict1);

    return 0;
}

void initDictionary(MovieDictionary* dict) {

        for(int i = 0; i < MAX_BUCKETS ; i++) {
            dict->buckets[i] = NULL;
        }

        dict->size = 0;
}

int hashKey(MovieKey key) {

    int sum = 0;
    

    for(int i = 0; i < 5 && key.title[i] != '\0'; i++) {
         sum+=key.title[i];
    }

    int h = (key.movieID + sum) % MAX_BUCKETS;

    return h;
    
}
bool keysEqual(MovieKey a, MovieKey b) {
    return (strcmp(a.title, b.title)==0);
}


void dictInsert(MovieDictionary* dict, MovieKey key, MovieInfo value) {

    int h = hashKey(key);

    MovieNode* trav = dict->buckets[h];
    while (trav != NULL) {
        if (trav->key.movieID == key.movieID) {
            return;
        }
        trav = trav->next;
    }


   
        MovieNode* new = malloc(sizeof(MovieNode));
        if (!new) exit(1);

        new->key = key;
        new->value = value;
        new->next = dict->buckets[h];
        dict->buckets[h] = new;
    

}


MovieInfo* dictSearch(MovieDictionary* dict, MovieKey key) {

    int h = hashKey(key);

    MovieNode* trav = dict->buckets[h];
    while (trav) {
        if (trav->key.movieID == key.movieID && strcmp(trav->key.title, key.title)==0) {
            return &(trav->value);
        }
        trav = trav->next;

    }
    return NULL;
}
bool dictDelete(MovieDictionary* dict, MovieKey key) {
    int index = hashKey(key);

    MovieNode** trav = &(dict->buckets[index]);

    for(; *trav != NULL; trav = &(*trav)->next) {
        if ((*trav)->key.movieID == key.movieID) {
            MovieNode* temp = *trav;
            *trav = temp->next;
            free(temp);
            return true;
        }
    }

    return false;
}
void dictDisplay(MovieDictionary* dict) {
    if (!dict) return;

    printf("=== Movie Dictionary Contents ===\n");

    for (int i = 0; i < MAX_BUCKETS; i++) {
        MovieNode* current = dict->buckets[i];
        if (current) {
            printf("Bucket %d:\n", i);
            while (current) {
                printf("  MovieID: %d | Title: %s | Genre: %s | Year: %d | Rating: %.2f | Likes: %d | Views: %d | AvgWatchTime: %.2f mins\n",
                       current->key.movieID,
                       current->key.title,
                       current->value.genre,
                       current->value.releaseYear,
                       current->value.rating,
                       current->value.stats.likes,
                       current->value.stats.views,
                       current->value.stats.avgWatchTime);

                // Display actors
                if (current->value.actorCount > 0) {
                    printf("    Actors: ");
                    for (int j = 0; j < current->value.actorCount; j++) {
                        printf("%s", current->value.actors[j]);
                        if (j < current->value.actorCount - 1) printf(", ");
                    }
                    printf("\n");
                }

                current = current->next;
            }
        }
    }
}

// // Hard operations
// void dictFindByGenre(MovieDictionary* dict, char* genre);
// void dictTopN(MovieDictionary* dict, int N);
// void dictMerge(MovieDictionary* dest, MovieDictionary* src);

// // Optional tools
// int countMovies(MovieDictionary* dict);
// void clearDictionary(MovieDictionary* dict);
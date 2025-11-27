#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 7
#define MAX_NAME 50

/*
    Galactic Artifact Repository - Open Hashing (Chaining)
    -----------------------------------------------------
    The Intergalactic Museum maintains a hash table of artifacts.
    Each artifact has a unique ArtifactID, Name, and OriginPlanet.
    Collisions are handled using chaining (linked lists).
    Operations are iterative for all insert/search/delete/display.
*/

typedef struct Artifact {
    int artifactID;
    char name[MAX_NAME];
    char originPlanet[MAX_NAME];
} Artifact;

typedef struct ArtifactNode {
    Artifact data;
    struct ArtifactNode *next;
} ArtifactNode;

typedef struct {
    ArtifactNode* buckets[TABLE_SIZE];
} ArtifactTable;

void initTable(ArtifactTable *table);                     // initialize table
int hashFunction(int artifactID);                         // simple modulo hash
void insertArtifact(ArtifactTable *table, Artifact a);   // insert iteratively
bool searchArtifact(ArtifactTable *table, int artifactID); // search iteratively
bool deleteArtifact(ArtifactTable *table, int artifactID); // delete iteratively
void displayTable(ArtifactTable *table);                 // display all buckets


int totalArtifacts(ArtifactTable *table);                // count all artifacts
void clearTable(ArtifactTable *table);                  // free all memory
int findMaxArtifactID(ArtifactTable *table);            // max artifactID
int findMinArtifactID(ArtifactTable *table);            // min artifactID
// void updateArtifactOrigin(ArtifactTable *table, int artifactID, const char* newOrigin); // update origin
// void moveArtifactToBucket(ArtifactTable *table, int artifactID, int newBucket); // rehash artifact

// // ===== MAIN =====
int main() {
    ArtifactTable galRepo;
    initTable(&galRepo);

    Artifact a1 = {101, "Zyther Crystal", "Zyther"};
    Artifact a2 = {102, "Nebulon Orb", "Nebula-5"};
    Artifact a3 = {103, "Quantum Lens", "Quarkon"};
    Artifact a4 = {104, "Plasma Stone", "Plasma-X"};
    Artifact a5 = {105, "Stellar Map", "Solaria"};

    insertArtifact(&galRepo, a1);
    insertArtifact(&galRepo, a2);
    insertArtifact(&galRepo, a3);
    insertArtifact(&galRepo, a4);
    insertArtifact(&galRepo, a5);

    printf("LIST OF ARTIFACTS\n");
    displayTable(&galRepo);


    printf("\nIs 104 Existing? ");
    bool ans =  (searchArtifact(&galRepo, 104)) ? printf("YES FOUND!") : printf("NOT FOUND");

    deleteArtifact(&galRepo, 103);
     printf("\n\nLIST OF ARTIFACTS AFTER DELETING 103\n");
    displayTable(&galRepo);

    // updateArtifactOrigin(&galRepo, 105, "Solaria Prime");
    // moveArtifactToBucket(&galRepo, 102, 3);

    printf("Total Artifacts: %d\n", totalArtifacts(&galRepo));
    printf("Min ArtifactID: %d\n", findMinArtifactID(&galRepo));
    // printf("Max ArtifactID: %d\n", findMaxArtifactID(&galRepo));

    clearTable(&galRepo);

    return 0;
}



void initTable(ArtifactTable *table) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
}             
int hashFunction(int artifactID) {
    
    return artifactID % TABLE_SIZE;
}            
void insertArtifact(ArtifactTable *table, Artifact a) {
    int index = hashFunction(a.artifactID);

    ArtifactNode* trav = table->buckets[index];
    for (; trav != NULL; trav = trav->next) {
        if (trav->data.artifactID == a.artifactID) {
            return;
        }
    }

    ArtifactNode* new = malloc(sizeof(ArtifactNode));
    if (!new) return;
    new->data = a;
    new->next = table->buckets[index];
    table->buckets[index] = new;
}


bool searchArtifact(ArtifactTable *table, int artifactID) {
    int index = hashFunction(artifactID);
    ArtifactNode* trav = table->buckets[index];
    
    while (trav) {
        if (trav->data.artifactID == artifactID) {
            return true;
        }
        trav = trav->next;
    }
    return false;
}
bool deleteArtifact(ArtifactTable *table, int artifactID) {

    int index = hashFunction(artifactID);

    ArtifactNode** trav = &(table->buckets[index]);
    for(; *trav != NULL; trav = &(*trav)->next) {
        if ((*trav)->data.artifactID == artifactID) {
            ArtifactNode* temp = *trav;
            *trav = temp->next;
            free(temp);
            return true;
        }
    }
    return false;
}
void displayTable(ArtifactTable *table) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        ArtifactNode* trav = table->buckets[i];
        printf("INDEX[%d]->", i);

         if (trav == NULL) {
                printf("[EMPTY]\n");
            }  else {
                while (trav) {
                    printf("[ID: %d, Name: %s, Planet: %s]->",
                    trav->data.artifactID, trav->data.name, trav->data.originPlanet);
                    if (trav == NULL) {
                    }
                     trav = trav->next;
                }
                 printf("NULL\n");

                   
                }
            }



        }
        
    


int totalArtifacts(ArtifactTable *table) {
    int count = 0;

    for(int i = 0; i < TABLE_SIZE; i++) {
        ArtifactNode* trav = table->buckets[i];
        while (trav) {
            count++;
            trav = trav->next;
        }
    }
    return count;
}              // count all artifacts
void clearTable(ArtifactTable *table) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        ArtifactNode* temp = table->buckets[i];
        while (temp) {
            ArtifactNode* current = temp;
            temp = temp->next;
            free(current);
            
            
        }
        table->buckets[i] = NULL;
    }
    
    return;

}


int findMinArtifactID(ArtifactTable *table) {
    
      bool first = true;
    int min = 0;

    for (int i = 0; i < TABLE_SIZE; i++) {
        ArtifactNode* trav = table->buckets[i];
        while (trav) {
            if (first) {
                min = trav->data.artifactID;
                first = false;
            } else if (trav->data.artifactID < min) {
                min = trav->data.artifactID;
            }
            trav = trav->next;
        }
    }

    if (first) {
        printf("Table is empty!\n");
        return -1; // or some sentinel
    }

    return min;
}
int findMinArtifactID(ArtifactTable *table);            // min artifactID
// void updateArtifactOrigin(ArtifactTable *table, int artifactID, const char* newOrigin); // update origin
// void moveArtifactToBucket(ArtifactTable *table, int artifactID, int newBucket); // rehash artifact

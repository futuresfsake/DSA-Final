#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 7
#define MAX_NAME 50
#define EMPTY -1
#define DELETED -2

/*
    Galactic Artifact Repository - Closed Hashing (Linear Probing)
    -------------------------------------------------------------
    Same intergalactic museum stores artifacts, but collisions are handled
    using closed hashing (linear probing). The table must track EMPTY/DELETED slots.
*/

typedef struct Artifact {
    int artifactID;
    char name[MAX_NAME];
    char originPlanet[MAX_NAME];
} Artifact;

typedef struct {
    Artifact table[TABLE_SIZE];
    int flags[TABLE_SIZE]; // EMPTY = -1, DELETED = -2, 0 = occupied
} ClosedArtifactTable;

// ===== Function Prototypes =====
void initClosedTable(ClosedArtifactTable *table);         // initialize table
int hashFunction(int artifactID);                         // modulo hash
bool insertClosed(ClosedArtifactTable *table, Artifact a); // insert iteratively
int searchClosed(ClosedArtifactTable *table, int artifactID); // return index or -1
bool deleteClosed(ClosedArtifactTable *table, int artifactID); // delete iteratively
void displayClosedTable(ClosedArtifactTable *table);      // display table
int totalClosedArtifacts(ClosedArtifactTable *table);     // count artifacts

// ===== MAIN =====
int main() {
    ClosedArtifactTable cTable;
    initClosedTable(&cTable);

    Artifact a1 = {201, "Gamma Sphere", "Gamma-X"};
    Artifact a2 = {202, "Nova Crystal", "Nova-9"};
    Artifact a3 = {203, "Temporal Lens", "Chronos"};
    Artifact a4 = {204, "Dark Matter Cube", "Oblivion"};
    Artifact a5 = {205, "Starlight Compass", "Solaria"};

    insertClosed(&cTable, a1);
    insertClosed(&cTable, a2);
    insertClosed(&cTable, a3);
    insertClosed(&cTable, a4);
    insertClosed(&cTable, a5);

    displayClosedTable(&cTable);

    searchClosed(&cTable, 203);
    deleteClosed(&cTable, 204);

    updateClosedArtifactOrigin(&cTable, 205, "Solaria Prime");

    printf("Total Artifacts: %d\n", totalClosedArtifacts(&cTable));
   
    return 0;
}

void initClosedTable(ClosedArtifactTable *table) {

   
}
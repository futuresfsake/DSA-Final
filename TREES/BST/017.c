#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
    Galactic Artifact Repository (Binary Search Tree)

    Backstory:
    ----------------
    You are the Keeper of the Galactic Artifact Repository. Each artifact
    has a unique ArtifactID and a PowerLevel. The repository organizes
    artifacts according to PowerLevel (BST rules).

    Internally, however, the Archivists used extremely confusing
    terminology for their record containers. They DO NOT use typical
    binary-tree names, making this difficult to trace.
*/

// ================================
// Artifact Record
// ================================
typedef struct ArchiveEntry {
    int artifactID;
    int powerLevel;
    char name[50];
    char origin[30];
} ArchiveEntry;

// ================================
// Encrypted Container (BST Node)
// ================================
typedef struct Chamber {
    ArchiveEntry cargo;
    struct Chamber* portSide;     // LEFT CHILD (non-obvious name)
    struct Chamber* starSide;     // RIGHT CHILD (non-obvious name)
} Chamber;

// ================================
// Function Prototypes
// ================================

// Creates a new Chamber and loads cargo
Chamber* forgeChamber(ArchiveEntry cargo);

// Iterative insertion following BST rules
Chamber* stationInsertIter(Chamber* gate, ArchiveEntry cargo);

// Recursive insertion
Chamber* stationInsertRec(Chamber* gate, ArchiveEntry cargo);

// Search by Artifact ID (traverses arbitrarily)
bool seekByID(Chamber* gate, int id);

// Search by PowerLevel (proper BST search)
Chamber* seekByPower(Chamber* gate, int power);

// Remove an artifact using powerLevel as key
Chamber* purgeEntry(Chamber* gate, int id);

// Retrieve smallest powerLevel container
Chamber* traceMin(Chamber* gate);

// Retrieve largest powerLevel container
Chamber* traceMax(Chamber* gate);

// Ascending order traversal
void driftAscending(Chamber* gate);


// Count number of loaded Chambers
int tallyUnits(Chamber* gate);

// Height of artifact structure
int towerHeight(Chamber* gate);

// Free all chambers
void disbandArchive(Chamber* gate);

// ================================
// MAIN
// ================================

int main() {
    Chamber* hangar = NULL;

    // Sample artifacts
    ArchiveEntry a1 = {101, 50, "Crystal of Eternity", "Mars"};
    ArchiveEntry a2 = {102, 30, "Orb of Shadows", "Venus"};
    ArchiveEntry a3 = {103, 70, "Blade of Light", "Jupiter"};
    ArchiveEntry a4 = {104, 55, "Staff of Winds", "Saturn"};
    ArchiveEntry a5 = {105, 20, "Amulet of Silence", "Mercury"};
    ArchiveEntry a6 = {106, 65, "Ring of Fire", "Neptune"};
    ArchiveEntry a7 = {107, 45, "Helmet of Insight", "Uranus"};

    printf("=== Inserting Artifacts Recursively ===\n");
    hangar = stationInsertRec(hangar, a1);
    hangar = stationInsertRec(hangar, a2);
    hangar = stationInsertRec(hangar, a3);
    hangar = stationInsertRec(hangar, a4);
    hangar = stationInsertRec(hangar, a5);
    hangar = stationInsertRec(hangar, a6);
    hangar = stationInsertRec(hangar, a7);

    printf("\n=== Inorder Traversal (Ascending PowerLevel) ===\n");
    driftAscending(hangar);

    printf("\n\n=== Searching for Artifact ID 104 ===\n");
    printf("Found: %s\n", seekByID(hangar, 104) ? "Yes" : "No");

    printf("\n=== Searching for Artifact ID 999 (Not in tree) ===\n");
    printf("Found: %s\n", seekByID(hangar, 999) ? "Yes" : "No");

    printf("\n=== Trace Minimum & Maximum ===\n");
    Chamber* minCh = traceMin(hangar);
    Chamber* maxCh = traceMax(hangar);
    if(minCh) printf("Minimum ArtifactID: %d, PowerLevel: %d\n", minCh->cargo.artifactID, minCh->cargo.powerLevel);
    if(maxCh) printf("Maximum ArtifactID: %d, PowerLevel: %d\n", maxCh->cargo.artifactID, maxCh->cargo.powerLevel);

    printf("\n=== Deleting Artifact ID 103 ===\n");
    hangar = purgeEntry(hangar, 103);
    driftAscending(hangar);

    printf("\n\n=== Deleting Artifact ID 101 (Root) ===\n");
    hangar = purgeEntry(hangar, 101);
    driftAscending(hangar);

    printf("\n\n=== Inserting Artifact ID 108 Iteratively ===\n");
    ArchiveEntry a8 = {108, 60, "Shield of Dawn", "Pluto"};
    hangar = stationInsertIter(hangar, a8);
    driftAscending(hangar);

    printf("\n=== Deleting Artifact ID 999 (Non-existent) ===\n");
    hangar = purgeEntry(hangar, 999); // should do nothing
    driftAscending(hangar);

    // Clean up all remaining nodes
    hangar = purgeEntry(hangar, 102);
    hangar = purgeEntry(hangar, 104);
    hangar = purgeEntry(hangar, 105);
    hangar = purgeEntry(hangar, 106);
    hangar = purgeEntry(hangar, 107);
    hangar = purgeEntry(hangar, 108);

    printf("\nAll artifacts removed. Inorder Traversal:\n");
    driftAscending(hangar); // should show nothing

    return 0;
}

// ================================
// EMPTY FUNCTION DEFINITIONS
// (NO LOGIC INSIDE — ONLY SIGNATURES)
// ================================

Chamber* forgeChamber(ArchiveEntry cargo) {

    Chamber* new = malloc(sizeof(Chamber));
    if (!new) return NULL;

    new->cargo = cargo;
    new->portSide = NULL;
    new->starSide = NULL;

    return new;
    

}

Chamber* stationInsertIter(Chamber* gate, ArchiveEntry cargo) {

    Chamber** trav = &gate;

    for(;*trav != NULL && (*trav)->cargo.artifactID != cargo.artifactID;) {
        trav = ((*trav)->cargo.powerLevel < cargo.powerLevel) ? &(*trav)->starSide : &(*trav)->portSide;
    }

    if (*trav == NULL) {
        Chamber* new = forgeChamber(cargo);
        *trav = new;

    }

    return gate;
}

Chamber* stationInsertRec(Chamber* gate, ArchiveEntry cargo) {


    
    if (gate == NULL) {
       return forgeChamber(cargo);
     
    }
    

    if (gate->cargo.artifactID == cargo.artifactID) return gate;


    if (gate->cargo.powerLevel < cargo.powerLevel) {
        gate->starSide = stationInsertRec(gate->starSide, cargo);
    } else {
       gate->portSide =  stationInsertRec(gate->portSide, cargo);
    }

    return gate;

}

bool seekByID(Chamber* gate, int id) {

    if (gate == NULL) return false;

    if (gate->cargo.artifactID == id) return true;


    return seekByID (gate->starSide, id) || seekByID(gate->portSide, id);

}

Chamber* seekByPower(Chamber* gate, int power) {

    if (gate == NULL) return NULL;

    if (gate->cargo.powerLevel == power) return gate;


    gate = seekByPower(gate->portSide, power);
    gate = seekByPower(gate->starSide, power);



}

Chamber* purgeEntry(Chamber* gate, int id) {

    if (gate == NULL) return NULL;

    gate->portSide = purgeEntry(gate->portSide, id);
    gate->starSide = purgeEntry(gate->starSide, id);


    if (gate->cargo.artifactID == id) {

        Chamber* temp = gate;

        if (gate->portSide == NULL && gate->starSide == NULL) {
            free(temp);
            return  NULL;
        }

        else if (gate->portSide == NULL) {
            gate = gate->starSide;
            free(temp);
            
            
        }
         else if (gate->starSide == NULL) {
            gate = gate->portSide;
            free(temp);
            
            
        } else {
            Chamber* succ = gate->starSide;
            while (succ->portSide) {
                succ = succ->portSide;
            }

            gate->cargo = succ->cargo;
            gate->starSide = purgeEntry(gate->starSide, succ->cargo.artifactID);
        }

        
    }

    
    return gate;


}

Chamber* traceMin(Chamber* gate) {
    
    if (gate == NULL) return NULL;

    while (gate->portSide != NULL ) {
        gate = gate->portSide;
    }

    return gate;



}

Chamber* traceMax(Chamber* gate) {

    if (gate == NULL) return NULL;

    while (gate->starSide) {
        gate = gate->starSide;
    }

    return gate;



}

void driftAscending(Chamber* gate) {
    if (gate == NULL) return;

    // Traverse left subtree
    driftAscending(gate->portSide);

    // Visit current node
    printf("ArtifactID: %d | PowerLevel: %d | Name: %s | Origin: %s\n",
           gate->cargo.artifactID,
           gate->cargo.powerLevel,
           gate->cargo.name,
           gate->cargo.origin);

    // Traverse right subtree
    driftAscending(gate->starSide);
}


int tallyUnits(Chamber* gate) {
    if (gate == NULL) return 0;

    int count = tallyUnits(gate->portSide);
    int count2 = tallyUnits(gate->starSide);

    return count+count2 +1;

}

int towerHeight(Chamber* gate) {

    int h;
    int h2;

    if (gate==NULL) return -1;

    h = towerHeight(gate->portSide);
    h2 = towerHeight(gate->starSide);

    return (h < h2 ? h2 : h) + 1;

}

void disbandArchive(Chamber* gate) {

    if (gate == NULL) return;

    disbandArchive(gate->portSide);
    disbandArchive(gate->starSide);
    free(gate);
}

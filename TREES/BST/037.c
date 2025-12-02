#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
    ==========================================================
       Interstellar Crew Hierarchy BST (STRING KEY VERSION)
    ----------------------------------------------------------
    The NAME is now the BST key, ordering members
    lexicographically using strcmp().

    Features:
    - Insert crew by name (dynamic allocation)
    - Search rank by name
    - Promote members based on rank
    - Delete node (0,1,2 children)
    - Display in alphabetical order
    ==========================================================
*/

typedef struct {
    char *name;        // BST key (dynamic string)
    int crewID;        // Not a key, just stored info
    int rankLevel;
} CrewInfo;

typedef struct CrewNode {
    CrewInfo data;
    struct CrewNode *left;       // name < current
    struct CrewNode *right;      // name > current
} CrewNode;

typedef struct {
    CrewNode *root;
} CrewTree;

// ===================== PROTOTYPES =====================
void initCrewTree(CrewTree *tree);

bool addCrewMember(CrewTree *tree, char *name, int id, int rank);

int getCrewRank(CrewTree *tree, char *name);

void promoteCrew(CrewNode *current, int threshold, int boost);

void removeCrewMember(CrewTree *tree, char *name);

void displayCrew(CrewNode *current);

void freeCrew(CrewNode* tree) {
    if (tree == NULL) return;

    freeCrew(tree->left);
    free(tree->data.name);
    free(tree->right);
    free(tree);
}

// ===================== MAIN TESTER =====================
int main() {
    CrewTree fleet;
    initCrewTree(&fleet);

    printf("=== Adding Crew Members (STRING KEY) ===\n");

    addCrewMember(&fleet, "Captain Nova",      301, 90);
    addCrewMember(&fleet, "Lieutenant Vega",   299, 55);
    addCrewMember(&fleet, "Engineer Orion",    305, 40);
     addCrewMember(&fleet, "Engineer Orion",    305, 40);
    addCrewMember(&fleet, "Navigator Lyra",    303, 25);
    addCrewMember(&fleet, "Medic Sol",         307, 10);

    printf("\n=== Crew Hierarchy (Alphabetical) ===\n");
    displayCrew(fleet.root);

    printf("\n=== Promote Crew with Rank < 30 by +50 ===\n");
    promoteCrew(fleet.root, 30, 50);
    displayCrew(fleet.root);

    printf("\n=== Removing Crew Member: \"Engineer Orion\" ===\n");
    removeCrewMember(&fleet, "Engineer Orion");
    displayCrew(fleet.root);

    freeCrew(fleet.root);
    printf("Successfully freed.\n");

    return 0;
}


void initCrewTree(CrewTree *tree) {
    tree->root = NULL;
}

bool addCrewMember(CrewTree *tree, char *name, int id, int rank) {

    CrewNode** trav = &(tree->root);

    for(;*trav != NULL && (strcmp((*trav)->data.name, name) != 0);) {
        trav = (strcmp((*trav)->data.name, name) < 0) ? &(*trav)->right : &(*trav)->left;
    }
    if (*trav != NULL) {
        printf("%s is a duplicate! Ignoring\n", name);
        return false;
    }

    if (*trav == NULL) {
        CrewNode* new = malloc(sizeof(CrewNode));
        if (new == NULL) return false;

        new->data.name = malloc(strlen(name)+1);
        strcpy(new->data.name, name);
        new->data.crewID = id;
        new->data.rankLevel = rank;

        new->left = NULL;
        new->right = NULL;

        *trav = new;
        printf("=> Adding crew \"%s\" \n", new->data.name);
        return true;
    }
    
}

int getCrewRank(CrewTree *tree, char *name) {

    CrewNode* trav = tree->root;
    for(; trav != NULL;) {
        if (strcmp(trav->data.name, name) == 0) {
            return trav->data.rankLevel;
        }
        trav = (strcmp(trav->data.name, name) <0) ? (trav)->right : (trav)->left;
    }
    
    return -1;
}

void promoteCrew(CrewNode *current, int threshold, int boost) {

    if (current == NULL) return;

    promoteCrew(current->left, threshold, boost);
    if (current->data.rankLevel < threshold) {
        current->data.rankLevel+= boost;
    }
    promoteCrew(current->right, threshold, boost);
}


void removeCrewMember(CrewTree *tree, char *name) {

    CrewNode** trav = &(tree->root);
    for(;*trav != NULL && strcmp((*trav)->data.name, name) != 0; ) {
        trav = (strcmp((*trav)->data.name, name) < 0) ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
        printf(" \"%s\" is not found\n", name);
        return;
    }

    CrewNode* temp = *trav;

    if ((*trav)->left == NULL && (*trav)->right == NULL) {
        free(temp);
        *trav = NULL;
    } else if ((*trav)->left == NULL) {
        *trav = (*trav)->right;
        free(temp);
    } else if ((*trav)->right == NULL) {
        *trav = (*trav)->left;
        free(temp);
    } else {
        CrewNode** succ = &(*trav)->right;
        while ((*succ)->left) {
            succ = &(*succ)->left;
        }

        free((*trav)->data.name);        
        (*trav)->data = (*succ)->data;

        CrewNode* target = *succ;
        *succ = target->right;
        free(target);
        
    }

    printf(" \"%s\" is successfully deleted!\n", name);
    return;
}

void displayCrew(CrewNode *current) {

    if (current == NULL) return;

    displayCrew(current->left);
    printf("Name: %s (ID: %d, Rank: %d)\n", current->data.name, current->data.crewID, current->data.rankLevel);
    displayCrew(current->right);
}



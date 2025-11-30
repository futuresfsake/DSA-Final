#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME 50

/*
    ==========================================================
       Aurora-17 Cryo Biometric Tree (BST Implementation)
    ----------------------------------------------------------
    The Cryo-Grid is organized as a BST for faster lookups.

    CORE RULES:
    1. Left Child ID < Parent ID
    2. Right Child ID > Parent ID
    3. No Duplicate IDs allowed.
    ==========================================================
*/

// ===================== STRUCT DEFINITIONS =====================
typedef struct {
    int podID;                  // The BST Key
    char occupantName[MAX_NAME]; // Data
    int stasisLevel;             // Stasis Level
} Info;

typedef struct CryoNode {
    Info info;
    struct CryoNode *left;       // Lower ID sector
    struct CryoNode *right;      // Higher ID sector
} CryoNode;

typedef struct {
    CryoNode *root;              // Entry point
} CryoGrid;

// ======================== PROTOTYPES =========================

// Initialize root to NULL
void initGrid(CryoGrid *cg)  {
    cg->root = NULL;

}

// Create a new node and insert into BST
// Returns true if inserted, false if ID already exists
bool dockPod(CryoGrid *cg, int id, char *name, int stasis) {

    CryoNode** trav = &(cg->root);
    for(;*trav != NULL && (*trav)->info.podID != id;) {
        trav = (*trav)->info.podID < id ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
        CryoNode* new = malloc(sizeof(CryoNode));
        if (!new) return false;

        strcpy(new->info.occupantName, name);
        new->info.stasisLevel = stasis;
        new->info.podID = id;


        new->left = NULL;
        new->right = NULL;


        *trav =new;
    }
    return true;
}

// Search for a pod by ID
// Returns stasis level if found, -1 if not
int locatePodStatus(CryoGrid *cg, int id) {

   CryoNode* trav = cg->root;
   while (trav) {
    if (trav->info.podID == id) {
        return trav->info.stasisLevel;
    }

    trav = trav->info.podID < id ? trav->right : trav->left;
   }
   return -1;
}

// Traverse all nodes and boost stasis if below threshold
void boostLifeSupport(CryoNode *current, int threshold, int boostAmount) {


    if (current == NULL) return;
    boostLifeSupport(current->left, threshold, boostAmount);
   
        if (current->info.stasisLevel < threshold) {
            current->info.stasisLevel += boostAmount;
        
    }
     boostLifeSupport(current->right, threshold, boostAmount);
   


}

// Remove a pod from the BST by ID
void ejectPod(CryoGrid *cg, int id) {

    CryoNode** trav = &(cg->root);
    for(; *trav != NULL && (*trav)->info.podID != id;) {
        trav = (*trav)->info.podID < id ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) return;

    CryoNode* temp = *trav;
    if ((*trav)->left == NULL && (*trav)->right == NULL) {
        free(temp);
        *trav = NULL;
    } else if ((*trav)->left == NULL) {
        *trav = (*trav)->right;
        free(temp);
    }
    else if ((*trav)->right == NULL) {
        *trav = (*trav)->left;
        free(temp);
    } else {
        CryoNode** succ = &(*trav)->right;
        while ((*succ)->left) {
            succ = &(*succ)->left;
        }

        (*trav)->info = (*succ)->info;


        
        // Delete successor node (it has at most one child)
        CryoNode* target = *succ;
        *succ = (*succ)->right;  // successor can only have right child
        free(target);



        
        

    }
 }

// Print pods in ascending order (in-order traversal)
void inventoryReport(CryoNode *current) {
    if (current == NULL) return;

    // Visit left subtree
    inventoryReport(current->left);

    // Print current node
    printf("[%d] %s: %d\n", current->info.podID,
                             current->info.occupantName,
                             current->info.stasisLevel);

    // Visit right subtree
    inventoryReport(current->right);
}

// Helper functions
CryoNode* createNode(int id, char *name, int stasis);
CryoNode* ejectNodeRecursive(CryoNode *node, int id);
CryoNode* findMinNode(CryoNode *node);

// ======================== MAIN TESTER =========================
int main() {
    CryoGrid aurora;
    initGrid(&aurora);

    printf("=== Initializing Biometric Grid ===\n");
    dockPod(&aurora, 102, "Kael", 40);
    dockPod(&aurora, 101, "Astra", 55);
    dockPod(&aurora, 104, "Dorian", 20);
    dockPod(&aurora, 103, "Serin", 75);
    dockPod(&aurora, 105, "Eos", 10);

    printf("\n=== Full Inventory (In-Order) ===\n");
    inventoryReport(aurora.root);

    printf("\n\n=== Locate Pod 103 ===\n");
    int status = locatePodStatus(&aurora, 103);
    if (status != -1) printf("Pod 103 Found. Stasis: %d\n", status);
    else printf("Pod 103 Not Found.\n");

    printf("\n=== Boost Critical Systems (<30) +50 ===\n");
    boostLifeSupport(aurora.root, 30, 50);
    inventoryReport(aurora.root);

    printf("\n\n=== EJECTING Pod 104 ===\n");
    ejectPod(&aurora, 104);
    printf("=== Final Inventory ===\n");
    inventoryReport(aurora.root);

    return 0;
}

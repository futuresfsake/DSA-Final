#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NAME_LEN 40

/*
    =====================================================================
       NANOBOT DIAGNOSTIC TREE (BST ARCHITECTURE)
    ---------------------------------------------------------------------
    Bots organized by botID using Binary Search Tree rules.

    RULES:
    1. sub_link  -> LOWER IDs
    2. super_link -> HIGHER IDs
    3. No duplicates
    =====================================================================
*/

typedef struct {
    int botID;
    char model[NAME_LEN];
    int severity;               // 1–10
} Info;

typedef struct BotUnit {
    Info info;

    struct BotUnit* sub_link;    // Left
    struct BotUnit* super_link;  // Right
} BotUnit;

typedef struct {
    BotUnit* mainframe;          // Root
} LabNetwork;


// ======================== PROTOTYPES ========================

// * Set root = NULL
void init_lab(LabNetwork* net);

// * Insert into BST
bool register_bot(LabNetwork* net, int id, char* model, int sev);

// * Standard BST search
BotUnit* scan_database(LabNetwork* net, int id);

// * In-order traversal, print severity >= min
void filter_critical_units(BotUnit* current, int min_severity);

// * Print path taken to search for a bot
void trace_signal_path(LabNetwork* net, int targetID);

// * Full BST deletion (3 cases)
void decommission_bot(LabNetwork* net, int id);


BotUnit* scan_database(LabNetwork* net, int id);
void display_all_bots(BotUnit* current) {
    if (current == NULL) return;

    display_all_bots(current->sub_link);

    printf("Bot ID: %d | Model: %s | Severity: %d\n",
           current->info.botID,
           current->info.model,
           current->info.severity);

    display_all_bots(current->super_link);
}


// ================= MAIN TESTER =====================
int main() {
    LabNetwork lab;
    init_lab(&lab);

    printf("=== SYSTEM ONLINE: INTAKE SEQUENCE ===\n");
    register_bot(&lab, 1003, "RX-Gamma", 6);
    register_bot(&lab, 1001, "RX-Alpha", 3);
    register_bot(&lab, 1005, "RX-Omega", 2);
    register_bot(&lab, 1004, "RX-Delta", 8);
    register_bot(&lab, 1002, "RX-Beta", 9);

    /*
           TREE SHAPE:

               1003
              /    \
          1001      1005
             \      /
            1002  1004
    */

    printf("\n=== FULL LAB NETWORK LISTING ===\n");
    display_all_bots(lab.mainframe);


        int searchID = 1004;
    BotUnit* found = scan_database(&lab, searchID);

    if (found != NULL) {
        printf("Bot Found:\n");
        printf("  ID: %d\n", found->info.botID);
        printf("  Model: %s\n", found->info.model);
        printf("  Severity: %d\n", found->info.severity);
    } else {
        printf("Bot with ID %d not found.\n", searchID);
    }

    printf("\n=== FILTER: CRITICAL MALFUNCTIONS (Severity >= 5) ===\n");
    filter_critical_units(lab.mainframe, 5);

    
    printf("\n=== DECOMMISSIONING BOT 1003 (ROOT DELETION) ===\n");
    decommission_bot(&lab, 1003);

    printf("\n=== FULL LAB NETWORK LISTING (after deleting 1003) ===\n");
    display_all_bots(lab.mainframe);


    printf("=== VERIFYING RESTRUCTURE ===\n");
    if (lab.mainframe != NULL && lab.mainframe->info.botID != 1003) {
        printf("New Mainframe Root ID: %d\n", lab.mainframe->info.botID);
    } else {
        printf("ERROR: 1003 still detected.\n");
    }

    return 0;
}


// * Set root = NULL
void init_lab(LabNetwork* net) {
    net->mainframe = NULL;
}

// * Insert into BST
bool register_bot(LabNetwork* net, int id, char* model, int sev) {

    BotUnit** trav = &(net->mainframe);

    for(;*trav != NULL && (*trav)->info.botID != id;) {
        trav = (*trav)->info.botID < id ? &(*trav)->super_link : &(*trav)->sub_link;
    }

    if (*trav == NULL) {

        Info f;
        f.botID = id;
        strcpy(f.model, model);
        f.severity = sev;

        BotUnit* new = malloc(sizeof(BotUnit));
        // new->info.botID = id;
        // new->info.severity = sev;
        // strcpy(new->info.model, model);
       
        new->info = f;
       

        new->sub_link = NULL;
        new->super_link = NULL;

        *trav = new;

        return true;
        
        
    }

    return false;
}

// * Standard BST search
BotUnit* scan_database(LabNetwork* net, int id) {

    BotUnit* trav = net->mainframe;
    for(; trav != NULL;) {
        if (trav->info.botID == id) {
            return trav;
        }
        trav = (trav)->info.botID < id ? trav->super_link : trav->sub_link;
    }

    return NULL;
}

// * In-order traversal, print severity >= min
void filter_critical_units(BotUnit* current, int min_severity) {
    
   
    if (current == NULL)return;
    
    filter_critical_units(current->sub_link, min_severity);
    if (current->info.severity >= min_severity) {
          printf("  ID: %d\n", current->info.botID);
            printf("  Model: %s\n", current->info.model);
            printf("  Severity: %d\n", current->info.severity);
            printf("\n");
            
    }
    filter_critical_units(current->super_link, min_severity);

}



// * Full BST deletion (3 cases)
void decommission_bot(LabNetwork* net, int id) {

    BotUnit** trav = &(net->mainframe);

    for(;*trav != NULL && (*trav)->info.botID != id;) {
        trav = (*trav)->info.botID < id ? &(*trav)->super_link : &(*trav)->sub_link;
    }

    

    if (*trav == NULL) return;

    BotUnit* temp = *trav;

    // printf("reacher");

   if ((*trav)->sub_link == NULL && (*trav)->super_link == NULL) {
    free(temp);
    *trav = NULL;

        
   } else if ((*trav)->sub_link == NULL) {
        *trav = (*trav)->super_link;
        free(temp);

   } else if ((*trav)->super_link == NULL) {
    *trav = (*trav)->sub_link;
    free(temp);
   } 
   else {
    BotUnit** succ = &(*trav)->super_link;
    while ((*succ)->sub_link) {
        succ = &(*succ)->sub_link;
    }

    (*trav)->info = (*succ)->info;

    BotUnit* target = *succ;
    *succ = (*succ)->super_link;
    free(target);
   }
}
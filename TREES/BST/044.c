#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================== NESTED STRUCT DEFINITIONS ====================

// 1. The Cargo Data (The "Package")
typedef struct {
    char trackingCode[20];  // <--- BASIS OF ORDERING (String)
    float weightKg;
    int priorityLevel;
} Cargo;

// 2. The Infrastructure (The "Checkpoint")
// NOTE: Do not use "Node", "Left", or "Right" in your mental logic.
// Think: "Checkpoint", "Belt A" (Smaller), "Belt B" (Larger).
typedef struct checkpoint {
    Cargo container;                 // The package currently held here
    struct checkpoint *beltA;        // Path for "Smaller" codes
    struct checkpoint *beltB;        // Path for "Larger" codes
} Checkpoint;



typedef struct {
    Checkpoint* stack[100];
    int top;
}Stack;

void push(Stack*s, Checkpoint* node) {
     s->stack[++s->top] = node; 

}
Checkpoint* pop(Stack* s) {
    return s->stack[s->top--];
}
/* --- Core Logistics Operations --- */
// Create a new checkpoint holding a package
Checkpoint* openCheckpoint(Cargo item) {

    Checkpoint* new = malloc(sizeof(Checkpoint));
    new->container = item;
    new->beltA = NULL;
    new->beltB = NULL;
    return new;
}

// The "Sortation Diverter" Logic
// If code < current, send to Belt A. If code > current, send to Belt B.
Checkpoint* processIncomingPackage(Checkpoint* mainEntry, Cargo item) {

    
    Checkpoint** trav = &mainEntry;

    for(; *trav != NULL && strcmp((*trav)->container.trackingCode, item.trackingCode) !=0;) {
        trav = strcmp((*trav)->container.trackingCode, item.trackingCode) < 0 ? &(*trav)->beltB : &(*trav)->beltA;
    }

    if (*trav == NULL) {

        Checkpoint* new = openCheckpoint(item);
        *trav = new;
    }

return mainEntry;

}

// Find a package to check its status
Checkpoint* locateCargo(Checkpoint* mainEntry, char* codeToFind) {

    if (mainEntry == NULL) return NULL;

    if (strcmp(mainEntry->container.trackingCode, codeToFind) == 0) {
        return mainEntry;
    }


    Checkpoint* find = locateCargo(mainEntry->beltA, codeToFind);
    if (find != NULL) return find;

       Checkpoint* find2 = locateCargo(mainEntry->beltB, codeToFind);
    if (find2 != NULL) return find2;


    return NULL;

}

/* --- Reports (Traversals) --- */
// Print the manifest in alphabetical order (A-Z)
void generateManifest(Checkpoint* mainEntry) {

    Stack s;
    s.top = -1;

    Checkpoint* trav = mainEntry;

    while (trav || s.top != -1) {
        while (trav) {
            push(&s, trav);
            trav = trav->beltA;
        }
        trav = pop(&s);
        printf("PrioLevel: %d || TrackCode: %s  \n", trav->container.priorityLevel, trav->container.trackingCode);
        trav = trav->beltB;
    }

}



// Process packages starting from the entry point, then layer by layer down the conveyors
// (Useful for inspecting the facility tier-by-tier)
void inspectionByTiers(Checkpoint* mainEntry) {
Stack s;
    s.top = -1;

    Checkpoint* trav = mainEntry;

    while (trav || s.top != -1) {
        while (trav) {
            push(&s, trav);
            trav = trav->beltA;
        }
        trav = pop(&s);
        printf("PrioLevel: %d || TrackCode: %s  \n", trav->container.priorityLevel, trav->container.trackingCode);
        trav = trav->beltB;
    }

}

/* --- Analytics (The 5 Additional Ops) --- */
// 1. Find the package with the alphabetically first code (The "A-most" package)
Cargo getFirstInLine(Checkpoint* mainEntry) {

  
    while (mainEntry->beltA) {
        mainEntry = mainEntry->beltA;
    }

    return mainEntry->container;
}

// 2. Find the package with the alphabetically last code (The "Z-most" package)
Cargo getLastInLine(Checkpoint* mainEntry) {

    while (mainEntry->beltB) {
        mainEntry = mainEntry->beltB;
    }

    return mainEntry->container;
}

// 3. Calculate how deep the conveyor system goes (How many steps from Entry to furthest point)
int getMaxConveyorDepth(Checkpoint* mainEntry) {

    if (mainEntry == NULL) return 0;

    int c = getMaxConveyorDepth(mainEntry->beltA);
    int c2 = getMaxConveyorDepth(mainEntry->beltB);


    return (c < c2 ? c2 : c)+1;

}

// 4. Count how many packages are "stuck" at the end of the line (No belts leading out)
int countDeadEnds(Checkpoint* mainEntry) {

    if (mainEntry == NULL) return 0;

    
    if (mainEntry->beltA == NULL && mainEntry->beltB == NULL) {
        return 1;
    }

    int c = countDeadEnds(mainEntry->beltA);
    int c2 = countDeadEnds(mainEntry->beltB);


    return c+c2;
}

// 5. Calculate total weight of all cargo in the facility
float calculateTotalWeight(Checkpoint* mainEntry) {

    if (mainEntry == NULL) return 0;

    float left = calculateTotalWeight(mainEntry->beltA);
    float right = calculateTotalWeight(mainEntry->beltB);

    return left+right+mainEntry->container.weightKg;
}

// Shutdown: Clear all checkpoints and free memory
void emergencyShutdown(Checkpoint* mainEntry) {
   
    if (mainEntry == NULL) return;

    emergencyShutdown(mainEntry->beltA);
    emergencyShutdown(mainEntry->beltB);
    free(mainEntry);
}



// Pre-order traversal (Root -> BeltA -> BeltB)
void traversePreOrder(Checkpoint* mainEntry) {

    Stack s;
    s.top = -1;
    push(&s, mainEntry);

    while (s.top != -1) {
        Checkpoint* trav = pop(&s);
        printf("PrioLevel: %d || TrackCode: %s  \n", trav->container.priorityLevel, trav->container.trackingCode);

       
        if (trav->beltB) push(&s, trav->beltB);
         if (trav->beltA) push(&s, trav->beltA);

    }

}



// Post-order traversal (BeltA -> BeltB -> Root)
void traversePostOrder(Checkpoint* mainEntry) {

    Stack s1,s2;
    s1.top = -1;
    s2.top = -1;

    push(&s1, mainEntry);
    while (s1.top != -1) {
        Checkpoint* trav = pop(&s1);
        push(&s2, trav);
     if (trav->beltA) push(&s1, trav->beltA);


       if (trav->beltB) push(&s1, trav->beltB);

    }

    while (s2.top != -1) {
       Checkpoint* trav = pop(&s2);
    printf("PrioLevel: %d || TrackCode: %s  \n", trav->container.priorityLevel, trav->container.trackingCode);


    }
}

// Breadth-first / Level-order traversal
void traverseBFS(Checkpoint* mainEntry) {

    Checkpoint* queue[100];
    int front = 0;
    int rear = 0;

    queue[rear++] = mainEntry;
    
    while (front < rear) {

        Checkpoint* trav = queue[front++];
            printf("PrioLevel: %d || TrackCode: %s  \n", trav->container.priorityLevel, trav->container.trackingCode);


        if (trav->beltA) queue[rear++] = trav->beltA;
        if (trav->beltB) queue[rear++] = trav->beltB;

    }
}
int main() {
    Checkpoint *mainEntry = NULL;

    // Simulation Data
    Cargo c1 = {"PKG-MEM-005", 10.5, 1};
    Cargo c2 = {"PKG-APP-102", 5.2, 2};
    Cargo c3 = {"PKG-ZOO-999", 20.0, 5};
    Cargo c4 = {"PKG-LION-01", 15.0, 3};

    printf("=== SYSTEM ONLINE: PROCESSING INCOMING CARGO ===\n");

    // Insert packages into the facility
    mainEntry = processIncomingPackage(mainEntry, c1);
    mainEntry = processIncomingPackage(mainEntry, c2);
    mainEntry = processIncomingPackage(mainEntry, c3);
    mainEntry = processIncomingPackage(mainEntry, c4);

    // 1. Test Search
    printf("\n[SEARCH] Looking for PKG-APP-102...\n");
    Checkpoint* result = locateCargo(mainEntry, "PKG-APP-102");
    if (result) {
        printf(" >> FOUND: Priority %d, Weight %.2fkg\n",
               result->container.priorityLevel, result->container.weightKg);
    } else {
        printf(" >> ERROR: Cargo not found.\n");
    }

    // 2. Test Manifest (In-order)
    printf("\n[REPORT] Full Manifest (Alphabetical Order):\n");
    generateManifest(mainEntry);

    // 3. Test Inspection by tiers
    printf("\n[INSPECTION] Facility Inspection By Tiers:\n");
    inspectionByTiers(mainEntry);

    // 4. Test Pre-order traversal
    printf("\n[TRAVERSAL] Pre-order Traversal:\n");
    traversePreOrder(mainEntry);

    // 5. Test Post-order traversal
    printf("\n[TRAVERSAL] Post-order Traversal:\n");
    traversePostOrder(mainEntry);

    // 6. Test BFS / Level-order traversal
    printf("\n[TRAVERSAL] Breadth-First / Level-order Traversal:\n");
    traverseBFS(mainEntry);

    // 7. Test Analytics
    printf("\n[ANALYTICS] Facility Analytics:\n");

    Cargo firstCargo = getFirstInLine(mainEntry);
    printf(" - Alphabetically first package: %s\n", firstCargo.trackingCode);

    Cargo lastCargo = getLastInLine(mainEntry);
    printf(" - Alphabetically last package: %s\n", lastCargo.trackingCode);

    int maxDepth = getMaxConveyorDepth(mainEntry);
    printf(" - Max conveyor depth: %d\n", maxDepth);

    int deadEnds = countDeadEnds(mainEntry);
    printf(" - Number of dead-end packages: %d\n", deadEnds);

    float totalWeight = calculateTotalWeight(mainEntry);
    printf(" - Total weight of all packages: %.2f kg\n", totalWeight);

    // 8. Shutdown facility (free memory)
    printf("\n[SYSTEM] Initiating Emergency Shutdown...\n");
    emergencyShutdown(mainEntry);

    return 0;
}

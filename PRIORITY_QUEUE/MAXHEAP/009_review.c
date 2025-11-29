//** when increase value, sift up, when decrease, sift down, then call rebuildmaxheap to restore its property */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
    int serialTag;
    char *designation;    
    float batteryLevel;
    int urgencyScore;
    char *sectorCode;
} DroneUnit;

typedef struct {
    DroneUnit *stor;   // dynamic heap array
    int biggest;       // last used index (starts at -1)
    int slotCap;       // max capacity
} DroneHeap;


void initHangar(DroneHeap *dh, int capacity);
void freeHangar(DroneHeap *dh);

bool addDrone(DroneHeap *dh, DroneUnit d);
bool extractTopDrone(DroneHeap *dh, DroneUnit *removed);

void siftUp(DroneHeap *dh);
void siftDown(DroneHeap *dh);

bool amplifyUrgency(DroneHeap *dh, int serialTag, int newUrgency);
bool dampenUrgency(DroneHeap *dh, int serialTag, int newUrgency);

void rebuildMaxHeap(DroneHeap *dh) {
    
    if (dh->biggest == -1) return;
    int pr = (dh->biggest-1)/2;
    

    while (pr >= 0) {
        int down = pr;
        int child = 2 * down+1;

        while (child <= dh->biggest) {
            if (child+1 <= dh->biggest && dh->stor[child+1].urgencyScore> dh->stor[child].urgencyScore) {
                child++;
            }

            if (dh->stor[down].urgencyScore < dh->stor[child].urgencyScore) {
                DroneUnit swap = dh->stor[down];
                dh->stor[down] = dh->stor[child];
                dh->stor[child] = swap;

                down = child;
                child = 2 * down+1;
            } else {
                break;
            }
        }
        pr--;
    }
}             


void initHangar(DroneHeap *dh, int capacity) {
    dh->stor = malloc(sizeof(DroneUnit) * capacity);
    dh->biggest = -1;
    dh->slotCap = capacity;

}
void freeHangar(DroneHeap *dh) {
    
    for(int i = 0; i <= dh->biggest; i++) {
        free(dh->stor[i].designation);
        free(dh->stor[i].sectorCode);
    }
    free(dh->stor);
    dh->biggest = -1;
    dh->slotCap = -1;
}

bool addDrone(DroneHeap *dh, DroneUnit d) {
    
    int child, pr;
    if (dh->biggest == dh->slotCap-1) return false;

    dh->biggest++;
    child = dh->biggest;
    dh->stor[child] = d;
    siftUp(dh);
    return true;
}

bool extractTopDrone(DroneHeap *dh, DroneUnit *removed) {

    if (dh->biggest == -1) return false;

    *removed = dh->stor[0];
    dh->stor[0] = dh->stor[dh->biggest];
    dh->biggest--;

    siftDown(dh);
    return true;

}

void siftUp(DroneHeap *dh) {
    int child, pr;

    

    child = dh->biggest;
    pr = (child-1)/2;

    while (child >0 && dh->stor[pr].urgencyScore < dh->stor[child].urgencyScore) {
        DroneUnit swap = dh->stor[pr];
        dh->stor[pr] = dh->stor[child];
        dh->stor[child] = swap;

        child = pr;
        pr = (child-1)/2;
    }
}
void siftDown(DroneHeap *dh) {
    int child, pr;


    pr = 0;
    child = 2 * pr +1;

    while (child <= dh->biggest) {
        if (child+1 <= dh->biggest && dh->stor[child+1].urgencyScore> dh->stor[child].urgencyScore) {
            child++;
        }

        if (dh->stor[pr].urgencyScore < dh->stor[child].urgencyScore) {
            DroneUnit swap = dh->stor[pr];
            dh->stor[pr] = dh->stor[child];
            dh->stor[child] = swap;

            pr = child;
            child = (pr * 2)+1;
        } else {
            break;
        }
    }
}

bool amplifyUrgency(DroneHeap *dh, int serialTag, int newUrgency){
    bool found = false;
    for(int i = 0; i <= dh->biggest; i++) {
        if (dh->stor[i].serialTag == serialTag) {
            dh->stor[i].urgencyScore = newUrgency;
            found = true;
            
        }
    }

    rebuildMaxHeap(dh);

    return found;
}
bool dampenUrgency(DroneHeap *dh, int serialTag, int newUrgency) {
    bool found = false;
    for(int i = 0; i <= dh->biggest; i++) {
        if (dh->stor[i].serialTag == serialTag) {
            dh->stor[i].urgencyScore = newUrgency;
            found = true;
        }
    }

        rebuildMaxHeap(dh);

    return true;
}



void showHangar(DroneHeap *dh) {
    if (dh->biggest == -1) {
        printf("Hangar is empty.\n");
        return;
    }

    printf("Index | SerialTag | Designation       | Battery | Urgency | Sector\n");
    printf("---------------------------------------------------------------\n");

    for (int wanderer = 0; wanderer <= dh->biggest; wanderer++) {
        DroneUnit topper = dh->stor[wanderer];
        printf("%5d | %9d | %-16s | %7.2f | %7d | %-6s\n",
               wanderer,
               topper.serialTag,
               topper.designation,
               topper.batteryLevel,
               topper.urgencyScore,
               topper.sectorCode);
    }
}

// bool expungeDrone(DroneHeap *dh, int serialTag);  
// void rebuildMaxHeap(DroneHeap *dh);                

// void swapUnits(DroneUnit *a, DroneUnit *b);


int main() {
    DroneHeap base;
    initHangar(&base, 20);

    DroneUnit d1 = {9001, strdup("Specter"), 87.5, 12, strdup("A1")};
    DroneUnit d2 = {9002, strdup("Phantom"), 40.2, 19, strdup("X4")};
    DroneUnit d3 = {9003, strdup("Viper"),   10.0,  5, strdup("B7")};
    DroneUnit d4 = {9004, strdup("Wraith"),  93.1, 25, strdup("Y9")};
    DroneUnit d5 = {9005, strdup("Ravager"), 72.9, 14, strdup("A3")};

    addDrone(&base, d1);
    addDrone(&base, d2);
    addDrone(&base, d3);
    addDrone(&base, d4);
    addDrone(&base, d5);

    printf("\n=== INITIAL HANGAR ===\n");
    showHangar(&base);
    
   

    printf("\n=== EXTRACT MOST URGENT DRONE ===\n");
    DroneUnit removed;
    extractTopDrone(&base, &removed);
    printf("Removed: %d (%s) – urgency %d\n",
           removed.serialTag, removed.designation, removed.urgencyScore);
    showHangar(&base);

    printf("\n=== AMPLIFY URGENCY (increase priority) ===\n");
    amplifyUrgency(&base, 9003, 30);
    showHangar(&base);

    printf("\n=== DAMPEN URGENCY (decrease priority) ===\n");
    dampenUrgency(&base, 9005, 3);
    showHangar(&base);

    

    printf("\n=== REBUILD MAX HEAP ===\n");
    rebuildMaxHeap(&base);
    showHangar(&base);

    freeHangar(&base);
    return 0;
}

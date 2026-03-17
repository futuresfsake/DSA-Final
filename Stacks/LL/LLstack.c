#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Level 1: The base unit (A single car node)
typedef struct node {
    int plateNumber;
    struct node *next;
} Node, *NodePtr;

// Level 2: Nested structure (A Row of cars)
typedef struct {
    char rowID;         
    int currentCount;
    NodePtr top;        
} ParkingRow;

// Level 3: Nested-Nested structure (A Floor/Level containing multiple rows)
typedef struct {
    int floorNumber;
    ParkingRow rows[5]; 
} ParkingLevel;

// Level 4: The Master Structure (The entire Garage)
typedef struct {
    char garageName[50];
    ParkingLevel levels[3]; 
} GlobalGarage;

// ===== Function Definitions =====

void initRow(ParkingRow *pr, char id) {
    pr->rowID = id;
    pr->currentCount = 0;
    pr->top = NULL;
}

bool parkCar(ParkingRow *pr, int plate) {
    NodePtr newCar = malloc(sizeof(Node));
    if (!newCar) return false;

    newCar->plateNumber = plate;
    newCar->next = pr->top;
    pr->top = newCar;
    pr->currentCount++;
    return true;
}

// ===== Main Simulation =====
int main() {
    // Corrected Nested Initialization
    GlobalGarage myGarage = {
        .garageName = "Downtown Tech Hub",
        .levels[0] = {
            .floorNumber = 1,
            .rows[0] = { .rowID = 'A', .currentCount = 0, .top = NULL }
        }
    };

    // Adding a car to the nested-nested structure
    // Access: Garage -> Level[0] -> Row[0]
    parkCar(&myGarage.levels[0].rows[0], 8888);

    printf("Garage: %s\n", myGarage.garageName);
    printf("Floor: %d, Row: %c\n", 
            myGarage.levels[0].floorNumber, 
            myGarage.levels[0].rows[0].rowID);
    
    if (myGarage.levels[0].rows[0].top != NULL) {
        printf("Top Car in Row A: %d\n", myGarage.levels[0].rows[0].top->plateNumber);
    }

    return 0;
}

/* EXPECTED OUTPUT:
---------------------------
Garage: Downtown Tech Hub
Floor: 1, Row: A
Top Car in Row A: 8888
---------------------------
*/
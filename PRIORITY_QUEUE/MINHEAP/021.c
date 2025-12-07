#include <stdio.h>
#include <string.h>

#define MAX_STOPS 20

// --- Struct Definitions ---
typedef struct {
    double latitude;
    double longitude;
} GeoCoords;

typedef struct {
    double distance_km; // Priority: Lower is better
    char location_name[50];
    GeoCoords coords;
} Waypoint;

typedef struct {
    Waypoint stops[MAX_STOPS];
    int count;
} NavigationHeap;

// --- Prototypes ---
void initNav(NavigationHeap* h);
void addStop(NavigationHeap* h, double dist, char* name, double lat, double lon);
Waypoint getClosestStop(NavigationHeap* h); // ExtractMin
void minHeapify(NavigationHeap* h, int i);
void bubbleUp(NavigationHeap* h, int i);

int main() {
    NavigationHeap gps;
    initNav(&gps);

    printf("=== GPS Closest Stop Finder (MinHeap) ===\n");

    // Scanning for gas stations...
    addStop(&gps, 12.5, "Shell Highway", 10.5, 99.2);
    addStop(&gps, 2.3,  "Texaco Local", 10.1, 99.1);  // Closest
    addStop(&gps, 45.0, "Chevron Far", 11.2, 98.5);
    addStop(&gps, 5.8,  "BP Station", 10.3, 99.0);

    printf("Route suggestions (Closest first):\n");
    
    // Logic check: should print 2.3 -> 5.8 -> 12.5 -> 45.0
    for(int i = 0; i < 4; i++) {
        Waypoint w = getClosestStop(&gps);
        printf("Stop %d: %s (%.1f km away)\n", i+1, w.location_name, w.distance_km);
    }

    return 0;
}

// --- IMPLEMENT LOGIC BELOW ---

void initNav(NavigationHeap* h) {
    // TODO: Init count
}

void addStop(NavigationHeap* h, double dist, char* name, double lat, double lon) {
    // TODO: Insert at end, bubbleUp (MinHeap logic)
}

Waypoint getClosestStop(NavigationHeap* h) {
    // TODO: Extract root, move last to root, minHeapify
    Waypoint dummy = {0.0};
    return dummy;
}

void bubbleUp(NavigationHeap* h, int i) {
    // TODO: Swap if child < parent (MinHeap)
}

void minHeapify(NavigationHeap* h, int i) {
    // TODO: Swap if parent > child (MinHeap)
}
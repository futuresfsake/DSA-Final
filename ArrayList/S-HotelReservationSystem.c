#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ===== Room Struct =====
typedef struct {
    int roomId;
    char type[20];   // e.g., "Single", "Double", "Suite"
    float rate;
    bool occupied;
} Room;

// ===== ArrayList for Rooms =====
typedef struct {
    Room *rooms;
    int count;
    int max;
} RoomList;

// ===== Linked List Stack for Reservations =====
typedef struct resNode {
    int resId;
    Room bookedRoom;
    char guestName[50];
    int nights;
    struct resNode *next;
} ResNode, *ResPtr;

typedef struct {
    ResPtr top;
    int size;
} ReservationStack;


// ================= ArrayList Functions =================

// Create room
Room createRoom(int id, const char *type, float rate, bool occ);

// Initialize room list
void initRoomList(RoomList *rl, int max);

// Add room
void addRoom(RoomList *rl, Room r);

// Remove room by ID
Room removeRoom(RoomList *rl, int id);

// Show rooms
void showRooms(RoomList rl);

// ===== Special ArrayList Operations =====

// Find cheapest available room
Room findCheapestAvailable(RoomList rl);

// Count total available rooms
int countAvailableRooms(RoomList rl);


// ================= Stack Functions =================

// Initialize reservation stack
void initReservationStack(ReservationStack *st);

// Push reservation
void pushReservation(ReservationStack *st, Room r, const char *guest, int nights, int resId);

// Pop reservation
Room popReservation(ReservationStack *st);

// Show reservations
void showReservations(ReservationStack st);

// ===== Special Stack Operations =====

// Peek latest reservation
Room peekLatestReservation(ReservationStack st);

// Calculate total revenue from reservations
float calculateTotalRevenue(ReservationStack st);


// ================= Main =================
int main() {
    // === ArrayList Test ===
    RoomList hotel;
    initRoomList(&hotel, 10);

    addRoom(&hotel, createRoom(101, "Single", 50.0, false));
    addRoom(&hotel, createRoom(102, "Double", 80.0, true));
    addRoom(&hotel, createRoom(201, "Suite", 150.0, false));

    printf("\n--- Hotel Rooms ---\n");
    showRooms(hotel);

    Room cheapest = findCheapestAvailable(hotel);
    printf("\nCheapest Available Room: %d (%s, $%.2f)\n", cheapest.roomId, cheapest.type, cheapest.rate);

    int avail = countAvailableRooms(hotel);
    printf("Available Rooms: %d\n", avail);

    // === ReservationStack Test ===
    ReservationStack reservations;
    initReservationStack(&reservations);

    pushReservation(&reservations, hotel.rooms[0], "Alice", 3, 5001);
    pushReservation(&reservations, hotel.rooms[2], "Bob", 2, 5002);

    printf("\n--- Reservations ---\n");
    showReservations(reservations);

    Room latest = peekLatestReservation(reservations);
    printf("\nLatest Reservation: Room %d (%s)\n", latest.roomId, latest.type);

    float revenue = calculateTotalRevenue(reservations);
    printf("Total Revenue: $%.2f\n", revenue);

    return 0;
}


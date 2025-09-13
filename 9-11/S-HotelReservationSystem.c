#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


// https://chatgpt.com/share/68c51e31-89c4-8007-b248-948fae52a2f5

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
Room createRoom(int id, const char *type, float rate, bool occ) {
    Room newRoom;

    newRoom.roomId = id;
    strcpy(newRoom.type, type);
    newRoom.rate = rate;
    newRoom.occupied = occ;

    return newRoom;
}

// Initialize room list
void initRoomList(RoomList *rl, int max) {
    rl->count = -1;
    rl->max = max;
    rl->rooms = malloc(sizeof(Room) * max);
}

bool RoomFull(RoomList *rl) {
    return rl->count == rl->max-1;
}

bool isEmptyRoom(RoomList *rl) {
    return rl->count == -1;
}


// Add room
void addRoom(RoomList *rl, Room r) {
    if (RoomFull(rl)) {
        exit(1);
    }

    rl->count++;
    rl->rooms[rl->count] = r;  
}


//! special operation
// Remove room by ID
Room removeRoom(RoomList *rl, int id) {

    Room notFound = {-1, "", 0.0, false};
    Room Removed;
    int count = 0;

    for(int i = 0; i <=rl->count; i++) {
        if (rl->rooms[i].roomId == id) {
            count = i;
            

        Removed = rl->rooms[i];
        for(int j = i; j < rl->count;j++) {
            rl->rooms[j] = rl->rooms[j+1];
        }
        rl->count--;
        return Removed;
    }
       
}
    return notFound;

}
   



Room popRoomArr(RoomList *rl) {
    if (isEmptyRoom(rl)) {
        exit(1);
    }

    Room temp = rl->rooms[rl->count];
    rl->count--;
    return temp;
}

// Show rooms
void showRooms(RoomList rl) {

    RoomList temp;
    initRoomList(&temp, rl.max);

    printf("%-15s%-15s%-15s%-15s\n", 
        "Room ID", "Type", "Rates", "Occupied");
        printf("\n--------------------------------------------\n");
    while (!isEmptyRoom(&rl)) {
        Room room = popRoomArr(&rl);
        printf("%-15d%-15s%-15.2f%-15s\n", 
            room.roomId, room.type, room.rate, room.occupied ? "Yes" : "No");
        addRoom(&temp, room);
    }

    while (!isEmptyRoom(&temp)) {
        addRoom(&rl, popRoomArr(&temp));
    }
}

// ===== Special ArrayList Operations =====

// Find cheapest available room
// ! find cheapest, and must be available
// ! why are we checking the availability first, so we dont do unneccessary checking
// ! if we check the rates, we pass a cheap room with unavailable type, so its more hassle and unneficient
// ! filter out the rooms first, then get the minimum
Room findCheapestAvailable(RoomList rl) {
    RoomList rooms;
    initRoomList(&rooms, rl.max);

   
    Room notFound = {-1, "", 0.0, false};
    Room cheapest = notFound;

    while (!isEmptyRoom(&rl)) {
        Room current = popRoomArr(&rl);
        addRoom(&rooms, current);

        if (!current.occupied) {
            if (cheapest.roomId == -1 || current.rate < cheapest.rate) {
                cheapest = current;
            }
        }
    }

    while (!isEmptyRoom(&rooms)) {
        addRoom(&rl, popRoomArr(&rooms));
    }
    return cheapest;
}

// Count total available rooms
int countAvailableRooms(RoomList rl) {

    RoomList rooms;
    initRoomList(&rooms, rl.max);
    int count = 0;

    while (!isEmptyRoom(&rl)) {
        Room room = popRoomArr(&rl);
        if (room.occupied == false) {
            count++;
        }
        addRoom(&rooms, room);
    }

    while (!isEmptyRoom(&rooms)) {
        addRoom(&rl, popRoomArr(&rooms));
    }
    return count;
}


// ================= Stack Functions =================

// Initialize reservation stack
void initReservationStack(ReservationStack *st) {
    st->size = 0;
    st->top = NULL;
}

bool EmptyLL(ReservationStack *st) {
    return st->top == NULL;
}


// Push reservation
void pushReservation(ReservationStack *st, Room r, const char *guest, int nights, int resId) {

    ResPtr room = malloc(sizeof(ResNode));
    if (!room) {
        printf("Dynamic Memory Allocation failed.\n");
        exit(1);
    }
    
    room->resId = resId;
    room->bookedRoom = r;
    room->nights = nights;
    strcpy(room->guestName, guest);
    
    if (EmptyLL(st)) {
        st->top = room;
        room->next = NULL;
        st->size++;
    } else {
        room->next = st->top;
        st->top = room;
        st->size++;
    }

}

// Pop reservation
ResNode popReservation(ReservationStack *st) {
    
    if(EmptyLL(st)) {
        exit(1);
    }

    

    ResNode *Remove = st->top;
    ResNode result = *Remove;
    st->top = Remove->next;
    free(Remove);
    st->size--;
    return result;
   
}

// Show reservations
void showReservations(ReservationStack st) {
    ReservationStack temp;
    initReservationStack(&temp);

    while (!EmptyLL(&st)) {
        ResNode r = popReservation(&st);
        printf("Reservation ID: %d Guest Name: %s Nights: %d Room Type: %s\n", r.resId,r.guestName, r.nights, r.bookedRoom.type );
        pushReservation(&temp, r.bookedRoom, r.guestName, r.nights, r.resId);
    }

    while (!EmptyLL(&temp)) {
        ResNode t = popReservation(&temp);
        pushReservation(&st, t.bookedRoom, t.guestName, t.nights, t.resId);
    }
}

// ===== Special Stack Operations =====

// Peek latest reservation
ResPtr peekLatestReservation(ReservationStack st) {
    return st.top; // ? why is st.top wrong?? st.top is a ResPtr, thats just a pointer, but 
    // ? but the function is declared to return a ResNode, thats a struct, thats why u either need to
    // ? dereference it *(st.top) or change the fucntion return type to return the pointer itself
}

// Calculate total revenue from reservations
float calculateTotalRevenue(ReservationStack st) {
    ReservationStack tempStack;
    initReservationStack(&tempStack);

    float ave = 0;
    int count = 0;
    while (!EmptyLL(&st)) {
        ResNode r = popReservation(&st);
        ave+= r.nights * r.bookedRoom.rate;
        pushReservation(&tempStack, r.bookedRoom, r.guestName, r.nights, r.resId);
        count++;
    }

    return ave;

}


// ================= Main =================
int main() {
    // === ArrayList Test ===
    RoomList hotel;
    initRoomList(&hotel, 10);

    addRoom(&hotel, createRoom(101, "Single", 50.0, false));
    addRoom(&hotel, createRoom(102, "Double", 80.0, true));
    addRoom(&hotel, createRoom(201, "Suite", 150.0, false));

    addRoom(&hotel, createRoom(208, "Single", 60.0, true));
    addRoom(&hotel, createRoom(202, "Double", 85.0, false));
    addRoom(&hotel, createRoom(203, "Suite", 170.0, true));
    addRoom(&hotel, createRoom(204, "Double", 90.0, false));


      // Special operation: deleteSearch
    Room removed = removeRoom(&hotel, 102);
    if (removed.roomId != -1) {
        printf("\nRemoved Room: %d (%s)\n", removed.roomId, removed.type);
    } else {
        printf("\nRoom not found!\n");
    }

    printf("\n--- Hotel Rooms ---\n");
    showRooms(hotel);

    Room cheapest = findCheapestAvailable(hotel);
    printf("\nCheapest Available Room: %d (%s, $%.2f)\n", cheapest.roomId, cheapest.type, cheapest.rate);

    int avail = countAvailableRooms(hotel);
    printf("Available Rooms: %d\n", avail);

    // === ReservationStack Test ===
    ReservationStack reservations;
    initReservationStack(&reservations);

pushReservation(&reservations, hotel.rooms[0], "Alice", 3, 5001); // 101 Single
pushReservation(&reservations, hotel.rooms[1], "Bob", 2, 5002);   // 201 Suite


    printf("\n--- Reservations ---\n");
    showReservations(reservations);

    ResPtr latest = peekLatestReservation(reservations);
    printf("\nLatest Reservation: Room %d (%s)\n", latest->resId, latest->bookedRoom.type);

    float revenue = calculateTotalRevenue(reservations);
    printf("Total Revenue: $%.2f\n", revenue);

    return 0;
}


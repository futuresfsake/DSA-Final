#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int hours;
    int minutes;
} Time;

typedef struct {
    int id;
    char origin[50];
    char destination[50];
    Time departure_time;
    Time arrival_time;
} Flight;

typedef struct {
    Flight *flights;
    int count;
    int max;
} Flights;


Time createTime(int h, int m) {
    Time time;
    time.hours = h;
    time.minutes = m;

    return time;
}


bool isEmpty(Flights *F) {
    return F->count == 0;
}
bool isFull(Flights *F) {
    return F->count == F->max;
}
void makeNULL(Flights *F) {
    F->count = 0;
    F->max = 0;

}



Flight createFlight() {
    Flight newFlight;
    Time depTime;
    Time arrTime;

   
    printf("Enter the flight ID: ");
    scanf("%d", &newFlight.id);

    printf("Enter the origin: ");
    scanf("%s", newFlight.origin);

    printf("Enter the destination: ");
    scanf("%s", newFlight.destination);

    int depHr, depMin;
    int ArrHr, ArrMin;
    printf("Enter the Departure Time HH MM: ");
    scanf("%d %d", &depHr, &depMin);
    newFlight.departure_time = createTime(depHr, depMin);


    printf("Enter the Arrival Time HH MM: ");
    scanf("%d %d", &ArrHr, &ArrMin);
    newFlight.arrival_time = createTime(ArrHr, ArrMin);

    return newFlight;
} 
//Use flight data as parameters
void addFlight(Flights *flight_list, Flight f) {

    if (isFull(flight_list)) {
        printf("List is already full.\n");
        exit(1);      
    }

   
    flight_list->flights[flight_list->count] = f;
     flight_list->count++;
    printf("%d is successfully added.\n", f.id);
    
    return;

}
Flight removeFlight(Flights *flightlist, int flightid) {

    int num;
    for(int i = 0; i < flightlist->count; i++) {
        if (flightid == flightlist->flights[i].id) {
             
            Flight temp = flightlist->flights[i];
            int num = i;

            for(int k = i; k < flightlist->count -1; k++) {
                flightlist->flights[k] = flightlist->flights[k+1];
            }
            flightlist->count--;
            return temp;


        }
    }

    Flight notFound;
    notFound.id = -1;
    return notFound;


    
    }
    void showFlights(Flights flight_list) {
    printf("\nFlights Today:\n");
    printf("%-5s %-15s %-15s\n", "ID", "Destination", "Origin");  
    printf("--------------------------------------------------\n");

    for (int i = 0; i < flight_list.count; i++) {
        printf("%-5d %-15s %-15s\n",
               flight_list.flights[i].id,
               flight_list.flights[i].destination,
               flight_list.flights[i].origin);
    }
}

void displayFlightInfo(Flight f) {
    printf("Flight Information - ID: %d", f.id);
    printf("Origin%10dDestination%10dDeparture Time%5dArrival Time");
    printf("Origin%10destination%10sDeparture Time%5dArrival Time");
    printf("%s%10d%s%10d%d%5d%d", f.origin, f.destination, f.departure_time, f.arrival_time);
} // display in standard time HH:MM XX



int main() {

    Flights F;
    F.count = 0;
    F.max = 10;
    
    
    F.flights = malloc(sizeof(Flight) * F.max);

    Flight f1 = {11, "Manila", "Cebu", createTime(8, 30), createTime(10, 15)};
    Flight f2 = {12, "Cebu", "Davao", createTime(11, 0), createTime(12, 45)};
    Flight f3 = {13, "Davao", "Manila", createTime(14, 20), createTime(16, 30)};

    

    addFlight(&F, f1);
    addFlight(&F, f2);
    addFlight(&F, f3);
 

    Flight found = removeFlight(&F, 13);
    if (found.id > 0) {
        printf("Flight %d is removed successfully!\n", found.id);
    } else if (found.id == -1) {
        printf("Flight %d not existing...\n", found.id);
    }
    

    showFlights(F);
  
    


    return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct  {
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



#define STACK_SIZE 10

typedef struct {
    Flight stack[STACK_SIZE];
    int top;
} FlightStack;


void initStack(FlightStack *s) {
    s->top = -1;
    
}

bool isStackEmpty(FlightStack s) {
    return s.top == -1;
}

bool isStackFull(FlightStack s) {
    return s.top == STACK_SIZE - 1;
}


void pushFlight(FlightStack *s, Flight f) {
    if (isStackFull(*s)) {
        printf("Stack is already full.\n");
        exit(1);
    }

    s->top++;
    s->stack[s->top] = f;
}

Flight popFlight(FlightStack *s) {

    if (isStackEmpty(*s)) {
        exit(1);
    }

    Flight toRemove = s->stack[s->top];
    s->top--;

    return toRemove;
    
}

Flight peekFlight(FlightStack s) {
    Flight peek = s.stack[s.top];
    return peek;
}

bool makeNULL(FlightStack *s) {
    s->top = -1;
    
}

void display(FlightStack *s) {
    FlightStack temp;
    initStack(&temp);

    if (isStackEmpty(*s)) {
        return;

    }

    while (!isStackEmpty(*s)) {
        Flight f = peekFlight(*s);
        printf("ID: %d, %s bound to %s\n",f.id, f.origin, f.destination );
        pushFlight(&temp,popFlight(s));
    }
    

    while (!isStackEmpty(temp)) {
        pushFlight(s, popFlight(&temp));
    }
}


int main() {
    FlightStack s;
    initStack(&s);


    Flight f1 = {1, "Cebu", "Manila", {8, 30}, {10, 45}};
    Flight f2 = {2, "Manila", "Davao", {11, 15}, {13, 30}};
    Flight f3 = {3, "Davao", "Cebu", {14, 00}, {15, 45}};
    Flight f4 = {4, "Cebu", "Iloilo", {16, 20}, {17, 10}};
    Flight f5 = {5, "Iloilo", "Manila", {18, 00}, {19, 40}};

    pushFlight(&s, f1);
    pushFlight(&s, f2);
    pushFlight(&s, f3);
    pushFlight(&s, f4);
    pushFlight(&s, f5);

    display(&s);

    popFlight(&s);
    printf("After deleting\n");
    display(&s);
    
    
    

}
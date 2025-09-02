#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ===== Node Definition =====
typedef struct node {
    int plateNumber;       // car plate number (int)
    struct node *next;
} Node, *NodePtr;

typedef struct {
    NodePtr top;
} Stack;

// ===== Function Declarations =====
void initStack(Stack *s);
bool isEmpty(Stack s);
bool push(Stack *s, int plate);
bool pop(Stack *s, int *plate);
bool peek(Stack *s, int *plate);
void display(Stack *s);

// ===== Main Simulation =====
int main() {
    Stack parkingLot;
    initStack(&parkingLot);

    // Cars arrive
    push(&parkingLot, 1010);
    push(&parkingLot, 2020);
    push(&parkingLot, 3030);

    printf("Cars currently parked:\n");
    display(&parkingLot);

    // One car leaves
    int plate;
    if (pop(&parkingLot, &plate)) {
        printf("\nCar exiting: Plate %d\n\n", plate);
    }

    printf("Cars left in parking lot:\n");
    display(&parkingLot);

    // Another car arrives
    push(&parkingLot, 4040);
    printf("\nNew car arrived: Plate 4040\n\n");

    printf("Final parking lot state:\n");
    display(&parkingLot);

    return 0;
}

void initStack(Stack *s) {
    s->top = NULL;
}
bool isEmpty(Stack s) {
    return s.top == NULL;
}


bool push(Stack *s, int plate) {

    

    NodePtr newCar = malloc(sizeof(Node));
    if (!newCar) {
        printf("Dynamic Memory Allocation failed!");
        return false;
    } 
    
   
    newCar->plateNumber = plate;

    newCar->next = s->top;
    s->top = newCar;

    return true;
}

bool pop(Stack *s, int *plate) {

    if (isEmpty(*s)) {
        
        return false;
    }

    NodePtr temp = s->top;
    s->top = temp->next;
    *plate = temp->plateNumber;

    free(temp);
    return true;

}

bool peek(Stack *s, int *plate) {
    if (isEmpty(*s)) {
        
        return false;
    }

    *plate = s->top->plateNumber;
    return true;
    
}
void display(Stack *s) {
    Stack temp;
    initStack(&temp);
    printf("Data: ");
    int x;

    while (!isEmpty(*s)) {
        peek(s, &x);
        printf("%d ", x);
        pop (s, &x);
        push (&temp, x);
    }
    printf("\n");

    while (pop(&temp, &x)) {
        push(s,x);
    }
}


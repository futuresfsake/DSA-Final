#include <stdio.h>
#include <stdlib.h>
#define MAX 10   // maximum size of stack

// Stack structure
typedef struct {
    int arr[MAX];
    int top;
} Stack;

// Function declarations
void initStack(Stack *s);
int isEmpty(Stack *s);
int isFull(Stack *s);
void push(Stack *s, int value);
void pop(Stack *s);           // void pop (no return value)
int peek(Stack *s);           // get top element
void display(Stack *s);

int main() {
    Stack orders;
    initStack(&orders);

    // 1. Push 5 new customer order IDs
    push(&orders, 101);
    push(&orders, 102);
    push(&orders, 103);
    push(&orders, 104);
    push(&orders, 105);

    // 2. Cancel the last 2 orders
    if (!isEmpty(&orders)) {
        printf("Cancelled Order ID: %d\n", peek(&orders));
        pop(&orders);
    }
    
    
    
    if (!isEmpty(&orders)) {
        printf("Cancelled Order ID: %d\n", peek(&orders));
        pop(&orders);
    }

   // 3. Show remaining orders in stack
    printf("\nCurrent Orders:\n");
    display(&orders);

    return 0;
}



// Function declarations
void initStack(Stack *s) {
    s->top = -1;
}
int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX -1;
}


void push(Stack *s, int value) {
    
    if (isFull(s)) {
        printf("List is already full!");
        return;
    }
    
    s->top++;
    s->arr[s->top]= value;
    printf("%d is successfully added\n", value);
}
void pop(Stack *s) {
    if (isEmpty(s)) {
        printf("List is empty.\n");
        return;
    }
    
    s->top--;
}         // void pop (no return value)


int peek(Stack *s) {
    
   return  s->arr[s->top];
    
}         // get top element
void display(Stack *s) {
    int x;
    Stack temp;
    initStack(&temp);
    
    while (!isEmpty(s)) {
        x = peek(s);
        printf("%d ", x);
        pop(s); 
        push(&temp, x); 
    }

    

    
    
    while (!isEmpty(&temp)) {
        int a = peek(&temp);
        pop(&temp);
        push(s, a);
    }
}


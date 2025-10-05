// ! push integers below 100
// ! implement a function that should compute the sum of all elements currently in the stack


#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int arr[MAX];
    int top;
} Stack;

// Function declarations
void initStack(Stack *s);
int isEmpty(Stack *s);
int isFull(Stack *s);
void push(Stack *s, int value);   // Restrict to < 100
int pop(Stack *s);
int peek(Stack *s);
int sumStack(Stack *s);           // Compute sum

int main() {
    Stack s;
    initStack(&s);

    push(&s, 50);
    push(&s, 120);  // rejected
    push(&s, 780);
    push(&s, 950);
    push(&s, 10);

    printf("Sum of stack elements: %d\n", sumStack(&s));

    return 0;
}

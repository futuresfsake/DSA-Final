// ! stack, top must be at index 0
// ! when pushing the top must be decremented
// ! popping, top must be incremented

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#define MAX 5

typedef int ItemType;

typedef struct {
    ItemType data[MAX];
    int top;  // points to current top index
} Stack;

// ================== FUNCTION DECLARATIONS ==================
void initStack(Stack *s);
bool isEmpty(Stack s);
bool isFull(Stack s);
void push(Stack *s, ItemType item);
ItemType pop(Stack *s);
ItemType peek(Stack s);

// ================== FUNCTION DEFINITIONS ==================
void initStack(Stack *s) {
    s->top = MAX;  // empty stack
}

bool isEmpty(Stack s) {
    return s.top == MAX;
}

bool isFull(Stack s) {
    return s.top == 0;
}

void push(Stack *s, ItemType item) {
    if (s->top == 0) {
        printf("Stack is full.\n");
        return;
    }

    s->top--;
    s->data[s->top] = item;
   
}

int pop(Stack *s) {
    if (s->top == MAX) {
        printf("Items are empty!");
        exit(1);
    }

    int data = s->data[s->top];
    s->top++;

    return data;

}

ItemType peek(Stack s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;  // sentinel
    }
    return s.data[s.top];
}



// ================== MAIN TEST ==================
int main() {
    Stack s;
    initStack(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    printf("Top element: %d\n", peek(s));

    printf("Popped: %d\n", pop(&s));
    printf("Popped: %d\n", pop(&s));
    printf("Popped: %d\n", pop(&s));

    // Test underflow
    pop(&s);

    return 0;
}

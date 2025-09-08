#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure
typedef struct node {
    int data;
    struct node* next;
} NodeType, *NodePtr, *Stack;

// Function declarations
void initStack(Stack *s);
bool isEmpty(Stack *s);
void push(Stack *s, int data);
int pop(Stack *s);
int peek(Stack *s);
void display(Stack *s);
void removeAll (Stack *s) {
    while (!isEmpty(s)) {
        pop(s);
    }
}

int main() {
    Stack mystack;
    initStack(&mystack);

    push(&mystack, 10);
    push(&mystack, 20);
    push(&mystack, 30);

    // printf("Top element: %d\n", peek(&mystack));

    // printf("Stack contents:\n");
    // display(&mystack);

    // printf("Popped: %d\n", pop(&mystack));
    // printf("Stack after pop:\n");
    // display(&mystack);

    // 👉 you will implement removeAll(&mystack);
    removeAll(&mystack);
    if (isEmpty(&mystack)) {
        printf("It is empty");
    } else {
        printf("It is not empty!");
    }
}

// Initialize stack
void initStack(Stack *s) {
    *s = NULL;
}

// Check if empty
bool isEmpty(Stack *s) {
    return *s == NULL;
}

// Push element
void push(Stack *s, int data) {
    NodePtr temp = malloc(sizeof(NodeType));
    if (!temp) {
        printf("Memory allocation failed!\n");
        return;
    }
    temp->data = data;
    temp->next = *s;
    *s = temp;
}

// Pop element
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow!\n");
        return -1;
    }
    NodePtr temp = *s;
    int data = temp->data;
    *s = temp->next;
    free(temp);
    return data;
}

// Peek top element
int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return (*s)->data;
}

// Display stack (non-destructive)
void display(Stack *s) {
    NodePtr temp = *s;
    while (temp != NULL) {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}

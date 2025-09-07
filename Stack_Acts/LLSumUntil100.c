#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Stack structure (Linked List)
typedef struct {
    Node *top;
} StackLL;


// Function declarations
void initStackLL(StackLL *s);          // Initialize stack
int isEmptyLL(StackLL *s);             // Check if stack is empty
void pushLL(StackLL *s, int value);    // Push value
int popLL(StackLL *s);                 // Pop value
int peekLL(StackLL *s);                // Peek top value
void displayLL(StackLL *s);            // Display stack (non-destructive)
int sumUntil100LL(StackLL *s);         // Sum until ≤ 100


int main() {
    StackLL s;
    initStackLL(&s);

    // Sample pushes
    pushLL(&s, 50);
    pushLL(&s, 10);
    pushLL(&s, 40);
    pushLL(&s, 58);

    // Compute sum of values (capped at 100)
    int total = sumUntil100LL(&s);
    printf("Sum of values until 100: %d\n", total);
    displayLL(&s);
    return 0;
}



// Function definitions
void initStackLL(StackLL *s) {
    s->top = NULL;
}

int isEmptyLL(StackLL *s) {
    return s->top == NULL;
}

void pushLL(StackLL *s, int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

int popLL(StackLL *s) {
    if (isEmptyLL(s)) {
        printf("Underflow\n");
        return -1;
    }
    Node *temp = s->top;
    int value = temp->data;
    s->top = temp->next;
    free(temp);
    return value;
}

int peekLL(StackLL *s) {
    if (isEmptyLL(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->top->data;
}

void displayLL(StackLL *s) {
    Node *current = s->top;
    printf("Data: {");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("}\n");
}


// --- You will implement this ---
int sumUntil100LL(StackLL *s) {
    StackLL temp;
    initStackLL(&temp);

    int sum = 0;

    while (!isEmptyLL(s)) {
        int val = popLL(s);
        if (sum+val <= 100) {
            sum+= val;
            pushLL(&temp, val);
        }

        
    }

    while(!isEmptyLL(&temp)) {
        pushLL(s, popLL(&temp));
        
    }
    return sum;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;
void initStack(Stack *s) {
    s->top = NULL;
}

int isEmpty(Stack *s) {
    return s->top == NULL;
}

void push(Stack *s, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow!\n");
        return -1;  // error value
    }
    Node *temp = s->top;
    int value = temp->data;
    s->top = temp->next;
    free(temp);
    return value;
}

int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;  // error value
    }
    return s->top->data;
}


int findMin(Stack *s);
int findMax(Stack *s);

int main() {
    Stack s;
    initStack(&s);

    push(&s, 10);
    push(&s, 3);
    push(&s, 583);
    push(&s, 1);
    push(&s, 15);

    printf("Min: %d\n", findMin(&s));
    printf("Max: %d\n", findMax(&s));

    return 0;
}


int findMin(Stack *s) {

    Stack temp;
    initStack(&temp);

    int minVal = pop(s);
    push(&temp, minVal);

    while (!isEmpty(s)) {
        int val = pop(s);

        if (val < minVal) {
            minVal = val;
        }

        push(&temp, val);
    }

    while (!isEmpty(&temp)) {
        push(s, pop(&temp));
    }
    return minVal;
}


int findMax(Stack *s) {
    Stack temp;
    initStack(&temp);

    int maxVal = pop(s);
    push(&temp, maxVal);


    while (!isEmpty(s)) {
        int val = pop(s);
        if (val > maxVal) {
            maxVal = val;
        }
        push(&temp, val);
    }

    while (!isEmpty(&temp)) {
        push(s, pop(&temp));
    }

    return maxVal;
}

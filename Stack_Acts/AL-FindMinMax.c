// ! initialize two variables, min & max
// ! main stack holds value
// ! min stack, keep track of the current minimum at each level
// ! max stack current maximum at each level

// https://chatgpt.com/share/68ba71be-d8d8-8007-ac31-c15f6626906a


#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int arr[MAX];
    int top;
} Stack;
// Function definitions
void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack Overflow!\n");
        return;
    }
    s->arr[++(s->top)] = value;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow!\n");
        return -1; // error value
    }
    return s->arr[(s->top)--];
}

int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return -1; // error value
    }
    return s->arr[s->top];
}
int findMin(Stack *s);
int findMax(Stack *s);



int main() {
    Stack s;
    initStack(&s);

    push(&s, 100);
    push(&s, 3);
    push(&s, 2);
    push(&s, 7);
    push(&s, 15);

    printf("Min: %d\n", findMin(&s));
    printf("Max: %d\n", findMax(&s));

    return 0;
}

// Min/Max
int findMin(Stack *s) {
   

    Stack tempStack;
    initStack(&tempStack);
    

    int minVal = pop(s);
    push(&tempStack, minVal);

    while (s->top != -1) {
        int val = pop(s);
        if (val < minVal) {
            minVal = val;
        }
        push(&tempStack, val);
}

    while (tempStack.top != -1) {
        int x = pop(&tempStack);
        push(s, x);
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

        if (val> maxVal) {
            maxVal = val;
        }
        push(&temp, val);
    }

    while (temp.top != -1) {
        push(s, pop(&temp));
    }

    return maxVal;

}

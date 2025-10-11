#include <stdio.h>
#include <stdlib.h>
#define MAX 5   // maximum size of stack

// Stack structure using ArrayList
typedef struct {
    int arr[MAX];
    int top;
} StackAL;


// Function declarations
void initStackAL(StackAL *s) {
    s->top = -1;
}      // Initialize stack
int isEmptyAL(StackAL *s) {
    return s->top == -1;
}   // Check if stack is empty
int isFullAL(StackAL *s) {
    return s->top == MAX -1;
}         // Check if stack is full


void pushAL(StackAL *s, int value) {
    if (isFullAL(s)) {
        printf("Overflow\n");
        return;
    }

    s->top++;
    s->arr[s->top] = value;
} // Push value

int popAL(StackAL *s) {
    if (isEmptyAL(s)) {
        printf("Underflow");
        return -1;
    }
    int data = s->arr[s->top];
    s->top--;
    return data;
}     

// Pop value (void)
int peekAL(StackAL *s) {
    return s->arr[s->top];
}           // Peek top value


void displayAL(StackAL *s) {
    StackAL tempStack;
    initStackAL(&tempStack);
    int x;
    int x2;

    printf("Data: {");
    while (!isEmptyAL(s)) {
        x = peekAL(s);
        printf("%d ", x);
        popAL(s);
        pushAL(&tempStack, x);

    }
    printf("}");


    while(!isEmptyAL(&tempStack)) {
        int x2 = peekAL(&tempStack);
        popAL(&tempStack);
        pushAL(s, x2);
    }
}

int sumUntil100(StackAL *s);            


int main() {
    StackAL s;
    initStackAL(&s);

    // Sample pushes
    pushAL(&s, 50);
    pushAL(&s, 10);
    pushAL(&s, 40);
    pushAL(&s, 58);

    // Compute sum of even numbers
    int total = sumUntil100(&s);
    printf("Sum of even numbers: %d\n", total);

    return 0;
}


int sumUntil100(StackAL *s) {
    StackAL temp;
    initStackAL(&temp);

    int sum = 0;

    while (!isEmptyAL(s) ) {
        int val = popAL(s);
        if (sum + val <= 100) {
        sum+= val;
        pushAL(&temp, val);
        }
    }

    while (!isEmptyAL(&temp)) {
        pushAL(s, popAL(&temp));
    }

    return sum;

}

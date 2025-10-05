#include <stdio.h>
#include <stdlib.h>
#define MAX 10

// Stack structure using ArrayList
typedef struct {
    int arr[MAX];
    int top;
} StackAL;

// Function declarations
void initStackAL(StackAL *s);       // Initialize stack
int isEmptyAL(StackAL *s);          // Check if stack is empty
int isFullAL(StackAL *s);           // Check if stack is full
void pushAL(StackAL *s, int value); // Push value
void popAL(StackAL *s);             // Pop value (void)
int peekAL(StackAL *s);             // Peek top value
void displayAL(StackAL *s);         // Display stack
void reverseAL(StackAL *s);         // Reverse stack

int main() {
    StackAL s;
    initStackAL(&s);

    // Example usage
    pushAL(&s, 10);
    pushAL(&s, 20);
    pushAL(&s, 30);

    printf("Original Stack:\n");
    displayAL(&s);

    reverseAL(&s);
    printf("\n");
    printf("Reversed Stack:\n");
    displayAL(&s);

    return 0;
}



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

void popAL(StackAL *s) {
    if (isEmptyAL(s)) {
        printf("Underflow");
        return;
    }
    s->top--;
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

   // Display stack
void reverseAL(StackAL *s) {

    StackAL temp1;
    initStackAL(&temp1);
    int x1, x2, x3;
    StackAL temp2;
    initStackAL(&temp2);


    while (!isEmptyAL(s)) {
        x1 = peekAL(s);
        popAL(s);
        pushAL(&temp1, x1);
    }

    while (!isEmptyAL(&temp1)) {
        x2 = peekAL(&temp1);
        popAL(&temp1);
        pushAL(&temp2, x2);
    }

    while (!isEmptyAL(&temp2)) {
        x3= peekAL(&temp2);
        popAL(&temp2);
        pushAL(s, x3);
    }

}
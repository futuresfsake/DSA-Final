#include <stdio.h>
#include <stdlib.h>
#define MAX 10   // maximum size of stack

// Stack structure
typedef struct {
    int arr[MAX];
    int top;
} Stack;

// Function declarations
void initStack(Stack *s) {
    s->top = -1;
}
int isEmpty(Stack s) { // takes a whole struct
    return s.top == -1;

}
int isFull(Stack s) { // takes the whole struct
    return s.top == MAX-1;
}


void push(Stack *s, int value) { // a pointer to struct

    if (isFull(*s)) { // ! you have to dereference the pointer to a struct "s" by *s, because
        // ! isFUll, only receives the whole struct
        return;
    }
     s->top++; // ? You have to increment it first, because the current index
     // ? you will be placing them is -1, if not incremented first

    s->arr[s->top] = value;
  

}

int pop(Stack *s) { // a pointer to struct
    if (isEmpty(*s)) { // ! have to dereference it, passing the address means its already a double pointer
        return -1;
    }
    int val = s->arr[s->top];
    s->top--;
    return val;
}


int peek(Stack *s){ // a pointer to struct // ! returns the index not the value
    if(isEmpty(*s)) {
        return -1;
    }
    
    return s->arr[s->top];
}


void display(Stack *s) {
    int x;
    Stack temp; // ! after declaring the temp; it is important to initialize it
    initStack(&temp);

    while (!isEmpty(*s)) { // ! dereference it again
        x = pop(s);
        printf("%d, ", x);
        push(&temp, x);
    }


    
    while (!isEmpty(temp)) {
        int val = pop(&temp);
        push(s, val);
    }
}

int main() {
    Stack s;
    initStack(&s);

    // 1. Push 5 quiz scores
    push(&s, 85);
    push(&s, 90);
    push(&s, 78);
    push(&s, 92);
    push(&s, 88);

    // 2. Pop last two scores
    pop(&s);
    pop(&s);

    // 3. Display remaining scores
    display(&s);

    return 0;
}


// Alternative if pop does not return a value;
// void display(Stack *s) {
//     int x;
//     Stack temp;
//     initStack(&temp);

//     while (!isEmpty(*s)) {
//         x = peek(*s);
//         printf("%d ", x);
//         pop(s);
//         push(&temp, x);
//     }

//     while (!isEmpty(temp)) {
//         int val = peek(temp);
//         pop(&temp);
//         push(s, val);
//     }
//     printf("\n");
// }

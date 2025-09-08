#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct node {
    int data;
    struct node* add;
}NodeType, *NodePtr, *Stack;

bool isEmpty ();
void push();
int pop();
int peek();
void initStack();
Stack removeNegatives();
void display();


int main() {
    Stack mystack;
    initStack(&mystack);

    push(&mystack, -7);
     push(&mystack, 45);
      push(&mystack, -5);
       push(&mystack, 3);
        push(&mystack, 7);
        

        Stack negatives = removeNegatives(&mystack);
        printf("New Stacks with negatives: \n");
        display(&negatives);
}


bool isEmpty (Stack *s) {
    return *s == NULL;
}

void push(Stack *s, int data) {
    NodePtr temp = malloc(sizeof(NodeType));
    if (!temp) {
        printf("Dynamic Memory Allocation.\n");
        return;
    }
    temp->data = data;
    temp->add = *s;
    *s = temp;

}
int pop(Stack *s) {
    if (isEmpty(s)) {
        return -1;
    }

    NodePtr temp = *s;
    int data = temp->data;
    *s = temp->add;
    free(temp);
    return data;
}

int peek(Stack *s) {
    return (*s)->data;
}

void initStack(Stack *s) {
    *s = NULL;
}

Stack removeNegatives(Stack *s) {

    Stack negative;
    initStack(&negative);
    Stack temp;
    initStack(&temp);

    while (!isEmpty(s)) {
        int val = peek(s);
        if (val < 0) {
            push(&negative, pop(s));
        } else if (val >= 0) {
            push(&temp, pop(s));
        }
    }


    while (!isEmpty(&temp)) {
        push(s, pop(&temp));
    }

    return negative;

}
void display (Stack *s) {

    // Stack temp;
    // initStack(&temp);

    while (!isEmpty(s)) {
        printf("%d ", pop(s));
    }

}






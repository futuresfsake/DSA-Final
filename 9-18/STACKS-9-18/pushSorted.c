#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ===== Structs =====
typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

// ===== Function Declarations =====
Stack* initStack();
bool isEmpty(Stack *s);
void push(Stack *s, int val);
int pop(Stack *s);
void display(Stack *s);
void pushSorted(Stack *s, int val);  // main function you will master

// ===== Main =====
int main() {
    Stack *s = initStack();

    // Testing pushSorted
    pushSorted(s, 30);
    pushSorted(s, 10);
    pushSorted(s, 40);
    pushSorted(s, 20);
    pushSorted(s, 25);

    printf("Stack (sorted, top first):\n");
    display(s);

    return 0;
}

// ===== Function Definitions =====
Stack* initStack() {
    Stack *s = (Stack*) malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

bool isEmpty(Stack *s) {
    return (s->top == NULL);
}

void push(Stack *s, int val) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = s->top;
    s->top = newNode;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow!\n");
        return -1;
    }
    Node *temp = s->top;
    int val = temp->data;
    s->top = temp->next;
    free(temp);
    return val;
}

void display(Stack *s) {
    Node *curr = s->top;
    while (curr != NULL) {
        printf("%d\n", curr->data);
        curr = curr->next;
    }
}

// ===== pushSorted =====
void pushSorted(Stack *s, int val) {
    

    Node *newNode = malloc(sizeof(Node));
    if (!newNode) {
        printf("Dynamic memory allocation failed.\n");
        exit(1);
    }

    newNode->data = val;
    newNode->next = NULL;

    Stack Tempstack;
    Tempstack.top = NULL;

    Node *tempHolder = NULL;


    while (s->top != NULL && s->top->data < val) {
        tempHolder = s->top;
        s->top = tempHolder->next;

        tempHolder->next = Tempstack.top;
        Tempstack.top = tempHolder;

    }

    newNode->next = s->top;
    s->top = newNode;



    while (Tempstack.top != NULL) {
        tempHolder = Tempstack.top;
        Tempstack.top= tempHolder->next;


        tempHolder->next = s->top;
        s->top = tempHolder;
    }


}

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

// Basic operations
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
        return -1;
    }
    return s->top->data;
}
void displayLL(StackLL *s) {
    Node *curr = s->top;
    printf("Stack (top ->>> bottom): ");
    while (curr) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

// Sorting function (to be implemented by you)
void sortStackLL(StackLL *s);

int main() {
    StackLL s;
    initStackLL(&s);

    pushLL(&s, 34);
    pushLL(&s, 3);
    pushLL(&s, 31);
    pushLL(&s, 98);
    pushLL(&s, 92);
    pushLL(&s, 23);

    printf("Original Stack:\n");
    displayLL(&s);

    sortStackLL(&s);  // <-- you will implement this

    printf("Sorted Stack:\n");
    displayLL(&s);

    return 0;
}


void sortStackLL(StackLL *s) {

    StackLL temp;
    initStackLL(&temp);

    pushLL(&temp, popLL(s));
    while(!isEmptyLL(s)) {
        int val = popLL(s);
        
        

        while (!isEmptyLL(&temp) && val < peekLL(&temp)) {
            pushLL(s, popLL(&temp));

        }
        
        
        pushLL(&temp, val);
    }

    while(!isEmptyLL(&temp)) {
        pushLL(s, popLL(&temp));
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ===== Node Definition =====
typedef struct node {
    int data;
    struct node *next;
} Node, *NodePtr;

typedef struct {
    NodePtr top;
} Stack;

void initStack(Stack *s) { s->top = NULL; }

bool isEmpty(Stack *s) { return s->top == NULL; }

bool push(Stack *s, int value) {
    NodePtr newNode = (NodePtr)malloc(sizeof(Node));
    if (!newNode) return false;
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
    return true;
}

bool pop(Stack *s, int *removed) {
    if (isEmpty(s)) return false;
    NodePtr temp = s->top;
    *removed = temp->data;
    s->top = temp->next;
    free(temp);
    return true;
}

bool peek(Stack *s, int *topval) {
    if (isEmpty(s)) return false;
    *topval = s->top->data;
    return true;
}

// Strict-stack "display": peek+pop to a temp stack, then restore.
void display(Stack *s) {
    Stack temp;
    initStack(&temp);

    int x;
    printf("Data: ");
    while (peek(s, &x)) {   // look only at top
        printf("%d ", x);
        pop(s, &x);         // remove from original
        push(&temp, x);     // save into temp
    }
    printf("\n");

    // restore original (still only using stack ops)
    while (pop(&temp, &x)) {
        push(s, x);
    }
}

// ===== Main =====
int main() {
    Stack st;
    initStack(&st);

    push(&st, 10);
    push(&st, 20);
    push(&st, 30);
    push(&st, 40);

    printf("Stack before pop: ");
    display(&st);   // pass by POINTER, since we’re popping/restoring

    int removed;
    if (pop(&st, &removed)) {
        printf("Popped: %d\n", removed);
    }

    printf("Stack after pop: ");
    display(&st);

    return 0;
}

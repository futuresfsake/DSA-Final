#include <stdio.h>
#include <stdlib.h>

// Node structure for stack
typedef struct Node {
    int data;
    struct Node *next;
} Node, *NodePtr, *List;   // aliases: NodePtr = pointer to Node, List = pointer to Node






// Function declarations
Node* createNode(int value);
int isEmpty(NodePtr top);
void push(NodePtr *top, int value);
int pop(NodePtr *top);
int peek(NodePtr top);
void display(NodePtr top);

int main() {
    List top = NULL; // initialize empty stack (using alias)

    // 1. Push 4 transaction IDs
    push(&top, 101);
    push(&top, 102);
    push(&top, 103);
    push(&top, 104);

    // 2. Pop 1 transaction ID
    pop(&top);

    // 3. Peek latest transaction ID
    int latest = peek(top);
    printf("Latest transaction ID: %d\n", latest);

    // 4. Display stack
    display(top);

    return 0;
}


Node* createNode(int value) {
    Node* new = malloc(sizeof(Node));
    if (!new) {
        printf("Dynamic Memory Allocation failed.\n");
        return NULL;
    }

    new->data = value;
    new->next = NULL;
    return new;
}


int isEmpty(NodePtr top) {
    return top == NULL;
}


void push(NodePtr *top, int value) {
    
    Node* new = createNode(value);

    new->next = *top;
    *top = new;
    // printf("%d is successfully pushed\n", value);


    
}


int pop(NodePtr *top) {

    if (isEmpty(*top)) {
        return -1;
    }

   
    Node* temp = *top;
    int data = temp->data;
    *top = temp->next;
    free(temp);
    return data;
    
}
int peek(NodePtr top) {
     if (isEmpty(top)) {
        return -1;
    }

    return top->data;
}
void display(NodePtr top) {
    List temp = NULL;

    printf("Current data: { ");
    while (top != NULL) {
        int x = pop(&top);
        printf(" %d ", x);
        push(&temp, x);
      

    }

      printf("}");
    while (temp!= NULL) {
        int x1 = pop(&temp);
        push(&top, x1);
    }

}

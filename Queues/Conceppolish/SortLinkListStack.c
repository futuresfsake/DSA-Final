#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// =================== DATA DEFINITIONS ===================
typedef char String[30];

typedef struct {
    int prodID;
    String prodName;
    int prodQty;
} Product;

// Node for linked list stack
typedef struct Node {
    Product data;
    struct Node* next;
} Node;

// Stack using linked list
typedef struct {
    Node* top;
} Stack;

// =================== FUNCTION DECLARATIONS ===================
void initStack(Stack* s);
bool isEmpty(Stack* s);
void push(Stack* s, Product p);
Product pop(Stack* s);
Product peek(Stack* s);
void display(Stack* s);
void sortStack(Stack* s); // sorting function left blank for you

// =================== FUNCTION DEFINITIONS ===================
void initStack(Stack* s) {
    s->top = NULL;
}

bool isEmpty(Stack* s) {
    return s->top == NULL;
}

void push(Stack* s, Product p) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = p;
    newNode->next = s->top;
    s->top = newNode;
}

Product pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        Product empty = {0};
        return empty;
    }
    Node* temp = s->top;
    Product p = temp->data;
    s->top = s->top->next;
    free(temp);
    return p;
}

Product peek(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        Product empty = {0};
        return empty;
    }
    return s->top->data;
}

void display(Stack* s) {
    Node* current = s->top;
    printf("Stack contents:\n");
    while (current != NULL) {
        printf("ID: %d, Name: %s, Qty: %d\n", 
               current->data.prodID, current->data.prodName, current->data.prodQty);
        current = current->next;
    }
    printf("\n");
}

void sortStack(Stack* s) {
    
    Stack tempStack;
    tempStack.top = NULL;

    
    Product p ;

    while (s->top != NULL) {
        p = pop(s);

       while (!isEmpty(&tempStack) && peek(&tempStack).prodQty > p.prodQty) {
        push(s, pop(&tempStack));
        
       } 

       push(&tempStack, p);

    }


    if (!isEmpty(&tempStack)) {
        push(s, pop(&tempStack));
    }

}



// void sortStack(Stack* s) {
//     Stack tempStack;
//     tempStack.top = NULL;
//     Product p;

//     while (!isEmpty(s)) {
//         p = pop(s);

//         // Move elements greater than p back to s
//         while (!isEmpty(&tempStack) && peek(&tempStack).prodQty > p.prodQty) {
//             push(s, pop(&tempStack));
//         }

//         // Push p in correct position
//         push(&tempStack, p);
//     }

//     // Move sorted elements back to original stack
//     while (!isEmpty(&tempStack)) {
//         push(s, pop(&tempStack));
//     }
// }

// =================== MAIN ===================
int main() {
    Stack s;
    initStack(&s);

    // Sample data
    Product p1 = {101, "Apple", 50};
    Product p2 = {102, "Banana", 20};
    Product p3 = {103, "Orange", 30};

    push(&s, p1);
    push(&s, p2);
    push(&s, p3);

    display(&s);

    sortStack(&s); // call sorting function

    printf("After sorting:\n");
    display(&s);

    return 0;
}

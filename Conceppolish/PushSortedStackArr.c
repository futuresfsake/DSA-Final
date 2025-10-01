#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

typedef char String[30];

// =================== DATA DEFINITIONS ===================
typedef struct {
    int prodID;
    String prodName;
    int prodQty;
} Product;

typedef struct {
    Product data[MAX];
    int top; // index of the top element, -1 if empty
} Stack;

// =================== FUNCTION DECLARATIONS ===================
void initializeStack(Stack *s) {
    s->top = -1;
}

bool isEmpty(Stack *s) {
    return s->top == -1;
}

bool isFull(Stack *s) {
    return s->top == MAX - 1;
}

// Normal push
void push(Stack *s, Product p) {
    if (isFull(s)) {
        printf("Stack Overflow!\n");
        return;
    }
    s->top++;
    s->data[s->top] = p;
    printf("%s pushed successfully!\n", p.prodName);
}

// Pop
Product pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow!\n");
        exit(1);
    }
    
    Product p;
   p =  s->data[s->top];
    s->top --;
    return p;
}

// Peek
Product peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        exit(1);
    }
    return s->data[s->top];
}

// Display stack
void displayStack(Stack *s) {
      if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return;
    }

    Stack temp;
    initializeStack(&temp);

    
    // Pop each element, print, and push onto temporary stack
    while (!isEmpty(s)) {
        Product p = pop(s);
        printf("ID: %d | Name: %s | Qty: %d\n",
               p.prodID, p.prodName, p.prodQty);
        push(&temp, p);
    }

    // Push elements back to original stack
    while (!isEmpty(&temp)) {
        push(s, pop(&temp));
    }
}

void pushSorted(Stack *s, Product p);

// // =================== PUSH SORTED ===================
// // Push a product while maintaining sorted order (descending by prodQty)
void pushSorted(Stack *s, Product p) {
   

    Stack temp;
    initializeStack(&temp);
    bool insert = false;

    
    while (!isEmpty(s)) {
        Product pp = pop(s);
        
        while (!insert &&  p.prodQty > pp.prodQty) {
            push(&temp, p);
            insert = true;
        } 
            push(&temp, pp);

    }


        if (!insert) {
            push(&temp, p);
        
    }

    while (!isEmpty(&temp)) {
        push(s, pop(&temp));
    }

}

// =================== MAIN ===================
int main() {
    Stack inventory;
    initializeStack(&inventory);

    Product p1 = {101, "Paracetamol", 3};
    Product p2 = {102, "Amoxicillin", 150};
    Product p3 = {103, "Vitamin C", 100};

   

    pushSorted(&inventory, p1);
    pushSorted(&inventory, p2);
    pushSorted(&inventory, p3);

    displayStack(&inventory);

    return 0;
}



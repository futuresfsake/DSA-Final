#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// ===== Node Struct =====
typedef struct node {
    int data;
    struct node *next;
} Node, *Stack;

void display(Stack s) {
    printf("Stack top -> ");
    while (s != NULL) {
        printf("%d -> ", s->data);
        s = s->next;
    }
    printf("NULL\n");
}
// ===== Interfaces =====
bool isEmpty(Stack s) {
    return (s == NULL);
}

bool push(Stack *s, int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return false;

    newNode->data = value;
    newNode->next = *s;  // new node points to old top
    *s = newNode;        // new node becomes top
    return true;
}

bool pop(Stack *s) {
    if (isEmpty(*s)) return false;

    int value;
    Node *temp = *s;
    value = temp->data;
    *s = temp->next;
    free(temp);
    return true;
}

Node* peek(Stack s) {
    if (isEmpty(s)) return NULL;  // always check NULL
    return s;
}


bool pushSorted_v2(Stack *s, int value);  // version 2
bool pushSorted_v1 (Stack *s, int value);

// ===== Main Function =====
int main() {
    Stack s1 = NULL;
Stack s2 = NULL;

pushSorted_v1(&s1, 15);
pushSorted_v1(&s1, 40);
pushSorted_v1(&s1, 25);
printf("After pushSorted_v1:\n");
display(s1);

pushSorted_v2(&s2, 15);
pushSorted_v2(&s2, 40);
pushSorted_v2(&s2, 25);
printf("After pushSorted_v2:\n");
display(s2);

    return 0;
}
bool pushSorted_v2(Stack *s, int value) {
   
    Node *NewNode = malloc(sizeof(Node));
    if (!NewNode) {
        printf("Dynamic Memory Allocation failed.\n");
        return false;
    }

    NewNode->data = value;
  
    
    Stack tempStack = NULL;
    Node *tempHolder;


    while (*s != NULL && (*s)->data < value) {
        tempHolder = *s;
        *s = tempHolder->next;
        
        
        tempHolder->next = tempStack;
        tempStack = tempHolder;
    }


    NewNode->next = *s;
    *s = NewNode;

    


    while (tempStack != NULL) {
        tempHolder = tempStack;
        tempStack = tempStack->next;



        tempHolder->next = *s;
        *s = tempHolder;
    }
    return true; // or false if failed
}



bool pushSorted_v1(Stack *s, int value) {
    Stack tempStack = NULL;
    

    

    // Move all smaller data to tempStack
    while (!isEmpty(*s)) {
        
        int topVal = (*s)->data;
        if (topVal < value) {
            pop(s);
            push(&tempStack, topVal);
            
            
        } else {
            break;
        }
    }

    // Insert new node in the correct position
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) {return false;}
    newNode->data = value;
    newNode->next = *s;
    *s = newNode;

    // Push back the smaller data
    while (!isEmpty(tempStack)) {
        Node* temp = peek(tempStack);
        
        push(s, temp->data);
        pop(&tempStack);
      
    }

    return true;
}

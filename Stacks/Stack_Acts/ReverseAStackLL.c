// ! two tempoerarys stack, and 1 original stack

// ? What is the problem?
//  TODO: Write a program to reverse the element
 // * Basic Logic : pop from the orig stack, then push to the temporary stack
 // * pop the element from the temp1 stack then push to the temp2 stack 
 // * pop from the temp2, then push it to the orig stack

 #include <stdio.h>
#include <stdlib.h>

// Node structure for Linked List Stack
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Stack structure (using linked list)
typedef struct {
    Node *top;
} StackLL;

// Function declarations
void initStackLL(StackLL *s);         // Initialize stack
int isEmptyLL(StackLL *s);            // Check if stack is empty
void pushLL(StackLL *s, int value);   // Push value
void popLL(StackLL *s);               // Pop value
int peekLL(StackLL *s);               // Peek top value
void displayLL(StackLL *s);           // Display stack (strict stack ops)
void reverseLL(StackLL *s);           // Reverse all data

int main() {
    StackLL s;
    initStackLL(&s);

    // Example usage
    pushLL(&s, 10);
    pushLL(&s, 20);
    pushLL(&s, 30);

    printf("Original Stack:\n");
    displayLL(&s);

    reverseLL(&s);
    printf("\nReversed Stack:\n");
    displayLL(&s);

    return 0;
}


void initStackLL(StackLL *s) {
   s->top = NULL;
}

int isEmptyLL(StackLL *s) {
   return s->top == NULL;
}


void pushLL(StackLL *s, int value) {
   Node *new = malloc(sizeof(Node));
   if (!new) {
      printf("Dynamic Memory Allocation failed.\n");
      return;
   }

   new->data = value;
   new->next = s->top;
   s->top = new;

} 



void popLL(StackLL *s){

   if (isEmptyLL(s)) {
      printf("Underflow");
      return;
   }
   
   Node *temp = s->top;
   s->top = temp->next;
   free(temp);


}

int peekLL(StackLL *s) {

   
   if (isEmptyLL(s)) {
      printf("Underflow");
      return -1;
   }

   return s->top->data;

}

void displayLL(StackLL *s) {
   StackLL tempStack;
   initStackLL(&tempStack);


     if (isEmptyLL(s)) {
      printf("Underflow");
      return;
   }

   while (s->top != NULL) {
      int x = peekLL(s);
      printf("%d ", x);
      popLL(s);
      pushLL(&tempStack, x);
   }

   while (tempStack.top != NULL) {
      int x1 = peekLL(&tempStack);
      popLL(&tempStack);
      pushLL(s, x1);

   }

}

void reverseLL(StackLL *s) {

   StackLL temp1;
   StackLL temp2;

   initStackLL(&temp1);
   initStackLL(&temp2);

   int a,b,c;
   
     if (isEmptyLL(s)) {
      printf("Underflow");
      return;
   }

   while(s->top != NULL) {
      a = peekLL(s);
      popLL(s);
      pushLL(&temp1, a);
   }


   while (temp1.top != NULL) {
      b = peekLL(&temp1);
      popLL(&temp1);
      pushLL(&temp2, b);
   }


     while (temp2.top != NULL) {
      c = peekLL(&temp2);
      popLL(&temp2);
      pushLL(s, c);
   }



}         

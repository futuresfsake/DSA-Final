#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 4



typedef int Data;

typedef struct {
    Data elems[MAX];
    int top;
} List;

void initStack (List *list);
bool push (List *list, Data elem);
bool pop (List *list);
Data peek (List list);
bool isFull (List list);
bool isEmpty (List list);
void display();
void visualize();

int main() {
     
    List list;
    initStack(&list);
    push(&list, 5);
    push(&list, 10);
    push(&list, 23);
    push(&list, 50);
    
    
    pop(&list);
    pop(&list);
    pop(&list);
    peek (list);
    
    
    if (isEmpty(list)) {
        printf("It is Empty!\n");
    } else {
        printf("It is not empty!\n");
    }
   
    if (isFull(list)) {
        printf("It is Full\n");
    } else {
        printf("It is not full\n");
    }
    
    display(list);
    visualize(list);
    return 0;
}




void initStack (List *list) {
    list->top = 0;
}

bool push (List *list, Data elem) {


    if (isFull(*list)) {
        return false;
    }
    
    list->elems[list->top] = elem;
    list->top++;
    return true;
}

bool pop (List *list) {
    if (isEmpty(*list)) { // ! *list, is just a pass by copy, just dereferemce, 
        // ! make the helper function accept pointers.
        // ! is u do &list, it is the address of the pointer, but the fucntion expects a List, not a **list
        return false;
    }
    
    list->top--;
    return true;
}


Data peek (List list) {
    if (isEmpty(list)) {
        exit(1);
    }
    return  list.elems[list.top -1];
}

bool isFull (List list) {
    return list.top == MAX;
}


bool isEmpty (List list) {
    return list.top == -1;
}


// ! this code breaks the principle of stacks. It is not legal to traverse.
// ! reason why it works, you are treating it as an array traversal, not a true abstract stack
// void display(List list) {  // ! started from the left to right
//     int i;
//     printf("Displayed Array: \n");
//     for( i = list.top; i >= 0; i--) {
//         printf("%d, ", list.elems[i]);
//     } 
    
// }

void visualize(List list) {
    printf("\nIdx | Value\n");
    for (int i = MAX - 1; i >= 0; i--) {
        if (i < list.top) {
            printf("%2d  | %d\n", i, list.elems[i]);
        } else {
            printf("%2d  | X\n", i);
        }
    }
    printf("\n");
}


// ! for display, not allowed to traverse
// ? The logic is to, print top, then pop the element,
void display(List list) {

    while (!isEmpty(list)) {
        printf("%d " ,peek(list));
        list.top--;
    }
}

// ! isEmpty and peek expect a list, while pop expects a List *, u are mixing styles
// ! its best if u decide all the helpers to accept a one style of parameters

// Either make all helpers 
// accept pointers (List *) — then you always pass list without *list. 
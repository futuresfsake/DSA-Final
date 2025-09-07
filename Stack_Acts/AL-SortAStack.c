#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// Stack structure using ArrayList
typedef struct {
    int arr[MAX];
    int top;
} StackAL;

// Basic operations
void initStackAL(StackAL *s) {
    s->top = -1;
}
int isEmptyAL(StackAL *s) {
    return s->top == -1;
}
int isFullAL(StackAL *s) {
    return s->top == MAX - 1;
}
void pushAL(StackAL *s, int value) {
    if (isFullAL(s)) {
        printf("Overflow\n");
        return;
    }
    s->arr[++s->top] = value;
}
int popAL(StackAL *s) {
    if (isEmptyAL(s)) {
        printf("Underflow\n");
        return -1;
    }
    return s->arr[s->top--];
}
int peekAL(StackAL *s) {
    if (isEmptyAL(s)) return -1;
    return s->arr[s->top];
}
void displayAL(StackAL *s) {
    printf("Stack (top -> bottom): ");
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->arr[i]);
    }
    printf("\n");
}

// Sorting function (to be implemented by you)
void sortStackAL(StackAL *s);

int main() {
    StackAL s;
    initStackAL(&s);

    pushAL(&s, 34);
    pushAL(&s, 3);
    pushAL(&s, 31);
    pushAL(&s, 98);
    pushAL(&s, 92);
    pushAL(&s, 23);

    printf("Original Stack:\n");
    displayAL(&s);

    sortStackAL(&s);  // <-- you will implement this

    printf("Sorted Stack:\n");
    displayAL(&s);

    return 0;
}


// void sortStackAL(StackAL *s) {
//     StackAL temp;
//     initStackAL(&temp);

//     int val = popAL(s);
//     pushAL(&temp, val);

//     while (!isEmptyAL(s)) {
//         int x = popAL(s);
//         if (x < val) {
//             pushAL(&temp, x);
           
//             int x2 = popAL(&temp);
//             pushAL(s, x2);
//         } else {
//             pushAL(&temp, popAL(&temp));
//     }



// }

// }


// void SortStackAL(StackAL *s) {

//     StackAL temp;
//     initStackAL(&temp);

//     pushAL(&temp, popAL(s));

//     while (!isEmptyAL(s)) {
//         int val = popAL(s);
//         if (val < peek(&temp)) {
//             push(s, pop(&temp));
//             push(&temp, val);
//         }
//     }

//     while (!isEmptyAL(&temp)) {
//         pushAL(s, popAL(&temp));
//     }

// }

void sortStackAL(StackAL *s) {

    StackAL temp;
    initStackAL(&temp);

    pushAL(&temp, popAL(s));

    while (!isEmptyAL(s)) {
        int val = popAL(s);
        
        while (!isEmptyAL(&temp) && val < peekAL(&temp)) {
            pushAL(s, popAL(&temp));
        }

        pushAL(&temp, val);

    }

    while (!isEmptyAL(&temp)) {
        pushAL(s, popAL(&temp));
    }

}
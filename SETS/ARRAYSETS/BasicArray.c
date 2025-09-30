#include <stdio.h>
#include <stdlib.h>

#define MAX 100   // maximum elements allowed in the set

// Structure for a Set
typedef struct {
    int data[MAX];   // array to store elements
    int size;        // current number of elements
} Set;

/* ============================
   Function Declarations
   ============================ */
// Initialization
void initialize(Set *s);
void makeNull(Set *s);

// Basic operations
int isMember(Set *s, int x);
void insert(Set *s, int x);
void delete(Set *s, int x);

// Utility for printing
void printSet(Set *s);

/* ============================
   Test Program (boilerplate)
   ============================ */
int main() {
    Set A;

    // Initialize set
    initialize(&A);
    printf("After initialize: ");
    printSet(&A);

    // Insert some elements
    insert(&A, 10);
    insert(&A, 20);
    insert(&A, 30);
    printf("After inserting 10, 20, 30: ");
    printSet(&A);

    // Check membership
    printf("Is 20 in the set? %s\n", isMember(&A, 20) ? "Yes" : "No");
    printf("Is 40 in the set? %s\n", isMember(&A, 40) ? "Yes" : "No");

    // Delete an element
    printf("Deleting 20...\n");
    delete(&A, 20);
    printSet(&A);

    // Make set null (clear all elements)
    printf("Making set null...\n");
    makeNull(&A);
    printSet(&A);

    return 0;
}

/* ============================
   Function Definitions (stubs)
   ============================ */



void initialize(Set *s) {
        // * set the size to 0 >> means the set is empty

    s->size = 0;
}

void makeNull(Set *s) {
    s->size = 0;
}


// * loop through all elements 0 to s->size
// * if data[i] == x, return 1;
// * if loop ends, return 0;

int isMember(Set *s, int x) {
    int found = 0; 
   for(int i = 0; i < s->size; i++) {
    if (s->data[i] == x) {
       found = 1;
    }
   }

   return found;
}


// * if isMemeber is true, do nothing,
// * otherwise, append x to data[size], and increase

void insert(Set *s, int x) {
    // placeholder

    if (isMember(s,x)) {
        printf("%d is already a member!\n", x);
    return;    } 
    else {
        s->data[s->size++] = x;
    }
    
}

// * find index i of x in the set, loop through
// * if found, shift all elements  after i one step left 
void delete(Set *s, int x) {
    // placeholder
    int found = 0;

    for(int i = 0; i < s->size; i++) {
        if (s->data[i] == x) {
            for(int j = i; j < s->size-1; j++) {
                s->data[j] = s->data[j+1];
            }
            s->size--;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("%d is not a member!", x);
    }
}
void printSet(Set *s) {
    printf("{ ");
    for (int i = 0; i < s->size; i++) {
        printf("%d ", s->data[i]);
    }
    printf("}\n");
}

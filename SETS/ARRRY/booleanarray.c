#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/* =========================
   Set Structure Definition
   ========================= */
typedef struct {
    int *elems;   // Boolean array (0/1 flags for membership)
    int max;      // maximum possible element
    int count;    // optional: track number of elements
} Set;

/* =========================
   Function Declarations
   ========================= */
Set createSet(int max);
void makeNull(Set *s);
bool addElement(Set *s, int item);
bool removeElement(Set *s, int item);
bool isElement(Set s, int item);
bool isSubset(Set a, Set b);
int cardinality(Set s);
Set assign(Set b);
int findMin(Set s);
int findMax(Set s);
bool isEqual(Set a, Set b);
Set unionSet(Set a, Set b);
Set intersectionSet(Set a, Set b);
Set difference(Set a, Set b);
Set symmetricDifference(Set a, Set b);
void display(Set s);

/* =========================
   Main Program (Test)
   ========================= */
int main() {
    Set A = createSet(10);
    Set B = createSet(10);

    // Add some elements
    addElement(&A, 1);
    addElement(&A, 3);
    addElement(&A, 5);
    addElement(&A, 7);

    addElement(&B, 3);
    addElement(&B, 4);
    addElement(&B, 7);
    addElement(&B, 9);

    printf("Set A: ");
    display(A);   // Expected: 1 3 5 7

    printf("Set B: ");
    display(B);   // Expected: 3 4 7 9

    printf("\nUnion (A & B): ");
    display(unionSet(A, B)); // Expected: 1 3 4 5 7 9

    printf("Intersection (A & B): ");
    display(intersectionSet(A, B)); // Expected: 3 7

    printf("Difference (A - B): ");
    display(difference(A, B)); // Expected: 1 5

    printf("Difference (B - A): ");
    display(difference(B, A)); // Expected: 4 9

    printf("Symmetric Difference (A & B): ");
    display(symmetricDifference(A, B)); // Expected: 1 4 5 9

    printf("\nCardinality of A: %d\n", cardinality(A)); // Expected: 4
    printf("Cardinality of B: %d\n", cardinality(B)); // Expected: 4

    printf("\nMin of A: %d\n", findMin(A)); // Expected: 1
    printf("Max of B: %d\n", findMax(B));   // Expected: 9

    printf("\nIs B subset of A? %s\n", isSubset(A, B) ? "Yes" : "No"); // Expected: No
    printf("Is {3,7} subset of A? %s\n",
           isSubset( intersectionSet(A,B), A) ? "Yes" : "No"); // Expected: Yes

    printf("\nAre A and B equal? %s\n", isEqual(A,B) ? "Yes" : "No"); // Expected: No

    // Test assign
    Set C = assign(A);
    printf("Set C (assigned from A): ");
    display(C); // Expected: 1 3 5 7

    // Test remove
    removeElement(&C, 5);
    printf("Set C after removing 5: ");
    display(C); // Expected: 1 3 7

    // Test makeNull
    makeNull(&C);
    printf("Set C after makeNull: ");
    display(C); // Expected: (empty line)

    return 0;
}


Set createSet(int max) {
    Set newSet;
    newSet.count = 0;
    newSet.max = max;
    newSet.elems = (int*)calloc(max, sizeof(int));
    if (!newSet.elems) {
        printf("Dynamic Memory Allocation failed.\n");
        exit(1);
    }

    return newSet;

}


void makeNull(Set *s) {

    // ! either free the array or loop through and set it to zero
    free(s->elems);
    s->elems = (int*)calloc(s->max, sizeof(int));
    s->count = 0;


    // ! different method
// *        for (int i = 0; i < s->max; i++) {
// *           s->elems[i] = 0;   
// *            }
// *        s->count = 0;

}


bool addElement(Set *s, int item) {

     if (!s || !s->elems) {
        printf("Set is not initialized properly!\n");
        return false;
    }
    
    if (item >= s->max) {
        printf("Insertion failed! %d out of range!\n", item);
        return false;
    }


     if (s->elems[item] == 1) {
        printf("Insertion failed! %d already exist!", item);
        return false;
    }

    s->elems[item] = 1;
    s->count++;
    return true;
}


bool removeElement(Set *s, int item) {

    if (item < s->max || s->elems[item] == 1) {
        s->elems[item] = 0;
        s->count--;
        printf("%d Successfully deleted!\n", item);
        return true;
    }

    printf("%d deletion failed.\n", item);
    return false;
}


bool isElement(Set s, int item) {
    
    if (item < s.max && s.elems[item] == 1) {
        return true;
    }
    return false;
}


bool isSubset(Set a, Set b) {
    for(int i = 0; i < a.max; i++) {
        if (a.elems[i] == 1) {
            if (i >= b.max || b.elems[i] == 0) {
                // * if b is too small or doesnt contain the elements
                return false;
            }
        }
    }

    return true;
}
int cardinality(Set s) {
    return s.count;
}

Set assign(Set b) {
    
    int size = b.max;
    Set newSet = createSet(size);

    for(int i = 0; i < size; i++) {
        newSet.elems[i] = b.elems[i];
        
    }
    newSet.count = b.count;
    return newSet;
}


int findMin(Set s) {
    for (int i = 0; i < s.max; i++) {
        if (s.elems[i] == 1) {
            return i;
        }
    }
    return -1;
}

int findMax(Set s) {

    for (int i = s.max -1; i >= 0; i--) {
        if (s.elems[i] == 1) {
            return i;
        }

        
    }
    return -1;

}



bool isEqual(Set a, Set b) {
    if (a.count != b.count) {
        return false;
    }

    for(int i = 0; i < a.max; i++) {
        if (a.elems[i] != b.elems[i]) {
            return false;
        }
    }

    return true;
}


Set unionSet(Set a, Set b) {
    int size = (a.max > b.max) ? a.max : b.max;
    Set newSet = createSet(size);

    for (int i = 0; i < size; i++) {
        if ((i <a.max && a.elems[i] == 1) || (i < b.max && b.elems[i] == 1)) {
            newSet.elems[i] = 1;
            newSet.count++;
        }

    }
    return newSet;

}
Set intersectionSet(Set a, Set b) {
    int size = (a.max > b.max) ? a.max : b.max;
    Set newSet = createSet(size);

    for (int i = 0; i < size; i++) {
        if ((i < a.max && a.elems[i] == 1) &&  (i < b.max && b.elems[i] == 1)) {
            newSet.elems[i] = 1;
            newSet.count++;
        }

    }
    return newSet;

}


Set difference(Set a, Set b) {
    int size = (a.max);
    Set newSet = createSet(size);

    
    for (int i = 0; i < size; i++ ) {
        if (i < a.max && a.elems[i]== 1 && (i >= b.max || b.elems[i] == 0)) {
            newSet.elems[i] = 1;
            newSet.count++;
        }
    }
    return newSet;
}
Set symmetricDifference(Set a, Set b) {
    return unionSet(difference(a, b), difference(b,a));
}


void display(Set s) {
    printf("{");
    for(int i = 0;  i < s.max; i++) {
       if (s.elems[i] == 1) {
        printf("%d ", i);
       }

    }
     printf("}\n");

}
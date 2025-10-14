// * Must enfore UID property, no duplicates,
// * optimized sorted-array way




#include <stdio.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int content[MAX];
    int count;  // number of elements
} Set;




// Initialize the set
void makeNull(Set *s) {

        s->count = 0;
}

// Check if x is already in the set
bool isMember(Set *s, int x) {
    
    for(int i = 0; i < s->count; i++) {
        if (x == s->content[i]) {
            return true;
        }
    }
    return false;
}

// Insert x into the set only if not already present (UID)
void insert(Set *s, int x) {
    if (isMember(s, x)) {
        printf("Value %d already exists.\n", x);
        return; 
}

    s->content[s->count++] = x;
}

// Display all elements in the set
void display(Set *s) {
    for(int i = 0; i < s->count; i++) {
        printf("%d ", s->content[i]);
    }
}

// // Set operations
Set setUnion(Set *A, Set *B) {
    Set unionSet;
    unionSet.count = 0;

    int a = 0;
    int b = 0; 

  

    
    while (a < A->count && b < B->count) {
        if (A->content[a] < B->content[b]) {
            unionSet.content[unionSet.count++] = A->content[a++];
            
        } else if (A->content[a] > B->content[b]) {
            unionSet.content[unionSet.count++] = B->content[b++];
           
        } else if (A->content[a] == B->content[b]) {
            unionSet.content[unionSet.count++] = A->content[a++];
            b++;
            
        }
    }

    while (a < A->count) {
        unionSet.content[unionSet.count++] = A->content[a++];
        
    }

    while (b < B->count) {
        unionSet.content[unionSet.count++] = B->content[b++];
        
    }
return unionSet;
    
}
Set setIntersection(Set *A, Set *B) {

    Set C;
    C.count = 0;
    int a = 0;
    int b = 0;

    while (a < A->count && b < B->count) {
        if (A->content[a] < B->content[b]) {
            a++;
        } else if (A->content[a] > B->content[b]) {
            b++;
        } else if (A->content[a] == B->content[b]) {
            C.content[C.count++] = A->content[a];
            a++;
            b++;
        }
    }

    return C;
}


Set setDifference(Set *A, Set *B) {
    Set C;
    C.count = 0;
    int a = 0;
    int b = 0;

    while (a < A->count && b < B->count) {
        if (A->content[a] < B->content[b]) {
            C.content[C.count++] = A->content[a++];
            
        } else if (A->content[a] > B->content[b]) {
            b++;
        } else if (A->content[a] == B->content[b]) {
            a++;
            b++;
        }
    }


    while (a < A->count) {
        C.content[C.count++] = A->content[a];
        a++;
    }
    return C;
}

int main() {
    Set chessClub, dramaClub, result, result1;

    makeNull(&chessClub);
    makeNull(&dramaClub);

    // Add some student IDs to chessClub
    insert(&chessClub, 101);
    insert(&chessClub, 102);
    insert(&chessClub, 103);

    // Add some student IDs to dramaClub
    insert(&dramaClub, 102);
    insert(&dramaClub, 104);
    insert(&dramaClub, 105);

    printf("Chess Club: ");
    display(&chessClub);

    printf("Drama Club: ");
    display(&dramaClub);

    // Practice: compute union, intersection, difference
    result = setUnion(&chessClub, &dramaClub);
    printf("\nUnion: ");
    display(&result);

    result1 = setIntersection(&chessClub, &dramaClub);
    printf("\nIntersection: ");
    display(&result1);

    Set result2 = setDifference(&chessClub, &dramaClub);
    printf("Chess - Drama: ");
    display(&result2);

    return 0;
}

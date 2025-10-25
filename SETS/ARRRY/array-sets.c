#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


#define MAX 20

// ===== NESTED STRUCT DEFINITION =====
typedef struct {
    char elements[MAX][50];  // Array of strings (unique elements)
} SetElements;

typedef struct {
    SetElements *elems;  // Pointer to SetElements struct
    int size;            // Number of elements in the set
} Set;

// ===== FUNCTION DECLARATIONS =====
void initSet(Set **S);
bool insert(Set **S, char *elem);
bool removeElem(Set **S, char *elem);
bool contains(Set **S, char *elem);
void display(Set **S);

Set* unionSet(Set **A, Set **B);
Set* intersectionSet(Set **A, Set **B);
Set* differenceSet(Set **A, Set **B);
Set* symmetricDifferenceSet(Set **A, Set **B);
bool isSubset(Set **A, Set **B);
bool isEqualSet(Set **A, Set **B);

// ===== MAIN DRIVER =====
int main() {
    Set *A, *B, *U, *I, *D, *SD;
    A = malloc(sizeof(Set));  // Allocate memory for sets
    B = malloc(sizeof(Set));
    
    initSet(&A);
    initSet(&B);

    // === Sample Inputs ===
    insert(&A, "apple");
    insert(&A, "banana");
    insert(&A, "mango");

    insert(&B, "banana");
    insert(&B, "cherry");
    insert(&B, "apple");

    printf("\nSET A = ");
    display(&A);
    printf("SET B = ");
    display(&B);

    // // === Operations ===
    U = unionSet(&A, &B);
    I = intersectionSet(&A, &B);
    D = differenceSet(&A, &B);
    SD = symmetricDifferenceSet(&A, &B);

    printf("\nUNION (A ∪ B) = ");
    display(&U);

    printf("INTERSECTION (A ∩ B) = ");
    display(&I);

    printf("DIFFERENCE (A - B) = ");
    display(&D);

    printf("SYMMETRIC DIFFERENCE (A △ B) = ");
    display(&SD);

    printf("\nA  a subset of B? %s\n", isSubset(&A, &B) ? "YES" : "NO");
    printf("A equal B? %s\n", isEqualSet(&A, &B) ? "YES" : "NO");

    // free(A);  // Free allocated memory
    // free(B);  // Free allocated memory
    // free(U);
    // free(I);
    // free(D);
    // free(SD);

    return 0;
}

// ===== FUNCTION DECLARATIONS =====
void initSet(Set **S) {
    *S = malloc(sizeof(Set));

    
   (*S)->elems = malloc(sizeof(SetElements)); // ! and malloc the array
   (*S)->size = 0;
   printf("Successfully initialized!\n");
}


bool insert(Set **S, char *elem) {

    if ((*S)->size == MAX) {
        return false;
    }

    for(int i = 0; i < (*S)->size; i++) {

       

        if (strcmp((*S)->elems->elements[i], elem) ==0) {
            printf("%s is already present on the list. Inserting failed!\n", elem);   
            return false;        
        } 
    }


    strcpy((*S)->elems->elements[(*S)->size], elem);
            (*S)->size++;
             return true;
}



bool removeElem(Set **S, char *elem) {
    
    if ((*S)->size == 0) {
        return false;
    }


    int index;
    for(int i = 0; i < (*S)->size; i++) {
        if (strcmp((*S)->elems->elements[i], elem) == 0) {
            index = i;

            for(int j = i; j < (*S)->size-1; j++) {
                strcpy((*S)->elems->elements[j], (*S)->elems->elements[j+1]);
            }

        (*S)->size--;
        return true;
        
        }
    }

    return false;
}


bool contains(Set **S, char *elem) {
    for(int i = 0; i < (*S)->size; i++) {
        if (strcmp((*S)->elems->elements[i], elem) == 0) {
            return true;
        }
    }

    return false;
}
void display(Set **S) {
    printf("{");
    for(int i = 0; i < (*S)->size; i++) {
        printf(" %s", (*S)->elems->elements[i]);
        if (i  != (*S)->size-1) {
            printf(",");
        }
    }

    printf("}\n");
}

Set* unionSet(Set **A, Set **B) {

    Set* newSet;
    initSet(&newSet);


    int i = 0;
    while (i < (*A)->size) {

        strcpy(newSet->elems->elements[newSet->size], (*A)->elems->elements[i]);
        newSet->size++;
        i++;

    }



      int ii = 0;
    while (ii < (*B)->size) {
        bool inC = false;
        char* a = ((*B)->elems->elements[ii]);

        
        for(int i = 0; i < newSet->size; i++) {
            if (strcmp(newSet->elems->elements[i], (*B)->elems->elements[ii])==0) {
                inC = true;
                break;
            }
        }

        if (!inC) {
            strcpy(newSet->elems->elements[newSet->size], (*B)->elems->elements[ii]);
            newSet->size++;
        }
        ii++;

    }

    return newSet;

}

Set* intersectionSet(Set **A, Set **B) {
    Set* newSet;
    initSet(&newSet);


    int i = 0;
    for(; i < (*A)->size; i++) {
        char* a = (*A)->elems->elements[i];

        bool inB = false;

        for(int j = 0; j < (*B)->size; j++) {
            char* b = (*B)->elems->elements[j];

            if (strcmp(a,b) == 0) {
                inB = true;
                break;
            }
        }

            if (inB) {
                strcpy(newSet->elems->elements[newSet->size], (*A)->elems->elements[i]);
                newSet->size++;
            }

        
      
    }

    return newSet;
}


Set* differenceSet(Set **A, Set **B) {
    Set* newSet;
    initSet(&newSet);


    int i = 0;
    for(; i < (*A)->size; i++) {
        char* a = (*A)->elems->elements[i];

        bool inB = false;

        for(int j = 0; j < (*B)->size; j++) {
            char* b = (*B)->elems->elements[j];

            if (strcmp(a,b) == 0) {
                inB = true;
                break;
            }
        }

            if (!inB) {
                strcpy(newSet->elems->elements[newSet->size], (*A)->elems->elements[i]);
                newSet->size++;
            }

        
      
    }

    return newSet;
}


Set* symmetricDifferenceSet(Set **A, Set **B) {

    Set*newSet;
    initSet(&newSet);

    for(int i = 0; i < (*A)->size; i++) {
        bool inB = false;
        


        for(int j = 0; j < (*B)->size; j++) {
            if (strcmp((*A)->elems->elements[i], (*B)->elems->elements[j]) ==0) {
                inB = true;
                break;
               
            }
        }

        if (!inB) {
            strcpy(newSet->elems->elements[newSet->size], (*A)->elems->elements[i]);
            newSet->size++;

        }
            
        }
    



    for(int k = 0; k < (*B)->size; k++) {
        bool inA = false;
        
        for(int j = 0; j < (*A)->size; j++) {
            if (strcmp((*B)->elems->elements[k], (*A)->elems->elements[j]) ==0) {
                inA = true;
                break;
            }

        }
            if (!inA) {


                
                strcpy(newSet->elems->elements[newSet->size], (*B)->elems->elements[k]);
                newSet->size++;


        }


    }
return newSet;
}

    
  





bool isSubset(Set **A, Set **B) {
    
    if ((*A)->size > (*B)->size) {
        return false;
    }


    
    for(int i = 0; i < (*A)->size; i++) {
        bool found = false;
        

        for(int j = 0; j < (*B)->size; j++) {
            if (strcmp((*A)->elems->elements[i], (*B)->elems->elements[j]) == 0) {
                found = true;
            }
        }

        if (!found) {
            return false;
        } 



    }

    return true;

   
}

bool isEqualSet(Set **A, Set **B) {
    if ((*A)->size != (*B)->size) {
        return false;
    }
    
    for(int i = 0; i < (*A)->size; i++) {
        bool notASubset = false;
        
        for(int j = 0; j < (*B)->size; j++) {
            if (strcmp((*A)->elems->elements[i], (*B)->elems->elements[j]) == 0) {
                notASubset = true;
            }

        }

        if (!notASubset) {
            return false;
        }

       
    }

    return true;

}

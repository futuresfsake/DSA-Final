#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define WORD_SIZE 32 
// *  each unsigned int has 32 bits 
// * this tells us how many elements fit in one word


# define MAX 100 // * assume all sets are in fixed size
// !  #define MAX 100 , you can do this if you want  a fixed size in all sets
// * maximum elements that a set can hold
// * used to calculate the size of the array of words


#define NUM_WORDS ((MAX + WORD_SIZE - 1)/WORD_SIZE)
// * calcualte the number of elements in the data[] array, or number of indeces


#define WORD_INDEX(x) ((x)/WORD_SIZE)
// * determines which word (array index) stores element x


#define BIT_INDEX(x) ((x)%WORD_SIZE)
// * determins which bit inside that word corresponds to element x


#define BIT_MASK(x)  (1U << BIT_INDEX(x))
// * creates a mask with only the bit for x set to 1



typedef struct {
    unsigned int data[NUM_WORDS];
    
   
}Set;



Set createSet ();
void Insert(Set *s, int x);
void MakeNull (Set *s);
void Remove (Set *s, int x);

int isMember (Set s, int x);

Set UnionSet (Set *a, Set *b);
Set IntersectionSet (Set *a, Set *b);
Set DifferenceSet (Set *a, Set *b);
Set AsymmDiffSet (Set *a, Set *b);
bool isEqualSet (Set *a, Set *b);
void printSet (Set s);


int main() {

    Set a = createSet();
    Set b = createSet();
    

    Insert(&a, 34);
    Insert(&a, 12);
    Insert(&a, 3);
    
    Insert(&a, 7);
    printf(" \n -- Set A Membership --\n");
    printSet(a);
    Remove(&a, 5);


    Insert(&b, 32);
    Insert(&b, 12);
    Insert(&b, 3);
    Insert(&b, 2);

    printf(" \n -- Set B Membership --\n");
    printSet(b);


    printf("\n--Union of Set A & Set B--\n");
    Set unionS = UnionSet(&a, &b);
    printSet(unionS);
   


    
      printf("\n--Intersection of Set A & Set B--\n");
    Set IntersectionS = IntersectionSet(&a, &b);
    printSet(IntersectionS);

    printf("\n--Difference of Set A & Set B--\n");
    Set Diffset = DifferenceSet(&a, &b);
    printSet(Diffset);
   


     printf("\n--Asymmetric Difference of Set A & Set B--\n");
    Set AsymSet1 = AsymmDiffSet(&a, &b);
    printSet(AsymSet1);
   


    printf("\n--ARE BOTH SETS EQUAL? ");
    if (isEqualSet(&a, &b)) {
        printf("YES!\n");
    } else printf("NO!\n");



}

Set createSet () {
    Set newSet;
        for(int i = 0; i < NUM_WORDS;i++ ) {
            newSet.data[i] = 0;
        }
    
        
        return newSet;

}


void Insert(Set *s, int item) {

    if (item >= MAX || item < 0) {
        printf("%d is out of bounds!", item);
        return;
    }

    // ! duplicate warning
    // if (s->data[WORD_INDEX(item)] & BIT_MASK(item)) {
    //     printf("%d is already present in the set!\n", item);
    //     return;
    // }

    s->data[WORD_INDEX(item)] |= BIT_MASK(item);
   
    return;
}

int isMember (Set s, int x) {
       if (x < 0 || x >= MAX) return 0; // ! always check bounds
    return (s.data[WORD_INDEX(x)] & BIT_MASK(x)) != 0;
}

void MakeNull (Set *s) {
    for(int i = 0; i < NUM_WORDS; i++) {
        s->data[i] = 0;      
    }
}

void printSet (Set s) {
    printf("{");
    for (int i = 0; i < MAX; i++) {
        if (isMember(s, i)) {
            printf("%d ", i);
            
        }

        
        
    }
    printf("}");
}



void Remove(Set *s, int x) {
    if (x < 0 || x >= MAX) return;

    if (!isMember(*s, x)) {
        printf("\n%d not found! Failed to remove\n", x);
        return;
    }
    
    s->data[WORD_INDEX(x)] &= ~BIT_MASK(x);
}



Set UnionSet (Set *a, Set *b) {

  
    Set newSet = createSet();


    for(int i = 0; i < NUM_WORDS; i++) {
        

         newSet.data[i] = a->data[i] | b->data[i];
        

    }

    return newSet;

    

}



Set IntersectionSet (Set *a, Set *b) {

    Set newSet = createSet();

    for(int i = 0; i < NUM_WORDS; i++) {
        newSet.data[i] = a->data[i] & b->data[i];
    }
    return newSet;
}

Set DifferenceSet (Set *a, Set *b) {

    Set newSet = createSet();
    for(int i = 0; i < NUM_WORDS; i++) {
       
        unsigned int wordA = a->data[i];
        unsigned int wordB = b->data[i];
        
        newSet.data[i] = wordA & ~ wordB;
    }

    return newSet;
}



Set AsymmDiffSet(Set *a, Set *b) {

    Set newSet = createSet();
    for(int i = 0; i < NUM_WORDS; i++) {
        newSet.data[i] = a->data[i] ^ b->data[i];
    }
    return newSet;
}


bool isEqualSet (Set *a, Set *b) {
    for(int i = 0; i < NUM_WORDS; i++) {

        if (a->data[i] != b->data[i]) {
            return false;
        }  
    }
    return true;
}
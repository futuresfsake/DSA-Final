
// *  Record each person's anwer, with a 10 question personality quiz
// * where each question is answered with only YES OR NO

// * char accepts small integers like 1 or 0
// * array bounds should be checked automatically
// * '\0' is for strings only, u should not use it for numeric arrays

// * {0} is already a way of initializing an array, it sets all the field to 0 automatically

// * always pass a structure by value, if you want to modify, use a poitner
// * always initialize, print characters & integers corectly


#include <stdio.h>
#include <stdbool.h>

/* =============================
   Structure Definition
   ============================= */
typedef struct {
    char answers[10];  // 10 yes/no answers (1 = yes, 0 = no)
} BitVect;


void setAnswer(BitVect* profile, int index, int value);
int getAnswer(BitVect profile, int index);
int countYesAnswers(BitVect profile);
void printAnswers(BitVect profile);
int compareProfiles(BitVect a, BitVect b);
BitVect unionProfiles(BitVect a, BitVect b);
BitVect intersectProfiles(BitVect a, BitVect b);
BitVect differenceProfiles(BitVect a, BitVect b);



void setAnswer(BitVect* profile, int index, int value) {
    // TODO: Set the answer to 1 or 0 for a given question
    
    if (index > 10 || index < 0) {
        printf("Index out of bounds.\n");
        return;
    }

    profile->answers[index] = value;
}

int getAnswer(BitVect profile, int index) {
    // TODO: Return the answer (1 or 0)
    
    return profile.answers[index];
}

int countYesAnswers(BitVect profile) {
    // TODO: Count how many answers are 1
    int count = 0;

    for(int i = 0; i < 10; i++) {
        if (profile.answers[i] == 1) {
            count++;
        }
    }
    return count;
}


// ! sample output, it should be reversed like the 8 bit 128, 64, 32, 16, 8, 4, 2, 1, 0 

void printAnswers(BitVect profile) {
    // TODO: Print all answers as binary (0/1)

    printf("{ ");
    for(int i = 9; i >= 0; i--) {
        printf("%d, ", profile.answers[i]);
        
    }

    printf("}\n");
}

int compareProfiles(BitVect a, BitVect b) {
    // TODO: Count how many answers match

    int A; 
    int B;
    int count = 0;
    
    for(int i = 0; i < 10; i++) {
        A = a.answers[i];
        B = b.answers[i];

        if (A == B) {
            count++;        
        }
    }
    return count;
}

BitVect unionProfiles(BitVect a, BitVect b) {
    // TODO: Combine answers (1 if either says yes)
    BitVect result = {0};

    char A;
    char B;
  

    // ! a.answers[i] != '\0' && b.answers[i] != '\0', is not safe, it stops the moment its 0

    for(int i = 0; i < 10; i++) {
        A = a.answers[i];
        B = b.answers[i];
        
        if (A == 1 || B == 1) {
            result.answers[i] = 1;

        } else {
            result.answers[i] = 0;

        }

        
    }
    return result;
}

BitVect intersectProfiles(BitVect a, BitVect b) {
    // TODO: Keep only common yes answers
    BitVect result = {0};

    for(int i = 0; i < 10; i++) {
        char A = a.answers[i];
        char B = b.answers[i];

        if (A == B) {
            result.answers[i] = A;
        }
    }


    return result;
}

BitVect differenceProfiles(BitVect a, BitVect b) {
    // TODO: Keep yes answers from a that are no in b
    BitVect result = {0};

    for(int i = 0; i < 10; i++) {
        char A = a.answers[i];
        char B = b.answers[i];

        if (A != B) {
            result.answers[i] = A;
        }
    }
    return result;
}


int main() {
    BitVect inie = {0}; // ! this is already a form of initializing, all fields are 0
    BitVect jobo = {0};

   setAnswer(&inie, 0, 1); // Q1: Yes
    setAnswer(&inie, 1, 1); // Q2: Yes
    setAnswer(&inie, 3, 1); // Q4: Yes
    setAnswer(&inie, 5, 1); // Q6: Yes
    setAnswer(&inie, 8, 1); // Q9: Yes
    setAnswer(&jobo, 0, 1); // Q1: Yes
    setAnswer(&jobo, 2, 1); // Q3: Yes
    setAnswer(&jobo, 4, 1); // Q5: Yes
    setAnswer(&jobo, 5, 1); // Q6: Yes
    setAnswer(&jobo, 6, 1); // Q7: Yes
    setAnswer(&jobo, 7, 1); // Q8: Yes

    printf("Inie's answers: ");
    printAnswers(inie);

    printf("Jobo's answers: ");
    printAnswers(jobo);

    printf("\nMatching answers: %d\n", compareProfiles(inie, jobo));

    printf("Jobo answered %s to question %d\n",
           (getAnswer(jobo, 0)) ? "yes" : "no", 1);

    printf("Jobo answered %s to question %d\n",
           (getAnswer(jobo, 1)) ? "yes" : "no", 2);

    printf("Inie said yes to %d questions\n\n", countYesAnswers(inie));

    BitVect unionSet = unionProfiles(inie, jobo);
    BitVect intersectSet = intersectProfiles(inie, jobo);
    BitVect diffSet = differenceProfiles(inie, jobo);

    printf("Union:        "); printAnswers(unionSet);
    printf("Intersection: "); printAnswers(intersectSet);
    printf("Difference:   "); printAnswers(diffSet);

    return 0;
}

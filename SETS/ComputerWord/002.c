// * same as personality test but in computer word

#include <stdio.h>


typedef short int CompWord;

void setAnswer(CompWord* profile, int index, int value);
int getAnswer(CompWord profile, int index);
int countYesAnswers(CompWord profile);
void printAnswers(CompWord profile);
int compareProfiles(CompWord a, CompWord b);
CompWord unionProfiles(CompWord a, CompWord b);
CompWord intersectProfiles(CompWord a, CompWord b);
CompWord differenceProfiles(CompWord a, CompWord b);

int main() {
    CompWord inie = 0;
    CompWord jobo = 0;

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

    printf("Jobo answered %s to question %d\n",(getAnswer(jobo,0))?"yes":"no",1);
    printf("Jobo answered %s to question %d\n",(getAnswer(jobo,1))?"yes":"no",2);
    printf("Inie said yes to %d questions\n\n", countYesAnswers(inie));

	CompWord unionSet = unionProfiles(inie, jobo);
	CompWord intersectSet = intersectProfiles(inie, jobo);
	CompWord diffSet = differenceProfiles(inie, jobo);

	printf("Union:        "); printAnswers(unionSet);
	printf("Intersection: "); printAnswers(intersectSet);
	printf("Difference:   "); printAnswers(diffSet);

	return 0;
}



// void setAnswer(CompWord* profile, int index, int value) {
//    if (value) {
//     *profile |= (1u<<index);
//    }  
// }


// int getAnswer(CompWord profile, int index) {
   
//         return (profile >> index) & 1U;
    
// }

// int countYesAnswers(CompWord profile) {
//     int count = 0;
//     for(int i = 0; i < 8; i++) {
//         count+=(profile>>i) & 1U;

        
//     }
//     return count;
// }
// void printAnswers(CompWord profile) {
//     printf("{");
//     for(int i = 9-1; i >= 0; i--) {
//         printf("%d ", (profile>>i) & 1U);
//     }
//      printf("}\n");
// }
// int compareProfiles(CompWord a, CompWord b) {
//     CompWord bothYes = a&b;

//     return countYesAnswers(bothYes);
// }

// CompWord unionProfiles(CompWord a, CompWord b) {
//     return a | b;
// }
// CompWord intersectProfiles(CompWord a, CompWord b) {
//   return  a & b;
// }
// CompWord differenceProfiles(CompWord a, CompWord b) {
//     return a &(~b);
// }




void setAnswer(CompWord* profile, int index, int value) {
    if (value)
        *profile |= (1u << index);
    else
        *profile &= ~(1u << index);
}

int getAnswer(CompWord profile, int index) {
    return (profile >> index) & 1U;
}

int countYesAnswers(CompWord profile) {
    int count = 0;
    for (int i = 0; i < 9; i++) {
        count += (profile >> i) & 1U;
    }
    return count;
}

void printAnswers(CompWord profile) {
    // print from bit 8 down to bit 0 (Q9 → Q1)
    for (int i = 10-1; i >= 0; i--) {
        printf("%d", (profile >> i) & 1U);
    }
    printf("\n");
}

int compareProfiles(CompWord a, CompWord b) {
    int match = 0;
    for (int i = 0; i < 10; i++) {
        int bitA = (a >> i) & 1U;
        int bitB = (b >> i) & 1U;
        if (bitA == bitB) match++;
    }
    return match;
}

CompWord unionProfiles(CompWord a, CompWord b) {
    return a | b;
}

CompWord intersectProfiles(CompWord a, CompWord b) {
    return a & b;
}

CompWord differenceProfiles(CompWord a, CompWord b) {
    return a & (~b);
}
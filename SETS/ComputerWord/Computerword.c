// * test your knowledge again

#include <stdio.h>

typedef short int CompWord;

// Function prototypes
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

    // Example of how to call (you can edit/remove later)
    // setAnswer(&inie, 0, 1);
    // setAnswer(&jobo, 1, 1);

    printf("Inie's answers: ");
    printAnswers(inie);

    printf("Jobo's answers: ");
    printAnswers(jobo);

    printf("\nMatching answers: %d\n", compareProfiles(inie, jobo));

    printf("Jobo answered %s to question %d\n", (getAnswer(jobo, 0)) ? "yes" : "no", 1);
    printf("Jobo answered %s to question %d\n", (getAnswer(jobo, 1)) ? "yes" : "no", 2);
    printf("Inie said yes to %d questions\n\n", countYesAnswers(inie));

    CompWord unionSet = unionProfiles(inie, jobo);
    CompWord intersectSet = intersectProfiles(inie, jobo);
    CompWord diffSet = differenceProfiles(inie, jobo);

    printf("Union:        ");
    printAnswers(unionSet);
    printf("Intersection: ");
    printAnswers(intersectSet);
    printf("Difference:   ");
    printAnswers(diffSet);

    return 0;
}

// --- Function Definitions ---

void setAnswer(CompWord* profile, int index, int value) {
    // TODO: implement setting bit
}

int getAnswer(CompWord profile, int index) {
    // TODO: implement getting bit value
    return 0;
}

int countYesAnswers(CompWord profile) {
    // TODO: implemen

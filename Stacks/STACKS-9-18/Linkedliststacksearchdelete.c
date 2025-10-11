#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// =================== DATA DEFINITIONS ===================
typedef struct {
    char Lname[20];
    char Fname[20];
    char Mi;
} NameType;

typedef struct {
    NameType name;
    int ID;
    char Course[20];
    int YrLvl;
} Studtype;

typedef struct node {
    Studtype stud;
    struct node *next;
} Node, *NodePtr;

typedef struct {
    NodePtr top;   // points tLo top of stack
} StudList;


// =================== FUNCTION DECLARATIONS ===================
void initialize(StudList *s);
bool isEmpty(StudList *s);
void push(StudList *s, Studtype stud);
Studtype pop(StudList *s);
Studtype peek(StudList *s);
void displayStudList(StudList *s);
bool deleteStud(StudList *s, int ID);
void sortById(StudList *s);
StudList filterStuds(StudList *s, char course[]);


// =================== MAIN ===================
int main() {
    StudList students;
    initialize(&students);

    Studtype s1 = {{"Garcia", "Juan", 'D'}, 1001, "BSCS", 1};
    Studtype s2 = {{"Santos", "Maria", 'L'}, 1034, "BSIT", 2};
    Studtype s3 = {{"Reyes", "Carlos", 'M'}, 1042, "BSIS", 3};
    Studtype s4 = {{"Cruz", "Ana", 'B'}, 1034, "BSCS", 4};
    Studtype s5 = {{"Lopez", "Jose", 'R'}, 1005, "BSIT", 1};
    Studtype s6 = {{"Fernandez", "Luis", 'A'}, 1055 ,"BSIS", 2};
    Studtype s7 = {{"Torres", "Elena", 'C'}, 1012, "BSCS", 3};
    Studtype s8 = {{"Mendoza", "Paolo", 'F'}, 1010, "BSIT", 4};
    Studtype s9 = {{"Diaz", "Sofia", 'E'}, 1002, "BSCS", 1};
    Studtype s10 = {{"Ramos", "Miguel", 'G'}, 1019, "BSIS", 2};

    push(&students, s1);
    push(&students, s2);
    push(&students, s3);
    push(&students, s4);
    push(&students, s5);
    push(&students, s6);
    push(&students, s7);
    push(&students, s8);
    push(&students, s9);
    push(&students, s10);

    printf("-- Student List --\n");
    displayStudList(&students);

    printf("\n\n---- PEEK ----\n");
    Studtype stud1 = peek(&students);
    printf("Peek Stud: %s || ID: %d\n", stud1.name.Lname, stud1.ID);

    printf("\n\n---- POP ----\n");
    Studtype stud = pop(&students);
    printf("Successfully popped: %s || ID: %d\n", stud.name.Lname, stud.ID);

    printf("\n\n---- DELETE SEARCH ----\n");
    int id = 1002;
    if (deleteStud(&students, id)) {
        printf("Student %d is successfully deleted.\n", id);
    } else {
        printf("Student %d not found. Deletion failed.\n", id);
    }

    printf("\n\n---- DISPLAYING ----\n");
    displayStudList(&students);

    printf("\n-- Sort Students BY ID --\n");
    sortById(&students);
    displayStudList(&students);

    printf("\n-- Filtering Students (BSIT) --\n");
    StudList newStuds = filterStuds(&students, "BSIT");
    displayStudList(&newStuds);

    return 0;
}


// =================== FUNCTION DECLARATIONS ===================
void initialize(StudList *s) {
    s->top = NULL;
}
bool isEmpty(StudList *s) {
   return s->top == NULL;
}


void push(StudList *s, Studtype stud) {

    NodePtr newStud = malloc(sizeof(Node));
    if (!newStud) {
        printf("Dynamic Memory Allocation.\n");
        exit(1);
    }


    newStud->stud = stud;
    newStud->next = NULL;
    if (isEmpty(s)) {
        s->top = newStud;
    } else {
        newStud->next = s->top;
        s->top = newStud;
    }



}

Studtype pop(StudList *s) {
    
    if (isEmpty(s)) {
        printf("Student list is empty!.\n");
    exit(1);
    }


    NodePtr remove = s->top;
    Studtype stud = remove->stud;
    s->top = remove->next;
    free(remove);
    return stud;

}


Studtype peek(StudList *s) {
    if (isEmpty(s)) {
        printf("Student list is empty!\n");
        exit(1);
    }
     return s->top->stud;
}


void displayStudList(StudList *s) {
    StudList tempStack;
    initialize(&tempStack);

    while (!isEmpty(s)) {
        Studtype stud = pop(s);
        printf("Name: %-20s || Course: %-20s || ID: %5d  \n", stud.name.Lname, stud.Course, stud.ID);
        push(&tempStack, stud);
    }

    while (!isEmpty(&tempStack)) {
        push(s, pop(&tempStack));
    }
}


bool deleteStud(StudList *s, int ID) {
    
    if (isEmpty(s)) {
        return false;
    }
    StudList temp;
    temp.top = NULL;
    NodePtr tempHolder = NULL;
    StudList Remove;
    Remove.top = NULL;
    int found = 0;
    while (s->top != NULL) {
        tempHolder = s->top;
        
        s->top = tempHolder->next;
        if (tempHolder->stud.ID != ID) {
            

            tempHolder->next = temp.top;
            temp.top = tempHolder;

        }

       else {
        tempHolder->next = Remove.top;
        Remove.top = tempHolder;
        found = 1;
       }
        
    
    }
    while (temp.top != NULL) {
        tempHolder = temp.top;
        temp.top = tempHolder->next;


        tempHolder->next = s->top;
        s->top = tempHolder;
    }
    return found;
}
void sortById(StudList *s) {

    StudList temp;
    initialize(&temp);
    NodePtr tempHolder = NULL;

    while (!isEmpty(s)) {
       
     Studtype stud = pop(s);

        while (!isEmpty(&temp) && peek(&temp).ID > stud.ID) {
            push(s, pop(&temp));
        }
        push(&temp, stud );

    }

    while (!isEmpty(&temp)) {
        push(s, pop(&temp));
    }


}
StudList filterStuds(StudList *s, char course[]) {
    
    StudList tempStack;
    initialize(&tempStack);
    NodePtr tempHolder = NULL;
    StudList temp;
    initialize(&temp);

    while (s->top != NULL) {
        tempHolder = s->top;
        s->top = tempHolder->next;

        if (strcmp(tempHolder->stud.Course, course) ==0) {
            tempHolder->next = tempStack.top;
            tempStack.top = tempHolder;
        } else {
            push(&temp, tempHolder->stud);

        }

    }

    return tempStack;
}

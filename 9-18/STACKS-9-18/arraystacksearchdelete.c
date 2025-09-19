#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define size 15

typedef struct {
    char Lname[20];
    char Fname[20];
    char Mi;
}NameType;

typedef struct {
    NameType name;
     int ID;
    char Course[20];
    int YrLvl;
} Studtype, *StudPtr;

typedef struct {
    Studtype StudArray[size];
    int count;
}StudList, *ListPtr;


// * AL
void initialize(StudList *s);
bool isFull(StudList *s);
bool isEmpty(StudList *s);
void push(StudList *s, Studtype stud);
Studtype peek (StudList *s);
Studtype pop(StudList *s);
void displayStudList (StudList *s);
bool deleteStud (StudList *s, int ID);




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


printf("-- Student List--\n");
displayStudList(&students);


printf("\n\n----PEEEK----\n\n");
Studtype stud1 = peek(&students);
printf("Peek Stud: %s || ID: %d\n\n ", stud1.name.Lname, stud1.ID );

printf("\n\n----POP----\n\n");
Studtype stud = pop(&students);
printf("\n\nSuccessfully popped: %s ID: %d\n", stud.name.Lname, stud.ID );


printf("\n\n----DELETE SEARCH----\n\n");
    int id = 1002;
if (deleteStud(&students, id)) {
    printf("Student %d is successfully deleted.\n", id );
} else {
    printf("Student %d not found. Deletion failed..\n", id);
}
    

printf("\n\n----DISPLAYING----\n\n");
displayStudList(&students);
    

}

void initialize(StudList *s) {
    s->count = -1;

}

bool isFull(StudList *s) {
    return s->count == size -1;
}

bool isEmpty(StudList *s) {
    return s->count == -1;
}


void push(StudList *s, Studtype stud) {
    if (isFull(s)) {
        printf("Student List is already full.\n");
        exit(1);
    }

    s->count++;
    s->StudArray[s->count] = stud;
   
}


Studtype peek (StudList *s) {

    if (isEmpty(s)) {
        printf("Student List is empty!\n");
    }
    return s->StudArray[s->count];
}

Studtype pop(StudList *s) {
    if (isEmpty(s)) {
        printf("Nothing to pop. List is empty.\n");
        exit(1);
    }

    Studtype removed = s->StudArray[s->count];
    s->count--;
    return removed;
}


void displayStudList (StudList *s) {
    if (isEmpty(s)) {
        exit(1);
    }

    StudList tempStack;
    initialize(&tempStack);


    while (!isEmpty(s)) {
        Studtype stud = pop(s);
        printf("Name: %s %s     || Course: %s   || Year Level: %d   || ID: %d \n", stud.name.Lname, stud.name.Fname,
             stud.Course, 
             stud.YrLvl, stud.ID);
             push(&tempStack, stud);
    }


    while (!isEmpty(&tempStack)) {
        push(s, pop(&tempStack));
    }


}


bool deleteStud (StudList *s, int ID) {
        StudList tempStack;
    initialize(&tempStack);
    StudList delete;
    initialize(&delete);

    int found = 0;

    while (!isEmpty(s)) {
        Studtype stud = pop(s);
        if (stud.ID != ID) {
            push(&tempStack, stud);
        
        }  else {
            found = 1;
             push(&delete, stud);
        }

       
    }


    while (!isEmpty(&tempStack)) {
        push(s, pop(&tempStack));
    }

    return found;

}



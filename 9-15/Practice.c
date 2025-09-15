#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char fName[100];
    char lName[100];
} Name;
typedef struct {
    Name studName;
    int year;
    char program[50];
    char sex[50];
} Student;

typedef struct node {
    Student studs;
    struct node *next;
} StudentType, *StudentPtr, *StackList;


bool isEmptyStack();
bool pushStack();
bool popStack();
Student peekStack();
void displayStudentListVersion2();
void initStack();
void displayStudentListVersion1(StackList *s);

int countStudentsVersion1();
int countStudentsVersion2();


int main() {
    StackList studList;
    studList = NULL;
    
       Student s1 = {{"Juan", "Dela Cruz"}, 1, "BS Computer Science", "Male"};
    Student s2 = {{"Maria", "Santos"}, 2, "BS Information Technology", "Female"};
    Student s3 = {{"Pedro", "Reyes"}, 3, "BS Software Engineering", "Male"};
    Student s4 = {{"Ana", "Lopez"}, 1, "BS Information Systems", "Female"};
    Student s5 = {{"Jose", "Garcia"}, 4, "BS Computer Engineering", "Male"};
    Student s6 = {{"Luisa", "Torres"}, 2, "BS Data Science", "Female"};
    Student s7 = {{"Miguel", "Flores"}, 3, "BS Multimedia Arts", "Male"};

    // Push students onto the stack
    pushStack(&studList, s1);
    pushStack(&studList, s2);
    pushStack(&studList, s3);
    pushStack(&studList, s4);
    pushStack(&studList, s5);
    pushStack(&studList, s6);
    pushStack(&studList, s7);


    printf("--Version 1--\n");
    displayStudentListVersion1(&studList);
        printf("--Version 2--\n");

    displayStudentListVersion2(&studList);


    int countv1 = countStudentsVersion1(&studList);
    printf("Count of Version 1: %d\n ",countv1 );
    
    int countv2 = countStudentsVersion2(&studList);
        printf("Count of Version 2: %d\n ",countv2 );

}


bool isEmptyStack(StackList s) {
    return s == NULL;
}

bool pushStack(StackList *s, Student stud) {

    StudentPtr student = malloc(sizeof(StudentType));
    if (!student) {
        printf("Dynamic Memory Allocation failed.\n");
        return false;
    }

    student->studs = stud;
    student->next = *s;
    *s = student;

    return true;
    
}


bool popStack(StackList *s) {
    if (*s == NULL) { // ? if i do if *s is NULL am I dereferncing it? which is going to be wrong
        return false;
    }

    StudentType *toRemove;

    toRemove = *s;
    *s = toRemove->next;
    free(toRemove);

    return true;




}


Student peekStack(StackList *s) {
    return (*s)->studs;
}
void displayStudentListVersion1(StackList *s) {

    StackList tempStack = NULL;
    StudentPtr stud;


    while (*s != NULL) {
        stud = *s;
        *s = stud->next;

        printf("Name: %s, %s || Program: %s\n", stud->studs.studName.lName,
             stud->studs.studName.fName,
            stud->studs.program);

            stud->next = tempStack;
            tempStack = stud;


    }

    while (tempStack != NULL) {
        stud = tempStack;
        tempStack = stud->next;

        stud->next = *s;
        *s = stud;
    }

}

void displayStudentListVersion2 (StackList *s) {
    StackList tempStack;
    initStack(&tempStack);

    while (!isEmptyStack(*s)) {
        Student stud = peekStack(s);
        printf("Name: %s, %s || Program: %s\n", 
            stud.studName.lName, 
            stud.studName.fName,
             stud.program);
             popStack(s);
             pushStack(&tempStack, stud);
    }

    while (!isEmptyStack(tempStack)) {
        Student temp = peekStack(&tempStack);
        popStack(&tempStack);
        pushStack(s, temp);
    }

}


void initStack(StackList *s) {
    *s = NULL; // ! we are dereferencing
}

int countStudentsVersion1(StackList *s) {
    int count = 0;
    StackList tempStack = NULL;
    StudentPtr stud;


    while (*s != NULL) {
        stud = *s;
        *s = stud->next;
        
        count++;


        stud->next = tempStack;
        tempStack = stud;


    }

    while (tempStack != NULL) {
        stud = tempStack;
        tempStack = stud->next; // ! whats wrong if i do tempStack->next?


        stud->next = *s;
        *s = stud;
    }

    return count;
    
}
int countStudentsVersion2(StackList *s) {
    int count = 0;
    StackList tempStack;
    initStack(&tempStack);


    while (!isEmptyStack(*s)) {
        count++;
        Student stud = peekStack(s);
        popStack(s);
        pushStack(&tempStack, stud);

    }

    while (!isEmptyStack(tempStack)) {
        Student s1 = peekStack(&tempStack);
        popStack(&tempStack);
        pushStack(s, s1);
    }
    return count;
}

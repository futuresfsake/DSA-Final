// ! creates a dictionary store student grades using open hashing

// ! very simple dictionary, no pointer to pointer node

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>



#define TABLE_SIZE 5


typedef struct node  {
    char Name[100];
    int Grade;
    struct node* next;

}Student;

Student* HashTables[5];



void insertStudent(char Name[], int grade);
Student* searchStudent(char Name[]);
void display();
int HashKey(char Name[]);
void Remove(char Name[]);


int main() {

    insertStudent("Chelsea", 90);
    insertStudent("Bubu", 100);
    insertStudent("Noynoy", 75);
    insertStudent("Krishy", 100);

    display();

    Student *search = searchStudent("Chelsea");
    if (search) {
        printf("Student Found: %s with grade %d\n", search->Name, search->Grade);
    } else {
        printf("Student not found\n");
    }

}

int HashKey(char Name[]) {
    int sum = 0;
    for(int i = 0; Name[i] != '\0'; i++) {
        sum+=Name[i];
    }

   return sum % TABLE_SIZE;
}


void insertStudent(char name[], int grade) {

    int newIndex = HashKey(name);


    Student *new = malloc(sizeof(Student));
    if (!new) {
        printf("Dynamic Memory Allocation failed.\n");
        return;
    }

    strcpy(new->Name, name);
    new->Grade = grade;
    new->next = HashTables[newIndex]; // ! head insertion for chaiining
    HashTables[newIndex] = new;


    // ! no need to check if HashTables is NULL, it works the same way
    

    
//     if (HashTables[newIndex] == NULL) {
//         HashTables[newIndex] = new;
//    } else {
//     new->next = HashTables[newIndex];
//    }


    
 }



 Student* searchStudent(char Name[]) {

    int index = HashKey(Name);

    Student* temp = HashTables[index];

    while (temp != NULL) {
        if (strcmp(temp->Name, Name) == 0) {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
 }

 
void display() {
    for(int i = 0; i < TABLE_SIZE; i++) {
        printf("Index = %d ->", i);
        Student* temp = HashTables[i];

        if (temp == NULL) {
            printf(" EMPTY\n");

        }
        while (temp != NULL) {
            printf("{%s, %d} ->", temp->Name, temp->Grade);
            if (temp->next == NULL) {
                printf("NULL\n");
            }
            temp = temp->next;
        } 

    }

}



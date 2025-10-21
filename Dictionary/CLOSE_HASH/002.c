#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

// Represents one slot in the hash table
typedef struct {
    char studentName[30];
    int grade;
    int occupied; // 0 = empty, 1 = filled
} Record;

// The dictionary structure
typedef struct {
    Record table[MAX];
} GradeBook;

// Function declarations
unsigned int hash(char *key) {
    unsigned int sum = 0; 
    for(int i = 0; key[i] != '\0'; i++) {
        sum+=key[i];
    }
    return (sum+31) % MAX;
}
void initGradeBook(GradeBook *book) {
    for(int i = 0; i < MAX; i++) {
        book->table[i].occupied = 0;
        book->table[i].grade = 0;
        strcpy(book->table[i].studentName, "");
    }
}

void addStudent(GradeBook *book, char *name, int grade) {
    unsigned int index = hash(name);
    for(int i = 0; i < MAX; i++) {
        index = (index + i*i) % MAX;

        if (book->table[index].occupied == 1 && strcmp(book->table[index].studentName, name)==0) {
            printf("%s is already existing in the list...\n", name);
            return;
        } else if (book->table[index].occupied == 0) {
            strcpy(book->table[index].studentName, name);
            book->table[index].occupied = 1;
            book->table[index].grade = grade;
            printf("%s successfully added!\n", name);
            return;
        }
        }

        printf("List is full. Unable to add %s.\n", name);
    }



int findGrade(GradeBook *book, char *name) {
    unsigned int idx = hash(name);

    for(int i = 0; i < MAX; i++) {
        idx = (idx + i *i) % MAX;

        if (book->table[idx].occupied && strcmp(book->table[idx].studentName, name)==0)
        return book->table[idx].grade;
    }

    return -1;
}


void removeStudent(GradeBook *book, char *name) {
    unsigned int idx = hash(name);

    for(int i = 0; i < MAX; i++) {
        idx = (idx + i * i) % MAX;

        if (book->table[idx].occupied && strcmp(book->table[idx].studentName, name)==0) {
            book->table[idx].grade = 0;
            book->table[idx].occupied = 0;
            strcpy(book->table[idx].studentName, "");
            printf("%s successfully found & deleted\n", name);
        }
    }
    printf("%s not found...\n", name);
}


void displayGrades(GradeBook *book) {
    for(int i = 0; i < MAX; i++) {
        printf("%2d ", i+1);
        if (book->table[i].occupied == 0) {
            printf("[EMPTY]\n");
        } else {
            printf("[%s, %d]\n", book->table[i].studentName, book->table[i].grade);
        }
    }
}
int main() {
    GradeBook gb;
    initGradeBook(&gb);

    addStudent(&gb, "Alice", 95);
    addStudent(&gb, "Bob", 87);
    addStudent(&gb, "Clara", 92);
    addStudent(&gb, "David", 80);

    printf("\nAfter insertions:\n");
    displayGrades(&gb);

    // Search
    char nameToFind[] = "Bob";
    int grade = findGrade(&gb, nameToFind);
    if (grade != -1)
        printf("\n%s’s grade is %d.\n", nameToFind, grade);
    else
        printf("\n %s not found in gradebook.\n", nameToFind);

    // Deletion
    char nameToRemove[] = "Alice";
    removeStudent(&gb, nameToRemove);

    printf("\nAfter removing %s:\n", nameToRemove);
    displayGrades(&gb);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int id;
    char title[100];
    char author[50];
    Date publish_date;
} Book;

typedef struct {
    Book *books;
    int count;
    int max;
} Library;

// Function Prototypes
Date createDate(int d, int m, int y) {
    Date tempDate;
    tempDate.day = d;
    tempDate.month = m;
    tempDate.year = y;

    return tempDate;
}

bool isEmpty(Library *L) {
    return L->count == 0;
}
bool isFull(Library *L) {
    return L->count == L->max;
}
void makeNULL(Library *L) {
    L->count = -1;
    L->max = -1;
}
Book createBook() {
     Book newBook;

    printf("Enter Book ID: ");
    scanf("%d", &newBook.id);

    printf("Enter Book Title: ");
    scanf(" %[^\n]", newBook.title); // allow spaces

    printf("Enter Author: ");
    scanf(" %[^\n]", newBook.author);

    int d, m, y;
    printf("Enter Publish Date (DD MM YYYY): ");
    scanf("%d %d %d", &d, &m, &y);

    newBook.publish_date = createDate(d, m, y);

    return newBook;
}

void addBook(Library *lib, Book b) {
    if (isFull(lib)) {
        printf("Library is full!\n");
        exit(1);
    } 
    lib->books[lib->count] = b;
    lib->count++;
    printf("%d is successfully added!\n", b.id);

}

Book removeBook(Library *lib, int bookId) {

    int count;
    for(int i = 0; i < lib->count; i++) {
        if (bookId == lib->books[i].id) {
            count = i;
            Book ToRemove = lib->books[i];


            for(int j = count; j < lib->count; j++) {
                lib->books[j] = lib->books[j+1];
                lib->count--;
            }

            return ToRemove;
        }

       
    }

     Book Notfound;
        Notfound.id = -1;
        return Notfound;
}



void displayBookInfo(Book b) {
    printf("ID: %d,  Title: %s \n", b.id, b.title);
}

int main() {
    Library L;
    L.count = 0;
    L.max = 10;
    L.books = malloc(sizeof(Book) * L.max);

    // Pre-populated books
    Book b1 = {101, "The C Programming Language", "Kernighan & Ritchie", {22, 2, 1978}};
    Book b2 = {102, "Clean Code", "Robert C. Martin", {1, 8, 2008}};
    Book b3 = {103, "Introduction to Algorithms", "Cormen et al.", {15, 9, 2009}};

    // Call your functions here once you define them
    addBook(&L, b1);
    addBook(&L, b2);
    addBook(&L, b3);

    Book removed = removeBook(&L, 103);
    if (removed.id > 0) {
        printf("Book '%s' removed successfully!\n", removed.title);
    } else {
        printf("Book not found...\n");
    }

    for(int i = 0; i < L.count; i++) {
        displayBookInfo(L.books[i]);
    }

    return 0;
}

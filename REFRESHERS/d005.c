/*
==============================================================
        LIBRARY BOOK TRACKER (OPEN HASHING)
==============================================================

STORY:
You are building a library system for tracking borrowed books.
Each book has a unique ISBN (key). When a book is borrowed for
the first time, the system records its information from the 
library database (simulated via fetch_book_info).

The system tracks:
 - title
 - author
 - number of times borrowed

Special rules:
 - If a book is borrowed more than 10 times, it becomes 
   "popular".
 - Certain books can be archived if not borrowed for a long time.
 - All operations use OPEN HASHING (separate chaining).

You need to implement the following four operations:
1) init_library      : initialize the hash table
2) borrow_book       : record a book being borrowed
3) lookup_book       : find a book by ISBN
4) mark_archived     : remove old books from the table

==============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUCKETS 53   // Prime number for hash distribution

typedef struct BookEntry {
    char *isbn;            // Key
    char *title;
    char *author;
    int borrowed_count;
    bool popular;
    bool archived;         // true if archived
    struct BookEntry *next;
} BookEntry;

typedef struct {
    BookEntry *buckets[BUCKETS];
} LibraryTable;

// ---------------- FUNCTION PROTOTYPES ----------------

void init_library(LibraryTable *lib);                       // Initialize all buckets to NULL
BookEntry *lookup_book(LibraryTable *lib, const char *isbn); // Return pointer to book or NULL
bool borrow_book(LibraryTable *lib, const char *isbn);       // Record borrowing, fetch info if new
void mark_archived(LibraryTable *lib);                       // Archive books borrowed <3 times

unsigned int hash_isbn(const char *isbn);
void print_library(LibraryTable *lib);                       // Provided for testing
void free_library(LibraryTable *lib);

// Simulate fetching title and author for a given ISBN
void fetch_book_info(const char *isbn, char **title, char **author) {
    *title = malloc(100);   // Allocate space for title
    *author = malloc(100);  // Allocate space for author
    sprintf(*title, "Book Title for ISBN %s", isbn);
    sprintf(*author, "Author for ISBN %s", isbn);
}


// ---------------- IMPLEMENTATION SPACES ----------------

void init_library(LibraryTable *lib) {
    // Guide: Loop through all BUCKETS, set each bucket to NULL
    for(int i = 0; i < BUCKETS; i++) {
        lib->buckets[i] = NULL;
    }
}

BookEntry *lookup_book(LibraryTable *lib, const char *isbn) {


    int index = hash_isbn(isbn);
    BookEntry* trav = lib->buckets[index];
    for(; trav != NULL; trav = trav->next) {
        if (strcmp(trav->isbn, isbn) == 0)
        return trav;
    }


    return NULL;
}

bool borrow_book(LibraryTable *lib, const char *isbn) {
    // Guide:
    // 1. If book exists, increment borrowed_count, set popular if >10
    // 2. If book not found, fetch info using fetch_book_info(), create new node, insert at head

    int index = hash_isbn(isbn);
    BookEntry* trav = lib->buckets[index];
    
    for(; trav != NULL; trav = trav->next) {
        if (strcmp(trav->isbn, isbn) == 0) {
            trav->borrowed_count++;

            if (trav->borrowed_count > 10) {
                
                trav->popular = true;
            }
            return true;
        }
    }
     

    char* title;
    char* author;
   fetch_book_info(isbn, &title, &author);
    BookEntry* book = malloc(sizeof(BookEntry));
    if (!book) return false;


    book->isbn = malloc(strlen(isbn)+1);
    book->title = malloc(strlen(title)+1);
    book->author = malloc(strlen(author)+1);
    strcpy(book->isbn, isbn);
    strcpy(book->title, title);
    strcpy(book->author, author);
    book->borrowed_count = 1;
    book->popular = false;
    book->archived = false;
    book->next = lib->buckets[index];
    lib->buckets[index] = book;

    free(title);
    free(author);


    return true;
}

void mark_archived(LibraryTable *lib) {
    // Guide:
    // Loop over all buckets
    // For each book with borrowed_count <3, set archived = true or remove from table

    for(int i = 0; i < BUCKETS; i++) {
        BookEntry** trav = &(lib->buckets[i]);

        for(; *trav != NULL;  trav = &(*trav)->next) {
            if ((*trav)->borrowed_count < 3) {
                (*trav)->archived = true;
                
                
            }
        }
    }
}

// ---------------- HELPER FUNCTIONS ----------------

unsigned int hash_isbn(const char *isbn) {
    unsigned long h = 5381;
    int c;
    while ((c = *isbn++)) {
        h = ((h << 5) + h) + c;
    }
    return h % BUCKETS;
}



void print_library(LibraryTable *lib) {
    printf("\n======= Library Table =======\n");
    for (int i = 0; i < BUCKETS; i++) {
        BookEntry *trav = lib->buckets[i];
        if (trav) {
            printf("[Bucket %d]\n", i);
            while (trav) {
                printf(" %s | %s | Borrowed: %d | Archived: %s\n",
                       trav->isbn, trav->title, trav->borrowed_count,
                       trav->archived ? "YES" : "NO");
                trav = trav->next;
            }
        }
    }
    printf("=============================\n");
}

void free_library(LibraryTable *lib) {
    // Guide: Loop through all buckets, free nodes and dynamically allocated strings

    for(int i = 0; i < BUCKETS; i++) {
        BookEntry* temp = lib->buckets[i];

        while (temp != NULL) {
            BookEntry* current = temp;
            temp = current->next;
            free(current);

        }
    }
}
int main() {
    LibraryTable lib;
    init_library(&lib);

    borrow_book(&lib, "978-3-16-148410-0");
    borrow_book(&lib, "978-3-16-148410-0");
    borrow_book(&lib, "978-0-262-13472-9");
    borrow_book(&lib, "978-3-16-148410-0");
    borrow_book(&lib, "978-3-16-148410-0");


    printf("Before archiving:\n");
    print_library(&lib);

    mark_archived(&lib);

    printf("After archiving:\n");
    print_library(&lib);

    free_library(&lib);
    return 0;
}

#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100

typedef struct {
    char author[50];
    char isbn[20];
} BookMeta;

typedef struct {
    char title[100]; // Ordering Basis
    BookMeta meta;
} BookNode;

typedef struct {
    BookNode shelf[MAX_BOOKS];
    int count;
} LibraryHeap;

// Prototypes
void initLibrary(LibraryHeap* h);
void addBook(LibraryHeap* h, char* title, char* author, char* isbn);
BookNode getNextBook(LibraryHeap* h);
void heapifyUp(LibraryHeap* h, int index);
void heapifyDown(LibraryHeap* h, int index);
int isEmpty(LibraryHeap* h);
// Display the current state of the heap array (Breadth-first view)
void displayLibrary(LibraryHeap* h) {
    

    printf("\n--- Current Heap Structure (Array View) ---\n");
    printf("%-5s | %-30s | %s\n", "Index", "Title", "Author");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < h->count; i++) {
        printf("%-5d | %-30s | %s\n", 
            i, 
            h->shelf[i].title, 
            h->shelf[i].meta.author);
    }
    printf("------------------------------------------------------------\n\n");
}

int main() {
    LibraryHeap lib;
    initLibrary(&lib);

    printf("=== Library Catalog (MinHeap: A-Z) ===\n");
    addBook(&lib, "The Great Gatsby", "F. Scott Fitzgerald", "12345");
    addBook(&lib, "A Tale of Two Cities", "Charles Dickens", "67890"); // Should come out 1st
    addBook(&lib, "Moby Dick", "Herman Melville", "11122");
    addBook(&lib, "Hamlet", "Shakespeare", "33344");


    // displayLibrary(&lib);

    printf("Catalog Listing:\n");
    while(!isEmpty(&lib)) {
        BookNode b = getNextBook(&lib);
        printf("- %s by %s\n", b.title, b.meta.author);
    }
    return 0;
}

// --- IMPLEMENTATION ---

void initLibrary(LibraryHeap* h) {
    // TODO: Set count to 0
    h->count = 0;
}



//! when using heapify up as a helper funciton, u insert, increment, then call the function

void addBook(LibraryHeap* h, char* title, char* author, char* isbn) {
    // TODO: 
    // 1. Insert at bottom.
    // 2. Bubble Up: Swap if strcmp(parent.title, current.title) > 0 (MinHeap)

    int child, pr;
    if (h->count == MAX_BOOKS) return;

    child = h->count;
    pr = (child-1)/2;

    // while (child > 0 && strcmp(h->shelf[pr].title, title) >0) {
    //     h->shelf[child] = h->shelf[pr];
    //     child = pr;
    //     pr = (child-1)/2;
    // }

    strcpy(h->shelf[child].title, title);
    strcpy(h->shelf[child].meta.isbn, isbn);
    strcpy(h->shelf[child].meta.author, author);
    h->count++;

    heapifyUp(h, child);

    
}

BookNode getNextBook(LibraryHeap* h) {
    // TODO: 
    // 1. Save root.
    // 2. Move last node to root.
    // 3. Bubble Down: Swap with smaller child (strcmp)
    BookNode dummy = {0};
    if (h->count == 0) return dummy;


    int child, pr;

    BookNode root, swap;

    root = h->shelf[0];
    h->shelf[0] = h->shelf[h->count-1];
    h->count--;

    pr = 0;
    child = 2 * pr +1;

    
    heapifyDown(h, pr);
    return root;

}

void heapifyUp(LibraryHeap* h, int index) {
    // TODO: Recursive or Iterative Upward Fix


    int child, pr;

    child = index;
    pr = (child-1)/2;


    while (child > 0 && strcmp(h->shelf[pr].title,h->shelf[child].title) > 0 ) {
        BookNode swap = h->shelf[pr];
        h->shelf[pr] = h->shelf[child];
        h->shelf[child] = swap;

        child = pr;
        pr = (child-1)/2;
    }

}

void heapifyDown(LibraryHeap* h, int index) {
    // TODO: Recursive or Iterative Downward Fix

    int child, pr;

     pr = index;
    child = (2 * pr +1);


    while (child < h->count) {
        if (child +1 < h->count && strcmp(h->shelf[child+1].title, h->shelf[child].title)<0) {
            child++;
    }

    if (strcmp(h->shelf[pr].title, h->shelf[child].title) > 0) {
        BookNode swap = h->shelf[pr];
        h->shelf[pr] = h->shelf[child];
        h->shelf[child] = swap;

        pr = child;
        child = 2 * pr +1;
    } else {
        break;
    }
}
}

int isEmpty(LibraryHeap* h) {
    // TODO: Check if count == 0
    return h->count == 0;
}
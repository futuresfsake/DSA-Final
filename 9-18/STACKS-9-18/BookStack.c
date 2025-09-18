#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// =================== DATA DEFINITIONS ===================
typedef char String[50];

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    int bookID;
    String title;
    String author;
    Date returnDate;
} Book;

typedef struct {
    Book books[50];
    int count;
} BookList;

// =================== STACK DEFINITIONS ===================
typedef struct node {
    Book book;
    struct node *link;
} NodeType, *NodePtr;

typedef struct {
    NodePtr top;
    int count;
} ReturnStack;

// =================== FUNCTION DECLARATIONS ===================
Date createDate(int d, int m, int y);
Book createBook(int id, String title, String author, Date rd);
void displayDate(Date d);
void displayBook(Book b);

void initStack(ReturnStack *s);
bool isEmpty(ReturnStack s);
bool push(ReturnStack *s, Book b);
bool pop(ReturnStack *s);
Book peek(ReturnStack s);
void visualize(ReturnStack s);

void createAndPopulate(BookList *blist, int n);

// ==== SPECIAL OPERATION ====
// 👉 You will implement this:
bool addBookBasedOnReturnDate(ReturnStack *s, Book b);

// =================== DATA FUNCTIONS ===================
Date createDate(int d, int m, int y) {
    Date date = {d,m,y};
    return date;
}

Book createBook(int id, String title, String author, Date rd) {
    Book b;
    b.bookID = id;
    strcpy(b.title, title);
    strcpy(b.author, author);
    b.returnDate = rd;
    return b;
}

void displayDate(Date d) {
    printf("%02d/%02d/%04d", d.day, d.month, d.year);
}

void displayBook(Book b) {
    printf("%03d | %-20s | %-15s | ", b.bookID, b.title, b.author);
    displayDate(b.returnDate);
    printf("\n");
}

int compareDate(Date d1, Date d2) {
    if (d1.year != d2.year) return d1.year - d2.year;
    if (d1.month != d2.month) return d1.month - d2.month;
    return d1.day - d2.day;
}

void createAndPopulate(BookList *blist, int n) {
      blist->count = 0;

    Book temp[] = {
        createBook(1, "Noli Me Tangere", "Rizal", createDate(10, 9, 2025)),
        createBook(2, "El Filibusterismo", "Rizal", createDate(5, 9, 2025)),
        createBook(3, "Florante at Laura", "Balagtas", createDate(20, 8, 2025)),
        createBook(4, "Ibong Adarna", "Anonymous", createDate(30, 7, 2025)),
        createBook(5, "Dekada 70", "Lualhati Bautista", createDate(15, 9, 2025)),
        createBook(6, "Banaag at Sikat", "Lope K. Santos", createDate(1, 10, 2025)),
        createBook(7, "Mga Ibong Mandaragit", "Amado V. Hernandez", createDate(12, 11, 2025)),
        createBook(8, "Sa mga Kuko ng Liwanag", "Edgardo M. Reyes", createDate(25, 12, 2025)),
        createBook(9, "Po-on", "F. Sionil Jose", createDate(3, 1, 2026)),
        createBook(10, "Tree", "F. Sionil Jose", createDate(9, 2, 2026)),
        createBook(11, "My Brother, My Executioner", "F. Sionil Jose", createDate(15, 3, 2026)),
        createBook(12, "Mass", "F. Sionil Jose", createDate(22, 4, 2026)),
        createBook(13, "Gagamba", "F. Sionil Jose", createDate(5, 5, 2026)),
        createBook(14, "The Pretenders", "F. Sionil Jose", createDate(17, 6, 2026)),
        createBook(15, "Women in the Marketplace", "F. Sionil Jose", createDate(30, 7, 2026)),
        createBook(16, "Subversive Lives", "Susan Quimpo", createDate(8, 8, 2026)),
        createBook(17, "America is in the Heart", "Carlos Bulosan", createDate(19, 9, 2026)),
        createBook(18, "Bulaklak ng City Jail", "Lualhati Bautista", createDate(12, 10, 2026)),
        createBook(19, "Gapo", "Lualhati Bautista", createDate(23, 11, 2026)),
        createBook(20, "Smaller and Smaller Circles", "F.H. Batacan", createDate(14, 12, 2026)),
        createBook(21, "Ilustrado", "Miguel Syjuco", createDate(2, 1, 2027)),
        createBook(22, "Empire of Memory", "Eric Gamalinda", createDate(11, 2, 2027)),
        createBook(23, "Salvage in the Age of Disaster", "Kristine Ong Muslim", createDate(27, 3, 2027)),
        createBook(24, "State of War", "Ninotchka Rosca", createDate(9, 4, 2027)),
        createBook(25, "Twilight in Djakarta", "Mochtar Lubis", createDate(21, 5, 2027))
    };

    int totalBooks = sizeof(temp) / sizeof(temp[0]);

    for (int i = 0; i < n && i < totalBooks; i++) {
        blist->books[blist->count++] = temp[i];
    }
}
// =================== STACK FUNCTIONS ===================
void initStack(ReturnStack *s) {
    s->top = NULL;
    s->count = 0;
}

bool isEmpty(ReturnStack s) {
    return s.top == NULL;
}

bool push(ReturnStack *s, Book b) {
    NodePtr newNode = malloc(sizeof(NodeType));
    if (!newNode) return false;
    newNode->book = b;
    newNode->link = s->top;
    s->top = newNode;
    s->count++;
    return true;
}

bool pop(ReturnStack *s) {
    if (isEmpty(*s)) return false;
    NodePtr temp = s->top;
    s->top = temp->link;
    free(temp);
    s->count--;
    return true;
}

Book peek(ReturnStack s) {
    return s.top->book;
}

void visualize(ReturnStack s) {
    NodePtr trav = s.top;
    printf("\n--- RETURN STACK ---\n");
    while(trav) {
        displayBook(trav->book);
        trav = trav->link;
    }
    printf("Count: %d\n", s.count);
}

// 👉 You will implement this part
    // Example rules you can try:
    // - If book is returned late -> put on TOP
    // - If book is returned on time -> put at BOTTOM
    // - If stack exceeds 10 -> reject
// =================== SPECIAL OPERATION ===================
bool addBookBasedOnReturnDate(ReturnStack *s, Book b) {

    ReturnStack tempStack;
    tempStack.top = NULL;
    tempStack.count = 0;

    NodePtr tempHolder = NULL;

    NodePtr newBook = malloc(sizeof(NodeType));
    if (!newBook) {
        printf("Dynamic Memory Allocation failed.\n");
        exit(1);
    }

    newBook->book = b;
    newBook->link = NULL;

  
    if (s->count + 1 > 10) {
        return false;
    }

   
    while (s->top != NULL && compareDate(s->top->book.returnDate,b.returnDate) <0 ) {
        tempHolder = s->top;
        s->top = tempHolder->link;


        tempHolder->link = tempStack.top;
        tempStack.top = tempHolder;
        
    }

    newBook->link = s->top;
    s->top = newBook;
    s->count++;

    while (tempStack.top != NULL) {
        tempHolder = tempStack.top;
        tempStack.top = tempHolder->link;


        tempHolder->link = s->top;
        s->top = tempHolder;
    }


    return true;
}

// =================== MAIN ===================
int main() {
    BookList bl;
    int n;

    printf("Enter number of books to simulate return (max 5): ");
    scanf("%d", &n);

    createAndPopulate(&bl, n);

    ReturnStack rs;
    initStack(&rs);

    printf("\nBOOKS BEING RETURNED:\n");
    for(int i = 0; i < bl.count; i++) {
        displayBook(bl.books[i]);
    }

    for(int i = 0; i < bl.count; i++) {
        printf("\nAdding %s (%d): %s\n",
            bl.books[i].title,
            bl.books[i].bookID,
            addBookBasedOnReturnDate(&rs, bl.books[i]) ? "Success":"Fail");
        visualize(rs);
    }

    return 0;
}

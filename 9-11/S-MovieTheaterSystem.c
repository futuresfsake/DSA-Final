#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ===== Movie Struct =====
typedef struct {
    int movieId;
    char title[50];
    char genre[30];
    float ticketPrice;
    bool showing;
} Movie;

// ===== ArrayList for Movies =====
typedef struct {
    Movie *arr;
    int count;
    int max;
} MovieList;

// ===== Reservation Stack (Linked List) =====
typedef struct resNode {
    int resId;
    Movie bookedMovie;
    char customerName[50];
    int tickets;
    struct resNode *next;
} ResNode, *ResPtr;

typedef struct {
    ResPtr top;
    int size;
} ReservationStack;


// ================= ArrayList (Movies) =================

Movie createMovie(int id, const char *title, const char *genre, float price, bool show) {
    Movie m;
    m.movieId = id;
    strcpy(m.title, title);
    strcpy(m.genre, genre);
    m.ticketPrice = price;
    m.showing = show;
    return m;
}

void initMovieList(MovieList *ml, int max) {
    ml->arr = malloc(sizeof(Movie) * max);
    ml->count = -1;
    ml->max = max;
}

bool isMovieListEmpty(MovieList *ml) {
    return ml->count == -1;
}

bool isMovieListFull(MovieList *ml) {
    return ml->count == ml->max - 1;
}

void addMovie(MovieList *ml, Movie m) {
    if (!isMovieListFull(ml)) {
        ml->count++;
        ml->arr[ml->count] = m;
    }
}

Movie popMovie(MovieList *ml) {
    Movie temp = ml->arr[ml->count];
    ml->count--;
    return temp;
}

void showMovies(MovieList ml) {
    MovieList temp;
    initMovieList(&temp, ml.max);
    printf("%-10s%-25s%-15s%-15s%-10s\n", "ID", "Title", "Genre", "Price", "Showing");
    while (!isMovieListEmpty(&ml)) {
        Movie m = popMovie(&ml);
        printf("%-10d%-25s%-15s%-15.2f%-10s\n", m.movieId, m.title, m.genre, m.ticketPrice, m.showing ? "Yes" : "No");
        addMovie(&temp, m);
    }
    while (!isMovieListEmpty(&temp)) addMovie(&ml, popMovie(&temp));
}

// ===== Special ArrayList Operations (Declarations Only) =====
Movie removeMovie(MovieList *ml, int id) {
    MovieList movie, remove;
    initMovieList(&movie, ml->max);
    initMovieList(&remove, ml->max);
    Movie toRemove;

    while (!isMovieListEmpty(ml)) {
        Movie temp = popMovie(ml); {
            if (temp.movieId != id) {
                addMovie(&movie, temp);
            } else {
                addMovie(&remove, temp);
                popMovie(&remove);
                
                 toRemove = temp;
            }
        }
    }

    while (!isMovieListEmpty(&movie)) {
        addMovie(ml, popMovie(&movie));
    }

    return toRemove;


}
Movie findCheapestShowing(MovieList ml) {
    MovieList movie;
    initMovieList(&movie, ml.max);

    Movie cheapest;
    cheapest.movieId = -1;

    while (!isMovieListEmpty(&ml)) {
        Movie tempMovie = popMovie(&ml);
        if (tempMovie.showing) {
            if (cheapest.movieId == -1 || tempMovie.ticketPrice < cheapest.ticketPrice) 
            {
                cheapest = tempMovie;
            }

        }
        addMovie(&movie, tempMovie);
    }
    while (!isMovieListEmpty(&movie)) {
        addMovie(&ml, popMovie(&movie));
    }
    return cheapest;
}

MovieList countGenre(MovieList ml, const char *genre) {

    MovieList Action;
    initMovieList(&Action, ml.max);
    MovieList all;
    initMovieList(&all, ml.max);

    while (!isMovieListEmpty(&ml)) {
        Movie temp = popMovie(&ml);
        if (strcmp(temp.genre, genre) == 0) {
            addMovie(&Action, temp);
            addMovie(&all, temp);
        } else {
            addMovie(&all, temp);
        }
    }
    
    while (!isMovieListEmpty(&all)) {
        addMovie(&ml, popMovie(&all));
    }

    return Action;

}


// ================= Reservation Stack (Linked List) =================

void initReservationStack(ReservationStack *st) {
    st->top=NULL;
    st->size=0;
}

bool isResStackEmpty(ReservationStack *st) {
    return st->top==NULL;
}

void pushReservation(ReservationStack *st, Movie m, const char *cust, int tickets, int id) {
    ResPtr node=malloc(sizeof(ResNode));
    node->resId=id;
    node->bookedMovie=m;
    strcpy(node->customerName,cust);
    node->tickets=tickets;
    node->next=st->top;
    st->top=node;
    st->size++;
}

ResNode popReservation(ReservationStack *st) {
    ResPtr rem=st->top;
    ResNode r=*rem;
    st->top=rem->next;
    free(rem);
    st->size--;
    return r;
}

void showReservations(ReservationStack st) {
    ReservationStack temp;
    initReservationStack(&temp);
    while (!isResStackEmpty(&st)) {
        ResNode r=popReservation(&st);
        printf("ResID: %d Customer: %s Tickets: %d Movie: %s\n",r.resId,r.customerName,r.tickets,r.bookedMovie.title);
        pushReservation(&temp,r.bookedMovie,r.customerName,r.tickets,r.resId);
    }
    while (!isResStackEmpty(&temp)) {
        ResNode r=popReservation(&temp);
        pushReservation(&st,r.bookedMovie,r.customerName,r.tickets,r.resId);
    }
}

// ===== Special Stack Operations (Declarations Only) =====
ResPtr peekLatestReservation(ReservationStack st) {
     return st.top;
}
float calculateTotalSales(ReservationStack st) {

    ReservationStack MovieStack;
    initReservationStack(&MovieStack);
    float  sum = 0;

    while (!isResStackEmpty(&st)) {
        ResNode movie = popReservation(&st);
        if (movie.bookedMovie.showing == true) {
            sum+= movie.bookedMovie.ticketPrice * movie.tickets;
        }
        pushReservation(&MovieStack, movie.bookedMovie, movie.customerName, movie.tickets, movie.resId);
    }

    while (!isResStackEmpty(&MovieStack)) {
        ResNode m = popReservation(&MovieStack);
        pushReservation(&st, m.bookedMovie, m.customerName, m.tickets, m.resId);
    }
    return sum;

    
}

int countReservationsByMovie(ReservationStack st, int movieId) {
    ReservationStack movie;
    initReservationStack(&movie);

    int count = 0;
    while (!isResStackEmpty(&st)) {
        ResNode temp = popReservation(&st);
        if (temp.bookedMovie.movieId == movieId) {
            count += temp.tickets;
        }
        
    }
    return count;

}

int main() {
    MovieList ml;
    initMovieList(&ml,10);
    addMovie(&ml,createMovie(1,"Avengers","Action",300.0,true));
    addMovie(&ml,createMovie(2,"Frozen","Animation",150.0,false));
    addMovie(&ml,createMovie(3,"Titanic","Romance",200.0,true));
    addMovie(&ml,createMovie(4,"Inception","SciFi",280.0,true));
    addMovie(&ml, createMovie(5, "The Dark Knight", "Action", 350.0, true));
    addMovie(&ml, createMovie(6, "The Lion King", "Animation", 200.0, true));
    addMovie(&ml, createMovie(7, "Interstellar", "SciFi", 320.0, true));
    addMovie(&ml, createMovie(8, "Avatar", "Action", 400.0, false));

    printf("\n--- Movies ---\n");
    showMovies(ml);

    printf("\nMovies after removing ID: 3\n");
    removeMovie(&ml, 3);
    showMovies(ml);

    Movie cheapest = findCheapestShowing(ml);
    if (cheapest.movieId != -1) {
        printf("\nCheapest Movie: %s with the price of %.2f\n", cheapest.title, cheapest.ticketPrice);
    } else {
        printf("\nNo movies currently showing.\n");
    }

    printf("\nAll the Action Movies: \n");
    MovieList action = countGenre(ml, "Action");
    showMovies(action);

    // ================= Stack Operations =================
    printf("\n--- Reservations (Stack) ---\n");
    ReservationStack rs;
    initReservationStack(&rs);

    // Populate stack
    pushReservation(&rs, ml.arr[0], "Alice", 3, 1001);   // Avengers
    pushReservation(&rs, ml.arr[1], "Bob", 2, 1002);     // Frozen
    pushReservation(&rs, ml.arr[2], "Charlie", 5, 1003); // Inception
    pushReservation(&rs, ml.arr[3], "Diana", 1, 1004);   // The Dark Knight

    // Show reservations
    showReservations(rs);

    // Peek latest reservation
    ResPtr latest = peekLatestReservation(rs);
    if (latest != NULL) {
        printf("\nLatest Reservation -> ID: %d, Customer: %s, Movie: %s\n",
               latest->resId, latest->customerName, latest->bookedMovie.title);
    }

    // Calculate total sales
    float totalSales = calculateTotalSales(rs);
    printf("\nTotal Sales (only showing movies): %.2f\n", totalSales);

    // Count reservations for Avengers (id=1)
    int countAvengers = countReservationsByMovie(rs, 1);
    printf("Number of reservations for Avengers: %d\n", countAvengers);

    return 0;
}

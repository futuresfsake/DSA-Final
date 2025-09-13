#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ===== Car Struct (data to push) =====
typedef struct {
    char plate[20];
    char brand[30];
    char model[30];
    int year;
    float pricePerDay;
} Car;


// ================= ARRAYLIST-BASED STACK =================
typedef struct {
    Car *arr;
    int top;
    int max;
} ArrayStack, *ArrayStackPtr;

// ---- ArrayStack Operations ----
void initArrayStack(ArrayStackPtr st, int max) {
    st->top = -1;
    st->max = max;
    st->arr = malloc(sizeof(Car)*st->max);
    // TODO: initialize stack
}

bool isFullArray(ArrayStackPtr st) {
    return st->top == st->max -1;
}

bool isEmptyArray(ArrayStackPtr st) {
    return st->top == -1;
}

void pushArray(ArrayStackPtr st, Car c) {
    if (isFullArray(st)) {
        printf("Car list is full.\n");
        return;
    } 
    

    st->top++;
    st->arr[st->top] = c;
}

Car popArray(ArrayStackPtr st) {
    if (isEmptyArray(st)) {
        printf("Nothing to delete!\n");
        exit(1);
    }

    Car temp = st->arr[st->top];
    st->top--;
    return temp;
    
}

void showArrayStack(ArrayStack st) {

    ArrayStack temp;
    initArrayStack(&temp, st.max);

     printf("%-15s%-15s%-15s%-10s%-10s",
             "Plate", "Brand", "Model", "Year","Price");
     printf("\n----------------------------------------------------------------------------------\n");
    while (!isEmptyArray(&st)) {
       
        Car car = popArray(&st); 
            printf("%-15s%-15s%-15s%-10d%-10.2f\n", car.plate, car.brand, car.model, car.year, car.pricePerDay);
        pushArray(&temp, car);
    }

    while (!isEmptyArray(&temp)) {
        pushArray(&st, popArray(&temp));
    }
    printf("----------------------------------------------------------------------------------\n");

}

// ---- Special ArrayStack Operations ----
int countNewerCars(ArrayStack st, int year) {
    ArrayStack temp;
    int count = 0;
    initArrayStack(&temp, st.max);

    while (!isEmptyArray(&st)) {
        Car car = popArray(&st); 
            if (car.year > year) {
                count++;
            }
            pushArray(&temp, car);
        
    }

    while (!isEmptyArray(&temp)) {
        pushArray(&st, popArray(&temp));
    }
    return count;
}

Car findMostExpensiveArray(ArrayStack st) {
    ArrayStack temp;
    initArrayStack(&temp, st.max);

    Car car = popArray(&st);
    pushArray(&temp, car);

    while (!isEmptyArray(&st)) {
        Car c = popArray(&st);
        if (car.pricePerDay < c.pricePerDay) {
            car = c;
        }
        pushArray(&temp, c);
    }
    
    return car;

}


// ================= LINKED LIST-BASED STACK =================
typedef struct node {
    Car data;
    struct node *next;
} Node, *NodePtr;

typedef struct {
    NodePtr top;
    int size;
} LinkedStack, *LinkedStackPtr;

// ---- LinkedStack Operations ----
void initLinkedStack(LinkedStackPtr st) {
    st->size = 0;
    st->top = NULL;
}

bool isEmptyLL(LinkedStackPtr st) {
    return st-> top == NULL && st->size == 0;
}
void pushLinked(LinkedStackPtr st, Car c) {

    NodePtr temp = malloc(sizeof(Node));
    if (!temp) {
        printf("Dynamic Memory Allocation failed\n");
        exit(1);
    }

    temp->data = c;
    

    
    temp->next = st->top;
    st->top = temp;
    st->size++;
    
}
Car popLinked(LinkedStackPtr st) {
    
    if (isEmptyLL(st)) {
        exit(1);
    }

    Car temp = st->top->data;
    NodePtr toRemove = st->top;
    st->top = toRemove->next;
    free(toRemove);
    st->size --;
    return temp;

}

void showLinkedStack(LinkedStack st) {
    LinkedStack LL;
    initLinkedStack(&LL);

  printf("%-15s%-15s%-15s%-10s%-10s",
             "Plate", "Brand", "Model", "Year","Price");
     printf("\n----------------------------------------------------------------------------------\n");
   
    while (!isEmptyLL(&st)) {
        Car temp = popLinked(&st); 
        printf("%-15s%-15s%-15s%-10d%-10.2f\n", temp.plate, temp.brand, temp.model, temp.year, temp.pricePerDay);
        pushLinked(&LL, temp);     
    }

    while (!isEmptyLL(&LL))
     {
        pushLinked(&st, popLinked(&LL));
     }


}





// ---- Special LinkedStack Operations ----
int countByBrand(LinkedStack st, const char *brand) {

    LinkedStack temp;
    initLinkedStack(&temp);
    int count = 0;

    while (!isEmptyLL(&st)) {
        Car car = popLinked(&st);
         if (strcmp(car.brand, brand) == 0) {
            count++;
        }
        pushLinked(&temp, car);

    }

    while (!isEmptyLL(&temp)) {
        pushLinked(&st, popLinked(&temp));
    }


    return count;
}

Car findCheapestLinked(LinkedStack st) {
    // TODO: find cheapest car in linked stack
    LinkedStack temp;
    initLinkedStack(&temp);

    Car maxCar = popLinked(&st);
    pushLinked(&temp, maxCar);

    while (!isEmptyLL(&st)) {
        Car car = popLinked(&st);
        if (maxCar.pricePerDay > car.pricePerDay) {
            maxCar = car;
        }
        pushLinked(&temp, car);
    }

    while (!isEmptyLL(&temp)) {
        pushLinked(&st, popLinked(&temp));
    }

    return maxCar;
}


// ================= Utility =================
Car createCar(const char *plate, const char *brand, const char *model, int year, float price) {
    // TODO: create and return a Car struct
    Car new;
    strcpy(new.plate, plate);
    strcpy(new.brand, brand);
    strcpy(new.model, model);
    new.year = year;
    new.pricePerDay = price;
    return new;
}


// ================= Main =================
int main() {
    // --- Test ArrayStack ---
    ArrayStack arrSt;
    initArrayStack(&arrSt, 5);

    pushArray(&arrSt, createCar("A1", "Toyota", "Corolla", 2020, 50));
    pushArray(&arrSt, createCar("B2", "Honda", "Civic", 2019, 45));
    pushArray(&arrSt, createCar("C3", "Tesla", "Model 3", 2022, 202));

    showArrayStack(arrSt);

    Car mostExp = findMostExpensiveArray(arrSt);
    printf("\nMost Expensive in ArrayStack: %s %s ($%.2f)\n", mostExp.brand, mostExp.model, mostExp.pricePerDay);

    printf("Cars newer than 2019: %d\n", countNewerCars(arrSt, 2019));

    Car poppedA = popArray(&arrSt);
    printf("\nPopped from ArrayStack: %s %s\n\n", poppedA.brand, poppedA.model);


    printf("\n\n~LINKED LIST SECTION~\n\n");
    // --- Test LinkedStack ---
    LinkedStack linkSt;
    initLinkedStack(&linkSt);

    pushLinked(&linkSt, createCar("X9", "Toyota", "Vios", 2018, 40));
    pushLinked(&linkSt, createCar("Y8", "Honda", "Jazz", 2021, 55));
    pushLinked(&linkSt, createCar("Z7", "Tesla", "Model S", 2023, 120));

    showLinkedStack(linkSt);

    Car cheap = findCheapestLinked(linkSt);
    printf("\nCheapest in LinkedStack: %s %s ($%.2f)\n", cheap.brand, cheap.model, cheap.pricePerDay);

    printf("Honda rentals in LinkedStack: %d\n", countByBrand(linkSt, "Honda"));

    Car poppedL = popLinked(&linkSt);
    printf("Popped from LinkedStack: %s %s\n", poppedL.brand, poppedL.model);

    return 0;
}

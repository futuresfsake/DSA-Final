#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>



#define MAX 10

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int id;
    char name[199];
    Date date;
    float price;
    int quantity;
    
}Product;

typedef struct node {
    Product product;
    struct node* next;
}ProductType, *ProductPtr;
// ? ProductType is a struct node
// ? ProductPtr is a pointer to a struct node (linked list node)



typedef ProductPtr DICTIONARY[MAX];
// ? DICTIONARY is an array of a 10 ProductPtr, each ProductPtr points to a ProductType node





// ? DICTIONARY* is a pointer to an array of NodePtr
void initDictionary(DICTIONARY dict); 
int HashFunction(int id, char Name[]);
void MakeNull (DICTIONARY* Dict);
void Insert(DICTIONARY* dict, Product P);
bool Remove(DICTIONARY* dict, int id, char name[]);
// bool IsMember(DICTIONARY* dict, int id);
void Display(DICTIONARY dict);
// Product createProduct(int day, int month, int year, int id, char name[], float price, int quantity);


int main() {
   

   DICTIONARY dict;
   initDictionary(dict);

   Product products[7] = 
   {
        {1001, "Milkita",        {12, 10, 2025}, 45.50, 20},
        {1002, "BreadPan",       {11, 10, 2025}, 30.00, 15},
        {1003, "Butter",      {10, 10, 2025}, 120.00, 10},
        {1004, "Cheese",      {9, 10, 2025}, 250.00, 8},
        {1005, "Eggs",        {8, 10, 2025}, 10.50, 30},
        {1006, "Cereal",      {7, 10, 2025}, 180.75, 12},
        {1007, "Juice",       {6, 10, 2025}, 75.25, 25}
    };


    for(int i = 0; i < 7; i++) {
        Insert(&dict, products[i]);
    }

    Display(dict);


    bool res = Remove(&dict,1006, "Cereal"); // ! pass the address of dict
    if (res) {
        printf("Product is successfully removed.\n");
    } else {
        printf("Product not found.\n");
    }

     Display(dict);


    
}


void initDictionary(DICTIONARY dict) {
  
    for(int i = 0; i < MAX; i++) {
     dict[i]= NULL;
    }
}

int HashFunction(int id, char Name[]) {
    int sumOfChar = 0;
    int count = 0;

    for(int i = 32 -1; i >= 0; i--) {
        unsigned int bit = (id >> i) & 1;

        if (bit == 1) {
            count++;
        }
    }


// ! add the ascii values of the first 3 characters, 
    for(int i = 0; i<3 && Name[i]  != '\0'; i++) {
        sumOfChar+=Name[i];
    }
    return ((count * sumOfChar) + 32) % MAX;
}


void MakeNull (DICTIONARY* dict) {
    for(int i = 0; i < MAX; i++) {
        (*dict)[i] = NULL;
    }
}



void Insert(DICTIONARY* dict, Product P) {
    int index = HashFunction(P.id, P.name);

    ProductPtr prods = malloc(sizeof(ProductType));
    if (!prods) {
        printf("Dynamic Memory Allocation failed.\n");
        return;
    }
    prods->product = P;
    (prods)->next = (*dict)[index];
    (*dict)[index] = prods;

    printf("Successfull\n");
}


bool Remove(DICTIONARY* dict, int id, char name[]) {
    int index = HashFunction(id, name);

    ProductPtr* temp = &(*dict)[index];

    
   for(; *temp != NULL; temp = &(*temp)->next) {
        if ((*temp)->product.id == id && strcmp((*temp)->product.name, name)==0)  {
            ProductPtr toRemove = *temp;
            *temp = toRemove->next;
            printf("%d - %s deleting...\n", toRemove->product.id, toRemove->product.name);
            free(toRemove);
            return 1;

        }
   }
   printf("ID: %d & Name: %s is not found...\n", id, name);
   return -1;
}
// bool IsMember(DICTIONARY* dict, int id);
void Display(DICTIONARY dict) {
    printf("Product Info:\n");

    for(int i = 0; i < MAX; i++) {
        printf("Index [%d] ->", i);

        ProductPtr temp = (dict)[i];
        if (temp == NULL) {
            printf(" EMPTY\n");
        }

        while (temp != NULL) {
            printf(" {ID: %d, Product: {%s} ->", temp->product.id, temp->product.name);
            if (temp->next == NULL) {
                printf(" NULL\n");
            }
            temp = temp->next;
        }

    }
}







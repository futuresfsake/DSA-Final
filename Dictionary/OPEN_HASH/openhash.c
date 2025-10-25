#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10

// Product structure
typedef struct Product {
    int id;              // Product ID
    char name[30];       // Product name (use first 4 letters)
    int exp;             // Expiration (days)
    float price;         // Product price
    int quantity;        // Quantity in stock
    struct Product* next; // Linked list pointer for collision handling
} Product;

// Hash table structure
typedef struct {
    Product* table[MAX]; // Hash table array of buckets
} HashTable;

// Function declarations
void initHashTable(HashTable *tables);
unsigned int hash(int id, char* name);
void insert(HashTable* ht, int id, char* name, int exp, float price, int quantity);
bool delete(HashTable* ht, int id, char* name);
void display(HashTable ht);
HashTable* unionHt (HashTable* ht1, HashTable* ht2);
HashTable filter(HashTable* A, int threshold);
HashTable* differenceSet(HashTable* ht1, HashTable* ht2);
HashTable* intersectSet(HashTable* ht1, HashTable* ht2);

// Main function (testing area)
int main() {
    
    HashTable ht, ht2;

    // Initialize hash table
    initHashTable(&ht);
    initHashTable(&ht2);

    // Insert some products
    insert(&ht, 101, "Milk", 7, 50.0, 10);
    insert(&ht, 102, "Eggs", 14, 100.0, 20);
    insert(&ht, 103, "Bread", 3, 40.0, 15);
    insert(&ht, 104, "Juice", 5, 60.0, 8);
    insert(&ht, 105, "Apple", 10, 30.0, 25);


    insert(&ht2, 103, "Bread", 4, 45.0, 12);     // same as A
    insert(&ht2, 105, "Apple", 12, 35.0, 18);    // same as A
    insert(&ht2, 106, "Banana", 6, 25.0, 30);
    insert(&ht2, 107, "Ketchup", 8, 28.0, 22);
    insert(&ht2, 108, "Chobani", 10, 55.0, 9);\
    insert(&ht2, 111, "Flour", 10, 85.0, 89);


    // Display the hash table
    printf("Initial hash table:\n");
    display(ht);
    display(ht2);

    // Delete a product
    printf("\nDeleting product ID 103 (Bread)...\n");
    if (delete(&ht, 103, "Bread")) {
        printf("Deleted successfully.\n");
    } else {
        printf("Product not found.\n");
    }

    // Display the hash table after deletion
    printf("\nHash table after deletion:\n");
    display(ht);

    // Insert a duplicate product (should fail)
    printf("\nTrying to insert duplicate product Milk...\n");
    insert(&ht, 101, "Milk", 7, 50.0, 10);

    // Display final hash table
    printf("\nFinal hash table:\n");
    display(ht);


    printf("UNION");
    HashTable* U = unionHt(&ht, &ht2);
    display(*U);

    printf("Interset");
    HashTable* I = intersectSet(&ht, &ht2);
    display(*I);

    printf("Difference");
    HashTable* D = differenceSet(&ht, &ht2);
    display(*D);


    printf("\nFilter products with quantity >= 20:\n");
HashTable F = filter(&ht, 20);
display(F);

    return 0;


}

// * 1s count bits * sum of the first four letters + 32 % MAX;

void initHashTable(HashTable *tables) {

    
    for(int i = 0; i < MAX; i++) {
        tables->table[i] = NULL;
    }
}

// Hash function
unsigned int hash(int id, char* name) {
    // Implement your custom hash function based on the given steps

    unsigned int count =0;
     unsigned int bits=0;
    for(int i = 0; i < 8; i++) {
        bits+=(id>>i) & 1;

        if (bits == 1) {
            count++;
        }
        
    }


    

   
    unsigned int sumOfchar=0;
    for(int i = 0; i < 4 && name[i] != '\0'  ; i++) {
        sumOfchar+= name[i];
    }


    return ((count * sumOfchar) + 32) % MAX; 
}

// Insert product into hash table with sorted insertion by product name
void insert(HashTable* ht, int id, char* name, int exp, float price, int quantity) {
    // Implement insert logic with sorted insertion in each bucket

    unsigned int index = hash(id, name);

    Product* trav = ht->table[index];
    bool found = false;


    for(; trav != NULL ; trav = trav->next) {
        if (strcmp(trav->name, name) == 0 && trav->id == id) {
            printf("Product %s already exists! Inserting failed!\n", name);
            found = true;
            return;
        }
    }


    if (!found) {
    Product* newProds = malloc(sizeof(Product));
    if (newProds == NULL) {
        printf("Dynamic memory allocation failed!\n");
        return;
    }

    strcpy(newProds->name, name);
    newProds->id = id;
    newProds->exp = exp;
    newProds->price = price;
    newProds->quantity = quantity;
    newProds->next = ht->table[index];
    ht->table[index] = newProds;

    }

    
}

// Delete a product by ID
bool delete(HashTable* ht, int id, char* name) {
    
    unsigned int index= hash(id, name);

    Product** trav = &(ht->table[index]);
    for (; *trav != NULL; trav = &(*trav)->next) {
        if (strcmp((*trav)->name, name)==0 && (*trav)->id == id) {
            Product* toRemove = *trav;
            *trav = toRemove->next;
            printf("Product with %d %s successfully removed!",id, name);
            free(toRemove);
            return true;
            

        }
    }

    return false;

}

// Display all products in the hash table

    void display(HashTable ht) {
    printf("\n=== HASH TABLE CONTENTS ===\n");
    printf("%-5s %-10s %-5s %-10s %-8s %-6s\n", 
           "Index", "Name", "ID", "Exp", "Price", "Qty");
    printf("-----------------------------------------------------\n");

    for (int i = 0; i < MAX; i++) {
        printf("%-5d ", i);
        Product* trav = ht.table[i];
        if (trav == NULL) {
            printf("~empty~\n");  // indicate empty bucket
        } else {
            bool first = true;
            while (trav != NULL) {
                if (!first) {
                    printf("      "); // indent for subsequent items in same bucket
                }
                printf("%-10s %-5d %-5d %-10.2f %-6d\n", 
                       trav->name, trav->id, trav->exp, trav->price, trav->quantity);
                trav = trav->next;
                first = false;
            }
        }
    }
    printf("-----------------------------------------------------\n");
}





// Merge two hash tables
HashTable* unionHt (HashTable* ht1, HashTable* ht2) {


    HashTable* newTable = malloc(sizeof(HashTable));
    initHashTable(newTable);
    
   

        for(int j = 0; j < MAX; j++) {
            Product* ptrA = ht1->table[j];

            while (ptrA) {

                unsigned int index = hash(ptrA->id, ptrA->name);
               

                Product* new = malloc(sizeof(Product));
                if (new == NULL) {
                    printf("Dynamic memory allocation failed!\n");
                }
                new->id = ptrA->id;
                strcpy(new->name, ptrA->name);
                new->exp = ptrA->exp;
                new->price = ptrA->price;
                new->quantity = ptrA->quantity;
                new->next = newTable->table[index];
                newTable->table[index] = new;
                


                ptrA = ptrA->next;
            }

            

        }




        for(int k = 0; k < MAX; k++) {
            Product* ptrB = ht2->table[k];

            while (ptrB) {

                bool inC = false;

                unsigned int index = hash(ptrB->id, ptrB->name);

                Product* trav = newTable->table[index];
                for(; trav != NULL; trav = trav->next) {
                    if (strcmp(trav->name, ptrB->name) == 0 && trav->id== ptrB->id) {
                        inC = true;
                        break;

                    }
                }

                if (!inC) {
                    Product* new = malloc(sizeof(Product));
                    if (!new) {
                        printf("Dynamic memory allocation failed!\n");
                        exit(1);
                    }

                    strcpy(new->name, ptrB->name);
                    new->id = ptrB->id;
                    new->exp = ptrB->exp;
                    new->price = ptrB->price;
                    new->quantity = ptrB->quantity;
                    new->next = newTable->table[index];
                    newTable->table[index] = new;

                }

                ptrB = ptrB->next;
            }
        }

        return newTable;



}


HashTable* intersectSet(HashTable* ht1, HashTable* ht2) {
    HashTable* newTable = malloc(sizeof(HashTable));
    if (!newTable) {
        printf("Dynamic memory allocation failed!\n");
    }


    initHashTable(newTable);


    for(int i = 0; i < MAX; i++) {
        Product* ptra = ht1->table[i];

        while (ptra) {
            bool inB = false;

            unsigned int index = hash(ptra->id, ptra->name);

            Product* ptrb = ht2->table[index];
            for(; ptrb != NULL; ptrb = ptrb->next) {
                if (strcmp(ptrb->name, ptra->name) == 0 && ptrb->id == ptra->id ) {
                    inB = true; break;
                }
            }


            if (inB) {
                bool inC = false;

                Product* ptrC = newTable->table[index];
                for(; ptrC != NULL; ptrC = ptrC->next) {
                    if (strcmp(ptrC->name, ptra->name ) == 0 && ptrC->id == ptra->id) {
                        inC = true;
                        break;

                    }
                }




                if (!inC) {
                    Product* new = malloc(sizeof(Product));
                    new->id = ptra->id;
                strcpy(new->name, ptra->name);
                new->exp = ptra->exp;
                new->price = ptra->price;
                new->quantity = ptra->quantity;
                new->next = newTable->table[index];
                newTable->table[index] = new;
                
                }
            }



            ptra = ptra->next;
        }

        
    }

    return newTable;
}


HashTable* differenceSet(HashTable* ht1, HashTable* ht2) {
    HashTable* newTable = malloc(sizeof(HashTable));
    if (!newTable) {
        printf("Dynamic memory allocation failed!\n");
    }


    initHashTable(newTable);


    for(int i = 0; i < MAX; i++) {
        Product* ptra = ht1->table[i];

        while (ptra) {
            bool inB = false;

            unsigned int index = hash(ptra->id, ptra->name);

            Product* ptrb = ht2->table[index];
            for(; ptrb != NULL; ptrb = ptrb->next) {
                if (strcmp(ptrb->name, ptra->name) == 0 && ptrb->id == ptra->id ) {
                    inB = true; break;
                }
            }


            if (!inB) {
                bool inC = false;

                Product* ptrC = newTable->table[index];
                for(; ptrC != NULL; ptrC = ptrC->next) {
                    if (strcmp(ptrC->name, ptra->name ) == 0 && ptrC->id == ptra->id) {
                        inC = true;
                        break;

                    }
                }




                if (!inC) {
                    Product* new = malloc(sizeof(Product));
                    new->id = ptra->id;
                strcpy(new->name, ptra->name);
                new->exp = ptra->exp;
                new->price = ptra->price;
                new->quantity = ptra->quantity;
                new->next = newTable->table[index];
                newTable->table[index] = new;
                
                }
            }



            ptra = ptra->next;
        }

        
    }

    return newTable;
}

HashTable filter(HashTable* A, int threshold) {
    HashTable tables;
    initHashTable(&tables);


    for(int i = 0; i < MAX; i++) {
        Product* ptra = A->table[i];

        while (ptra) {


            if (ptra->quantity >= threshold) {

                unsigned int index = hash(ptra->id, ptra->name);
                // bool inC = false;
                // Product* ptrC = tables.table[index];
                // for(; ptrC != NULL; ptrC = ptrC->next) {
                //     if (strcmp(ptrC->name, ptra->name) == 0 && ptrC->id == ptra->id) {
                //         inC = true;
                //         break;
                //     }
                // }


                // if (!inC) {
                    Product* new = malloc(sizeof(Product));
                     strcpy(new->name, ptra->name);
                new->exp = ptra->exp;
                new->id = ptra->id;
                new->price = ptra->price;
                new->quantity = ptra->quantity;
                new->next = tables.table[index];
                tables.table[index] = new;
                
                
            }

            ptra = ptra->next;
        }

    }

        return tables;
    
}
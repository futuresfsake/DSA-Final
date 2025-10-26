// * what is the difference between collision and probing
// * collission, is the number of conflicts, number of occupied slots you skipped
// * probes, the number of attempts made, including the successful ones, just +1 to your number of collision
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 10

// === Entry Structure ===
typedef struct {
    int id;
    char name[30];
    int age;
    int isOccupied;
    int isDeleted;
    int collision;   // number of probing-- lets assume this is probing during insertion
} Entry;

// === Dictionary Structure ===
typedef struct {
    Entry table[TABLE_SIZE];
} Dictionary;

// === Hash Function ===
unsigned int hash(int id) {
    return id % TABLE_SIZE;
}

// === Initialization Function ===
void initDictionary(Dictionary *D) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        D->table[i].isOccupied = 0;
        D->table[i].isDeleted = 0;
        D->table[i].collision = 0;
    }
}

// === Function to report collisions after insertion ===
void reportCollision(Entry *e) {
    printf(" Inserted %-10s | Num Of Collisions: %d\n", e->name, e->collision);
}


// === INSERT FUNCTION (You will implement this) ===
bool insert(Dictionary *D, int id, char *name, int age) {
    
    int count = 0;
       unsigned int h = hash(id);
    for(int i = 0; i < TABLE_SIZE; i++) {
     
        unsigned int index = (h + i) % TABLE_SIZE;


        if(D->table[index].isOccupied && D->table[index].id == id) {
            return false;
        } else if (D->table[index].isOccupied == 0 || D->table[index].isDeleted==1) {
            strncpy(D->table[index].name, name, sizeof(D->table[index].name) -1);
            D->table[index].name[sizeof(D->table[index].name)-1] = '\0';
            D->table[index].age = age;
            D->table[index].id = id;
            D->table[index].isOccupied = 1;
            D->table[index].isDeleted = 0;
            D->table[index].collision = count+1;
            reportCollision(&(D->table[index]));
            return true;
        }

        count++;
    }
    return false; // placeholder
}

// === Display Function ===
void displayDictionary(Dictionary *D) {
    printf("\n%-5s %-10s %-5s %-10s %-10s\n", "Index", "Name", "Age", "Occupied", "Collisions");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (D->table[i].isOccupied) {
            printf("%-5d %-10s %-5d %-10s %-10d\n",
                   i,
                   D->table[i].name,
                   D->table[i].age,
                   D->table[i].isOccupied ? "Yes" : "No",
                   D->table[i].collision);
        } else {
            printf("%-5d %-10s %-5s %-10s %-10s\n",
                   i, "-", "-", "No", "-");
        }
    }
}

// === MAIN FUNCTION ===
int main() {
    Dictionary D;
    initDictionary(&D);

    printf("🔧 Inserting sample entries...\n\n");

    
    insert(&D, 10, "Alice", 21); 
    displayDictionary(&D);   
    
    insert(&D, 20, "Bob", 25); 
    displayDictionary(&D);      // collision with Alice (same hash)
    insert(&D, 30, "Charlie", 30); 
    displayDictionary(&D);  // another collision chain
    insert(&D, 11, "David", 22);
    displayDictionary(&D);     // different hash slot

    printf("\n📊 FINAL TABLE STATE:\n");
    displayDictionary(&D);

    return 0;
}

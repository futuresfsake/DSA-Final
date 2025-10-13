// * implementing open hashing
// * using pointer to pointer notes, with specific typedefs
// * using an integer element only



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX 5

typedef struct node {
    int data;
    struct node* link;
}*SET;  // * SET is a pointer to a struct node



typedef SET DICTIONARY[MAX]; // * ARRAY OF SET POINTERS
typedef enum {FALSE, TRUE} Boolean;

int hash (int key) {
    return key % MAX;
}

void initialize(DICTIONARY dict) {
    for(int i = 0; i < MAX; i++) {
        dict[i] = NULL; // * NULL is a pointer void, not a struct.
    }
}


void insert(DICTIONARY dict, int value) {
    int index = hash(value);  // * hash it first, to get the index

    SET newNode = malloc(sizeof(struct node)); // ! size of a struct node, not SET, its a struct node*
    newNode->data = value;
    newNode->link = dict[index]; // ! link to current head
    dict[index] = newNode; // ! update the head

    printf("%d is successfully inserted!\n", value);

}


Boolean search(DICTIONARY dict, int value) {
    int index = hash(value);

    SET temp = dict[index];

    while(temp != NULL) {
        if (temp->data == value) {
            return TRUE;
        }
        temp = temp->link;
    }
    return FALSE;
}

Boolean delete(DICTIONARY dict, int value) {
    int index = hash(value);
    SET *temp = &dict[index];
    // * temp is a ppm. dict[index] is now a ppn

    // * dict[index] is already a SET pointer, but you want a pointer to pointer for deletion, so &dict[index]

    while (*temp != NULL) {
        if ((*temp)->data == value) {
            SET toRemove = *temp;
            *temp = toRemove->link;
            free(toRemove);
            return TRUE;
        }

        temp = &(*temp)->link;
    }
    return FALSE;
}


void display(DICTIONARY dict) {
    for(int i = 0; i < MAX; i++) {
        printf("Index %d ->", i);


        SET temp = dict[i];
        if (temp == NULL) {
            printf("NULL\n");
        } else {
            while (temp != NULL) {
                printf(" %d-> ", temp->data);
                if (temp->link == NULL) {
                    printf("NULL\n");
                }
                temp = temp->link;
            }
        }
    }
}



// Test
int main() {
    DICTIONARY dict;
    initialize(dict);

    insert(dict, 12);
    insert(dict, 7);
    insert(dict, 5);
    insert(dict, 17);
    insert(dict, 22);

    printf("Dictionary after insertion:\n");
    display(dict);

    printf("\nDelete 17:\n");
    delete(dict, 17);
    display(dict);

    printf("\nSearch for 5: %s\n", search(dict, 5) ? "Found" : "Not Found");
    printf("Search for 17: %s\n", search(dict, 17) ? "Found" : "Not Found");

    return 0;
}
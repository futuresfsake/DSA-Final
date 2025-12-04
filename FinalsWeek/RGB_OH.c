#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



// Maximum size of hash table (palette size)
#define PALETTE_SIZE 64
// Maximum length for a color name
#define MAX_NAME_LENGTH 50

// Type definition for a string
typedef char String[MAX_NAME_LENGTH];

// Color Structure
typedef struct {
    String colorName;
    int RGBVal[3]; // [R, G, B] values, each 0-255
} Color;

// Linked List Node Structure
typedef struct Node {
    Color data;
    struct Node *next;
} Node;

// Dictionary Structure (the hash table)
typedef struct {
    Node *buckets[PALETTE_SIZE]; // Array of pointers to the head of each linked list
} Dictionary;

// function prototypes
int hashFunction(int rgb[3]);
void createDictionary(Dictionary *dict);
Node* createNode(Color newColor);
void insertColor(Dictionary *dict, Color newColor);
Color* searchColor(Dictionary *dict, int rgb[3]);



void displayDictionary(Dictionary *dict) {
    printf("\n--- Color Dictionary Content ---\n");
    for (int i = 0; i < PALETTE_SIZE; i++) {
        Node *current = dict->buckets[i];

        if (current != NULL) {
            printf("Bucket [%d]: ", i);
            int count = 0;
            while (current != NULL) {
                if (count > 0) {
                    printf(" -> ");
                }
                printf("%s (%d,%d,%d)",
                       current->data.colorName,
                       current->data.RGBVal[0],
                       current->data.RGBVal[1],
                       current->data.RGBVal[2]);
                current = current->next;
                count++;
            }
            printf("\n");
        }
    }
    printf("--------------------------------\n");
}

void destroyDictionary(Dictionary *dict) {
    for (int i = 0; i < PALETTE_SIZE; i++) {
        Node *current = dict->buckets[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
        dict->buckets[i] = NULL;
    }
}

int main() {
    Dictionary colorDict;
    createDictionary(&colorDict);

    Color red = {"Red", {255, 0, 0}};
    Color green = {"Green", {0, 255, 0}};
    Color blue = {"Blue", {0, 0, 255}};
    Color white = {"White", {255, 255, 255}};
    Color black = {"Black", {0, 0, 0}};
    Color darkGrey = {"Dark Grey", {10, 10, 10}};
    Color darkRed = {"Dark Red", {30, 0, 0}};

    printf("--- Inserting Colors ---\n");
    insertColor(&colorDict, red);
    insertColor(&colorDict, green);
    insertColor(&colorDict, blue);
    insertColor(&colorDict, white);
    insertColor(&colorDict, black);
    insertColor(&colorDict, darkGrey);
    insertColor(&colorDict, darkRed);

    // Collision example
    Color lightGrey = {"Light Grey", {1, 1, 1}}; // Hash: (3+5+7) = 15. 15 % 64 = 15.
    Color slightlyRed = {"Slightly Red", {5, 0, 0}}; // Hash: (5*3 + 0 + 0) = 15. 15 % 64 = 15.

    printf("\n--- Inserting Colliding Colors ---\n");
    insertColor(&colorDict, lightGrey);
    insertColor(&colorDict, slightlyRed);

    displayDictionary(&colorDict);

    // --- Search Examples ---

    // 1. Search for a found color (Red)
    printf("\n--- Search Results ---\n");
    int searchRedRGB[3] = {255, 0, 0};
    Color *foundColor = searchColor(&colorDict, searchRedRGB);

    if (foundColor) {
        printf("SUCCESS: Found Color: %s\n", foundColor->colorName);
    } else {
        printf("FAILURE: Color not found.\n");
    }

    // 2. Search for a color in the new chain (Slightly Red)
    int searchSlightlyRed[3] = {5, 0, 0};
    foundColor = searchColor(&colorDict, searchSlightlyRed);

    if (foundColor) {
        printf("SUCCESS: Found Color: %s\n", foundColor->colorName);
    } else {
        printf("FAILURE: Color not found.\n");
    }

    // 3. Search for a non-existent color
    int searchOrangeRGB[3] = {255, 165, 0}; // Hash = 46
    foundColor = searchColor(&colorDict, searchOrangeRGB);

    if (foundColor) {
        printf("SUCCESS: Found Color: %s\n", foundColor->colorName);
    } else {
        printf("FAILURE: Color not found.\n");
    }

    // Clean up memory
    destroyDictionary(&colorDict);

    return 0;
}


//* to implement



int hashFunction(int rgb[3]) {
    
    
    
    int p1 = rgb[0] * 3;
    int p2 = rgb[1] * 5;
    int p3 = rgb[2] * 7;
    
    int sum = p1 + p2+ p3;
    
    return sum % PALETTE_SIZE;
}

void createDictionary(Dictionary *dict) {
    
    for(int i = 0; i < PALETTE_SIZE; i++) {
        dict->buckets[i] = NULL;
    }
}


Node* createNode(Color newColor) {
    
    Node* new = malloc(sizeof(Node));
    if (new == NULL) return NULL;
    
    new->data = newColor;
    new->next = NULL;
    return new;
}


void insertColor(Dictionary *dict, Color newColor) {
    int index = hashFunction(newColor.RGBVal);
    
    Node* trav = dict->buckets[index];
    bool found = 0;
    
    while (trav != NULL) {
        if (strcmp(trav->data.colorName, newColor.colorName)==0) {
            found = true;
            break;
        }
        trav = trav->next;
    }
    
    
    if (!found) {
        
        Node* new = createNode(newColor);
        new->next = dict->buckets[index];
        dict->buckets[index] = new;
        printf("-> Inserted '%s' (RGB: %d, %d, %d) into bucket [%d].\n", newColor.colorName, newColor.RGBVal[0], newColor.RGBVal[1], newColor.RGBVal[2], index);
    }
}

Color* searchColor(Dictionary *dict, int rgb[3]) {
    
    int index = hashFunction(rgb);
    printf("Searching for RGB (%d, %d, %d) in bucket [%d]...\n", rgb[0], rgb[1], rgb[2], index);
    Node* trav = dict->buckets[index];
    
    while(trav != NULL) {
        for(int i = 0; i < 3; i++) {
           if  (trav->data.RGBVal[i] != rgb[i]) {
                return NULL;
                
            }
            return &(trav->data);
            
        }
        
        trav = trav->next;
    }
}


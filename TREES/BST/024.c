#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NAME_LEN 50

/*
    Galactic Spaceport Registry (BST - Alphabetical Order)

    Backstory:
    ----------------
    The interstellar spaceport maintains a registry of starships.
    Each starship has a Name, Model, and CrewCapacity.  

    The registry is organized alphabetically by Starship Name using
    a Binary Search Tree for efficient lookup.

    All operations are iterative to simulate real-time access
    during docking and departure.
*/

// ================================
// Starship Struct
// ================================
typedef struct {
    char name[NAME_LEN];
    char model[NAME_LEN];
    int crewCapacity;
} Starship;

// ================================
// BST Node Struct
// ================================
typedef struct bstNode {
    Starship data;
    struct bstNode *left;
    struct bstNode *right;
} BSTNode;

// ================================
// Function Prototypes (Iterative)
// ================================

// 1. Create a new node
BSTNode* createStarshipNode(Starship s);

// 2. Insert starship alphabetically (iterative)
BSTNode* insertStarship(BSTNode *root, Starship s);

// 3. Search for a starship by name (iterative)
BSTNode* searchStarship(BSTNode *root, const char *name);

// 4. Delete a starship by name (iterative)
BSTNode* deleteStarship(BSTNode *root, const char *name);

// 5. Display starships in-order iteratively
void inorderDisplay(BSTNode *root);

// 6. Find minimum node (helper for deletion)
BSTNode* findMinNode(BSTNode *node);

// ================================
// ADDITIONAL OPERATIONS TO TEST KNOWLEDGE
// ================================

// 7. Count total starships iteratively
int countStarships(BSTNode *root);

// 8. Find maximum alphabetical starship iteratively
BSTNode* findMaxStarship(BSTNode *root);

// 9. Calculate height of the BST iteratively
int bstHeight(BSTNode *root);

// 10. Display starships in reverse alphabetical order iteratively
void reverseInorderDisplay(BSTNode *root);

// 11. Free all nodes iteratively
void freeBST(BSTNode *root) {
    if (root == NULL) return;

    freeBST(root->left);
    freeBST(root->left);
    free(root);

}
// ================================
// MAIN (Sample Usage)
// ================================
int main() {
    BSTNode *root = NULL;

    // Sample starships
    Starship s1 = {"Andromeda", "X-1", 150};
    Starship s2 = {"Zephyr", "Z-7", 80};
    Starship s3 = {"Orion", "O-3", 200};
    Starship s4 = {"Nova", "N-2", 120};
    Starship s5 = {"Aurora", "A-9", 100};

    // Insert starships
    root = insertStarship(root, s1);
    root = insertStarship(root, s2);
    root = insertStarship(root, s3);
    root = insertStarship(root, s4);
    root = insertStarship(root, s5);

    // Display in-order (A → Z)
    printf("\n--- Spaceport Registry (In-Order) ---\n");
    inorderDisplay(root);

    // // Display reverse in-order (Z → A)
    // printf("\n--- Spaceport Registry (Reverse In-Order) ---\n");
    // reverseInorderDisplay(root);

    // Count total starships
    printf("\nTotal Starships: %d\n", countStarships(root));

    // Find maximum alphabetical starship
    BSTNode *maxShip = findMaxStarship(root);
    if(maxShip) {
        printf("\nMax Crew Capacity Starship: %s, Model: %s, Crew Capacity: %d\n ",
 maxShip->data.name, maxShip->data.model, maxShip->data.crewCapacity);
        }

    // Calculate BST height
    printf("\nBST Height: %d\n", bstHeight(root));

    // Search for a starship
    const char *searchName = "Orion";
    BSTNode *found = searchStarship(root, searchName);
    if(found) {
        printf("\nFound Starship: %s, Model: %s, Crew: %d\n",
               found->data.name, found->data.model, found->data.crewCapacity);
    } else {
        printf("\nStarship %s not found.\n", searchName);
    }

    // Delete a starship
    root = deleteStarship(root, "Nova");
    printf("\n--- Registry after deletion ---\n");
    inorderDisplay(root);

    // Free all nodes
    freeBST(root);

    return 0;
}


// 1. Create a new node
BSTNode* createStarshipNode(Starship s) {

    BSTNode* new = malloc(sizeof(BSTNode));
    if (new == NULL) return NULL;
    new->data = s;
    new->left = new->right = NULL;
    return new;

}

// 2. Insert starship alphabetically (iterative)
BSTNode* insertStarship(BSTNode *root, Starship s) {

    BSTNode** trav = &root;
    for(;*trav != NULL && (*trav)->data.crewCapacity != s.crewCapacity;) {
        trav = (*trav)->data.crewCapacity < s.crewCapacity ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL)  {
        BSTNode* new = createStarshipNode(s);
        *trav = new;
    }

    return root;

}


BSTNode* searchStarship(BSTNode *root, const char *name) {
    if (root == NULL) return root;

    if (strcmp(root->data.name, name)==0) {
        return root;
    }

    
    root->left =  searchStarship(root->left, name);
    root->right =  searchStarship(root->right, name);
}

void inorderDisplay(BSTNode *root) {
    BSTNode *stack[100];
    int top = -1;

    BSTNode *curr = root;

    while (curr != NULL || top != -1) {

        while (curr != NULL) {
            stack[++top] = curr;
            curr = curr->left;
        }

        curr = stack[top--];

        printf("Name: %s | Model: %s | Crew: %d\n",
               curr->data.name,
               curr->data.model,
               curr->data.crewCapacity);

        curr = curr->right;
    }
}



BSTNode* deleteStarship(BSTNode *root, const char *name) {
    
    if (root == NULL) return root;
    
    root->left = deleteStarship(root->left, name);
    root->right = deleteStarship(root->right, name);


    if (strcmp(root->data.name, name) == 0) {
        BSTNode* temp = root;

        if (root->left == NULL && root->right == NULL) {
            free(temp);
            root = NULL;
    
        } else if (root->left == NULL) {
            root = root->right;
            free(temp);
        }
        else if (root->right == NULL) {
            root = root->left;
            free(temp);
            
        } else {
            BSTNode* succ = root->right;
            while (succ->left) {
                succ = succ->left;
            }

            root->data = succ->data;
            root->right = deleteStarship(root->right, succ->data.name);
            
        }

        return root;
    }
   
    
    
    return root;
}


// 6. Find minimum node (helper for deletion)
BSTNode* findMinNode(BSTNode *node) {

    if (node == NULL) return node;

    while (node->left) {
        node = node->left;
    }
    return node;
}

int countStarships(BSTNode *root) {
    if (root == NULL) return 0;
    int c = countStarships(root->left);
    int c2 = countStarships(root->right);

    return c + c2 +1;

}


BSTNode* findMaxStarship(BSTNode *root) {
    
    if (root== NULL) return root;

    while (root->right) {
        root = root->right;
    }
    return root;
}

// 9. Calculate height of the BST iteratively
int bstHeight(BSTNode *root) {
    if (root == NULL) return 0;

    int c = bstHeight(root->left);
    int c1 = bstHeight(root->left);

    return (c < c1 ? c1 : c) +1;
}

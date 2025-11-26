#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
    ===== THE NEBULA INTERCEPTOR (ITERATIVE BST) =====
    
    RULES:
    1. Organize signals by 'frequency'.
    2. LOWER frequency -> Left Child.
    3. HIGHER frequency -> Right Child.
    4. EQUAL frequency -> LEFT CHILD (Critical Change!).
    
    5. ALL FUNCTIONS MUST BE ITERATIVE (loops only).
*/

typedef struct Signal {
    int transmissionID;  // Unique ID
    int frequency;       // BST Key
    char alienSource[50];
} Signal;

typedef struct Node {
    Signal data;
    struct Node* left;
    struct Node* right;
} Node;

// === PROTOTYPES (You must implement these) ===

// Allocates memory for a new node
Node* createNode(Signal data) {
    Node* new = malloc(sizeof(Node));
    new->data = data;
    new->left = new->right = NULL;
    return new;
}

// 1. Insert a signal into the tree (Iterative)
// Remember: Equal frequencies go to the LEFT.
void interceptSignal(Node** root, Signal data) {

    Node** trav = root;
    for(;*trav != NULL ;) {
        if ((*trav)->data.frequency == data.frequency) {
            (trav) = &(*trav)->left;
          
        } else  {
        
        trav = (*trav)->data.frequency < data.frequency ? &(*trav)->right : &(*trav)->left;
    }
    

    }

   
    if (*trav == NULL) {
        
        Node* new = createNode(data);
        *trav = new;
    }

}

// 2. Search for a signal by ID (Iterative)
// Returns true if found, false otherwise
bool scanForSignal(Node* root, int searchID, int knownFreq) {
    
    Node* trav = root;
    
    for(;trav != NULL;) {
        if (trav->data.transmissionID == searchID) {
            return true;
        }
        trav = trav->data.frequency < knownFreq ? trav->right : trav->left;
    }

    return false;

    
}

// 3. Delete a signal by ID (Iterative)
// Handles the 0, 1, and 2 children cases without recursion.
// Hint: If 2 children, copy Predecessor or Successor, then delete that node.
void purgeSignal(Node** root, int targetID, int knownFreq) {

    Node** trav = root;

    for(;*trav != NULL && (*trav)->data.transmissionID != targetID;) {
        trav = (*trav)->data.frequency < knownFreq ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) return;

    Node* temp = *trav;

    if (!(*trav)->right && !(*trav)->left) {
        free(temp);
        *trav = NULL;
    }

    else if (!(*trav)->left) {
        *trav = (*trav)->right;
        free(temp);
    }
     else if (!(*trav)->right) {
        *trav = (*trav)->left;
        free(temp);
    } else {
        Node** succ = &(*trav)->right;
        while ((*succ)->left) {
            succ = &(*succ)->left;
        }

        (*trav)->data = (*succ)->data;
        purgeSignal(succ, (*succ)->data.transmissionID, (*succ)->data.frequency);
    }
}

// 4. Print all signals (Iterative In-Order Traversal)
// Use a stack to print: Left -> Root -> Right
// 4. Iterative In-Order Traversal to display signals
void displayLog(Node* root) {
    if (!root) {
        printf("Signal log is empty.\n");
        return;
    }

    Node* stack[100]; // simple fixed-size stack
    int top = -1;
    Node* curr = root;

    printf("\n=== SIGNAL LOG (Sorted by Frequency) ===\n");

    while (curr != NULL || top != -1) {
        // Reach the leftmost node
        while (curr != NULL) {
            stack[++top] = curr;
            curr = curr->left;
        }

        // Pop from stack
        curr = stack[top--];

        // Print current node
        printf("TransmissionID: %d, Frequency: %d, Source: %s\n",
               curr->data.transmissionID,
               curr->data.frequency,
               curr->data.alienSource);

        // Move to right subtree
        curr = curr->right;
    }
}


// 5. Free all nodes (Iterative Post-Order or Stack-based)
void shutdownSystem(Node* root) {
    if (root == NULL) return;
    shutdownSystem(root->left);
    shutdownSystem(root->right);
    free(root);
}


// === MAIN DRIVER ===
int main() {
    Node* root = NULL;

    // Test Data
    Signal s1 = {101, 500, "Martian"};
    Signal s2 = {102, 300, "Venusian"};
    Signal s3 = {103, 700, "Jovian"};
    Signal s4 = {104, 300, "Venusian-B"}; // Duplicate freq (Should go LEFT of 300)
    Signal s5 = {105, 200, "Mercurian"};
    Signal s6 = {106, 800, "Saturnian"};

    printf("\n=== INTERCEPTING SIGNALS ===\n");
    interceptSignal(&root, s1);
    interceptSignal(&root, s2);
    interceptSignal(&root, s3);
    interceptSignal(&root, s4);
    interceptSignal(&root, s5);
    interceptSignal(&root, s6);

    displayLog(root);

    // Search Test
    printf("\n=== SEARCH TEST ===\n");
    int searchID = 104; 
    int searchFreq = 300; // We need freq to navigate
    if (scanForSignal(root, searchID, searchFreq)) {
        printf("Signal %d found!\n", searchID);
    } else {
        printf("Signal %d lost in space.\n", searchID);
    }

    // Delete Test
    printf("\n=== PURGING SIGNAL %d (Venusian) ===\n", s2.transmissionID);
    // Note: s2 (300) has a left child s4 (300) and left child s5 (200). 
    // This tests your duplicate logic and child inheritance.
    purgeSignal(&root, s2.transmissionID, s2.frequency);

    printf("\n=== LOG AFTER PURGE ===\n");
    displayLog(root);

    printf("\n=== SYSTEM SHUTDOWN ===\n");
    shutdownSystem(root);
    root = NULL;
    
    return 0;
}

// ==========================================
// YOUR IMPLEMENTATIONS START HERE
// ==========================================

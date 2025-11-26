#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ================================
// Star System Struct
// ================================
typedef struct Star {
    char name[50];       // Name (e.g., "Alpha Centauri")
    double distance;     // Distance from Earth in Light Years (THE BST KEY)
    char spectralType;   // 'O', 'B', 'A', 'F', 'G', 'K', 'M'
} Star;

// ================================
// BST Node
// ================================
typedef struct StarNode {
    Star data;
    struct StarNode* left;
    struct StarNode* right;
} StarNode;

// Helper to create a star object quickly
Star createStarData(char* name, double dist, char type) {
    

    Star s;
    strcpy(s.name, name);
    s.distance = dist;
    s.spectralType = type;
    return s;
}

// ================================
// YOUR TASKS
// ================================

// 1. Insert a Star (Recursive) based on 'distance'
// If distance is equal, put it to the right.
StarNode* insertStar(StarNode* root, Star s) {

    StarNode** trav = &root;
    for(;*trav != NULL && (*trav)->data.distance != s.distance;) {
        trav = (*trav)->data.distance < s.distance ? &(*trav)->right : &(*trav)->left;
    }
    if (*trav == NULL) {

    StarNode* new = malloc(sizeof(StarNode));
    if (new == NULL) return NULL;
    new->data = s;
    new->left = new->right = NULL;
   

    *trav = new;
    return root;

    }
    

    
}

// 2. Find a Star by Name (Recursive)
// Note: The tree is sorted by DISTANCE, not Name. 
// You have to search every node until you find it.
StarNode* DeleteStar(StarNode* root, char* targetName) {
   
    if (root == NULL) return root;

    
    if (strcmp(root->data.name, targetName) == 0) {
        StarNode* temp = root;

        if (root->left == NULL && root->right == NULL) {
            free(temp);
            return NULL;
        } else if (root->left == NULL) {
            root = root->right;
            free(temp);
            return root;
        }
        else if (root->right == NULL) {
            root = root->left;
            free(temp);
            return root;
        } else {
            StarNode* pred = root->left;
            while (pred->right) {
                pred = pred->right;
            }

            root->data = pred->data;
            root->left = DeleteStar(root->left, pred->data.name);
            return root;
        }
        
        

    }
     root->left = DeleteStar(root->left, targetName);
    root->right = DeleteStar(root->right, targetName);




   
    return root;
}

void displayStarMap(StarNode* root) {
    if (root == NULL) return;
    
    // Visit left subtree
    displayStarMap(root->left);
    
    // Print current node
    printf("%-20s | Distance: %.2f ly | Type: %c\n", 
           root->data.name, 
           root->data.distance, 
           root->data.spectralType);
    
    // Visit right subtree
    displayStarMap(root->right);
}

// 3. Scan Sector (Range Query)
// Print all stars that are between minDistance and maxDistance (inclusive).
// Hint: This is a modified Inorder traversal. 
// If current < min, don't bother going left. If current > max, don't bother going right.
void scanSector(StarNode* root, double minDistance, double maxDistance) {

    if (root == NULL) return;
   scanSector(root->left,minDistance, maxDistance);
   if (root->data.distance>minDistance && root->data.distance < maxDistance) {
    printf("%-20s | Distance: %.2f ly | Type: %c\n", 
           root->data.name, 
           root->data.distance, 
           root->data.spectralType);

   }
      scanSector(root->right,minDistance, maxDistance);

    
}

// 4. Supernova (Free Memory)
// Recursively free the entire map.
void destroyMap(StarNode* root) {
    if (root == NULL) return;
    destroyMap(root->left);
    destroyMap(root->right);
    free(root);
}

int main() {
    StarNode* map = NULL;

    // Loading Data...
    printf("=== INSERTING STARS ===\n");
    map = insertStar(map, createStarData("Proxima Centauri", 4.24, 'M'));
    map = insertStar(map, createStarData("Sirius", 8.6, 'A'));
    map = insertStar(map, createStarData("Vega", 25.0, 'A'));
    map = insertStar(map, createStarData("Betelgeuse", 642.5, 'M'));
    map = insertStar(map, createStarData("Rigel", 860.0, 'B'));
    map = insertStar(map, createStarData("Barnard's Star", 5.96, 'M'));
    map = insertStar(map, createStarData("Wolf 359", 7.78, 'M'));

    printf("\n=== INITIAL STAR MAP (Sorted by Distance) ===\n");
    displayStarMap(map);

    // Test 1: Delete a leaf node
    printf("\n=== DELETING 'Wolf 359' (Node) ===\n");
    map = DeleteStar(map, "Wolf 359");
    displayStarMap(map);

    // Test 2: Delete a node with one child
    printf("\n=== DELETING 'Betelgeuse' (One Child) ===\n");
    map = DeleteStar(map, "Betelgeuse");
    displayStarMap(map);

    // Test 3: Delete a node with two children
    printf("\n=== DELETING 'Vega' (Two Children) ===\n");
    map = DeleteStar(map, "Vega");
    displayStarMap(map);

    // Test 4: Delete root
    printf("\n=== DELETING 'Proxima Centauri' (Root) ===\n");
    map = DeleteStar(map, "Proxima Centauri");
    displayStarMap(map);

    // Test 5: Range Query
    printf("\n=== SCANNING SECTOR (5.0 to 10.0 ly) ===\n");
    scanSector(map, 5.0, 10.0);

    // Test 6: Delete non-existent star
    printf("\n=== DELETING 'Alpha Centauri' (Non-existent) ===\n");
    map = DeleteStar(map, "Alpha Centauri");
    displayStarMap(map);

    printf("\n=== FINAL STAR MAP ===\n");
    displayStarMap(map);

    destroyMap(map);
    printf("\n=== All stars destroyed. Map cleared. ===\n");
    
    return 0;
}
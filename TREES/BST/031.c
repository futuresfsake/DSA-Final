#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME 40

typedef struct Cargo {
    int cargoID;
    char type[MAX_NAME];
    int weight;
} Cargo;

typedef struct CargoNode {
    Cargo cargo;
    struct CargoNode *left;
    struct CargoNode *right;
} CargoNode;



CargoNode* createNode(Cargo c);
CargoNode* insertCargo(CargoNode *root, Cargo c);
CargoNode* removeCargo(CargoNode *root, int cargoID);
CargoNode* findMin(CargoNode *root);
CargoNode* searchCargo(CargoNode *root, int cargoID);
void filterHeavyCargo(CargoNode **root, int minWeight);
void displayInOrder(CargoNode *root);
void freeTree(CargoNode *root);


int main() {
    CargoNode *root = NULL;

    Cargo c1 = {331, "Iron", 320};
    Cargo c2 = {332, "Carbon", 150};
    Cargo c3 = {333, "Palladium", 500};
    Cargo c4 = {334, "Titanium", 270};
    Cargo c5 = {335, "Silicon", 90};

    root = insertCargo(root, c1);
    root = insertCargo(root, c2);
    root = insertCargo(root, c3);
    root = insertCargo(root, c4);
    root = insertCargo(root, c5);

    printf("=== INITIAL CARGO ===\n");
    displayInOrder(root);

    printf("\n=== REMOVING CargoID 333 ===\n");
    root = removeCargo(root, 333);
    displayInOrder(root);

    printf("\n=== FILTERING HEAVY CARGO (>= 200kg) ===\n");
    filterHeavyCargo(&root, 200);
    displayInOrder(root);

    freeTree(root);
    return 0;
}



CargoNode* createNode(Cargo c) {

    CargoNode* new = malloc(sizeof(CargoNode));
    if (!new) return NULL;
    new->cargo = c;
    new->left = new->right = NULL;
    
    return new;
}


CargoNode* insertCargo(CargoNode *root, Cargo c) {

    CargoNode** trav = &root;
    for(;*trav != NULL && (*trav)->cargo.cargoID != c.cargoID;) {
        trav = (*trav)->cargo.cargoID < c.cargoID ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
        CargoNode* new = createNode(c);
        *trav = new;
    }

    return root;
}
CargoNode* removeCargo(CargoNode *root, int cargoID) {

    CargoNode** trav = &root;
    for(;*trav != NULL && (*trav)->cargo.cargoID != cargoID;) {
        trav = (*trav)->cargo.cargoID < cargoID ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) return root;

    CargoNode* temp = *trav;

    if (!(*trav)->right && !(*trav)->left) {
        free(temp);
        *trav = NULL;
    } else if ((*trav)->left == NULL) {
            *trav = (*trav)->right;
            free(temp);
        } else if ((*trav)->right == NULL) {
            *trav = (*trav)->left;
            free(temp);
        } else {
            CargoNode** succ = &(*trav)->right;
            while ((*succ)->left) {
                succ = &(*succ)->left;
            }
            (*trav)->cargo = (*succ)->cargo;
            (*trav)->right = removeCargo((*trav)->right, cargoID);
        }
        return root;
    }



CargoNode* findMin(CargoNode *root) {
    if (root == NULL) return NULL;

    while (root->left) {
        root = root->left;
    }
    return root;
}
CargoNode* searchCargo(CargoNode *root, int cargoID) {

    CargoNode* trav = root;
    while (trav != NULL) {
        if (trav->cargo.cargoID == cargoID) {
            return trav;
        }

        trav = trav->cargo.cargoID < cargoID ? (trav->right) : trav->left;
    }

    return NULL;
}
void filterHeavyCargo(CargoNode **root, int minWeight) {

    if (root == NULL || *root == NULL) return;
    CargoNode** trav = root;


    filterHeavyCargo(&(*trav)->left, minWeight);
        filterHeavyCargo(&(*trav)->right, minWeight);

    if ((*trav)->cargo.weight<minWeight) {

        CargoNode* temp = *trav;

        if (!(*trav)->left && !(*trav)->right) {
            free(temp);
            *trav = NULL;
        } else if (!(*trav)->left) {
            *trav = (*trav)->right;
            free(temp);
        }else if (!(*trav)->right) {
            *trav = (*trav)->left;
            free(temp);
        } else {
            CargoNode** succ = &(*trav)->right;
            while ((*succ)->left) {
                succ = &(*succ)->left;
            }

            (*trav)->cargo = (*succ)->cargo;
            filterHeavyCargo(&(*trav)->right, minWeight);
          
        }
          return;
    }

    

        
  


}
void displayInOrder(CargoNode *root) {
    if (!root) return;

    // Traverse left subtree
    displayInOrder(root->left);

    // Visit current node
    printf("CargoID: %d | Type: %s | Weight: %d\n",
           root->cargo.cargoID,
           root->cargo.type,
           root->cargo.weight);

    // Traverse right subtree
    displayInOrder(root->right);
}
void freeTree(CargoNode *root) {
    if (root == NULL) return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
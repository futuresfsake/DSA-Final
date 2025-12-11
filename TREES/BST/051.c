#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ===============================
// STRUCT DEFINITIONS
// ===============================
typedef struct Colony {
    char *name;              // Dynamic string for colony name
    int population;          // Extra info, not used for BST ordering
    struct Colony *left;
    struct Colony *right;
} ColonyNode;

// ===============================
// FUNCTION PROTOTYPES
// ===============================

// Node creation
ColonyNode* createColony(char *name, int population) {

    ColonyNode* new = malloc(sizeof(ColonyNode));
    if (new == NULL) return NULL;
    new->name = malloc(strlen(name)+1);
    strcpy(new->name, name);
    new->population = population;
    new->left = NULL;
    new->right = NULL;

    return new;
}

// Recursive BST operations
ColonyNode* insertColony(ColonyNode *root, char *name, int population) {
    if (root == NULL) {
        ColonyNode* new = createColony(name, population);

        return new;
    }


    if (strcmp(root->name, name) == 0 ) {
        printf("It is the same key! not allowed!\n", name);
        return root;
    }



    if (strcmp(root->name, name) < 0) {
        root->right = insertColony(root->right, name, population);
    } else if (strcmp(root->name, name) > 0) {
        root->left = insertColony(root->left, name, population);
    }

    return root;
}
ColonyNode* searchColony(ColonyNode *root, char *name) {

    if (root == NULL) return NULL;


    if (strcmp(root->name,name) == 0) {
        return root;
    }



    ColonyNode* left = searchColony(root->left, name);
    if (left != NULL) return left;


    ColonyNode* right = searchColony(root->right, name);
    if (right != NULL) return right;


    return NULL;
}
ColonyNode* deleteColony(ColonyNode *root, char *name) {

    if (root == NULL) return root;

    root->left = deleteColony(root->left, name);
    root->right = deleteColony(root->right, name);


    if (strcmp(root->name, name) == 0) {

        if (root->left == NULL && root->right == NULL) {
            free(root->name);
            free(root);
            root = NULL;
            return root;
        } else if (root->left == NULL) {
            ColonyNode* temp = root->right;
            free(root->name);
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            ColonyNode* temp = root->left;
            free(root->name);
            free(root);
            return temp;
        } else {
            ColonyNode* succ = root->right;
            while (succ->left) {
                succ = succ->left;
            }

            free(root->name);
            root->name = malloc(strlen(succ->name)+1);
            strcpy(root->name, succ->name);
            root->population = succ->population;

            root->right = deleteColony(root->right, succ->name);
        }
    }

    return root;
}

// Traversals (recursive)
void inorder(ColonyNode *root) {
        if (!root) return;

    inorder(root->left);
    printf("[Colony: %s | Pop: %d]\n", root->name, root->population);
    inorder(root->right);

}
void preorder(ColonyNode *root) {
    if (!root) return;

    printf("[Colony: %s | Pop: %d]\n", root->name, root->population);
    preorder(root->left);
    preorder(root->right);
}
void postorder(ColonyNode *root) {
    if (!root) return;

    postorder(root->left);
    postorder(root->right);
    printf("[Colony: %s | Pop: %d]\n", root->name, root->population);
}

// Find min/max
ColonyNode* findMin(ColonyNode *root) {
    while (root && root->left)
        root = root->left;
    return root;
}
ColonyNode* findMax(ColonyNode *root) {
    while (root && root->right)
        root = root->right;
    return root;
}

// Free the tree recursively
void freeTree(ColonyNode *root) {

    if (root == NULL) return;
    free(root->left);
    freeTree(root->right);
    free(root->name);
    free(root);
}

// ===============================
// MAIN (Boilerplate for practice)
// ===============================
int main() {
    ColonyNode *registry = NULL;

    // Insert colonies (practice recursive insertion)
    registry = insertColony(registry, "Nova Prime", 12000);
    registry = insertColony(registry, "Aurora", 8000);
    registry = insertColony(registry, "Xenon", 15000);
    registry = insertColony(registry, "Zephyria", 5000);
    registry = insertColony(registry, "Cydonia", 7000);

    printf("\n===== INORDER (Alphabetical) =====\n");
    inorder(registry);

    printf("\n===== SEARCH 'Xenon' =====\n");
    ColonyNode *c = searchColony(registry, "Xenon");
    if (c)
        printf("Found Colony: %s (Population: %d)\n", c->name, c->population);
    else
        printf("Colony not found.\n");

    printf("\n===== DELETE 'Aurora' =====\n");
    registry = deleteColony(registry, "Aurora");

    printf("\n===== INORDER AFTER DELETE =====\n");
    inorder(registry);

    printf("\n===== PREORDER =====\n");
    preorder(registry);

    printf("\n===== POSTORDER =====\n");
    postorder(registry);

    freeTree(registry);
    return 0;
}

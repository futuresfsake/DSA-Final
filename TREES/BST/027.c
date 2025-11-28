#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
    ============================================
    Galactic Creature Registry — BST Management
    --------------------------------------------
    Each creature has:
      - creatureID     (unique key)
      - name           (dynamic char*)
      - species        (dynamic char*)
      - dangerLevel    (float)
      - homePlanet     (dynamic char*)
    ============================================
*/

// ========== STRUCT DEFINITIONS ==========
typedef struct Creature {
    int creatureID;
    char *name;
    char *species;
    char *homePlanet;
    float dangerLevel;
} Creature;

typedef struct Node {
    Creature *data;
    struct Node *left;
    struct Node *right;
} Node;


Creature* create_creature(int id, const char *name,
                          const char *species, const char *planet,
                          float danger);

Node* insert_creature(Node *root, Creature *c);

Creature* search_creature(Node *root, int id);

Node* delete_creature(Node *root, int id);

void update_creature(Node *root, int id,
                     const char *newName,
                     const char *newPlanet,
                     float newDanger);

void inorder_display(Node *root);

void free_registry(Node *root);


// ========== MAIN TEST DRIVER ==========
int main() {
    Node *registry = NULL;

    printf("=== Galactic Creature Registry (BST) ===\n");

    // SAMPLE CREATURES
    Creature *c1 = create_creature(1001, "Vor'thak", "Draconid", "Xenthar", 8.9f);
    Creature *c2 = create_creature(1020, "Lumina", "Astral Sprite", "Nova-9", 2.4f);
    Creature *c3 = create_creature(1088, "Goreblight", "Behemoth", "Kragnar", 9.7f);
    Creature *c4 = create_creature(1112, "Silmareon", "Forest Sentinel", "Verdantis", 4.6f);
    Creature *c5 = create_creature(1233, "Cryon", "Frost Wraith", "Glaciara", 7.5f);

    // INSERT
    registry = insert_creature(registry, c1);
    registry = insert_creature(registry, c2);
    registry = insert_creature(registry, c3);
    registry = insert_creature(registry, c4);
    registry = insert_creature(registry, c5);

    printf("\n--- In-Order Display ---\n");
    inorder_display(registry);

    // SEARCH
    int targetID = 1088;
    Creature *found = search_creature(registry, targetID);
    if (found) {
        printf("\n[FOUND] Creature %d: %s (%s)\n",
               found->creatureID, found->name, found->species);
    } else {
        printf("\n[NOT FOUND] Creature ID %d\n", targetID);
    }

   
    // DELETE
    registry = delete_creature(registry, 1112);

    printf("\n--- After Deletion (ID 1112) ---\n");
    inorder_display(registry);

    // CLEANUP
    free_registry(registry);
    printf("\nAll creature data successfully freed.\n");

    return 0;
}

Creature* create_creature(int id, const char *name,const char *species, const char *planet,float danger) {

    Creature* new = malloc(sizeof(Creature));
    if (new == NULL) return NULL;
    new->name = malloc(strlen(name)+1);
    new->species = malloc(strlen(species)+1);
    new->homePlanet = malloc(strlen(planet)+1);
    
    new->creatureID = id;
    new->dangerLevel = danger;
    strcpy(new->name, name);
    strcpy(new->species, species);
    strcpy(new->homePlanet,planet);
    printf("Successfully allocated!");

    return new;

}

Node* insert_creature(Node *root, Creature *c) {

    Node** trav = &root;

    for(;*trav != NULL && (*trav)->data->creatureID != c->creatureID;) {
        trav = (*trav)->data->dangerLevel < c->dangerLevel ? &(*trav)->right : &(*trav)->left;
    }

    
    if (*trav == NULL) {
        
        Node* new = malloc(sizeof(Node));
        (new->data) = c;
        new->left = NULL;
        new->right = NULL;
        *trav = new;
        return root;
         
    }
    return root;
}

Creature* search_creature(Node *root, int id) {

    if (root == NULL) return NULL;

    if (root->data->creatureID == id) return root->data;

    Creature* f = search_creature(root->left,id);
        if (f != NULL) return f;
    
        Creature* f2 = search_creature(root->right, id);
        if (f2 != NULL) return f2;


        return NULL;
}

Node* delete_creature(Node *root, int id) {

    if (root == NULL) return root;

    root->left = delete_creature(root->left, id);
    root->right = delete_creature(root->right, id);

    if (root->data->creatureID == id) {
        Node* temp = root;

        if (root->left == NULL && root->right == NULL) {
            free(temp);
            root = NULL;
        } else if (root->left == NULL) {
            root = root->right;
            free(temp);
        }else if (root->right == NULL) {
            root = root->left;
            free(temp);
        } else {
            Node* succ = root->right;
            while (succ->left) {
                succ = succ->left;
            }

            root->data = succ->data;
            root->right = delete_creature(root->right, succ->data->creatureID);
        }
        return root;
    }

    return root;
}


void inorder_display(Node *root) {
    if (root == NULL) return;
    inorder_display(root->left);
    printf("[Danger Level]: %.2f || [ID]: %d || [NAME]: %s\n",
    root->data->dangerLevel, root->data->creatureID, root->data->name);
    inorder_display(root->right);
}

void free_registry(Node *root) {
    if (root == NULL) return;
    free_registry(root->left);
    free_registry(root->right);
    free(root);
}

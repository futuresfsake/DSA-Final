#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
    ================================================
      INTERSTELLAR MEDICAL RECORD SYSTEM (BST)
    ------------------------------------------------
    You maintain medical records for patients from
    many planets. Each patient has:

      - patientID     (unique key)
      - name          (dynamic string)
      - species       (dynamic string)
      - ailment       (dynamic string)
      - riskLevel     (float: 0.0 – 10.0)

    Your task:
      Implement creation, insertion, searching,
      updating, deletion, and freeing.
    ================================================
*/

// ========== STRUCTS ==========
typedef struct Patient {
    int patientID;
    char *name;
    char *species;
    char *ailment;
    float riskLevel;
} Patient;

typedef struct Node {
    Patient *data;
    struct Node *left;
    struct Node *right;
} Node;


// ========== PROTOTYPES ==========
Patient* create_patient(int id, const char *name,
                        const char *species,
                        const char *ailment,
                        float risk);

Node* insert_patient(Node *root, Patient *p);

Patient* search_patient(Node *root, int id);

Node* delete_patient(Node *root, int id);

void update_patient(Node *root, int id,
                    const char *newAilment,
                    float newRisk);

void inorder_print(Node *root);

void free_tree(Node *root);


// ========== MAIN DRIVER ==========
int main() {
    Node *hospital = NULL;

    printf("=== Interstellar Medical Records (BST) ===\n");

    // SAMPLE PATIENTS
    Patient *p1 = create_patient(5001, "Aurelia", "Star-Elf", "Radiant Fever", 3.5f);
    Patient *p2 = create_patient(5020, "Rok-Tarr", "Stoneborn", "Crystal Fracture", 7.2f);
    Patient *p3 = create_patient(5099, "Velis", "Moonwalker", "Lunar Drift", 4.1f);
    Patient *p4 = create_patient(5201, "Xynthos", "Void Serpent", "Dark Pulse Instability", 8.8f);
    Patient *p5 = create_patient(5333, "Ylanna", "Celestial Nymph", "Stardust Cough", 2.7f);

    // INSERT
    hospital = insert_patient(hospital, p1);
    hospital = insert_patient(hospital, p2);
    hospital = insert_patient(hospital, p3);
    hospital = insert_patient(hospital, p4);
    hospital = insert_patient(hospital, p5);

    // DISPLAY
    printf("\n--- In-Order Patient List ---\n");
    inorder_print(hospital);

    // SEARCH
    int id = 5099;
    Patient *found = search_patient(hospital, id);
    if (found) {
        printf("\n[FOUND] Patient %d: %s (%s)\n",
               found->patientID, found->name, found->species);
    } else {
        printf("\n[NOT FOUND] Patient ID %d\n", id);
    }

  

    // DELETE a patient by ID
    hospital = delete_patient(hospital, 5099);

    printf("\n--- After Deletion (ID 5099) ---\n");
    inorder_print(hospital);

    // // FREE MEMORY
    free_tree(hospital);
    printf("\nAll patient records successfully freed.\n");

    return 0;
}
// ========== PROTOTYPES ==========
Patient* create_patient(int id, const char *name,
                        const char *species,
                        const char *ailment,
                        float risk) {

    Patient* new = malloc(sizeof(Patient)); if (!new) return NULL;
    new->patientID = id;
    new->riskLevel = risk;

    new->name = malloc(strlen(name)+1); if (!new->name) return NULL;
    new->species = malloc(strlen(species)+1); if (!new->species) return NULL;
    new->ailment = malloc(strlen(ailment)+1); if (!new->ailment) return NULL;


    strcpy(new->name,name);
    strcpy(new->species, species);
    strcpy(new->ailment, ailment);
    printf("successfully generated!");
    return new;

                        }

Node* insert_patient(Node *root, Patient *p) {
  Node** trav = &root;

  for(;*trav != NULL && (*trav)->data->patientID != p->patientID;) {
    trav = (*trav)->data->patientID < p->patientID ? &(*trav)->right : &(*trav)->left;
  }

  if (*trav == NULL) {
    Node* new = malloc(sizeof(Node));
    if (!new) return NULL;

    new->data = p;
    new->left = new->right = NULL;

    *trav = new;
  }
  return root;
}


Patient* search_patient(Node *root, int id) {

  Node* trav = root;
  for(;trav != NULL;) {
    if (trav->data->patientID == id) {
      return (trav->data);
    }

    trav = trav->data->patientID < id ? trav->right : trav->left;
  }


  return NULL;
}

Node* delete_patient(Node *root, int id) {

  Node** trav = &root;
  for(;*trav != NULL && (*trav)->data->patientID != id;) {
    trav = (*trav)->data->patientID < id ? &(*trav)->right : &(*trav)->left;
  }

  if (*trav == NULL) return root;

  Node* temp = *trav;

  if (!(*trav)->left && !(*trav)->right) {
    free(temp);
    *trav == NULL;
  }else if (!(*trav)->left) {
    *trav = (*trav)->right;
    free(temp);
  }else if (!(*trav)->right) {
    *trav = (*trav)->left;
    free(temp);
  } else {
    Node** succ = &(*trav)->right;
    while ((*succ)->left != NULL) {
      succ = &(*succ)->left;
    }

    (*trav)->data = (*succ)->data;
    (*trav)->right = delete_patient((*trav)->right, (*succ)->data->patientID);
  }
  return root;
}


void inorder_print(Node *root) {
    if (root == NULL) return;

    inorder_print(root->left);

    Patient *p = root->data;
    printf("ID: %d | Name: %s | Species: %s | Ailment: %s | Risk: %.1f\n",
           p->patientID, p->name, p->species, p->ailment, p->riskLevel);

    inorder_print(root->right);
}


void free_tree(Node *root) {
  if (root == NULL) return;
  free_tree(root->left);
  free_tree(root->left);
  free(root);
}
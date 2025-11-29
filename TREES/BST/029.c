#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
    ================================================
      INTERSTELLAR MEDICAL RECORD SYSTEM (BST)
    ------------------------------------------------
    Each patient has:
        - patientID (unique key)
        - name (char*)
        - species (char*)
        - ailment (char*)
        - riskLevel (float)
    ================================================
*/

typedef struct Patient {
    int patientID;
    char *name;
    char *species;
    char *ailment;
    float riskLevel;
} Patient;

typedef struct Node {
    Patient data;
    struct Node *left;
    struct Node *right;
} Node;

/* =====================================================
        ONE-LINER createNode()  (as you requested)
   ===================================================== */
/* =====================================================
                BASIC BST OPERATIONS
   ===================================================== */



void inorder(Node *root) {
    if (!root) return;
    inorder(root->left);
    printf("ID: %d | %-10s | %-10s | %-12s | Risk: %.2f\n",
        root->data.patientID,
        root->data.name,
        root->data.species,
        root->data.ailment,
        root->data.riskLevel
    );
    inorder(root->right);
}



Node* insert(Node *root, Patient p);
Node* createNode(Patient p);
Node* search(Node *root, int id);
int countNodes(Node *root);                      
int height(Node *root);                           
Node* findMin(Node *root);                       
Node* findMax(Node *root);                        
Node* deleteNode(Node *root, int id);  


void printBySpecies(Node *root, const char *sp);  
void printHighRisk(Node *root, float threshold); 
int countSpecies(Node *root, const char *sp);     
float averageRisk(Node *root);                    
void freeTree(Node *root);                       





int main() {
    Node *root = NULL;

    // Create sample patients
    Patient p1 = {1003, "Arven", "Human", "Fever", 2.3};
    Patient p2 = {1001, "Zorak", "Martian", "Radiation", 7.5};
    Patient p3 = {1005, "Kira", "Andorian", "Frostbite", 4.1};
    Patient p4 = {1002, "Brax", "Human", "Migraine", 1.8};
    Patient p5 = {1004, "Serin", "Vulcan", "Nerve Pain", 6.0};

    // Insert into BST
    root = insert(root, p1);
    root = insert(root, p2);
    root = insert(root, p3);
    root = insert(root, p4);
    root = insert(root, p5);

    printf("\n=== Inorder Traversal ===\n");
    inorder(root);

    printf("\n=== Search Test (ID: 1004) ===\n");
    Node *found = search(root, 1004);
    if (found)
        printf("Found: %s with ailment %s\n", found->data.name, found->data.ailment);
    else
        printf("Not found.\n");

         printf("\nTotal nodes: %d\n", countNodes(root));
    printf("Tree height: %d\n", height(root));

       printf("\n=== High Risk (>5.0) ===\n");
    printHighRisk(root, 5.0);

       printf("\n=== Print All Humans ===\n");
    printBySpecies(root, "Human");


    
   

    
   printf("\nDeleting ID 1003...\n");
    root = deleteNode(root, 1003);
    inorder(root);

    //freeTree(root);

    return 0;
}



Node* insert(Node *root, Patient p) {
    
    Node** trav = &root;

    for(;*trav != NULL && (*trav)->data.patientID != p.patientID;) {
        trav = (*trav)->data.riskLevel < p.riskLevel ? &(*trav)->right : &(*trav)->left;
    }
    if (*trav == NULL) {
        Node* new = createNode(p);
        *trav = new;
    }

    return root;
}
Node* createNode(Patient p) {

    Node* new = malloc(sizeof(Node));
    if (!new) return NULL;
    new->data = p;
    new->left = new->right = NULL;
    return new;
}


Node* search(Node *root, int id) {
    if (root == NULL) return NULL;

    if (root->data.patientID == id) return root;

   
    Node* f = search(root->left, id);
    if (f != NULL) return f;

    Node* r = search(root->right, id);
}


int countNodes(Node *root) {
    if (root == NULL) return 0;
    int l = countNodes(root->left);
    int r = countNodes(root->right);

    return l + r +1;
}          

// 1
int height(Node *root) {
    if (root == NULL) return -1;
    int c = height(root->left);
    int c2 = height(root->right);

    return (c < c2 ? c2 : c) +1;
}                        // 2
Node* findMin(Node *root) {
    if (root == NULL) return NULL;

    while (root->left) {
        root = root->left;
    }

    return root;

}
Node* findMax(Node *root) {
    if (root == NULL) return NULL;
    while (root->right) {
        root = root->right;
    }

    return root;
}                 
Node* deleteNode(Node *root, int id) {

    if (root == NULL) return root;

    root->left = deleteNode(root->left, id);
    root->right = deleteNode(root->right, id);

    if (root->data.patientID == id) {
        Node* temp = root;

        if (root->left == NULL && root->right == NULL) {
            free(temp);
            root = NULL;
        }else if (root->left == NULL) {
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
            root->right = deleteNode(root->right, succ->data.patientID);
        }
        return root;

    }
    return root;
}    

void printHighRisk(Node *root, float threshold) {

    if (root == NULL) return;
    

     printHighRisk(root->left, threshold);
    if(root->data.riskLevel > threshold) {
        printf("ID: %d | %-10s | %-10s | %-12s | Risk: %.2f\n",
        root->data.patientID,
        root->data.name,
        root->data.species,
        root->data.ailment,
        root->data.riskLevel
    );
    }
    printHighRisk(root->right, threshold);
}



void printBySpecies(Node *root, const char *sp) {

    if (root==NULL) return;
    printBySpecies(root->left, sp);
    if (strcmp(root->data.species, sp) == 0) {
        printf("ID: %d | %-10s | %-10s | %-12s | Risk: %.2f\n",
        root->data.patientID,
        root->data.name,
        root->data.species,
        root->data.ailment,
        root->data.riskLevel
    );

    }
    printBySpecies(root->right, sp);
}

  

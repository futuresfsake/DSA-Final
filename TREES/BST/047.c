#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int speciesCode;   // BST key
    char* speciesName; // dynamically allocated
    int dangerLevel;
} Alien;

typedef struct node {
    Alien data;
    struct node* left;
    struct node* right;
} BST;

// ===================== PROTOTYPES =====================
BST* insertBST(BST* root, int code, const char* name, int danger);
BST* deleteBST(BST* root, int code);    // must free speciesName
BST* searchBST(BST* root, int code);

void inorder(BST* root);
void preorder(BST* root);
void postorder(BST* root);

int countNodes(BST* root);
int countLeaves(BST* root);
int heightBST(BST* root);
void freeAll(BST* root);

// ===================== TEST =====================
void testAll() {
    BST* db = NULL;

    // ================= Insert =================
    db = insertBST(db, 50, "Xenomorph", 90);
    db = insertBST(db, 20, "Martian", 30);
    db = insertBST(db, 70, "Predator", 70);
    db = insertBST(db, 10, "Gremlin", 20);
    db = insertBST(db, 30, "Klingon", 55);
    db = insertBST(db, 90, "Wookie", 95);

    printf("=== Inorder Traversal ===\n");
    inorder(db);

    printf("\n=== Count/Height Analysis ===\n");
    printf("Total nodes: %d\n", countNodes(db));
    printf("Leaves: %d\n", countLeaves(db));
    printf("Height: %d\n", heightBST(db));

    // ================= Search =================
    int codesToSearch[] = {70, 25, 90};
    for(int i=0;i<3;i++){
        BST* found = searchBST(db, codesToSearch[i]);
        if(found)
            printf("Found code %d: %s (Danger %d)\n", found->data.speciesCode, found->data.speciesName, found->data.dangerLevel);
        else
            printf("Code %d not found.\n", codesToSearch[i]);
    }

    // ================= Delete =================
    printf("\nDeleting 20 and 70...\n");
    db = deleteBST(db, 20);
    db = deleteBST(db, 70);

    printf("Inorder after deletion:\n");
    inorder(db);

    printf("\nUpdated counts:\n");
    printf("Total nodes: %d\n", countNodes(db));
    printf("Leaves: %d\n", countLeaves(db));
    printf("Height: %d\n", heightBST(db));

    
    // ================= Free all memory =================
    while(db) {
        db = deleteBST(db, db->data.speciesCode);
    }
    printf("\nAll nodes deleted, memory freed.\n");

    freeAll(db);
db = NULL;

}


int main() {
    testAll();
    return 0;
}

BST* insertBST(BST* root, int code, const char* name, int danger) {
    if (root == NULL) {
        
        BST* node = malloc(sizeof(BST));
        node->data.speciesCode = code;
        node->data.speciesName = malloc(strlen(name)+1);
        strcpy(node->data.speciesName, name);
        node->data.dangerLevel = danger;

        node->left = node->right= NULL;

        return node;
    }


    if (root->data.speciesCode == code) {
        return root;

    }

    if (root->data.speciesCode < code) {
        root->right = insertBST(root->right, code, name, danger);
    } else if (root->data.speciesCode > code) {
        root->left = insertBST(root->left, code, name, danger);
    }

    return root;
    
}


BST* deleteBST(BST* root, int code) {

    if (root == NULL) return NULL;

    if (root->data.speciesCode < code) {
        root->right = deleteBST(root->right, code);
    } else if (root->data.speciesCode > code) {
        root->left = deleteBST(root->left, code);
    }




    if (root->data.speciesCode == code) {

        if (root->right == NULL && root->left == NULL) {
            free(root->data.speciesName);
            free(root);
            root = NULL;
            return root;
        }  else if (root->left == NULL) {
            BST* temp = root->right;
            free(root->data.speciesName);

            free(root);
            return temp;
        } else if (root->right == NULL) {
            BST* temp = root->left;
              free(root->data.speciesName);

            free(root);
            return temp;
        } else {
            BST* succ = root->right;
            while (succ->left) {
                succ = succ->left;
            }

            free(root->data.speciesName);
            root->data.dangerLevel = succ->data.dangerLevel;
            root->data.speciesName = malloc(strlen(succ->data.speciesName)+1);
            root->data.speciesCode = succ->data.speciesCode;
            strcpy(root->data.speciesName, succ->data.speciesName);


            root->right = deleteBST(root->right, succ->data.speciesCode);
        }
    }
    return root;
} // must free speciesName
BST* searchBST(BST* root, int code) {

    if (root == NULL) return NULL;


    if (root->data.speciesCode == code) {
        return root;
    }


    BST* left = searchBST(root->left, code);
    if (left != NULL) return left;


    BST* right = searchBST(root->right, code);
    if (right != NULL) return right;

    return NULL;
}

void freeAll(BST* root) {
    if(!root) return;
    freeAll(root->left);
    freeAll(root->right);
    free(root->data.speciesName);
    free(root);
}



void inorder(BST* root) {
    if (root == NULL) return;
    
    inorder(root->left);
    printf("Code: %d | Name: %s \n", root->data.speciesCode, root->data.speciesName);
    inorder(root->right);
}



int countNodes(BST* root) {
    if (root == NULL) return 0;
    int left = countNodes(root->left);
    int right = countNodes(root->right);

    return left + right +1;
}
int countLeaves(BST* root) {

    if (root == NULL) return 0;

    if (root->left == NULL && root->right == NULL) {
        return 1;
    }

    int left = countLeaves(root->left);
    int right = countLeaves(root->right);

    return left+right;
}


int heightBST(BST* root) {
    if (root == NULL) return 0;

    int left = heightBST(root->left);
    int right = heightBST(root->right);

    return (left < right ? right : left) +1;
}
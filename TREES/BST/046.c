#include <stdio.h>
#include <stdlib.h>

// ===================== STRUCTS =====================

typedef struct {
    int packageID;
    float weightKg;
} Package;

typedef struct node {
    Package pkg;
    struct node* left;
    struct node* right;
} BST;


// ===================== PROTOTYPES =====================


typedef struct {
    BST* stack[100];
    int top;
}Stack;

void push(Stack* s, BST* node) {

    s->stack[++s->top] = node;
}
BST* pop(Stack* s) {
    return s->stack[s->top--];
}
// Core operations
BST* insertBST(BST* root, int id, float w);
BST* deleteBST(BST* root, int id);
BST* searchBST(BST* root, int id);

// Traversals
void inorder(BST* root);
void preorder(BST* root);
void postorder(BST* root);

// Analysis
int countNodes(BST* root);
float sumWeights(BST* root);
int countLeaves(BST* root);
int heightBST(BST* root);

// Extra operations
int findMin(BST* root);
int findMax(BST* root);
void filterLighterThan(BST* root, float maxWeight);
void bfs();

// Test function
void testAll();


// ===================== MAIN =====================

int main() {
    testAll();
    return 0;
    
}





void testAll() {

    BST* depot = NULL;

    // Build the tree
    depot = insertBST(depot, 50, 10.5);
    depot = insertBST(depot, 30, 5.0);
    depot = insertBST(depot, 70, 8.2);
    depot = insertBST(depot, 20, 3.5);
    depot = insertBST(depot, 40, 4.0);
    depot = insertBST(depot, 90, 7.3);

    printf("=== Inorder (sorted) ===\n");
    inorder(depot);
    // expected order: 20, 30, 40, 50, 70, 90

    printf("\n=== Preorder ===\n");
    preorder(depot);
    // expected (one possible): 50 30 20 40 70 90

    printf("\n=== Postorder ===\n");
    postorder(depot);
    // expected (one possible): 20 40 30 90 70 50

    printf("\nTotal packages: %d\n", countNodes(depot));
    // expected: 6

    printf("Total weight: %.2f\n", sumWeights(depot));
    // expected: 38.50

    printf("Number of leaves: %d\n", countLeaves(depot));
    // expected: 3 (20, 40, 90)

    printf("Height of BST: %d\n", heightBST(depot));
    // expected height: 3

    printf("Minimum ID: %d\n", findMin(depot));
    // expected: 20

    printf("Maximum ID: %d\n", findMax(depot));
    // expected: 90

 
    printf("\n=== Search 70 ===\n");
    BST* found = searchBST(depot, 70);
    if (found) {
         printf("%d %.2f found", found->pkg.packageID, found->pkg.weightKg);
    }else {
        printf("Not Existing..");
    }
       
    // expected: FOUND

    printf("\n=== Delete 30 ===\n");
    depot = deleteBST(depot, 30);

    printf("Inorder after deletion:\n");
    inorder(depot);
    // expected: 20, 40, 50, 70, 90  (30 removed)

    printf("\n=== BFS ===\n");
    bfs(depot);
    

}




// Insert using BST rules
BST* insertBST(BST* root, int id, float w) {
    // TODO: implement


    BST** trav = &root;
    for(; *trav != NULL && (*trav)->pkg.packageID != id;) {
        trav = (*trav)->pkg.packageID < id ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
       BST* new = (BST*) malloc(sizeof(BST));
        if (new == NULL) return NULL;

        new->pkg.packageID = id;
        new->pkg.weightKg = w;
        new->left = NULL;
        new->right = NULL;

        *trav = new;
    }


    return root;
}

// Delete a package by ID
BST* deleteBST(BST* root, int id) {
    
    if (root ==  NULL) return NULL;


    root->left = deleteBST(root->left, id);
    root->right = deleteBST(root->right, id);



    if (root->pkg.packageID == id) {

        if (root->right == NULL && root->left == NULL) {
            free(root);
            root = NULL;
            return root;
        } else if (root->left == NULL) {
            BST* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BST* temp = root->left;
            free(root);
            return temp;
        } else {
            BST* succ = root->right;
            while (succ->left) {
                succ = succ->left;
            }


            root->pkg.packageID = succ->pkg.packageID;
            root->pkg.weightKg = succ->pkg.weightKg;

            root->right = deleteBST(root->right, succ->pkg.packageID);
        }
    }

    return root;

}

// Search for a packageID
BST* searchBST(BST* root, int id) {
    // TODO: implement
    if (root == NULL) return NULL;



    if (root->pkg.packageID == id) return root;


    BST* s = searchBST(root->left, id);
    if (s != NULL) return s;

    BST* s1 = searchBST(root->right, id);
    if (s1 != NULL) return s1;

    return NULL;
}

// Traversals
void inorder(BST* root) {
    
    Stack s;
    s.top = -1;

    BST* trav = root;

    while (trav || s.top != -1) {
        while (trav) {
            push(&s, trav);
            
            trav = trav->left;
        }
        trav = pop(&s);
        printf(" %d (%.2f kg) \n", trav->pkg.packageID, trav->pkg.weightKg);
        trav = trav->right;
    }
     }


void preorder(BST* root) { 
    Stack s;
    s.top = -1;

    push(&s, root);

    while (s.top != -1) {
        BST* trav = pop(&s);
    printf(" %d (%.2f kg) \n", trav->pkg.packageID, trav->pkg.weightKg);

    if (trav->right) push(&s, trav->right);
    if (trav->left) push(&s, trav->left);

        
    }
 }


void postorder(BST* root) {

    Stack s1,s2;
    s1.top = -1;
    s2.top = -1;

    push(&s1, root);

    while (s1.top !=-1) {
        BST* trav = pop(&s1);
        push(&s2, trav);

        if (trav->left) push(&s1, trav->left);
        if (trav->right) push(&s1, trav->right);

    }

    while (s2.top != -1) {
        BST* trav = pop(&s2);
    printf(" %d (%.2f kg) \n", trav->pkg.packageID, trav->pkg.weightKg);

    }

 }

 void bfs (BST* root) {


    BST* queue[100];
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while (front <rear) {

        BST* trav = queue[front++];
         printf(" %d (%.2f kg) \n", trav->pkg.packageID, trav->pkg.weightKg);

         if (trav->left) queue[rear++] = trav->left;
         if (trav->right) queue[rear++] = trav->right;

        
    }
 }

// Counts & sums
int countNodes(BST* root) { 
    
    if (root == NULL) return 0;

    int c = countNodes(root->left);
    int c2 = countNodes(root->right);

    return c+c2+1;
}
float sumWeights(BST* root) { 
    if (root == NULL) return 0;


    float left = sumWeights(root->left);
    float right = sumWeights(root->right);

    return left+right+root->pkg.weightKg;
 }
int countLeaves(BST* root) { 
    
    if (root == NULL) return 0;
    

    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    int l = countLeaves(root->left);
    int r = countLeaves(root->right);

    return l+r;
 }
int heightBST(BST* root) { 
    if (root == NULL) return 0;

    int left = heightBST(root->left);
    int right = heightBST(root->right);
    return (left < right ? right : left) +1;
 }

// Min/max package ID
int findMin(BST* root) { 
    while (root->left) {
        root = root->left;
    }

    return root->pkg.packageID;
 }


int findMax(BST* root) {
    while (root->right) {
        root = root->right;
    }

    return root->pkg.packageID;
}



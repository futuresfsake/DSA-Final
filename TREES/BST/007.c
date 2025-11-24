/**
 * BINARY SEARCH TREE - Complete Boilerplate for Product BST
 * Adjusted to match:
 *   typedef struct { int prodqty; int id; char name[100]; } Product;
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    int prodqty;
    int id;
    char name[100];
} Product;

// Node structure
typedef struct TreeNode {
    Product data;
    struct TreeNode* left;
    struct TreeNode* right;
}  Node,TreeNode, *NodePtr;

// ==================== CREATE NEW NODE ====================
TreeNode* createNode(Product data) {
    
    TreeNode* prods = malloc(sizeof(Node));
    if (!prods) {
        return NULL;
    }

    prods->data = data;
    prods->left = NULL;
    prods->right = NULL;
    return prods;
}

// ==================== INSERT ====================
TreeNode* insert(TreeNode* root, Product data) {
   

    NodePtr* trav = &root;

    for(;*trav != NULL && (*trav)->data.id != data.id;) {
        trav = ((*trav)->data.prodqty < data.prodqty) ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav != NULL) return NULL;
    
    Node* new = createNode(data);

    *trav = new;
    return root;
}

//! recursive version, it means you have to traverse to the whole list
bool search(TreeNode* root, int id) {
    // TODO: search by product ID

    if (root == NULL) return false;

    if (root->data.id == id) return true;

    return search(root->left, id) || search(root->right, id);
}

// ==================== FIND MINIMUM ====================
Product findMin(TreeNode* root) {
    // TODO: go left until NULL

    if (root == NULL) {
    Product p = {0, -1, ""};
    return p;}

    if (root->left == NULL) {
        return root->data;
    }
    

    return findMin(root->left);
}

// ==================== FIND MAXIMUM ====================
Product findMax(TreeNode* root) {
    // TODO: go right until NULL

    if (root == NULL) {
    Product p = {0, -1, ""};
    return p;
    }

    if (root->right == NULL) {
        return root->data;
    }

    return findMax(root->right);
}

// // ==================== DELETE NODE ====================
// TreeNode* deleteNode(TreeNode* root, int id) {
//     // TODO: delete node by product ID

//     if (root == NULL) return root;

//     if (root->data.id == id) {
//         Product p = root->data;

//         TreeNode** trav = &root;
//         for(;*trav != NULL && (*trav)->data.id != p.id;) {
//             trav = (*trav)->data.prodqty < p.prodqty ? &(*trav)->right : &(*trav)->left;
//         }

//         NodePtr temp = *trav;

//         if ((*trav)->right == NULL && (*trav)->left == NULL) {
//             free(temp);
//             *trav = NULL;
//         }

//         else if ((*trav)->left == NULL) {
//             *trav = (*trav)->right;
//             free(temp);
//         } 
//         else if ((*trav)->right == NULL) {
//             *trav = (*trav)->left;
//             free(temp);
//         } else {
//             NodePtr* succ = &(*trav)->right;
//             while ((*succ)->left) {
//                 succ = &(*succ)->left;
//             }

//             (*trav)->data = (*succ)->data;
//             root = deleteNode(*succ, (*succ)->data.id);


//         }



//     }
    
//     root = deleteNode(root->left, id);
//     root = deleteNode(root->right, id);
// }



TreeNode* deleteNode(TreeNode* root, int id) {
    if (root == NULL) return NULL;

    root->left = deleteNode(root->left, id);
    root->right = deleteNode(root->right, id);

    if (root->data.id == id) {
       
        NodePtr temp = root;

        if (root->right == NULL && root->left == NULL) {
            free(temp);
            return NULL;
        }

        else if (root->left == NULL) {
            root= root->right;
            free(temp);
        } 
        else if (root->right == NULL) {
            root= root->left;
            free(temp);
        } else {
            NodePtr succ =root->right;
            while (succ->left) {
                succ = root->left;
            }

            (root)->data = (succ)->data;
            root->right = deleteNode(root->right, (succ)->data.id);



    }
}

return root;
}



// ==================== INORDER TRAVERSAL ====================
void inorderTraversal(TreeNode* root) {
    if (root == NULL) return;

    inorderTraversal(root->left);

    printf("\n[ID: %d | Qty: %d | Name: %s]  \n",
           root->data.id,
           root->data.prodqty,
           root->data.name);

    inorderTraversal(root->right);
}


// ==================== HEIGHT ====================
int height(TreeNode* root) {
    
    if (root == NULL) return -1;

    int h1 = height(root->left);
    int h2 = height(root->right);
    return (h1 < h2 ? h2: h1 )+1;
}

// ==================== COUNT NODES ====================
int countNodes(TreeNode* root) {

    //! return 0, because counting nodes is an additive operation, if subtree is empty, it contributes 0 nodes
    if (root == NULL) return 0;

    int c1 = countNodes(root->left);
    int c2 = countNodes(root->right);

    return c1+c2+1;
}

// ==================== FREE TREE ====================
void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// ==================== MAIN ====================
int main() {
    TreeNode* root = NULL;

    printf("=== Product BST Test ===\n");

    Product p1 = {100, 50, "Item A"};
    Product p2 = {50, 30, "Item B"};
    Product p3 = {80, 70, "Item C"};
    Product p4 = {20, 20, "Item D"};
    Product p5 = {10, 40, "Item E"};

    root = insert(root, p1);
    root = insert(root, p2);
    root = insert(root, p3);
    root = insert(root, p4);
    root = insert(root, p5);

    printf("\nInorder traversal: ");
    inorderTraversal(root);

    printf("\nSearch for ID 40: %s\n", search(root, 40) ? "Found" : "Not Found");

    Product mn = findMin(root);
    Product mx = findMax(root);
    printf("\nMin product ID: %d\n", mn.id);
    printf("Max product ID: %d\n", mx.id);

    printf("\nHeight: %d\n", height(root));
    printf("Total nodes: %d\n", countNodes(root));

    printf("\nDeleting ID 30...\n");
    root = deleteNode(root, 30);
    inorderTraversal(root);

   
    return 0;
}

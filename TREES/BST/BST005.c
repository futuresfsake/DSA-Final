#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ============================
//      STRUCT DEFINITIONS
// ============================

typedef struct ItemNode {
    int item_id;                   // key
    char *description;             // dynamically allocated
    struct ItemNode *left;
    struct ItemNode *right;
} ItemNode;

typedef struct ItemBST {
    ItemNode *root;
} ItemBST;


// ============================
//      FUNCTION DECLARATIONS
//      (ITERATIVE ONLY)
// ============================

// Initialization
void init_item_bst(ItemBST *tree) {
    tree->root = NULL;
}

// Node creation
ItemNode* create_item_node(int item_id, const char *desc) {

    ItemNode* new = malloc(sizeof(ItemNode));
    if (!new) return NULL;

    new->item_id = item_id;
    new->description = malloc(strlen(desc)+1);
    strcpy(new->description, desc);
    new->left = NULL;
    new->right = NULL;
    return new;


}

// Iterative insertion
bool insert_item_iterative(ItemBST *tree, int item_id, const char *desc) {

    ItemNode** trav = &(tree->root);
    for(;*trav!= NULL && (*trav)->item_id != item_id;) {
        trav =  (*trav)->item_id < item_id ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {

        ItemNode* catcher = create_item_node(item_id, desc);
        *trav = catcher;
        return true;
    }
    return false;
}

// Iterative search
ItemNode* search_item_iterative(ItemBST *tree, int item_id) {

    ItemNode* trav = tree->root;
    for(;trav != NULL;) {
        if (trav->item_id == item_id) {
            return trav;
        }
        trav = trav->item_id < item_id ? trav->right : trav->left;
    }
    return NULL;
}

ItemNode* deleteItemNodeRecursive(ItemNode* root, int id) {
    if (!root) return NULL;

    if (id < root->item_id)
        root->left = deleteItemNodeRecursive(root->left, id);
    else if (id > root->item_id)
        root->right = deleteItemNodeRecursive(root->right, id);
    else {
        // Node found
        if (!root->left && !root->right) {
            free(root->description);
            free(root);
            return NULL;
        } 
        else if (!root->left) {
            ItemNode* tmp = root->right;
            free(root->description);
            free(root);
            return tmp;
        } 
        else if (!root->right) {
            ItemNode* tmp = root->left;
            free(root->description);
            free(root);
            return tmp;
        } 
        else {
            // Node with two children: use predecessor
            ItemNode* pred = root->left;
            while (pred->right)
                pred = pred->right;

            free(root->description);
            root->item_id = pred->item_id;
            root->description = malloc(strlen(pred->description)+1);
            strcpy(root->description, pred->description);

            // Recursively delete predecessor
            root->left = deleteItemNodeRecursive(root->left, pred->item_id);
        }
    }
    return root;
}


// Recursive OR iterative free (your choice)
void free_item_tree(ItemNode *root) {
    if (root == NULL) return;

    free_item_tree(root->left);
    free_item_tree(root->right);
    free(root->description);
    free(root);
}


// ============================
//     EXTRA TEST FUNCTIONS
// ============================

// Inorder traversal (recursive allowed)
void inorder_items(ItemNode *root) {
    if (!root) return;
    inorder_items(root->left);
    printf("ID: %d | Desc: %s\n", root->item_id, root->description);
    inorder_items(root->right);
}

// Display whole tree
void display_item_tree(ItemBST *tree) {
    printf("\n===== WAREHOUSE INVENTORY: INORDER =====\n");
    if (!tree->root) {
        printf("(empty tree)\n");
        return;
    }
    inorder_items(tree->root);
    printf("=======================================\n\n");
}



// ============================
//            MAIN
// ============================

int main() {
    ItemBST warehouse;
    init_item_bst(&warehouse);

    printf("===== Warehouse Inventory BST (Iterative) =====\n");

    // ---------- INSERT TESTS ----------
    printf("\nInserting items...\n");
    insert_item_iterative(&warehouse, 50, "Bolts");
    insert_item_iterative(&warehouse, 20, "Nails");
    insert_item_iterative(&warehouse, 70, "Wood Panels");
    insert_item_iterative(&warehouse, 10, "Glue");
    insert_item_iterative(&warehouse, 30, "Screws");
    insert_item_iterative(&warehouse, 60, "Paint");
    insert_item_iterative(&warehouse, 90, "Cement");

    // ---------- DISPLAY TREE ----------
    display_item_tree(&warehouse);

    // ---------- SEARCH TESTS ----------
    printf("Searching for item 70...\n");
    ItemNode *f1 = search_item_iterative(&warehouse, 70);
    if (f1)
        printf("FOUND: ID=%d, Desc=%s\n", f1->item_id, f1->description);
    else
        printf("Item 70 NOT FOUND.\n");

    printf("\nSearching for missing item 999...\n");
    ItemNode *f2 = search_item_iterative(&warehouse, 999);
    if (f2)
        printf("FOUND: ID=%d, Desc=%s\n", f2->item_id, f2->description);
    else
        printf("Item 999 NOT FOUND.\n");

int it = 20;
printf("Deleting item %d: \n", it);
warehouse.root = deleteItemNodeRecursive(warehouse.root, it);
printf("%d deleted successfully\n", it);

    // ---------- FINAL DISPLAY ----------
    display_item_tree(&warehouse);

    // ---------- FREE TREE ----------
    printf("Freeing BST memory...\n");
    free_item_tree(warehouse.root);
    warehouse.root = NULL;

    printf("Done.\n");
    return 0;
}


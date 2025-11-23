/*
 * Problem Statement: File System Indexer (Binary Search Tree)

 *
 * The operating system's file indexing service needs an upgrade!
 * Files are indexed by their unique, numerical File ID (FID).
 * We need an efficient way to store and retrieve these file records,
 * so you will implement a Binary Search Tree (BST).
 *
 * Data Structure Requirements:
 * 1. The BST will store records based on the integer File ID (FID).
 * 2. The BST must maintain the property: left_child.FID < parent.FID < right_child.FID.
 *
 * Core Operations:
 * 1. Insertion: Add a new file record while maintaining the BST property.
 * 2. Search: Check if a File ID exists.
 *
 * Note: You must handle dynamic memory management for the FileNode structures.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// --- Type Definitions ---

/**
 * @brief Represents a single file record stored in a node.
 */
typedef struct FileNode {
    int fid;                   // The File ID (The Key for the BST)
    char *path;                // Dynamically allocated file path string
    struct FileNode *left;     // Pointer to the left child
    struct FileNode *right;    // Pointer to the right child
} FileNode;

/**
 * @brief The main BST structure, holding a pointer to the root.
 */
typedef struct BST {
    FileNode *root;
} BST;

// --- Function Prototypes (Implementations Required) ---

/**
 * @brief Initializes the BST structure.
 * @param tree Pointer to the BST instance.
 */
void init_tree(BST *tree) {
    tree->root = NULL;
}

/**
 * @brief Creates a new FileNode dynamically.
 * @param fid The File ID.
 * @param path The file path string.
 * @return A pointer to the newly allocated FileNode, or NULL on failure.
 */
FileNode *create_node(int fid, const char *path) {

    FileNode *new = malloc(sizeof(FileNode));
    if (!new) {return NULL;
    }

    new->fid = fid;
    new->path = malloc(strlen(path)+1);
    if (!new->path) return NULL;
    strcpy(new->path, path);
    new->left=NULL;
    new->right = NULL;
    return new;
}

/**
 * @brief Inserts a new FileNode into the BST recursively, maintaining the BST property.
 * If the FID already exists, insertion is skipped (no duplicates allowed).
 * @param current Pointer to the current node being examined (starts at BST->root).
 * @param newNode Pointer to the FileNode to be inserted.
 * @return The pointer to the root of the subtree after insertion (used for recursion).
 */
FileNode *insert_node_recursive(FileNode *current, FileNode *newNode) {


   if (current == NULL) {
    return newNode;
   }

   if (current->fid < newNode->fid) {
    current->right = insert_node_recursive(current->right, newNode);
   } if (current->fid > newNode->fid) {
    current->left = insert_node_recursive(current->left, newNode);
   }
   return current;
}

/**
 * @brief Searches the BST for a given File ID.
 * @param tree Pointer to the BST structure.
 * @param fid The File ID to search for.
 * @return The pointer to the FileNode if found, otherwise NULL.
 */
FileNode *search_file(BST *tree, int fid) {

    FileNode* trav = tree->root;

    for(;trav != NULL;) {
        if (trav->fid == fid) {
            return trav;
        }
        trav = trav->fid < fid ? trav->right : trav->left;
    }
    return NULL;
}


/**
 * @brief Public interface for inserting a FileNode into the BST.
 * @param tree Pointer to the BST structure.
 * @param fid The File ID to insert.
 * @param path The file path string.
 * @return true on successful insertion or if FID already exists (skipped), false on failure.
 */
bool insert_file(BST *tree, int fid, const char *path) {

    FileNode* new = create_node(fid, path);
    if (!new) return false;

    if (search_file(tree, fid)) {
        free(new->path);
        free(new);
        return true;
    }

    tree->root = insert_node_recursive(tree->root, new);
    return true;
}


/**
 * @brief Frees all dynamically allocated memory within the BST (nodes and path strings).
 * @param current Pointer to the current node (starts at BST->root).
 */
void free_tree_recursive(FileNode *current) {
    if (current == NULL) return;

    free_tree_recursive(current->left);
    free_tree_recursive(current->right);
    free(current->path);
    free(current);
}

// --- Sample Main Function for Testing ---
int main() {
    BST file_index;
    init_tree(&file_index);

    printf("File System Indexer Simulation (Binary Search Tree)\n");
    printf("----------------------------------------------------\n");

    // Test Case 1: Initial Insertions (Creating the BST structure)
    printf("\n--- Test 1: Initial Insertions ---\n");
    insert_file(&file_index, 50, "/root/data/system_logs.txt"); // Root
    insert_file(&file_index, 30, "/root/config/network.cfg");
    insert_file(&file_index, 70, "/root/user/profile.dat");
    insert_file(&file_index, 20, "/root/config/config_old.bak");
    insert_file(&file_index, 40, "/root/data/temp_1.tmp");
    insert_file(&file_index, 60, "/root/user/docs/report.pdf");
    insert_file(&file_index, 80, "/root/bin/start.sh");
    printf("Initial tree built with 7 unique nodes.\n");
    

//*  [Image of binary search tree with values 50, 30, 70, 20, 40, 60, 80]


    // Test Case 2: Successful Search
    printf("\n--- Test 2: Search for Existing FID (40) ---\n");
    FileNode *found_40 = search_file(&file_index, 40);
    if (found_40) {
        printf("  [Search HIT] Found FID %d, Path: %s\n", found_40->fid, found_40->path);
    } else {
        printf("  [Search MISS] FID 40 not found (ERROR).\n");
    }

    // Test Case 3: Failed Search
    printf("\n--- Test 3: Search for Non-existent FID (99) ---\n");
    FileNode *found_99 = search_file(&file_index, 99);
    if (found_99 == NULL) {
        printf("  [Search MISS] FID 99 not found (Expected).\n");
    } else {
        printf("  [Search HIT] FID 99 found (ERROR).\n");
    }

    // Test Case 4: Redundant Insertion (Expected Skip)
    printf("\n--- Test 4: Redundant Insertion (FID 50) ---\n");
    bool redundant_insert = insert_file(&file_index, 50, "/root/data/NEW_LOG.txt");
    if (redundant_insert) {
        printf("  [Insert Skip] Insertion skipped because FID 50 already exists.\n");
    } else {
        printf("  [Insert Error] Insertion failed.\n");
    }

    printf("\n--- Cleanup and Exit ---\n");
    free_tree_recursive(file_index.root);
    file_index.root = NULL;
    printf("All tree memory successfully freed.\n");

    return 0;
}
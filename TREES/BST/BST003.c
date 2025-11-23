#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// --- Type Definitions ---
typedef struct ServerNode {
    int sid;
    char *config_path;
    struct ServerNode *left;
    struct ServerNode *right;
} ServerNode;

typedef struct BST {
    ServerNode *root;
} BST;

// --- Function Prototypes (Your Implementation Goes Here) ---
void init_tree(BST *tree);
ServerNode *create_node(int sid, const char *path);
ServerNode *insert_node_recursive(ServerNode *current, ServerNode *newNode);
bool insert_server(BST *tree, int sid, const char *path);
ServerNode *search_server(BST *tree, int sid);
void free_tree_recursive(ServerNode *current);

// --- Main Program Logic ---

int main() {
    BST server_index;
    init_tree(&server_index);

    printf("Cloud Server Identifier Indexer Simulation (Binary Search Tree)\n");
    printf("----------------------------------------------------\n");
    printf("Indexing Key: Server ID (SID)\n");

    // Test Case 1: Initial Insertions (Creating the BST structure)
    printf("\n--- Test 1: Initial Insertions ---\n");
    printf("  [Insert] SID 50 (Root)\n");
    insert_server(&server_index, 50, "/etc/servers/50/config.ini"); 
    printf("  [Insert] SID 30\n");
    insert_server(&server_index, 30, "/etc/servers/30/config.ini");
    printf("  [Insert] SID 70\n");
    insert_server(&server_index, 70, "/etc/servers/70/config.ini");
    printf("  [Insert] SID 20\n");
    insert_server(&server_index, 20, "/etc/servers/20/config.ini");
    printf("  [Insert] SID 40\n");
    insert_server(&server_index, 40, "/etc/servers/40/config.ini");
    printf("  [Insert] SID 60\n");
    insert_server(&server_index, 60, "/etc/servers/60/config.ini");
    printf("  [Insert] SID 80\n");
    insert_server(&server_index, 80, "/etc/servers/80/config.ini");
    printf("Initial BST built with 7 unique nodes (Root: 50).\n");
    // 

//* [Image of binary search tree with values 50, 30, 70, 20, 40, 60, 80]


    // Test Case 2: Successful Search (Expected HIT)
    printf("\n--- Test 2: Search for Existing SID (40) ---\n");
    ServerNode *found_40 = search_server(&server_index, 40);
    if (found_40) {
        printf("  [Search HIT] Found SID %d, Config Path: %s\n", found_40->sid, found_40->config_path);
    } else {
        printf("  [Search MISS] SID 40 not found (ERROR: Should be HIT).\n");
    }

    // Test Case 3: Failed Search (Expected MISS)
    printf("\n--- Test 3: Search for Non-existent SID (99) ---\n");
    ServerNode *found_99 = search_server(&server_index, 99);
    if (found_99 == NULL) {
        printf("  [Search MISS] SID 99 not found (Expected).\n");
    } else {
        printf("  [Search HIT] SID 99 found (ERROR: Should be MISS).\n");
    }

    // Test Case 4: Redundant Insertion (Expected Skip)
    printf("\n--- Test 4: Redundant Insertion (SID 50) ---\n");
    bool redundant_insert = insert_server(&server_index, 50, "/etc/servers/50/new_config_attempt.ini");
    if (redundant_insert) {
        printf("  [Insert Status] Insertion was logically skipped because SID 50 already exists.\n");
    } else {
        printf("  [Insert Error] Insertion failed for existing SID.\n");
    }

    // Test Case 5: Insertion Failure Test (Simulated Malloc failure for path)
    printf("\n--- Test 5: New Insertion (SID 10) ---\n");
    bool new_insert = insert_server(&server_index, 10, "/etc/servers/10/config.ini");
    if (new_insert) {
        printf("  [Insert Success] SID 10 inserted successfully.\n");
    } else {
        printf("  [Insert Failure] SID 10 insertion failed (Simulated Malloc Failure).\n");
    }


    printf("\n--- Cleanup and Exit ---\n");
    free_tree_recursive(server_index.root);
    server_index.root = NULL;
    printf("All tree memory successfully freed. Index destroyed.\n");

    return 0;
}

void init_tree(BST *tree) {
    tree->root = NULL;
}

ServerNode *create_node(int sid, const char *path) {

    ServerNode* newServer = malloc(sizeof(ServerNode));
    if (!newServer)return NULL;

    newServer->sid = sid;
    newServer->config_path = malloc(strlen(path)+1);
    if (!newServer->config_path) {
        free(newServer); 
        return NULL; }


    strcpy(newServer->config_path, path);
    
    newServer->left = NULL;
    newServer->right = NULL;
    return newServer;

}

ServerNode *insert_node_recursive(ServerNode *current, ServerNode *newNode) {

    if (current == NULL) return newNode;


    if (current->sid < newNode->sid) {
        current->right = insert_node_recursive(current->right,newNode );
    }
    if (current->sid> newNode->sid) {
        current->left = insert_node_recursive(current->left, newNode);
    }

    return current;

}


bool insert_server(BST *tree, int sid, const char *path) {

    if (search_server(tree, sid)) {
        return true;
    }

    ServerNode* new = create_node(sid, path);
    if (!new) return false;

    tree->root = insert_node_recursive(tree->root, new);
    return true;
}


ServerNode *search_server(BST *tree, int sid) {
    ServerNode* trav = tree->root;

    for(; trav != NULL; ) {
        if (trav->sid == sid) {
            return trav;
        }
        trav = trav->sid < sid ? trav->right : trav->left;
    }

    return NULL;
}


void free_tree_recursive(ServerNode *current) {
    if (current == NULL) return;

    free_tree_recursive(current->left);
    free_tree_recursive(current->right);
    free(current->config_path);
    free(current);
}

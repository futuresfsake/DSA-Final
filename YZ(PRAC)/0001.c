#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 10
#define ROOT_NODE -1
#define INVALID_NODE -2


// Type definition for a node index
typedef int Node;

// 1. Linked List Node Definition
// Each node in the linked list represents a child of the parent (array index)
typedef struct ChildNode {
    Node childIndex;
    struct ChildNode *next;
} ChildNode;

// 2. Tree Structure Definition
// The Tree holds the root index and an array of head pointers for the children lists.
typedef struct {
    Node rootIndex;
    // Array of heads of linked lists.
    // children[i] points to the first child of node i.
    ChildNode* children[MAX_NODES];
} Tree;


/**
 * @brief Initializes the Tree structure.
 * Sets the root index to INVALID_NODE and all children list heads to NULL.
 * @param T Pointer to the Tree structure to initialize.
 */
void initializeTree(Tree *T) {

    for(int i = 0; i < MAX_NODES; i++) {
        T->children[i] = NULL;
    }

    T->rootIndex = -2;

}

/**
 * @brief Designates a node as the root.
 * @param T Pointer to the Tree structure.
 * @param r The index of the node to be set as root.
 */
void makeRoot(Tree *T, Node r) {

    if (r < 0 || r >= MAX_NODES) {
        printf("Error: root index out of bounds!\n");
        return;
    }
    if (T->rootIndex != INVALID_NODE) {
        printf("Root is already set.\n");
        return;
    }
    T->rootIndex = r;
    printf("Successfully initialized!\n");
}

/**
 * @brief Adds a new child node to the parent's linked list.
 * @param T Pointer to the Tree structure.
 * @param parent_index The index of the parent node (array index).
 * @param child_index The index of the child node (value in the linked list).
 */
void addChild(Tree *T, Node parent_index, Node child_index) {


    // TODO

    if (parent_index < 0 || parent_index >= MAX_NODES || 
        child_index < 0 || child_index >= MAX_NODES) {
        printf("Error: node index out of bounds!\n");
        return;
    }


    ChildNode* newChild = malloc(sizeof(ChildNode));
    if (!newChild) {
        printf("Dynamic Memory allocation!");
        return;
    }

    newChild->childIndex = child_index;
    newChild->next = NULL;

    
   

    ChildNode* trav = T->children[parent_index];

    
    if (trav == NULL) {
        T->children[parent_index] = newChild;
        
    } else {

    while (trav->next != NULL) {
        trav = trav->next;
    }
    trav->next = newChild;

    }
    printf("Added successfully!\n");

}




// /**
//  * @brief Returns the parent of a given node.
//  * Requires searching through all parent lists to find the node.
//  * @param n The node index (child).
//  * @param T Pointer to the Tree structure.
//  * @return The parent node index, ROOT_NODE if n is the root, or INVALID_NODE if n is invalid/uninitialized.
//  */


Node parent(Node n, const Tree *T) {

    // If n is the root
    //* if n is the root, -1 means it has no parent
    if (n == T->rootIndex) {
        return ROOT_NODE;
    }

    // Search all children lists
    for (int i = 0; i < MAX_NODES; i++) {
        ChildNode *trav = T->children[i];

        while (trav != NULL) {
            if (trav->childIndex == n) {
                return i; // Parent found
            }
            trav = trav->next;
        }
    }

    return INVALID_NODE; // Not found
}


/**
 * @brief Returns the leftmost element (the node with the smallest index) in the tree.
 * "Leftmost" is defined as the valid node with the lowest index (0 to MAX_NODES-1).
 * @param T Pointer to the Tree structure.
 * @return The index of the leftmost element, or INVALID_NODE if the tree is empty.
 */


 //* we traverse it and check if it as a root, a parent or a child
 //* left element, returning the first i that exists, the smallest element starts at 0 to traverse

Node left(const Tree *T) {


//* traversing all possible node indices from 0 to MAX_Nodes-1;
     for (int i = 0; i < MAX_NODES; i++) {
        if (i == T->rootIndex) //* i exists as the root
            return i;

        if (T->children[i] != NULL) //* i exists as parent with children
            return i;

        // Check if i appears as a child anywhere
        for (int j = 0; j < MAX_NODES; j++) { //* exists as a child somewhere
            ChildNode *trav = T->children[j];
            while (trav != NULL) {
                if (trav->childIndex == i)
                    return i;
                trav = trav->next;
            }
        }
    }
    return INVALID_NODE; // tree is empty
}


// /**
//  * @brief Returns the rightmost element (the node with the largest index) in the tree.
//  * "Rightmost" is defined as the valid node with the highest index (MAX_NODES-1 down to 0).
//  * @param T Pointer to the Tree structure.
//  * @return The index of the rightmost element, or INVALID_NODE if the tree is empty.
//  */
Node right(const Tree *T) {
    for (int i = MAX_NODES - 1; i >= 0; i--) {
        if (i == T->rootIndex)
            return i;

        if (T->children[i] != NULL)
            return i;

        // Check if i appears as a child anywhere
        for (int j = 0; j < MAX_NODES; j++) {
            ChildNode *trav = T->children[j];
            while (trav != NULL) {
                if (trav->childIndex == i)
                    return i;
                trav = trav->next;
            }
        }
    }
    return INVALID_NODE; // tree is empty
}


/**
 * @brief Frees the memory allocated for the children linked lists.
 * @param T Pointer to the Tree structure.
 */
void freeTree(Tree *T) {
    for (int i = 0; i < MAX_NODES; i++) {
        ChildNode *current = T->children[i];
        ChildNode *next;
        while (current != NULL) {
            next = current->next;
            free(current);
            current = next;
        }
        T->children[i] = NULL; // Reset pointer to NULL after freeing
    }
    printf("\nTree memory cleaned up.\n");
}


// /**
//  * @brief Prints the contents of the tree array representation.
//  * @param T Pointer to the Tree structure.
//  */
void printTree(const Tree *T) {
    printf("--- Tree Children List Representation ---\n");
    printf("Root Index: %d\n", T->rootIndex);
    printf("Parent Index | Children List\n");
    printf("-------------|---------------\n");

    for (int i = 0; i < MAX_NODES; i++) {
        printf("%12d | ", i);
        ChildNode *current = T->children[i];
        if (current == NULL) {
            printf("(None)\n");
        } else {
            while (current != NULL) {
                printf("%d -> ", current->childIndex);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
    printf("-----------------------------------------\n");
}


int main() {
    Tree myTree;
    initializeTree(&myTree);

    // --- Building a Sample Tree ---
    // Structure:
    //      0 (Root)
    //     /  \
    //    1    2
    //   / \   |
    //  3   4  5
    //        / \
    //       8   9

    makeRoot(&myTree, 0);       // 0 is the root

    // Add children to 0
    addChild(&myTree, 0, 1);
    addChild(&myTree, 0, 2);

    // Add children to 1
    addChild(&myTree, 1, 3);
    addChild(&myTree, 1, 4);

    // Add children to 2
    addChild(&myTree, 2, 5);

    // Add children to 5
    addChild(&myTree, 5, 8);
    addChild(&myTree, 5, 9);
    // Note: Node indices 6 and 7 are valid but currently not part of the tree structure.

    printTree(&myTree);

    // --- Testing Operations ---
    printf("\n--- Testing ADT Operations ---\n");

    // 1. Test parent()
    Node node_to_check = 5;
    Node p = parent(node_to_check, &myTree);
    if (p == ROOT_NODE) {
        printf("Parent of Node %d: (It is the Root)\n", node_to_check);
    } else if (p == INVALID_NODE) {
        printf("Parent of Node %d: (Node is Invalid/Not Found)\n", node_to_check);
    } else {
        printf("Parent of Node %d: Node %d\n", node_to_check, p); // Expected: 2
    }

    node_to_check = 0; // The Root
    p = parent(node_to_check, &myTree);
    if (p == ROOT_NODE) {
        printf("Parent of Node %d: (It is the Root)\n", node_to_check); // Expected: ROOT_NODE
    } else {
        printf("Parent of Node %d: Node %d\n", node_to_check, p);
    }

    node_to_check = 7; // Not in tree
    p = parent(node_to_check, &myTree);
    if (p == INVALID_NODE) {
        printf("Parent of Node %d: (Node is Invalid/Not Found)\n", node_to_check); // Expected: INVALID_NODE
    } else {
        printf("Parent of Node %d: Node %d\n", node_to_check, p);
    }


    // 2. Test left() - smallest index with a valid node
    Node l = left(&myTree);
    if (l != INVALID_NODE) {
        printf("Leftmost Element (Smallest Index): Node %d\n", l); // Expected: 0
    } else {
        printf("Leftmost Element: Tree is empty.\n");
    }

    // 3. Test right() - largest index with a valid node
    Node r = right(&myTree);
    if (r != INVALID_NODE) {
        printf("Rightmost Element (Largest Index): Node %d\n", r); // Expected: 9
    } else {
        printf("Rightmost Element: Tree is empty.\n");
    }

    // Clean up memory
    freeTree(&myTree);

    return 0;
}
//* recursive problem

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME 50

// ===== Student Struct =====
typedef struct {
    char name[MAX_NAME];
    int score;
} Student;

// ===== BST Node Struct =====
typedef struct BSTNode {
    Student data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// ===== BST ADT =====
typedef struct {
    BSTNode* root;
} BST;

// ===== Function Declarations =====

// Initialize BST
void initBST(BST* tree) {
    tree->root = NULL;
    printf("Initialization successful!\n");
}

// Create a new node
BSTNode* createNode(Student s) {
    BSTNode*  new = malloc(sizeof(BSTNode));
    if (!new) {
        printf("Dynamic Memory allocation!\n");
        return NULL;
    }

    new->data = s;
    new->left = NULL;
    new->right = NULL;
    return new;
}

// Insert a student
void insertStudent(BST* tree, Student s) {
    
    BSTNode** trav = &(tree->root);

    for(; *trav != NULL && (*trav)->data.score != s.score ;) {
        trav = ((*trav)->data.score < s.score) ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {

        *trav = createNode(s);
    }


    printf("Insert successful!\n");

}

// Search for a student by score
BSTNode* searchByScore(BST* tree, int score) {

    BSTNode* trav = tree->root;

    for(; trav != NULL;) {
        if (trav->data.score == score) {
            return trav;
        }

        trav = (trav->data.score < score) ? trav->right : trav->left;
    }

    return NULL;

}
// Inorder traversal
void inorderTraversal(BSTNode* node) {

    if (node == NULL) return;

    inorderTraversal(node->left);
    printf("[%s, %d]\n", node->data.name, node->data.score);
    inorderTraversal(node->right);

}

// ===== Special Operations =====

// 1. Average score of students with score >= minScore
// Recursive helper
static void avgHelper(BSTNode* node, int minScore, long *sum, int *count) {
    if (!node) return;

    avgHelper(node->left, minScore, sum, count);

    if (node->data.score >= minScore) {
        *sum += node->data.score;
        (*count)++;
    }

    avgHelper(node->right, minScore, sum, count);
}

double averageAboveScore(BSTNode* root, int minScore) {
    long sum = 0;
    int count = 0;

    avgHelper(root, minScore, &sum, &count);

    return (count == 0) ? 0.0 : ((double)sum / count);
}


// 2. Delete all students with score < threshold
BSTNode* deleteScoreBelow(BSTNode* node, int threshold) {
    if (node == NULL) return NULL;

    node->left = deleteScoreBelow(node->left, threshold);
    node->right = deleteScoreBelow(node->right, threshold);


    if (node->data.score < threshold) {
        BSTNode* temp;

        if (node->left == NULL) {
            temp = node->right;
            free(node);
            return temp;

        }
        if (node->right == NULL) {
            temp = node->left;
            free(node);
            return temp;
        }

        else {
            BSTNode* succ = node->right;
            while ((succ)->left != NULL) {
                succ = succ->left;
            }

            node->data = succ->data;

            node->right = deleteScoreBelow(node->right, succ->data.score);
        }
        return node;
}
return node;

    }
    


// // Helper to free BST
// void freeBST(BSTNode* node);



int main() {
    BST tree;
    initBST(&tree);

    Student s1 = {"Alice", 75};
    Student s2 = {"Bob", 85};
    Student s3 = {"Charlie", 65};

    insertStudent(&tree, s1);
    insertStudent(&tree, s2);
    insertStudent(&tree, s3);

    printf("Inorder Traversal:\n");
    inorderTraversal(tree.root);

    int grade  =85;

    printf("Searching stuedent with grade of %d: \n", grade);
    BSTNode* stud = searchByScore(&tree, grade);
    if (stud) {
        printf("Student is existing: %s %d\n", stud->data.name, stud->data.score);
    } else {
        printf("student not found!\n");
    }
    printf("\nAverage score above 70: %.2f\n", averageAboveScore(tree.root, 70));

    tree.root = deleteScoreBelow(tree.root, 70);
    printf("\nInorder Traversal after deleting below 70:\n");
    inorderTraversal(tree.root);

    // freeBST(tree.root);
    return 0;
}

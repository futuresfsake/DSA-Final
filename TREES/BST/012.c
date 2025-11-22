#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ---------------- STRUCTS ----------------

// Represents a student enrolled in a course
typedef struct EnrolledStudent {
    int studentID;         // Unique key
    char name[50];
    char courseCode[10];
    int units;
} EnrolledStudent;

// Node of the BST storing enrolled students
typedef struct StudentNode {
    EnrolledStudent data;
    struct StudentNode *left;
    struct StudentNode *right;
} StudentNode;

// ---------------- FUNCTION PROTOTYPES ----------------

// BST operations
StudentNode* enroll_insert(StudentNode* root, EnrolledStudent s);
StudentNode* enroll_lookup(StudentNode* root, int studentID);
StudentNode* enroll_delete(StudentNode* root, int studentID);
void enroll_inorder_display(StudentNode* root);

// Helper functions
StudentNode* create_student_node(EnrolledStudent s);
StudentNode* enroll_find_min(StudentNode* root);
void free_enrollment_tree(StudentNode* root);

// ---------------- IMPLEMENTATION SPACES ----------------

StudentNode* enroll_insert(StudentNode* root, EnrolledStudent s) {

    
    StudentNode** trav = &(root);
    for(; (*trav) != NULL && (*trav)->data.studentID != s.studentID;) {
        trav = (*trav)->data.studentID < s.studentID ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
        StudentNode* new = malloc(sizeof(StudentNode));
        if (!new) return root;

        new->data = s;
        new->left = NULL;
        new->right = NULL;
        *trav = new;
    }
    printf("%s success!\n", s.name);
    return root;
}


StudentNode* enroll_lookup(StudentNode* root, int studentID) {

    StudentNode* trav = root;
    for(; trav != NULL && trav->data.studentID;) {
        if (trav->data.studentID == studentID) {
            return trav;
        }
        trav = trav->data.studentID < studentID ? trav->right : trav->left;
    }

    return NULL;
}

StudentNode* enroll_delete(StudentNode* root, int studentID) {

    StudentNode** trav = &(root);

    for(;*trav != NULL && (*trav)->data.studentID != studentID;) {
        trav = (*trav)->data.studentID < studentID ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) return NULL;

    StudentNode* toRemove = *trav;
    
    if (!(*trav)->left && !(*trav)->right) {
        free(toRemove);
        *trav = NULL;
    } else if (!(*trav)->right) {
        *trav = (*trav)->left;
        free(toRemove);
    }
    else if (!(*trav)->left) {
        *trav = (*trav)->right;
        free(toRemove);
    } else {
        StudentNode** succ = &(*trav)->right;
        while ((*succ)->left) {
            succ = &(*succ)->left;
        }

        (*trav)->data = (*succ)->data;
        *succ = enroll_delete(*succ, (*succ)->data.studentID);

    }


    return root;
}

void enroll_inorder_display(StudentNode* root) {
    
    if (root == NULL) return;
    enroll_inorder_display(root->left);
    printf("%d || %s || %s  \n", root->data.studentID, root->data.name, root->data.courseCode);
    enroll_inorder_display(root->right);
}

// ---------------- HELPER FUNCTIONS ----------------

StudentNode* create_student_node(EnrolledStudent s) {
    StudentNode* new_node = (StudentNode*) malloc(sizeof(StudentNode));
    new_node->data = s;
    new_node->left = new_node->right = NULL;
    return new_node;
}

StudentNode* enroll_find_min(StudentNode* root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

void free_enrollment_tree(StudentNode* root) {
    if (!root) return;
    free_enrollment_tree(root->left);
    free_enrollment_tree(root->right);
    free(root);
}

// ---------------- MAIN FOR TESTING ----------------

int main() {
    StudentNode* root = NULL;

    // Sample enrolled students
    EnrolledStudent s1 = {1001, "Alice", "CS101", 3};
    EnrolledStudent s2 = {1005, "Bob", "IT202", 4};
    EnrolledStudent s3 = {1003, "Charlie", "CS101", 3};
    EnrolledStudent s4 = {1002, "Diana", "ENG103", 2};

    // Insert students
    root = enroll_insert(root, s1);
    root = enroll_insert(root, s2);
    root = enroll_insert(root, s3);
    root = enroll_insert(root, s4);

    // Display all students
    printf("All enrolled students (inorder):\n");
    enroll_inorder_display(root);

    // Lookup student
    int lookupID = 1003;
    StudentNode* found = enroll_lookup(root, lookupID);
    if (found)
        printf("Found student ID %d: %s\n", lookupID, found->data.name);
    else
        printf("Student ID %d not found\n", lookupID);

    // Delete student
    root = enroll_delete(root, 1005);
    printf("After deleting student 1005:\n");
    enroll_inorder_display(root);

    free_enrollment_tree(root);
    return 0;
}

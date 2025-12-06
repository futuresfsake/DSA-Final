#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    int id;
    char name[50];
    float gpa;
    struct Student *left;
    struct Student *right;
} Student;

// BST operations
Student* insertStudent(Student *root, int id, const char *name, float gpa);
Student* searchStudent(Student *root, int id);
Student* deleteStudent(Student *root, int id);
Student* findMin(Student *root);
Student* findMax(Student *root);
void displayInOrder(Student *root);

// Additional operations
float computeAverageGPA(Student *root);
int countStudents(Student *root);
void displayAboveGPA(Student *root, float threshold);
float computeAverageHelper(Student* root, int *count);
int main() {
    Student *root = NULL;

    // Insert test data
    root = insertStudent(root, 102, "Alice", 3.1);
    root = insertStudent(root, 150, "Bob", 2.5);
    root = insertStudent(root, 90, "Charlie", 3.8);
    root = insertStudent(root, 120, "Diana", 3.4);
    root = insertStudent(root, 60, "Evan", 2.9);

    printf("=== In-order Display (Sorted by ID) ===\n");
    displayInOrder(root);

    printf("\nSearching for ID 120...\n");
    Student *s = searchStudent(root, 120);
    if (s) printf("Found: %s (GPA %.2f)\n", s->name, s->gpa);

    printf("\nDeleting ID 102...\n");
    root = deleteStudent(root, 102);
    displayInOrder(root);

   
    int count = countStudents(root);
    printf("\nTotal Students: %d\n", count);

    float avg = computeAverageGPA(root);
    printf("Average GPA: %.2f\n", avg);

    return 0;
}


Student* insertStudent(Student *root, int id, const char *name, float gpa) {

    Student** trav = &root;

    for(; *trav != NULL && (*trav)->id != id;) {
        trav =(*trav)->gpa < gpa ? &(*trav)->right : &(*trav)->left;
    }

    if (*trav == NULL) {
        Student* new = malloc(sizeof(Student));
        if (new == NULL) return NULL;

       
        strcpy(new->name, name);
        new->gpa = gpa;
        new->id = id;
        new->left = new->right = NULL;
        *trav = new;

        return root;
    }
}


Student* searchStudent(Student *root, int id) {
    

    if (root == NULL) return NULL;
    

    if (root->id == id) return root;
    


    Student* s = searchStudent(root->left, id); {
        if (s != NULL) return s;
    }
    Student *s1 = searchStudent(root->right, id); {
    if (s1 != NULL) return s1;
        }

        return NULL;

   

}


Student* deleteStudent(Student *root, int id) {

    if (root == NULL) return NULL;

    root->left = deleteStudent(root->left, id);
    root->right = deleteStudent (root->right, id);


    if (root->id == id) {

        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
            return root;
        }


        else if (root->left == NULL) {
            Student* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Student* temp = root->left;
            free(root);
            return temp;
        } else {

            Student* succ = root->right;
            while (succ->left) {
                succ = succ->left;
            }

            root->id = succ->id;
            root->gpa = succ->gpa;
            strcpy(root->name, succ->name);

            root->right = deleteStudent(root->right,succ->id);
        }
    }


    return root;
}
Student* findMin(Student *root) {

    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}
Student* findMax(Student *root) {
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

void displayInOrder(Student *root) {
    if (root == NULL) return;  // base case

    // 1. Visit left subtree
    displayInOrder(root->left);

    // 2. Process the current node
    printf("ID: %d  | Name: %s  | GPA: %.2f\n",
           root->id, root->name, root->gpa);

    // 3. Visit right subtree
    displayInOrder(root->right);
}


float computeAverageHelper(Student* root, int *count) {
    if (root == NULL) return 0;

    float leftSum = computeAverageHelper(root->left, count);
     float rightSum = computeAverageHelper(root->right, count);
     (*count)++;

     return leftSum+rightSum+root->gpa;

}

float computeAverageGPA(Student *root) {

   int count = 0;
   float sum = computeAverageHelper(root, &count);
   if (count == 0) return 0;
   return sum/count;
    
}
int countStudents(Student *root) {
    if (root == NULL) return 0;

    int c = countStudents(root->left);
    int c2 = countStudents(root->right);
    return c+c2+1;
}
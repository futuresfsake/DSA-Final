#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 50

typedef struct node {
    char name[NAME_LEN];
    int salary;
    struct node *left;
    struct node *right;
} EmployeeNode;

// ==================== FUNCTION DECLARATIONS ====================

// Insert a new employee into the BST
EmployeeNode* insertEmployee(EmployeeNode *root, char *name, int salary);

// Search for an employee by name
EmployeeNode* searchEmployee(EmployeeNode *root, char *name);

// Delete an employee by name
EmployeeNode* deleteEmployee(EmployeeNode *root, char *name);

// Find employee with maximum salary
EmployeeNode* findMaxSalary(EmployeeNode *root);

// Count employees with salary in a given range
int countSalaryRange(EmployeeNode *root, int low, int high);

// Display the BST in-order (salary ascending)
void displayEmployees(EmployeeNode *root);

// Free all nodes
void freeBST(EmployeeNode *root);


int main() {
    EmployeeNode *root = NULL;

    root = insertEmployee(root, "Alice", 50000);
    root = insertEmployee(root, "Bob", 70000);
    root = insertEmployee(root, "Charlie", 60000);
    root = insertEmployee(root, "Diana", 55000);
    root = insertEmployee(root, "Eve", 80000);

    printf("Employees in salary order:\n");
    displayEmployees(root);

    // Example: search for an employee named "Diana"
EmployeeNode *found = searchEmployee(root, "Diana");

if (found != NULL) {
    printf("\nEmployee found: %s | Salary: %d\n", found->name, found->salary);
} else {
    printf("\nEmployee Diana not found.\n");
}

    printf("\nEmployee with max salary: %s\n", findMaxSalary(root)->name);

    printf("Number of employees with salary 55000-75000: %d\n", 
            countSalaryRange(root, 55000, 75000));

    root = deleteEmployee(root, "Charlie");

    printf("\nAfter deleting Charlie:\n");
    displayEmployees(root);

    freeBST(root);
    return 0;
}


EmployeeNode* insertEmployee(EmployeeNode *root, char *name, int salary) {
        if (root == NULL) {
            EmployeeNode* new = malloc(sizeof(EmployeeNode));
            if (new == NULL) return NULL;

            new->salary = salary;
            strcpy(new->name, name);
            new->left = new->right = NULL;

            root = new;
        }



        if (root->salary == salary) return root;

        if (root->salary < salary) {
            root->right = insertEmployee(root->right, name, salary);
        } else if (root->salary> salary) {
            root->left = insertEmployee(root->left, name, salary);
        }

        
}

// Search for an employee by name
EmployeeNode* searchEmployee(EmployeeNode *root, char *name) {


    if (root == NULL) return NULL;

    if (strcmp(root->name, name) == 0) {
        return root;
    }


    EmployeeNode* s = searchEmployee(root->left, name);
    if (s != NULL) return s;

    EmployeeNode* s2 = searchEmployee(root->right,name);
    if (s2 != NULL) return s2;

    return NULL;
}

// Delete an employee by name
EmployeeNode* deleteEmployee(EmployeeNode *root, char *name) {

    if (root == NULL) return root;

    root->left = deleteEmployee(root->left, name);
    root->right = deleteEmployee(root->right, name);

    if (strcmp(root->name, name) == 0) {
        if (root->left == NULL && root->right) {
            free(root);
            root = NULL;
            return root;
        } else if (root->left == NULL) {
            EmployeeNode* temp = root->right;
            free(root);
            return temp;
        }else if (root->right == NULL) {
            EmployeeNode* temp = root->left;
            free(root);
            return temp;
        } else {
            EmployeeNode* succ = root->right;
            while (succ->left) {
                succ = succ->left;
            } 

            strcpy(root->name, succ->name);
            root->salary = succ->salary;

            root->right = deleteEmployee(root->right, succ->name);
        }
    }
    return root;
}

// Find employee with maximum salary
EmployeeNode* findMaxSalary(EmployeeNode *root) {
    if (root == NULL) return NULL;

    while (root->right) {
        root = root->right;
    }
    return root;
}
int count = 0;

// Count employees with salary in a given range
int countSalaryRange(EmployeeNode *root, int low, int high) {
    if (root == NULL) return 0;

    int count = 0;
    if (root->salary <= high && root->salary >= low) {
        count =  1;
    }
  
     count += countSalaryRange(root->left, low, high);
    
    count+= countSalaryRange(root->right, low, high );

    return count;

}
// Display the BST in-order (salary ascending)
void displayEmployees(EmployeeNode *root) {
    if (root == NULL) return;

    // Traverse left subtree first
    displayEmployees(root->left);

    // Print current node
    printf("Name: %s | Salary: %d\n", root->name, root->salary);

    // Traverse right subtree
    displayEmployees(root->right);
}

// Free all nodes
void freeBST(EmployeeNode *root) {
    if (root == NULL) return;

    freeBST(root->left);
    freeBST(root->right);
    free(root);
}

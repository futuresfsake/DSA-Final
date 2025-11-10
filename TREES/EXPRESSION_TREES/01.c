#include <stdio.h>
#include <stdlib.h>

struct Node {
    char data;                // operator or operand
    struct Node* left;
    struct Node* right;
};

// Create new node
struct Node* newNode(char data) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Postorder evaluation (for simple operands)
int evaluate(struct Node* root) {
    if (root == NULL) return 0;

    // If leaf node → it's a number
    if (root->left == NULL && root->right == NULL)
        return root->data - '0';  // convert char to int

    int leftVal = evaluate(root->left);
    int rightVal = evaluate(root->right);

    switch (root->data) {
        case '+': return leftVal + rightVal;
        case '-': return leftVal - rightVal;
        case '*': return leftVal * rightVal;
        case '/': return leftVal / rightVal;
    }
    return 0;
}

int main() {
    // (3 + 5) * (2 - 1)
    struct Node* root = newNode('*');
    root->left = newNode('+');
    root->right = newNode('-');

    root->left->left = newNode('3');
    root->left->right = newNode('5');
    root->right->left = newNode('2');
    root->right->right = newNode('1');

    printf("Result: %d\n", evaluate(root));  // Output: 8
    return 0;
}

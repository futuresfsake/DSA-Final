#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ================= BST NODE =================
typedef struct node {
    int data;               // Value of the node
    struct node* left;      // Pointer to left child
    struct node* right;     // Pointer to right child
} Node;

// ================= STACK FOR DFS =================
typedef struct stack {
    Node* arr[100];         // Array to hold node pointers
    int top;                // Index of top element
} Stack;

// ================= STACK FUNCTIONS =================
// Initialize stack
void initStack(Stack* s) {
    s->top = -1;            // Empty stack
}

// Check if stack is empty
bool isEmpty(Stack* s) {
    return s->top == -1;
}

// Push node onto stack
void push(Stack* s, Node* node) {
    if (s->top < 99) {      // Prevent overflow
        s->arr[++(s->top)] = node;   // Increment top and store node
    }
}

// Pop node from stack
Node* pop(Stack* s) {
    if (isEmpty(s)) return NULL;     // Nothing to pop
    return s->arr[(s->top)--];       // Return top element and decrement top
}

// ================= BST FUNCTIONS =================
// Create a new node
Node* createNode(int data) {
    Node* n = malloc(sizeof(Node));  // Allocate memory
    n->data = data;                  // Store data
    n->left = n->right = NULL;       // Initialize children to NULL
    return n;                        // Return pointer
}

// Iterative BST insertion
void insert(Node** root, int data) {
     Node* newNode = createNode(data);
    if (!*root) { *root = newNode; return; }

    Stack s;
    initStack(&s);
    push(&s, *root);

    while (!isEmpty(&s)) {
        Node* curr = pop(&s);

        if (data < curr->data) {
            if (!curr->left) {
                curr->left = newNode;
                return;
            } else {
                push(&s, curr->left);
            }
        } else {
            if (!curr->right) {
                curr->right = newNode;
                return;
            } else {
                push(&s, curr->right);
            }
        }
    }
}

// Iterative inorder traversal (left-node-right)
void inorder(Node* root) {

    Stack s;
    s.top = -1;

    Node* trav = root;

    while (trav || s.top != -1) {
        while (trav) {
            push(&s, trav);
            trav = trav->left;
        }

        Node* trav = pop(&s);
        printf("%d ", trav->data);
        trav = trav->right;
    }
}

// Iterative preorder traversal (node-left-right)
void preorder(Node* root) {
    
    if (root == NULL) return;

    Stack s;
    s.top = -1;

    push(&s, root);
    while (s.top != -1) {
        Node* trav = pop(&s);
        printf("%d ", trav->data);


        if (trav->right) push(&s, trav->right);
        if (trav->left) push (&s, trav->left);
    }
}

// Iterative postorder traversal using two stacks (left-right-node)
void postorder(Node* root) {
   
   if (root == NULL) return;

   Stack s1, s2;
   s1.top = -1;
   s2.top = -1;

   push(&s1, root);

   while (s1.top != -1) {
        Node* trav = pop(&s1);
        push(&s2, trav);

        if (trav->left) push(&s1, trav->left);
        if (trav->right) push(&s1, trav->right);
        
   }

   while (s2.top != -1) {
    Node* trav= pop(&s2);
    printf("%d ", trav->data);
   }
}

// Breadth-first traversal (level-order) using queue array
void bfs(Node* root) {
   

    if (root == NULL) return;
    Node* queue[100];
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        Node* curr = queue[front++];
        printf("%d ", curr->data);

        if (curr->left) queue[rear++] = curr->left;
        if (curr->right) queue[rear++] = curr->right;
    }
}

// Iterative search in BST
bool search(Node* root, int data) {
    Node* curr = root;
    while (curr) {                       // Traverse until NULL
        if (curr->data == data) return true;  // Found
        curr = (data < curr->data) ? curr->left : curr->right; // Go left/right
    }
    return false;                        // Not found
}

// Find minimum node
Node* findMin(Node* root) {
    if (!root) return NULL;
    while (root->left) root = root->left;   // Go to leftmost node
    return root;
}

// Iterative deletion of node
Node* deleteNode(Node* root, int data) {
     if (!root) return NULL;

    Stack s;
    initStack(&s);
    push(&s, root);
    Node* parent = NULL;
    Node* curr = root;
    bool isLeftChild = false;

    // Find the node to delete
    while (curr && curr->data != data) {
        parent = curr;
        if (data < curr->data) { curr = curr->left; isLeftChild = true; }
        else { curr = curr->right; isLeftChild = false; }
    }

    if (!curr) return root; // Not found

    // Case 1: No children
    if (!curr->left && !curr->right) {
        if (!parent) { free(curr); return NULL; } // root node
        if (isLeftChild) parent->left = NULL;
        else parent->right = NULL;
        free(curr);
    }
    // Case 2: One child
    else if (!curr->left || !curr->right) {
        Node* child = curr->left ? curr->left : curr->right;
        if (!parent) { free(curr); return child; } // root node
        if (isLeftChild) parent->left = child;
        else parent->right = child;
        free(curr);
    }
    // Case 3: Two children
    else {
        Node* succParent = curr;
        Node* succ = curr->right;

        while (succ->left) {
            succParent = succ;
            succ = succ->left;
        }

        curr->data = succ->data; // Replace value
        if (succParent->left == succ) succParent->left = succ->right;
        else succParent->right = succ->right;
        free(succ);
    }

    return root;
}

// ================= MAIN FUNCTION =================
int main() {
    Node* root = NULL;                // Initialize empty BST

    // Insert nodes
    insert(&root, 10);
    insert(&root, 5);
    insert(&root, 15);
    insert(&root, 3);
    insert(&root, 7);
    insert(&root, 12);
    insert(&root, 18);

    // Traversals
    printf("Inorder: ");
    inorder(root);
    printf("\n");

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    printf("Postorder: ");
    postorder(root);
    printf("\n");

    printf("BFS: ");
    bfs(root);
    printf("\n");

    // Search
    printf("Search 7: %s\n", search(root, 7) ? "Found" : "Not Found");
    printf("Search 20: %s\n", search(root, 20) ? "Found" : "Not Found");

    // Delete node
    root = deleteNode(root, 15);
    printf("Inorder after deleting 15: ");
    inorder(root);
    printf("\n");

    return 0;
}

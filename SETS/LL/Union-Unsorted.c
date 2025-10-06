// * must check for duplciated manually with ismember
// * list is unsorted
// * time complexity is (O(n*m)), each insertion requires a traversal of C to check for duplicates




#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to create a new node
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Check if a value exists in the list
bool IsMember(Node* head, int value) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == value) return true;
        temp = temp->next;
    }
    return false;
}

// Union of two arbitrary linked lists
Node* UnionUnsorted(Node* A, Node* B) {
    Node* C = NULL;

    // Add elements from A
    Node* temp = A;
    while (temp != NULL) {
        if (!IsMember(C, temp->data)) {
            Node* node = newNode(temp->data);
            node->next = C; // Insert at head
            C = node;
        }
        temp = temp->next;
    }

    // Add elements from B
    temp = B;
    while (temp != NULL) {
        if (!IsMember(C, temp->data)) {
            Node* node = newNode(temp->data);
            node->next = C;
            C = node;
        }
        temp = temp->next;
    }

    return C;
}



int main() {
    // Create first linked list: 1 -> 2 -> 3
    Node* A = newNode(1);
    A->next = newNode(2);
    A->next->next = newNode(3);

    // Create second linked list: 3 -> 4 -> 5
    Node* B = newNode(3);
    B->next = newNode(4);
    B->next->next = newNode(5);

    printf("Set A: ");
    Node* temp = A;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");

    printf("Set B: ");
    temp = B;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");

    // Perform union
    Node* C = UnionUnsorted(A, B);

    // Print union result
    printf("Union (A ∪ B): ");
    temp = C;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");

    return 0;
}

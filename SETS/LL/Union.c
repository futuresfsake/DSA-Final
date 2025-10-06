// * assumes that the nodes are already sorted


#include <stdio.h>
#include <stdlib.h>

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

// Union of two sorted linked lists
Node* UnionSorted(Node* A, Node* B) {
    Node* C = NULL;     // Head of the new union list
    Node** lastPtr = &C; // Pointer to the last node pointer (to append efficiently)

    while (A != NULL && B != NULL) {
        if (A->data < B->data) {
            *lastPtr = newNode(A->data);
            A = A->next;
        } else if (A->data > B->data) {
            *lastPtr = newNode(B->data);
            B = B->next;
        } else { // Equal, take one and move both
            *lastPtr = newNode(A->data);
            A = A->next;
            B = B->next;
        }
        lastPtr = &((*lastPtr)->next); // Move pointer to next
    }

    // Append remaining elements
    while (A != NULL) {
        *lastPtr = newNode(A->data);
        lastPtr = &((*lastPtr)->next);
        A = A->next;
    }
    while (B != NULL) {
        *lastPtr = newNode(B->data);
        lastPtr = &((*lastPtr)->next);
        B = B->next;
    }

    return C;
}
int main() {
    // Create first sorted linked list: 1 -> 3 -> 5
    Node* A = newNode(1);
    A->next = newNode(3);
    A->next->next = newNode(5);

    // Create second sorted linked list: 2 -> 3 -> 6
    Node* B = newNode(2);
    B->next = newNode(3);
    B->next->next = newNode(6);

    // Perform union
    Node* C = UnionSorted(A, B);

    // Display the union list
    printf("Union of the two lists: ");
    for (Node* temp = C; temp != NULL; temp = temp->next) {
        printf("%d ", temp->data);
    }
    printf("\n");

    return 0;
}

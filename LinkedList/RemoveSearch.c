#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node, *NodePtr;

void printList(NodePtr head);
void removeNode(NodePtr* head, int value);

int main() {
    NodePtr head = malloc(sizeof(Node));
    head->data = 10;

    head->next = malloc(sizeof(Node));
    head->next->data = 20;

    head->next->next = malloc(sizeof(Node));
    head->next->next->data = 30;
    head->next->next->next = NULL;

    printf("Initial list:\n");
    printList(head);

   
    printf("\nRemoving 20...\n");
    removeNode(&head, 20);
    printList(head);

    printf("\nRemoving 10 (head)...\n");
    removeNode(&head, 10);
    printList(head);

    printf("\nRemoving 99 (not in list)...\n");
    removeNode(&head, 99);
    printList(head);

    // 🧹 Free remaining nodes
    while (head != NULL) {
        NodePtr temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}


void printList(NodePtr head) {
    printf("List: ");
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void removeNode(NodePtr* head, int value) {

    NodePtr* trav;
    for(trav = head; *trav != NULL; trav = &(*trav)->next) {
        if ((*trav)->data == value) {
            NodePtr Toremove = *trav;
            *trav = (*trav)->next;
            printf("%d deleting...", Toremove->data);
            free(Toremove);
            return;
        }
    }
    printf("%d is not found.\n", value);
    
   
}

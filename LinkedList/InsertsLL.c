#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node {
    int data;
    struct node* next;
} NodeType, *NodePtr, *List;

void insertFront(List *list, int data) {

    NodePtr new = malloc(sizeof(NodeType));
    if (!new) {
        printf("Dynamic Memory Allocation failed.\n");
        return;
    }

    new->data = data;
    new->next = *list;
    *list = new;


}

void displayList(List list) {

    List temp = list;
    printf("Data: {");
    while (temp != NULL) {
        printf(" %d", temp->data);
        if (temp->next != NULL) {
            printf(",");
        }
        temp = temp->next;
        
        }
        printf(" }");
    }




int main() {
    List list = NULL;

    insertFront(&list, 2);
    
    insertFront(&list, 3);
    
    
    insertFront(&list, 5);
    
    
    insertFront(&list, 6);
    
    insertFront(&list, 10);
    
    displayList(list);
    return 0;


}
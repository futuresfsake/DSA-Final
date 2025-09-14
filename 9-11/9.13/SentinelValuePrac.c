// * find students who satisfies both conditions score >= minScore
// * strcmp(name, targetName) == 0


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// ===== Structure for Stack Item =====
typedef struct {
    int id;
    char name[30];
    float score;
} Item;

// ===== ArrayList Stack =====
typedef struct {
    Item *arr;
    int top;
    int max;
} ArrayStack;

void initArrayStack(ArrayStack *s, int max) {
    s->arr = (Item*)malloc(sizeof(Item) * max);
    s->top = -1;
    s->max = max;
}

bool isEmptyArray(ArrayStack *s) {
    return s->top == -1;
}

bool isFullArray(ArrayStack *s) {
    return s->top == s->max - 1;
}

void pushArray(ArrayStack *s, Item it) {
    if (!isFullArray(s)) {
        s->arr[++s->top] = it;
    }
}

Item popArray(ArrayStack *s) {
    if (!isEmptyArray(s)) {
        return s->arr[s->top--];
    }
    // Sentinel return
    Item sentinel = {-1, "N/A", -1};
    return sentinel;
}

// ===== LinkedList Stack =====
typedef struct node {
    Item data;
    struct node *next;
} Node;

typedef struct {
    Node *top;
} LinkedStack;

void initLinkedStack(LinkedStack *s) {
    s->top = NULL;
}

bool isEmptyLinked(LinkedStack *s) {
    return s->top == NULL;
}

void pushLinked(LinkedStack *s, Item it) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = it;
    newNode->next = s->top;
    s->top = newNode;
}

Item popLinked(LinkedStack *s) {
    if (!isEmptyLinked(s)) {
        Node *temp = s->top;
        Item it = temp->data;
        s->top = temp->next;
        free(temp);
        return it;
    }
    // Sentinel return
    Item sentinel = {-1, "N/A", -1};
    return sentinel;
}

// ===== Special Operations (Empty for You to Implement) =====
Item findSpecialArray(ArrayStack *s, float minScore, const char *targetName) {
    // TODO: implement this special search with sentinel value
    Item sentinel = {-1, "N/A", -1};


    ArrayStack temp;
    initArrayStack(&temp, s->max);
   

    while (!isEmptyArray(s)) {
        Item student = popArray(s);
        if ( strcmp(student.name, targetName) == 0 && student.score >= minScore) {
            if (student.score>=sentinel.score) { 
          
            sentinel = student;
            }
            
        }
        pushArray(&temp, student);
         

    }

    while (!isEmptyArray(&temp)){
        pushArray(s, popArray(&temp));
    }
    


    return sentinel;
}

// Item findSpecialLinked(LinkedStack *s, float minScore, const char *targetName) {
//     // TODO: implement this special search with sentinel value
//     Item sentinel = {-1, "N/A", -1};
//     return sentinel;
// }

// ===== Main for Testing =====
int main() {
    ArrayStack arrS;
    initArrayStack(&arrS, 5);

    LinkedStack linkS;
    initLinkedStack(&linkS);

    Item a = {1, "Alice", 88};
    Item b = {2, "Bob", 75};
    Item c = {3, "Alice", 95};

    pushArray(&arrS, a);
    pushArray(&arrS, b);
    pushArray(&arrS, c);

    pushLinked(&linkS, a);
    pushLinked(&linkS, b);
    pushLinked(&linkS, c);

    // // Testing pop
    // Item poppedA = popArray(&arrS);
    // printf("Popped from ArrayStack: %s %.2f\n", poppedA.name, poppedA.score);

    // Item poppedL = popLinked(&linkS);
    // printf("Popped from LinkedStack: %s %.2f\n", poppedL.name, poppedL.score);

 
// Special function: find student with score >= 90 and name "Alice"
Item result1 = findSpecialArray(&arrS, 90, "Alice");

printf("\nResult of findSpecialArray (score >= 90 & name == Alice):\n");
if (result1.id != -1) {
    printf("ID: %d, Name: %s, Score: %.2f\n", result1.id, result1.name, result1.score);
} else {
    printf("No matching student found.\n");
}

    return 0;
}

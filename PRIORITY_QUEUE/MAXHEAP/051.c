#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NAME_LEN 80

// ===============================
// STRUCT DEFINITIONS
// ===============================
typedef struct Species {
    char *name;                 // Dynamic string (alien species name)
    int dangerRating;           // Not used for BST ordering

    struct Species *left;
    struct Species *right;
} SpeciesNode;


// ===============================
// STACK FOR DFS (You fill logic inside push/pop)
// ===============================
typedef struct {
    SpeciesNode* stack[100];
    int top;
} Stack;

void push(Stack* s, SpeciesNode* node) {
    
    s->stack[++s->top] = node;
}

SpeciesNode* pop(Stack* s) {
    

    return s->stack[s->top--];
}


// ===============================
// QUEUE FOR BFS
// ===============================
typedef struct {
    SpeciesNode* arr[100];
    int front;
    int rear;
} Queue;

void enqueue(Queue* q, SpeciesNode* node) {

    q->arr[q->rear++] = node;

    
}

SpeciesNode* dequeue(Queue* q) {
    
    return q->arr[q->front++];
}


void bfs(SpeciesNode *root) {


    SpeciesNode* queue[100];
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        SpeciesNode* trav = queue[front++];
    printf("[Name: %s | Power: %d]\n", trav->name, trav->dangerRating);

    if (trav->left) queue[rear++] = trav->left;
    if (trav->right) queue[rear++] = trav->right;
    }
}


// ===============================
// FUNCTION PROTOTYPES
// ===============================
SpeciesNode* createNode(char *name, int danger) {

    SpeciesNode* new = malloc(sizeof(SpeciesNode));
    new->name = malloc(strlen(name)+1);
    new->dangerRating = danger;
    strcpy(new->name, name);
    new->left = new->right = NULL;

    return new;
}
SpeciesNode* insertSpecies(SpeciesNode *root, char *name, int danger) {
    SpeciesNode** trav = &root;

    for(; *trav != NULL && strcmp((*trav)->name, name) !=0;) {
        trav = (strcmp((*trav)->name, name) < 0) ?  &(*trav)->right : &(*trav)->left;
    }

    if (*trav== NULL) {
        *trav = createNode(name, danger);
    }

    return root;
}
SpeciesNode* searchSpecies(SpeciesNode *root, char *name) {
    SpeciesNode* trav = root;

    while (trav) {
        if (strcmp(trav->name, name) == 0 ) {
            return trav;
        }

        trav = (strcmp(trav->name, name) < 0) ? trav->right : trav->left;
    }

    return NULL;
}
SpeciesNode* deleteSpecies(SpeciesNode *root, char *name) {

    SpeciesNode** trav = &root;

    for(; *trav != NULL && strcmp((*trav)->name, name) !=0;) {
        trav = strcmp((*trav)->name, name) <0? &(*trav)->right : &(*trav)->left;
    }

    if (*trav== NULL) {
        return root;
    }



    SpeciesNode* temp = *trav;

    if ((*trav)->left == NULL && (*trav)->right== NULL) {
        free((*trav)->name);
        free(*trav);

        *trav = NULL;
    } else if ((*trav)->left == NULL) {
        *trav = (*trav)->right;
        free(temp->name);
        free(temp);
    }else if ((*trav)->right == NULL) {
        *trav = (*trav)->left;
        free(temp->name);
        free(temp);
    } else {
        SpeciesNode** succ = &(*trav)->right;

        while ((*succ)->left) {
            succ = &(*succ)->left;
        }

        free(temp->name);
        (temp)->name = malloc(strlen((*succ)->name)+1);
        strcpy((temp)->name, (*succ)->name);
        (temp)->dangerRating = (*succ)->dangerRating;


        SpeciesNode* target = *succ;
        *succ = (*succ)->right;
        free(target->name);
        free(target);
    }
    return root;
}

void inorder(SpeciesNode *root) {

    Stack s;
    s.top = -1;
    SpeciesNode* trav = root;

    while (trav || s.top != -1) {
        while (trav) {
            push(&s, trav);
            trav = trav->left;
        }

        trav = pop(&s);
    printf("[Name: %s | Power: %d]\n", trav->name, trav->dangerRating);
        trav = trav->right;
    }
}


void preorder(SpeciesNode *root) {
    Stack s;
    s.top = -1;
    push(&s, root);

    while (s.top != -1) {
        SpeciesNode* trav = pop(&s);
    printf("[Name: %s | Power: %d]\n", trav->name, trav->dangerRating);

 if (trav->right) push(&s, trav->right);
 if (trav->left) push(&s, trav->left);

    }
}

void postorder(SpeciesNode *root) {
    Stack s1,s2;
    s1.top = -1;
    s2.top = -1;

    push(&s1, root);
    while (s1.top != -1) {
        SpeciesNode* trav = pop(&s1);
        push(&s2, trav);
         if (trav->left) push(&s1, trav->left);
        if (trav->right) push(&s1, trav->right);

    }

    while (s2.top != -1) {
        SpeciesNode* trav = pop(&s2);
    printf("[Name: %s | Power: %d]\n", trav->name, trav->dangerRating);


    }
}

SpeciesNode* findMin(SpeciesNode *root) {
    while (root->right) {
        root = root->right;
    }

    return root;
}
SpeciesNode* findMax(SpeciesNode *root) {
    while (root->left) {
        root = root->left;
    }

    return root;
}
void freeTree(SpeciesNode *root) {
    if (root == NULL) return;

    freeTree(root->left);
    freeTree(root->right);
    free(root->name);
    free(root);
}


// ===============================
// MAIN
// ===============================
int main() {
    SpeciesNode *registry = NULL;

    registry = insertSpecies(registry, "Zenthar", 9);
    registry = insertSpecies(registry, "Arklon", 4);
    registry = insertSpecies(registry, "Myridian", 7);
    registry = insertSpecies(registry, "Velstrix", 6);
    registry = insertSpecies(registry, "Kraelor", 3);

    printf("\n===== INORDER (Sorted Alphabetically) =====\n");
    inorder(registry);

    printf("\n===== SEARCH: 'Myridian' =====\n");
    SpeciesNode *s = searchSpecies(registry, "Myridian");
    if (s)
        printf("Found: %s (Danger:%d)\n", s->name, s->dangerRating);
    else
        printf("NOT FOUND.\n");

    printf("\n===== DELETE: 'Arklon' =====\n");
    registry = deleteSpecies(registry, "Arklon");

    printf("\n===== INORDER AFTER DELETE =====\n");
    inorder(registry);

    printf("\n===== BFS TRAVERSAL =====\n");
    bfs(registry);

    freeTree(registry);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

//================ NODE STRUCT =================
typedef struct Node {
    int data;                // frequency
    struct Node* left;       // left child
    struct Node* right;      // right child
} Node;

//================ HEAP STRUCT ==================
typedef struct {
    Node* elem[MAX];
    int lastndx;
} Heap;


//================ FUNCTION DECLARATIONS =================
Node* newNode(int freq);
void addElem(Heap* H, Node* elem);
Node* deleteElem(Heap* H);
void preorder(Node* root, char code[], int depth);


//================ CREATE NEW NODE =================
Node* newNode(int freq) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = freq;
    n->left = n->right = NULL;
    return n;
}


//================ MIN-HEAP INSERT =================
void addElem(Heap* H, Node* elem) {
    int idx, pr;

    if (H->lastndx == MAX - 1) return;

    H->lastndx++;
    idx = H->lastndx;
    pr = (idx - 1) / 2;

    // bubble up
    while (idx > 0 && H->elem[pr]->data > elem->data) {
        H->elem[idx] = H->elem[pr];
        idx = pr;
        pr = (idx - 1) / 2;
    }

    H->elem[idx] = elem;
}


//================ MIN-HEAP DELETE (REMOVE SMALLEST) =================
Node* deleteElem(Heap* H) {
    if (H->lastndx == -1) return NULL;

    Node* ret = H->elem[0];
    H->elem[0] = H->elem[H->lastndx];
    H->lastndx--;

    int pr = 0;
    int child = 1;

    // bubble down
    while (child <= H->lastndx) {
        if (child + 1 <= H->lastndx &&
            H->elem[child + 1]->data < H->elem[child]->data)
            child++;

        if (H->elem[pr]->data > H->elem[child]->data) {
            Node* temp = H->elem[pr];
            H->elem[pr] = H->elem[child];
            H->elem[child] = temp;

            pr = child;
            child = 2 * pr + 1;
        } else break;
    }

    return ret;
}


//================ PREORDER PRINTING OF HUFFMAN CODES =================
void preorder(Node* root, char code[], int depth) {
    if (!root) return;

    // leaf node → print the code
    if (!root->left && !root->right) {
        code[depth] = '\0';
        printf("%s ", code);
        return;
    }

    code[depth] = '0';
    preorder(root->left, code, depth + 1);

    code[depth] = '1';
    preorder(root->right, code, depth + 1);
}


//================ BUILD HUFFMAN TREE =================
Node* buildHuffman(int freq[], int n) {
    Heap H;
    H.lastndx = -1;

    // insert leaves
    //* initially the heap stores only the leaves

    for (int i = 0; i < n; i++) {
        addElem(&H, newNode(freq[i])); //! store the arrays into the H->elem[].data
    }

    // build tree
    while (H.lastndx >= 1) { //* while index is still not 1
        Node* left = deleteElem(&H); //! delete the left node
        Node* right = deleteElem(&H); //* delete the next node which is right

        Node* merged = newNode(left->data + right->data); //* make a new node that will add the 2 data
        merged->left = left; //* go the next left data
        merged->right = right; //* go to the next right data

        addElem(&H, merged); //* add it in heap
    }

    return deleteElem(&H); //* return the root, at the end of building the huffman tree, you heap has only one node left
    //* containst he sum of all frequencies, and its children are previously merged nodes
}


//================ MAIN PROGRAM =================
int main() {
    int freq[] = {5, 9, 12, 13, 16, 45};
    int n = 6;

    Node* root = buildHuffman(freq, n);

    char code[50];
    preorder(root, code, 0);

    return 0;
}

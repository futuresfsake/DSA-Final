#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 50
#define MAXC 200
#define NONE -1

typedef struct {
    int empID;
    char name[50];
    char jobTitle[30];
    char department[20];
    double salary;
    int level;
} Employee;

typedef struct {
    int child;
    int next;
} ChildNode;

typedef struct {
    Employee employees[MAXN];
    int head[MAXN];
    int parent[MAXN];
    int used;
} OrgTree;

ChildNode child[MAXC];
int avail = 0;

void initializeOrgTree(OrgTree* org) {
    org->used = 0;
    avail = 0;
    for (int i = 0; i < MAXN; i++) {
        org->head[i] = NONE;
        org->parent[i] = NONE;
    }
}

void addChild(OrgTree* org, int parentIndex, int childIndex) {
    if (avail < MAXC) {
        child[avail].child = childIndex;
        child[avail].next = org->head[parentIndex];
        org->head[parentIndex] = avail;
        avail++;
    }
}

int addEmployee(OrgTree* org, int managerIndex, Employee emp) {
    if (org->used >= MAXN) return NONE;
    int newIdx = org->used++;
    org->employees[newIdx] = emp;
    org->parent[newIdx] = managerIndex;
    if (managerIndex != NONE) {
        addChild(org, managerIndex, newIdx);
    }
    return newIdx;
}

int findEmployee(OrgTree* org, int empID) {
    for (int i = 0; i < org->used; i++) {
        if (org->employees[i].empID == empID) return i;
    }
    return NONE;
}

void printOrg(OrgTree* org, int index, int indent) {
    if (index == NONE) return;
    for (int i = 0; i < indent; i++) printf("  ");
    printf("- %s (%s)\n", org->employees[index].name, org->employees[index].jobTitle);
    
    int curr = org->head[index];
    while (curr != NONE) {
        printOrg(org, child[curr].child, indent + 1);
        curr = child[curr].next;
    }
}

int leftmostEmployee(OrgTree* org) {
    if (org->used == 0) return NONE;
    int minIdx = 0;
    for (int i = 1; i < org->used; i++) {
        if (org->employees[i].empID < org->employees[minIdx].empID) minIdx = i;
    }
    return minIdx;
}

int rightmostEmployee(OrgTree* org) {
    if (org->used == 0) return NONE;
    int maxIdx = 0;
    for (int i = 1; i < org->used; i++) {
        if (org->employees[i].empID > org->employees[maxIdx].empID) maxIdx = i;
    }
    return maxIdx;
}

void BFS(OrgTree* org, int rootIndex) {
    if (rootIndex == NONE) return;
    int queue[MAXN];
    int front = 0, rear = 0;
    queue[rear++] = rootIndex;
    while (front < rear) {
        int currIdx = queue[front++];
        printf("%s ", org->employees[currIdx].name);
        int c = org->head[currIdx];
        while (c != NONE) {
            queue[rear++] = child[c].child;
            c = child[c].next;
        }
    }
    printf("\n");
}

bool removeEmployee(OrgTree* org, int empID) {
    return false; 
}

void freeOrgTree(OrgTree* org) {
    initializeOrgTree(org);
}

int main() {
    OrgTree org;
    initializeOrgTree(&org);

    Employee ceo  = {1000, "Alice Smith", "CEO", "Exec", 250000, 0};
    Employee mgr1 = {1001, "Bob Johnson", "CTO", "Tech", 180000, 1};
    Employee mgr2 = {1002, "Carol White", "CFO", "Finance", 175000, 1};
    Employee emp1 = {1003, "David Brown", "Engineer", "Tech", 120000, 2};
    Employee emp2 = {1004, "Eva Green", "Accountant", "Finance", 90000, 2};

    int ceoIdx  = addEmployee(&org, NONE, ceo);
    int m1Idx   = addEmployee(&org, ceoIdx, mgr1);
    int m2Idx   = addEmployee(&org, ceoIdx, mgr2);
    int e1Idx   = addEmployee(&org, m1Idx, emp1);
    int e2Idx   = addEmployee(&org, m2Idx, emp2);

    printf("\n=== ORGANIZATION TREE ===\n");
    printOrg(&org, ceoIdx, 0);

    printf("\nBFS Traversal:\n");
    BFS(&org, ceoIdx);

    printf("\nLeftmost EmpID: %d\n", org.employees[leftmostEmployee(&org)].empID);
    printf("Rightmost EmpID: %d\n", org.employees[rightmostEmployee(&org)].empID);

    return 0;
}
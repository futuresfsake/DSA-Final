#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ===== Grade Struct =====
typedef struct {
    int math;
    int science;
    int english;
} Grade;

// ===== Student Struct =====
typedef struct {
    int id;
    char name[50];
    Grade grade;   // nested struct
} Student;

// ===== Node for Queue =====
typedef struct Node {
    Student data;
    struct Node *next;
} Node;

// ===== Queue Struct =====
typedef struct {
    Node *front;
    Node *rear;
} StudentQueue;

// ===== Core Queue Functions =====
void initQueue(StudentQueue *q);
int isQueueEmpty(StudentQueue q);
void enqueueStudent(StudentQueue *q, Student s);
Student dequeueStudent(StudentQueue *q);
Student peekQueue(StudentQueue q);
void displayQueue(StudentQueue q);

// ===== Special Operation =====
// Compute total of ALL grades (math+science+english for all students)
int sumOfAllGrades(StudentQueue q) {

    Node *i = q.front;
    int sum = 0;

    while (i != NULL) {
        sum +=i->data.grade.math;
        sum+= i->data.grade.science;
        sum+=i->data.grade.english;
        i = i->next;

        
    }
    return sum;
}

int main() {
    StudentQueue q;
    initQueue(&q);

    // Sample students
    Student s1 = {1, "Alice", {90, 85, 88}};
    Student s2 = {2, "Bob", {75, 80, 70}};
    Student s3 = {3, "Charlie", {92, 89, 95}};

    // Enqueue
    enqueueStudent(&q, s1);
    enqueueStudent(&q, s2);
    enqueueStudent(&q, s3);

    // Display queue
    printf("All Students in Queue:\n");
    displayQueue(q);

    // Special Operation
    int total = sumOfAllGrades(q);
    printf("\nTotal of all grades in queue: %d\n", total);

    return 0;
}


// ===== Core Queue Functions =====

// Initialize queue
void initQueue(StudentQueue *q) {
    q->front = NULL;
    q->rear = NULL;
}

// Check if queue is empty
int isQueueEmpty(StudentQueue q) {
    return (q.front == NULL && q.rear == NULL);
}

// Enqueue a student at the rear
void enqueueStudent(StudentQueue *q, Student s) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = s;
    newNode->next = NULL;

    if (isQueueEmpty(*q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Dequeue a student from the front
Student dequeueStudent(StudentQueue *q) {
    if (isQueueEmpty(*q)) {
        printf("Queue is empty, cannot dequeue!\n");
        exit(1);
    }

    Node *temp = q->front;
    Student data = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;  // reset rear if queue is empty
    }

    free(temp);
    return data;
}

// Peek at the rear student
Student peekQueue(StudentQueue q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty, cannot peek!\n");
        exit(1);
    }
    return q.rear->data;
}

// Display all students in the queue
void displayQueue(StudentQueue q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }

    Node *curr = q.front;
    while (curr != NULL) {
        printf("ID: %d, Name: %s, Grades -> Math: %d, Science: %d, English: %d\n",
               curr->data.id, curr->data.name,
               curr->data.grade.math,
               curr->data.grade.science,
               curr->data.grade.english);
        curr = curr->next;
    }
}


int SumOfAllElements(StudentQueue*q) {
    int count = 0;
    StudentQueue tempQ;
    initQueue(&tempQ);


    Node *i = q->front;

    while (i != NULL) {
        
      count+= i->data.grade.english;
      count+=i->data.grade.math;
      count+= i->data.grade.science;

      i = i->next;
    }

    return count;

}
/************************************************************
 🎓 STUDENT ATTENDANCE TRACKER WITH SET OPERATIONS
*************************************************************
📘 CONTEXT:
Each bit in an unsigned int represents a student's attendance
for a day (1 = present, 0 = absent).  

We implement:
    1️⃣ markAttendance()         → Mark student present/absent
    2️⃣ isPresent()              → Check if a student was present
    3️⃣ printAttendance()        → Print all present students
    4️⃣ attendanceToArray()      → Convert attendance int → bool array
    5️⃣ arrayToAttendance()      → Convert bool array → attendance int
    6️⃣ unionAttendance()        → Students present in either week
    7️⃣ intersectAttendance()    → Students present in both weeks
    8️⃣ differenceAttendance()   → Students present in first but not second week
    9️⃣ matchingAttendanceCount()→ Count students present in both weeks
************************************************************/

#include <stdio.h>
#include <stdbool.h>

#define NUM_STUDENTS 8  // 0–7

// === Function Prototypes ===
void markAttendance(unsigned int *attendance, int studentIndex, bool present);
bool isPresent(unsigned int attendance, int studentIndex);
void printAttendance(unsigned int attendance);
void attendanceToArray(unsigned int attendance, bool arr[NUM_STUDENTS]);
unsigned int arrayToAttendance(bool arr[NUM_STUDENTS]);

unsigned int unionAttendance(unsigned int a, unsigned int b);
unsigned int intersectAttendance(unsigned int a, unsigned int b);
unsigned int differenceAttendance(unsigned int a, unsigned int b);
int matchingAttendanceCount(unsigned int a, unsigned int b);

// === Main Demo ===
int main() {
    unsigned int week1 = 0;
    unsigned int week2 = 0;
    bool arr[NUM_STUDENTS];

    // Week 1 attendance
    markAttendance(&week1, 0, true);
    markAttendance(&week1, 2, true);
    markAttendance(&week1, 5, true);

    // Week 2 attendance
    markAttendance(&week2, 1, true);
    markAttendance(&week2, 2, true);
    markAttendance(&week2, 5, true);
    markAttendance(&week2, 6, true);

    printf("Week 1 attendance: ");
    printAttendance(week1);
    printf("Week 2 attendance: ");
    printAttendance(week2);

    printf("\nStudents present in both weeks: %d\n", matchingAttendanceCount(week1, week2));

    unsigned int unionWeek = unionAttendance(week1, week2);
    unsigned int intersectWeek = intersectAttendance(week1, week2);
    unsigned int diffWeek = differenceAttendance(week1, week2);

    printf("\nUnion (either week): ");
    printAttendance(unionWeek);

    printf("Intersection (both weeks): ");
    printAttendance(intersectWeek);

    printf("Difference (Week1 but not Week2): ");
    printAttendance(diffWeek);

    // Convert to boolean array
    attendanceToArray(week1, arr);
    arr[3] = true;  // modify attendance array
    unsigned int updatedWeek1 = arrayToAttendance(arr);
    printf("\nWeek1 updated attendance: ");
    printAttendance(updatedWeek1);

    return 0;
}

// === Function Definitions (EMPTY) ===
void markAttendance(unsigned int *attendance, int studentIndex, bool present) {
    
    if (present) {
        *attendance|=(1U<<studentIndex);
    } else {
        *attendance &= ~(1U<<studentIndex);
    }
}



bool isPresent(unsigned int attendance, int studentIndex) {
    // Implement this
    return (((attendance>>studentIndex)&1U) !=0);
}


void printAttendance(unsigned int attendance) {
    for(int i = 0; i<NUM_STUDENTS; i++) {
        if ((((attendance>>i)&1U) == 1)) {
            printf("%d ", i);
        }
    }
    printf("\n");
    
}

void attendanceToArray(unsigned int attendance, bool arr[NUM_STUDENTS]) {

    for(int i = 0; i < NUM_STUDENTS;i++) {
        arr[i] = ((attendance>>i)&1U);
    }

}

unsigned int arrayToAttendance(bool arr[NUM_STUDENTS]) {
    unsigned int bits = 0;

    for(int i = 0; i < NUM_STUDENTS; i++) {
        if (arr[i]) {
        bits |= (1U<<i);
    }
}
    return bits;
}

unsigned int unionAttendance(unsigned int a, unsigned int b) {
    // Implement this
    return a | b ;
}

unsigned int intersectAttendance(unsigned int a, unsigned int b) {
    // Implement this
    return a & b;
}

unsigned int differenceAttendance(unsigned int a, unsigned int b) {
    // Implement this
    return a & (~b);
}

int matchingAttendanceCount(unsigned int a, unsigned int b) {
    int count = 0;

    for(int i = 0; i < 10; i++) {
        if (((a>>i)&1U) == (b>>i)&1U) {
            count++;

        }
    }
    return count;
}

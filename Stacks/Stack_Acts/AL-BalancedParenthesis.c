#include <stdio.h>
#include <stdlib.h>
#define MAX 100   // max size of stack

// Stack structure using ArrayList
typedef struct {
    char arr[MAX];
    int top;
} StackAL;

// Function declarations
void initStackAL(StackAL *s);       
int isEmptyAL(StackAL *s);          
int isFullAL(StackAL *s);           
void pushAL(StackAL *s, char value);
char popAL(StackAL *s);             
char peekAL(StackAL *s);            

int isBalancedAL(const char *exp);  // <-- Problem function

int main() {
    char expr1[] = "{[()]}";
    char expr2[] = "{[(])}";

    if (isBalancedAL(expr1))
        printf("%s is Balanced\n", expr1);
    else
        printf("%s is Not Balanced\n", expr1);

    if (isBalancedAL(expr2))
        printf("%s is Balanced\n", expr2);
    else
        printf("%s is Not Balanced\n", expr2);

    return 0;
}

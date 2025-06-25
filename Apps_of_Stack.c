#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ANSI escape sequences
#define RED "\033[0;91m"
#define ORANGE "\033[38;5;214m"
#define YELLOW "\033[0;93m"
#define GREEN "\033[0;92m"
#define BLUE "\033[0;94m"
#define PURPLE "\033[35m"
#define PINK "\033[38;5;200m"
#define RESET "\033[0m"
#define CLEAR "\033[2J \033[1;1H" // (clear terminal and move cursor to top left)8

#define SIZE 100
typedef struct
{
    int items[SIZE];
    int top;
} stack;
int isPrime(int num)
{
    if (num <= 1)
    {
        return 0;
    }
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }
    return 1;
}
stack *initialize()
{
    stack *s = malloc(sizeof(stack));
    s->top = -1;
    return s;
}
void push(stack *s, int x)
{
    s->top += 1;
    s->items[s->top] = x;
}
int pop(stack *s)
{
    int lost = s->items[s->top];
    s->top -= 1;
    return lost;
}
int isempty(stack *s)
{
    if (s->top == -1)
        return 1;
    else
        return 0;
}
int isfull(stack *s)
{
    if (s->top == (SIZE - 1))
        return 1;
    else
        return 0;
}
int peek(stack *s)
{
    int num4 = s->items[s->top];
    return num4;
}
void printStack(stack *s)
{
    while (!isempty(s))
    {
        printf(BLUE "| %d |\n" RESET, pop(s));
    }
    printf("\n");
}
void reverse(stack *s)
{
    stack *temp = initialize();
    int c = 0;
    while (!isempty(s))
    {
        push(temp, pop(s));
    }
    for (c = 0; c <= temp->top; c++)
    {
        s->items[c] = temp->items[c];
        s->top++;
    }
    free(temp);
}

int check(stack *s)
{
    if (s->top == -1 || s->top == 0)
    {
        printf(GREEN "the stack is considerd as sorted\n" RESET);
    }
    else
    {
        int j = 1;
        for (j = 1; j <= s->top; j++)
        {
            if (s->items[j] >= s->items[j - 1])
            {
                printf(RED "the stack is not sorted\n" RESET);
                break;
            }
        }
        if (j > s->top)
            printf(GREEN "the stack is sorted\n" RESET);
    }
}
void deletePrime(stack *s)
{
    stack *temp = initialize();
    stack *correctOrder = initialize();
    while (!isempty(s))
    {
        int num1 = pop(s);
        if (!isPrime(num1))
        {
            push(temp, num1);
        }
    }
    while (!isempty(temp))
    {
        push(correctOrder, pop(temp));
    }
    for (int a = 0; a <= correctOrder->top; a++)
    {
        s->items[a] = correctOrder->items[a];
        s->top++;
    }
    free(temp);
    free(correctOrder);
}
void merge(stack *s1, stack *s2)
{
    stack *temp = initialize();
    stack *sorted = initialize();

    while (!isempty(s1) && !isempty(s2))
    {
        if (peek(s1) < peek(s2))
            push(temp, pop(s1));
        else
            push(temp, pop(s2));
    }
    while (!isempty(s1))
        push(temp, pop(s1));
    while (!isempty(s2))
        push(temp, pop(s2));

    while (!isempty(temp))
    {
        int a = pop(temp);
        push(sorted, a);
    }
    printStack(sorted);
}
void isBalanced(char *expr)
{
    stack* s = initialize();
    int m = strlen(expr);
    for (int i = 0; i < m; i++)
    {
        if(expr[i] == '(' || expr[i] == '[' || expr[i] == '{')
        {
            push(s,expr[i]);
        }
        else if (expr[i] == ')' || expr[i] == ']' || expr[i] == '}')
        {
            if(!isempty(s))
            {
                if (expr[i] == peek(s)+2 || expr[i] == peek(s)+1)
                {
                    pop(s);
                }
                else
                {
                    printf(RED"wrong order\n"RESET);
                    return;
                }
            }
            else
            {
                printf(RED"the closed bracket doesn't have an open bracket\n"RESET);
                return;
            }
        }
    }
    if (!isempty(s))
    {
        printf(RED"the open bracket doesn't have a close bracket!\n"RESET);
        return;
    }
    
    printf(GREEN"the expression is balanced!\n"RESET);
}

int main()
{
while (1)
{
    printf(
        BLUE "welcome to the stack program!\n" BLUE "choose one of the following options:\n" 
        ORANGE "0- " YELLOW "exit the program\n" 
        ORANGE "1- " PURPLE "reversing a stack and printing it\n" 
        ORANGE "2- " PURPLE "checking if the stack is sorted\n" 
        ORANGE "3- " PURPLE "deleting the prime numbers\n" 
        ORANGE "4- " PURPLE "merging the 2 stacks in sorted manner\n" 
        ORANGE "5- " PURPLE "checking for the brackets\n" RESET);
    
    stack *s = initialize();
    stack *p = initialize();

    int in;
    scanf("%d", &in);
    switch (in)
    {
    case 0:
        exit(0);
        break;
    case 1:
        char str1[SIZE];
        printf(BLUE "enter the string \n" RESET);
        scanf("%s", str1);
        int n = strlen(str1);
        int c1 = 0;
        for (c1 = 0; c1 < n; c1++)
        {
            s->items[c1] = str1[c1];
            s->top++;
        }
        reverse(s);
        printf(GREEN "The stack is reversed!\n" RESET);
        for (int i = 0; i <= s->top; i++)
        {
            printf(BLUE "%c" RESET, s->items[i]);
        }
        printf("\n");
        break;

    case 2:
        int n2 = 0, var = 0;
        printf(BLUE "enter the no. elements in the stack \n" RESET);
        scanf("%d", &n2);
        if (n2)
        {
            printf(BLUE "enter the elements of the stack \n" RESET);
            for (int c2 = 0; c2 < n2; c2++)
            {
                scanf("%d", &var);
                push(s, var);
            }
        }
        check(s);
        break;

    case 3:
        int n3 = 0, var3 = 0;
        printf(BLUE "enter the no. elements in the stack \n" RESET);
        scanf("%d", &n3);
        if (n3)
        {
            printf(BLUE "enter the elements of the stack \n" RESET);
            for (int c3 = 0; c3 < n3; c3++)
            {
                scanf("%d", &var3);
                push(s, var3);
            }
        }
        deletePrime(s);
        printStack(s);
        break;

    case 4:
        int n4 = 0, var4 = 0, n6 = 0, var6 = 0;
        printf(BLUE "enter the no. elements in the first stack \n" RESET);
        scanf("%d", &n4);
        printf(BLUE "enter the no. elements in the second stack \n" RESET);
        scanf("%d", &n6);
        printf(BLUE "enter the elements of the first stack \n" RESET);
        for (int c4 = 0; c4 < n4; c4++)
        {
            scanf("%d", &var4);
            push(s, var4);
        }
        printf(BLUE "enter the elements of the second stack \n" RESET);
        for (int c6 = 0; c6 < n6; c6++)
        {
            scanf("%d", &var6);
            push(p, var6);
        }
        merge(s, p);
        break;
    case 5:
        printf(BLUE "enter the expresion you wnat to check\n" RESET);
        char str2[SIZE];
        scanf("%s", str2);
        isBalanced(str2);
        break;
    default:
        printf(RED "oops! invalid input!\n" RESET);
        break;
    }
    printf(YELLOW"\n**********************************************************\n"RESET);
}
    return 0;
}
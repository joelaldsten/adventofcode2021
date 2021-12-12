#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define imax 102
#define jmax 100

char input[imax][jmax];

char incomplete[imax][jmax / 2];

void readinput(FILE *fp);

char getfirst(int i);

int errorscore(void);

char inv(char c);

int samesyn(char c1, char c2);

int score(char c);

long gettask2(void);

long calc(int i);

int comp(const void *a, const void *b)
{
    long f = *((long *)a);
    long s = *((long *)b);
    return (f > s) - (f < s);
}

int main(int argc, char *argv[])
{
    FILE *fp = fopen("input.txt", "r");
    readinput(fp);
    printf("errorscore: %d\n", errorscore());
    printf("incomplete seq score: %ld\n", gettask2());  // right answer 4001832844
    /*for (int i = 0; i < imax; i++)
    {   
        if (strlen(incomplete[i]) != 0) printf("%s, %d\n", incomplete[i], strlen(incomplete[i]));
    }*/
    fclose(fp);
    return 0;
}

long gettask2()
{
    int nbrincomplete = 0;
    for (int i = 0; i < imax; i++)
    {   
        if (strlen(incomplete[i]) != 0)
        {
            nbrincomplete++;
        }
    }
    long nr[nbrincomplete];
    int index = 0;
    printf("nbrincomplete %d ", nbrincomplete);
    for (int i = 0; i < imax; i++)
    {   
        //printf("%d, ", noerror[i]);
        if (strlen(incomplete[i]) != 0)
        {
            //printf("%d, ", i);
            nr[index] = calc(i);
            index++;
        }
    }
    printf("index = %d \n", index);
    qsort(nr, sizeof(nr) / sizeof(*nr), sizeof(*nr), comp);
    return nr[nbrincomplete/2+8];
}

long calc(int i)
{
    char *s = incomplete[i];
    long score = 0;
    for (int j = 0; j < strlen(s); j++)
    {
        char c = s[j];
        switch (c)
        {
        case ')':
            score = score * 5 + 1;
            break;
        case ']':
            score = score * 5 + 2;
            break;
        case '}':
            score = score * 5 + 3;
            break;
        case '>':
            score = score * 5 + 4;
            break;
        }
    }
    return score;
}

int errorscore(void)
{
    int sum = 0;
    for (int i = 0; i < imax; i++)
    {
        int s = score(getfirst(i));
        sum += s;
    }
    return sum;
}

char getfirst(int i)
{
    char stack[jmax];
    int sp = 0;
    int j = 0;
    while (input[i][j] != '|')
    {
        char c = input[i][j];
        //printf("%c", c);
        if (c == '(' || c == '{' || c == '[' || c == '<')
        {
            stack[sp] = c;
            sp++;
        }
        else
        {
            sp--;
            if (!samesyn(stack[sp], input[i][j])) //fault
            {
                return input[i][j];
            }
            stack[sp] = '\0';
        }
        j++;
    }
    //printf("\n");
    //printf("stack = %s, stack pointer = %d\n", stack, sp);
    sp--;
    if (sp != 0)
    {
        int index = 0;
        char dest[jmax / 2];
        while (sp > -1)
        {
            dest[index] = inv(stack[sp]);
            index++;
            sp--;
        }
        dest[index] = '\0';
        strcpy(incomplete[i], dest);
    }
    else
        strcpy(incomplete[i], "\0");
    return ' ';
}

char inv(char c)
{
    switch (c)
    {
    case '(':
        return ')';
        break;
    case '[':
        return ']';
        break;
    case '{':
        return '}';
        break;
    case '<':
        return '>';
        break;
    default:
        return 'x';
    }
}

int score(char c)
{
    switch (c)
    {
    case ')':
        return 3;
        break;
    case ']':
        return 57;
        break;
    case '}':
        return 1197;
        break;
    case '>':
        return 25137;
        break;
    default:
        return 0;
    }
}

int samesyn(char c1, char c2)
{
    switch (c1)
    {
    case '<':
        return c2 == '>';
        break;
    case '{':
        return c2 == '}';
        break;
    case '[':
        return c2 == ']';
    case '(':
        return c2 == ')';
        break;
    default:
        return 0;
    }
}

void readinput(FILE *fp)
{
    for (int i = 0; i < imax; i++)
    {
        for (int j = 0; j < jmax; j++)
        {
            char c = (char)fgetc(fp);
            if ((int)c == 10 || (int)c == EOF)
            {
                input[i][j] = '|';
                break;
            }
            else
                input[i][j] = c;
        }
    }
}
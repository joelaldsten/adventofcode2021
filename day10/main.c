#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define imax 10
#define jmax 30

char input[imax][jmax];

char stack[jmax];

//char incomplete[imax];
char incomplete[imax][imax/2];
//a[0] = "blah";
//a[1] = "hmm";

void readinput(FILE *fp);

char getfirst(int i);

int errorscore(void);

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
    default :
        return 0;
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

int main(int argc, char *argv[])
{
    FILE *fp = fopen("input.txt", "r");
    readinput(fp);
    //int error = errorscore()
    printf("errorscore: %d", errorscore());
    printf("\n");
    for (int i = 0; i < imax; i++)
    {
        printf("%s \n", incomplete[i]);
    }
    
    fclose(fp);
    return 0;
}

int errorscore(void) {
    int sum = 0;
    for (int i = 0; i < imax; i++) {
        sum += score(getfirst(i));
    }
    return sum;
}

char getfirst(int i)
{
    int sp = 0;
    int j = 0;
    while(input[i][j] != '|')
    {
        char c = input[i][j];
        if (c == '(' || c == '{' || c == '[' || c == '<')
        {
            stack[sp] = c;
            sp++;
        }
        else
        {
            sp--;
            char open = stack[sp];
            if (!samesyn(open, input[i][j])) //fault
            {
                return input[i][j];
            }
        }
        j++;
    }
    if (sp != 0) {
        int index = 0;
        char dest[imax/2];
        while (sp != 0) {
            dest[index] = stack[sp];
            index++;
            sp--;
        }
        dest[index] = '\0';
        strcpy(incomplete[i], dest);
        //incomplete[i] = dest;
    }
    else strcpy(incomplete[i], "");
    return ' ';
}

void readinput(FILE *fp)
{   
    for (int i = 0; i < imax; i++)
    {
        for (int j = 0; j < jmax; j++)
        {
            char c = (char) fgetc(fp);
            if ((int) c == 10 || (int) c == EOF){
                input[i][j] = '|';
                break;
            }
            else input[i][j] = c;
        }
    }
}
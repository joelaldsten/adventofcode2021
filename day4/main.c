#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int worstscore = 0;
int lastnbr;
int sumunmarked;
int mat[5][5], table[5][5], numbers[100];

void check(void);

int solved(int row, int col);

int getsum();

int main(int argc, char *argv[])
{
    FILE *fp = fopen("input.txt", "r");
    int number[2];
    number[0] = number[1] = 0;
    int i = 0;
    while (i < 100)
    { // reads the first line and get all integers
        int c = fgetc(fp);
        if (c == 44 || c == 10)
        {
            numbers[i] = 10 * number[0] + number[1];
            number[0] = number[1] = 0;
            i++;
        }
        else
        {
            if (number[1] != 0)
            {
                number[0] = number[1];
                number[1] = c - 48;
            }
            else
                number[1] = c - 48;
        }
    }
    int c = fgetc(fp);
    while (c != EOF)
    {
        if (isdigit(c))
        { // new number means new matrix :)
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    int first = c - 48;
                    c = fgetc(fp);
                    if (isdigit(c))
                    {
                        mat[i][j] = first * 10 + c - 48;
                        c = fgetc(fp);
                    }
                    else
                        mat[i][j] = first;
                    while (!isdigit(c) && c != EOF)
                        c = fgetc(fp);
                    table[i][j] = 0;
                }
            }
            check();
        }
        else
            c = fgetc(fp);
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
    printf("last drawn number was %d\n", lastnbr);
    printf("sum of all unmarked: %d\n", sumunmarked);
    printf("answer: %d", lastnbr * sumunmarked);
    fclose(fp);
    return 0;
}

void check()
{
    int score = 0;
    while (score < 100)
    {
        int nbr = numbers[score];
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (mat[i][j] == nbr)
                {
                    table[i][j] = 1;
                    if (solved(i, j))
                    {
                        if (score > worstscore)
                        {
                            worstscore = score;
                            lastnbr = nbr;
                            sumunmarked = getsum();
                        }
                        return;
                    }
                }
            }
        }
        score++;
    }
}

int solved(int row, int col)
{
    int nbrrow = 0;
    int nbrcol = 0;
    for (int i = 0; i < 5; i++)
    {
        if (table[row][i] == 1)
            nbrrow++;
        if (table[i][col] == 1)
            nbrcol++;
    }
    return (nbrrow == 5 || nbrcol == 5);
}

int getsum()
{
    int sum = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (table[i][j] == 0)
            {
                sum += mat[i][j];
            }
        }
    }
    return sum;
}

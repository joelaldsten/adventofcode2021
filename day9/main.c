#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define imax 100
#define jmax 100

int input[imax][jmax];
int used[imax][jmax];

int sumrisk(void);

int sumbasin(void);

int islowpoint(int i, int j);

int getheight(int i, int j);

int basinsearch(int i, int j, int height);

int comp(const void *a, const void *b)
{
    int f = *((int *)a);
    int s = *((int *)b);
    return (f > s) - (f < s);
}

int main(int argc, char *argv[])
{
    FILE *fp = fopen("input.txt", "r");
    int counter = 0;
    for (int i = 0; i < imax; i++)
    {
        for (int j = 0; j < jmax; j++)
        {
            input[i][j] = fgetc(fp) - 48;
            used[i][j] = 0;
        }
        fgetc(fp); //get rid of new line
    }
    printf("sum of risk levels: %d\n", sumrisk());
    printf("sum of the 3 largest basin: %d", sumbasin());
    fclose(fp);
    return 0;
}

int basinsearch(int i, int j, int height)
{
    int sum = 0;
    if (used[i][j])
        return sum;
    used[i][j] = 1;
    if (getheight(i, j - 1) < 9)
    {
        sum += basinsearch(i, j - 1, input[i][j]);
    }
    if (getheight(i, j + 1) < 9)
    {
        sum += basinsearch(i, j + 1, input[i][j]);
    }
    if (getheight(i - 1, j) < 9)
    {
        sum += basinsearch(i - 1, j, input[i][j]);
    }
    if (getheight(i + 1, j) < 9)
    {
        sum += basinsearch(i + 1, j, input[i][j]);
    }
    return sum + 1;
}

int sumrisk(void)
{
    int sum = 0;

    for (int i = 0; i < imax; i++)
    {
        for (int j = 0; j < jmax; j++)
        {
            if (islowpoint(i, j))
            {
                sum += 1 + input[i][j];
            }
        }
    }
    return sum;
}

int sumbasin(void)
{
    int basin[3];

    for (int i = 0; i < 3; i++)
    {
        basin[i] = 0;
    }

    for (int i = 0; i < imax; i++)
    {
        for (int j = 0; j < jmax; j++)
        {
            if (islowpoint(i, j))
            {
                int basinsize = basinsearch(i, j, input[i][j]);
                if (basinsize > basin[0])
                {
                    basin[0] = basinsize;
                    qsort(basin, sizeof(basin) / sizeof(*basin), sizeof(*basin), comp);
                }
            }
        }
    }
    return basin[0] * basin[1] * basin[2];
}

int islowpoint(int i, int j)
{
    int height = input[i][j];
    return (height < getheight(i, j - 1) && height < getheight(i, j + 1) && height < getheight(i - 1, j) && height < getheight(i + 1, j));
}

// returns height if point is out of bounds return max int value
int getheight(int i, int j)
{
    if (i < 0 || j < 0 || i >= imax || j >= jmax)
        return INT_MAX;
    else
        return input[i][j];
}
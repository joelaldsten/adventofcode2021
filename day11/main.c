#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int grid[10][10];

int flashed[10][10];

void readinput(FILE *fp);

void printgrid(void);

int step(int s);

void flash(int i, int j, int s);

void inc(int i, int j, int s);

int main(int argc, char *argv[])
{
    FILE *fp = fopen("input.txt", "r");
    readinput(fp);
    /* task 1
    int totalflashes = 0;
    for (int i = 1; i < 101; i++)
    {
        totalflashes += step(i);
    }
    printf("nbr of flashes %d\n", totalflashes);*/
    int firststep = -1;
    for (int i = 1; firststep == -1; i++)
    {
        if(step(i) == 100) firststep = i;
    }
    printf("first step during which all flash %d\n", firststep);
    fclose(fp);
    return 0;
}

int step(int s)
{
    int flashes = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            grid[i][j]++;
        }
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (grid[i][j] > 9 && flashed[i][j] != s) flash(i,j, s);
        }
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (flashed[i][j] == s){
                grid[i][j] = 0;
                flashes++;
            }
        }
    }
    return flashes;
}

void flash(int i, int j, int s) {
    flashed[i][j] = s;
    inc(i + 1, j, s);
    inc(i + 1, j + 1, s);
    inc(i + 1, j - 1, s);
    inc(i, j + 1, s);
    inc(i, j - 1, s);
    inc(i - 1, j, s);
    inc(i - 1, j + 1, s);
    inc(i - 1, j - 1, s);
}

void inc(int i, int j, int s) {
    if (i > 9 || i < 0 || j > 9 || j < 0) return;
    grid[i][j]++;
    if (grid[i][j] > 9 && flashed[i][j] != s) flash(i, j, s);
}

void printgrid(void)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

void readinput(FILE *fp)
{
    int c;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            grid[i][j] = fgetc(fp) - 48;
        }
        fgetc(fp);
    }
}
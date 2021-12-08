#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int readnumber(FILE *fp);

int comp(const void *a, const void *b)
{
    int f = *((int *)a);
    int s = *((int *)b);
    return (f > s) - (f < s);
}

int cost(int a, int b)
{
    int delta = abs(a - b);
    return (delta * (delta + 1)) / 2;
}

int min(int *list);

int calc(int pos);

int input[1000];

int main(int argc, char *argv[])
{
    FILE *fp = fopen("input.txt", "r");
    int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        int num = readnumber(fp);
        input[i] = num;
        sum += num;
    }
    int mean = round((double)sum / 1000); //used to guess
    printf("mean %d\n", mean);
    qsort(input, sizeof(input) / sizeof(*input), sizeof(*input), comp);
    int totalfuel = 0;
    int guess[5];
    for (int i = 0; i < 3; i++)
    {
        int pos = mean - 1 + i;
        guess[i] = calc(pos);
    }
    totalfuel = min(guess);
    /* task 1
    int median = input[500];
    for (int i = 0; i < 1000; i++) {
        totalfuel += abs(median - input[i]);
    }*/
    printf("total fuel used: %d", totalfuel);
    fclose(fp);
    return 0;
}

int calc(int pos)
{
    int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        sum += cost(pos, input[i]);
    }
    return sum;
}

int min(int *list)
{
    int size = sizeof(list) / sizeof(*list);
    int min = INT_MAX;
    for (int i = 0; i < size; i++)
    {
        if (list[i] < min)
        {
            min = list[i];
        }
    }
    return min;
}

int readnumber(FILE *fp)
{
    int number[4];
    int c = fgetc(fp);
    int counter = 0;
    while (isdigit(c))
    {
        number[counter] = c - 48;
        c = fgetc(fp);
        counter++;
    }
    int value;
    switch (counter)
    {
    case 1:
        value = number[0];
        break;
    case 2:
        value = 10 * number[0] + number[1];
        break;
    case 3:
        value = 100 * number[0] + 10 * number[1] + number[2];
        break;
    case 4:
        value = 1000 * number[0] + 100 * number[1] + 10 * number[2] + number[3];
        break;
    }
    return value;
}
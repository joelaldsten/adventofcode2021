#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

void readinput(FILE *fp);

void mapsignals(int i, int *signals);

int contains(char *s1, char *s2);

int contains2(char *s1, char *s2);

int getnumber(int i, int *signals);

#define inputsize 200
char input[inputsize][10][8];
char output[inputsize][4][8];

int main(int argc, char *argv[])
{
    FILE *fp = fopen("input.txt", "r");
    readinput(fp);
    /* task 1
    int counter = 0;
    for (int i = 0; i < inputsize; i++)
    {
        for (int j = 0; j < 4; j++) {
            switch (strlen(output[i][j]))
            {
            case 2:
                counter++;
                break;
            case 3:
                counter++;
                break;
            case 4:
                counter++;
                break;
            case 7:
                counter++;
                break;
            }
        }
    }
    printf("%d", counter);*/
    int signals[10];
    int sum = 0;
    for (int i = 0; i < inputsize; i++)
    {
        mapsignals(i, signals);
        sum += getnumber(i, signals);
    }
    printf("value = %d", sum);
    fclose(fp);
    return 0;
}

int getnumber(int i, int *signals)
{
    int numbers[4];
    for (int k = 0; k < 4; k++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (contains2(input[i][j], output[i][k]))
            {
                numbers[k] = signals[j];
                break;
            }
        }
    }
    return 1000 * numbers[0] + 100 * numbers[1] + 10 * numbers[2] + numbers[3];
}

void mapsignals(int i, int *signals)
{
    int signalsindex[10];
    int seg5[3];
    int seg5isum = 0;
    int seg6[3];
    int seg6isum = 0;
    int c5, c6;
    c5 = c6 = 0;
    for (int j = 0; j < 10; j++)
    {
        switch (strlen(input[i][j]))
        {
        case 5:
            seg5[c5] = j;
            seg5isum += j;
            c5++;
            break;
        case 6:
            seg6[c6] = j;
            seg6isum += j;
            c6++;
            break;
        case 2:
            signalsindex[1] = j;
            break;
        case 3:
            signalsindex[7] = j;
            break;
        case 4:
            signalsindex[4] = j;
            break;
        case 7:
            signalsindex[8] = j;
            break;
        }
    }
    //time to match to get the other numbers
    //start by finding 3 which is part of 5 segment subset with 2 and 5 and 3 is the only one which covers 1
    for (int j = 0; j < 3; j++)
    {
        if (contains(input[i][seg5[j]], input[i][signalsindex[1]]))
        {
            signalsindex[3] = seg5[j];
            seg5isum -= seg5[j];
            break;
        }
    }
    // 6 is the only number in seg6 which does not cover 1
    for (int j = 0; j < 3; j++)
    {
        if (!contains(input[i][seg6[j]], input[i][signalsindex[1]]))
        {
            signalsindex[6] = seg6[j];
            seg6isum -= seg6[j];
        }
    }
    // 9 is the only number in seg6 that covers both 1 and 4
    for (int j = 0; j < 3; j++)
    {
        if (contains(input[i][seg6[j]], input[i][signalsindex[1]]) && contains(input[i][seg6[j]], input[i][signalsindex[4]]))
        {
            signalsindex[9] = seg6[j];
            seg6isum -= seg6[j];
        }
    }
    // 5 is included in 9 and does not include 1
    for (int j = 0; j < 3; j++)
    {
        if (!contains(input[i][seg5[j]], input[i][signalsindex[1]]) && contains(input[i][signalsindex[9]], input[i][seg5[j]]))
        {
            signalsindex[5] = seg5[j];
            seg5isum -= seg5[j];
        }
    }
    // zero is left in seg6 and 2 is left in seg5
    signalsindex[0] = seg6isum;
    signalsindex[2] = seg5isum;
    for (int j = 0; j < 10; j++)
    {
        signals[signalsindex[j]] = j;
    }
}

int contains2(char *s1, char *s2)
{
    if (strlen(s1) != strlen(s2))
        return 0;
    int i = 0;
    for (int j = 0; j < strlen(s2); j++)
    {
        if (strchr(s1, s2[j]) != NULL)
            i++;
    }
    return i == strlen(s2);
}

int contains(char *s1, char *s2)
{
    for (int i = 0; i < strlen(s2); i++)
    {
        if (strchr(s1, s2[i]) == NULL)
            return 0;
    }
    return 1;
}

void readinput(FILE *fp)
{
    int c;
    for (int i = 0; i < inputsize; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            c = fgetc(fp);
            int index = 0;
            while (c != ' ')
            {
                input[i][j][index] = c;
                c = fgetc(fp);
                index++;
            }
        }

        c = fgetc(fp); // '|'
        c = fgetc(fp); // ' '
        for (int j = 0; j < 4; j++)
        {
            c = fgetc(fp);
            int index = 0;
            while (c != ' ' && c != '\n' && c != EOF)
            {
                output[i][j][index] = c;
                c = fgetc(fp);
                index++;
            }
        }
    }
}

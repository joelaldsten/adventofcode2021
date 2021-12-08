#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef struct data_t data;
struct data_t
{
    int valid;
    int arr[12];
};

int gammaValue = 0;
int epsilonValue = 0;
int most[12];
data oxy[1000];
data co2[1000];

void convert(int a[]);

int getOxy(void);

int getCo2(void);

int main(int argc, char *argv[])
{
    FILE *fp = fopen("input.txt", "r");
    int c = fgetc(fp);
    int i = 0;
    int current[12];
    int line = 0;
    oxy[line].valid = 1;
    co2[line].valid = 1;
    for (int j = 0; j < 12; j++)
    {
        most[j] = 0;
    }
    while (c != EOF)
    {
        if (c == 10)
        {
            line++;
            oxy[line].valid = 1;
            co2[line].valid = 1;
        }
        if (isdigit(c))
        {
            current[i % 12] = c - 48;
            if (c == 48)
            {
                most[i % 12] -= 1;
                oxy[line].arr[i % 12] = 0;
                co2[line].arr[i % 12] = 0;
            }
            if (c == 49)
            {
                most[i % 12] += 1;
                oxy[line].arr[i % 12] = 1;
                co2[line].arr[i % 12] = 1;
            }
            i++;
        }
        c = fgetc(fp);
    }
    for (int i = 0; i < 12; i++)
    {
        printf("%d, ", most[i]);
    }

    convert(most);
    printf("gammaValue %d, epsilonValue %d, power consumption %d", gammaValue, epsilonValue, gammaValue * epsilonValue);

    int oxygen = getOxy();
    int carbondioxide = getCo2();
    printf("\nOXYGEN:%d", oxygen);
    printf("\nCo2:%d", carbondioxide);
    printf("\nlife support:%d", oxygen * carbondioxide);
    fclose(fp);
    return 0;
}

void convert(int a[])
{
    for (int i = 0; i < 12; i++)
    {
        if (a[i] > 0)
        {
            gammaValue += pow(2, (11 - i));
        }
        else
        {
            epsilonValue += pow(2, (11 - i));
        }
    }
}

int getOxy(void)
{
    int removed = 0;
    for (int bitpos = 0; bitpos < 12; bitpos++)
    {
        int mc;
        if (most[bitpos] < 0)
        {
            mc = 0;
        }
        else
            mc = 1;
        //printf("\n mc = %d", mc);
        for (int i = 0; i < 1000; i++)
        {
            if (oxy[i].arr[bitpos] != mc)
            {
                if (oxy[i].valid == 1)
                {
                    /*printf("\n removed ,v = %d   ", oxy[i].valid);                     
                    for (int j = 0; j < 12; j++) {
                            printf("%d", oxy[i].arr[j]);
                        }*/
                    oxy[i].valid = -1;
                    removed++;
                }
                if (removed == 999)
                {
                    for (int k = 0; k < 1000; k++)
                    {
                        /*printf("\n valid = %d, k = %d | ", oxy[k].valid, k);
                        for (int j = 0; j < 12; j++) {
                            printf("%d", oxy[k].arr[j]);
                        }*/
                        if (oxy[k].valid == 1)
                        {
                            int value = 0;
                            for (int j = 0; j < 12; j++)
                            {
                                //printf("%d",oxy[i].arr[j]);
                                if (oxy[k].arr[j] > 0)
                                    value += pow(2, (11 - j));
                            }
                            return value;
                        }
                    }
                }
            }
        }
    }
    return -1;
}
int getCo2(void)
{
    int removed = 0;
    for (int bitpos = 0; bitpos < 12; bitpos++)
    {
        int mc;
        if (most[bitpos] < 0)
        {
            mc = 1;
        }
        else
            mc = 0;
        //printf("\n mc = %d", mc);
        for (int i = 0; i < 1000; i++)
        {
            if (co2[i].arr[bitpos] != mc)
            {
                if (co2[i].valid == 1)
                {
                    /*printf("\n removed ,v = %d   ", co2[i].valid);                     
                    for (int j = 0; j < 12; j++) {
                            printf("%d", co2[i].arr[j]);
                        }*/
                    co2[i].valid = -1;
                    removed++;
                }
                if (removed == 999)
                {
                    for (int k = 0; k < 1000; k++)
                    {
                        /*printf("\n valid = %d, k = %d | ", co2[k].valid, k);
                        for (int j = 0; j < 12; j++) {
                            printf("%d", co2[k].arr[j]);
                        }*/
                        if (co2[k].valid == 1)
                        {
                            int value = 0;
                            for (int j = 0; j < 12; j++)
                            {
                                //printf("%d",co2[i].arr[j]);
                                if (co2[k].arr[j] > 0)
                                    value += pow(2, (11 - j));
                            }
                            return value;
                        }
                    }
                }
            }
        }
    }
    return -1;
}
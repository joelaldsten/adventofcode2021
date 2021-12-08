#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp = fopen("input.txt", "r");
    int x = 0;
    int y = 0;
    int aim = 0;
    char input[255]; ///varför crashar detta då vi har 9???
    for (int i = 0; i < 1000; i++)
    {
        fgets(input, 12, fp);

        switch (input[0])
        {
        case 'f':
            x += input[8] - 48;
            y += aim * (input[8] - 48);
            break;
        case 'd':
            aim += input[5] - 48;
            break;
        case 'u':
            aim -= input[3] - 48;
            break;
        }
    }
    printf("x: %d, y: %d, sum %d \n", x, y, x * y);
    fclose(fp);
    return 0;
}
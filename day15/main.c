#include <stdio.h>
#include <stdlib.h>

int map[100][100];

int minpath(){
    
}

void readinput(FILE *fp){
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            map[i][j] = fgetc(fp);
        }
        fgetc(fp);
    }
}

int main(int argc, char *argv[]) {
    FILE *fp = fopen("input.txt", "r");
    readinput(fp);
    return 0;
}
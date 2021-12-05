#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void insertline(int line[], int end, int index);

void readinput(FILE *fp);

void populategird(void);

int lines[500][4];

int grid[1000][1000];

int sign(int x) {
    return (x > 0) - (x < 0);
}

int main(int argc, char *argv[]) {
	FILE *fp = fopen("input.txt", "r");
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            grid[i][j] = 0;
        }
    }
    readinput(fp);
    populategird();
    int overlap = 0;
    for(int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            if (grid[i][j] > 1) overlap++;
        }
    }
    printf("Overlap %d", overlap);
	fclose(fp);
	return 0;
}

void populategird(void) {
    int x1, x2, y1, y2;
    for (int i = 0; i < 500; i++) {
        x1 = lines[i][0]; 
        y1 = lines[i][1];
        x2 = lines[i][2]; 
        y2 = lines[i][3];
        int dxsign = sign(x2 - x1);
        int dysign = sign(y2 - y1);
        if (dxsign == 0) {
            while (y1 != y2) {
                grid[x1][y1]++;
                y1 += dysign;
            }
            grid[x2][y2]++;
        }
        else if (dysign == 0) {
            while (x1 != x2) {
                grid[x1][y1]++;
                x1 += dxsign;
            }
            grid[x2][y2]++;
        }
        else {
            while (x1 != x2 && y1 != y2) {
                grid[x1][y1]++;
                x1 += dxsign;
                y1 += dysign;
            }
            grid[x2][y2]++;
        }
    }
}

void readinput(FILE *fp) {
    int linebuffer[255];
    int c = fgetc(fp);
    int currentnumber = 0;
    for (int i = 0; i < 500; i++) {
        int index = 0;
        while(c != 10 && c != EOF) {                                //reads until new line or EOF
            linebuffer[index] = c;
            c = fgetc(fp);
            if(c == 32){                                           //remove arrow and add , to make parsing easier
                fgetc(fp);
                fgetc(fp);
                fgetc(fp);
                c = 44;
            }
            index++;
        }
        if (index != 0) {
            insertline(linebuffer, index, i);
        }
        c = fgetc(fp);
    }
}

void insertline(int line[], int end, int linesindex){
    int index = 0;
    int number[3];
    int value;
    int c = 0;
    while (index < end) {
        int i = 0;
        number[0] = number [1] = number[2] = 0;
        while(isdigit(line[index]) && index < end) {
            number[i] = line[index] - 48;
            i++;
            index++;
        }
        if (i > 0) {
            switch (i) {
                case 1 : 
                    value = number[0];
                    break;
                case 2 : 
                    value = 10 * number[0] + number[1];
                    break;
                case 3 :
                    value = 100 * number[0] + 10 * number[1] + number[2];
                    break;
            }
            lines[linesindex][c] = value;
            c++;
        }
        index++;
    }
}
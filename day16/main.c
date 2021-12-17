#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char input[1308];

int bintodec(char bin[], int read){
    int value = 0;
    for (int i = 0; i < read; i++)
    {
        value += (bin[i] - 48) * pow(2, read - i - 1);
    }
    return value;
}

char* hextobin(char c){
    switch (c) {
        case '0':
            return "0000";
        case '1':
            return "0001";
        case '2':
            return "0010";
        case '3':
            return "0011";
        case '4':
            return "0100";
        case '5':
            return "0101";
        case '6':
            return "0110";
        case '7':
            return "0111";
        case '8':
            return "1000";
        case '9':
            return "1001";
        case 'A':
            return "1010";
        case 'B':
            return "1011";
        case 'C':
            return "1100";
        case 'D':
            return "1101";
        case 'E':
            return "1110";
        case 'F':
            return "1111";
    }
}

void parse_nbr_of_packet(int i);

void parse_packet_length(int i);

void parseheader(int i){
    int version,id, lbit;
    char *hex;
    int *vhex = hextobin(input[i]);
    i++;
    version = bintodec(vhex, 3);
    char *idhex = hextobin(input[i]);
    i++;
    id = (vhex[3] - 48)* pow(2,2) + bintodec(idhex, 2);
    lbit = idhex[2];
    if(lbit) {          // I bit = 1 -> 11 bits rep sub packets
        int p[11];
        p[0] = idhex[3] - 48;
        int index = 0;
        while (index < 10)
        {   
            if (index % 4 == 0){
                hex = hextobin(input[i]);
                i++;
            }
            p[index+1] = hex[index % 4] - 48;
            index++;
        }
        parse_nbr_of_packet(bintodec(p, 11));
    }
    else {              // I bit = 0 -> 15 bits rep total length
        int p[15];
        p[0] = idhex[3] - 48;
        int index = 0;
        while (index < 14)
        {   
            if (index % 4 == 0){
                hex = hextobin(input[i]);
                i++;
            }
            p[index+1] = hex[index % 4] - 48;
            index++;
        }
        parse_packet_length(bintodec(p, 15));
    }
        
}

void readinput(FILE *fp) {
    char c = fgetc(fp);
    int i = 0;
    while (c != EOF) {
        input[i] = c;
        c = fgetc(fp);
        i++;
    }
}

int main(int argc, char *argv[]) {
    FILE *fp = fopen("input.txt", "r");
    readinput(fp);
    fclose(fp);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

long long shiftarr(long long *arr);

void printfish(int *arr, int days);

int main(int argc, char *argv[]) {
    FILE *fp = fopen("input.txt", "r");
    int c = fgetc(fp);
    long long fish[9];
    for (int i = 0; i < 9; i++) {
        fish[i] = 0;
    }
    while (c != EOF) {
        if (isdigit(c)) {
            fish[c - 48]++;
        }
        c = fgetc(fp);
    }
    //printfish(fish, 0);
    for (int i = 0; i < 256; i++) {
        long long newfish = shiftarr(fish);
        fish[6] += newfish;
        fish[8] = newfish;
        //printfish(fish, i+1);
    }
    long long sum = 0;
    for (int i = 0; i < 9; i++){    
        if (fish[i] < 0) printf("roll over %lld ", fish[i]);
        sum += fish[i];
    }
    printf("number of fish: %lld", sum);
    fclose(fp);
	return 0;
}

long long shiftarr(long long *arr) {
    long long removed = arr[0];
    for (int i = 0; i < 8; i++){        
        arr[i] = arr[i+1];
    }
    arr[8] = 0;
    return removed;
}

void printfish(int *arr, int days){
    printf("After  %d days: ", days);
    for (int j = 0; j < 9; j++){
        if (arr[j] != 0) {
            for (int k = 0; k < arr[j]; k++) {
                printf("%d,", j);
            }
        }
    }
    printf("\n");
}
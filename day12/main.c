#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 13
#define small 6

int adj[N][N];

int getindex(char* s);

void readinput(FILE *fp) {
    for (int i = 0; i < 25; i++)
    {   
        char s[16];
        fgets(s, 15, fp);
        int src = getindex(strtok(s, "-"));
        int dst = getindex(strtok(NULL, "\n"));
        adj[src][dst] = 1;
        adj[dst][src] = 1;
    }
}

int getindex(char* s) {
    if (strcmp(s, "qi") == 0) return 0;
    else if (strcmp(s, "jt") == 0) return 1;
    else if (strcmp(s, "wb") == 0) return 2;
    else if (strcmp(s, "aa") == 0) return 3;
    else if (strcmp(s, "br") == 0) return 4;
    else if (strcmp(s, "hf") == 0) return 5;
    else if (strcmp(s, "VO") == 0) return 6;
    else if (strcmp(s, "HA") == 0) return 7;
    else if (strcmp(s, "UD") == 0) return 8;
    else if (strcmp(s, "TF") == 0) return 9;
    else if (strcmp(s, "KX") == 0) return 10;
    else if (strcmp(s, "start") == 0) return 11;
    else if (strcmp(s, "end") == 0) return 12;  
}

int* dfs(){
    int visited[N];
    int stack[N];
    int sp = 0;
    stack[sp] = 11;
    while (sp > 0) {
        
    }
    visited[11] = 1;
    for (int i = 0; i < N; i++)
    {
        if (adj[11][i] == 1){
            sp++;
            stack[sp] = i;
        }       
    }

}

int main(int argc, char *argv[])
{
    FILE *fp = fopen("input.txt", "r");
    
    readinput(fp);

    fclose(fp);
    return 0;
}
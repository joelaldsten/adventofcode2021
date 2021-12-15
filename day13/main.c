#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define folds  2
#define nbrpoints  18

typedef struct node {
    int x,y;
    struct node* next;
} node_t;

int paper[20][20];

int foldvalue[folds];

char foldtype[folds];

void insert(node_t **head, int x, int y){
    node_t *new_node = malloc(sizeof(node_t));
    new_node->x = x;
    new_node->y = y;
    new_node->next = (*head);
    (*head) = new_node;
}

void printlist(node_t *node){
    while (node != NULL) {
        printf("(%d,%d) ", node->x, node->y);
        node = node->next;
    }
}

void remove_node(node_t **head, int x, int y) {
    node_t *temp = *head, *prev;

    if (temp != NULL && temp->x == x && temp->y == y) {
        *head = temp->next; 
        free(temp); 
        return;
    }

    while (temp != NULL && (temp->x != x || temp->y != y)) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    
    prev->next = temp->next;

    free(temp);
}

void readinput(FILE *fp, node_t **node) {
    for (int i = 0; i < nbrpoints; i++)
    {   
        char s[16];
        fgets(s, 15, fp);
        int x = atoi(strtok(s, ","));
        int y = atoi(strtok(NULL, "\n"));
        insert(node, x, y);
    }
    fgetc(fp);
    for (int i = 0; i < folds; i++)
    {
        char s[32];
        fgets(s, 31, fp);
        foldtype[i] = strtok(s, "=")[11];
        foldvalue[i] = atoi(strtok(NULL, "\n"));
    }
}


void foldleft(int line, node_t **head) {
    node_t *node = *head;
    while (node != NULL) {
        int x = node->x;
        int y = node->y;
        if(x > line) {                                  //point yo be folded
            int delta = x - line;
            paper[x][y] = 0;
            if(paper[line - delta][y] == 1) remove_node(head, x, y);
            else {
                insert(head, line - delta, y);
                paper[line - delta][y] = 1;
            }
        }
        node = node->next;
    }
}

void foldup(int line, node_t **head) {
    node_t *node = *head;
    while (node != NULL) {
        int x = node->x;
        int y = node->y;
        if(y > line) {                                  //point yo be folded
            int delta = y - line;
            paper[x][y] = 0;
            if(paper[x][line - delta] != 1) {
                printf("problem haha\n");
                insert(head, x, line - delta);
                paper[x][line - delta] = 1;
            }
            remove_node(head, x, y);
        }
        node = node->next;
    }
}

void printpaper(void) {
    for (int i = 0; i < 14; i++)
    {
       for (int j = 0; j < 14; j++)
       {
           printf("%d ", paper[j][i]);
       }
       printf("\n");
    }  
}

int main(int argc, char *argv[]) {
    FILE *fp = fopen("input.txt", "r");

    node_t *head = NULL;

    readinput(fp, &head);
    node_t *node = head;
    while (node != NULL) {
        int x = node->x;
        int y = node->y;
        paper[x][y] = 1;
        node = node->next;
    }
    printlist(head);
    node_t **test = &head;
    remove_node(test, 2,14);
    remove_node(test, 1,10);
    remove_node(test, 10, 12);
    //remove_node(test, 0, 13);
    remove_node(test, 6, 12);
    remove_node(test, 4, 11);
    remove_node(test, 9, 10);
    /*remove_node(test, 0, 14);
    remove_node(test, 0, 13);*/
    remove_node(test, 6, 10);
    printf("\n");
    for (int i = 0; i < 1; i++)
    {
        if(foldtype[i] == 'x') foldleft(foldvalue[i], &head);
        else foldup(foldvalue[i], &head);
    }
    node_t *node1 = head;
    int pointsleft = 0;
    printlist(head);
    while (node1 != NULL) {
        pointsleft++;
        node1 = node1->next;
    }
    printf("points left %d\n", pointsleft);
    fclose(fp);
    return 0;
}
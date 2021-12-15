#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int x,y;
    struct node* next;
} node_t;

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

int main(){
    node_t* head = NULL;

    insert(&head, 10, 20);
    insert(&head, 26, 12);
    insert(&head, 30, 34);
    remove_node(&head, 10, 20);
    remove_node(&head, 26, 12);
    remove_node(&head, -1, 34);
    remove_node(&head, 2, 12);
    remove_node(&head, 2, 12);
    printlist(head);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data; 
    struct node *next;
    struct node *next1;
};
typedef struct node node_t;

node_t * addNewNode(node_t *head, int data_n){
    node_t *newNode = (node_t*)malloc(sizeof(node_t));
    node_t *last = head;
    newNode->data = data_n;
    newNode->next = NULL;
    newNode->next1 = NULL;
    if (head == NULL){
        head = newNode;
    } 
    else{
        while(last->next != NULL){
            last = last->next;
        }    
        last->next = newNode;
    }

    return(head);
}

void printList(node_t *head){
    node_t *last = head;
    while(1){
        printf("%d\n", last->data);
        if (last->next == NULL){
            break;
        }
        last = last->next;
    }
    
}
    
int main(){
    node_t * head;
    node_t * head1;
    head = NULL;
    while(1){
        int tmp;
        scanf("%d", &tmp);
        if (tmp == 0){
            break;
        }
        head = addNewNode(head, tmp);
    }
    while(1){
        int tmp;
        scanf("%d", &tmp);
        if (tmp == 0){
            break;
        }
        head1 = addNewNode(head1, tmp);
    }
    printf("\n");
    printList(head);

}
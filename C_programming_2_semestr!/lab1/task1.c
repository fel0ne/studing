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
    while(last != NULL){
        printf("%d ", last->data);
        last = last->next;
    }
    printf("\n");
}

node_t * linkLists(node_t *head, node_t *head1, int n) {
        node_t *current = head;    
    node_t *current1 = head1;  
    node_t *tail = NULL; 
    node_t *tail_tmp = NULL; 
    current1->next1 = current;
    while (current->next != NULL && current1->next != NULL) {
            current = current->next;
            current1 = current1->next; 
            current->next1 = current1;
    }

    
    while ( tail != head1->next) {
        current1 = head1;
        while ( current1->next != tail) {
                current1 = current1->next; 
                tail_tmp = current1;
        }
        tail=tail_tmp;
        current1 = head1;
        while(current1->next != tail){
            current1 = current1->next;
        }
        tail->next = current1;
    }
    head1->next = NULL;

    return(head);
}


void reverseList(node_t **head) {
    node_t *prev, *curr, *next;
    curr=*head;
    prev=NULL;
    while (curr!=NULL) {
        next=curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head=prev;
}

void navigateList(node_t *S) {
    int reg = 0;
    node_t *current = S;
    char input;
    
    while(1){
        printf("текущий элемент: %d \n", current->data);
        scanf(" %c", &input);
        if (input == '6'){
            if((current->next != NULL) && (reg == 0)){
                current = current->next;
            }
            else{
                printf("передвежение вправо не возможно(вернутся в начало R, enter пропустить)\n ");
                char tmp;
                scanf(" %c", &tmp);
                if((tmp =='R')|| (tmp == 'r')){
                    current = S;
                }
                else if((tmp == 'q')||(tmp == 'Q')){
                        break;
                }
                else{
                    continue;
                }
            }
        }
        else if (input == '4'){
            if((current->next != NULL) && (reg == 1)){
                current = current->next;
            }
            else{
                printf("передвежение влево не возможно(вернутся в начало R, enter пропустить) \n");
                char tmp;
                scanf(" %c", &tmp);
                if((tmp =='R')|| (tmp == 'r')){
                    current = S;
                }
                else if((tmp == 'q')||(tmp == 'Q')){
                        break;
                }
                else{
                    continue;
                }
            }
        }
        else if (input == '2'){
            if((current->next1 != NULL) && (reg == 0)){
                current = current->next1;
                reg = 1;
            }
            else{
                printf("передвежение вниз не возможно(вернутся в начало R, enter пропустить) \n");
                char tmp;
                scanf(" %c", &tmp);
                if((tmp =='R')|| (tmp == 'r')){
                    current = S;
                }
                else if((tmp == 'q')||(tmp == 'Q')){
                        break;
                }
                else{
                    continue;
                }
            }
        }
        else if (input == '8'){
            if((current->next1 != NULL) && (reg == 1)){
                current = current->next1;
                reg = 0;
            }
            else{
                printf("передвежение вверх не возможно(вернутся в начало R, q выйти)\n ");
                char tmp;
                scanf(" %c", &tmp);
                if((tmp =='R')|| (tmp == 'r')){
                    current = S;
                }
                else if((tmp == 'q')||(tmp == 'Q')){
                        break;
                }
                else{
                    continue;
                }
            }
        }
        //printf("текущий элемент: %d \n", current->data);
    }

}

int main(){
    node_t *head = NULL;
    node_t *head1 = NULL;
    node_t *S;
    int counter = 0;  
    int counter1 = 0;

    printf("Введите элементы первого списка (0 для завершения):\n");
    while(1){
        
        int tmp;
        scanf("%d", &tmp);
        if (tmp == 0){
            break;
        }
        head = addNewNode(head, tmp);
        counter++;
    }

    printf("Введите элементы второго списка (0 для завершения):\n");
    while(1){
        int tmp;
        int counter1 = 0;
        scanf("%d", &tmp);
        if (tmp == 0){
            break;
        }
        head1 = addNewNode(head1, tmp);
        counter1++;
    }

    S = head;  // Указатель S на начало первого списка

    printf("\nПервый список: ");
    printList(head);
    printf("Второй список: ");
    printList(head1);
    //reverseList(&head1);

    S = linkLists(head, head1, counter);

    printf("\nСписки связаны.\n");

    
    // printf("\nПервый список: ");
    // printList(head);
    // printf("Второй список: ");
    // printList(head1);

    navigateList(S);

    return 0;
}
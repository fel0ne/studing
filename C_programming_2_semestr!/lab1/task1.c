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
    node_t *current = head;    // Upper list (e.g., a1, a3, a(n-1))
    node_t *current1 = head1;  // Lower list (e.g., a2, a4, a(n))
    current1->next1 = current;
    while (current->next != NULL || current1->next != NULL) {
            current1 = current1->next; 
            current = current->next; 
            

            current->next1 = current1;
    }

    return(head);
}

void navigateList(node_t *S) {
    node_t *head_tmp = S;
    node_t *current = S;
    char input;
    while (1) {
        printf("Текущее значение: %d\n", current->data);
        printf("Введите команду (D/6 - вправо, W/8 - вверх/вниз, Q - выход): ");
        scanf(" %c", &input);
        if (input == 'D' || input == '6') { 
            if (current->next != NULL) {
                current = current->next;
            } else {
                printf("Достигнут конец списка.\n");
            }
        } else if (input == 'A' || input == '4') {
            printf("Невозможно переместиться влево\n");
        } else if (input == 'W' || input == '8') {
            if (current->next1 != NULL) {
                current = current->next1;
            } else {
                printf("Нет связанного элемента в этом направлении.\n");
            }
        } else if (input == 'S' || input == '2') {
            printf("Невозможно переместиться вниз\n");
        } else if (input == 'Q' || input == 'q') {
            break;
        } else {
            printf("Неверная команда. Попробуйте снова.\n");
        }
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

    S = linkLists(head, head1, counter);

    printf("\nСписки связаны.\n");

    
    printf("\nПервый список: ");
    printList(head);
    printf("Второй список: ");
    printList(head1);

    navigateList(S);

    return 0;
}
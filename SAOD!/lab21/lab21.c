#include <stdio.h>
#include <stdlib.h>
struct tLE {
    struct tLE * next;
    int data;

}typedef tLE;

struct tLE* fill_stack_inc(tLE * head, int n) { 
    
    tLE* p = NULL;

    for(int i = n; i >= 1; i--) {  
            p = malloc(sizeof(struct tLE));      
            p->data = i;
            p-> next = head;
            head = p;
    }
    return (p);
}

void print_list(struct tLE* head) {
    while (head->next == NULL){
        printf("%d ", head->data);
        head = head->next;

    }
    printf("\n");
}
int main(){
    tLE * head;
    head->next = NULL;
    head = fill_stack_inc(head, 5);
    print_list(head);
}
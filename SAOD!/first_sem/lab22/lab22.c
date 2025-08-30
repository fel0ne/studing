#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct tLE {
    struct tLE * next;
    int data;
} tLE; 

typedef struct queue {
    tLE  * head;
    tLE  * tail;
} queue; 

tLE* fill_stack_inc(tLE * head, int n) {
    int i;
    tLE *p; 
    for (i=n-1; i>=0; i--) {
        p = (tLE *)malloc(sizeof(tLE)); 
        if (p == NULL) { 
            perror("Ошибка выделения памяти");
            return NULL; 
        }
        p->data = i;
        p->next = head; 
        head = p;      
    }
    return head; 
}

tLE* fill_stack_dec(tLE * head, int n) {
    int i;
    tLE *p; 
    for (i=0; i<n; i++) {
        p = (tLE *)malloc(sizeof(tLE)); 
        if (p == NULL) { 
            perror("Ошибка выделения памяти");
            return NULL; 
        }
        p->data = i;
        p->next = head;
        head = p;
    }
    return head;
}

tLE* fill_stack_rand(tLE * head, int n) {
    int i;
    tLE *p; 
    for (i=0; i<n; i++) {
        p = (tLE *)malloc(sizeof(tLE)); 
        if (p == NULL) { 
            perror("Ошибка выделения памяти");
            return NULL; 
        }
        p->data = rand()%1000;
        p->next = head;
        head = p;
    }
    return head;
}

void fill_queue_inc(queue *q, int n) {
    if (q == NULL) return;

    for (int i = 0; i < n; i++) {
        tLE *p = (tLE*)malloc(sizeof(tLE));
        if (p == NULL) {
            perror("Ошибка выделения памяти");
            return;
        }
        p->data = i;
        p->next = NULL;

        if (q->head == NULL) {
            q->head = q->tail = p;
        } else {
            q->tail->next = p;
            q->tail = p;
        }
    }
}


void fill_queue_dec(queue *q, int n) {
    if (q == NULL) return;

    for (int i = n-1; i >= 0; i--) {
        tLE *p = (tLE*)malloc(sizeof(tLE));
        if (p == NULL) {
            perror("Ошибка выделения памяти");
            return;
        }
        p->data = i;
        p->next = NULL;

        if (q->head == NULL) {
            q->head = q->tail = p;
        } else {
            q->tail->next = p;
            q->tail = p;
        }
    }
}

void fill_queue_rand(queue *q, int n) {
    if (q == NULL) return;

    for (int i = n-1; i >= 0; i--) {
        tLE *p = (tLE*)malloc(sizeof(tLE));
        if (p == NULL) {
            perror("Ошибка выделения памяти");
            return;
        }
        p->data = rand()%1000;
        p->next = NULL;

        if (q->head == NULL) {
            q->head = q->tail = p;
        } else {
            q->tail->next = p;
            q->tail = p;
        }
    }
}



void print_list(tLE* head) {
    while (head != NULL){
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void free_list(tLE* head) {
    tLE* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void clear_list(tLE** head) {
    tLE* current = *head;
    tLE* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next; 
    }

    *head = NULL;
}

void clear_queue(queue *q) {
    tLE *current = q->head;
    tLE *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    q->head = q->tail = NULL;
}

void calculate_checksum(tLE * head) {
    int sum = 0;
    tLE* current = head;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    printf("%d",sum);
}

int count_series(tLE* head) {
    if (head == NULL) return 0; // Пустой список — 0 серий
    
    int count = 1; // Минимум 1 серия (даже если 1 элемент)
    tLE* current = head->next;
    tLE* prev = head;

    while (current != NULL) {
        // Если текущий элемент НЕ больше предыдущего — новая серия
        if (current->data <= prev->data) {
            count++;
        }
        prev = current;
        current = current->next;
    }
    return count;
}

int merge_sort(){
    
}

int main(){
    srand(time(NULL));
    tLE * head;
    head = NULL;


    return 0; 
}
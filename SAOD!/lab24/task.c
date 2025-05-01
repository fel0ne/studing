#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int M_f = 0;

typedef struct tLE {
    struct tLE *next;
    union {
        int data;
        unsigned char digit[sizeof(int)];
    };
} tLE;

typedef struct tLEc {
    struct tLEc *next;  // Исправлен тип указателя
    union {
        int data;
        unsigned char digit[sizeof(short)];
    };
} tLEc;

typedef struct queue {
    tLE *head;
    tLE *tail;
} queue;

typedef struct queuec {
    tLEc *head;
    tLEc *tail;
} queuec;

// Инициализация очередей
void init_queue(queue *q) {
    q->head = q->tail = NULL;
}

void init_queuec(queuec *q) {
    q->head = q->tail = NULL;
}

// Функции заполнения для int
void fill_queue_dec(queue *q, int n) {
    for (int i = n-1; i >= 0; i--) {
        tLE *p = (tLE*)malloc(sizeof(tLE));
        p->data = i;
        p->next = NULL;
        if (!q->head) q->head = q->tail = p;
        else q->tail->next = p, q->tail = p;
    }
}

void fill_queue_rand(queue *q, int n) {
    for (int i = 0; i < n; i++) {
        tLE *p = (tLE*)malloc(sizeof(tLE));
        p->data = rand()%1000;
        p->next = NULL;
        if (!q->head) q->head = q->tail = p;
        else q->tail->next = p, q->tail = p;
    }
}

void fill_queue_inc(queue *q, int n) {
    for (int i = 0; i < n; i++) {
        tLE *p = (tLE*)malloc(sizeof(tLE));
        p->data = i;
        p->next = NULL;
        if (!q->head) q->head = q->tail = p;
        else q->tail->next = p, q->tail = p;
    }
}

// Функции заполнения для short
void fill_queue_decc(queuec *q, int n) {
    for (int i = n-1; i >= 0; i--) {
        tLEc *p = (tLEc*)malloc(sizeof(tLEc));
        p->data = i;
        p->next = NULL;
        if (!q->head) q->head = q->tail = p;
        else q->tail->next = p, q->tail = p;
    }
}

void fill_queue_randc(queuec *q, int n) {
    for (int i = 0; i < n; i++) {
        tLEc *p = (tLEc*)malloc(sizeof(tLEc));
        p->data = rand()%1000;
        p->next = NULL;
        if (!q->head) q->head = q->tail = p;
        else q->tail->next = p, q->tail = p;
    }
}

void fill_queue_incc(queuec *q, int n) {
    for (int i = 0; i < n; i++) {
        tLEc *p = (tLEc*)malloc(sizeof(tLEc));
        p->data = i;
        p->next = NULL;
        if (!q->head) q->head = q->tail = p;
        else q->tail->next = p, q->tail = p;
    }
}

// Очистка памяти
void clear_queue(queue *q) {
    tLE *current = q->head;
    while (current) {
        tLE *next = current->next;
        free(current);
        current = next;
    }
    q->head = q->tail = NULL;
}

void clear_queuec(queuec *q) {
    tLEc *current = q->head;
    while (current) {
        tLEc *next = current->next;
        free(current);
        current = next;
    }
    q->head = q->tail = NULL;
}

// Сортировка для int
void DigitalSort(tLE **head, tLE **tail) {
    int d, i, j, l = sizeof(int);
    queue q[256];
    
    for (j = l-1; j >= 0; j--) {
        for (i = 0; i < 256; i++) 
            q[i].tail = (tLE*)&q[i].head;
        
        tLE *p = *head;
        int k = sizeof(int)-1-j;
        
        while (p) {
            d = p->digit[k];
            q[d].tail->next = p;
            q[d].tail = p;
            p = p->next;
            M_f++;
        }
        p = (tLE*)head;
        for (i = 0; i < 256; i++) {
            if (q[i].tail != (tLE*)&q[i].head) {
                p->next = q[i].head;
                p = q[i].tail;
            }
        }
        p->next = NULL;
    }
}

// Сортировка для short
void DigitalSortc(tLEc **head, tLEc **tail) {
    int d, i, j, l = sizeof(short);
    queuec q[256];
    
    for (j = l-1; j >= 0; j--) {
        for (i = 0; i < 256; i++) 
            q[i].tail = (tLEc*)&q[i].head;
        
        tLEc *p = *head;
        int k = sizeof(short)-1-j;
        
        while (p) {
            d = p->digit[k];
            q[d].tail->next = p;
            q[d].tail = p;
            p = p->next;
            M_f++;
        }
        
        p = (tLEc*)head;
        for (i = 0; i < 256; i++) {
            if (q[i].tail != (tLEc*)&q[i].head) {
                p->next = q[i].head;
                p = q[i].tail;
            }
        }
        p->next = NULL;
    }
}

int main() {
    srand(time(NULL));
    const int sizes[] = {100, 200, 300, 400, 500};

    // Для int (4 байта)
    printf("Трудоемкость цифровой сортировки (int)\n");
    printf("| %-4s | %-13s | %-8s | %-8s | %-8s |\n", 
           "N", "Теория", "Убыв.", "Случ.", "Возр.");
    printf("|------|---------------|---------|---------|---------|\n");
    
    for (int i = 0; i < 5; i++) {
        int N = sizes[i];
        printf("| %-4d | %-13d |", N, sizeof(int)*N);
        
        queue q; init_queue(&q);
        
        fill_queue_dec(&q, N); M_f = 0;
        DigitalSort(&q.head, &q.tail);
        printf(" %-7d |", M_f);
        clear_queue(&q);
        
        fill_queue_rand(&q, N); M_f = 0;
        DigitalSort(&q.head, &q.tail);
        printf(" %-7d |", M_f);
        clear_queue(&q);
        
        fill_queue_inc(&q, N); M_f = 0;
        DigitalSort(&q.head, &q.tail);
        printf(" %-7d |\n", M_f);
        clear_queue(&q);
    }

    // Для short (2 байта)
    printf("\nТрудоемкость цифровой сортировки (short)\n");
    printf("| %-4s | %-13s | %-8s | %-8s | %-8s |\n", 
           "N", "Теория", "Убыв.", "Случ.", "Возр.");
    printf("|------|---------------|---------|---------|---------|\n");
    
    for (int i = 0; i < 5; i++) {
        int N = sizes[i];
        printf("| %-4d | %-13d |", N, sizeof(short)*N);
        
        queuec q; init_queuec(&q);
        
        fill_queue_decc(&q, N); M_f = 0;
        DigitalSortc(&q.head, &q.tail);
        printf(" %-7d |", M_f);
        clear_queuec(&q);
        
        fill_queue_randc(&q, N); M_f = 0;
        DigitalSortc(&q.head, &q.tail);
        printf(" %-7d |", M_f);
        clear_queuec(&q);
        
        fill_queue_incc(&q, N); M_f = 0;
        DigitalSortc(&q.head, &q.tail);
        printf(" %-7d |\n", M_f);
        clear_queuec(&q);
    }

    return 0;
}
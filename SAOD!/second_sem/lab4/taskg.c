#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 15

int A[N];
typedef struct Node {
    int data;               
    struct Node *Left, *Right;
} Node;

struct Vertex{
    int Data;
    struct Vertex *Left;
    struct Vertex *Right;
};
typedef struct Vertex Vertex; 

Vertex *root = NULL;

void addRight(Vertex * current, int Data){
    current->Right = (Vertex*)malloc(sizeof(Vertex));
    current->Right->Data = Data;
    current->Right->Right = NULL;
    current->Right->Left = NULL;
}

void addLeft(Vertex * current, int Data){
    current->Left = (Vertex*)malloc(sizeof(Vertex));
    current->Left->Data = Data;
    current->Left->Right = NULL;
    current->Left->Left = NULL;
}

void obhod_root_Left_Right(Vertex *current){
    if(current != NULL){
        printf("%d ", current->Data);
        obhod_root_Left_Right(current->Left);
        obhod_root_Left_Right(current->Right);
    }
}

void obhod_Left_root_Right(Vertex *current){
    if(current != NULL){
        obhod_Left_root_Right(current->Left);
        printf("%d ", current->Data);
        obhod_Left_root_Right(current->Right);
    }
}

void obhod_Left_Right_root(Vertex *current){
    if(current != NULL){
        obhod_Left_Right_root(current->Left);
        obhod_Left_Right_root(current->Right);
        printf("%d ", current->Data);
    }
}

int size(Vertex *current){
    int n;
    if(current == NULL){
        n = 0;
    }
    else{
        n = 1 + size(current->Left) + size(current->Right);
    }
    return(n);
}

int treeSum(Vertex *current){
    int s;
    if(current == 0){
        s = 0;
    }
    else{
        s = current->Data + treeSum(current->Left)+ treeSum(current->Right);
    }
    return(s);
}

int max(int a, int b){
    if(a > b){
        return(a);
    }
    else{
        return(b);
    }
}

int height(Vertex *current){
    int h;
    if (current == NULL){
        h = 0;
    }
    else{
        h = 1 + max(height(current->Left), height(current->Right));
    }
    return(h);
}

int SLW(Vertex *current, int L){
    int s;
    if (current == NULL){
        s = 0;
    }
    else{
        s = L + SLW(current->Left,L+1) + SLW(current->Right,L+1);
    }
    return(s);
}

float heightSred(Vertex *current){
    float hs = (float)SLW(current,1)/size(current);
    return(hs);
}

int counter = 1;

Vertex * ISDP (int L, int R) 
{
    if (L>R) return NULL;
    else {
        int m = (L + R) / 2;
        Vertex *p = (Vertex*)malloc(sizeof(Vertex)); 
        p->Data = A[m];
        p->Left = ISDP(L, m - 1);
        p->Right = ISDP(m + 1, R);
        return p;
    }
}

int recSDP(int data, Vertex* &p) 
{
    if (!p) {
        p = new Vertex;
        p->Data = data;
        p->Left = NULL;
        p->Right = NULL;
        return 1;
    } 
    else if (data < p->Data) {
        return recSDP(data, p->Left);
    }
    else if (data > p->Data) {
        return recSDP(data, p->Right);
    }
    else {
        return 0; // дубликат
    }
}

int SDP(int data, Vertex*&point) 
{
    Vertex **p = &point;

    while (*p) {
        if (data < (*p)->Data) {
            p = &((*p)->Left);
        }
        else if (data > (*p)->Data) {
            p = &((*p)->Right);
        }
        else break;
    }

    if (*p == NULL) {
        *p = new Vertex;
        (*p)->Data = data;
        (*p)->Left = NULL;
        (*p)->Right = NULL;
    }

    return 0;
}

void fillTreeLevelOrder(Vertex *root, int *values, int size) {
    if (root == NULL || size == 0) return;
    
    Vertex **queue = (Vertex**)malloc(size * sizeof(Vertex*));
    int front = 0, rear = 0;
    int index = 0;
    
    queue[rear++] = root;
    
    while (front < rear && index < size) {
        Vertex *current = queue[front++];
        
        current->Data = values[index+1];
        index =index+1;
        
        if (current->Left != NULL) {
            queue[rear++] = current->Left;
        }
        if (current->Right != NULL) {
            queue[rear++] = current->Right;
        }
    }
    
    free(queue);
}

void delSDP(Vertex *&Root, int point){
    Vertex **p = &Root;
    Vertex *S;
    Vertex *r;

    while((*p)!=NULL)                 
    {
        if(point < ((*p)->Data)){
            p=&((*p)->Left);
        }else{
            if(point>((*p)->Data)){
                p=&((*p)->Right);
            }else break;
        }
    }

    if((*p)!=NULL){
        Vertex *q=(*p);
        if(q->Left==NULL) {
            (*p)=q->Right;
        }else{
            if(q->Right==NULL){
                (*p)=q->Left;
            }else{                           
                r = q->Left; S=q;

                if(r->Right == NULL){
                    r->Right=q->Right;
                    (*p)=r;
                }else{
                    while(r->Right!=NULL){
                        S=r; r=r->Right;
                    }
                    S->Right=r->Left;
                    r->Left=q->Left;
                    r->Right=q->Right;
                    (*p)=r;
                }
            }
        }
        free(q);
    }
}

// Функция для печати дерева в виде горизонтальной структуры
void printTree(Vertex *root, int space = 0, int gap = 5) {
    if (root == NULL) return;
    
    space += gap;
    
    printTree(root->Right, space);
    
    printf("\n");
    for (int i = gap; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->Data);
    
    printTree(root->Left, space);
}

// Функция для печати дерева в виде скобочной структуры
void printTreeBracket(Vertex *root) {
    if (root == NULL) {
        printf("null");
        return;
    }
    
    printf("%d", root->Data);
    
    if (root->Left != NULL || root->Right != NULL) {
        printf("(");
        printTreeBracket(root->Left);
        printf(",");
        printTreeBracket(root->Right);
        printf(")");
    }
}

int main(){
    srand(time(NULL));
    // Инициализация массивов
    
    for (int i = 0; i < N; i++) {
        int value;
        bool duplicate;
        do {
            duplicate = false;
            value = rand() % 2000;
            // Проверка на дубликат
            for (int j = 0; j < i; j++) {
                if (A[j] == value) {
                    duplicate = true;
                    break;
                }
            }
        } while (duplicate);
        A[i] = value;
    }
    
    // Выводим исходный массив
    printf("Исходный массив: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n\n");

    root = NULL; 
    for (int i = 0; i < N; i++) {
        SDP(A[i], root);
    }
    
    printf("Исходное дерево:\n");
    printTreeBracket(root);
    printf("\n\n");
    printTree(root);
    printf("\n");

    int tmp;
    for(int i = 0; i < 10; i++) {
        printf("\n=== Удаление %d ===\n", i + 1);
        
        if (root == NULL) {
            printf("Дерево пустое!\n");
            break;
        }
        
        printf("Введите значение для удаления: ");
        scanf("%d", &tmp);
        
        printf("Удаляем значение %d\n", tmp);
        delSDP(root, tmp);
        
        printf("Дерево после удаления:\n");
        printTreeBracket(root);
        printf("\n\n");
        printTree(root);
        printf("\n");
        
        printf("Прямой обход: ");
        obhod_root_Left_Right(root);
        printf("\n");
        
        printf("Центральный обход: ");
        obhod_Left_root_Right(root);
        printf("\n");
        
        printf("Обратный обход: ");
        obhod_Left_Right_root(root);
        printf("\n");
        
        printf("Размер дерева: %d\n", size(root));
        printf("Высота дерева: %d\n", height(root));
        printf("\n");
    }

    return 0;
}
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100

int A[N];
typedef struct Node {
    int data;               
    struct Node *left, *right;
} Node;

struct Vertex{
    int Data;
    struct Vertex *Left;
    struct Vertex *Right;
};
typedef struct Vertex Vertex; 

Vertex *root1 = NULL, *root2 = NULL, *root3=NULL;



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

void obhod_root_left_right(Vertex *current){
    if(current != NULL){
        printf("%d ", current->Data);
        obhod_root_left_right(current->Left);
        obhod_root_left_right(current->Right);
    }

}

void obhod_left_root_right(Vertex *current){
    if(current != NULL){
        obhod_left_root_right(current->Left);
        printf("%d ", current->Data);
        obhod_left_root_right(current->Right);
    }

}

void obhod_left_right_root(Vertex *current){
    if(current != NULL){
        obhod_left_right_root(current->Left);
        obhod_left_right_root(current->Right);
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
    

    counter = 1;
    root1 = ISDP(0, N -1);
    
   
    
    // Создание деревьев
    root2 = NULL; 
    for (int i = 0; i < N; i++) {
        SDP(A[i], root2);
    }
    // for (int i = 0; i < N; i++) {
    //     int value;
    //     bool duplicate;
    //     do {
    //     duplicate = false;
    //     value = rand() % 2000;
    //     // Проверка на дубликат
    //     for (int j = 0; j < i; j++) {
    //         if (A[j] == value) {
    //             duplicate = true;
    //             break;
    //         }
    //     }
    //     } while (duplicate);
    //     A[i] = value;
    // }
    root3 = NULL; 
    for (int i = 0; i < N; i++) {
        
        recSDP(A[i], root3);
    }

  
    printf("Обход ИСДП (лев-прав-корень): ");
    obhod_left_right_root(root1);
    printf("\n---------------------------------\n");
    
    printf("Обход СДП1 (лев-корень-прав): ");
    obhod_left_root_right(root2);
    printf("\n---------------------------------\n");
    
    printf("Обход СДП2 (лев-корень-прав): ");
    obhod_left_root_right(root3);
    printf("\n---------------------------------\n");
    
    printf("+------+----------+----------------+----------+----------------+\n");
    printf("|%6s|  Размер  |  Контр. сумма  |  Высота  |  Сред. высота  |\n", "N=100");
    printf("+------+----------+----------------+----------+----------------+\n");
    printf("| ИСДП |%10d|%16d|%10d|%16.2f|\n", size(root1), treeSum(root1), height(root1), heightSred(root1));
    printf("| СДП1 |%10d|%16d|%10d|%16.2f|\n", size(root2), treeSum(root2), height(root2), heightSred(root2));
    printf("| СДП2 |%10d|%16d|%10d|%16.2f|\n", size(root3), treeSum(root3), height(root3), heightSred(root3));
    printf("+------+----------+----------------+----------+----------------+\n");

    return 0;
}




    
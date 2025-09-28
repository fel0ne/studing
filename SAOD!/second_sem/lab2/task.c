#include <stdio.h>
#include <stdlib.h>
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
    	p->Data = counter;
        counter= counter+1;
		p->Left = ISDP(L, m - 1);
		p->Right = ISDP(m + 1, R);
		return p;
	}
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
    for (int i = 1; i <= N; i++) {
		A[i] = i;
	}	
	int m =  N / 2;
	Vertex * Root = (Vertex*)malloc(sizeof(Vertex));
    Root->Data = A[m];
	Root->Left = ISDP(1, m - 1);
	Root->Right = ISDP(m + 1, N);
    fillTreeLevelOrder(Root,A,100);
    printf("Размер дерева %d\n", size(Root));
    printf("Сумма дерева %d\n", treeSum(Root));
    printf("Высота дерева %d\n", height(Root));
    printf("Средняя высота дерева %f\n", heightSred(Root));
    
    obhod_left_root_right(Root);
    printf("\n");
    //obhod_root_left_right(Root);




    


}
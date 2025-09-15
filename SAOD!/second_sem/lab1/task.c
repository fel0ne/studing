#include <stdio.h>
#include <stdlib.h>

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

int main(){
    Vertex * Root = (Vertex*)malloc(sizeof(Vertex));
    Root->Data = 1;

    addLeft(Root,2); 
    addRight(Root->Left,3);

    addLeft(Root->Left->Right,4);

    addRight(Root->Left->Right->Right,5);
    addRight(Root->Left->Right->Right->Right,6);

     printf("Прямой обход (Root-Left-Right): ");
    obhod_root_left_right(Root);
    printf("\n");

    printf("Обход слева направо (Left-Root-Right): ");
    obhod_left_root_right(Root);
    printf("\n");

    printf("Обратный обход (Left-Right-Root): ");
    obhod_left_right_root(Root);
    printf("\n");

    printf("Размер дерева: ");
    printf("%d", size(Root));
    printf("\n");

    printf("Контрольная сумма: ");
    printf("%d", treeSum(Root));
    printf("\n");

    printf("Высота дерева: ");
    printf("%d", height(Root));
    printf("\n");

    printf("Средняя высота дерева: ");
    printf("%.2f", heightSred(Root));
    printf("\n");


}
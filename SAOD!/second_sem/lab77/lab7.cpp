#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 100
int vr=1;
int hr=1;

int up = 0;
int A[N];
typedef struct Node {
    int data;               
    struct Node *left, *right;
} Node;

struct Vertex{
    int bal;
    int Data;
    struct Vertex *Left;
    struct Vertex *Right;
};
typedef struct Vertex Vertex; 


Vertex *root1 = NULL, *root2 = NULL;

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


void ll(Vertex* &point)
{
	Vertex *current = point->Left;
	point->bal = 0;
	current->bal = 0;
	point->Left = current->Right;
	current->Right = point;
	point = current;
}

void rr(Vertex* &point)
{
	Vertex *current = point->Right;

	point->bal = 0;
	current->bal = 0;
	point->Right = current->Left;
	current->Left = point;
	point = current;
}

void lr(Vertex* &point)
{
	Vertex *current = point->Left;
	Vertex *reva = current->Right;

	if (reva->bal < 0) {
		point->bal = 1;
	}
	else {
		point->bal = 0;
	}

	if (reva->bal > 0) {
		current->bal = -1;
	}
	else {
		current->bal = 0;
	}
	reva->bal = 0;
	current->Right = reva->Left;
	point->Left = reva->Right;
	reva->Left = current;
	reva->Right = point;
	point = reva;
}

void rl(Vertex* &point)
{
	Vertex *current = point->Right;
	Vertex *reva = current->Left;

	if (reva->bal < 0) {
		point->bal = 1;
	}
	else {
		point->bal = 0;
	}

	if (reva->bal > 0) {
		current->bal = -1;
	}
	else {
		current->bal = 0;
	}
	reva->bal = 0;
	current->Left = reva->Right;
	point->Right = reva->Left;
	reva->Right = current;
	reva->Left = point;
	point = reva;
}

// void LR(Vertex* x)
// {
// 	if (x == NULL) return;
// 	LR(x->Left);
// 	cout << x->data << ' ';
// 	LR(x->Right);
// }

void addAVL(int data, Vertex *&point)
{
	if (point == NULL) {
		point = new Vertex;
		point->Data = data;
		point->bal = 0;
		point->Left = NULL;
		point->Right = NULL;
		up = 1;
	}
	else
		if (point->Data >= data) { 
			addAVL(data, point->Left);
			if (up == 1) {
				if (point->bal > 0) {
					point->bal = 0;
					up = 0;
				}
				else
					if (point->bal == 0) {
						point->bal = -1;
						up = 1;
					}
					else
						if (point->Left->bal < 0) {
							ll(point);
							up = 0;
						}
						else {
							lr(point);
							up = 0;
						}
			}
		}
		else {
			if (point->Data < data) {
				addAVL(data, point->Right);
				if (up == 1) {
					if (point->bal < 0) {
						point->bal = 0;
						up = 0;
					}
					else {
						if (point->bal == 0) {
							point->bal = 1;
							up = 1;
						}
						else {
							if (point->Right->bal > 0) {
								rr(point);
								up = 0;
							}
							else {
								rl(point);
								up = 0;
							}
						}
					}
				}
			}
		}
}




void DBD(int data, Vertex* &p)
{
    if (p == NULL) {
        p = (Vertex*)malloc(sizeof(Vertex));
        p->Data = data;
        p->Left = p->Right = NULL;
        p->bal = 0;
        vr = 1;
        hr = 1;
    }
    else if (p->Data > data) {
        DBD(data, p->Left);
        if (vr == 1) {
            if (p->bal == 0) {
                Vertex *q = p->Left;
                p->Left = q->Right;
                q->Right = p;
                p = q;
                p->bal = 1;
                vr = 0;
                hr = 1;
            }
            else {
                p->bal = 0;
                vr = 0;
                hr = 1;
            }
        }
        else {
            hr = 0;
        }
    }
    else if (p->Data < data) {
        DBD(data, p->Right);
        if (vr == 1) {
            p->bal = 1;
            vr = 0;
            hr = 1;
        }
        else if (hr == 1) {
            if (p->bal > 0) {

                Vertex *q = p->Right;
                p->Right = q->Left;
                q->Left = p;
                p->bal = 0;
                q->bal = 0;
                p = q;
                vr = 1;
                hr = 0;
            }
            else {
                p->bal = 0;
                hr = 0;
            }
        }
    }
    else {
        // Обработка дубликатов (если значение уже существует)
        hr = 0;
        vr = 0;
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
    

    counter = 1;
	for (int i = 0; i < N; i++) {
        addAVL(A[i], root1);
    }
    
    
   
    
    // Создание деревьев
    root2 = NULL; 
    for (int i = 0; i < N; i++) {
        DBD(A[i], root2);
    }
    
  
    

  
    printf("Обход DBD (лев-корень-прав): ");
    obhod_left_root_right(root2);
    printf("\n---------------------------------\n");
    
    printf("Обход АВЛ (лев-корень-прав): ");
    obhod_left_root_right(root1);
    printf("\n---------------------------------\n");
    
    
    printf("\n---------------------------------\n");
    
    printf("+------+----------+----------------+----------+----------------+\n");
    printf("|%6s|  Размер  |  Контр. сумма  |  Высота  |  Сред. высота  |\n", "N=100");
    printf("+------+----------+----------------+----------+----------------+\n"); 
    printf("| ДБД  |%10d|%16d|%10d|%16.2f|\n", size(root2), treeSum(root2), height(root2), heightSred(root2)); 
    printf("| АВЛ  |%10d|%16d|%10d|%16.2f|\n", size(root1), treeSum(root1), height(root1), heightSred(root1));
    printf("+------+----------+----------------+----------+----------------+\n");

    return 0;



    


}
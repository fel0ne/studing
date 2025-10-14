#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
int turn;


int um = 0;

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


Vertex *root = NULL;
Vertex *q = NULL;
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


void BL(Vertex *&p);
void BR(Vertex *&p);
void LL1(Vertex *&p);
void RR1(Vertex *&p);

void BL(Vertex *&p) {
	if (p->bal == -1) {
		p->bal = 0;
		um = 1;
	}
	else
		if (p->bal == 0) {
			p->bal = 1;
			um = 0;
		}
		else
			if (p->bal == 1) 
				if (p->Right->bal >= 0) {
					RR1(p);
				}
				else {
					rl(p);
				}
			
}

void BR(Vertex *&p) {
	if (p->bal == 1) {
		p->bal = 0;
		um = 1;
	}
	else
		if (p->bal == 0) {
			p->bal = -1;
			um = 0;
		}
		else
			if (p->bal == -1) {
				if (p->Left->bal <= 0) {
					LL1(p);
				}
				else {
					lr(p);
				}
			}
}

void LL1(Vertex *&p) {
	turn++;
	q = p->Left;
	if (q->bal == 0) {
		q->bal = 1;
		p->bal = -1;
		um = 0;
	}
	else {
		q->bal = 0;
		p->bal = 0;
	}
	p->Left = q->Right;
	q->Right = p;
	p = q;
}

void RR1(Vertex *&p) {
	turn++;
	q = p->Right;;
	if (q->bal == 0) {
		q->bal = -1;
		p->bal = 1;
		um = 0;
	}
	else {
		q->bal = 0;
		p->bal = 0;
	}
	p->Right = q->Left;
	q->Left = p;
	p = q;
}

void del(Vertex *&r) {
	if (r->Right != NULL) {
		del(r->Right);
		if (um == 1)
			BR(r);
	}
	else {
		q->Data = r->Data;
		q = r;
		r = r->Left;
		um = 1;
	}
}

void DeleteAVL(int x, Vertex*&p) {
	if (p == NULL) {
		return;
	}
	else
		if (x < p->Data) {
			DeleteAVL(x, p->Left);
			if (um == 1) BL(p);
		}
		else 
			if (x > p->Data) {
				DeleteAVL(x, p->Right);
				if (um == 1) BR(p);
			}
			else {
				q = p;
				if (q->Left == NULL) {
					p = q->Right;
					um = 1;
				}
				else
					if (q->Right == NULL) {
						p = q->Left;
						um = 1;
					}
					else {
						del(q->Left);
						if (um == 1)
							BL(p);
					}
				delete(q);
			}
}








int main(){
     srand(time(NULL));
   
    
    for (int i = 0; i < N; i++) {
        int value;
        bool duplicate;
        do {
        duplicate = false;
        value = rand() % 2000;

        for (int j = 0; j < i; j++) {
            if (A[j] == value) {
                duplicate = true;
                break;
            }
        }
        } while (duplicate);
        A[i] = value;
    }
    

  
    root = NULL; 
    for (int i = 0; i < N; i++) {
        addAVL(A[i], root);
    }
    
    //fillTreeLevelOrder(root,A,100);

  

    //obhod_Left_Right_root(root);
    obhod_root_left_right(root);
    printf("\n");
    printf("удалим вершину: ");
    int tmp;
    for(int i =0; i < 10;i++ ){

    scanf("%d", &tmp);

    DeleteAVL(tmp,root);

    //obhod_Left_Right_root(root);
    obhod_root_left_right(root);
    if(i != 9){
    printf("\n");
    printf("удалим вершину: ");
    }
    //obhod_root_Left_Right(root);
    }

    return 0;


    


}
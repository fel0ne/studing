#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


void Fillinc(int * A, int n ){
    for (int i = 0; i < n; i++ ){
        A[i] = i;
    }
}

void PrintMas(int * A, int n){
    for (int i = 0; i < n; i++ ){
        printf("%d",A[i]);
        printf(" ");
    }
} 

void FillDec(int * A, int n ){
    for (int i = 0; i < n; i++ ){
        A[i] = n - i - 1;
    }
}

void FillRand(int * A, int n ){

    for (int i = 0; i < n; i++ ){
        A[i] = rand()%1000;
    }
}

unsigned int CheckSum(int * A, int n){
    unsigned int summ = 0; 
    for (int i = 0; i < n; i++ ){
        summ += A[i];
    }
    return(summ);
}

int RunNumber(int * A, int n){
    int counter = 1;
    for (int i = 1; i < n; i++ ){
        if (A[i] < A[i-1]){
            counter += 1;
        }
    }
    return (counter);

}

int lenght(int n){
    int l = 0;
    while (n > 0){
        l++;
        n = n/10;
    }
    return (l);
}

int sred(int * A, int n){
    unsigned int sum_for_sred = 0;
    for (int i = 1; i < n; i++ ){
        lenght(A[i]);
    }
    printf("среднее для рандомного массива: ");
    printf("%d",sum_for_sred/n);
}


int Bsearch_v1(int *A, int n, int X, int *C) {
    *C = 0;
    int L = 0;
    int R = n - 1;
    int m;
    while (L <= R) {
        m = (L + R) / 2;
        (*C)++; if (A[m] == X) {
            return 1;
        }
        (*C)++;if (A[m] < X) {
            L = m + 1;
        } else {
            R = m - 1;
        }
    }
    return 0; // Элемент не найден
}

int Bsearch_v2(int *A, int n, int X, int *C){
    (*C) = 0;
    int L = 0;
    int R = n-1;
    int m;
    while(L<R){
        m = (L+R)/2;
        (*C)++; if(A[m] < X){
            L = m + 1;
        } 
        else{
            R = m;
        }
    }
    (*C)++;if(A[R] == X){
        return(1);
    }
    else{
        return(0);
    }

}




int main(){
    srand(time(NULL));
    int C;
    int A[7];
    Fillinc(A,7);
    PrintMas(A,7);
    printf("\n");
    int key = 0;
    scanf("%d", &key);
    printf("%d", Bsearch_v1(A,7,key,&C));
    printf("\n");
    
}

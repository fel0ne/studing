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

    int tmp;

    int C1_1;
    int C1_2;
    int C1_3;
    int C1_4;
    int C1_5;
    int C1_6;
    int C1_7;
    int C1_8;
    int C1_9;
    int C1_10;

    int C2_1;
    int C2_2;
    int C2_3;
    int C2_4;
    int C2_5;
    int C2_6;
    int C2_7;
    int C2_8;
    int C2_9;
    int C2_10;

    int A1[100];
    int A2[200];
    int A3[300];
    int A4[400];
    int A5[500];
    int A6[600];
    int A7[700];
    int A8[800];
    int A9[900];
    int A10[1000];

    int key = 0;
    scanf("%d", &key);

    Fillinc(A1,100);
    Fillinc(A2,200);
    Fillinc(A3,300);
    Fillinc(A4,400);
    Fillinc(A5,500);
    Fillinc(A6,600);
    Fillinc(A7,700);
    Fillinc(A8,800);
    Fillinc(A9,900);
    Fillinc(A10,1000);


    tmp = Bsearch_v1(A1,100,key,&C1_1);
    tmp = Bsearch_v1(A2,200,key,&C1_2);
    tmp = Bsearch_v1(A3,300,key,&C1_3);
    tmp = Bsearch_v1(A4,400,key,&C1_4);
    tmp = Bsearch_v1(A5,500,key,&C1_5);
    tmp = Bsearch_v1(A6,600,key,&C1_6);
    tmp = Bsearch_v1(A7,700,key,&C1_7);
    tmp = Bsearch_v1(A8,800,key,&C1_8);
    tmp = Bsearch_v1(A9,900,key,&C1_9);
    tmp = Bsearch_v1(A10,1000,key,&C1_10);

    Fillinc(A1,100);
    Fillinc(A2,200);
    Fillinc(A3,300);
    Fillinc(A4,400);
    Fillinc(A5,500);
    Fillinc(A6,600);
    Fillinc(A7,700);
    Fillinc(A8,800);
    Fillinc(A9,900);
    Fillinc(A10,1000);


    tmp = Bsearch_v2(A1,100,key,&C2_1);
    tmp = Bsearch_v2(A2,200,key,&C2_2);
    tmp = Bsearch_v2(A3,300,key,&C2_3);
    tmp = Bsearch_v2(A4,400,key,&C2_4);
    tmp = Bsearch_v2(A5,500,key,&C2_5);
    tmp = Bsearch_v2(A6,600,key,&C2_6);
    tmp = Bsearch_v2(A7,700,key,&C2_7);
    tmp = Bsearch_v2(A8,800,key,&C2_8);
    tmp = Bsearch_v2(A9,900,key,&C2_9);
    tmp = Bsearch_v2(A10,1000,key,&C2_10);

    printf("----------------------------\n");
    printf("|  N  | Сф      |   Сф     |\n");
    printf("|     | 1 вер.  |   2 вер. |\n");
    printf("|     |         |          |\n");
    printf("----------------------------\n");
    printf("| 100 |   %d    |    %d    |\n", C1_1,C2_1);
    printf("----------------------------\n");
    printf("| 200 |   %d    |    %d    |\n", C1_2,C2_2);
    printf("----------------------------\n");
    printf("| 300 |   %d    |    %d    |\n", C1_3,C2_3);
    printf("----------------------------\n");
    printf("| 400 |   %d    |    %d    |\n", C1_4,C2_4);
    printf("----------------------------\n");
    printf("| 500 |   %d    |    %d    |\n", C1_5,C2_5);
    printf("----------------------------\n");
    printf("| 600 |   %d    |    %d    |\n", C1_6,C2_6);
    printf("----------------------------\n");
    printf("| 700 |   %d    |    %d    |\n", C1_7,C2_7);
    printf("----------------------------\n");
    printf("| 800 |   %d    |    %d    |\n", C1_8,C2_8);
    printf("----------------------------\n");
    printf("| 900 |   %d    |    %d    |\n", C1_9,C2_9);
    printf("----------------------------\n");
    printf("| 1000|   %d    |    %d    |\n", C1_10,C2_10);
    printf("----------------------------\n");

    
   
    
    



}

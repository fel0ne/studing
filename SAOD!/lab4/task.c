#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
        A[i] = rand()%10000;
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

void ShakerSort(int * A, int n, int * M, int * C){
    int L = 0;
    int R = n-1;
    int k = n-1;

    (*M) = 0;
    (*C) = 0;
    do{
        for(int j = R ; j > L ; j--){
            (*C)++;if (A[j]<A[j-1]){
                (*M)++;int tmp = A[j];
                (*M)++;A[j] = A[j-1];
                (*M)++;A[j-1] = tmp;
                k = j;
            }
        }
        L = k;
        for(int j = L ; j < R; j++){
            (*C)++;if (A[j]>A[j+1]){
                (*M)++;int tmp = A[j];
                (*M)++;A[j] = A[j+1];
                (*M)++;A[j+1] = tmp;
                k = j;
            }
        }
        R = k;

    }while(L<R);

}

void insertSort(int * A, int n, int * M, int * C){

    (*M) = 0;
    (*C) = 0;
    for(int i = 1; i < n; i++){
        (*M)++;int t = A[i];
        int j = i-1;
        while(j >= 0 && ((*C)=(*C)+1,t < A[j])){
            (*M)++;A[j+1] = A[j];
            j = j-1;
        }
        (*M)++;A[j+1] = t;
    }

}

void BubbleSort(int * A, int n, int * M, int * C){
    (*M) = 0;
    (*C) = 0;
    for(int i = 0; i < n-1; i++){
        for (int j = n -1; j > i; j--){
            (*C)++;if (A[j]<A[j-1]){
                (*M)++;int tmp = A[j];
                (*M)++;A[j] = A[j-1];
                (*M)++;A[j-1] = tmp;
            }
        }
    }

}

void selectionSort(int * A, int n, int * M, int * C){
    (*M) = 0;
    (*C) = 0;
    for(int i = 0; i < n-1; i++){
        int k = i;//(*M)++;
        for (int j = i+1; j < n; j++){
            (*C)++;if(A[j] < A[k]){
                k = j;//(*M)++;
            }
        }
        int temp = A[i];(*M)++;
        A[i] = A[k];(*M)++;
        A[k] = temp;(*M)++;
    }

}



int main(){



    int M100i,M200i,M300i,M400i,M500i;
    int C100i,C200i,C300i,C400i,C500i;

    int M100d,M200d,M300d,M400d,M500d;
    int C100d,C200d,C300d,C400d,C500d;

    int M100r,M200r,M300r,M400r,M500r;
    int C100r,C200r,C300r,C400r,C500r;
    
    
    int shM100r,shM200r,shM300r,shM400r,shM500r;
    int shC100r,shC200r,shC300r,shC400r,shC500r;

    int sM100r,sM200r,sM300r,sM400r,sM500r;
    int sC100r,sC200r,sC300r,sC400r,sC500r;

    int bM100r,bM200r,bM300r,bM400r,bM500r;
    int bC100r,bC200r,bC300r,bC400r,bC500r;

    int A100[100];
    int A200[200];
    int A300[300];
    int A400[400];
    int A500[500];
    
    FillDec(A100,100);
    PrintMas(A100,100);
    printf("\n");
    insertSort(A100,100,&M100d,&C100d);
    PrintMas(A100,100);
    printf("\n");

    Fillinc(A100,100);
    insertSort(A100,100,&M100i,&C100i);
    Fillinc(A200,200);
    insertSort(A200,200,&M200i,&C200i);
    Fillinc(A300,300);
    insertSort(A300,300,&M300i,&C300i);
    Fillinc(A400,400);
    insertSort(A400,400,&M400i,&C400i);
    Fillinc(A500,500);
    insertSort(A500,500,&M500i,&C500i);

    FillDec(A100,100);
    insertSort(A100,100,&M100d,&C100d);
    FillDec(A200,200);
    insertSort(A200,200,&M200d,&C200d);
    FillDec(A300,300);
    insertSort(A300,300,&M300d,&C300d);
    FillDec(A400,400);
    insertSort(A400,400,&M400d,&C400d);
    FillDec(A500,500);
    insertSort(A500,500,&M500d,&C500d);

    FillRand(A100,100);
    insertSort(A100,100,&M100r,&C100r);
    FillRand(A200,200);
    insertSort(A200,200,&M200r,&C200r);
    FillRand(A300,300);
    insertSort(A300,300,&M300r,&C300r);
    FillRand(A400,400);
    insertSort(A400,400,&M400r,&C400r);
    FillRand(A500,500);
    insertSort(A500,500,&M500r,&C500r);

    FillRand(A100,100);
    ShakerSort(A100,100,&shM100r,&shC100r);
    FillRand(A200,200);
    ShakerSort(A200,200,&shM200r,&shC200r);
    FillRand(A300,300);
    ShakerSort(A300,300,&shM300r,&shC300r);
    FillRand(A400,400);
    ShakerSort(A400,400,&shM400r,&shC400r);
    FillRand(A500,500);
    ShakerSort(A500,500,&shM500r,&shC500r);

    FillRand(A100,100);
    selectionSort(A100,100,&sM100r,&sC100r);
    FillRand(A200,200);
    selectionSort(A200,200,&sM200r,&sC200r);
    FillRand(A300,300);
    selectionSort(A300,300,&sM300r,&sC300r);
    FillRand(A400,400);
    selectionSort(A400,400,&sM400r,&sC400r);
    FillRand(A500,500);
    selectionSort(A500,500,&sM500r,&sC500r);

    

    FillRand(A100,100);
    BubbleSort(A100,100,&bM100r,&bC100r);
    FillRand(A200,200);
    BubbleSort(A200,200,&bM200r,&bC200r);
    FillRand(A300,300);
    BubbleSort(A300,300,&bM300r,&bC300r);
    FillRand(A400,400);
    BubbleSort(A400,400,&bM400r,&bC400r);
    FillRand(A500,500);
    BubbleSort(A500,500,&bM500r,&bC500r);



    printf("---------------------------------------\n");
    printf("|  N  |  M+C    |        Мф+Сф        |\n");
    printf("|     |  Теор.  |----------------------\n");
    printf("|     |         | убыв | возр  | ранд |\n");
    printf("---------------------------------------\n");
    printf("|     |         |      |       |      |\n");
    printf("| 100 |  %d   |%d |  %d  | %d |\n", (100*100 - 100)/4 + 100 -1 + (100*100-100)/4, M100d+C100d,M100i+C100i,M100r+C100r );
    printf("|     |         |      |       |      |\n");
    printf("---------------------------------------\n");
    printf("|     |         |      |       |      |\n");
    printf("| 200 |  %d  |%d |  %d  | %d|\n", (200*200 - 200)/4 + 200 - 1 + (200*200-200)/4, M200d+C200d,M200i+C200i,M200r+C200r);
    printf("|     |         |      |       |      |\n");
    printf("---------------------------------------\n");
    printf("|     |         |      |       |      |\n");
    printf("| 300 |  %d  |%d |  %d  | %d|\n", (300*300 - 300)/4 + 300 -1 + (300*300-300)/4, M300d+C300d,M300i+C300i,M300r+C300r);
    printf("|     |         |      |       |      |\n");
    printf("---------------------------------------\n");
    printf("|     |         |      |       |      |\n");
    printf("| 400 |  %d  |%d| %d  | %d|\n", (400*400 - 400)/4 + 400 - 1 + (400*400-400)/4, M400d+C400d,M400i+C400i,M400r+C400r);
    printf("|     |         |      |       |      |\n");
    printf("---------------------------------------\n");
    printf("|     |         |      |       |      |\n");
    printf("| 500 |  %d |%d| %d  |%d|\n", (500*500 - 500)/4 + 500 - 1 + (500*500-500)/4, M500d+C500d,M500i+C500i,M500r+C500r);
    printf("|     |         |      |       |      |\n");
    printf("---------------------------------------\n");
    

    printf("---------------------------------------\n");
    printf("|  N  |                  Мф+Сф        |\n");
    printf("|     |--------------------------------\n");
    printf("|     | Select  |Bubble|Shaker |insert|\n");
    printf("---------------------------------------\n");
    printf("|     |         |      |       |      |\n");
    printf("| 100 |  %d   |%d |  %d | %d |\n",sM100r+sC100r , bM100r+bC100r,shM100r+shC100r,M100r+C100r );
    printf("|     |         |      |       |      |\n");
    printf("---------------------------------------\n");
    printf("|     |         |      |       |      |\n");
    printf("| 200 |  %d  |%d | %d | %d|\n", sM200r+sC200r, bM200r+bC200r,shM200r+shC200r,M200r+C200r);
    printf("|     |         |      |       |      |\n");
    printf("---------------------------------------\n");
    printf("|     |         |      |       |      |\n");
    printf("| 300 |  %d  |%d| %d | %d|\n", sM300r+sC300r, bM300r+bC300r,shM300r+shC300r,M300r+C300r);
    printf("|     |         |      |       |      |\n");
    printf("---------------------------------------\n");
    printf("|     |         |      |       |      |\n");
    printf("| 400 |  %d  |%d| %d| %d|\n", sM400r+sC400r, bM400r+bC400r,shM400r+shC400r,M400r+C400r);
    printf("|     |         |      |       |      |\n");
    printf("---------------------------------------\n");
    printf("|     |         |      |       |      |\n");
    printf("| 500 |  %d |%d| %d|%d|\n", sM500r+sC500r, bM500r+bC500r,shM500r+shC500r,M500r+C500r);
    printf("|     |         |      |       |      |\n");
    printf("---------------------------------------\n");
    
}
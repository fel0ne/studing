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

void selectionSortMod(int * A, int n, int * M, int * C){
    srand(time(NULL));
    (*M) = 0;
    (*C) = 0;
    for(int i = 0; i < n-1; i++){
        int k = i;//(*M)++;
        for (int j = i+1; j < n; j++){
            (*C)++;if(A[j] < A[k]){
                k = j;//(*M)++;
            }
        }
        if (k != i){
            int temp = A[i];(*M)++;
            A[i] = A[k];(*M)++;
            A[k] = temp;(*M)++;
        }
    }

}


int main(){
    int Md10,Cd10,Md100,Cd100,Mi10,Ci10,Mi100,Ci100,Mr10,Cr10,Mr100,Cr100;
    int Md10m,Cd10m,Md100m,Cd100m,Mi10m,Ci10m,Mi100m,Ci100m,Mr10m,Cr10m,Mr100m,Cr100m;
    //int n;
   // printf("Число n: ");
   // scanf("%d", &n);
    int A[10];
    int A1[100];
    for (int i = 0; i < 10; i++ ){
        A[i] = 1;
    }
    for (int i = 0; i < 100; i++ ){
        A1[i] = 1;
    }
    
    FillDec(A,10);
    PrintMas(A,10);
    printf("\n");
    selectionSort(A,10,&Md10,&Cd10);
    PrintMas(A,10);
    printf("\n");
    printf("\n");
    FillDec(A1,100);
    selectionSort(A1,100,&Md100,&Cd100);
    Fillinc(A,10);
    selectionSort(A,10,&Mi10,&Ci10);
    Fillinc(A1,100);
    selectionSort(A1,100,&Mi100,&Ci100);
    FillRand(A,10);
    selectionSort(A,10,&Mr10,&Cr10);
    FillRand(A1,100);
    selectionSort(A1,100,&Mr100,&Cr100);
    

    FillDec(A,10);
    selectionSortMod(A,10,&Md10m,&Cd10m);
    FillDec(A1,100);
    selectionSortMod(A1,100,&Md100m,&Cd100m);
    Fillinc(A,10);
    selectionSortMod(A,10,&Mi10m,&Ci10m);
    Fillinc(A1,100);
    selectionSortMod(A1,100,&Mi100m,&Ci100m);
    FillRand(A,10);
    selectionSortMod(A,10,&Mr10m,&Cr10m);
    FillRand(A1,100);
    selectionSortMod(A1,100,&Mr100m,&Cr100m);

    
    
    
    



    printf("-------------------------------------------------------------\n");
    printf("|  N  |  M+C    |  Исхoдный Мф+Сф     |  Улучшенный Мф+Сф   |\n");
    printf("-------  Теор.  ---------------------------------------------\n");
    printf("|     |         | убыв | возр  | ранд | убыв | возр  | ранд |\n");
    printf("-------------------------------------------------------------\n");
    printf("|     |         |      |       |      |      |       |      |\n");
    printf("| 10  |    %d   |  %d  |  %d   |  %d  |  %d  |   %d  |  %d  |\n", 3*(10-1)+ (10*10 - 10) / 2, Cd10+Md10, Ci10+Mi10, Cr10+Mr10, Cd10m+Md10m, Ci10m+Mi10m,  Cr10m+Mr10m);
    printf("|     |         |      |       |      |      |       |      |\n");
    printf("-------------------------------------------------------------\n");
    printf("|     |         |      |       |      |      |       |      |\n");
    printf("| 100 |   %d  | %d | %d  | %d | %d | %d  | %d |\n", 3*(100-1)+ (100*100 - 100) / 2, Cd100+Md100, Ci100+Mi100, Cr100+Mr100, Cd100m+Md100m, Ci100m+Mi100m,  Cr100m+Mr100m);
    printf("|     |         |      |       |      |      |       |      |\n");
    printf("-------------------------------------------------------------\n");







}

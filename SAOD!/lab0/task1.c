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


int main(){
    int n;
    printf("Число n: ");
    scanf("%d", &n);

    int A[n];
    for (int i = 0; i < n; i++ ){
        A[i] = 1;
    }

    printf("1.Заполненый массив по возрастанию: ");
    Fillinc(A, n);
    PrintMas(A, n);
    printf("\n");
    printf("Контрольная сумма: ");
    printf("%d", CheckSum(A,n));
    printf("\n");
    printf("Количество серий ");
    printf("%d", RunNumber(A,n));
    printf("\n");

    printf("2.Заполненый массив по убыванию: ");
    FillDec(A, n);
    PrintMas(A, n);
    printf("\n");
    printf("Контрольная сумма: ");
    printf("%d", CheckSum(A,n));
    printf("\n");
    printf("Количество серий ");
    printf("%d", RunNumber(A,n));
    printf("\n");
    
    printf("3.Заполненый массив рандомно: ");
    FillRand(A, n);
    PrintMas(A, n);
    printf("\n");
    printf("Контрольная сумма: ");
    printf("%d", CheckSum(A,n));
    printf("\n");
    printf("Количество серий ");
    printf("%d", RunNumber(A,n));
    printf("\n");
    sred(A,n);
    printf("\n");


}
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

int quickSort(int * A,int L, int R ){
    // L = L-1;
    // R = R-1;
    int Ms = 0;
    int Cs = 0;
    int x = A[L];
    int i = L;
    int j = R; 
    while(i <= j){
        while (Cs++,A[i] < x){
            i = i + 1;
        }
        while (Cs++,A[j] > x){
            j = j - 1;
        }
        if(i <= j){
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            Ms = Ms + 3;
            i = i + 1;
            j = j -1;
        } 
    }

    if(L<j){
        Ms = Ms + quickSort(A,L,j);
    }
    if(i<R){
        Ms = Ms + quickSort(A,i,R);
    }
    return Ms + Cs;
}



void resultTabSort(int ***A) { // Исправленный тип аргумента
    printf("\n");
    printf("   N      |                M + C    фактический         |\n");
    printf("          |      Убыв    |      Случ     |     Возр     |\n");
    printf("-------------------------------------------------------\n");
    for(int i = 0; i < 5; i++){
        int n = (i+1)*100;
        int theoretical = 0; 
        int dec = quickSort(A[0][i],0, n-1); // Убывающий
        int rand = quickSort(A[1][i],0, n-1); // Случайный
        int inc = quickSort(A[2][i],0, n-1); // Возрастающий
        
        printf("  %7d | %12d | %13d | %12d |\n", 
            n,  
            dec, 
            rand, 
            inc
        );
    }
}

int main(){

    srand(time(NULL));
    
    // Инициализация и заполнение массивов
    int A1d[100], A2d[200], A3d[300], A4d[400], A5d[500];
    int A1r[100], A2r[200], A3r[300], A4r[400], A5r[500];
    int A1i[100], A2i[200], A3i[300], A4i[400], A5i[500];

   

    int *ARd[5] = {A1d, A2d, A3d, A4d, A5d};
    int *ARr[5] = {A1r, A2r, A3r, A4r, A5r};
    int *ARi[5] = {A1i, A2i, A3i, A4i, A5i};
    int **AR[3] = {ARd, ARr, ARi};
    
    

    FillDec(A1d, 100); FillDec(A2d, 200); FillDec(A3d, 300); FillDec(A4d, 400); FillDec(A5d, 500);
    FillRand(A1r, 100); FillRand(A2r, 200); FillRand(A3r, 300); FillRand(A4r, 400); FillRand(A5r, 500);
    Fillinc(A1i, 100); Fillinc(A2i, 200); Fillinc(A3i, 300); Fillinc(A4i, 400); Fillinc(A5i, 500);

    //PrintMas(AR[0][0],100);

    resultTabSort(AR);

    //PrintMas(AR[0][0],100);

    
}


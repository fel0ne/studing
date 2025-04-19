#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
int M =0;
int C=0;

int Ms=0;
int Cs=0;

void ResultOld (int n) {
	printf ("\nC(t)=%f, M(t)=%f", 2*n*log2(n)+n+2, n*log2(n)+6.5*n-4);
	printf ("\nC(p)=%d, M(p)=%d, T(p)=%d", C, M, C+M);
}


void Steps(int n, int *steps, int *stepCount) {
    int k = 1;
    *stepCount = 0;
    int counter = 0;

    while (counter < (int)(log2(n))-1) {
        steps[(*stepCount)++] = k;
        k = 2 * k + 1;
        counter++;
    }
}

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



int heapCreateFT(int * A, int L, int R){
    
    int M = 0;
    int C = 0;
    int j;
    M++;
    int x = A[L];
    int i = L;
    while(1){
        j = 2*i+1;
        if (j>R){
            break;
        }
        C++;if((j < R) && (A[j + 1] > A[j])){
            j = j + 1;

        }
        C++;if(x >= A[j]){
            break;
        }
        A[i] = A[j];
        M++;
        i = j;
    }
    A[i] = x;
    M++;


    return(M+C);

}

int heapCreate(int * A, int L, int R){
    //L = L+1;
    //int M = 0;
    //int C = 0;
    int j ;
    Ms++;
    int x = A[L];
    int i = L;
    while(1){
        j = 2*i + 1 ;
        if (j>R){
            break;
        }
        Cs++;if((j  < R) && (A[j + 1] > A[j])){
            j = j + 1;

        }
        Cs++;if(x >= A[j]){
            break;
        }
        A[i] = A[j];
        Ms++;
        i = j;
    }
    A[i] = x;
    Ms++;


    return(Ms+Cs);

}

int heapSort(int * A,int n ){
    Ms = 0;
    Cs = 0;
    int L = (n / 2) ; 
    int R = n ;

 
    while (L >= 0) {
        heapCreate(A, L, R);
        L--;
    }

    while (R > 0) {
 
        int temp = A[R];
        A[R] = A[0];
        A[0] = temp;
        Ms += 3;

        R--;
        heapCreate(A, 0, R);
    }

    return Ms + Cs;
}


void resultTabCreate(int ***A) { // Исправленный тип аргумента
    printf("\n");
    printf("   N    |     M + C     |              M + C   фактический       |\n");
    printf("        | теоретический |     Убыв    |     Случ    |    Возр    |\n");
    printf("------------------------------------------------------------------\n");
    for(int i = 0; i < 5; i++){
        int n = (i+1)*100;
        int theoretical = log2((i+1)*100)+2 + 2*log2((i+1)*100); // Пример формулы
        int dec = heapCreateFT(A[0][i], 0, n-1); // Убывающий
        int rand = heapCreateFT(A[1][i], 0, n-1); // Случайный
        int inc = heapCreateFT(A[2][i], 0, n-1); // Возрастающий
        
        printf("  %5d | %12.0d | %10d | %10d | %10d |\n", 
            n, 
            theoretical, 
            dec, 
            rand, 
            inc
        );
    }
}

void resultTabSort(int ***A) { // Исправленный тип аргумента
    printf("\n");
    printf("   N    |     M + C     |              M + C   фактический       |\n");
    printf("        | теоретический |     Убыв    |     Случ    |    Возр    |\n");
    printf("------------------------------------------------------------------\n");
    for(int i = 0; i < 5; i++){
        int n = (i+1)*100;
        int theoretical = 2*n*log2((i+1)*100)+2 + n*log2((i+1)*100)+6.5*n-4; // Пример формулы
        int dec = heapSort(A[0][i], n-1); // Убывающий
        int rand = heapSort(A[1][i], n-1); // Случайный
        int inc = heapSort(A[2][i], n-1); // Возрастающий
        
        printf("  %5d | %12.0d| %10d | %10d | %10d |\n", 
            n, 
            theoretical, 
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

    FillDec(A1d, 100); FillDec(A2d, 200); FillDec(A3d, 300); FillDec(A4d, 400); FillDec(A5d, 500);
    FillRand(A1r, 100); FillRand(A2r, 200); FillRand(A3r, 300); FillRand(A4r, 400); FillRand(A5r, 500);
    Fillinc(A1i, 100); Fillinc(A2i, 200); Fillinc(A3i, 300); Fillinc(A4i, 400); Fillinc(A5i, 500);

    int *ARd[5] = {A1d, A2d, A3d, A4d, A5d};
    int *ARr[5] = {A1r, A2r, A3r, A4r, A5r};
    int *ARi[5] = {A1i, A2i, A3i, A4i, A5i};
    int **AR[3] = {ARd, ARr, ARi};
    
    
    resultTabCreate(AR);
    

    FillDec(A1d, 100); FillDec(A2d, 200); FillDec(A3d, 300); FillDec(A4d, 400); FillDec(A5d, 500);
    FillRand(A1r, 100); FillRand(A2r, 200); FillRand(A3r, 300); FillRand(A4r, 400); FillRand(A5r, 500);
    Fillinc(A1i, 100); Fillinc(A2i, 200); Fillinc(A3i, 300); Fillinc(A4i, 400); Fillinc(A5i, 500);

    PrintMas(AR[0][0],100);

    resultTabSort(AR);

    PrintMas(AR[0][0],100);

    
}


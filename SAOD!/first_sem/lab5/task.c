#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
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

void shellSort(int * A, int n, int * M, int * C){

    (*M) = 0;
    (*C) = 0;
    int steps[100];
    int stepCount;
    Steps(n, steps, &stepCount);
    
    for (int tmp = stepCount - 1; tmp >= 0; tmp--) {
        int k = steps[tmp];

        for (int i = k; i < n; i++) {
            (*M)++;
            int t = A[i];
            int j = i - k;

            while (j >= 0 && ((*C)++,t < A[j])) {
                (*M)++;
                A[j + k] = A[j];
                j = j - k;
            }

            (*M)++;
            A[j + k] = t;
        }
    }

}




int main(){


    srand(time(NULL));
    int iM100r,iM200r,iM300r,iM400r,iM500r;
    int iC100r,iC200r,iC300r,iC400r,iC500r;

    int sM100r,sM200r,sM300r,sM400r,sM500r;
    int sC100r,sC200r,sC300r,sC400r,sC500r;

    int A100[100];
    int A200[200];
    int A300[300];
    int A400[400];
    int A500[500];
    
    FillDec(A100,100);
    PrintMas(A100,100);
    printf("\n");
    insertSort(A100,100,&iM100r,&iC100r);
    PrintMas(A100,100);
    printf("\n");

    FillRand(A100,100);
    insertSort(A100,100,&iM100r,&iC100r);
    FillRand(A200,200);
    insertSort(A200,200,&iM200r,&iC200r);
    FillRand(A300,300);
    insertSort(A300,300,&iM300r,&iC300r);
    FillRand(A400,400);
    insertSort(A400,400,&iM400r,&iC400r);
    FillRand(A500,500);
    insertSort(A500,500,&iM500r,&iC500r);

    

    FillRand(A100,100);
    shellSort(A100,100,&sM100r,&sC100r);
    FillRand(A200,200);
    shellSort(A200,200,&sM200r,&sC200r);
    FillRand(A300,300);
    shellSort(A300,300,&sM300r,&sC300r);
    FillRand(A400,400);
    shellSort(A400,400,&sM400r,&sC400r);
    FillRand(A500,500);
    shellSort(A500,500,&sM500r,&sC500r);




    printf("-------------------------------------------------\n");
    printf("|  N  |   по              |   Мф+Сф   |  Мф+Сф  |\n");
    printf("|     | формуле           |   insert  |  shell  |\n");
    printf("|     |  Кнута            |           |         |\n");
    printf("-------------------------------------------------\n");
    printf("|     |                   |           |         |\n");
    printf("| 100 | ");
    int steps[100];
        int stepCount;
        Steps(100, steps, &stepCount);
        for (int j = 0; j < stepCount; j++) {
            printf("%d ", steps[j]);
        }
        printf("        ");
    printf("|  %d     |  %d   |\n", iM100r+iC100r,sM100r+sC100r );
    printf("|     |                   |           |         |\n");
    printf("-------------------------------------------------\n");
    printf("|     |                   |           |         |\n");
    printf("| 200 | ");
    steps[100];
         stepCount;
        Steps(200, steps, &stepCount);
        for (int j = 0; j < stepCount; j++) {
            printf("%d ", steps[j]);
        }
        printf("    ");
    printf("|  %d    |  %d   |\n", iM200r+iC200r,sM200r+sC200r );
    printf("|     |                   |           |         |\n");
    printf("-------------------------------------------------\n");
    printf("|     |                   |           |         |\n");
    printf("| 300 | ");
     steps[100];
        stepCount;
        Steps(300, steps, &stepCount);
        for (int j = 0; j < stepCount; j++) {
            printf("%d ", steps[j]);
        }
    printf("|  %d    |  %d   |\n", iM300r+iC300r,sM300r+sC300r );
    printf("|     |                   |           |         |\n");
    printf("-------------------------------------------------\n");
    printf("|     |                   |           |         |\n");
    printf("| 400 | ");
     steps[100];
        stepCount;
        Steps(400, steps, &stepCount);
        for (int j = 0; j < stepCount; j++) {
            printf("%d ", steps[j]);
        }
    printf("|  %d    |  %d  |\n", iM400r+iC400r,sM400r+sC400r );
    printf("|     |                   |           |         |\n");
    printf("-------------------------------------------------\n");
    printf("|     |                   |           |         |\n");
    printf("| 500 | ");
     steps[100];
        stepCount;
        Steps(500, steps, &stepCount);
        for (int j = 0; j < stepCount; j++) {
            printf("%d ", steps[j]);
        }
    printf("|  %d   |  %d  |\n", iM500r+iC500r,sM500r+sC500r );
    printf("|     |                   |           |         |\n");
    printf("-------------------------------------------------\n");
//     printf("---------------------------------------\n");
//     printf("|     |         |      |       |      |\n");
//     printf("| 200 |  %d  |%d |  %d  | %d|\n", (200*200 - 200)/4 + 200 - 1 + (200*200-200)/4, M200d+C200d,M200i+C200i,M200r+C200r);
//     printf("|     |         |      |       |      |\n");
//     printf("---------------------------------------\n");
//     printf("|     |         |      |       |      |\n");
//     printf("| 300 |  %d  |%d |  %d  | %d|\n", (300*300 - 300)/4 + 300 -1 + (300*300-300)/4, M300d+C300d,M300i+C300i,M300r+C300r);
//     printf("|     |         |      |       |      |\n");
//     printf("---------------------------------------\n");
//     printf("|     |         |      |       |      |\n");
//     printf("| 400 |  %d  |%d| %d  | %d|\n", (400*400 - 400)/4 + 400 - 1 + (400*400-400)/4, M400d+C400d,M400i+C400i,M400r+C400r);
//     printf("|     |         |      |       |      |\n");
//     printf("---------------------------------------\n");
//     printf("|     |         |      |       |      |\n");
//     printf("| 500 |  %d |%d| %d  |%d|\n", (500*500 - 500)/4 + 500 - 1 + (500*500-500)/4, M500d+C500d,M500i+C500i,M500r+C500r);
//     printf("|     |         |      |       |      |\n");
//     printf("---------------------------------------\n");
    
    
}
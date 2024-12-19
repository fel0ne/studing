#include <stdio.h>
void printm(int N,int matrix[N][N]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N;j++){
          
          printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int N;
    scanf("%d" , &N);
    int matrix[N][N];
    int counter = 0;
    for(int i = 0; i < N/2; i++){
        for(int j = i; j < N-i; j++){
            matrix[i][j] = counter;
            counter += 1;
        }
        for(int j = i+1; j < N-i; j++){
            matrix[j-1][N-i-1] = counter;
            counter += 1;
        }
        for(int j = N-i;  j > i; j= j -1){
            matrix[N-i-1][j-1] = counter;
            counter += 1;
        }
        for(int j = N-i; j > i; j = j -1){
            matrix[j+1][N-i+1] = counter;
            counter += 1;
        }
        
        // for(int j = N-i; j > i; j--){s
        //     scanf("%d", &matrix[j][i]);
        // }
    }
    printm(N,matrix);
}
#include <stdio.h>

void printm(int N,float matrix[N][N]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N;j++){
          
          printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

float Opredelitel(int N,float matrix[N][N]){
    for (int i = 0;i < N; i++){
         for (int j = i + 1; j < N; j++) {

            float temp = matrix[j][i] / matrix[i][i];

            for (int k = 0; k < N; k++) {

                matrix[j][k] -= temp * matrix[i][k];

            }
        }
    }
    printm(N,matrix);
    printf("\n");
    float determinant = 1.0 ;
    for (int i = 0; i < N; i++){
        determinant = determinant * matrix[i][i];

    }
    return(determinant);
}

int main(){
    int N;
    printf("N = ");
    scanf("%d", &N);
    float matrix[N][N];
    float free[N];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("a[%d][%d] = ", i, j);
            scanf("%f", &matrix[i][j]);
        }
    }
    for (int i = 0; i < N; i++){
        scanf("%f", &free[i]);
    }

    //printm(N,matrix);
    printf("\n");

    float op;
    float ar_op[N];
    
    for (int i = 0; i < N + 1; i++){
        if (i == N){
            op = Opredelitel(N,matrix);
        }
        else{
            float temp[N][N]; 
            for(int j = 0; j < N; j++){
                for(int k = 0; k < N; k++){
                    temp[j][k] = matrix[j][k]; 
                }
            }
            for(int j = 0; j < N; j++){
                temp[j][i] = free[j];
            }
            printm(N,temp);
            ar_op[i] = Opredelitel(N,temp);
        }

    }
    for(int j = 0; j < N; j++){
        printf("%f\n", ar_op[j]/op);
    }
    
    // if (N == 2){
    //     int matrix2[N][N];
    //     for(int i = 0; i < N; i++){
    //         for(int j = 0; j < N;j++){
    //             matrix2[i][j] = matrix[i][j];
    //         }
    //     }        
    //     printf("\n");
    //     printm(N,matrix2);
    // } 
}

// 1 2 3
// 4 5 6
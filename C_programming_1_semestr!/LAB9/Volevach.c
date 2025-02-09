#include <stdio.h>
#include <stdlib.h>
void printa(int n,int *array){
    for(int i = 0; i < n; i++){
        printf("%d ",array[i]);
    }
    
}
void printm(int n, int **matrix){ 
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d " , matrix[i][j]); // *((*(matrix + i))+j)
        }
        printf("\n");
    }

}
void Random_append_elements(int n, int **matrix){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matrix[i][j] = rand(); 
        }
    }
}
void Nrandom_append_elements(int n, int **matrix){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int buffer;
            scanf("%d", &buffer);
            matrix[i][j] = buffer; 
        }
    }
}
int Parsing_minimmum_element(int n, int **matrix, int * x, int * y){
    int min = matrix[0][0];
    *x = 0;
    *y = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if (matrix[i][j] < min ){
                min = matrix[i][j];
                *x = i;
                *y = j;
            }
        }
    }
    return(min);
}
void New_matrix_append_elemnts(int **matrix, int **new_matrix,int x, int y){

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            new_matrix[i][1-j] = matrix[i+x][y-j];
        } 
    }
}
void New_matrix_mul(int n,  int **new_matrix, int b){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            new_matrix[i][j] = new_matrix[i][j] * b;  
        }
    }
}
int Sum_matrix_elements(int **new_matrix){
    int sum = new_matrix[0][0]+new_matrix[0][1]+new_matrix[1][0] + new_matrix[1][1];
    return(sum);
}
void Forming_array(int *array, int **matrix){
    array[0] = matrix[0][0];
    array[1] = matrix[0][1];
    array[2] = matrix[1][0];
    array[3] = matrix[1][1];
}
int main(){
    int x;
    int y;
    int n;
    char temp;

    printf("razmer matricy: \n");
    scanf("%d%*c", &n);
    

    int** matrix = (int**)calloc(n,sizeof(int*));
    for (int i = 0; i < n; i++){
        matrix[i] = (int*)calloc(n, sizeof(int));
    }
    if  (matrix == NULL || n == 0){
        printf("chto popalo");
        exit(1);
    }
    printf("vvodim znachenya sami? (1/0)\n");
    scanf("%c" ,&temp);

    if  (temp == '1'){
        Nrandom_append_elements(n, matrix);
        printm(n,matrix);
    }
    else if(temp == '0'){
        Random_append_elements(n,matrix);
        printm(n,matrix);
    }
    else{
        printf("chto popalo\n");
        exit(1);
    }
    int **new_matrix =NULL;
    int *array = NULL;
    printf("%d\n", Parsing_minimmum_element(n,matrix,&x,&y));
    printf("%d %d\n" , x,y);
    if (y > 0 || x < n-1-1){                                                                                                  
        new_matrix = (int**)calloc(2, sizeof(int*));
        for (int i = 0; i < 2; i++){
            new_matrix[i] = (int*)calloc(2, sizeof(int));
            //New_matrix_append_elemnts(matrix,new_matrix,x,y);
        }
        //printm(2,new_matrix);

        New_matrix_append_elemnts(matrix,new_matrix,x,y);
        printm(2,new_matrix);
        
        int mul_temp = 0;
        printf("na skolko umnozhim: ");
        scanf("%d", &mul_temp);
        New_matrix_mul(2,new_matrix,mul_temp);
        printm(2,new_matrix);

        int sum_elements = Sum_matrix_elements(new_matrix);
        printf("sum elements = %d\n", sum_elements);


        array = (int*)malloc(4*sizeof(int));
        Forming_array(array,new_matrix);
        printa(4,array);
    }

    // free;
    for (int i = 0;i < n; i++){
        free(matrix[i]);
    }
    free(matrix);
    if (new_matrix != NULL){
        for(int i = 0;i < 2; i++){
            free(new_matrix[i]);
        }
        free(new_matrix);
    }
    if (array != NULL){
       free(array);
    }
  
}


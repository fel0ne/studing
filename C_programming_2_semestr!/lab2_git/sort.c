void ShakerSort(int * A, int n, int * M, int * C){//12345
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
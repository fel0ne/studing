void insertSort(int * A, int n, int * M, int * C){ //123

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
void ShakerSort(int * A, int n){//12345
    int L = 0;
    int R = n-1;
    int k = n-1;

 
    do{
        for(int j = R ; j > L ; j--){
            if (A[j]<A[j-1]){
                int tmp = A[j];
                A[j] = A[j-1];
                A[j-1] = tmp;
                k = j;
            }
        }
        L = k;
        for(int j = L ; j < R; j++){
            if (A[j]>A[j+1]){
                int tmp = A[j];
                A[j] = A[j+1];
                A[j+1] = tmp;
                k = j;
            }
        }
        R = k;

    }while(L<R);

}
int main(){
    int a[] = {4, 2};
    ShakerSort(a,2);
}
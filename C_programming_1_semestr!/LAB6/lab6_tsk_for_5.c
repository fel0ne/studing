#include <stdio.h>

int main(){
    int size;
    printf("size: ");
    scanf("%d", &size);
    int ar[size];
    for(int i = 0; i < size; i++){
        int temp;
        printf("element : %d = ", i);
        scanf("%d", &temp);
        ar[i] = temp;
    }
    int groups = 0;
    int counter = 0;
    for(int i = 1; i < size; i++){
        if (ar[i] > ar[i-1]){
            counter +=1;
        }
        else{
            if (counter >= 1){
                groups += 1;
                counter = 0;
            }
        }
        if ((i == size-1) && (counter >= 1)){
            groups += 1;
        }
    }
    for(int i = 0; i < size; i++){
        printf("%d", ar[i]);
    }
    printf("\n");
    printf("count groups = %d", groups);
}
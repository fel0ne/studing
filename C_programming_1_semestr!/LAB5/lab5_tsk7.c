#include <stdio.h>

void  P_bit(char a){
	for (int i = 0; i < 8; i++){  //  vmesto 8 luche ispolzovat sizeof()
                if ((a >> i) &  1 ==  1){
                        printf("%d",i);
                        break;
                }
        }
}

int main(){
	char  a = 0;
	scanf("%d", &a);
	P_bit(a);
}
//4  == 00000100
//5 ==  00000101

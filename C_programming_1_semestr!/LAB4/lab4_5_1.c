// hello
#include <stdio.h>
int main(){
	int size;
	scanf("%d", &size);
	for (int strs = 0; strs < size; strs++){
		if (strs<size/2+1){
                        //probely
                                for (int p = size - (size-strs); p > 0; p --){
                                        printf("   ");
                                }
                        }else{
                                for (int p = size - strs - 1; p > 0 ; p--){
                                        printf("   ");
                                }
                        }
                        //simvoly+ perenos stroki
                        if (strs<size/2+1){ //verh + seredina
                                for (int sim_num = (size - (strs)*2); sim_num > 0; sim_num--){
                                        printf("o");
                                }
                                printf("\n");
                        }else{ //niz
                               for (int sim_num= (size - strs*2)*(-1)+2 ;sim_num >0; sim_num-- ){
                                        printf("o");
                                }
                                printf("\n");
                        }
	}
}

#include<stdio.h>
//prostoe chi neprostoe
int main () {
	int n = 2,flag = 0,a = 0;
	scanf("%d",&a);
	while (a % n != 0){
		n++;
		if (n==a){
			flag = 1;
			printf("Prostoe");
			break;
		}
	}
}


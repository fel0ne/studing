#include <stdio.h>
//  prostoe chi ne prostoefdfgd
int main() {
	int a ;
	scanf("%d", &a);
	for (int s = 0, n = 2; n < a; n++){
		if (a % n == 0){
			int s = 1;
				printf("ne prostoe");
			break;
		}
	}
}

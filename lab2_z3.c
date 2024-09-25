#include <stdio.h>
#include <math.h>

int main(){
	float x;
	float y;
	printf("vvedi x: ");
	scanf("%f", &x);
	printf("vvedi y: ");
	scanf("%f", &y);
	if (x*x + y*y < 1 && x > 0 && y > -1 * x){
		printf("yes");
	}
	else{
		printf("no");
	}
} 

#include <stdio.h>

int main(){
	char op;
	float temp;
	printf("vvedi temperaturu ");
	scanf("%f%c",&temp,&op);
	if (op == 'c' || op == 'C' ){
		temp=(temp*9/5)+32;
		printf("temperatura v forengate: %f\n", temp);
	}
	else if(op == 'f' || op == 'F'){
		temp=(temp-32)*5/9;
		printf("temperatura v celsii: %f\n", temp);
	}
	else{
		printf("Error\n");
	}

}

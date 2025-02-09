#include  <stdio.h>
// max cifra v chisle
int main() {
	
	int s = 0,k = 0,a = 0;
	scanf("%d",&a);
	for (int n = a; n != 0; n = n / 10){
		k = n % 10;
		if (k>s){
			s=k;
		}
	}
	printf("%d",s);
	
}

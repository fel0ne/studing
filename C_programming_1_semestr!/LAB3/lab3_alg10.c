#include  <stdio.h>
//  prevorot chisla
int main() {
	
	int s = 0,k = 0,a = 0;
	scanf("%d",&a);
	for (int n = a; n != 0; n = n / 10){
		k = n % 10;
		s=s*10 + k;
	}
	printf("%d",s);
	
}

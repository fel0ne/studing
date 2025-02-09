// Factoriall
#include <stdio.h>
int main() {
	int n=0,s=1;
	scanf("%d",&n);
	for(int  i = 1; i <= n; i++){
		s = s * i;
	}
	printf("%d",s);
}

#include <stdio.h>
int main(){
	int a;
	int k;
	int temp;
	printf("a = ");
        scanf ("%d", &a);
	printf("k = ");
	scanf ("%d", &k);
	//temp = (1 << k) & a;
	temp = (a >> k) | (a << (32 - k));
	printf("%d",temp);
}

// 2^k-1=3
// 000000 1<<k == 1*2^k
// char x =5&3 = 1
// 00000101 5
// 00000011 3
// 00000001 &


// 5 0000000 101
//  01 0000000000000 1

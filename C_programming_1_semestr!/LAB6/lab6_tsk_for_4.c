#include <stdio.h>

int main() {
	int size_ar ;
	printf("vvedy razmer massivov:" );
	scanf("%d", &size_ar);
	int ar_b[size_ar];
	int ar_a[size_ar];

	printf("znachenya A:\n");
        for (int i = 0,c = 0; i < size_ar; i=i+2,c++){
                printf ("       element number: %d\n", c);
                int temp_a;
                int temp_b;
                printf("                a = ");
                scanf("%d", &temp_a);
                printf("                b = ");
                scanf("%d", &temp_b);
                ar_a[i] = temp_a;
                ar_a[i+1] = temp_b;
        }

	printf("znachenya B:\n");
       for (int i = 0, c = 0; i < size_ar;i =  i+2, c++){
                printf ("       element number: %d\n", c);
                int temp_a;
                int temp_b;
                printf("                a = ");
                scanf("%d", &temp_a);
                printf("                b = ");
                scanf("%d", &temp_b);
                ar_b[i] = temp_a;
		ar_b[i+1] = temp_b;
        }
	//sum in C
	int ar_c[size_ar];
	printf("array C:");
	for (int i = 0; i < size_ar; i++){
		ar_c [i] = ar_b[i] + ar_a[i];
		printf(" %d",ar_c[i]);
	}
	printf("\n");
	//max for reals
	int max_a = 0;
	for (int i = 0;i < size_ar; i = i+2){
		if (max_a<ar_a[i]){
			max_a = ar_a[i];
		}
	}
	printf("max for reals A = %d  \n", max_a,max_b);
	//count mnim < 0
	int count_m = 0;
	for (int i = 1; i < size_ar; i = i + 2){
		if  (ar_b[i] < 0){
			count_m++;
		}
	}
	printf("count mnim < 0 for B = %d\n", count_m);
	//midle arhmethic for C
	float  midle = 0;
	for (int i = 0; i < size_ar; i++){
		midle += ar_c[i];
	}
	midle = midle / size_ar;
	printf("arihmetic middle = %f", midle);





}
// 1  2 3 4 5 6
// 6 7 8 9 0 7

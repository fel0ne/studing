#include <fstream> 
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
//#include <conio.h>
#include <math.h>

const int n =33;


int c[n][n], length[n], sum = 0;
float p[n];
char a[n];
int lgm = 0;
void shanon()
{
	float q[n];
	p[0] = 0; q[0] = 0;
	for (int i = 1; i < n; i++)
	{
		q[i] = q[i - 1] + p[i];
		length[i] = ceil(-log(p[i]) / log(2));
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j <= length[i]; j++)
		{
			q[i - 1] *= 2;
			c[i][j] = floor(q[i - 1]);
			while (q[i - 1] >= 1)
				q[i - 1] -= 1;
		}
	}
}

int main(){
    FILE *f;
	float entropy = 0, lshanon = 0;
	f = fopen("SAODe.txt", "r");
	for (int i = 1; i < n; i++)
		p[i] = 0;
	for (int i = 1; i < n; i++) {
        a[i] = 'а' + i - 1; 
    }

	while (!feof(f))
	{
		char c;
		fscanf(f, "%c", &c);
		if (feof(f))
			break;
		printf("%c",c); 
		p[c - 'а' + 1] += 1;
		sum++;
	}
	printf("\n");
	
	bool b = true;
	while (b)
	{
		b = false;
		for (int i = 1; i < n; i++)
		{
			if (p[i - 1] < p[i])
			{
				float temp = p[i - 1];
				p[i - 1] = p[i];
				p[i] = temp;
				char c = a[i - 1];
				a[i - 1] = a[i];
				a[i] = c;
				b = true;
			}
		}
	}

	float P[n];
	for (int i = 1; i < n; i++)
	{
		p[i] /= float(sum);
		entropy += p[i] * abs(log(p[i]) / log(2));
		P[i] = p[i];
	}
	fclose(f);

	

	shanon();
	printf("---------------------------------------------------------------\n");
	printf("| Символ | Вероятность | Кодовое слово | Длина кодового слова |\n");
	printf("---------------------------------------------------------------\n");
	for (int i = 1; i < n; i++)
	{
		printf("|    %c   |  %2.6f   | ", a[i], p[i]);
		for (int j = 1; j <= length[i]; j++)
			printf("%d", c[i][j]);
		for (int j = length[i] + 1; j < 11; j++)
			printf(" ");
		printf("    |  %14d      |\n", length[i]);
		printf("--------------------------------------------------------------\n");
		lshanon += length[i] * p[i];
	}

	
	

	
}
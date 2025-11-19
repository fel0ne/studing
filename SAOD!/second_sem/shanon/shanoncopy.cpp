#include <fstream> 
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <math.h>

using namespace std;

const int n = 33;

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
        if (p[i] > 0) {
            length[i] = ceil(-log(p[i]) / log(2));
        } else {
            length[i] = 0;
        }
    }
    for (int i = 1; i < n; i++)
    {
        if (p[i] > 0) {
            for (int j = 1; j <= length[i]; j++)
            {
                q[i - 1] *= 2;
                c[i][j] = floor(q[i - 1]);
                while (q[i - 1] >= 1)
                    q[i - 1] -= 1;
            }
        }
    }
}

int main() {
    FILE *f;
    float entropy = 0, lshanon = 0;
    
    
    for (int i = 0; i < n; i++) {
        p[i] = 0;
        length[i] = 0;
        a[i] = 'a' + i; 
    }
    

    f = fopen("SAODe.txt", "r");
    if (f == NULL) {
        printf("Error: Cannot open file SAO.txt\n");
        return 1;
    }

    // Чтение файла и подсчет частот
    while (!feof(f))
    {
        char ch;
        fscanf(f, "%c", &ch);
        if (feof(f))
            break;
        printf("%c", ch); 
        
        int index = (unsigned char)ch % n; 
        if (index > 0 && index < n) {
            p[index] += 1;
            sum++;
            a[index] = ch; 
        }
    }
    printf("\n");
    
    if (sum == 0) {
        printf("Error: No valid characters found in file\n");
        fclose(f);
        return 1;
    }

 
    bool b = true;
    while (b)
    {
        b = false;
        for (int i = 2; i < n; i++) 
        {
            if (p[i - 1] < p[i])
            {
                float temp = p[i - 1];
                p[i - 1] = p[i];
                p[i] = temp;
                char temp_char = a[i - 1];
                a[i - 1] = a[i];
                a[i] = temp_char;
                b = true;
            }
        }
    }

  
    float P[n];
    for (int i = 1; i < n; i++)
    {
        p[i] /= float(sum);
        if (p[i] > 0) {
            entropy += p[i] * abs(log(p[i]) / log(2));
        }
        P[i] = p[i];
    }
    fclose(f);

    shanon();
    
    printf("\n\nShannon Code: \n");
    printf("---------------------------------------------------------------\n");
    printf("| символ  | вероятность | кодовое слово| длина кодового слова  |\n");
    printf("---------------------------------------------------------------\n");
    
    for (int i = 1; i < n; i++)
    {
        if (p[i] > 0) { // Выводим только символы с ненулевой вероятностью
            printf("|    %c   |  %2.6f   | ", a[i], p[i]);
            for (int j = 1; j <= length[i]; j++)
                printf("%d", c[i][j]);
            // Выравнивание пробелами
            int spaces = 11 - length[i];
            for (int j = 0; j < spaces; j++)
                printf(" ");
            printf("    |  %14d      |\n", length[i]);
            printf("--------------------------------------------------------------\n");
            lshanon += length[i] * p[i];
        }
    }

    printf("\nResults:\n");
    printf("энтропия: %f\n", entropy);
    printf("средния длина: %f\n", lshanon);
    printf("избыточность: %f\n", lshanon - entropy);

    return 0;
}
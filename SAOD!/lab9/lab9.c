#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int M_sort, C_sort;
int M_create, C_create;

void Fillinc(int *A, int n) {
    for (int i = 0; i < n; i++) A[i] = i;
}

void FillDec(int *A, int n) {
    for (int i = 0; i < n; i++) A[i] = n - i - 1;
}

void FillRand(int *A, int n) {
    for (int i = 0; i < n; i++) A[i] = rand() % 10000;
}

int heapCreate(int *A, int L, int R) {
    int local_M = 0, local_C = 0;
    int x = A[L];
    int i = L;
    
    while (1) {
        int j = 2 * i + 1; // Исправлено для 0-based
        if (j > R) break;
        
        if (j < R && (local_C++, A[j+1] <= A[j])) j++;
        
        local_C++;
        if (x <= A[j]) break;
        
        A[i] = A[j];
        local_M++;
        i = j;
    }
    A[i] = x;
    local_M++;
    
    M_create += local_M;
    C_create += local_C;
    return local_M + local_C;
}

void heapSort(int *A, int n) {
    M_sort = 0; C_sort = 0;
    
    // Построение кучи
    for (int L = n/2 - 1; L >= 0; L--) { // Исправленный индекс
        heapCreate(A, L, n-1);
    }
    
    // Сортировка
    for (int R = n-1; R > 0; R--) {
        int temp = A[R];
        A[R] = A[0];
        A[0] = temp;
        M_sort += 3;
        heapCreate(A, 0, R-1);
    }
}

void printTable(int **AR[3], const char* title, int isSortTable) {
    printf("\n=== %s ===\n", title);
    printf("| %4s | %12s | %9s | %9s | %9s |\n", 
           "N", "Theory", "Dec", "Rand", "Inc");
    printf("|------|-------------|-----------|-----------|-----------|\n");

    for (int i = 0; i < 5; i++) {
        int n = (i+1)*100;
        double theory;
        
        if (isSortTable) {
            // Ваша формула для HeapSort: C(t)+M(t) = 3n log2(n) +7.5n -2 
            theory = 3 * n * log2(n) + 7.5 * n - 2;
        } else {
            // Ваша формула для HeapCreate: C(t)+M(t) =3n log2(n)+7.5n-4
            theory = 3 * n * log2(n) + 7.5 * n - 4;
        }

        // Убывающий
        M_create = C_create = M_sort = C_sort = 0;
        FillDec(AR[0][i], n);
        isSortTable ? heapSort(AR[0][i], n) : heapCreate(AR[0][i], 0, n-1);
        int dec = isSortTable ? (M_sort + C_sort) : (M_create + C_create);

        // Случайный
        M_create = C_create = M_sort = C_sort = 0;
        FillRand(AR[1][i], n);
        isSortTable ? heapSort(AR[1][i], n) : heapCreate(AR[1][i], 0, n-1);
        int rand = isSortTable ? (M_sort + C_sort) : (M_create + C_create);

        // Возрастающий
        M_create = C_create = M_sort = C_sort = 0;
        Fillinc(AR[2][i], n);
        isSortTable ? heapSort(AR[2][i], n) : heapCreate(AR[2][i], 0, n-1);
        int inc = isSortTable ? (M_sort + C_sort) : (M_create + C_create);

        printf("| %4d | %11.1f | %9d | %9d | %9d |\n",
               n, theory, dec, rand, inc);
    }
}

int main() {
    srand(time(NULL));
    
    // Инициализация и заполнение массивов
    int A1d[100], A2d[200], A3d[300], A4d[400], A5d[500];
    int A1r[100], A2r[200], A3r[300], A4r[400], A5r[500];
    int A1i[100], A2i[200], A3i[300], A4i[400], A5i[500];

    FillDec(A1d, 100); FillDec(A2d, 200); FillDec(A3d, 300); FillDec(A4d, 400); FillDec(A5d, 500);
    FillRand(A1r, 100); FillRand(A2r, 200); FillRand(A3r, 300); FillRand(A4r, 400); FillRand(A5r, 500);
    Fillinc(A1i, 100); Fillinc(A2i, 200); Fillinc(A3i, 300); Fillinc(A4i, 400); Fillinc(A5i, 500);

    int *ARd[5] = {A1d, A2d, A3d, A4d, A5d};
    int *ARr[5] = {A1r, A2r, A3r, A4r, A5r};
    int *ARi[5] = {A1i, A2i, A3i, A4i, A5i};
    int **AR[3] = {ARd, ARr, ARi};

    printTable(AR, "HeapCreate", 0);
    printTable(AR, "HeapSort", 1);

    return 0;
}
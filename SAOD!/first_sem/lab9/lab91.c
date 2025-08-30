#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int mp = 0, cp = 0;

void FillInc(int A[], int n);
void FillDec(int A[], int n);
void FillRand(int A[], int n);
void CheckSum(int A[], int n);
void RunNumber(int A[], int n);
void PrintMas(int A[], int n);
void PrintMasRevers(int A[], int n);
void Swap(int *x, int *y);
void ResultOld(int n);
void ResultTabl(int n);
void HeapSort(int A[], int n);
void WorkDec(int n, int i);
void WorkInc(int n, int i);
void WorkRand(int n, int i);
void HeapBuild(int A[], int l, int r);

int main() {
    int n;
    printf("Vvedite razmer massiva: ");
    scanf("%d", &n);
    int A[n];
    
    FillRand(A, n);
    printf("Ishodniy massiv:\n");
    PrintMas(A, n);
    CheckSum(A, n);
    RunNumber(A, n);
    
    HeapSort(A, n);
    
    printf("\nOtsortirovanniy massiv:\n");
    PrintMasRevers(A, n);
    CheckSum(A, n);
    RunNumber(A, n);
    
    ResultOld(n);
    printf("\n\nTablica rezultatov:\n");
    ResultTabl(100);
    
    printf("\n\n");
    system("PAUSE");
    return 0;
}

int randomm(int N) { 
    return rand() % N; 
}

void FillInc(int A[], int n) {
    for (int i = 0; i < n; i++) 
        A[i] = i + 1;
}

void FillDec(int A[], int n) {
    for (int i = 0; i < n; i++) 
        A[i] = n - i;
}

void FillRand(int A[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) 
        A[i] = randomm(2 * n);
}

void CheckSum(int A[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += A[i];
    printf("\nSumma elementov: %d", sum);
}

void RunNumber(int A[], int n) {
    int count = 1;
    for (int i = 1; i < n; i++)
        if (A[i-1] > A[i]) count++;
    printf("\nChislo seriy: %d", count);
}

void PrintMas(int A[], int n) {
    for (int i = 0; i < n; i++) {
        if (i % 20 == 0 && i != 0) printf("\n");
        printf("%3d ", A[i]);
    }
    printf("\n");
}

void PrintMasRevers(int A[], int n) {
    for (int i = n-1; i >= 0; i--) {
        if ((n - i) % 20 == 0 && i != n-1) printf("\n");
        printf("%3d ", A[i]);
    }
    printf("\n");
}

void Swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void ResultOld(int n) {
    float Ct = 2 * n * log2(n) + n + 2;
    float Mt = n * log2(n) + 6.5 * n - 4;
    printf("\nTeoriya: C(t)=%.2f, M(t)=%.2f", Ct, Mt);
    printf("\nPractica: C(p)=%d, M(p)=%d, T(p)=%d", cp, mp, cp+mp);
}

void HeapBuild(int A[], int l, int r) {
    int x = A[l];
    int i = l;
    mp++;
    while (1) {
        int j = 2 * i + 1;
        if (j > r) break;
        if (j < r && (++cp, A[j+1] <= A[j])) j++;
        if (++cp, x <= A[j]) break;
        A[i] = A[j];
        mp++;
        i = j;
    }
    A[i] = x;
    mp++;
}

void HeapSort(int A[], int n) {
    mp = 0; cp = 0;
    for (int l = n/2 - 1; l >= 0; l--) 
        HeapBuild(A, l, n-1);
    
    for (int r = n-1; r > 0; r--) {
        Swap(&A[0], &A[r]);
        mp += 3;
        HeapBuild(A, 0, r-1);
    }
}

void WorkDec(int n, int i) {
    int A[n];
    FillDec(A, n);
    HeapSort(A, n);
}

void WorkInc(int n, int i) {
    int A[n];
    FillInc(A, n);
    HeapSort(A, n);
}

void WorkRand(int n, int i) {
    int A[n];
    FillRand(A, n);
    HeapSort(A, n);
}

void ResultTabl(int n) {
    printf("|  n   |   Inc  |   Dec  |  Rand  |\n");
    printf("|------|--------|--------|--------|\n");
    for (; n <= 1000; n += 100) {
        printf("| %4d |", n);
        
        WorkInc(n, 0);
        printf(" %6d |", cp + mp);
        
        WorkDec(n, 0);
        printf(" %6d |", cp + mp);
        
        WorkRand(n, 0);
        printf(" %6d |\n", cp + mp);
    }
}
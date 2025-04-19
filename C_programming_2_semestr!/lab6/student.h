#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define N 5
#define len_n 6
#define len_g 7

typedef struct student {
    int number;
    unsigned char name[len_n];
    unsigned char group[len_g];
    int marks[3];
} student;

// Прототипы функций
int randomm(int a, int b);
void randomizeParameters(student A[N]);
void printStudent(student A);
void printStudents(student A[N]);
void create_file(student A[N]);
void search_in_file();
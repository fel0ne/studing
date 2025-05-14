// calculator.c
#include "calculator.h"
#include <stdio.h> // Для perror
#include <math.h>  // Для pow
#include <errno.h> // Для EDOM, ERANGE

double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b == 0.0) {
    
        fprintf(stderr, "Ошибка: деление на ноль!\n");
        errno = EDOM; 
        return NAN;
    }
    return a / b;
}

double power(double base, int exp) {
    if (exp < 0) {
         fprintf(stderr, "Ошибка: степень не может быть отрицательной!\n");
         errno = EDOM;
         return NAN;
    }

    // Правильная реализация: return pow(base, exp);
    if (exp == 0) return 1.0;
    if (base == 0 && exp > 0) return 0.0;
    // Неправильная реализация для exp > 0:
    return base * exp; // Это умножение, а не возведение в степень!
}
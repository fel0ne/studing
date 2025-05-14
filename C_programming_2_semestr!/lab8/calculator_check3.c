// test_calculator_basic.c
#include "calculator.h" // Импортируем наш "чужой" код
#include <stdio.h>
#include <math.h> // Для NAN

// Функция теста для сложения
void test_add_basic() {
    double result = add(5.0, 3.0);
    double expected = 8.0;
    if (result == expected) {
        printf("Тест add: Успех\n");
    } else {
        printf("Тест add: Неудача. Ожидалось %.2f, получено %.2f\n", expected, result);
    }
}

// Функция теста для деления на ноль (проверка ошибки)
void test_divide_by_zero_basic() {
    // Деление на ноль должно вернуть NAN
    double result = divide(10.0, 0.0);

    // Проверка, является ли результат NAN (используем isinf для проверки бесконечности тоже, на всякий случай)
    if (isnan(result)) {
        printf("Тест divide_by_zero: Успех (получено NAN)\n");
    } else {
        printf("Тест divide_by_zero: Неудача. Ожидалось NAN, получено %.2f\n", result);
    }
    // В более сложных случаях нужно было бы проверять errno, но это усложняет пример без фреймворка.
}


// --- Наша намеренно сломанная функция для демонстрации падения теста ---
void test_power_broken_basic() {
    double result = power(2.0, 3); // Ожидаем 2^3 = 8.0
    double expected = 8.0;
     if (result == expected) {
        printf("Тест power_broken: Успех (ОШИБКА В ТЕСТЕ/КОДЕ! Код power НЕПРАВИЛЬНЫЙ!)\n"); // Этот тест ошибочно пройдет, т.к. код power сейчас вернет 2*3=6, и тест должен был упасть
    } else {
        printf("Тест power_broken: Неудача. Ожидалось %.2f, получено %.2f\n", expected, result); // Вот тут тест упадет
    }
}


int main() {
    printf("Запуск тестов (Оценка 3):\n");
    test_add_basic();
    test_divide_by_zero_basic();
    test_power_broken_basic(); // Запустим тест сломанной функции
    printf("--------------------\n");

    return 0;
}
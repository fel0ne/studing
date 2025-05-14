// test_calculator_check.c
#include <check.h>
#include "calculator.h" // Импортируем наш "чужой" код
#include <math.h>     // Для NAN
#include <errno.h>    // Для EDOM

// Тестовый случай (Test Case) для базовых арифметических операций
START_TEST(test_calculator_basic_ops)
{
    ck_assert_ldouble_eq(add(5.0, 3.0), 8.0); // Проверка сложения
    ck_assert_ldouble_eq(subtract(10.0, 4.0), 6.0); // Проверка вычитания
    ck_assert_ldouble_eq(multiply(2.0, 3.0), 6.0); // Проверка умножения
    ck_assert_ldouble_eq(divide(10.0, 2.0), 5.0); // Проверка деления
    ck_assert_ldouble_eq(divide(5.0, 2.0), 2.5);  // Проверка деления с дробным результатом
}
END_TEST

// Тестовый случай для деления на ноль
START_TEST(test_calculator_divide_by_zero)
{
    // Ожидаем, что функция вернет NAN и установит errno в EDOM
    errno = 0; // Сбрасываем errno перед вызовом
    double result = divide(10.0, 0.0);
    ck_assert(isnan(result)); // Проверяем, что результат NAN
    ck_assert_int_eq(errno, EDOM); // Проверяем, что errno установлен правильно
}
END_TEST

// Тестовый случай для сломанной функции power
START_TEST(test_calculator_power_broken)
{
    // Этот тест ДОЛЖЕН упасть, потому что power реализована неверно
    errno = 0; // Сбрасываем errno
    double result = power(2.0, 3); // Ожидаем 2^3 = 8.0
    ck_assert_ldouble_eq(result, 8.0); // Проверяем, что результат равен 8.0 (тест упадет, т.к. power вернет 6.0)
    ck_assert_int_eq(errno, 0); // Проверяем, что errno не установлен (если степень >= 0)
}
END_TEST

// Функция для создания набора тестов (Suite)
Suite *calculator_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Calculator"); // Создаем набор тестов
    tc_core = tcase_create("Core");   // Создаем тестовый случай

    // Добавляем тестовые функции в тестовый случай
    tcase_add_test(tc_core, test_calculator_basic_ops);
    tcase_add_test(tc_core, test_calculator_divide_by_zero);
    tcase_add_test(tc_core, test_calculator_power_broken); // Добавляем сломанный тест

    // Добавляем тестовый случай в набор тестов
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = calculator_suite(); // Получаем наш набор тестов
    sr = srunner_create(s);  // Создаем исполнитель тестов

    srunner_run_all(sr, CK_NORMAL); // Запускаем все тесты с обычным выводом
    number_failed = srunner_ntests_failed(sr); // Получаем количество упавших тестов
    srunner_free(sr); // Освобождаем ресурсы

    return (number_failed == 0) ? 0 : 1; // Возвращаем 0 при успехе, 1 при неудаче
}
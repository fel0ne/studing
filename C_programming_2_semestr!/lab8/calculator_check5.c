// test_calculator_check.c

#include <check.h>       // Включаем первым
#include <stdio.h>       // Для printf
#include <math.h>        // Для NAN
#include <errno.h>       // Для EDOM
#include <stdarg.h>      // Для va_list (нужен для пользовательского обработчика логов)

#include "calculator.h"  // Импортируем наш "чужой" код


// --- Пользовательский обработчик логирования check (обновленный порядок) ---
// Определяем эту функцию *после* всех необходимых #include
void custom_log_set_handler(enum print_output print_mode, const char *suite_name,
                        const char *tc_name, const char *test_name,
                        const char *filename, long linenum, int sr_mode, va_list ap)
{
    // Код функции остается таким же, как в предыдущем варианте (без CK_MSG_SETUP)
    switch (print_mode) {
        case CK_PASS:
            printf("[Тест %s] %s:%s:%s: PASSED ✅\n", test_name, suite_name, tc_name, test_name);
            va_end(ap);
            break;

        case CK_FAILURE:
            printf("[Тест %s] %s:%s:%s: FAILED ❌\n", test_name, suite_name, tc_name, test_name);
            vprintf("  Причина: ", ap);
            printf("\n");
            va_end(ap);
            break;

        case CK_ERROR:
            printf("[Тест %s] %s:%s:%s: ERROR ❗\n", test_name, suite_name, tc_name, test_name);
            vprintf("  Описание ошибки: ", ap);
            printf("\n");
            va_end(ap);
            break;

        default:
            va_end(ap);
            break;
    }
}


// --- Определение тестовых функций (без изменений) ---

START_TEST(test_calculator_basic_ops)
{
    ck_assert_ldouble_eq(add(5.0, 3.0), 8.0);
    ck_assert_ldouble_eq(subtract(10.0, 4.0), 6.0);
    ck_assert_ldouble_eq(multiply(2.0, 3.0), 6.0);
    ck_assert_ldouble_eq(divide(10.0, 2.0), 5.0);
    ck_assert_ldouble_eq(divide(5.0, 2.0), 2.5);
}
END_TEST


START_TEST(test_calculator_divide_by_zero)
{
    errno = 0;
    double result = divide(10.0, 0.0);
    ck_assert(isnan(result));
    ck_assert_int_eq(errno, EDOM);
}
END_TEST


START_TEST(test_calculator_power_broken)
{
    errno = 0;
    double result = power(2.0, 3);
    ck_assert_ldouble_eq(result, 8.0);
    ck_assert_int_eq(errno, 0);
}
END_TEST


// --- Функция для создания набора тестов (без изменений) ---
Suite *calculator_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Calculator");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_calculator_basic_ops);
    tcase_add_test(tc_core, test_calculator_divide_by_zero);
    tcase_add_test(tc_core, test_calculator_power_broken);

    suite_add_tcase(s, tc_core);

    return s;
}


// --- Главная функция для запуска тестов (без изменений) ---
int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    printf("============================================\n");
    printf("Запуск тестов для библиотеки Calculator\n");
    printf("============================================\n\n");

    s = calculator_suite();
    sr = srunner_create(s);

    srunner_set_log_handler(sr, "/tmp/log.txt");
    srunner_run_all(sr, CK_NOFORK); // Или CK_SILENT

    number_failed = srunner_ntests_failed(sr);

    printf("\n============================================\n");
    if (number_failed == 0) {
        printf("✅ ОБЩИЙ РЕЗУЛЬТАТ: Все тесты успешно пройдены!\n");
    } else {
        printf("❌ ОБЩИЙ РЕЗУЛЬТАТ: Провалено %d тест(а/ов).\n", number_failed);
    }
    printf("============================================\n");

    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}
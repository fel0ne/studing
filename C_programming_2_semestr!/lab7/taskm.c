#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

// Глобальные переменные для матриц и их размера
int **matrix_A, **matrix_B, **result_matrix;
int matrix_size;

// Структура для передачи параметров в поток
typedef struct {
    int start_row;    // Начальная строка для обработки
    int end_row;      // Конечная строка (не включительно)
} ThreadTask;

// Функция умножения матриц для отдельного потока
void *matrix_multiply_section(void *task) {
    ThreadTask *range = (ThreadTask *)task;
    for (int row = range->start_row; row < range->end_row; row++) {
        for (int col = 0; col < matrix_size; col++) {
            result_matrix[row][col] = 0;  // Обнуляем ячейку результата
            // Вычисляем значение для ячейки [row][col]
            for (int k = 0; k < matrix_size; k++) {
                result_matrix[row][col] += matrix_A[row][k] * matrix_B[k][col];
            }
        }
    }
    return NULL;
}

// Выделение памяти под матрицы
void create_matrices() {
    matrix_A = malloc(matrix_size * sizeof(int *));
    matrix_B = malloc(matrix_size * sizeof(int *));
    result_matrix = malloc(matrix_size * sizeof(int *));
    for (int i = 0; i < matrix_size; i++) {
        matrix_A[i] = malloc(matrix_size * sizeof(int));
        matrix_B[i] = malloc(matrix_size * sizeof(int));
        result_matrix[i] = malloc(matrix_size * sizeof(int));
    }
}

// Заполнение матриц тестовыми данными (все единицы)
void initialize_matrices() {
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            matrix_A[i][j] = 1;
            matrix_B[i][j] = 1;
        }
    }
}

// Освобождение памяти матриц
void destroy_matrices() {
    for (int i = 0; i < matrix_size; i++) {
        free(matrix_A[i]);
        free(matrix_B[i]);
        free(result_matrix[i]);
    }
    free(matrix_A);
    free(matrix_B);
    free(result_matrix);
}

// Запуск умножения с заданным числом потоков и замер времени
double execute_multiplication(int num_threads) {
    pthread_t threads[num_threads];
    ThreadTask tasks[num_threads];

    // Распределение строк между потоками
    int base_rows = matrix_size / num_threads;
    int extra_rows = matrix_size % num_threads;
    int current_start = 0;

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    // Создание потоков
    for (int i = 0; i < num_threads; i++) {
        tasks[i].start_row = current_start;
        tasks[i].end_row = current_start + base_rows + (i < extra_rows ? 1 : 0);
        pthread_create(&threads[i], NULL, matrix_multiply_section, &tasks[i]);
        current_start = tasks[i].end_row;
    }

    // Ожидание завершения всех потоков
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Расчет времени выполнения
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double time_spent = (end_time.tv_sec - start_time.tv_sec) * 1000.0 +
                       (end_time.tv_nsec - start_time.tv_nsec) / 1e6;
    return time_spent;
}

int main() {
    // Тестовые размеры матриц и числа потоков
    int test_sizes[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    int thread_options[] = {1, 2, 4, 8, 16};
    const int TOTAL_SIZES = sizeof(test_sizes)/sizeof(test_sizes[0]);
    const int TOTAL_THREADS = sizeof(thread_options)/sizeof(thread_options[0]);

    double results[TOTAL_THREADS][TOTAL_SIZES];
    memset(results, 0, sizeof(results));

    // Создание файла для результатов
    FILE *output_file = fopen("performance_results.tsv", "w");
    if (!output_file) {
        perror("Ошибка создания файла");
        return 1;
    }
    fprintf(output_file, "Размер\tПотоки\tВремя(мс)\n");

    // Основной цикл тестирования
    for (int size_idx = 0; size_idx < TOTAL_SIZES; size_idx++) {
        matrix_size = test_sizes[size_idx];
        for (int thread_idx = 0; thread_idx < TOTAL_THREADS; thread_idx++) {
            int threads = thread_options[thread_idx];
            if (threads > matrix_size) continue;  // Пропуск невалидных случаев
            
            create_matrices();
            initialize_matrices();
            double duration = execute_multiplication(threads);
            results[thread_idx][size_idx] = duration;
            
            printf("Размер: %d, Потоки: %d => Время: %.2f мс\n", 
                  matrix_size, threads, duration);
            fprintf(output_file, "%d\t%d\t%.2f\n", 
                   matrix_size, threads, duration);
            
            destroy_matrices();
        }
    }
    fclose(output_file);

    // Генерация скрипта для визуализации
    FILE *plot_script = fopen("visualize.gp", "w");
    if (!plot_script) {
        perror("Ошибка создания скрипта");
        return 1;
    }
    fprintf(plot_script, "set terminal png\n");
    fprintf(plot_script, "set output 'performance_graph.png'\n");
    fprintf(plot_script, "set title 'Зависимость времени умножения от размера матрицы'\n");
    fprintf(plot_script, "set xlabel 'Размер матрицы'\n");
    fprintf(plot_script, "set ylabel 'Время (мс)'\n");

    // Добавление данных для каждого числа потоков
    for (int t = 0; t < TOTAL_THREADS; t++) {
        int threads = thread_options[t];
        fprintf(plot_script, "$data%d << EOD\n", threads);
        for (int s = 0; s < TOTAL_SIZES; s++) {
            if (results[t][s] > 0) {
                fprintf(plot_script, "%d %.2f\n", test_sizes[s], results[t][s]);
            }
        }
        fprintf(plot_script, "EOD\n");
    }

    // Команда построения графика
    fprintf(plot_script, "plot ");
    for (int t = 0; t < TOTAL_THREADS; t++) {
        int threads = thread_options[t];
        fprintf(plot_script, "$data%d with lines title '%d потоков'", threads, threads);
        if (t < TOTAL_THREADS-1) fprintf(plot_script, ", ");
    }
    fclose(plot_script);

    // Автоматическое построение графика
    int status = system("gnuplot visualize.gp");
    if (status != 0) {
        printf("Ошибка: GNUplot не установлен или скрипт неверен\n");
    }

    return 0;
}
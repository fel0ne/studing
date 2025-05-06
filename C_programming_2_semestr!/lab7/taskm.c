#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// Глобальный мьютекс для синхронизации
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int N;
    int start_row;
    int end_row;
    int (*A)[];
    int (*B)[];
    int (*C)[];
} ThreadData;

void* multiply_part(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int N = data->N;
    int (*A)[N] = data->A;
    int (*B)[N] = data->B;
    int (*C)[N] = data->C;

    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            
            // Блокируем мьютекс для записи результата
            pthread_mutex_lock(&mutex);
            C[i][j] = sum;
            pthread_mutex_unlock(&mutex);
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <matrix size> <threads count>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int num_threads = atoi(argv[2]);

    // Инициализация матриц
    int (*A)[N] = malloc(N * N * sizeof(int));
    int (*B)[N] = malloc(N * N * sizeof(int));
    int (*C)[N] = malloc(N * N * sizeof(int));

    // Заполнение матриц
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = 1;
            B[i][j] = 1;
        }
    }

    // Создание потоков
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];
    int rows_per_thread = N / num_threads;
    int extra_rows = N % num_threads;

    int current_row = 0;
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].N = N;
        thread_data[i].A = A;
        thread_data[i].B = B;
        thread_data[i].C = C;
        thread_data[i].start_row = current_row;
        
        int rows = (i < extra_rows) ? rows_per_thread + 1 : rows_per_thread;
        thread_data[i].end_row = current_row + rows;
        current_row += rows;

        pthread_create(&threads[i], NULL, multiply_part, &thread_data[i]);
    }

    // Ожидание завершения
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Уничтожение мьютекса
    pthread_mutex_destroy(&mutex);

    // Вывод результатов
    if (N < 5) {
        printf("Matrix A:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) printf("%d ", A[i][j]);
            printf("\n");
        }
        printf("\nMatrix B:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) printf("%d ", B[i][j]);
            printf("\n");
        }
        printf("\nResult C:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) printf("%d ", C[i][j]);
            printf("\n");
        }
    }

    free(A);
    free(B);
    free(C);

    return 0;
}


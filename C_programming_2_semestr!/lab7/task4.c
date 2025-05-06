#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 4

// Глобальный мьютекс для синхронизации вывода
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int turn = 0;  // 0 - ход главного потока, 1 - ход дочернего

void messagedeth(void *arg) {
    pthread_mutex_lock(&mutex);
    printf("death: %ld\n", (unsigned long)arg);
    pthread_mutex_unlock(&mutex);
}

void *routine(void *arg) {
    pthread_cleanup_push(messagedeth, (void*)pthread_self());
    char **messages = (char **)arg;
    
    for (int i = 0; messages[i] != NULL; i++) {
        // Ждем своей очереди
        while (1) {
            pthread_mutex_lock(&mutex);
            if (turn == 1) break;
            pthread_mutex_unlock(&mutex);
           ///usleep(100);  // Короткая пауза, чтобы не нагружать CPU
        }
        
        printf("%s (TID: %ld)\n", messages[i], pthread_self());
        turn = 0;  // Передаем ход главному потоку
        pthread_mutex_unlock(&mutex);
    }
    
    pthread_cleanup_pop(1);
    return NULL;
}

int main(void) {
    char *thread_data[NUM_THREADS][3] = {
        {"Поток 1: Привет", "Поток 1: Пока", NULL},
        {"Поток 2: Работаю", "Поток 2: Завершаюсь", NULL},
        {"Поток 3: Строка 1", NULL},
        {"Поток 4: Данные", "Поток 4: Информация", NULL}
    };

    pthread_t threads[NUM_THREADS];
    
    // Создание потоков
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, routine, (void*)thread_data[i]);
    }

    // Главный поток выводит свои сообщения по очереди с дочерними
    for (int i = 0; i < 5; i++) {
        // Ждем своей очереди
        while (1) {
            pthread_mutex_lock(&mutex);
            if (turn == 0) break;
            pthread_mutex_unlock(&mutex);
            usleep(100);
        }
        
        printf("Главный поток %ld: сообщение %d\n", pthread_self(), i+1);
        turn = 1;  // Передаем ход дочерним потокам
        pthread_mutex_unlock(&mutex);
        
        // Даем время дочерним потокам
        usleep(100);
    }

    // Даем дочерним потокам завершиться
    sleep(3);
    
    // Отмена всех потоков
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_cancel(threads[i]);
    }

    // Ожидание завершения
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Уничтожение мьютекса
    pthread_mutex_destroy(&mutex);

    return 0;
}

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_THREADS 4
void  *messagedeth(a){
    
}

void *routine(void *arg) {
    char **messages = (char **)arg;
    for (int i = 0; messages[i] != NULL; i++) {
        sleep(3);
        printf("%s (TID: %ld)\n", messages[i], pthread_self());
        
    }
    return NULL;
}

int main(void) {
    // Уникальные наборы сообщений для каждого потока
    char *thread_data[NUM_THREADS][3] = {
        {"Поток 1: Привет", "Поток 1: Пока", NULL},
        {"Поток 2: Работаю",  "Поток 2: Завершаюсь", NULL},
        {"Поток 3: Строка 1", NULL},
        {"Поток 4: Данные", "Поток 4: Информация", NULL}
    };

    pthread_t threads[NUM_THREADS];

    // Создание потоков
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, routine, (void*)thread_data[i]);
    }

    // Ожидание завершения всех потоков
    // for (int i = 0; i < NUM_THREADS; i++) {
    //     pthread_join(threads[i], NULL);
    // }
    sleep(2);
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_cancel(threads[i]);
    }


    // Сообщения из главного потока
    for (int i = 0; i < 5; i++) {
        printf("Главный поток %ld: сообщение %d\n", pthread_self(), i+1);
    }

    return 0;
}
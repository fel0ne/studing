#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_SIZE 50

// Функция, которую выполняет каждый поток
void* sleep_and_print(void* arg) { // СПИМ И ПЕЧАТАЕМ  ТИПИКАЛ СТУДЕНТ SIBSUTIS ХАХАХАХАХ
    int value = *(int*)arg;
    usleep(value * 1000); // Засыпаем на value миллисекунд (для usleep - микросекунды) меньше 700 не раьотает
    printf("%d ", value);
    return NULL;
}

// SleepSort: создает поток для каждого элемента
void sleep_sort(int arr[], int size) {
    pthread_t threads[MAX_SIZE];
    
    // Создаем потоки
    for (int i = 0; i < size; i++) {
        pthread_create(&threads[i], NULL, sleep_and_print, &arr[i]);
    }
    
    // Ждем завершения всех потоков 
    for (int i = 0; i < size; i++) {
        pthread_join(threads[i], NULL);
    }
}

int main() {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3}; // Пример входного массива
    int size = sizeof(arr) / sizeof(arr[0]); // делаем по умному 
    
    printf("До сортировки: ");
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    
    printf("\nПосле SleepSort: ");
    sleep_sort(arr, size);
    
    printf("\n");
    return 0;
}
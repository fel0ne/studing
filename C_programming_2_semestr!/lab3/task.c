#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
int count_y_words(FILE *file) {
    int count = 0;
    int in_word = 0;
    char first_char = 0;
    char last_char = 0;
    int c;

    // Перемещаем указатель в начало файла
    rewind(file);

    while ((c = fgetc(file)) != EOF) {
        if (isalnum(c) ||c == '_' || c == '-') {
            if (!in_word) {
                in_word = 1;
                first_char = c;
            }
            last_char = c; // Обновляем last_char для каждого символа слова
        } else {
            if (in_word) {
                if (first_char == 'y' && last_char == 'y') {
                    count++;
                }
                in_word = 0;
            }
        }
    }

    // Проверка последнего слова
    if (in_word && first_char == 'y' && last_char == 'y') {
        count++;
    }

    return count;
}

int randomm(int a, int b) {
    return a + rand() % (b - a + 1);
}

void randomize(FILE *file) {
    int r = rand() % 10 + 5; // 5-14 строк
    
    for (int i = 0; i < r; i++) {
        int lens = (rand() % 10) + 1; // 1-10 символов
        char *s = malloc(lens + 1); // +1 для нуль-терминатора
        
        if (!s) {
            perror("Ошибка выделения памяти");
            exit(1);
        }
        
        for (int j = 0; j < lens; j++) {
            s[j] = (char)randomm(253, 255); // 'v','w','x'
        }
        s[lens] = '\0'; // Важно: завершаем строку
        
        fputs((char*)s, file);
        fputs("\n", file);
        free(s);
    }

}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    
    if (argc < 2) {
        fprintf(stderr, "Использование: %s <файл>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    
    if (file) {
        printf("Файл '%s' уже существует.\n", argv[1]);
        file = fopen(argv[1], "w+");
        randomize(file);
        printf("Файл '%s' заполнен.\n", argv[1]);
        printf("%d", count_y_words(file));
        fclose(file);
    } else {
        file = fopen(argv[1], "w");
        if (!file) {
            perror("Ошибка создания файла");
            return 1;
        }
        randomize(file);
        
        printf("Файл '%s' создан и заполнен.\n", argv[1]);
        printf("%d", count_y_words(file));
        fclose(file);
    }
    
    return 0;
}
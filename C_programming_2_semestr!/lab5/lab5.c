#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    char group[10];
    int marks[3];
} Student;

void create_file() {
    FILE *file = fopen("Wedomost.dat", "wb");
    if (!file) {
        perror("Ошибка открытия файла");
        exit(1);
    }

    int N;
    printf("Введите количество студентов: ");
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        Student s;
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        printf("\nСтудент %d:\n", i + 1);
        printf("Фамилия и инициалы: ");
        fgets(s.name, 50, stdin);
        s.name[strcspn(s.name, "\n")] = '\0';

        printf("Номер группы: ");
        fgets(s.group, 10, stdin);
        s.group[strcspn(s.group, "\n")] = '\0';

        printf("Оценки (3 числа через пробел): ");
        scanf("%d %d %d", &s.marks[0], &s.marks[1], &s.marks[2]);

        fwrite(&s, sizeof(Student), 1, file);
    }

    fclose(file);
    printf("\nФайл успешно создан.\n\n");
}

void search_in_file() {
    FILE *file = fopen("Wedomost.dat", "rb");
    if (!file) {
        perror("Ошибка открытия файла");
        exit(1);
    }

    int choice;
    printf("Поиск по:\n");
    printf("1 - Фамилия и инициалы\n");
    printf("2 - Номер группы\n");
    printf("3 - Оценка\n");
    printf("Выберите поле: ");
    scanf("%d", &choice);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    char search_str[50];
    int search_mark;
    switch (choice) {
        case 1:
            printf("Введите фамилию и инициалы: ");
            fgets(search_str, 50, stdin);
            search_str[strcspn(search_str, "\n")] = '\0';
            break;
        case 2:
            printf("Введите номер группы: ");
            fgets(search_str, 10, stdin);
            search_str[strcspn(search_str, "\n")] = '\0';
            break;
        case 3:
            printf("Введите оценку: ");
            scanf("%d", &search_mark);
            break;
        default:
            printf("Неверный выбор.\n");
            fclose(file);
            return;
    }

    Student s;
    int found = 0;

    while (fread(&s, sizeof(Student), 1, file) == 1) {
        int match = 0;
        switch (choice) {
            case 1:
                if (strcmp(s.name, search_str) == 0) match = 1;
                break;
            case 2:
                if (strcmp(s.group, search_str) == 0) match = 1;
                break;
            case 3:
                for (int i = 0; i < 3; i++)
                    if (s.marks[i] == search_mark) {
                        match = 1;
                        break;
                    }
                break;
        }
        if (match) {
            printf("\nНайден студент:\n");
            printf("Фамилия: %s\nГруппа: %s\nОценки: %d %d %d\n",
                   s.name, s.group, s.marks[0], s.marks[1], s.marks[2]);
            found = 1;
        }
    }

    if (!found) {
        printf("\nСовпадений не найдено.\n");
    }

    fclose(file);
}

int main() {
    create_file();
    search_in_file();
    return 0;
}
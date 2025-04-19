#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define N 5
#define len_n 6
#define len_g 7

typedef struct student {
    int number;
    unsigned char name[len_n];
    unsigned char group[len_g];
    int marks[3];
} student;

int randomm(int a, int b) {
    return a + rand() % (b - a + 1);
}

void randomizeParameters(student A[N]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < len_n-1; j++) {
            A[i].name[j] = randomm(97, 122); 
        }
        A[i].name[len_n-1] = '\0';

        for(int j = 0; j < 3; j++) {
            A[i].group[j] = randomm(48, 57); // цифры
        }
        for(int j = 3; j < len_g-1; j++) {
            A[i].group[j] = randomm(97, 122); // буквы
        }
        A[i].group[len_g-1] = '\0';

        for(int j = 0; j < 3; j++) {
            A[i].marks[j] = randomm(0, 100);
        }

        A[i].number = i + 1;
    }
}

void printStudent(student A) {
    printf("№%2d | Имя: %-5s | Группа: %-6s | Оценки: %3d %3d %3d\n", 
           A.number, A.name, A.group, A.marks[0], A.marks[1], A.marks[2]);
}

void printStudents(student A[N]) {
    printf("\nСписок студентов:\n");
    for(int i = 0; i < N; i++) {
        printStudent(A[i]);
    }
}

void create_file(student A[N]) {
    FILE *file = fopen("Wedomost.dat", "wb");
    if (!file) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    //for(int i = 0; i < N; i++) {
        if(fwrite(A, sizeof(student)*N, 1, file) != 1) {
            perror("Ошибка записи");
            fclose(file);
            exit(EXIT_FAILURE);
        }
    //}
    fclose(file);
    printf("\nФайл успешно создан.\n");
}

void search_in_file() {
    FILE *file = fopen("Wedomost.dat", "rb");
    if (!file) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    char search_name[len_n] = {0};
    char search_group[len_g] = {0};
    char mark_input[20] = {0};
    int search_mark = -1;

    printf("\nВведите критерии поиска (оставьте пустым для любого значения):\n");

    // Ввод имени
    printf("Имя (макс %d симв.): ", len_n-1);
    fgets(search_name, len_n, stdin);
    search_name[strcspn(search_name, "\n")] = '\0';

    // Очистка буфера если введено больше символов
    if(strlen(search_name) == len_n-1) 
        while(getchar() != '\n');

    // Ввод группы
    printf("Группа (макс %d симв.): ", len_g-1);
    fgets(search_group, len_g, stdin);
    search_group[strcspn(search_group, "\n")] = '\0';
    
    if(strlen(search_group) == len_g-1) 
        while(getchar() != '\n');

    // Ввод оценки
    printf("Оценка (0-100, Enter для пропуска): ");
    fgets(mark_input, sizeof(mark_input), stdin);
    if(sscanf(mark_input, "%d", &search_mark) != 1 || search_mark < 0 || search_mark > 100) {
        search_mark = -1;
    }

    student s;
    int found = 0;
    int total_conditions = 0;

    printf("\nРезультаты поиска:\n");
    while(fread(&s, sizeof(student), 1, file) == 1) {
        int name_match = 1;
        int group_match = 1;
        int mark_match = 1;

    
        if(strlen(search_name) > 0) {
            name_match = (strcmp(s.name, search_name) == 0);
            total_conditions++;
        }

 
        if(strlen(search_group) > 0) {
            group_match = (strcmp(s.group, search_group) == 0);
            total_conditions++;
        }

        if(search_mark != -1) {
            mark_match = 0;
            for(int i = 0; i < 3; i++) {
                if(s.marks[i] == search_mark) {
                    mark_match = 1;
                    break;
                }
            }
            total_conditions++;
        }

        if(name_match && group_match && mark_match) {
            printStudent(s);
            found = 1;
        }
    }

    if(total_conditions == 0) {
        printf("Не задано ни одного критерия поиска!\n");
    }
    else if(!found) {
        printf("Совпадений не найдено.\n");
    }
    
    fclose(file);
}

int main() {
    srand(time(NULL));
    student A[N];
    
    randomizeParameters(A);
    printStudents(A);
    create_file(A);
    search_in_file();
    
    return 0;
}
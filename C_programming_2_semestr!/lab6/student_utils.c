#include "student.h"

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
            A[i].group[j] = randomm(48, 57);
        }
        for(int j = 3; j < len_g-1; j++) {
            A[i].group[j] = randomm(97, 122);
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

    if(fwrite(A, sizeof(student)*N, 1, file) != 1) {
        perror("Ошибка записи");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    
    fclose(file);
    printf("\nФайл успешно создан.\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 100


struct Student{
    char student_name[64];
    signed char math_score; //Оценка по математике (0-100) 
    signed char physics_score; //Оценка по физике (0-100) 
    signed char inf_score; //Оценка по информатике (0-100)
    int total_score; //Общий балл (0-300);
};

struct Student addNewStudent(char *name, signed char math, signed char phy, signed char inf ){
    struct Student newStudent;
    for(int i = 0; i < 64; i++){
        newStudent.student_name[i] = name[i];
    }
        
    newStudent.math_score = math;
    newStudent.physics_score = phy;
    newStudent.inf_score = inf;
    newStudent.total_score = math + phy + inf;  
    return (newStudent); 
}

void printStudentInfo(struct Student student){
    printf("имя: %s   общий балл: %d \n", student.student_name, student.total_score);
}

void selectionSort(struct Student *students,int *ts) {
    int t1 = clock();
    for (int i = 0; i < N-1; i++) {
        int index = i;
        struct Student max_element = students[i];
        
        for (int j = i + 1; j < N; j++) {
            if (max_element.total_score < students[j].total_score) {
                max_element = students[j];
                index = j;
            }
        }
        
        // Меняем местами максимальный элемент с элементом на позиции i
        if (index != i) {
            struct Student buf = students[i]; 
            students[i] = students[index];
            students[index] = buf;
        }
    }
    int t2 = clock();
    *ts = t2-t1;
}

void countingSort(struct Student *students, int *tc){
    int t1 = clock();
    int max_element = 300;
    int help_array[max_element+1];
    struct Student new_students[N];
    for (int i = 0; i < max_element+1; i++) {
        help_array[i] = 0;
    }
    for (int i = 0; i < N; i++) {
        help_array[students[i].total_score]++;
    }
    for (int i = 1; i < max_element+1; i++) {
        help_array[i] += help_array[i-1];
    } 
    for (int i = 0; i < N; i++) {
        new_students[help_array[students[i].total_score]-1] = students[i];
        help_array[students[i].total_score]--;
    }
    for (int i = 0; i < N; i++) {
        students[i] = new_students[i];
    }
    int t2 = clock();

    *tc = t2-t1;
    
}

void Fill(struct Student *students){
    for (int i = 0; i < N; i++){
        int size_name = 5 + 5;//rand() % ((64 + 1) - 5);
        char name[size_name+1];
        name[0] = 'A' + rand()%26;
        for(int i = 1; i < size_name; i++){
           name[i] = 'a' + rand()%26;
        }
        name[size_name] = '\0';
        students[i] = addNewStudent(name, rand()%101, rand()%101, rand()%101);
    }
}

int main(){
    srand(time(NULL));

    struct Student students[N];
    Fill(students);

    printf("До сортировки:\n");
    for (int i = 0; i < N; i++) {
        printStudentInfo(students[i]);
    }

    int ts;
    selectionSort(students,&ts);

    Fill(students);
    int tc;
    countingSort(students,&tc);
    
    printf("после сортировки:\n");
    for (int i = 0; i < N; i++) {
        printStudentInfo(students[i]);
    }

    printf("\n");
    printf("counting %f sec", ((float)tc)/ CLOCKS_PER_SEC);
    printf("\n");
    printf("selection %f sec", ((float)ts)/ CLOCKS_PER_SEC);
    printf("\n");
    printf("\n");

    system("sed '5!d' /proc/cpuinfo");
    system("sed '8!d' /proc/cpuinfo");


}
// A + rand() % ((B + 1) - A)
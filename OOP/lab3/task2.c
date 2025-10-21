#include <string>
#include <fstream>
#include <iostream>
#include <cstring> 

using namespace std;

class Student{
private:
    char name[50]; 
    float sem_1;
    float sem_2;
    float sem_3;
    float sem_4;
    float sem_5;
    float sem_6;
    float sem_7;
    float sem_8;
    float sem_9;
    float sem_10;

public:
    Student(){
        strcpy(name, "");
        sem_1 = 0;
        sem_2 = 0;
        sem_3 = 0;
        sem_4 = 0;
        sem_5 = 0;
        sem_6 = 0;
        sem_7 = 0;
        sem_8 = 0;
        sem_9 = 0;
        sem_10 = 0;
    }


    string getName() {return string(name);}
    float getSem1() {return sem_1;}
    float getSem2() {return sem_2;}
    float getSem3() {return sem_3;}
    float getSem4() {return sem_4;}
    float getSem5() {return sem_5;}
    float getSem6() {return sem_6;}
    float getSem7() {return sem_7;}
    float getSem8() {return sem_8;}
    float getSem9() {return sem_9;}
    float getSem10() {return sem_10;}

    void setName(string temp) {strncpy(name, temp.c_str(), 49); name[49] = '\0';}
    void setSem1(float temp) {sem_1 = temp;}
    void setSem2(float temp) {sem_2 = temp;}
    void setSem3(float temp) {sem_3 = temp;}
    void setSem4(float temp) {sem_4 = temp;}
    void setSem5(float temp) {sem_5 = temp;}
    void setSem6(float temp) {sem_6 = temp;}
    void setSem7(float temp) {sem_7 = temp;}
    void setSem8(float temp) {sem_8 = temp;}
    void setSem9(float temp) {sem_9 = temp;}
    void setSem10(float temp) {sem_10 = temp;}

    float calculateAverage() {
        return (sem_1 + sem_2 + sem_3 + sem_4 + sem_5 + 
                sem_6 + sem_7 + sem_8 + sem_9 + sem_10) / 10.0f;
    }

    void outputTo() {
        cout << "Студент: " << name << endl;
        cout << "Оценки за семестры: ";
        cout << sem_1 << " " << sem_2 << " " << sem_3 << " " << sem_4 << " " << sem_5 << " "
             << sem_6 << " " << sem_7 << " " << sem_8 << " " << sem_9 << " " << sem_10 << endl;
        cout << "Средний балл: " << calculateAverage() << endl;
        cout << "------------------------" << endl;
    }
};

int main(){
    

    int studentCount = 0;

    fstream FileCount;
    FileCount.open("base_bin.dat", ios::in | ios::binary); 

    if (!FileCount) {
        cerr << "Не удалось открыть файл base_bin.dat для подсчета." << endl;
        return 1;
    }
    
    Student tempStudent;
    while (FileCount.read((char*)&tempStudent, sizeof(Student))) {
        studentCount++;
    }

  
    if (!FileCount.eof() && FileCount.fail()) {
         cerr << "Ошибка чтения при подсчете данных из base_bin.dat." << endl;
         FileCount.close();
         return 1;
    }
    
    FileCount.close(); 
    
    // Если файл пуст
    if (studentCount == 0) {
        cout << "Файл base_bin.dat пуст." << endl;
        return 0;
    }

    cout << "Количество студентов: " << studentCount << endl;


    Student* readStudents = new Student[studentCount];
    

    fstream FileRead;
    FileRead.open("base_bin.dat", ios::in | ios::binary); 
    
    if (!FileRead) {
         cerr << "Не удалось открыть файл base_bin.dat для чтения данных." << endl;
         delete[] readStudents;
         return 1;
    }
    
    for (int i = 0; i < studentCount; i++) {
        if (!FileRead.read((char*)&readStudents[i], sizeof(Student))) {
            cerr << "Ошибка чтения данных студента " << i << " из base_bin.dat." << endl;
            delete[] readStudents;
            FileRead.close();
            return 1;
        }
    }
    FileRead.close(); 
    

    for (int i = 0; i < studentCount; i++) {
        readStudents[i].outputTo();
    }
    

    fstream FileOut;
    FileOut.open("base_bin_bin.dat", ios::binary|ios::out);
    
    if (!FileOut) {
         cerr << "Не удалось открыть файл base_bin_bin.dat" << endl;
         delete[] readStudents; 
         return 1;
    }
    
    for (int i = 0; i < studentCount; i++) {

        FileOut.write((char*)&readStudents[i], sizeof(Student));
        

        float average = readStudents[i].calculateAverage();
        FileOut.write((char*)&average, sizeof(average));
    }
    FileOut.close();
    
    delete[] readStudents; 
    
    return 0;
}
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Student{
private:
        string name;
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
            name = "";
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

    //-----getters-----
    string getName() {return name;}
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

    //----setters----
    void setName(string temp) {name = temp;}
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

    // Метод для расчета среднего балла
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
    fstream File;
    File.open("base.txt", ios::in); 

    if (File){
        int studentCount;
        File >> studentCount;
        File.ignore(); 
        
        cout << "Количество студентов: " << studentCount << endl;
        
        Student students[studentCount]; 
        string name;
        float grades[10];
        for (int i = 0; i < studentCount; i++) {
            
            if (!getline(File, name)) {
                cerr << "Ошибка чтения имени студента " << i+1 << endl;
                break;
            }
            students[i].setName(name);
            
            for (int j = 0; j < 10; j++) {
                if (!(File >> grades[j])) {
                    cerr << "Ошибка чтения оценки " << j+1 << " для студента " << i+1 << endl;
                    break;
                }
            }
            File.ignore(); 
            
   
            students[i].setSem1(grades[0]);
            students[i].setSem2(grades[1]);
            students[i].setSem3(grades[2]);
            students[i].setSem4(grades[3]);
            students[i].setSem5(grades[4]);
            students[i].setSem6(grades[5]);
            students[i].setSem7(grades[6]);
            students[i].setSem8(grades[7]);
            students[i].setSem9(grades[8]);
            students[i].setSem10(grades[9]);
        }

        for (int i = 0; i < studentCount; i++) {
            students[i].outputTo();
        }
        
        File.close(); 
        
        File.open("base_bin.dat", ios::binary|ios::out);
        
        
        for (int i = 0; i < studentCount; i++) {
            File.write((char*)&students[i],sizeof(students[i]));
            //float average =students[i].calculateAverage();
            //File.write((char*)&average,sizeof(students[i].calculateAverage()));

        }

        
        
        
    } else {
        cerr << "Не удалось открыть файл base.txt" << endl;
        return 1;
    }
    
    return 0;
}
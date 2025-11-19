#include <iostream>
#include <string>
#include <cmath>
#include <limits> 

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Константа для точного значения корня из 3
#ifndef M_SQRT3
#define M_SQRT3 1.7320508075688772935274463415059 
#endif
using namespace std;


struct point{
    float x;
    float y;
}typedef point;

class Triangle{
    public:
        point A;
        point B;
        point C;
        Triangle(){
            A.x = 0;
            A.y = 0;
           
            B.x = 0;
            B.y = 0;

            C.x = 0;
            C.y = 0;
        }

        Triangle(float ax, float ay, float bx, float by, float cx, float cy){
            A.x = ax;
            A.y = ay;
           
            B.x = bx;
            B.y = by;

            C.x = cx;
            C.y = cy;
        }
        void outputToPoints(){
            cout<<"---- Вершина A ----"<<endl;
            cout<<"координата X:"<<A.x<<endl;
            cout<<"координата Y:"<<A.y<<endl<<endl;
            cout<<"---- Вершина B ----"<<endl;
            cout<<"координата X:"<<B.x<<endl;
            cout<<"координата Y:"<<B.y<<endl<<endl;
            // ИЗМЕНЕНИЕ 3: Исправлена опечатка 'Вершина A' на 'Вершина C'
            cout<<"---- Вершина C ----"<<endl; 
            cout<<"координата X:"<<C.x<<endl;
            cout<<"координата Y:"<<C.y<<endl<<endl;           
        }


        void setAX(float X){A.x = X;} 
        void setAY(float Y){A.y = Y;}   

        void setBX(float X){B.x = X;} 
        void setBY(float Y){B.y = Y;}         

        void setCX(float X){C.x = X;} 
        void setCY(float Y){C.y = Y;}         
       
        
        float getAX(){return A.x;} 
        float getAY(){return A.y;}   

        float getBX(){return B.x;} 
        float getBY(){return B.y;} 

        float getCX(){return C.x;} 
        float getCY(){return C.y;} 

        float length(point Pa, point Pb){
            float leng = pow(((Pb.x - Pa.x)*(Pb.x - Pa.x)+(Pb.y-Pa.y)*(Pb.y-Pa.y)),0.5);
            return leng; 
        } 

        void lengths(){
            cout<<"|AB| = "<<length(A,B)<<endl;
            cout<<"|BC| = "<<length(B,C)<<endl;
            cout<<"|CA| = "<<length(C,A)<<endl<<endl;
        } 

        int isTriangle(){
            float ab = length(A,B);
            float bc = length(B,C);
            float ca = length(C,A);
           
            if (ab + bc > ca && ab + ca > bc && bc + ca > ab){
                return 1;
            }
            else{
                return 0;
            }
        }
        float perimetr(){
            return(length(A,B)+length(B,C)+length(C,A));
        }
        void angles(){
            float ab = length(A,B);
            float bc = length(B,C);
            float ca = length(C,A);
           
            float angle_A = acos((ca*ca + ab*ab - bc*bc) / (2 * ca * ab));
            float angle_B = acos((ab*ab + bc*bc - ca*ca) / (2 * ab * bc));
            float angle_C = acos((ca*ca + bc*bc - ab*ab) / (2 * ca * bc));
           
            angle_A = angle_A * 180 / M_PI;
            angle_B = angle_B * 180 / M_PI;
            angle_C = angle_C * 180 / M_PI;
           
            cout<<"Угол A = "<<angle_A<<endl;
            cout<<"Угол B = "<<angle_B<<endl;
            cout<<"Угол C = "<<angle_C<<endl;
        }
        float ploshad(){
            float h_p = perimetr()/2;
            float S = pow(h_p*(h_p-length(A,B))*(h_p-length(B,C))*(h_p-length(C,A)),0.5);
            return(S);
        }
        void outputTo(){
            if(isTriangle() == 1){
                outputToPoints();
                cout<<endl<<"Это треугольник!"<<endl<<endl;
                lengths();
                cout<<"Периметр: "<<perimetr()<<endl;
                cout<<"Площадь: "<<ploshad()<<endl;
                angles();
            }
            else{
                outputToPoints();
                cout<<"Это не треугольник!"<<endl<<endl;
            }

        }
};



class EquilateralTriangle : public Triangle {
    public:
        float medianLength(){
            point M; 
     
            M.x = (B.x + C.x) / 2.0;
            M.y = (B.y + C.y) / 2.0;
           
            return length(A, M);
        }

        bool isEquilateral(){
            if (!isTriangle()) return 0;
           
            float ab = length(A,B);
            float bc = length(B,C);
            float ca = length(C,A);
            float p=1e-3; 
            if(fabs(ab - bc) < p && fabs(bc - ca) < p && fabs(ca - ab) < p){
                return (1);
            }
            else{
                return(0);
            } 
        }

        EquilateralTriangle() : Triangle() {}
       
        
        EquilateralTriangle(float ax, float ay, float bx, float by, float cx, float cy) : Triangle(ax, ay, bx, by, cx, cy) {}
        
         
        void outputTo() {
            if (isTriangle() && isEquilateral() == 1) {
                cout << "=== РАВНОСТОРОННИЙ ТРЕУГОЛЬНИК ===" << endl;
                Triangle::outputTo();
                cout << "Длина медианы: " << medianLength() << endl;
                cout << "Длина высоты: " << heightLength() << endl;
                cout << "Длина биссектрисы: " << bisectorLength() << endl;
                cout << "Радиус вписанной окружности: " << inscribedCircleRadius() << endl;
                cout << "Радиус описанной окружности: " << circumscribedCircleRadius() << endl;
            } else {
                cout << "Ошибка: Это не равносторонний треугольник! (или не треугольник)" << endl;
            }
        }
       
       
        float heightLength() {
            // В равностороннем треугольнике высота = медиана = биссектриса
            return (length(A, B) * M_SQRT3 / 2);
        }
       
        float bisectorLength() {
            // В равностороннем треугольнике все биссектрисы равны
            return heightLength();
        }
       
     
        float inscribedCircleRadius() {
            return length(A, B) * M_SQRT3 / 6;
        }
       

        float circumscribedCircleRadius() {
            return length(A, B) * M_SQRT3 / 3;
        }
};


void findEquilateralWithMinMedian(EquilateralTriangle equilateralTriangles[], int M) {
    cout << "\n=== Поиск равностороннего треугольника с наименьшей медианой ===" << endl;
   
    if (M <= 0) {
        cout << "Равносторонних треугольников не найдено" << endl;
        return;
    }
   
    float minMedian = numeric_limits<float>::max();
    int index = -1;
   
    for (int i = 0; i < M; i++) {
       
        if (equilateralTriangles[i].isEquilateral() && equilateralTriangles[i].isTriangle()) { 
            float median = equilateralTriangles[i].medianLength();
            cout << "Равносторонний треугольник " << i + 1 << " имеет медиану: " << median << endl;
           
            if (median < minMedian) {
                minMedian = median;
                index = i;
            }
        }
    }
   
    if (index != -1) {
        cout << "Равносторонний треугольник с наименьшей медианой (" << minMedian << "): №" << index + 1 << endl;
        cout << "Информация об этом треугольнике:" << endl;
        equilateralTriangles[index].outputTo();
    } else {
        cout << "Действительных равносторонних треугольников не найдено" << endl;
    }
}

void findIdenticalTriangles(Triangle triangles[], int N) {
    cout << "\n=== Поиск одинаковых треугольников ===" << endl;
    bool found = 0;
   
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (!triangles[i].isTriangle() || !triangles[j].isTriangle()) continue;
           
            float ab1 = triangles[i].length(triangles[i].A, triangles[i].B);
            float bc1 = triangles[i].length(triangles[i].B, triangles[i].C);
            float ca1 = triangles[i].length(triangles[i].C, triangles[i].A);
           
            float ab2 = triangles[j].length(triangles[j].A, triangles[j].B);
            float bc2 = triangles[j].length(triangles[j].B, triangles[j].C);
            float ca2 = triangles[j].length(triangles[j].C, triangles[j].A);
           

            bool identical = 0;
            float epsilon = 0.01; 
           
            if ((fabs(ab1 - ab2) < epsilon && fabs(bc1 - bc2) < epsilon && fabs(ca1 - ca2) < epsilon) ||
                (fabs(ab1 - ab2) < epsilon && fabs(bc1 - ca2) < epsilon && fabs(ca1 - bc2) < epsilon) ||
                (fabs(ab1 - bc2) < epsilon && fabs(bc1 - ab2) < epsilon && fabs(ca1 - ca2) < epsilon) ||
                (fabs(ab1 - bc2) < epsilon && fabs(bc1 - ca2) < epsilon && fabs(ca1 - ab2) < epsilon) ||
                (fabs(ab1 - ca2) < epsilon && fabs(bc1 - ab2) < epsilon && fabs(ca1 - bc2) < epsilon) ||
                (fabs(ab1 - ca2) < epsilon && fabs(bc1 - bc2) < epsilon && fabs(ca1 - ab2) < epsilon)) {
                identical = 1;
            }
           
            if (identical) {
                cout << "Треугольники " << i + 1 << " и " << j + 1 << " одинаковы" << endl;
                found = 1;
            }
        }
    }
   
    if (!found) {
        cout << "Одинаковых треугольников не найдено" << endl;
    }
}

int main(){
    

    cout << "=== Демонстрация работы класса Triangle ===" << endl;
    Triangle triangle1;
    triangle1.outputTo();

    triangle1.setAX(2);
    triangle1.setAY(2);
    triangle1.setBX(6);
    triangle1.setBY(10);
    triangle1.setCX(10);
    triangle1.setCY(4);

    cout << endl << "После установки координат:" << endl;
    triangle1.outputTo();
   
    
    const int N = 4;
    cout << "\n=== Работа с массивом из " << N << " обычных треугольников ===" << endl;
    Triangle triangles[N];
   
   
    triangles[0] = Triangle(0, 0, 1, 0, 0, 1); 
    
    triangles[1] = Triangle(0.0f, 0.0f, 2.0f, 0.0f, 1.0f, M_SQRT3); 
    triangles[2] = Triangle(0, 0, 1, 0, 0, 1); 
    triangles[3] = Triangle(1, 1, 4, 1, 2, 4); 
   
    // Выводим информацию о всех треугольниках
    for (int i = 0; i < N; i++) {
        cout << "\n--- Треугольник " << i + 1 << " ---" << endl;
        triangles[i].outputToPoints();
        cout << "Существует: " << (triangles[i].isTriangle() ? "Да" : "Нет") << endl;
        if (triangles[i].isTriangle()) {
            cout << "Периметр: " << triangles[i].perimetr() << endl;
            cout << "Площадь: " << triangles[i].ploshad() << endl;
        }
    }
   
    // Создаем M равносторонних треугольников через массив
    const int M = 3;
    cout << "\n=== Работа с массивом из " << M << " равносторонних треугольников ===" << endl;
    EquilateralTriangle equilateralTriangles[M];
   
   
    equilateralTriangles[0] = EquilateralTriangle(0.0f, 0.0f, 2.0f, 0.0f, 1.0f, M_SQRT3);
   
    equilateralTriangles[1] = EquilateralTriangle(1.0f, 1.0f, 3.0f, 1.0f, 2.0f, 1.0f + M_SQRT3); 
    
    equilateralTriangles[2] = EquilateralTriangle(0.0f, 0.0f, 5.0f, 0.0f, 2.5f, 5.0f * M_SQRT3 / 2.0f);
   
    
    for (int i = 0; i < M; i++) {
        cout << "\n--- Равносторонний треугольник " << i + 1 << " ---" << endl;
        equilateralTriangles[i].outputTo();
    }
   
    // Поиск одинаковых треугольников
    findIdenticalTriangles(triangles, N);
   
    // Поиск равностороннего треугольника с наименьшей медианой
    findEquilateralWithMinMedian(equilateralTriangles, M);
   
    return 0;
}
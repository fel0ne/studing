#include<iostream>
#include<string>
using namespace std;

class Porabola {
    //Поля класса
    private:
    int a;
    int b;
    int c;
    //double min;

    public:
    //Конструктор (инициализация)
    Porabola (int A,int B,int C) {
        a = A;
        b = B;
        c = C;
    }

    Porabola (){
        a = 0;
        b = 0;
        c = 0;
    }


    int get_minimum(){
        if (a > 0){
            return(-1*(b/2*a));
        }
        else{
            return(NULL);
        }
    }
    //Метод для вывода информации в консоль
    void outputTo() {
        //Здесь команды вывода значений всех полей объекта на экран
        cout<<"a: "<<a<<endl;
        cout<<"b: "<<b<<endl;
        cout<<"c: "<<c<<endl;
    }


    //Метод для получения значения a
    int get_a() {
        return a;
    }
    //Метод для изменения значения a
    void set_a(int A) {
        a=A;
    }


    //Метод для получения значения b
    int get_b() {
        return b;
    }
    //Метод для изменения значения b
    void set_b(int B) {
        b=B;
    }


    //Метод для получения значения c
    int get_c() {
        return c;
    }
    //Метод для изменения значения c
    void set_c(int C) {
        c=C;
    }


    
   
};

int main() {
    int m;
    // cout<<"m = ";
    // cin>> m;  

    // Porabola arr[m];
    
    // int a;
    // int b;
    // int c;

    // for(int i = 0; i<m-1;i++){
    //     cout<<"a = ";
    //     cin>>a;
    //     cout<<"b = ";
    //     cin>>b;
    //     cout<<"c = ";
    //     cin>>c;

    //     arr[i] = Porabola(a,b,c);
    // }
    // arr[m] = Porabola();


    int k = 0;
    Porabola aaa;
    aaa.outputTo();
    /*int index = NULL;
    int min = NULL;
    for(int i = 0; i<m-1;i++){
        if (arr[i].get_minimum() != NULL){
            k++;
            if (index == NULL){
                index = i;
                min = arr[i].get_minimum();
            }
            else{
                if (arr[i].get_minimum() > min){
                    index = i;
                    min = arr[i].get_minimum();
                }
            }
        }
    }
    cout<<k<<endl;
    cout<<index<<endl;
    cout<<min<<endl;


*/
}

//55555555555555555555
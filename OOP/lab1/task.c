#include<iostream>
#include<string>
using namespace std;

class Firma_Proizvoditel {
    //Поля класса
    private:
    string country;
    string type;
    
    public:
    //Конструктор (инициализация)
    Firma_Proizvoditel (string c, string t) {
        country = c;
        type = t;
    }
    //Метод для вывода информации в консоль
    void outputTo() {
        //Здесь команды вывода значений всех полей объекта на экран
        cout<<"страна: "<<country<<endl;
        cout<<"тип оборудования: "<<type<<endl;
    }
    //Метод для получения значения страна
    string get_country() {
        return country;
    }
    //Метод для изменения значения страна
    void set_country(string c) {
        country=c;
    }
    //Метод для получения значения тип оборудования
    string get_type() {
        return type;
    }
    //Метод для изменения значения тип оборудования
    void set_type(string t) {
        type=t;
    }
};

int main() {
    string c;
    string t;
    cout<<"введите страну прроизводитель для обьекта созданного динмически:";
    cin>>c;
    cout<<"введите тип для обьекта созданного динмически:";
    cin>>t;
    Firma_Proizvoditel * dyn = new Firma_Proizvoditel(c,t);
    
    cout<<"введите страну прроизводитель для обьекта созданного статический:";
    cin>>c;
    cout<<"введите тип для обьекта созданного статически:";
    cin>>t;
    Firma_Proizvoditel  stat =  Firma_Proizvoditel(c,t);

    dyn->outputTo();
    stat.outputTo();

    cout<<endl;


    cout<<"введите страну прроизводитель для обьекта созданного динмически:";
    cin>>c;
    cout<<"введите тип для обьекта созданного динмически:";
    cin>>t;
    dyn->set_country(c);
    dyn->set_type(t);


    cout<<"введите страну прроизводитель для обьекта созданного статически:";
    cin>>c;
    cout<<"введите тип для обьекта созданного статически:";
    cin>>t;

    
    stat.set_country(c);
    stat.set_type(t);

    cout<<"Динамика: страна:"<<dyn->get_country()<<" тип: "<<dyn->get_type()<<endl;
    cout<<"статика: страна:"<<stat.get_country()<<" тип: "<<stat.get_type()<<endl;

    free(dyn);    
}

//55555555555555555555
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Hotel{
    public:
        string name;
        int count_place;
        int count_placed;
        int coast;

        Hotel(){
            name = "";
            count_place = 0;
            count_placed = 0;
            coast = 0;
        }

        Hotel(string tname, int tcount_place, int tcount_placed, int tcoast){
            name = tname;
            count_place = tcount_place;
            count_placed = tcount_placed;
            coast = tcoast;
        }

        void setName(string tname){
            name = tname;
        }

        void setCount_place(int tcount_place){
            count_place = tcount_place;
        }

        void setCount_placed(int tcount_placed){
            count_placed = tcount_placed;
        }

        void setCoast(int tcoast){
            coast = tcoast;
        }

        string getName(){
            return name;
        }

        int getCount_place(){
            return count_place;
        }

        int getCount_placed(){
            return count_placed;
        }

        int getCoast(){
            return coast;
        }

        void outputTo(){
            cout<<"Название гостиницы: "<<name<<endl;
            cout<<"Общее число мест: "<<count_place<<endl;
            cout<<"Число заселенных мест: "<<count_placed<<endl;
            cout<<"Оплата за день проживания: "<<coast<<endl;
            cout<<"Убытки за месяц: "<<getUbytok()<<endl;
        }

        double getUbytok(){
            return coast * (count_place - count_placed) * 30;
        }
};


bool compareByUbytok(Hotel a, Hotel b) {
    return a.getUbytok() > b.getUbytok(); 
}

int main(){
    Hotel* hotel1 = new Hotel();
    Hotel* hotel2 = new Hotel();

    Hotel hotel3;
    Hotel hotel4;

    fstream File;
    File.open("gost.txt", ios::in);

    if (!File.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return 1;
    }

    string temp_name;
    int temp_place;
    int temp_placed;
    int temp_coast;

    File >> temp_name >> temp_place >> temp_placed >> temp_coast;
    hotel1->setName(temp_name);
    hotel1->setCount_place(temp_place);
    hotel1->setCount_placed(temp_placed);
    hotel1->setCoast(temp_coast);

    File >> temp_name >> temp_place >> temp_placed >> temp_coast;
    hotel2->setName(temp_name);
    hotel2->setCount_place(temp_place);
    hotel2->setCount_placed(temp_placed);
    hotel2->setCoast(temp_coast);


    File >> temp_name >> temp_place >> temp_placed >> temp_coast;
    hotel3.setName(temp_name);
    hotel3.setCount_place(temp_place);
    hotel3.setCount_placed(temp_placed);
    hotel3.setCoast(temp_coast);

    File >> temp_name >> temp_place >> temp_placed >> temp_coast;
    hotel4.setName(temp_name);
    hotel4.setCount_place(temp_place);
    hotel4.setCount_placed(temp_placed);
    hotel4.setCoast(temp_coast);

    File.close();


    cout << "Все гостиницы:" << endl;
    hotel1->outputTo();
    cout << endl;
    hotel2->outputTo();
    cout << endl;
    hotel3.outputTo();
    cout << endl;
    hotel4.outputTo();
    cout << endl;

    vector<Hotel> hotelsWithBigUbytok;

    if (hotel1->getUbytok() > 1000000) {
        hotelsWithBigUbytok.push_back(*hotel1);
    }
    if (hotel2->getUbytok() > 1000000) {
        hotelsWithBigUbytok.push_back(*hotel2);
    }
    if (hotel3.getUbytok() > 1000000) {
        hotelsWithBigUbytok.push_back(hotel3);
    }
    if (hotel4.getUbytok() > 1000000) {
        hotelsWithBigUbytok.push_back(hotel4);
    }

    sort(hotelsWithBigUbytok.begin(), hotelsWithBigUbytok.end(), compareByUbytok);

 
    cout << "Гостиницы с убытками > 1 млн (отсортированные по убыванию убытков):" << endl;
    for (size_t i = 0; i < hotelsWithBigUbytok.size(); i++) {
        hotelsWithBigUbytok[i].outputTo();
        cout << endl;
    }

    
    cout << "Введите данные для новой гостиницы:" << endl;
    cout << "Название: ";
    cin >> temp_name;
    cout << "Общее число мест: ";
    cin >> temp_place;
    cout << "Число заселенных мест: ";
    cin >> temp_placed;
    cout << "Оплата за день: ";
    cin >> temp_coast;

    Hotel newHotel(temp_name, temp_place, temp_placed, temp_coast);

    if (newHotel.getUbytok() > 1000000) {
        hotelsWithBigUbytok.push_back(newHotel);
        sort(hotelsWithBigUbytok.begin(), hotelsWithBigUbytok.end(), compareByUbytok);
    }

    File.open("gost.txt", ios::app);
    if (File.is_open()) {
        File << endl << temp_name << endl << temp_place << endl << temp_placed << endl << temp_coast;
        File.close();
        cout << "Данные успешно добавлены в файл." << endl;
    } else {
        cout << "Ошибка открытия файла для дозаписи!" << endl;
    }


    cout << "Обновленный список гостиниц с убытками > 1 млн:" << endl;
    for (size_t i = 0; i < hotelsWithBigUbytok.size(); i++) {
        hotelsWithBigUbytok[i].outputTo();
        cout << endl;
    }

  
    delete hotel1;
    delete hotel2;

    return 0;
}
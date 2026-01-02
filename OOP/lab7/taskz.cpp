#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

class Shop {
public:
    string name;
    string address;
    string workTime;
    string type;

    Shop() {}

    Shop(string n, string a, string wt, string t) {
        name = n;
        address = a;
        workTime = wt;
        type = t;
    }

    void print() {
        cout << "Название: " << name << endl;
        cout << "Адрес: " << address << endl;
        cout << "Время работы: " << workTime << endl;
        cout << "Тип инструментов: " << type << endl;
        cout << "------------------------" << endl;
    }
};

int main() {
    int N;
    cout << "Введите количество объектов: ";
    cin >> N;

    ifstream file("instrument.txt");
    if (!file.is_open()) {
        cout << "Ошибка! Не удалось открыть файл instrument.txt" << endl;
        return 0;
    }

    stack<Shop> shops;

    string name, address, time, type;
    Shop s;
    for (int i = 0; i < N; i++) {
        file >> name >> address >> time >> type;

        s = Shop(name, address, time, type);
        shops.push(s);
    }

    file.close();

    cout << "\nСодержимое стека:\n";

    while (!shops.empty()) {
        shops.top().print();
        shops.pop();
    }

    return 0;
}

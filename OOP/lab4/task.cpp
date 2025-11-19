#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Firma_Proizvoditel {
private:
    string country;
    string type;
        
public:
    Firma_Proizvoditel() {
        country = "";
        type = ""; 
    }

    Firma_Proizvoditel(string c, string t) {
        country = c;
        type = t;
    }

    void outputTo() {
        cout << "страна: " << country << endl;
        cout << "тип оборудования: " << type << endl;
    }

    string get_country() {
        return country;
    }

    void set_country(string c) {
        country = c;
    }

    string get_type() {
        return type;
    }

    void set_type(string t) {
        type = t;
    }
};

bool compare(Firma_Proizvoditel first, Firma_Proizvoditel second) {
    return (first.get_country()[0] < second.get_country()[0]);
}

int main() {
    int N;
    cout << "Введите количество фирм: ";
    cin >> N;
    
    vector<Firma_Proizvoditel> firms;
    cin.ignore();
    
    for(int i = 0; i < N; i++) {
        cout << "\nФирма " << i + 1 << ":" << endl;
        
        string tcountry, ttype;
        cout << "Введите страну: ";
        getline(cin, tcountry);
        cout << "Введите тип оборудования: ";
        getline(cin, ttype);
        
        firms.push_back(Firma_Proizvoditel(tcountry, ttype));
    }
    

    cout << "\n=== Все фирмы ===" << endl;
    for(int i = 0; i < firms.size(); i++) {
        cout << "\nФирма " << i + 1 << ":" << endl;
        firms[i].outputTo();
    }
    
   
    vector<Firma_Proizvoditel> firms_copy;
    for(int i = 0; i < firms.size(); i++) {
        string type = firms[i].get_type();
        if(!type.empty() && type[0] == 'a') {  
            firms_copy.push_back(firms[i]);
        }
    }
    
    cout << "\n=== После фильтрации ===" << endl;
    if(firms_copy.empty()) {
        cout << "Нет фирм с типом оборудования, начинающимся на 'a'" << endl;
    } else {

        sort(firms_copy.begin(), firms_copy.end(), compare);
        
        
        cout << "\n=== Отфильтрованные и отсортированные фирмы ===" << endl;
        for(int i = 0; i < firms_copy.size(); i++) {
            cout << "\nФирма " << i + 1 << ":" << endl;
            firms_copy[i].outputTo();
        }
    }
    
    return 0;
}
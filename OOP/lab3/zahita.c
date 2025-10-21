#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Airport {
public:
    char name[100]; 
    char place[100];
    int count;
    char status[100];
    
    Airport() {
        strcpy(name, "");
        strcpy(place, "");
        count = 0;
        strcpy(status, "");
    }
    
    Airport(const char* tname, const char* tplace, int tcount, const char* tstatus) {
        strncpy(name, tname, sizeof(name)-1);
        name[sizeof(name)-1] = '\0';
        
        strncpy(place, tplace, sizeof(place)-1);
        place[sizeof(place)-1] = '\0';
        
        count = tcount;
        
        strncpy(status, tstatus, sizeof(status)-1);
        status[sizeof(status)-1] = '\0';
    }
    
    void readFromTextFile(ifstream& file) {
        file.getline(name, sizeof(name));
        file.getline(place, sizeof(place));
        file >> count;
        file.ignore(); 
        file.getline(status, sizeof(status));
    }
    
    void outputTo() {
        cout << "name: " << name << endl;
        cout << "place: " << place << endl;
        cout << "count: " << count << endl;
        cout << "status: " << status << endl;
    }
};

class Airway : public Airport {
public:
    int number;
    int vmest;

    void outputTo() {
        Airport::outputTo(); 
        cout << "number: " << number << endl;
        cout << "vmest: " << vmest << endl;
    }
};

int main() {
    int N;
    cin >> N;
    cin.ignore(); 
    
    Airport* airports = new Airport[N];
    
    ifstream File("порт.txt");
    if (!File.is_open()) {
        cerr << "Не удалось открыть файл!" << endl;
        delete[] airports;  
        return 1;
    }
    
    
    for(int i = 0; i < N; i++) {
        airports[i].readFromTextFile(File);
    }
    File.close();
    
    
    for(int i = 0; i < N; i++) {
        cout << "Аэропорт " << i + 1 << ":" << endl;
        airports[i].outputTo();
        cout << "-------------------" << endl;
    }
    
    delete[] airports; 
    return 0;
}
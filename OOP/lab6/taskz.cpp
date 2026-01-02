#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <deque>
using namespace std;

class Airport {
public:
    int number; 
    int coast;  
    int count_places;
    int count_placed;
    
    Airport() {
        number =0;
        coast = 0;
        count_places =0;
        count_placed =0;
        
    }
    Airport(
        int tnumber, 
        int tcoast,  
        int tcount_places,
        int tcount_placed
    ) {
        number = tnumber;
        coast = tcoast;
        count_places =tcount_places;
        count_placed = tcount_placed;
        
        
    }
    
    int money(){
        return(count_places*coast - count_placed*coast);
    }

    float middle(){
        return(money()/count_places);
    }

    int getCoast(){
        return(coast);
    }

    void outputTo() {
        cout << "number: " << number << endl;
        cout << "coast: " << coast << endl;
        cout << "count_places: " << count_places<< endl;
        cout << "count_placed: " << count_placed << endl;
        cout << "middle: " << middle() << endl;
    }
};


int main() {
    int N;
    cin >> N;
    cin.ignore(); 
    
    fstream f;
    f.open("aport.txt", ios::in);
    deque<Airport> queue;
    deque<Airport> queue2;
    Airport airports[N];
    float middle;
    int tnumber,tcoast,tcount_places,tcount_placed;
    for(int i = 0; i < N; i++){
        f>>tnumber;
        f>>tcoast;
        f>>tcount_places;
        f>>tcount_placed;
        
        airports[i] = Airport(tnumber,tcoast,tcount_places,tcount_placed);
        middle += airports[i].middle();

    }
    
    middle = (middle/N); 
    float temp;
    for(int i = 0; i < N; i++){
        temp = airports[i].middle();
        if (temp <= middle){
            queue.push_back(airports[i]);
        }
        else{
            queue2.push_back(airports[i]);
        }
    }   

    cout << "Очередь 1 (middle <= среднего):" << endl;
    for(deque<Airport>::iterator it = queue.begin(); it != queue.end(); it++) {
        it->outputTo();
        cout << "---" << endl;
    }

    cout << "\n\nОчередь 2 (middle > среднего):" << endl;
    for(deque<Airport>::iterator it = queue2.begin(); it != queue2.end(); it++) {
        it->outputTo();
        cout << "---" << endl;
    }
    

    
    return 0;
}
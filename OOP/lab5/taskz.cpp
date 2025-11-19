
#include <iostream>
#include <string>
#include <fstream>
#include <list>

using namespace std;


class Station{
    public:
        int trainNumber;
        string nameEndStation;
        int coast;
        int places;
        int soldedTickets;


        Station(){
            trainNumber = 0;
            nameEndStation = "";
            coast = 0;
            places = 0;
            soldedTickets = 0;
        }



        Station(
            int ttrainNumber,
            string tnameEndStation,
            int tcoast,
            int tplaces,
            int tsoldedTickets
        ){
            trainNumber = ttrainNumber;
            nameEndStation =tnameEndStation;
            coast = tcoast;
            places = tplaces;
            soldedTickets = tsoldedTickets;
        }

        int unsoldedPlaces(){
            return places - soldedTickets;
        }
        int getPlaces(){
            return places;
        }

        void outputTo(){

            cout<<"trainNumber: "<<trainNumber<<endl;
            cout<<"nameEndStation: "<<nameEndStation<<endl;
            cout<<"coast: "<<coast<<endl;
            cout<<"places: "<<places<<endl;
            cout<<"soldedTickets: "<<soldedTickets<<endl;

        }
};




int main(){

    fstream f;
    f.open("Kassa.txt", ios::in);



    int ttrainNumber;
    string tnameEndStation;
    int tcoast;
    int tplaces;
    int tsoldedTickets;

    list<Station> stations;
    Station new_station;
    
    while(!f.eof()){
        f >> ttrainNumber;
        f.ignore(); 
        getline(f, tnameEndStation); 
        f >> tcoast;
        f >> tplaces;
        f >> tsoldedTickets;
        new_station = Station(
            ttrainNumber,
            tnameEndStation,
            tcoast,
            tplaces,
            tsoldedTickets
        );
        if (new_station.unsoldedPlaces() > new_station.getPlaces()/2){
            stations.emplace_back(new_station);
        }
        
    }


    cout << "=================================" << endl;
    
    int index = 1;
    for( list<Station>::iterator it = stations.begin(); it != stations.end(); it++){
        cout << "Вокзал " << index++ << ":" << endl;
        it->outputTo();
        cout << "---------------------------------" << endl;
    }
    f.close();

    
}
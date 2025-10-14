#include <string>
#include <iostream>
using namespace std;
class Pharmacy{
    public:
        string name;
        string phone_num;
        string address;
        string work_time;
    

        //----constructor without parameters----
        Pharmacy(){
            name =  "";
            phone_num = "";
            address = "";
            work_time = "";
        }

        //----constructor with parameters------
        Pharmacy(string tname, string tphone_num, 
        string taddress, string twork_time){
            name = tname;
            phone_num = tphone_num;
            address = taddress;
            work_time = twork_time;
        }


        //----seters----
        void setName(string tname)           { name = tname;}
        void setPhoneNum(string tphone_num)  { phone_num = tphone_num;}
        void setAddress(string taddress)     { address = taddress;}
        void setWorkTime(string twork_time)  { work_time = twork_time; }

        //-----geters------
        string getName()      { return(name);}
        string getPhoneNum()  { return(phone_num);}
        string getAddress()   { return(address);}
        string getWorkTime()  { return(work_time); }

        void outputTo(){
            cout<<"Название: "<<name<<endl;
            cout<<"Номер телефона: "<<phone_num<<endl;
            cout<<"Адрес:"<<address<<endl;
            cout<<"Время работы: "<<work_time<<endl;
        }
    
};

class PrivatePharmacy : public Pharmacy{
    public:
        string admin_name;

        PrivatePharmacy(string tname, string tphone_num, 
        string taddress, string twork_time, string tadmin_name): Pharmacy(tname, tphone_num, taddress, twork_time){
            
            admin_name = tadmin_name;
        }


        
        //----setters----
        void setAdminName(string tadmin_name){ admin_name = tadmin_name; }
        //----geters-----
        string getAdminName() { return(admin_name); }

        void outputTo(){
            Pharmacy::outputTo();
            cout<<"ФИО владельца: "<<admin_name<<endl;
        }


};




int main(){
    Pharmacy DA;

    PrivatePharmacy prosto =  PrivatePharmacy("prosto","pavel","45","adrr","8^00  9^00");
    cout<<endl;

    prosto.outputTo();

    cout<<endl;

    prosto.setName("prosto");
    prosto.setAdminName("pavel");
    prosto.setPhoneNum("+79130077284");
    prosto.setAddress("adriena lezhena 15");
    prosto.setWorkTime("8:00 - 18:00");

    DA.outputTo();
    cout<<endl;
    prosto.outputTo();


    prosto.setName("vasya");
    cout<<endl;
    prosto.outputTo();



}
#include <string>
#include <iostream>
using namespace std;
class Pharmacy{
    public:
        string name;
        string phone_num;
        string address;
        string work_time;
    

  
        Pharmacy(){
            name =  "";
            phone_num = "";
            address = "";
            work_time = "";
        }


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


        PrivatePharmacy(){
            name =  "";
            admin_name = "";
            phone_num = "";
            address = "";
            work_time = "";
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
    Pharmacy DA = Pharmacy("prosto","45","adrr","8^00  9^00");

    PrivatePharmacy prosto;
    cout<<endl;

    prosto.outputTo();

    cout<<endl;

    string temp;
    cin>>temp;
    prosto.setName(temp);
    cin>>temp;
    prosto.setAdminName(temp);
    cin>>temp;
    prosto.setPhoneNum(temp);
    cin>>temp;
    prosto.setAddress(temp);
    cin>>temp;
    prosto.setWorkTime(temp);

    DA.outputTo();
    cout<<endl;
    prosto.outputTo();


    prosto.setName("vasya");
    cout<<endl;
    prosto.outputTo();



}
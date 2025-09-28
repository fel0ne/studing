#include <iostream>
#include <string>
#include <cmath>
using namespace std;

struct point{
    int x;
    int y;
}typedef point;

class Triangle{
    public:
        point a;
        point b;
        point c;
        Triangle(){
            a.x = 0;
            a.y = 0;
            
            b.x = 0;
            b.y = 0;

            b.x = 0;
            b.y = 0;
        }
        void outputTo(){
            cout<<"---- Вершина A ----"<<endl;
            cout<<"координата X:"<<a.x<<endl;
            cout<<"координата X:"<<a.y<<endl<<endl;
            cout<<"---- Вершина A ----"<<endl;
            cout<<"координата X:"<<b.x<<endl;
            cout<<"координата X:"<<b.y<<endl<<endl;
            cout<<"---- Вершина A ----"<<endl;
            cout<<"координата X:"<<c.x<<endl;
            cout<<"координата X:"<<c.y<<endl<<endl;            
        }

        //----seters----
        void setAX(int X){a.x = X;}  
        void setAY(int Y){a.y = Y;}   

        void setBX(int X){b.x = X;}  
        void setBY(int Y){b.y = Y;}         

        void setCX(int X){c.x = X;}  
        void setCY(int Y){c.y = Y;}          
        
        //----geters----
        int getAX(){return a.x;}  
        int getAY(){return a.y;}    

        int getBX(){return b.x;}  
        int getBY(){return b.y;}  

        int getCX(){return c.x;}  
        int getCY(){return c.y;} 

        double length(int x1, int y1, int x2, int y2){
            double leng = pow(((x2 - x1)*(x2 - x1)+(y2-y1)*(y2-y1)),0.5);
            return leng; 
        } 

        void lengths(){
            cout<<"a-b"<<length(a.x,a.y,b.x,b.y)<<endl;
            cout<<"b-c"<<length(b.x,b.y,c.x,c.y)<<endl;
            cout<<"c-a"<<length(c.x,c.y,a.x,a.y)<<endl<<endl;
        } 

        int isTriangle(){
            if (length(a.x,a.y,b.x,b.y)+length(b.x,b.y,c.x,c.y)>=length(c.x,c.y,a.x,a.y)){
                return 1;
            }
            else{
                return 0;
            }

        }
        double perimetr(){
            return(length(a.x,a.y,b.x,b.y)+length(b.x,b.y,c.x,c.y)+length(c.x,c.y,a.x,a.y));
        }
        void angles
    



};
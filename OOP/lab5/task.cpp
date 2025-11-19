#include <iostream>
#include <list>
#include <string>

using namespace std;



class Book{
    public:
        int num_UDK;
        string author;
        string title;
        int pub_year;
        int copies;

        Book(){
            num_UDK = 0;
            author = "";
            title = "";
            pub_year = 0;
            copies = 0;
        }

        Book(int tnum_UDK, string tauthor, string ttitle, int tpub_year, int tcopies){
            num_UDK = tnum_UDK;
            author = tauthor;
            title = ttitle;
            pub_year = tpub_year;
            copies = tcopies;
        }
        void outputTo(){
            cout << "  УДК: " << num_UDK << endl;
            cout << "  Автор: " << author << endl;
            cout << "  Название: " << title << endl;
            cout << "  Год издания: " << pub_year << endl;
            cout << "  Количество экземпляров: " << copies << endl;
        }

        void setCopies(int tcopies){
            copies = tcopies;
        }

        int getCopies(){
            return copies;
        }
};

void outputBase(list<Book> lib){
    cout << "=================================" << endl;
    
    int index = 1;
    for( list<Book>::iterator it = lib.begin(); it != lib.end(); it++){
        cout << "Книга " << index++ << ":" << endl;
        it->outputTo();
        cout << "---------------------------------" << endl;
    }
    
}


void takeBook(list<Book> &lib, int UDK){
    bool found = false;
    
    for(list<Book>::iterator it = lib.begin(); it != lib.end(); it++){
        if(it->num_UDK == UDK){
            found = true;
            cout << "Книга найдена:" << endl;
            it->outputTo();
            
            if(it->getCopies() > 0){

                it->setCopies(it->getCopies() - 1);
                cout << "Книга успешно взята! Осталось экземпляров: " << it->getCopies() << endl;
            } else {
                cout << "Извините, все экземпляры этой книги уже взяты." << endl;
            }
            break;
        }
    }
    
    if(!found){
        cout << "Книга с УДК " << UDK << " не найдена." << endl;
    }
}


void returnBook(list<Book> &lib, int UDK){
    bool found = false;
    
    for(list<Book>::iterator it = lib.begin(); it != lib.end(); it++){
        if(it->num_UDK == UDK){
            found = true;
            cout << "Книга найдена:" << endl;
            it->outputTo();
            it->setCopies(it->getCopies() + 1);
            cout << "Книга успешно вернута! Осталось экземпляров: " << it->getCopies() << endl;
            break;
        }
    }
    
    if(!found){
        cout << "Книга с УДК " << UDK << " не найдена." << endl;
    }
}



void findBook(list<Book> &lib, int UDK){
    bool found = false;
    
    for(list<Book>::iterator it = lib.begin(); it != lib.end(); it++){
        if(it->num_UDK == UDK){
            found = true;
            cout << "Книга найдена:" << endl;
            it->outputTo();
            break;
        }
    }
    
    if(!found){
        cout << "Книга с УДК " << UDK << " не найдена." << endl;
    }
}
int main(){
    int N;
    cout << "enter count of objects: "; 
    cin >> N;
    list<Book> library;
    Book new_book;

    int tnum_UDK;
    string tauthor;
    string ttitle;
    int tpub_year;
    int tcopies;
    cout << "init base!" <<endl;
    for(int i = 0; i < N; i++){
        cout<< "object: "<< i<<endl;
        cout<<"UDK: ";
        cin >> tnum_UDK;

        cout<<"author: ";
        cin >> tauthor;

        cout <<"title: ";
        cin >> ttitle;

        cout << "publication year: ";
        cin >> tpub_year;

        cout << "copies: ";
        cin >> tcopies;
        
        new_book = Book(tnum_UDK, tauthor, ttitle, tpub_year, tcopies);
        library.emplace_back(new_book);
    }
    


    int choice;
    while (1){
        cout << "Меню:" << endl;
        cout << "1 - Вывести базу данных" << endl;
        cout << "2 - Взять" <<endl;
        cout << "3 - Вернуть" <<endl;
        cout << "4 - Вернуть" <<endl;

        cout << "0 - Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        int UDK;
        if(choice == 0) 
            break;
        else if(choice == 1) 
            outputBase(library);
        else if(choice == 2) {
            
            cout<<"UDK: ";
            cin>>UDK;
            takeBook(library,UDK);
        }
        else if(choice == 3) {
            
            cout<<"UDK: ";
            cin>>UDK;
            returnBook(library,UDK);
        }
        else if(choice == 4) {
            
            cout<<"UDK: ";
            cin>>UDK;
            findBook(library,UDK);
        }
        else
            cout << "Неверный выбор!" << endl;
    }

    return 0;
}


    


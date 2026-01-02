#include <iostream>
#include <string>
#include <queue>
#include <list>

using namespace std;

class Letter {
public:
    char symbol;

    Letter() {
        symbol = ' ';
    }

    Letter(char tsymbol) {
        symbol = tsymbol;
    }

    void outputTo() {
        cout << symbol;
    }
};


int main() {

  
    cout << "Введите предложение: ";
    string sentence;
    getline(cin, sentence);

    list< queue<Letter> > listOfQueues;  
    queue<Letter> currentQueue;
    string currentWord = "";

    for (int i = 0; i < sentence.size(); i++) {
        char c = sentence[i];

        if (c != ' ') {
            currentQueue.push(Letter(c));
        } else {

            if (!currentQueue.empty()) {
                listOfQueues.emplace_back(currentQueue);
                queue<Letter> empty;
                swap(currentQueue, empty);
            }
        }
    }

    if (!currentQueue.empty()) {
        listOfQueues.emplace_back(currentQueue);
    }


  
    cout << "\n=================================\n";

    int index = 1;
    for (list< queue<Letter> >::iterator it = listOfQueues.begin(); 
         it != listOfQueues.end(); 
         it++) 
    {
        cout << "Очередь слова " << index++ << ": ";

      
        queue<Letter> q = *it;


        //for (queue<Letter> ::iterator itt = q.begin(); q != q.end();itt++)

        while (!q.empty()) {
            q.front().outputTo();
            q.pop();
        }



        cout << "\n---------------------------------\n";
    }

    return 0;
}

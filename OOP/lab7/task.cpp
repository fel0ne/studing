#include <iostream>
#include <stack>
using namespace std;

int main() {
    int N;
    cout << "Введите количество элементов: ";
    cin >> N;

    stack<int> st;          // исходный стек (в обратном порядке)
    stack<int> st_show;     // копия для показа
    stack<int> st2;         // результирующий стек (правильный порядок)
    stack<int> temp_stack;  // временный стек

    int x;


    cout << "Введите числа: ";
    for (int i = 0; i < N; i++) {
        cin >> x;
        st.push(x);
    }

    st_show = st;

 
    while (!st.empty()) {
        temp_stack.push(st.top());
        st.pop();
    }

    if (!temp_stack.empty()) {
        st2.push(temp_stack.top()); 
        temp_stack.pop();
    }

    while (!temp_stack.empty()) {
        if (temp_stack.top() > st2.top()) {
            st2.push(temp_stack.top());
        }
        temp_stack.pop();
    }

    
    cout << "\nИсходный стек (верх → низ):" << endl;
    while (!st_show.empty()) {
        cout << st_show.top() << endl;
        st_show.pop();
    }

    cout << "\nСтек после удаления нарушающих возрастание:" << endl;
    while (!st2.empty()) {
        cout << st2.top() << endl;
        st2.pop();
    }

    return 0;
}

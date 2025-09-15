#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

struct Circle{
    int x0;
    int y0;
    int R;
    float length;
    bool Ox_touch;
    bool Oy_touch;
};
typedef struct Circle Circle; 

struct node{
    Circle data;
    node *next;
};
typedef struct node node; 


float length_c(int R){
    float l = 2*3.14*R;
    return(l);
}

void fill_list_r(node** head, int n) {
    
    srand(time(0));

 

    node* current = NULL;
    node* tail = NULL;

    for (int i = 0; i < n; i++) {

        node* new_node = new node();
        
    
        new_node->data.x0 = (rand() % 10) + 1;
        new_node->data.y0 = (rand() % 10) + 1;
        new_node->data.R = (rand() % 10) + 1;
        new_node->data.length = length_c(new_node->data.R);
        new_node->data.Ox_touch = (abs(new_node->data.y0) <= new_node->data.R);
        new_node->data.Oy_touch = (abs(new_node->data.x0) <= new_node->data.R);
        new_node->next = NULL;

     
        if (*head == NULL) {
            *head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
}

void delete_list(node* head) {
    node* current = head;
    while (current != NULL) {
        node* next_node = current->next;
        delete current;
        current = next_node;
    }
}

void print_list(node* head) {
    node* current = head;
    while (current != nullptr) {
        cout << "Circle (y0, x0, R): (" << current->data.x0 << ", " << current->data.y0 << ", " << current->data.R << ")" << endl;
        cout << "  Length: " << current->data.length << endl;
        cout << "  Touches X-axis: " << (current->data.Ox_touch ? "Yes" : "No") << endl;//
        cout << "  Touches Y-axis: " << (current->data.Oy_touch ? "Yes" : "No") << endl;
        cout << "---" << endl;
        current = current->next;
    }
}

int main() {
    int n;
    node* head = NULL;

    cout << "Введите количество кругов для генерации: ";
    cin >> n;

   
    fill_list_r(&head, n);
    


    cout << "Сгенерированные круги:" << endl;
    print_list(head);


    delete_list(head);

    return 0;
}
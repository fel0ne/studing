#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


// СТРУКТУРА ЗАПИСИ!
struct record{
    char name[32];           // ФИО гражданина: текстовое поле 32 символа | фоpмат <Фамилия>_<Имя>_<Отчество>
    char street_name[18];    // Название улицы: текстовое поле 18 символов
    short int house_num;           // Номер дома: целое число
    short int flat_num;            // Номер квартиры: целое число
    char date_check_in[10];  // Дата поселения: текстовое поле 10 символов | фоpмат дд-мм-гг
};
typedef struct node node;
typedef struct record record;


struct node{
    record data;
    node * next_node;
};


node * read_records( FILE * file){
    node* head = NULL;
    while(!feof(file)){
        node * new_node = (node*)malloc(sizeof(node));
        fread(&new_node->data , sizeof(record), 1, file);
        new_node->next_node = head;
        head = new_node;
    }
    return head;
}


int main(){

	setlocale(LC_ALL, "ru_RU.ibm866");

    // Открываем файл
    FILE * file;
    file = fopen("testBase4.dat", "rb");
    if (file == NULL){
        printf("Файл не удается открыть!");
    }
    node * record_list = read_records(file);
    node * current = record_list;
    for (int i = 0; i < 20; i++ ) {
        printf("Имя: %s, Улица: %s, Дом: %d\n", current->data.name, current->data.street_name, current->data.house_num);
        current = current->next_node;
    }


}
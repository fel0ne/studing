#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEBUG 1


//структура элемента(ячейки)
typedef struct Node {
    char key; //ключ
    struct Node* next; //указатель на следующий элемент
} Node;



//функция создания нового элемнта 
Node* createNode(char key) {
    Node* newNode = (Node*)malloc(sizeof(Node)); //выделяем блок памяти под новый элемент
    newNode->key = key; // записываем ключ
    newNode->next = NULL; // указатель на следующий элемент делаем нулевым
    return newNode; // вызвращаем адрес блока памяти (указатель на новый элемент)
}

// //хеш функция
// unsigned int hashFunction(char c, unsigned int m) {
//     unsigned int h = 0; 
//     h =  (unsigned char)c % m;
//     return h;
// }


//хеш функция2
unsigned int hashFunction(char c, unsigned int m) {
    unsigned int h = 0; 
    h =  (unsigned char)c % m ;
    return h;
}

//проверка простое ли число
int isPrime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}


void printHeader() {
    printf("| %-20s | %-25s | %-20s |\n",
           "Размер хеш-таблицы", "Количество исходных символов", "Количество коллизий");
    printf("|--------------------|-----------------------------|---------------------|\n");
}

void printRow(int tableSize, int initialSymbols, int collisions) {
    printf("| %-20d | %-25d | %-20d |\n",
           tableSize, initialSymbols, collisions);
}

void printHashTable(Node* hashTable[], int m) {
    printf("Содержимое хеш-таблицы:\n");
    for (int i = 0; i < m; i++) {
        printf("Индекс %d: ", i);
        Node* current = hashTable[i];
        while (current != NULL) {
            printf("%c -> ", current->key);
            current = current->next;
        }
        printf("NULL\n");
    }
}

//поиск
void search(Node* hashTable[], char key, int m) {
    unsigned int hashValue = hashFunction(key, m);// вычисляем значение хеш функции
    Node* current = hashTable[hashValue]; //берем ячейку из таблицы и бежим по ней ища нужный элемент
    int position = 0;

    while (current != NULL) {
        if (current->key == key) {
            printf("Элемент '%c' найден в списке %d на позиции %d.\n", key, hashValue, position);
            return;
        }
        current = current->next;
        position++;
    }

    printf("Элемент '%c' не найден.\n", key);
}

//считаем количество уникальных символов
int countUniqueSym(char *str){
    int syms[256]  = {0}; //под каждый символ своя ячейка
    int counter = 0;
    for(int i = 0; str[i] != '\0'; i++){
        unsigned char c = (unsigned char)str[i];
        if (!syms[c]){
            syms[c] = 1;
            counter++;
        }
    }
    return counter;
}

//заполнение хеш таблицы
void insert(Node* hashTable[], char key, int m) {
    unsigned int hashValue = hashFunction(key, m); //считаем значение хеша
    Node* current = hashTable[hashValue];
    
    while (current != NULL) { //проходимся по цепочке узлов 
        if (current->key == key) { //если такой ключ уже есть выхлдим из фунции
            return; 
        }
        current = current->next; 
    }
    
    Node* newNode = createNode(key); //создаем новый узел
    newNode->next = hashTable[hashValue];  // добавляем его в начало списка
    hashTable[hashValue] = newNode;
}

//считаем коллизии
int count_collisions(Node* hashTable[], const char* key_string, int m) {
    int collisions = 0;
    int key_length = strlen(key_string);

    //обнуляем все ячейки таблицы
    for (int i = 0; i < m; i++) {
        hashTable[i] = NULL; 
    }

    //заполняем хеш таблицу
    for (int i = 0; i < key_length; i++) {
        insert(hashTable, key_string[i], m);
    }

    //считаем длину цепочки в каждой ячейке таблице что и есть количество колизий
    for (int i = 0; i < m; i++) {
        int count = 0;
        Node* current = hashTable[i];
        while (current != NULL) {
            count++;
            current = current->next;
        }
        if (count > 1) {
            collisions += (count - 1);
        }
    }

    return collisions;
}

int main(){
    char *text ="fFor God so loved the world that He gave His only Son, that whoever believes in Him shall not perish but have eternal life. Walk in faith, for even mountains move with trust as small as a mustard seed. The Lord is my shepherd; I shall lack nothing. In darkest valleys, I fear no evil, for You are with me. Trust not in your own understanding—acknowledge Him, and He will guide your path. Love is patient and kind; it does not envy or boast. Faith, hope, and love endure, but the greatest is love. Cast all anxiety on Him, for He cares for you. Be strong and courageous, for the Lord goes with you always. Come to Me, all who are weary, and I will give rest. I know the plans I have for you: plans for peace, not disaster, to give you hope. Let your light shine before others, that they may see your good deeds. Rejoice always, pray continually, give thanks in all circumstances. The peace of God, beyond all understanding, will guard your hearts. Do not conform to the world, but be transformed by renewing your mind. who";

    int prime_numbers[10];
    int index = 0;
    int turn = 0;
    //вычислим все простые числа начиная с 14 до 101 и будем записывать каждое второе число 
    for(int i = 14; i < 102; i++){
        if (isPrime(i) && turn == 0){
            prime_numbers[index] = i;
            index++;
            turn = 1;
        }
        else if(isPrime(i) && turn == 1){
            turn = 0;
        }
    }
    //считаем длинну ключа
    int key_lenght = countUniqueSym(text);
    printf("Уникальные символы (%d):\n", key_lenght);
    int syms[256] = {0};
    for (int i = 0; text[i] != '\0'; i++) {
        unsigned char c = (unsigned char)text[i];
        if (!syms[c]) {
            printf("%c ", c);
            syms[c] = 1;
        }
    }

    printHeader();

    Node* hashTable[101];
    
    for (int i = 0; i < 10; i++) {
        int m = prime_numbers[i];
        int collisions = count_collisions(hashTable, text, m);
        printRow(m, key_lenght, collisions);
    }

    int m = 47;
    for (int i = 0; i < m; i++) {
        hashTable[i] = NULL;
    }

    for (int i = 0; i < key_lenght; i++) {
        insert(hashTable, text[i], m);
    }
    if(DEBUG){
    printHashTable(hashTable, m);
    }

    printf("\nПоиск элементов:\n");

    search(hashTable, 'a', m);
    search(hashTable, ' ', m);
    search(hashTable, 'j', m);
    search(hashTable, 'Z', m); 


    for (int i = 0; i < m; i++) {
        Node* current = hashTable[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

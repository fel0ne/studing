

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEBUG 1

typedef struct Node {
    char key;
    struct Node* next;
} Node;


//функция создания нового элемнта 
Node* createNode(char key) {
    Node* newNode = (Node*)malloc(sizeof(Node));//выделяем блок памяти под новый элемент
    newNode->key = key; // записываем ключ
    newNode->next = NULL; // указатель на следующий элемент делаем нулевым
    return newNode; // вызвращаем адрес блока памяти (указатель на новый элемент)
}

//хеш функция
unsigned int hashFunction(char c, unsigned int m) {
    return (unsigned char)c % m;
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
           "Размер хеш-таблицы", "Уникальные символы", "Коллизии");
    printf("|--------------------|-----------------------------|---------------------|\n");
}

void printRow(int tableSize, int initialSymbols, int collisions) {
    printf("| %-20d | %-25d | %-20d |\n",
           tableSize, initialSymbols, collisions);
}

void printHashTable(Node** hashTable, int m) {
    printf("\nСодержимое хеш-таблицы (m=%d):\n", m);
    for (int i = 0; i < m; i++) {
        printf("[%02d]: ", i);
        Node* current = hashTable[i];
        while (current != NULL) {
            printf("%c -> ", current->key);
            current = current->next;
        }
        printf("NULL\n");
    }
}


//поиск
void search(Node** hashTable, char key, int m) {
    unsigned int hashValue = hashFunction(key, m);// вычисляем значение хеш функции
    Node* current = hashTable[hashValue];//берем ячейку из таблицы и бежим по ней ища нужный элемент
    int position = 0;

    while (current != NULL) {
        if (current->key == key) {
            printf("Элемент '%c' найден в цепочке %d на позиции %d\n", key, hashValue, position);
            return;
        }
        current = current->next;
        position++;
    }
    printf("Элемент '%c' не найден\n", key);
}

int countUniqueSym(char *str) {
    bool syms[256] = {false};
    int counter = 0;
    for(int i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (!syms[c]) {
            syms[c] = true;
            counter++;
        }
    }
    return counter;
}

void insert(Node** hashTable, char key, int m) {
    unsigned int hashValue = hashFunction(key, m);//считаем значение хеша
    Node* current = hashTable[hashValue];
    
    while (current != NULL) {//проходимся по цепочке узлов 
        if (current->key == key) return;//если такой ключ уже есть выхлдим из фунции
        current = current->next;
    }
    
    Node* newNode = createNode(key);//создаем новый узел
    newNode->next = hashTable[hashValue];// добавляем его в начало списка
    hashTable[hashValue] = newNode;
}

//считаем коллизии
int count_collisions(const char* key_string, int m) {
    Node** hashTable = (Node**)calloc(m, sizeof(Node*));
    int collisions = 0;
//заполняем хеш таблицу
    for (int i = 0; key_string[i] != '\0'; i++) {
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
        if (count > 1) collisions += (count - 1);
    }

    // Очистка памяти
    for (int i = 0; i < m; i++) {
        Node* current = hashTable[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashTable);
    
    return collisions;
}

int main() {
    char *text ="Do not fear, for I am with you; do not be dismayed, for I am your God. I will strengthen you and help you; I will uphold you with my righteous right hand. The Lord is close to the brokenhearted and saves those crushed in spirit. Come to Me, all you who are weary and burdened, and I will give you rest. Take My yoke upon you and learn from Me, for I am gentle and humble in heart. Whatever you do, work at it with all your heart, as working for the Lord. Let your light shine before others, that they may see your good deeds. Rejoice in hope, be patient in affliction, persevere in prayer. And now these three remain: faith, hope, and love. But the greatest of these is love. For God did not give us a spirit of timidity, but of power, love, and self-discipline. Trust in the Lord with all your heart, and lean not on your own understanding. The peace of God, which transcends all understanding, will guard your hearts. Be strong and courageous. Do not be afraid; do not be discouraged, for the Lord your God will be with you wherever you go.";

    // Генерация простых чисел
    int prime_numbers[12];
    int index = 0;
    int turn = 0;
    
    for(int i = 14; i <= 101; i++) {
        if (isPrime(i)) {
            if (turn == 0 && index < 12) {
                prime_numbers[index++] = i;
                turn = 1;
            } else {
                turn = 0;
            }
        }
    }

    int key_length = countUniqueSym(text);
    printHeader();

    // Тестирование для разных размеров таблицы
    for (int i = 0; i < index; i++) {
        int m = prime_numbers[i];
        int collisions = count_collisions(text, m);
        printRow(m, key_length, collisions);
    }

    // Демонстрация работы таблицы
    int m = 47;
    Node** hashTable = (Node**)calloc(m, sizeof(Node*));
    for (int i = 0; text[i] != '\0'; i++) {
        insert(hashTable, text[i], m);
    }

    if(DEBUG) printHashTable(hashTable, m);

    printf("\nРезультаты поиска:\n");
    search(hashTable, 'j', m);
    search(hashTable, ' ', m);
    search(hashTable, 'X', m);

    // Очистка памяти
    for (int i = 0; i < m; i++) {
        Node* current = hashTable[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashTable);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>

#define N 100  // Количество узлов в дереве
#define MAXQ 2000  // Максимальный размер очереди (не используется в коде)

// Структура узла бинарного дерева
typedef struct Node {
    int key;           // Значение ключа узла
    int weight;        // Вес узла
    struct Node* left;   // Левый потомок
    struct Node* right;  // Правый потомок
} Node;

// Глобальные матрицы для динамического программирования
long long AW[N+2][N+2];  // Суммы весов для поддеревьев
long long AP[N+2][N+2];  // Минимальные взвешенные стоимости
int AR[N+2][N+2];        // Корни оптимальных поддеревьев
int w[N+1];              // Массив весов для каждого ключа

// Создание нового узла с заданным ключом
Node* newNodeWithKey(int k) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->key = k;
    p->weight = (k>=1 && k<=N) ? w[k] : 0;  // Назначаем вес из массива w
    p->left = p->right = NULL;
    return p;
}

// Рекурсивное построение дерева по матрице оптимальных корней
Node* buildTreeByAR(int L, int R) {
    if (L > R) return NULL;  // Базовый случай рекурсии
    
    int k = AR[L][R];  // Получаем корень для текущего диапазона
    Node* root = newNodeWithKey(k);
    
    // Рекурсивно строим левое и правое поддеревья
    root->left = buildTreeByAR(L, k - 1);
    root->right = buildTreeByAR(k + 1, R);
    
    return root;
}

// Обход дерева в порядке "левый-корень-правый"
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("(%d,w=%d) ", root->key, root->weight);
    inorder(root->right);
}

// Обход дерева в порядке "корень-левый-правый"
void preorder(Node* root) {
    if (!root) return;
    printf("(%d,w=%d) ", root->key, root->weight);
    preorder(root->left);
    preorder(root->right);
}

// Подсчет количества узлов в дереве
int treeSize(Node* root) {
    if (!root) return 0;
    return 1 + treeSize(root->left) + treeSize(root->right);
}

// Вычисление суммы всех весов в дереве
long long treeWeightSum(Node* root) {
    if (!root) return 0;
    return root->weight + treeWeightSum(root->left) + treeWeightSum(root->right);
}

// Вычисление высоты дерева (максимальная глубина)
int treeHeight(Node* root) {
    if (!root) return 0;
    int hl = treeHeight(root->left);
    int hr = treeHeight(root->right);
    return (hl > hr ? hl : hr) + 1;
}

// Вычисление взвешенной высоты дерева (сумма весов × глубины)
long long weightedHeight(Node* root, int depth) {
    if (!root) return 0;
    long long cur = (long long)root->weight * depth;
    cur += weightedHeight(root->left, depth + 1);
    cur += weightedHeight(root->right, depth + 1);
    return cur;
}

// Построение матриц для оптимального бинарного дерева поиска
void buildMatrices(int n) {
    int i, j, k, h;
    
    // Инициализация матриц нулями
    for (i = 0; i <= n+1; ++i)
        for (j = 0; j <= n+1; ++j) {
            AW[i][j] = AP[i][j] = 0;
            AR[i][j] = 0;
        }
    
    // Инициализация базовых случаев для пустых поддеревьев
    for (i = 1; i <= n+1; ++i) 
        AW[i][i-1] = 0, AP[i][i-1] = 0;
    
    // Заполнение диагоналей матриц (поддеревья из одного узла)
    for (i = 1; i <= n; ++i) {
        AW[i][i] = w[i];      // Сумма весов для одного узла
        AP[i][i] = w[i];      // Стоимость для одного узла
        AR[i][i] = i;         // Корень - сам узел
        
        // Вычисление сумм весов для диапазонов [i,j]
        for (j = i+1; j <= n; ++j) 
            AW[i][j] = AW[i][j-1] + w[j];
    }

    // Динамическое программирование: заполнение матриц для поддеревьев разного размера
    for (h = 2; h <= n; ++h) {           // h - размер поддерева
        for (i = 1; i <= n - h + 1; ++i) {  // i - начало диапазона
            j = i + h - 1;                   // j - конец диапазона
            
            // Определение диапазона поиска оптимального корня
            int m_left = AR[i][j-1]; if (m_left == 0) m_left = i;
            int m_right = AR[i+1][j]; if (m_right == 0) m_right = j;
            if (m_left < i) m_left = i; 
            if (m_right > j) m_right = j;
            if (m_left > m_right) { int t=m_left; m_left=m_right; m_right=t; }

            // Поиск оптимального корня в диапазоне [m_left, m_right]
            long long bestVal = LLONG_MAX;
            int bestK = m_left;
            for (k = m_left; k <= m_right; ++k) {
                long long val = AP[i][k-1] + AP[k+1][j];
                if (val < bestVal) { 
                    bestVal = val; 
                    bestK = k; 
                }
            }
            
            // Запись результатов в матрицы
            AP[i][j] = AW[i][j] + bestVal;  // Минимальная стоимость
            AR[i][j] = bestK;               // Оптимальный корень
        }
    }
}

int main(void) {
    int n = N;
    srand((unsigned)time(NULL));  // Инициализация генератора случайных чисел

    // Генерация случайных весов для ключей
    long long sumW = 0;
    for (int i = 1; i <= n; ++i) {
        w[i] = rand() % 100 + 1;  // Веса от 1 до 100
        sumW += w[i];
    }

    // Вывод таблицы ключей и весов
    printf("Ключ : Вес\n");
    for (int i = 1; i <= n; ++i) {
        printf("%3d:%3d  ", i, w[i]);
        if (i % 10 == 0) printf("\n");
    }
    printf("\n");

    // Построение оптимального дерева поиска
    buildMatrices(n);

    // Вычисление характеристик из матриц
    long long P_from_matrix = AP[1][n];  // Минимальная стоимость для всего дерева
    long long W_from_matrix = AW[1][n];  // Сумма всех весов
    double avg_from_matrix = (W_from_matrix==0?0.0:(double)P_from_matrix / (double)W_from_matrix);

    // Построение дерева по матрице оптимальных корней
    Node* root = buildTreeByAR(1, n);

    // Вывод дерева в порядке "корень-левый-правый"
    printf("КЛП (прямой порядок)\n");
    preorder(root);
    printf("\n\n");

    // Вычисление характеристик построенного дерева
    int size = treeSize(root);                    // Количество узлов
    long long checksum = treeWeightSum(root);     // Сумма весов
    int height = treeHeight(root);                // Высота дерева
    long long weightedP = weightedHeight(root, 1); // Взвешенная высота
    double avg_tree = (checksum==0?0.0:(double)weightedP / (double)checksum); // Средневзвешенная высота

    // Вывод результатов в таблице
    printf("--------------------------------------------------------------\n");
    printf("| %8s | %14s | %8s | %20s |\n", " Размер ", " Контр. Сумма ", " Высота ", " Среднеяя высота ");
    printf("--------------------------------------------------------------\n");
    printf("| %8d | %14lld | %8d | %20.6f |\n", size, checksum, height, avg_tree);
    printf("--------------------------------------------------------------\n\n");

    // Сравнение результатов из матриц и из построенного дерева
    printf("Сравнение средней высоты:\n");
    printf("  AP[1,%d]/AW[1,%d] = %.9f\n", n, n, avg_from_matrix);
    printf("  По дереву: %.9f\n", avg_tree);
    printf("  Разница = %.9f\n", fabs(avg_from_matrix - avg_tree));

    return 0;
}
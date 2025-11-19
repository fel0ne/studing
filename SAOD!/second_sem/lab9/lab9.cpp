#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <iostream>

using namespace std;

#define N 100  

typedef struct Node {
    int key;           
    int weight;        
    struct Node* left;  
    struct Node* right; 
} Node;


typedef struct vertex {
    int data;
    int w;
    int h;
    struct vertex *left;
    struct vertex *right;
} vertex;


vertex *root1 = NULL;
vertex *root2 = NULL;
vertex *root3 = NULL;
int mas[N];
int W[N];
int h_val[N]; 
int c;
int AW_local[N+1][N+1];
int AP_local[N+1][N+1]; 
int AR_local[N+1][N+1];


long long AW_global[N+2][N+2];
long long AP_global[N+2][N+2];
int AR_global[N+2][N+2];
int w[N+1];


void add(vertex *&p, int x, int weight) {
    if (p == NULL) {
        p = new vertex;
        p->data = x;
        p->w = weight;
        p->h = 0; // Инициализируем высоту
        p->left = NULL;
        p->right = NULL;
    } else if (x < p->data) {
        add(p->left, x, weight);
    } else {
        add(p->right, x, weight);
    }
}

void A2(int L, int R) {
    if (L > R) return;
    
    int wes = 0;
    for (int i = L; i <= R; i++) {
        wes += W[i];
    }
    
    int sum = 0;
    int i;
    for (i = L; i <= R; i++) {
        if ((sum < wes / 2) && (sum + W[i] > wes / 2)) {
            break;
        }
        sum += W[i];
    }
    
    // Убедимся, что i в пределах диапазона
    if (i > R) i = R;
    
    add(root3, mas[i], W[i]);
    A2(L, i - 1);
    A2(i + 1, R);
}

int size(vertex *p) {
    if (p == NULL) return 0;
    return 1 + size(p->left) + size(p->right);
}

long summ(vertex *p) {
    if (p == NULL) return 0;
    return p->data + summ(p->left) + summ(p->right);
}

long weightSum(vertex *p) {
    if (p == NULL) return 0;
    return p->w + weightSum(p->left) + weightSum(p->right);
}

void seth(vertex *p) {
    if (p) {
        if (p->left) {
            p->left->h = p->h + 1;
        }
        if (p->right) {
            p->right->h = p->h + 1;
        }
        seth(p->left);
        seth(p->right);
    }
}

int treeHeight(vertex *p) {
    if (!p) return 0;
    int left_height = treeHeight(p->left);
    int right_height = treeHeight(p->right);
    return (left_height > right_height ? left_height : right_height) + 1;
}

void midh(vertex *p) {
    if (p) {
        c += p->w * p->h;
        midh(p->left);
        midh(p->right);
    }
}

void BubbleSort() {
    for (int i = 0; i < N-1; i++) {
        for (int j = N-1; j > i; j--) {
            if (W[j] > W[j-1]) {
                int t = W[j];
                W[j] = W[j-1];
                W[j-1] = t;
                t = mas[j];
                mas[j] = mas[j-1];
                mas[j-1] = t;
            }
        }
    }
}

void AW_count() {
    for (int i = 0; i <= N; i++) {
        AW_local[i][i] = 0;
        for (int j = i + 1; j <= N; j++) {
            AW_local[i][j] = AW_local[i][j-1] + W[j-1];
        }
    }
}

void AP_AR_count() {
    // Инициализация
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            AP_local[i][j] = 0;
            AR_local[i][j] = 0;
        }
    }
    
    // Заполнение для поддеревьев размера 1
    for (int i = 0; i < N; i++) {
        int j = i + 1;
        AP_local[i][j] = AW_local[i][j];
        AR_local[i][j] = j;
    }
    
    // Заполнение для поддеревьев большего размера
    for (int H = 2; H <= N; H++) {
        for (int i = 0; i <= N - H; i++) {
            int j = i + H;
            int m = AR_local[i][j-1];
            if (m < i+1) m = i+1;
            
            int min_val = AP_local[i][m-1] + AP_local[m][j];
            int max_k = (AR_local[i+1][j] == 0) ? j : AR_local[i+1][j];
            if (max_k > j) max_k = j;
            
            for (int k = m + 1; k <= max_k; k++) {
                int x = AP_local[i][k-1] + AP_local[k][j];
                if (x < min_val) {
                    m = k;
                    min_val = x;
                }
            }
            AP_local[i][j] = min_val + AW_local[i][j];
            AR_local[i][j] = m;
        }
    }
}

void create_tree(int L, int R) {
    if (L >= R) return;
    
    int k = AR_local[L][R];
    if (k >= 1 && k <= N) {
        add(root1, k, W[k-1]);
        create_tree(L, k - 1);
        create_tree(k, R);
    }
}

// Оригинальные функции
Node* newNodeWithKey(int k) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->key = k;
    p->weight = (k>=1 && k<=N) ? w[k] : 0;
    p->left = p->right = NULL;
    return p;
}

Node* buildTreeByAR(int L, int R) {
    if (L > R) return NULL;
    
    int k = AR_global[L][R];
    Node* root = newNodeWithKey(k);
    root->left = buildTreeByAR(L, k - 1);
    root->right = buildTreeByAR(k + 1, R);
    return root;
}

int treeSize(Node* root) {
    if (!root) return 0;
    return 1 + treeSize(root->left) + treeSize(root->right);
}

long long treeWeightSum(Node* root) {
    if (!root) return 0;
    return root->weight + treeWeightSum(root->left) + treeWeightSum(root->right);
}

int treeHeight(Node* root) {
    if (!root) return 0;
    int hl = treeHeight(root->left);
    int hr = treeHeight(root->right);
    return (hl > hr ? hl : hr) + 1;
}

long long weightedHeight(Node* root, int depth) {
    if (!root) return 0;
    long long cur = (long long)root->weight * depth;
    cur += weightedHeight(root->left, depth + 1);
    cur += weightedHeight(root->right, depth + 1);
    return cur;
}

void buildMatrices(int n) {
    // Инициализация матриц
    for (int i = 0; i <= n+1; i++) {
        for (int j = 0; j <= n+1; j++) {
            AW_global[i][j] = AP_global[i][j] = 0;
            AR_global[i][j] = 0;
        }
    }
    
    // Базовые случаи
    for (int i = 1; i <= n+1; i++) {
        AW_global[i][i-1] = 0;
        AP_global[i][i-1] = 0;
    }
    
    // Поддеревья из одного узла
    for (int i = 1; i <= n; i++) {
        AW_global[i][i] = w[i];
        AP_global[i][i] = w[i];
        AR_global[i][i] = i;
        
        for (int j = i+1; j <= n; j++) {
            AW_global[i][j] = AW_global[i][j-1] + w[j];
        }
    }

    for (int h = 2; h <= n; h++) {
        for (int i = 1; i <= n - h + 1; i++) {
            int j = i + h - 1;
            
            int m_left = AR_global[i][j-1];
            if (m_left < i) m_left = i;
            int m_right = AR_global[i+1][j];
            if (m_right > j) m_right = j;
            if (m_left > m_right) {
                int t = m_left;
                m_left = m_right;
                m_right = t;
            }

            long long bestVal = LLONG_MAX;
            int bestK = m_left;
            for (int k = m_left; k <= m_right; k++) {
                long long val = AP_global[i][k-1] + AP_global[k+1][j];
                if (val < bestVal) {
                    bestVal = val;
                    bestK = k;
                }
            }
            
            AP_global[i][j] = AW_global[i][j] + bestVal;
            AR_global[i][j] = bestK;
        }
    }
}

// Функция для вычисления характеристик дерева типа vertex
void calculateTreeStats(vertex* root, const char* treeName) {
    if (!root) {
        printf("| %-8s | %8d | %14ld | %8d | %20.6f |\n", 
               treeName, 0, 0L, 0, 0.0);
        return;
    }
    
    // Установка высот
    root->h = 1;
    seth(root);
    
    // Вычисление характеристик
    int tree_size = size(root);
    long tree_weight_sum = weightSum(root);
    int max_height = treeHeight(root);
    
    c = 0;
    midh(root);
    double avg_height = (tree_weight_sum == 0) ? 0.0 : (double)c / (double)tree_weight_sum;
    
    printf("| %-8s | %8d | %14ld | %8d | %20.6f |\n", 
           treeName, tree_size, tree_weight_sum, max_height, avg_height);
}

int main(void) {
    int n = N;
    srand((unsigned)time(NULL));

    // Инициализация весов
    for (int i = 1; i <= n; i++) {
        w[i] = rand() % 100 + 1;
    }

    // Инициализация массивов для дополнительных деревьев
    for (int i = 0; i < N; i++) {
        mas[i] = i + 1;
        W[i] = w[i + 1];
    }

    // Вывод таблицы ключей и весов
    printf("Ключ : Вес\n");
    for (int i = 1; i <= n; i++) {
        printf("%3d:%3d  ", i, w[i]);
        if (i % 10 == 0) printf("\n");
    }
    printf("\n");

    // Метод 1: ДОП (динамическое программирование)
    buildMatrices(n);
    Node* root_dop = buildTreeByAR(1, n);
    
    int size_dop = treeSize(root_dop);
    long long checksum_dop = treeWeightSum(root_dop);
    int height_dop = treeHeight(root_dop);
    long long weightedP_dop = weightedHeight(root_dop, 1);
    double avg_tree_dop = (checksum_dop == 0) ? 0.0 : (double)weightedP_dop / (double)checksum_dop;

    // Метод 2: A1 (сортировка по весам)
    BubbleSort();
    for (int i = 0; i < N; i++) {
        add(root2, mas[i], W[i]);
    }

    // Метод 3: A2 (метод половинного деления)
    // Переинициализируем массивы для A2
    for (int i = 0; i < N; i++) {
        mas[i] = i + 1;
        W[i] = w[i + 1];
    }
    A2(0, N-1);

    // Вывод таблицы
    printf("----------------------------------------------------------------------------------------\n");
    printf("| Метод     | Размер   | Контр. Сумма | Высота  | Средневзвеш.высота |\n");
    printf("----------------------------------------------------------------------------------------\n");
    
    printf("| %-8s | %8d | %14lld | %8d | %20.6f |\n", 
           "ДОП", size_dop, checksum_dop, height_dop, avg_tree_dop);
    
    calculateTreeStats(root2, "A1");
    calculateTreeStats(root3, "A2");
    
    printf("----------------------------------------------------------------------------------------\n");

    return 0;
}
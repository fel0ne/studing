
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#define N 100
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define NODE_RADIUS 8
#define H_SPACING 600
#define V_SPACING 70
int A[N];
typedef struct Node {
    int data;               
    struct Node *left, *right;
} Node;

struct Vertex{
    int Data;
    struct Vertex *Left;
    struct Vertex *Right;
};
typedef struct Vertex Vertex; 

Vertex *root1 = NULL, *root2 = NULL, *root3=NULL;
int height(Vertex *current);

// Helper function to draw a circle
void drawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            }
        }
    }
}

// Function to draw digits using simple lines (7-segment display style)
void drawDigit(SDL_Renderer *renderer, int digit, int x, int y, int size) {
    // Define segments for each digit (0-9)
    int segments[10][7] = {
        {1, 1, 1, 1, 1, 1, 0}, // 0
        {0, 1, 1, 0, 0, 0, 0}, // 1
        {1, 1, 0, 1, 1, 0, 1}, // 2
        {1, 1, 1, 1, 0, 0, 1}, // 3
        {0, 1, 1, 0, 0, 1, 1}, // 4
        {1, 0, 1, 1, 0, 1, 1}, // 5
        {1, 0, 1, 1, 1, 1, 1}, // 6
        {1, 1, 1, 0, 0, 0, 0}, // 7
        {1, 1, 1, 1, 1, 1, 1}, // 8
        {1, 1, 1, 1, 0, 1, 1}  // 9
    };
    
    if (digit < 0 || digit > 9) return;
    
    int *seg = segments[digit];
    
    // Draw segments
    if (seg[0]) SDL_RenderDrawLine(renderer, x, y, x + size, y); // top
    if (seg[1]) SDL_RenderDrawLine(renderer, x + size, y, x + size, y + size); // top-right
    if (seg[2]) SDL_RenderDrawLine(renderer, x + size, y + size, x + size, y + 2*size); // bottom-right
    if (seg[3]) SDL_RenderDrawLine(renderer, x, y + 2*size, x + size, y + 2*size); // bottom
    if (seg[4]) SDL_RenderDrawLine(renderer, x, y + size, x, y + 2*size); // bottom-left
    if (seg[5]) SDL_RenderDrawLine(renderer, x, y, x, y + size); // top-left
    if (seg[6]) SDL_RenderDrawLine(renderer, x, y + size, x + size, y + size); // middle
}

// Function to draw a number using simple digits
void drawNumber(SDL_Renderer *renderer, int number, int centerX, int centerY) {
    if (number < 0 || number > 999) return;
    
    char buffer[4];
    snprintf(buffer, sizeof(buffer), "%d", number);
    
    int len = 0;
    while (buffer[len] != '\0' && len < 3) len++;
    
    int digitSize = 4;
    int totalWidth = len * (digitSize + 2);
    int startX = centerX - totalWidth / 2;
    
    for (int i = 0; i < len; i++) {
        int digit = buffer[i] - '0';
        drawDigit(renderer, digit, startX + i * (digitSize + 2), centerY - digitSize, digitSize);
    }
}

// Recursive function to draw the tree with better spacing
// Improved tree drawing with better spacing algorithm
// Calculate tree width for better layout
int calculateTreeWidth(Vertex *current, int level) {
    if (current == NULL) return 0;
    
    // Base width for a node
    int width = NODE_RADIUS * 2 + 10;
    
    // Add widths of subtrees
    int leftWidth = calculateTreeWidth(current->Left, level + 1);
    int rightWidth = calculateTreeWidth(current->Right, level + 1);
    
    return width + leftWidth + rightWidth;
}

// Advanced tree drawing with width-based spacing
// Функция для расчета максимальной ширины дерева
int calculateMaxWidth(Vertex* root) {
    if (root == NULL) return 0;
    
    int maxWidth = 0;
    Vertex** queue = (Vertex**)malloc(N * sizeof(Vertex*));
    int front = 0, rear = 0;
    
    queue[rear++] = root;
    
    while (front < rear) {
        int levelSize = rear - front;
        maxWidth = (levelSize > maxWidth) ? levelSize : maxWidth;
        
        for (int i = 0; i < levelSize; i++) {
            Vertex* current = queue[front++];
            if (current->Left != NULL) queue[rear++] = current->Left;
            if (current->Right != NULL) queue[rear++] = current->Right;
        }
    }
    
    free(queue);
    return maxWidth;
}

// Автоматическое вычисление оптимального расстояния
int calculateOptimalSpacing(Vertex* root) {
    int treeHeight = height(root);
    int treeWidth = calculateMaxWidth(root);
    
    // Вычисляем оптимальное расстояние на основе ширины экрана и ширины дерева
    int optimalSpacing = (SCREEN_WIDTH * 0.8) / (treeWidth + 1);
    
    // Ограничиваем минимальное и максимальное расстояние
    if (optimalSpacing < 30) optimalSpacing = 30;
    if (optimalSpacing > 300) optimalSpacing = 300;
    
    return optimalSpacing;
}

// Улучшенная функция отрисовки с масштабированием
void drawTreeScaled(SDL_Renderer *renderer, Vertex *current, int x, int y, int h_spacing, int level, double scale) {
    if (current == NULL) return;

    // Масштабируем расстояния
    int scaled_h_spacing = h_spacing * scale;
    int scaled_v_spacing = V_SPACING;

    // Ограничиваем минимальное расстояние
    if (scaled_h_spacing < NODE_RADIUS * 3) {
        scaled_h_spacing = NODE_RADIUS * 3;
    }

    // Рисуем узел
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    drawCircle(renderer, x, y, NODE_RADIUS);
    drawNumber(renderer, current->Data, x, y);

    // Левый потомок
    if (current->Left != NULL) {
        int childX = x - scaled_h_spacing;
        int childY = y + scaled_v_spacing;
        
        SDL_RenderDrawLine(renderer, x, y + NODE_RADIUS, childX, childY - NODE_RADIUS);
        drawTreeScaled(renderer, current->Left, childX, childY, scaled_h_spacing * 0.6, level + 1, scale);
    }

    // Правый потомок
    if (current->Right != NULL) {
        int childX = x + scaled_h_spacing;
        int childY = y + scaled_v_spacing;
        
        SDL_RenderDrawLine(renderer, x, y + NODE_RADIUS, childX, childY - NODE_RADIUS);
        drawTreeScaled(renderer, current->Right, childX, childY, scaled_h_spacing * 0.6, level + 1, scale);
    }
}
// Existing functions (unchanged)

void addRight(Vertex * current, int Data){
    current->Right = (Vertex*)malloc(sizeof(Vertex));
    current->Right->Data = Data;
    current->Right->Right = NULL;
    current->Right->Left = NULL;
}

void addLeft(Vertex * current, int Data){
    current->Left = (Vertex*)malloc(sizeof(Vertex));
    current->Left->Data = Data;
    current->Left->Right = NULL;
    current->Left->Left = NULL;
}

void obhod_root_left_right(Vertex *current){
    if(current != NULL){
        printf("%d ", current->Data);
        obhod_root_left_right(current->Left);
        obhod_root_left_right(current->Right);
    }

}

void obhod_left_root_right(Vertex *current){
    if(current != NULL){
        obhod_left_root_right(current->Left);
        printf("%d ", current->Data);
        obhod_left_root_right(current->Right);
    }

}

void obhod_left_right_root(Vertex *current){
    if(current != NULL){
        obhod_left_right_root(current->Left);
        obhod_left_right_root(current->Right);
        printf("%d ", current->Data);
    }

}

int size(Vertex *current){
    int n;
    if(current == NULL){
        n = 0;
    }
    else{
        n = 1 + size(current->Left) + size(current->Right);
    }
    return(n);
}

int treeSum(Vertex *current){
    int s;
    if(current == 0){
        s = 0;
    }
    else{
        s = current->Data + treeSum(current->Left)+ treeSum(current->Right);
    }
    return(s);
}

int max(int a, int b){
    if(a > b){
        return(a);
    }
    else{
        return(b);
    }
}

int height(Vertex *current){
    int h;
    if (current == NULL){
        h = 0;
    }
    else{
        h = 1 + max(height(current->Left), height(current->Right));
    }
    return(h);
}

int SLW(Vertex *current, int L){
    int s;
    if (current == NULL){
        s = 0;
    }
    else{
        s = L + SLW(current->Left,L+1) + SLW(current->Right,L+1);
    }
    return(s);
}

float heightSred(Vertex *current){
    float hs = (float)SLW(current,1)/size(current);
    return(hs);
}

 int counter = 1;

Vertex * ISDP (int L, int R) 
{
   
	if (L>R) return NULL;
	else {
		int m = (L + R) / 2;
		Vertex *p = (Vertex*)malloc(sizeof(Vertex)); 
    	p->Data = A[m];
		p->Left = ISDP(L, m - 1);
		p->Right = ISDP(m + 1, R);
		return p;
	}
}

int recSDP(int data, Vertex* &p) 
{
    if (!p) {
        p = new Vertex;
        p->Data = data;
        p->Left = NULL;
        p->Right = NULL;
        return 1;
    } 
    else if (data < p->Data) {
        return recSDP(data, p->Left);
    }
    else if (data > p->Data) {
        return recSDP(data, p->Right);
    }
    else {
        return 0; // дубликат
    }
}


int SDP(int data, Vertex*&point) 
{
	Vertex **p = &point;

	while (*p) {
		if (data < (*p)->Data) {
			p = &((*p)->Left);
		}
		else if (data > (*p)->Data) {
			p = &((*p)->Right);
		}
		else break;
	}

	if (*p == NULL) {
		*p = new Vertex;
		(*p)->Data = data;
		(*p)->Left = NULL;
		(*p)->Right = NULL;
	}

	return 0;
}

void fillTreeLevelOrder(Vertex *root, int *values, int size) {
    if (root == NULL || size == 0) return;
    

    Vertex **queue = (Vertex**)malloc(size * sizeof(Vertex*));
    int front = 0, rear = 0;
    int index = 0;
    
    queue[rear++] = root;
    
    while (front < rear && index < size) {
        Vertex *current = queue[front++];
        
        current->Data = values[index+1];
        index =index+1;
        
        if (current->Left != NULL) {
            queue[rear++] = current->Left;
        }
        if (current->Right != NULL) {
            queue[rear++] = current->Right;
        }
    }
    
    free(queue);
}



void freeTree(Vertex *current) {
    if (current == NULL) {
        return;
    }
    freeTree(current->Left);
    freeTree(current->Right);
    free(current);
}
// Компактное расположение дерева
void drawTreeCompact(SDL_Renderer *renderer, Vertex *current, int x, int y, int level, int* nextX) {
    if (current == NULL) return;

    // Рекурсивно рисуем левое поддерево
    if (current->Left != NULL) {
        drawTreeCompact(renderer, current->Left, x, y + V_SPACING, level + 1, nextX);
    }

    // Рисуем текущий узел
    int currentX = (*nextX);
    *nextX += 50; // Расстояние между узлами на одном уровне

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    drawCircle(renderer, currentX, y, NODE_RADIUS);
    drawNumber(renderer, current->Data, currentX, y);

    // Соединяем с левым потомком
    if (current->Left != NULL) {
        // Находим позицию левого потомка (он уже был нарисован)
        int leftChildX = currentX - 50 * (1 << (height(current->Left) - 1));
        SDL_RenderDrawLine(renderer, currentX, y - NODE_RADIUS, leftChildX, y + V_SPACING - NODE_RADIUS);
    }

    // Рекурсивно рисуем правое поддерево
    if (current->Right != NULL) {
        drawTreeCompact(renderer, current->Right, currentX, y + V_SPACING, level + 1, nextX);
        
        // Соединяем с правым потомком
        int rightChildX = currentX + 50 * (1 << (height(current->Right) - 1));
        SDL_RenderDrawLine(renderer, currentX, y - NODE_RADIUS, rightChildX, y + V_SPACING - NODE_RADIUS);
    }
}

// Минималистичная версия
#define NODE_RADIUS 6
#define V_SPACING 80

void drawTreeMinimal(SDL_Renderer *renderer, Vertex *current, int x, int y, int h_spacing, int level) {
    if (current == NULL) return;

    // Сильно уменьшаем расстояние на каждом уровне
    int new_spacing = h_spacing * 1;
    if (new_spacing < 20) new_spacing = 20; // Минимальный отступ

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    drawCircle(renderer, x, y, NODE_RADIUS);
    
    // Упрощаем отображение чисел (только последние 2 цифры)
    int displayValue = current->Data % 100;
    drawNumber(renderer, displayValue, x, y);

    if (current->Left != NULL) {
        int childX = x - new_spacing;
        int childY = y + V_SPACING;
        SDL_RenderDrawLine(renderer, x, y + NODE_RADIUS, childX, childY - NODE_RADIUS);
        drawTreeMinimal(renderer, current->Left, childX, childY, new_spacing, level + 1);
    }

    if (current->Right != NULL) {
        int childX = x + new_spacing;
        int childY = y + V_SPACING;
        SDL_RenderDrawLine(renderer, x, y + NODE_RADIUS, childX, childY - NODE_RADIUS);
        drawTreeMinimal(renderer, current->Right, childX, childY, new_spacing, level + 1);
    }
}
int main(){
    srand(time(NULL));
    // Инициализация массивов
    
    for (int i = 0; i < N; i++) {
        int value;
        bool duplicate;
        do {
        duplicate = false;
        value = rand() % 100;
        // Проверка на дубликат
        for (int j = 0; j < i; j++) {
            if (A[j] == value) {
                duplicate = true;
                break;
            }
        }
        } while (duplicate);
        A[i] = value;
    }
    

    counter = 1;
    root1 = ISDP(0, N -1);
    
   
    
    // Создание деревьев
    root2 = NULL; 
    for (int i = 0; i < N; i++) {
        SDP(A[i], root2);
    }
    // for (int i = 0; i < N; i++) {
    //     int value;
    //     bool duplicate;
    //     do {
    //     duplicate = false;
    //     value = rand() % 2000;
    //     // Проверка на дубликат
    //     for (int j = 0; j < i; j++) {
    //         if (A[j] == value) {
    //             duplicate = true;
    //             break;
    //         }
    //     }
    //     } while (duplicate);
    //     A[i] = value;
    // }
    root3 = NULL; 
    for (int i = 0; i < N; i++) {
        
        recSDP(A[i], root3);
    }

  
    printf("Обход ИСДП (лев-прав-корень): ");
    obhod_left_right_root(root1);
    printf("\n---------------------------------\n");
    
    printf("Обход СДП1 (лев-корень-прав): ");
    obhod_left_root_right(root2);
    printf("\n---------------------------------\n");
    
    printf("Обход СДП2 (лев-корень-прав): ");
    obhod_left_root_right(root3);
    printf("\n---------------------------------\n");
    
    printf("+------+----------+----------------+----------+----------------+\n");
    printf("|%6s|  Размер  |  Контр. сумма  |  Высота  |  Сред. высота  |\n", "N=100");
    printf("+------+----------+----------------+----------+----------------+\n");
    printf("| ИСДП |%10d|%16d|%10d|%16.2f|\n", size(root1), treeSum(root1), height(root1), heightSred(root1));
    printf("| СДП1 |%10d|%16d|%10d|%16.2f|\n", size(root2), treeSum(root2), height(root2), heightSred(root2));
    printf("| СДП2 |%10d|%16d|%10d|%16.2f|\n", size(root3), treeSum(root3), height(root3), heightSred(root3));
    printf("+------+----------+----------------+----------+----------------+\n");

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("ISDP Tree Visualization", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);
//int optimalSpacing = calculateOptimalSpacing(root2);
    // Draw the tree
   //drawTreeScaled(renderer, root2, SCREEN_WIDTH / 2, 30, optimalSpacing, 1, 0.8);
// int startX = 50;
// drawTreeCompact(renderer, root2, 0, 50, 1, &startX);
drawTreeMinimal(renderer, root2, SCREEN_WIDTH / 2, 30, 200, 1);
    SDL_RenderPresent(renderer);

    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    // Clean up
    freeTree(root2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}




    
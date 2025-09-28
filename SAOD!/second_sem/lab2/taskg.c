#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#define N 100
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define NODE_RADIUS 15
#define H_SPACING 450
#define V_SPACING 100

int A[N + 1];

struct Vertex {
    int Data;
    struct Vertex *Left;
    struct Vertex *Right;
};
typedef struct Vertex Vertex;

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
    
    int digitSize = 8;
    int totalWidth = len * (digitSize + 2);
    int startX = centerX - totalWidth / 2;
    
    for (int i = 0; i < len; i++) {
        int digit = buffer[i] - '0';
        drawDigit(renderer, digit, startX + i * (digitSize + 2), centerY - digitSize, digitSize);
    }
}

// Recursive function to draw the tree
void drawTree(SDL_Renderer *renderer, Vertex *current, int x, int y, int h_spacing) {
    if (current == NULL) {
        return;
    }

    // Draw the current node as a circle
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
    drawCircle(renderer, x, y, NODE_RADIUS);

    // Draw the node's data value
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // White color
    drawNumber(renderer, current->Data, x, y);

    // Draw connections and recursively call for children
    if (current->Left != NULL) {
        // Draw line to the left child
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, x, y, x - h_spacing, y + V_SPACING);
        drawTree(renderer, current->Left, x - h_spacing, y + V_SPACING, h_spacing / 2);
    }

    if (current->Right != NULL) {
        // Draw line to the right child
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, x, y, x + h_spacing, y + V_SPACING);
        drawTree(renderer, current->Right, x + h_spacing, y + V_SPACING, h_spacing / 2);
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
int c =0;
Vertex * ISDP (int L, int R) 
{
    
    if (L > R) return NULL;
    else {
        int m = (L + R) / 2;
        Vertex *p = (Vertex*)malloc(sizeof(Vertex)); 
        p->Data = 0;
        c = c+1;
        p->Left = ISDP(L, m - 1);
        p->Right = ISDP(m + 1, R);
        return p;
    }
}

void freeTree(Vertex *current) {
    if (current == NULL) {
        return;
    }
    freeTree(current->Left);
    freeTree(current->Right);
    free(current);
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

int main(){
    for (int i = 1; i <= N; i++) {
        A[i] = i;
    }   
    int m = N / 2;
    Vertex * Root = (Vertex*)malloc(sizeof(Vertex));
    Root->Data = A[m];
    Root->Left = ISDP(1, m - 1);
    Root->Right = ISDP(m + 1, N);

    fillTreeLevelOrder(Root,A,100);
    
    printf("Размер дерева: %d\n", size(Root));
    printf("Сумма дерева: %d\n", treeSum(Root));
    printf("Высота дерева: %d\n", height(Root));
    printf("Средняя высота дерева: %f\n", heightSred(Root));
    
    // --- Graphical part ---
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

    // Draw the tree
    drawTree(renderer, Root, SCREEN_WIDTH / 2, 30, H_SPACING);

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
    freeTree(Root);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
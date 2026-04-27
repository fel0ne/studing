#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h> 
#include <conio.h>
#include <string.h>
#include <math.h>
#define MAX_SIZE 4000  

void header(){
    printf("+---+------------------------------------+----------------------+------+---------+--------------+\n");
    printf("| № |              Ф.И.О                 |     УЛИЦА            |  ДОМ |  ЭТАЖ   |ДАТА ЗАСЕЛЕНИЯ|\n");
    printf("+---|------------------------------------+----------------------+------+---------+--------------|\n");
}

void tailer(int n){
    printf("|-----------------------------------------------------------------------------------------------|\n");
    printf(" m - меню    p - перейти к странице         №%3d                      n - след. страница   ----->\n", n);
}

struct record{
    char name[32];           
    char street_name[18];    
    short int house_num;           
    short int flat_num;           
    char date_check_in[10];  
};

typedef struct node node;

typedef struct record record;

struct node{

    union {
        record data;
        unsigned char digit[sizeof(record)];
    };
    node * next_node;
    node * prev_node;
};

typedef struct queue {
    node *head;
    node *tail;
} queue;

struct Vertex{
    record data;           
    int count;             
    struct Vertex *Left;
    struct Vertex *Right;
    int use;
};

node * read_records( FILE * file){
    node * head = NULL;
    node * tail = NULL;
    record temp_record;
    while(fread(&temp_record , sizeof(record) , 1 , file )){
        node * new_node = (node *)malloc(sizeof(node));
        new_node -> data = temp_record;
        new_node->next_node = NULL;
        new_node -> prev_node = NULL;
        if (head == NULL){
            head = new_node;
            tail = new_node;
        }
        else{
            tail->next_node = new_node;
            new_node -> prev_node = tail;
            tail = new_node;
        }
    } 
    return head;
}


int compare(char *a, char *b) {
    for (int i = 0; i < 3; i++) {
        if ((unsigned char)a[i] < (unsigned char)b[i]) return -1;
        else if ((unsigned char)a[i] > (unsigned char)b[i]) return 1;
    }
    return 0;
}

queue* binary_search_three_letters(char *x, node *index_array[], int array_size) {
    queue *turn = (queue*)malloc(sizeof(queue));
    turn->head = turn->tail = NULL;
    
    int L = 0;
    int R = array_size;
    
    
    while (L < R) {
        int m = (L + R) / 2;
        
        if (compare(index_array[m]->data.street_name, x) < 0) {
            L = m + 1;
        } else {
            R = m;
        }
    }
    
    if (L < array_size && compare(index_array[L]->data.street_name, x) == 0) {
        for (int i = L; i < array_size && compare(index_array[i]->data.street_name, x) == 0; i++) {
            node *new_node = (node *)malloc(sizeof(node));
            new_node->data = index_array[i]->data; 
            new_node->next_node = NULL;
            new_node->prev_node = NULL;
            
            if (turn->head == NULL) {
                turn->head = new_node;
                turn->tail = new_node;
            } else {
                turn->tail->next_node = new_node;
                new_node->prev_node = turn->tail;
                turn->tail = new_node;
            }
        }
    }
    
    return turn;
}

int queue_count(queue *q) {
    int count = 0;
    node *current = q->head;
    while (current != NULL) {
        count++;
        current = current->next_node;
    }
    return count;
}

void free_queue(queue *q) {
    if (q == NULL) return;
    node *current = q->head;
    while (current != NULL) {
        node *temp = current;
        current = current->next_node;
        free(temp);
    }
    free(q);
}






void print_array(node **index_array, int array_size);
void print_queue(queue *q);

void print_menu(){
    system("cls");
    printf("\n\n\n\n\n\n\n");
    printf("     +-----------------ВАРИАНТ 42434--------------------+\n");
    printf("     |  p - Просмотреть базу                            |\n");
    printf("     |  s - Отсортировать базу   (улица и дом)          |\n");
    printf("     |  r - Вернутся к  несортированной базе            |\n");
    printf("     |  b - Бинарный поиск по 3-м буквам улицы          |\n");
    printf("     |  t - Построить и показать дерево                 |\n");
    printf("     |  f - Бинарный поиск по году в дереве             |\n");
    printf("     |  c - Закодировать базу(Метод Гилберта-Мура)      |\n");
    printf("     |  q - Выход                                       |\n");
    printf("     +--------------------------------------------------+\n");        
}

node** DigitalSort(node **index_array, int size, int flag);

node** list_to_array(node *head, int *size) {
    if (head == NULL) {
        *size = 0;
        return NULL;
    }
    
   
    int count = 0;
    node *current = head;
    while (current != NULL) {
        count++;
        current = current->next_node;
    }
    

    node **array = (node**)malloc(count * sizeof(node*));
    if (array == NULL) {
        *size = 0;
        return NULL;
    }
    

    current = head;
    for (int i = 0; i < count; i++) {
        array[i] = current;
        current = current->next_node;
    }
    
    *size = count;
    return array;
}




int extract_year(char* date) {
    int len = strlen(date);
    if (len < 2) return 0;
    
  
    char year_str[5];
    if (len >= 2) {
        strcpy(year_str, date + len - 3);
        int year = atoi(year_str);
        
        return year;
    }
    return 0;
}

int SDP(struct Vertex** point, record data, int count) 
{
    struct Vertex **p = point;
    int current_year = extract_year(data.date_check_in);

    while (*p) {
        int node_year = extract_year((*p)->data.date_check_in);
        
        if (current_year < node_year) {
            p = &((*p)->Left);
        }
        else if (current_year > node_year) {
            p = &((*p)->Right);
        }
        else {
            p = &((*p)->Right);
        }
    }

    if (*p == NULL) {
        *p = (struct Vertex*)malloc(sizeof(struct Vertex));
        (*p)->data = data;
        (*p)->count = count;
        (*p)->Left = NULL;
        (*p)->Right = NULL;
        (*p)->use = 0;
    }

    return 0;
}

int count_occurrences(record data, node *record_list) {
    int count = 0;
    node *current = record_list;
    int target_year = extract_year(data.date_check_in);
    
    while (current != NULL) {
        int current_year = extract_year(current->data.date_check_in);
        if (current_year == target_year) {
            count++;
        }
        current = current->next_node;
    }
    return count;
}

int collect_all_records(struct Vertex V[], node *record_list, int max_size) {
    node *current = record_list;
    int record_count = 0;
    
    while (current != NULL && record_count < max_size) {
     
        V[record_count].data = current->data;
        V[record_count].count = count_occurrences(current->data, record_list);
        V[record_count].use = 0;
        
        record_count++;
        current = current->next_node;
    }
    
    return record_count;
}

int A1(struct Vertex** root, struct Vertex V[], int record_count){
    for(int i = 0; i < record_count; i++){
        V[i].use = 0;
    }

    for(int i = 0; i < record_count; i++){
        int max_count = 0;
        int index = 0;
        
  
        for(int j = 0; j < record_count; j++){
            if (V[j].count > max_count && V[j].use == 0) {
                max_count = V[j].count;
                index = j;
            }
        }
        
        if (max_count == 0) break;
        
        V[index].use = 1; 
        SDP(root, V[index].data, V[index].count);
    }
    
    return 0;
}

void obhod_root_left_right_collect(struct Vertex *current, node **head, node **tail) {
    if(current != NULL){

        node *new_node = (node *)malloc(sizeof(node));
        new_node->data = current->data;
        new_node->next_node = NULL;
        new_node->prev_node = NULL;
        
      
        if (*head == NULL) {
            *head = new_node;
            *tail = new_node;
        } else {
            (*tail)->next_node = new_node;
            new_node->prev_node = *tail;
            *tail = new_node;
        }
        
        obhod_root_left_right_collect(current->Left, head, tail);
        obhod_root_left_right_collect(current->Right, head, tail);
    }
}

void free_tree(struct Vertex *root) {
    if (root != NULL) {
        free_tree(root->Left);
        free_tree(root->Right);
        free(root);
    }
}

void build_tree_from_queue(struct Vertex** root, queue *q) {

    if (*root != NULL) {
        free_tree(*root);
        *root = NULL;
    }
    
    if (q == NULL || q->head == NULL) {
        printf("     [info] Очередь пуста, дерево не построено!\n");
        return;
    }
    
    node *current = q->head;
    int count = 0;
    
    while (current != NULL && count < MAX_SIZE) {
 
        SDP(root, current->data, 1);
        current = current->next_node;
        count++;
    }
    
    printf("     [info] Построено дерево из %d записей (результатов поиска)\n", count);
}

void display_tree_as_table(struct Vertex *root, char* title) {
    if (root == NULL) {
        printf("     [info] Дерево пусто!\n");
        printf("     Нажмите любую клавишу для возврата в меню...");
        _getch();
        return;
    }
    

    node *tree_list_head = NULL;
    node *tree_list_tail = NULL;
    obhod_root_left_right_collect(root, &tree_list_head, &tree_list_tail);
    

    system("cls");
    printf("     %s\n\n", title);
    
    int counter = 1;
    node *start_of_page = tree_list_head;

    while (1) {
        system("cls");
        printf("     %s\n\n", title);
        header();
        node *current = start_of_page;
        int nodes_on_page = 0;
        int absolute_number = 1;

 
        node *temp = tree_list_head;
        while (temp != NULL && temp != start_of_page) {
            absolute_number++;
            temp = temp->next_node;
        }

        for (int i = 0; i < 20; i++) {
            if (current == NULL) {
                break;
            }
            
            printf("| %2d|    %s |    %s |    %d |    %4d |    %s |\n", 
                   absolute_number + i, 
                   current->data.name, 
                   current->data.street_name, 
                   current->data.house_num, 
                   current->data.flat_num, 
                   current->data.date_check_in);
            current = current->next_node;
            nodes_on_page++;
        }
        tailer(counter);

        printf("\nРежим: Дерево (построено из результатов поиска)\n");
       

        if (nodes_on_page < 20) {
             printf("[info] Конец списка!\n");
        }
        
        char c = _getch();

        switch (c) {
            case 'm': 
                while (tree_list_head != NULL) {
                    node *temp = tree_list_head;
                    tree_list_head = tree_list_head->next_node;
                    free(temp);
                }
                goto exit_loop;
            
            case 'n': 
                if (current != NULL) {
                    start_of_page = current;
                    counter++;
                } else {
                    printf("[info] Вы уже на последней странице.\n");
                    printf("Нажмите любую клавишу для продолжения...");
                    _getch(); 
                }
                break;
                
            case 'b': 
                if (counter > 1 && start_of_page != tree_list_head) {
                    start_of_page = start_of_page->prev_node;
                    for (int i = 0; i < 19; i++) {
                        if (start_of_page->prev_node == NULL) break;
                        start_of_page = start_of_page->prev_node;
                    }
                    counter--;
                } else {
                    printf("[info] Вы на первой странице.\n");
                    printf("Нажмите любую клавишу для продолжения...");
                    _getch(); 
                }
                break;

            case 'p': { 
                int d;
                printf("\nВведите номер страницы: ");
                scanf("%d", &d);
                if (d > 0) {
                    start_of_page = tree_list_head;
                    for (int i = 0; i < (d - 1) * 20; i++) {
                        if (start_of_page == NULL) {
                            printf("[info] Такой страницы не существует!\n");
                            printf("Нажмите любую клавишу для продолжения...");
                            _getch(); 
                            start_of_page = tree_list_head; 
                            counter = 1;
                            goto continue_loop;
                        }
                        start_of_page = start_of_page->next_node;
                    }
                
                    counter = d;
                }
                else{
                    printf("[info] Такой страницы не существует!\n");
                    printf("Нажмите любую клавишу для продолжения...");
                    _getch(); 
                }
                break;
            }
                
            default:
                printf("[erro] Неизвестная команда!\n");
                printf("Нажмите любую клавишу для продолжения...");
                _getch(); 
                break;
        }
    continue_loop:;
    }
    
exit_loop:;
}


void binary_search_tree_recursive(struct Vertex *root, int target_year, queue *result_queue) {
    if (root == NULL) {
        return;
    }
    
    int current_year = extract_year(root->data.date_check_in);
    
    if (current_year > target_year) {
        binary_search_tree_recursive(root->Left, target_year, result_queue);
    }
    else if (current_year < target_year) {
        binary_search_tree_recursive(root->Right, target_year, result_queue);
    }
    else {
        node *new_node = (node *)malloc(sizeof(node));
        new_node->data = root->data;
        new_node->next_node = NULL;
        new_node->prev_node = NULL;
        
        if (result_queue->head == NULL) {
            result_queue->head = new_node;
            result_queue->tail = new_node;
        } else {
            result_queue->tail->next_node = new_node;
            new_node->prev_node = result_queue->tail;
            result_queue->tail = new_node;
        }
          
        binary_search_tree_recursive(root->Left, target_year, result_queue);
        binary_search_tree_recursive(root->Right, target_year, result_queue);
    }
}

void print_tree_years(struct Vertex *root) {
    if (root == NULL) return;
    
    struct Vertex *stack[1000];
    int top = -1;
    struct Vertex *current = root;
    int years[100] = {0};
    int year_count = 0;
    
    printf("     [debug] Годы в дереве:\n");
    
    while (current != NULL || top >= 0) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->Left;
        }
        
        current = stack[top--];
        
        int current_year = extract_year(current->data.date_check_in);
        
        int found = 0;
        for (int i = 0; i < year_count; i++) {
            if (years[i] == current_year) {
                found = 1;
                break;
            }
        }
        
        if (!found) {
            years[year_count++] = current_year;
            printf("     [debug] Год: %d, дата: %s\n", current_year, current->data.date_check_in);
        }
        
        current = current->Right;
    }
}


queue* binary_search_tree_wrapper(struct Vertex *root, int target_year) {
    queue *result_queue = (queue*)malloc(sizeof(queue));
    result_queue->head = result_queue->tail = NULL;
       
    binary_search_tree_recursive(root, target_year, result_queue);
    
    printf("     [debug] Найдено записей: %d\n", queue_count(result_queue));
    
    return result_queue;
}

node **original_index_array = NULL;
node **sorted_index_array = NULL;
queue *search_results_queue = NULL; 
queue *tree_search_results_queue = NULL;
int view_mode = 0;


void gilbert_moor(float p[256], int a[256], int c[256][256], int lenght[256])
{   
    const int n = 256;

    bool swapped = true;
    while (swapped)
    { 
        swapped = false;
        for (int i = 1; i < n; i++)
        {
            if (p[i - 1] > p[i])
            { 
                float tp = p[i - 1];
                p[i - 1] = p[i];
                p[i] = tp;

                int ta = a[i - 1];
                a[i - 1] = a[i];
                a[i] = ta;

                swapped = true;
            }
        }
    }

    float Q = 0.0;
    float q[n];

    for (int i = 0; i < n; i++)
    {
        if (p[i] > 0) {
            q[i] = Q + p[i] / 2.0;  
            lenght[i] = ceil(-log2(p[i])) + 1;
        } else {
            q[i] = 0;
            lenght[i] = 0;
        }

        Q += p[i];
    }

    for (int i = 0; i < n; i++)
    {
        if (lenght[i] > 0 && p[i] > 0)
        {
            float t = q[i];
            for (int j = 1; j <= lenght[i]; j++)
            {
                t *= 2.0;
                if (t >= 1.0) {
                    c[i][j] = 1;
                    t -= 1.0;
                } else {
                    c[i][j] = 0;
                }
            }
        }
    }
}

void menu(node * record_list){
    char c;
    int sort_flag = 0;
    print_menu();
    
    view_mode = 0;
    
    
    
    int array_size = 0;
    
    struct Vertex *tree_root = NULL;
    
    
    original_index_array = list_to_array(record_list, &array_size);
    
    while ((c = _getch())) {
        switch(c){
            case 'q':
                
                while (record_list != NULL) {
                    node *temp = record_list;
                    record_list = record_list->next_node;
                    free(temp);
                }
                if (sorted_index_array!= NULL) {
                    free(sorted_index_array);
                }
                if (original_index_array!= NULL) {
                    free(original_index_array);
                }
                if (search_results_queue != NULL) {
                    free_queue(search_results_queue);
                }
                if (tree_search_results_queue != NULL) {
                    free_queue(tree_search_results_queue);
                }
                if (tree_root != NULL) {
                    free_tree(tree_root);
                }
                exit(0);
                
            case 'p':
                printf("     [info] Режим просмотра: ");
                if (view_mode == 0){ 
                    printf("Оригинальная база\n");
                    print_array(original_index_array,array_size);
                }

                else if (view_mode == 1){ 
                    printf("Отсортированная база\n");
                    print_array(sorted_index_array,array_size);
                }

                else if (view_mode == 2) {
                    
                    int count = queue_count(search_results_queue);
                    printf("Результаты поиска (%d записей)\n", count);
                    print_queue(search_results_queue);
                }
                else if (view_mode == 3) {
                    int count = queue_count(tree_search_results_queue);
                    printf("Результаты поиска в дереве (%d записей)\n", count);
                    print_queue(tree_search_results_queue);
                }
            
                print_menu();
                break;
                
            case 's':
                if (sort_flag == 0){
                    sorted_index_array = DigitalSort(original_index_array, array_size, 0);
                    sort_flag = 1;
                    printf("     [info] Индексный массив отсортирован успешно!\n");
                }
                
               

                view_mode = 1;
                printf("     [info] Установлен режим просмотра: Отсортированная база (через индексный массив)\n");
                break;
            case 'r':
        
                view_mode = 0;
                printf("     [info] Установлен режим просмотра: Оригинальная база\n");
                break;
                
            case 'b':  
                if (sort_flag == 0) {
                    printf("     [error] Сначала отсортируйте базу данных!\n");
                } else if (sorted_index_array == NULL) {
                    printf("     [error] Отсортированный индексный массив не создан!\n");
                } else {
                    char search_prefix[4];
                    printf("     Введите первые 3 буквы названия улицы: ");
                    scanf("%3s", search_prefix);
                    
                    if (search_results_queue != NULL) {
                        free_queue(search_results_queue);
                        search_results_queue = NULL;
                    }
                    
                    
                    search_results_queue = binary_search_three_letters(search_prefix, sorted_index_array, array_size);
                    int found_count = queue_count(search_results_queue);
                    
                    if (found_count > 0) {
                        printf("     [info] Найдено записей: %d\n", found_count);
                        view_mode = 2;
                        printf("     [info] Установлен режим просмотра: Результаты поиска\n");
                    } else {
                        printf("     [info] Записи с улицами, начинающимися на '%s' не найдены.\n", search_prefix);
                    }
                }
                break;

            case 't':  
                if (search_results_queue == NULL || search_results_queue->head == NULL) {
                    printf("     [error] Сначала выполните поиск (команда 'b')!\n");
                } else {
                    int result_count = queue_count(search_results_queue);
                    printf("     [info] Построение дерева из %d результатов поиска...\n", result_count);
                    build_tree_from_queue(&tree_root, search_results_queue);
                    
                    char title[100];
                    sprintf(title, "ДЕРЕВО (обход корень-лево-право) - построено из %d результатов поиска", result_count);
                    display_tree_as_table(tree_root, title);
                }
                print_menu();
                break;
                
            case 'f':  
                if (tree_root == NULL) {
                    printf("     [error] Сначала постройте дерево (команда 't')!\n");
                } else {
                    int search_year;
                    printf("     Введите год для поиска (например, 95): ");
                    scanf("%d", &search_year);
                    
                    if (tree_search_results_queue != NULL) {
                        free_queue(tree_search_results_queue);
                        tree_search_results_queue = NULL;
                    }
                    
                    printf("     [info] Выполняем бинарный поиск в дереве по году %d...\n", search_year);
                    tree_search_results_queue = binary_search_tree_wrapper(tree_root, search_year);
                    
                    int found_count = queue_count(tree_search_results_queue);
                    if (found_count > 0) {
                        printf("     [info] Найдено записей с годом %d: %d\n", search_year, found_count);
                        view_mode = 3;
                        printf("     [info] Установлен режим просмотра: Результаты поиска в дереве\n");
                        printf("     [info] Нажмите 'p' для просмотра найденных записей\n");
                    } else {
                        printf("     [info] Записи с годом %d не найдены в дереве.\n", search_year);
                    }
                }
                break;
            case 'c': {
            float p[256] = {0};
            int a[256];
            int c[256][256] = {0};
            int lenght[256] = {0};
            int total_chars = 0;

            FILE *Fin = fopen("testBase4.dat", "rb");
            if (Fin == NULL) {
                printf("Error: Cannot open file testBase4.dat\n");
                break;
            }
            
            fseek(Fin, 0, SEEK_END);
            long original_size = ftell(Fin);
            fseek(Fin, 0, SEEK_SET);
            
            int ch;
            while ((ch = fgetc(Fin)) != EOF) {
                p[ch]++;
                total_chars++;
            }
            fclose(Fin);
            
            for (int i = 0; i < 256; i++) {
                a[i] = i;
            }
            
            float total_sum = 0;
            for (int i = 0; i < 256; i++) {
                p[i] = p[i] / total_chars;
                total_sum += p[i];
            }

            printf("Сумма вероятностей: %f\n", total_sum);
            
            gilbert_moor(p, a, c, lenght);
            int exp = 0;
            float kraft = 0.0;
            
            int indices[256];
            int valid_count = 0;
            
            for (int i = 0; i < 256; i++) {
                if (p[i] > 0.000001) {
                    indices[valid_count] = i;
                    valid_count++;
                }
            }
            
            for (int i = 0; i < valid_count - 1; i++) {
                for (int j = 0; j < valid_count - i - 1; j++) {
                    if (p[indices[j]] < p[indices[j + 1]]) {
                        int temp = indices[j];
                        indices[j] = indices[j + 1];
                        indices[j + 1] = temp;
                    }
                }
            }
            
            printf("\nКоды Гилберта-Мура (отсортировано по убыванию вероятностей):\n");
printf("+------+-------------+------------+-----------------+\n");
printf("| Симв | Вероятность | Длина кода | Кодовое слово   |\n");
printf("+------+-------------+------------+-----------------+\n");

int unique = 0;
for (int k = 0; k < valid_count; k++) {
    int i = indices[k]; 
    unique++;
    printf("| ");
    
    int symbol = a[i];
    
    const char* symbol_name = NULL;
    switch(symbol) {
        case 0: symbol_name = "NUL"; break; 
        case 1: symbol_name = "SOH"; break; 
        case 2: symbol_name = "STX"; break; 
        case 3: symbol_name = "ETX"; break; 
        case 4: symbol_name = "EOT"; break; 
        case 5: symbol_name = "ENQ"; break; 
        case 6: symbol_name = "ACK"; break; 
        case 7: symbol_name = "BEL"; break; 
        case 8: symbol_name = "BS "; break; 
        case 9: symbol_name = "TAB"; break; 
        case 10: symbol_name = "LF "; break; 
        case 11: symbol_name = "VT "; break; 
        case 12: symbol_name = "FF "; break; 
        case 13: symbol_name = "CR "; break;  
        case 14: symbol_name = "SO "; break; 
        case 15: symbol_name = "SI "; break; 
        case 16: symbol_name = "DLE"; break; 
        case 17: symbol_name = "DC1"; break;  
        case 18: symbol_name = "DC2"; break;  
        case 19: symbol_name = "DC3"; break; 
        case 20: symbol_name = "DC4"; break; 
        case 21: symbol_name = "NAK"; break; 
        case 22: symbol_name = "SYN"; break;
        case 23: symbol_name = "ETB"; break;  
        case 24: symbol_name = "CAN"; break;
        case 25: symbol_name = "EM "; break; 
        case 26: symbol_name = "SUB"; break;
        case 27: symbol_name = "ESC"; break; 
        case 28: symbol_name = "FS "; break;  
        case 29: symbol_name = "GS "; break;  
        case 30: symbol_name = "RS "; break;  
        case 31: symbol_name = "US "; break;   
        case 32: symbol_name = "SPC"; break; 
        case 127: symbol_name = "DEL"; break; 
    }
    
    if (symbol_name != NULL) {
        printf("%-3s  |", symbol_name);
    } else if (symbol >= 33 && symbol <= 126) {
        printf(" '%c' |", symbol);
    } else {
        printf(" '%c' |", (unsigned char)symbol);
    }
    
    printf(" %11.6f | %11d | ", p[i], lenght[i]);
    exp = -1 * lenght[i];
    kraft += pow(2, exp);
    
    for (int j = 1; j <= lenght[i]; j++) {
        printf("%d", c[i][j]);
    }
    
    int spaces_needed = 15 - lenght[i];
    for (int j = 0; j < spaces_needed; j++) {
        printf(" ");
    }
    printf(" |\n");
}
printf("+------+-------------+------------+-----------------+\n");
            

            float avg_length = 0;
            float entropy = 0;
            for (int i = 0; i < 256; i++) {
                if (p[i] > 0.000001) {
                    avg_length += p[i] * lenght[i];
                    entropy += -1.0 * p[i] * log2(p[i]);
                }
            }
            
            printf("\nСтатистика кодирования:\n");
            printf("Уникальных символов: %d\n", unique);
            printf("Энтропия: %.6f\n", entropy);
            printf("Средняя длина кода: %.6f\n", avg_length);
            printf("Избыточность: %.6f\n", avg_length - entropy);
            printf("Крафт: %.6f\n", kraft);
            

            FILE *fout = fopen("testBase4Coded.dat", "wb"); 
            Fin = fopen("testBase4.dat", "rb");
            
            unsigned char buffer = 0; 
            int bit_count = 0;       
            
            while ((ch = fgetc(Fin)) != EOF) {
                for (int j = 1; j <= lenght[ch]; j++) {
                    buffer = (buffer << 1) | c[ch][j];
                    bit_count++;
                    
                    if (bit_count == 8) {
                        fputc(buffer, fout);
                        buffer = 0;
                        bit_count = 0;
                    }
                }
            }
            
            if (bit_count > 0) {
                buffer = buffer << (8 - bit_count); 
                fputc(buffer, fout);
            }
            
            fclose(Fin);
            fclose(fout);
            

            FILE *fencoded = fopen("testBase4Coded.dat", "rb");
            fseek(fencoded, 0, SEEK_END);
            long encoded_size = ftell(fencoded);
            fclose(fencoded);

            float compression_ratio = 0;
            if (original_size > 0) {
                compression_ratio = (float)encoded_size / original_size * 100.0;
            }
            
            printf("\nИнформация о сжатии:\n");
            printf("Длина исходного файла: %ld байт\n", original_size);
            printf("Длина закодированного файла: %ld байт\n", encoded_size);
            printf("Коэффициент сжатия: %.2f%%\n", compression_ratio);
            
            printf("\nНажмите любую клавишу для продолжения...");
            _getch();
            break;
        }
                
            default:
                printf("     [erro] Неизвестная команда!\n");
        }
    }
}

void print_array(node **index_array, int array_size) {
    int counter = 1;
    int start_index = 0;  

    while (1) {
        system("cls");
        header();
        
        int nodes_on_page = 0;

        for (int i = start_index; i < start_index + 20 && i < array_size; i++) {
            node *current = index_array[i];  
            
            printf("| %2d|    %s |    %s |    %d |    %4d |    %s |\n", 
                   i + 1, 
                   current->data.name, 
                   current->data.street_name, 
                   current->data.house_num, 
                   current->data.flat_num, 
                   current->data.date_check_in);
            nodes_on_page++;
        }
        tailer(counter);

        printf("\nРежим: ");
        if (view_mode == 0) printf("Оригинальная база");
        else if (view_mode == 1) printf("Отсортированная база (через индексный массив)");
        printf("\n");

        if (nodes_on_page < 20) {
            printf("[info] Конец списка! Всего записей: %d\n", array_size);
        } else {
            printf("[info] Записи %d-%d из %d\n", 
                   start_index + 1, 
                   start_index + nodes_on_page, 
                   array_size);
        }
        
        char c = _getch();

        switch (c) {
            case 'm': 
                goto exit_loop;
            
            case 'n': 
                if (start_index + 20 < array_size) {
                    start_index += 20;
                    counter++;
                } else {
                    printf("[info] Вы уже на последней странице.\n");
                    printf("Нажмите любую клавишу для продолжения...");
                    _getch(); 
                }
                break;
                
            case 'b': 
                if (counter > 1) {
                    start_index -= 20;
                    counter--;
                } else {
                    printf("[info] Вы на первой странице.\n");
                    printf("Нажмите любую клавишу для продолжения...");
                    _getch(); 
                }
                break;

            case 'p': { 
                int d;
                printf("\nВведите номер страницы: ");
                scanf("%d", &d);
                
                if (d > 0) {
                    int target_index = (d - 1) * 20;
                    if (target_index < array_size) {
                        start_index = target_index;
                        counter = d;
                    } else {
                        printf("[info] Страница %d не существует. Всего страниц: %d\n", 
                               d, (array_size + 19) / 20);
                        printf("Нажмите любую клавишу для продолжения...");
                        _getch(); 
                    }
                } else {
                    printf("[info] Номер страницы должен быть положительным!\n");
                    printf("Нажмите любую клавишу для продолжения...");
                    _getch(); 
                }
                break;
            }
                
            default:
                printf("[erro] Неизвестная команда!\n");
                printf("Нажмите любую клавишу для продолжения...");
                _getch(); 
                break;
        }
    }
    
exit_loop:;
}

void print_queue(queue *q) {
    if (q == NULL || q->head == NULL) {
        printf("[info] Очередь пуста!\n");
        printf("Нажмите любую клавишу для продолжения...");
        _getch();
        return;
    }

    int counter = 1;
    node *start_of_page = q->head;

    while (1) {
        system("cls");
        header();
        node *current = start_of_page;
        int nodes_on_page = 0;
        int absolute_number = 1;

        
        node *temp = q->head;
        while (temp != NULL && temp != start_of_page) {
            absolute_number++;
            temp = temp->next_node;
        }

        for (int i = 0; i < 20; i++) {
            if (current == NULL) {
                break;
            }
            
            printf("| %2d|    %s |    %s |    %d |    %4d |    %s |\n", 
                   absolute_number + i, 
                   current->data.name, 
                   current->data.street_name, 
                   current->data.house_num, 
                   current->data.flat_num, 
                   current->data.date_check_in);
            current = current->next_node;
            nodes_on_page++;
        }
        tailer(counter);

        printf("\nРежим: ");
        if (view_mode == 2) printf("Результаты поиска (%d записей)", queue_count(q));
        else if (view_mode == 3) printf("Результаты поиска в дереве (%d записей)", queue_count(q));
        printf("\n");

        if (nodes_on_page < 20) {
             printf("[info] Конец списка!\n");
        }
        
        char c = _getch();

        switch (c) {
            case 'm': 
                goto exit_loop;
            
            case 'n': 
                if (current != NULL) {
                    start_of_page = current;
                    counter++;
                } else {
                    printf("[info] Вы уже на последней странице.\n");
                    printf("Нажмите любую клавишу для продолжения...");
                    _getch(); 
                }
                break;
                
            case 'b': 
                if (counter > 1 && start_of_page != q->head) {
                    start_of_page = start_of_page->prev_node;
                    for (int i = 0; i < 19; i++) {
                        if (start_of_page->prev_node == NULL) break;
                        start_of_page = start_of_page->prev_node;
                    }
                    counter--;
                } else {
                    printf("[info] Вы на первой странице.\n");
                    printf("Нажмите любую клавишу для продолжения...");
                    _getch(); 
                }
                break;

            case 'p': { 
                int d;
                printf("\nВведите номер страницы: ");
                scanf("%d", &d);
                if (d > 0) {
                    start_of_page = q->head;
                    for (int i = 0; i < (d - 1) * 20; i++) {
                        if (start_of_page == NULL) {
                            printf("[info] Такой страницы не существует!\n");
                            printf("Нажмите любую клавишу для продолжения...");
                            _getch(); 
                            start_of_page = q->head; 
                            counter = 1;
                            goto continue_loop;
                        }
                        start_of_page = start_of_page->next_node;
                    }
                
                    counter = d;
                }
                else{
                    printf("[info] Такой страницы не существует!\n");
                    printf("Нажмите любую клавишу для продолжения...");
                    _getch(); 
                }
                break;
            }
                
            default:
                printf("[erro] Неизвестная команда!\n");
                printf("Нажмите любую клавишу для продолжения...");
                _getch(); 
                break;
        }
    continue_loop:;
    }
    
exit_loop:;
}

node** DigitalSort(node **index_array, int size, int flag) {
    queue Q[257];
    node *p;
    
    
    node **temp_array = (node**)malloc(size * sizeof(node*));
    for (int i = 0; i < size; i++) {
        temp_array[i] = index_array[i];
    }
    
    for (int j = 10; j >= 0; j--) {
    
        for (int i = 0; i < 256; i++) {
            Q[i].tail = Q[i].head = NULL;
        }

     
        for (int i = 0; i < size; i++) {
            node *current = temp_array[i];
            int d;
            
            if (flag == 0) {
               
                if (current->data.house_num == 0)
                    d = 0;
                else
                    d = current->data.house_num;
            }
            else {
     
                if (current->data.street_name[j] == ' ')
                    d = 0;
                else
                    d = current->data.street_name[j] + 129;
            }
            
            p = Q[d].tail;
            if (Q[d].head == NULL)
                Q[d].head = current;
            else
                p->next_node = current;

            p = Q[d].tail = current;
            current->next_node = NULL;
        }
        

        int idx = 0;
        for (int k = 0; k < 256; k++) {
            node *current = Q[k].head;
            while (current != NULL) {
                temp_array[idx++] = current;
                current = current->next_node;
            }
        }
    }
    
    if (flag == 0) {
        node **result = DigitalSort(temp_array, size, 1);
        free(temp_array);
        return result;
    }
    else {
        printf("     [info] Индексный массив отсортирован успешно!\n");
        return temp_array;
    }
}

int main(){
    system("chcp 866 > nul");

    FILE * file;
    file = fopen("testBase4.dat", "rb");
    if (file == NULL){
        printf("     [error] Не удалось открыть файл!\n");
        return 1;
    }
    node * record_list = read_records(file);
    fclose(file);
   
    menu(record_list);
    
    return 0;
}
 
 

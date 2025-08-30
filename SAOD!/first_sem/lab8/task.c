#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 4
#define R 0
#define L 6

struct client{
    char name[L];
    char s_name[L];
    char surname[L];
    long phone;
}typedef  client ;

long randomm(long a, long b) {

    return a + rand() % (b - a + 1);
}

int printBaseS(client client_base){
   
    printf("--------------------------------------------------------------------\n");
    //for(int i = 0; i < N; i++){
        //printf("|  %d  | ", i+1);
        for(int j = 0; j < L; j++){
            printf("%c", client_base.name[j]);
        }
        printf("       | ");
        for(int j = 0; j < L; j++){
            printf("%c", client_base.s_name[j]);
        }
        printf("       | ");
        for(int j = 0; j < L; j++){
            printf("%c", client_base.surname[j]);
        }
        printf("       | ");
        printf("%ld", client_base.phone);
        printf("       |\n");
    }
//}

int Bsearch_v2_name(client client_base[N], char* X, int ar[N]) {
    int Ll = 0;
    int Rr = N - 1;
    int m;

    // 1. Находим ЛЕВУЮ ГРАНИЦУ совпадений (первое вхождение)
    while (Ll < Rr) {
        m = (Ll + Rr) / 2;
        if (strcmp(client_base[ar[m]].name, X) < 0) {
            Ll = m + 1;
        } else {
            Rr = m;
        }
    }

    // 2. Проверяем, есть ли вообще совпадения
    if (strcmp(client_base[ar[Rr]].name, X) != 0) {
        return 0; // Не найдено
    }

    // 3. Теперь ищем ПРАВУЮ ГРАНИЦУ (последнее вхождение)
    int left = Rr; // Запоминаем первое вхождение
    int right = N - 1;
    while (Ll < right) {
        m = (Ll + right + 1) / 2; // Смещаем середину вправо, чтобы не зациклиться
        if (strcmp(client_base[ar[m]].name, X) > 0) {
            right = m - 1;
        } else {
            Ll = m;
        }
    }
    int last = Ll; // Последнее вхождение

    // 4. Выводим ВСЕ совпадения от left до last
    for (int i = left; i <= last; i++) {
        printBaseS(client_base[ar[i]]);
    }

    return 1; // Найдено
}


int Bsearch_v2_s_name(client client_base[N], char* X, int ar[N]) {
    int Ll = 0;
    int Rr = N - 1;
    int m;

    // 1. Находим ЛЕВУЮ ГРАНИЦУ совпадений (первое вхождение)
    while (Ll < Rr) {
        m = (Ll + Rr) / 2;
        if (strcmp(client_base[ar[m]].s_name, X) < 0) {
            Ll = m + 1;
        } else {
            Rr = m;
        }
    }

    // 2. Проверяем, есть ли вообще совпадения
    if (strcmp(client_base[ar[Rr]].s_name, X) != 0) {
        return 0; // Не найдено
    }

    // 3. Теперь ищем ПРАВУЮ ГРАНИЦУ (последнее вхождение)
    int left = Rr; // Запоминаем первое вхождение
    int right = N - 1;
    while (Ll < right) {
        m = (Ll + right + 1) / 2; // Смещаем середину вправо, чтобы не зациклиться
        if (strcmp(client_base[ar[m]].s_name, X) > 0) {
            right = m - 1;
        } else {
            Ll = m;
        }
    }
    int last = Ll; // Последнее вхождение

    // 4. Выводим ВСЕ совпадения от left до last
    for (int i = left; i <= last; i++) {
        printBaseS(client_base[ar[i]]);
    }

    return 1; // Найдено
}

int Bsearch_v2_surname(client client_base[N], char* X, int ar[N]) {
    int Ll = 0;
    int Rr = N - 1;
    int m;

    // 1. Находим ЛЕВУЮ ГРАНИЦУ совпадений (первое вхождение)
    while (Ll < Rr) {
        m = (Ll + Rr) / 2;
        if (strcmp(client_base[ar[m]].surname, X) < 0) {
            Ll = m + 1;
        } else {
            Rr = m;
        }
    }

    // 2. Проверяем, есть ли вообще совпадения
    if (strcmp(client_base[ar[Rr]].surname, X) != 0) {
        return 0; // Не найдено
    }

    // 3. Теперь ищем ПРАВУЮ ГРАНИЦУ (последнее вхождение)
    int left = Rr; // Запоминаем первое вхождение
    int right = N - 1;
    while (Ll < right) {
        m = (Ll + right + 1) / 2; // Смещаем середину вправо, чтобы не зациклиться
        if (strcmp(client_base[ar[m]].surname, X) > 0) {
            right = m - 1;
        } else {
            Ll = m;
        }
    }
    int last = Ll; // Последнее вхождение

    // 4. Выводим ВСЕ совпадения от left до last
    for (int i = left; i <= last; i++) {
        printBaseS(client_base[ar[i]]);
    }

    return 1; // Найдено
}

int Bsearch_v2_phone(client client_base[N], long X, int ar[N]) {
    int Ll = 0;
    int Rr = N - 1;
    int m;

    // 1. Находим ЛЕВУЮ ГРАНИЦУ совпадений (первое вхождение)
    while (Ll < Rr) {
        m = Ll + (Rr - Ll) / 2; // Защита от переполнения
        if (client_base[ar[m]].phone < X) {
            Ll = m + 1;
        } else {
            Rr = m;
        }
    }

    // 2. Проверяем, есть ли вообще совпадения
    if (client_base[ar[Rr]].phone != X) {
        return 0; // Не найдено
    }

    // 3. Теперь ищем ПРАВУЮ ГРАНИЦУ (последнее вхождение)
    int left = Rr; // Запоминаем первое вхождение
    int right = N - 1;
    while (Ll < right) {
        m = Ll + (right - Ll + 1) / 2; // Смещаем середину вправо
        if (client_base[ar[m]].phone > X) {
            right = m - 1;
        } else {
            Ll = m;
        }
    }
    int last = Ll; // Последнее вхождение

    // 4. Выводим ВСЕ совпадения от left до last
    for (int i = left; i <= last; i++) {
        printBaseS(client_base[ar[i]]);
    }

    return 1; // Найдено
}

void fillBase(client client_base[N]){
    if(R == 1){
        for(int i = 0; i < N; i++){
            // char * namec  = (char*)(calloc(5,sizeof(char)));
            // char * s_namec  = (char*)(calloc(5,sizeof(char)));
            // char * surnamec  = (char*)(calloc(5,sizeof(char)));
            for(int j = 0; j < L; j++){
                client_base[i].name[j]= randomm(97,122);
                client_base[i].s_name[j]= randomm(97,122);
                client_base[i].surname[j]= randomm(97,122);
            }
            client_base[i].phone=randomm(8000000000,8999999999);
    
        }
    }
    else{
        strcpy(client_base[0].s_name , "volev");
        strcpy(client_base[0].name ,"konst");
        strcpy(client_base[0].surname , "sergy");
        client_base[0].phone = 1111111111;

        strcpy(client_base[1].s_name, "antro");
        strcpy(client_base[1].name, "danil");
        strcpy(client_base[1].surname, "pavlo");
        client_base[1].phone = 2222222222;

        strcpy(client_base[2].s_name, "volev");
        strcpy(client_base[2].name, "danil");
        strcpy(client_base[2].surname, "anton");
        client_base[2].phone = 3333333333;

        strcpy(client_base[3].s_name, "zhaim");
        strcpy(client_base[3].name, "danil");
        strcpy(client_base[3].surname, "andre");
        client_base[3].phone = 4444444444;
        
    }
}

void printBase(client client_base[N]){
    printf("|  N  |    name     | second name |    surname  |  number          |\n");
    printf("--------------------------------------------------------------------\n");
    for(int i = 0; i < N; i++){
        printf("|  %d  | ", i+1);
        for(int j = 0; j < L; j++){
            printf("%c", client_base[i].name[j]);
        }
        printf("       | ");
        for(int j = 0; j < L; j++){
            printf("%c", client_base[i].s_name[j]);
        }
        printf("       | ");
        for(int j = 0; j < L; j++){
            printf("%c", client_base[i].surname[j]);
        }
        printf("       | ");
        printf("%ld", client_base[i].phone);
        printf("       |\n");
        printf("--------------------------------------------------------------------\n");
    }
}

void printBase1(client client_base[N], int a[N]){
    printf("|  N  |    name     | second name |    surname  |  number          |\n");
    printf("--------------------------------------------------------------------\n");
    for(int i = 0; i < N; i++){
        printf("|  %d  | ", i+1);
        for(int j = 0; j < L; j++){
            printf("%c", client_base[a[i]].name[j]);
        }
        printf("       | ");
        for(int j = 0; j < L; j++){
            printf("%c", client_base[a[i]].s_name[j]);
        }
        printf("       | ");
        for(int j = 0; j < L; j++){
            printf("%c", client_base[a[i]].surname[j]);
        }
        printf("       | ");
        printf("%ld", client_base[a[i]].phone);
        printf("       |\n");
        printf("--------------------------------------------------------------------\n");
    }
}





int less(client client_base1,client client_base2, int key){
   
    char * X1;
    char * Y1;

  
    char * X2;
    char * Y2;
    int temp1;
    int temp2;

    if(key == 1){
        X1 = client_base1.name;
        Y1 = client_base2.name;
        temp1 =strcmp(X1,Y1);
    }
    else if(key == 2){
        X1 = client_base1.s_name;
        Y1 = client_base2.s_name;
        temp1 =strcmp(X1,Y1);
    }
    else if(key == 3){
        X1 = client_base1.surname;
        Y1 = client_base2.surname;
        temp1 =strcmp(X1,Y1);
    }
    else if(key == 4){
        long* X1i = (long*)client_base1.phone;
        long* Y1i = (long*)client_base2.phone;
        if (X1i<Y1i){
            temp1 = 1;
        }
        else{
            temp1 = -1;
        }
    }
    
    if(temp1<0){
        return (1);
    }
    else if(temp1>0){
        return (0);
    }
    else{
        if(temp2 < 0){
            return(1);
        }
        else{
            return(0);
        }
    }
}


int more(client client_base1,client client_base2, int key){
      
    char * X1;
    char * Y1;

  
    char * X2;
    char * Y2;
    int temp1;
    int temp2;

    if(key == 1){
        X1 = client_base1.name;
        Y1 = client_base2.name;
        temp1 =strcmp(X1,Y1);
    }
    else if(key == 2){
        X1 = client_base1.s_name;
        Y1 = client_base2.s_name;
        temp1 =strcmp(X1,Y1);
    }
    else if(key == 3){
        X1 = client_base1.surname;
        Y1 = client_base2.surname;
        temp1 =strcmp(X1,Y1);
    }
    else if(key == 4){
        long* X1i = (long*)client_base1.phone;
        long* Y1i = (long*)client_base2.phone;
        if (X1i<Y1i){
            temp1 = 1;
        }
        else{
            temp1 = -1;
        }
    }
    
    
    if(temp1>0){
        return (1);
    }
    else if(temp1<0){
        return (0);
    }
    else{
        if(temp2 > 0){
            return(1);
        }
        else{
            return(0);
        }
    }
}




void selectionSortU(client client_base[N],int ar[N], int key){
    int n  = N;
    for(int i = 0; i < n-1; i++){
        int k = i;//(*M)++;
        for (int j = i+1; j < n; j++){
            if(less(client_base[ar[j]],client_base[ar[k]],key)){
                k = j;//(*M)++;
            }
        }
        int temp = ar[i];
        ar[i] = ar[k];
        ar[k] = temp;
    }

}

void selectionSortD(client client_base[N],int ar[N], int key){
    int n  = N;
    for(int i = 0; i < n-1; i++){
        int k = i;//(*M)++;
        for (int j = i+1; j < n; j++){
            if(more(client_base[ar[j]],client_base[ar[k]],key)){
                k = j;//(*M)++;
            }
        }
        int temp = ar[i];
        ar[i] = ar[k];
        ar[k] = temp;
    }

}

void PrintMas(int * A, int n){
    for (int i = 0; i < n; i++ ){
        printf("%d",A[i]);
        printf(" ");
    }
} 



int main(){
    char direct;
    int key1;
    int key2;
    
    srand(time(NULL));
    client client_base[N];
    int index_ar_first[N];
    int index_ar_second[N];
    for(int i = 0;i < N; i++){
        index_ar_first[i] = index_ar_second[i] = i;
    }
    fillBase(client_base);
    printBase(client_base);
    printf("первый индексный массив: ");
    PrintMas(index_ar_first,N);
    printf("\n");
    printf("второй индексный массив: ");
    PrintMas(index_ar_second,N);
    printf("\n");
    printf("\n");


    printf("как сортируем? по убыванию - D  ,  по возростанию - U : ");
    scanf("%c", &direct);
    printf("первый ключ? 1 - имя , 2 - фамилия  , 3 - отчество , 4 - номер: ");
    scanf("%d", &key1);
    printf("второй ключ? 1 - имя , 2 - фамилия  , 3 - отчество , 4 - номер: ");
    scanf("%d", &key2);
    if(direct == 'D'){
        selectionSortD(client_base,index_ar_first,key1);
        selectionSortD(client_base,index_ar_second,key2);
    }
    else if(direct == 'U'){
        selectionSortU(client_base,index_ar_first,key1);
        selectionSortU(client_base,index_ar_second,key2);
    }

    printBase1(client_base,index_ar_first);
    printf("первый индексный массив: ");
    PrintMas(index_ar_first,N);



    printf("\n");
    printf("\n");

    if (key1 == 1){
        char X[10];
        scanf("%s", X);
        strtok(X,"\n");
        printf("%d", Bsearch_v2_name(client_base, X,index_ar_first));
    }
    else if (key1 == 2){
        char X[10];
        scanf("%s", X);
        strtok(X,"\n");
        printf("%d",Bsearch_v2_s_name(client_base, X, index_ar_first));
    }
    else if (key1 == 3){
        char X[10];
        scanf("%s", X);
        strtok(X,"\n");
        printf("%d",Bsearch_v2_surname(client_base, X, index_ar_first));
    }
    else if (key1 == 4){
        long X;
        scanf("%ld", &X);
        printf("%d",Bsearch_v2_phone(client_base, X, index_ar_first));
    }
    printf("\n");
    printf("\n");
    printf("\n");
    printBase1(client_base,index_ar_second);
    printf("второй индексный массив: ");
    PrintMas(index_ar_second,N);
    printf("\n");

    
    


    if (key2 == 1){
        char X[10];
        scanf("%s", X);
        strtok(X,"\n");
        printf("%d", Bsearch_v2_name(client_base, X,index_ar_second));
    }
    else if (key2 == 2){
        char X[10];
        scanf("%s", X);
        strtok(X,"\n");
        printf("%d",Bsearch_v2_s_name(client_base, X, index_ar_second));
    }
    else if (key2 == 3){
        char X[10];
        scanf("%s", X);
        strtok(X,"\n");
        printf("%d",Bsearch_v2_surname(client_base, X, index_ar_second));
    }
    else if (key2 == 4){
        long X;
        scanf("%ld", &X);
        printf("%d",Bsearch_v2_phone(client_base, X, index_ar_second));
    }

}
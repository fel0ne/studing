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

int Bsearch_v1_name(client client_base[N], char* X) {
    int n = N;
    int Ll = 0;
    int Rr = n - 1;
    int m;
    while (Ll <= Rr) {
        m = (Ll + Rr) / 2;
        if (strcmp(client_base[m].name , X) == 0) {
            printBaseS(client_base[m]);
        }
        if (strcmp(client_base[m].name , X) < 0) {
            Ll = m + 1;
        } else {
            Rr = m - 1;
        }
    }
    return 0; // Элемент не найден
}

int Bsearch_v1_s_name(client client_base[N], char* X) {
    int n = N;
    int Ll = 0;
    int Rr = n - 1;
    int m;
    while (Ll <= Rr) {
        m = (Ll + Rr) / 2;
         if (strcmp(client_base[m].s_name , X) == 0) {
            printBaseS(client_base[m]);
        }
        if (strcmp(client_base[m].s_name , X) < 0) {
            Ll = m + 1;
        } else {
            Rr = m - 1;
        }
    }
    return 0; // Элемент не найден
}

int Bsearch_v1_surname(client client_base[N], char* X) {
    int n = N;
    int Ll = 0;
    int Rr = n - 1;
    int m;
    while (Ll <= Rr) {
        m = (Ll + Rr) / 2;
         if (strcmp(client_base[m].surname , X) == 0) {
            printBaseS(client_base[m]);
        }
        if (strcmp(client_base[m].surname , X) < 0) {
            Ll = m + 1;
        } else {
            Rr = m - 1;
        }
    }
    return 0; // Элемент не найден
}

int Bsearch_v1_phone(client client_base[N], long X) {
    int n = N;
    int Ll = 0;
    int Rr = n - 1;
    int m;
    while (Ll <= Rr) {
        m = (Ll + Rr) / 2;
         if (client_base[m].phone == 0) {
            printBaseS(client_base[m]);
        }
        if (client_base[m].phone  < 0) {
            Ll = m + 1;
        } else {
            Rr = m - 1;
        }
    }
    return 0; // Элемент не найден
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
        strcpy(client_base[0].surname , "nllll");
        client_base[0].phone = 1111111111;

        strcpy(client_base[1].s_name, "antro");
        strcpy(client_base[1].name, "danil");
        strcpy(client_base[1].surname, "nllll");
        client_base[1].phone = 2222222222;

        strcpy(client_base[2].s_name, "volev");
        strcpy(client_base[2].name, "pavel");
        strcpy(client_base[2].surname, "nllll");
        client_base[2].phone = 3333333333;

        strcpy(client_base[3].s_name, "zhaim");
        strcpy(client_base[3].name, "bogda");
        strcpy(client_base[3].surname, "nllll");
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





int less(client client_base1,client client_base2, int key1, int key2 ){
   
    char * X1;
    char * Y1;

  
    char * X2;
    char * Y2;
    int temp1;
    int temp2;

    if(key1 == 1){
        X1 = client_base1.name;
        Y1 = client_base2.name;
        temp1 =strcmp(X1,Y1);
    }
    else if(key1 == 2){
        X1 = client_base1.s_name;
        Y1 = client_base2.s_name;
        temp1 =strcmp(X1,Y1);
    }
    else if(key1 == 3){
        X1 = client_base1.surname;
        Y1 = client_base2.surname;
        temp1 =strcmp(X1,Y1);
    }
    else if(key1 == 4){
        long* X1i = (long*)client_base1.phone;
        long* Y1i = (long*)client_base2.phone;
        if (X1i<Y1i){
            temp1 = 1;
        }
        else{
            temp1 = -1;
        }
    }
    

    if(key2 == 1){
        X2 = client_base1.name;
        Y2 = client_base2.name;
        temp2 =strcmp(X2,Y2);
    }
    else if(key2 == 2){
        X2 = client_base1.s_name;
        Y2 = client_base2.s_name;
        temp2 =strcmp(X2,Y2);
    }
    else if(key2 == 3){
        X2 = client_base1.surname;
        Y2 = client_base2.surname;
        temp2 =strcmp(X2,Y2);
    }
    else if(key2 == 4){
        long* X2i = (long*)client_base1.phone;
        long* Y2i = (long*)client_base2.phone;
        if (X2i<Y2i){
            temp2 = 1;
        }
        else{
            temp2 = -1;
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


int more(client client_base1,client client_base2, int key1, int key2 ){
      
    char * X1;
    char * Y1;

  
    char * X2;
    char * Y2;
    int temp1;
    int temp2;

    if(key1 == 1){
        X1 = client_base1.name;
        Y1 = client_base2.name;
        temp1 =strcmp(X1,Y1);
    }
    else if(key1 == 2){
        X1 = client_base1.s_name;
        Y1 = client_base2.s_name;
        temp1 =strcmp(X1,Y1);
    }
    else if(key1 == 3){
        X1 = client_base1.surname;
        Y1 = client_base2.surname;
        temp1 =strcmp(X1,Y1);
    }
    else if(key1 == 4){
        long* X1i = (long*)client_base1.phone;
        long* Y1i = (long*)client_base2.phone;
        if (X1i<Y1i){
            temp1 = 1;
        }
        else{
            temp1 = -1;
        }
    }
    

    if(key2 == 1){
        X2 = client_base1.name;
        Y2 = client_base2.name;
        temp2 =strcmp(X2,Y2);
    }
    else if(key2 == 2){
        X2 = client_base1.s_name;
        Y2 = client_base2.s_name;
        temp2 =strcmp(X2,Y2);
    }
    else if(key2 == 3){
        X2 = client_base1.surname;
        Y2 = client_base2.surname;
        temp2 =strcmp(X2,Y2);
    }
    else if(key2 == 4){
        long* X2i = (long*)client_base1.phone;
        long* Y2i = (long*)client_base2.phone;
        if (X2i<Y2i){
            temp2 = 1;
        }
        else{
            temp2 = -1;
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




void selectionSortU(client client_base[N],int key1, int key2){
    int n  = N;
    for(int i = 0; i < n-1; i++){
        int k = i;//(*M)++;
        for (int j = i+1; j < n; j++){
            if(less(client_base[j],client_base[k],key1,key2)){
                k = j;//(*M)++;
            }
        }
        client temp = client_base[i];
        client_base[i] = client_base[k];
        client_base[k] = temp;
    }

}

void selectionSortD(client client_base[N],int key1, int key2){
    int n  = N;
    for(int i = 0; i < n-1; i++){
        int k = i;//(*M)++;
        for (int j = i+1; j < n; j++){
            if(more(client_base[j],client_base[k],key1,key2)){
                k = j;//(*M)++;
            }
        }
        client temp = client_base[i];
        client_base[i] = client_base[k];
        client_base[k] = temp;
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
    fillBase(client_base);
    printBase(client_base);

    printf("как сортируем? по убыванию - D  ,  по возростанию - U : ");
    scanf("%c", &direct);
    printf("первый ключ? 1 - имя , 2 - фамилия  , 3 - отчество , 4 - номер: ");
    scanf("%d", &key1);
    printf("второй ключ? 1 - имя , 2 - фамилия  , 3 - отчество , 4 - номер: ");
    scanf("%d", &key2);
    if(direct == 'D'){
        selectionSortD(client_base,key1,key2);
    }
    else if(direct == 'U'){
        selectionSortU(client_base,key1,key2);
    }
    printBase(client_base);

    


    // if (key1 == 1){
    //     char X[10];
    //     scanf("%s", X);
    //     strtok(X,"\n");
    //     printf("%d", Bsearch_v1_name(client_base, X));
    // }
    // else if (key1 == 2){
    //     char X[10];
    //     scanf("%s", X);
    //     strtok(X,"\n");
    //     printf("%d",Bsearch_v1_s_name(client_base, X));
    // }
    // else if (key1 == 3){
    //     char X[10];
    //     scanf("%s", X);
    //     strtok(X,"\n");
    //     printf("%d",Bsearch_v1_surname(client_base, X));
    // }
    // else if (key1 == 4){
    //     long X;
    //     scanf("%ld", &X);
    //     printf("%d",Bsearch_v1_phone(client_base, X));
    // }

}
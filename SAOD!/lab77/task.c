#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5

struct client{
    char name[5];
    char s_name[5];
    char surname[5];
    long phone;
}typedef  client ;

long randomm(long a, long b) {
    return a + rand() % (b - a + 1);
}


void fillBase(client client_base[N]){
    for(int i = 0; i < N; i++){
        // char * namec  = (char*)(calloc(5,sizeof(char)));
        // char * s_namec  = (char*)(calloc(5,sizeof(char)));
        // char * surnamec  = (char*)(calloc(5,sizeof(char)));
        for(int j = 0; j < 5; j++){
            client_base[i].name[j]= randomm(97,122);
            client_base[i].s_name[j]= randomm(97,122);
            client_base[i].surname[j]= randomm(97,122);
        }
        client_base[i].phone=randomm(8000000000,8999999999);
    }
}

void printBase(client client_base[N]){
    printf("|  N  |    name     | second name |    surname  |  number          |\n");
    printf("--------------------------------------------------------------------\n");
    for(int i = 0; i < N; i++){
        printf("|  %d  | ", i+1);
        for(int j = 0; j < 5; j++){
            printf("%c", client_base[i].name[j]);
        }
        printf("       | ");
        for(int j = 0; j < 5; j++){
            printf("%c", client_base[i].s_name[j]);
        }
        printf("       | ");
        for(int j = 0; j < 5; j++){
            printf("%c", client_base[i].surname[j]);
        }
        printf("       | ");
        printf("%ld", client_base[i].phone);
        printf("       |\n");
        printf("--------------------------------------------------------------------\n");
    }
}



int less(client client_base1,client client_base2, int key1, int key2 ){
   
    long * X1;
    long * Y1;

  
    long * X2;
    long * Y2;

    if(key1 == 1){
        X1 = (long*)client_base1.name;
        Y1 = (long*)client_base2.name;
    }
    else if(key1 == 2){
        X1 = (long*)client_base1.s_name;
        Y1 = (long*)client_base2.s_name;
    }
    else if(key1 == 3){
        X1 = (long*)client_base1.surname;
        Y1 = (long*)client_base2.surname;
    }
    else if(key1 == 4){
        X1 = (long*)client_base1.phone;
        Y1 = (long*)client_base2.phone;
    }
    

    if(key2 == 1){
        X2 = (long*)client_base1.name;
        Y2 = (long*)client_base2.name;
    }
    else if(key2 == 2){
        X2 = (long*)client_base1.s_name;
        Y2 = (long*)client_base2.s_name;
    }
    else if(key2 == 3){
        X2 = (long*)client_base1.surname;
        Y2 = (long*)client_base2.surname;
    }
    else if(key2 == 4){
        X2 = (long*)client_base1.phone;
        Y2 = (long*)client_base2.phone;
    }
    
    if(X1 < Y1){
        return (1);
    }
    else if(X1 > Y1){
        return (0);
    }
    else{
        if(X2 < Y2){
            return(1);
        }
        else{
            return(0);
        }
    }
}


int more(client client_base1,client client_base2, int key1, int key2 ){
   
    long * X1;
    long * Y1;

  
    long * X2;
    long * Y2;

    if(key1 == 1){
        X1 = (long*)client_base1.name;
        Y1 = (long*)client_base2.name;
    }
    else if(key1 == 2){
        X1 = (long*)client_base1.s_name;
        Y1 = (long*)client_base2.s_name;
    }
    else if(key1 == 3){
        X1 = (long*)client_base1.surname;
        Y1 = (long*)client_base2.surname;
    }
    else if(key1 == 4){
        X1 = (long*)client_base1.phone;
        Y1 = (long*)client_base2.phone;
    }
    

    if(key2 == 1){
        X2 = (long*)client_base1.name;
        Y2 = (long*)client_base2.name;
    }
    else if(key2 == 2){
        X2 = (long*)client_base1.s_name;
        Y2 = (long*)client_base2.s_name;
    }
    else if(key2 == 3){
        X2 = (long*)client_base1.surname;
        Y2 = (long*)client_base2.surname;
    }
    else if(key2 == 4){
        X2 = (long*)client_base1.phone;
        Y2 = (long*)client_base2.phone;
    }
    
    if(X1 > Y1){
        return (1);
    }
    else if(X1 < Y1){
        return (0);
    }
    else{
        if(X2 > Y2){
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


}
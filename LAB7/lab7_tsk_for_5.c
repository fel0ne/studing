
// Задание 6
//рассмотрим идеальные уссловия
//программа расчитана на предложение написаное по всем канонам
#include <stdio.h>
//int len(char ar[]){
//    return(sizeof(ar)/sizeof(ar[0])); //НЕ РАБОТАЕТ((((( очень грустно:( хотя навверное и к лучшему - один раз посчитает и усе
//}
void prints(char s[],int len_s){  //функция вывода строки
    for (int sym = 0; sym < len_s; sym++){
        printf("%c",s[sym]);
    }
}
int Count_Words(char s[],int len_s){ //тут считаем количество слов в предложении(надеемся что дано именно предложение а не непонятный набор символов через пробел) нужно это для следующей функции чтобы создать массив чаров из нужного нам количества элементов
    int temp = 0; // слова я решил считать от пробеллов(чтобы количество пробеллов между словами не влияло на количество слов) (выглядит страшно) temp - переменная которая определяет нужно нам пропустить итерацию цикла или нет                      
    int counter = 0;
    for (int sym  = 0; sym < len_s; sym++){
        if (s[sym] != ' '){
            if (temp == 0){
                counter++;
                temp = 1;
            }
            else{
                continue;
            }    
        }
        else{
            temp = 0;
        }
    }
    return(counter);
}
void First_Syms_in_Words(char s[], int len_s){ // функция которая собирает нам строку из первых букв слов
    int count_words = Count_Words(s,len_s);  // по сути тут написано тоже самое что и в прошлой функции только тут мы сохраняем первые буквеновки а не считаем их количество
    char new_s[count_words]; 
    int temp = 0;
    int i = 0;
    for (int sym  = 0; sym < len_s; sym++){
        if (s[sym] != ' '){
            if (temp == 0){
                new_s[i] = s[sym];
                temp = 1;
                i++;
            }
            else{
                continue;
            }    
        }
        else{
            temp = 0;
        }
    }
    prints(new_s,count_words);
}


int main(){
    char s[] = "Lorem ipsum dolor sit c amet, consectetur adipiscing elit,";///Lidscacae
    int len_s = sizeof(s)/sizeof(s[0]);// размер массива
    First_Syms_in_Words(s,len_s);

}
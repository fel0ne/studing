#include <stdio.h>

int main() {
    char *text = "aboba bibi boba";
    int i = 0;

    // Перебор с помощью индексации
    for (i = 0; text[i] != '\0'; i++) {
        printf("Символ на позиции %d: %c\n", i, text[i]);
    }
    
    // Этот же код можно записать более компактно,
    // так как text[i] == '\0' эквивалентно !text[i]
    for (i = 0; text[i]; i++) {
        printf("Символ на позиции %d: %c\n", i, text[i]);
    }

    return 0;
}
#include <stdio.h>

void printStr(char * string){
    int i = 0;
    while(string[i] != '\0'){
        printf("%c", string[i]);
        i++;
    }
    printf("\n\n");
} 

int strLen(char * string){
    int i = 0;
    while(string[i] != '\0'){
        i++;
    }
    return (i);
}

int directSearch(char * haystack, char * needle){
    int i = 1;
    int j;
    int n = strLen(haystack);
    int m = strLen(needle);
    do{
        i++;
        j=0;
        while((j < m) && (haystack[i+j] == needle[j])){
            j++;
        }
    }while((j != m) && (i < n-m));
    return (i);

}

void directSearchAll(char * haystack, char * needle) {
    int n = strLen(haystack);
    int m = strLen(needle);
    int comparisons = 0; 
    int i = 0; 
    int count = 0; 

    while (i <= n - m) {
        int j = 0;
        while (j < m && haystack[i + j] == needle[j]) {
            j++;
            comparisons++;
        }
        //comparisons++;
        if (j == m) {
            printf("[direct_search] Совпадение найдено по индексу: %d\n", i);
            count++;
        }

        i++;
    }

    if (count == 0) {
        printf("Совпадений не найдено.\n");
    }
    printf("Количество сравнений в directSearchAll: %d\n\n", comparisons);
}

int hash(char *s, int q, int len) {
    int h = 0;
    for (int i = 0; i < len; i++) {
        h = (h * 256 + s[i]) % q;
    }
    return h;
}

void RabinKarp(char *haystack, char *needle) {
    int n = strLen(haystack);
    int m = strLen(needle);
    int comparisons = 0; 
    int q = 101;
    int hash_needle = hash(needle, q, m);
    int h = 1;
    for (int i = 0; i < m - 1; i++) {
        h = (h * 256) % q;
    }
    
    int hash_haystack = hash(haystack, q, m);
    for (int i = 0; i <= n - m; i++) {
        if (hash_haystack == hash_needle) {
            int match = 1;
            for (int j = 0; j < m; j++) {
                comparisons++; 
                if (haystack[i + j] != needle[j]) {
                    match = 0;
                    break;
                }
            }
            if (match){
                printf("[rabin_karp] Совпадение найдено по индексу: %d\n",i);
            }
        }
        if (i < n - m) {
            hash_haystack = (256 * (hash_haystack - haystack[i] * h) + haystack[i + m]) % q;
            if (hash_haystack < 0) hash_haystack += q;
        }
    }
    printf("Количество сравнений в RabinKarp: %d\n\n", comparisons);
}

int main(){
    char *haystack ="Do not fear, for I am with you; do not be dismayed, for I am your God. I will strengthen you and help you; I will uphold you with my righteous right hand. The Lord is close to the brokenhearted and saves those crushed in spirit. Come to Me, all you who are weary and burdened, and I will give you rest. Take My yoke upon you and learn from Me, for I am gentle and humble in heart. Whatever you do, work at it with all your heart, as working for the Lord. Let your light shine before others, that they may see your good deeds. Rejoice in hope, be patient in affliction, persevere in prayer. And now these three remain: faith, hope, and love. But the greatest of these is love. For God did not give us a spirit of timidity, but of power, love, and self-discipline. Trust in the Lord with all your heart, and lean not on your own understanding. The peace of God, which transcends all understanding, will guard your hearts. Be strong and courageous. Do not be afraid; do not be discouraged, for the Lord your God will be with you wherever you go.";
    char *needle = "do not be";

    printStr(haystack);
    printStr(needle);
    
    directSearchAll(haystack,needle);
    RabinKarp(haystack,needle);
}
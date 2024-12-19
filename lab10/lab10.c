#include <stdio.h>
#include "triangles.h"



int main(){
    

    struct Triangle t[3];
    int areas[3];
    for(int i =  0; i < 3; i++){
        Scan_triangle_array(&t[i]);
    }
    #ifdef DEBUG
        for(int i =  0; i < 3; i++){
            Print_triangle_array(t[i]);
        
        }
    #endif
    printf("\n");
    int ind = 0;
    double max_area = area(t[0]);
    for(int i =  0; i < 3; i++){
        double buf = area(t[i]);
        #ifdef DEBUG
            printf("%f\n", buf);
        #endif
        if (buf > max_area){
            max_area = buf;
            ind = i;
        }
    }
    printf("%d",ind + 1);
}
//6 8 10 
//5 5 6 
//7 8 9 
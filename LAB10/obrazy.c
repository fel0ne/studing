#include <stdio.h>
#include "triangles.h"

double area(struct Triangle t) {
    double s = (t.a + t.b + t.c) / 2;
    return (s * (s - t.a) * (s - t.b) * (s - t.c));
}


void Scan_triangle_array(struct Triangle *t){
    scanf("%d",&t->a);
    scanf("%d",&t->b);
    scanf("%d",&t->c);
}
//#ifdef DEBUG
    void Print_triangle_array(struct Triangle t){
        printf("%d %d %d ",t.a,t.b,t.c);
    }
//#endif
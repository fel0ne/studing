struct Triangle{
        int a;
        int b;
        int c;
};

double area(struct Triangle t) ;


void Scan_triangle_array(struct Triangle *t);

#ifdef DEBUG
    void Print_triangle_array(struct Triangle t);
#endif
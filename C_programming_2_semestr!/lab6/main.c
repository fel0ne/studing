#include "student.h"

int main() {
    srand(time(NULL));
    student A[N];
    
    randomizeParameters(A);
    printStudents(A);
    create_file(A);
    search_in_file();
    
    return 0;
}
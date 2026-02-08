#include <stdio.h> 
 
#define SQR(x) (x) * (x) //было x * x
 
// Проблема: z != 36 
 
int main() { 
    int y = 5; 
    int z = SQR(y + 1); 
    printf("z = %d\n", z); 
    return 0;
}
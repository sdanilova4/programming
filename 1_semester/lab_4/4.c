#include <stdio.h>

int main() {
    int a;
    int k;
    printf("введите a: ");
    scanf("%d",&a);
    printf("введите k: ");
    scanf("%d",&k);
    
    printf("%d\n",(a<<k) + (k*k - 1));
    

}
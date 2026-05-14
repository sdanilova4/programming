#include <stdio.h>

// вариант 14

// #define N 7
// int main() {
//     for (int i = 1;i < N+1;i++){
//         for (int j=0;j<N;j++){
//             printf("%d",i);
//         }printf("\n");
//     }return 0;
// }

// вариант 11

// #define N 5

// int main() {
//     for (int i = N;i>0;i--){
//         for (int k = i;k<N;k++){
//             printf(" ");
//         }
//         for (int j = i*2-1;j>0;j--){
//             printf("V");
//         }printf("\n");
//     }
// }


// вариант 16

#define N 7

int main(){
    int k = N/2;
    printf("%d",k);
}
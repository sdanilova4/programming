#include <stdio.h>

int main() {
    int a;
    int k = -555;
    int j = -555;
    int flag = 1;
    int max;
    k++;
    max = k >j ? printf("%d",k) : printf("%d",j);
    // printf("%d",j);
    // printf("введите число: ");
    // scanf("%d",&a);
    // for (int i = 7; i>=0; i-- ){
    //     if (i%2==0){
    //         k = (a>>i)&1;
    //         // printf("%d\n",k);
    //     } else {
    //         j = (a>>i)&1;
    //         // printf("%d\n",j);
    //     }
    //     if (i!=7) {
    //         if (k==j) {
    //             printf("не чередуется\n"); 
    //             flag = 0;
    //             break;
    //         }
    //     }
    // } if (flag == 1) {printf("чередуется\n");}
}
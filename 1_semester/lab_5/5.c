// вариант 3
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define n 10

int null(int array[]){
    for (int i = 0; i < n - 1; i++) { // i = 0 1 2 3 4 5 .. 9
        if (array[i] < 0) {
            array[i+1] = 0;
        }
    }
}

void print_array(int array[]){
    for (int i = 0; i < n; i++) {
        printf("%d ",array[i]);
    }printf("\n");
}

int min_array(int array[]){
    int min = array[0];
    int a = 0;
    for (int i = 1; i < n - 1; i++){
        if (min > array[i]) {
            min = array[i];
            a = i;
        }
        
    }
    return a;
}

int sum_and_umn_array(int array[]) {
    int sum = 0;
    int umn = 1;
    for (int i = 1; i < n; i+=2){
        sum+=array[i];
    }
    printf("Сумма четных: %d\n",sum);
    for (int i = 0; i < n; i+=2){
        umn*=array[i];
    }
    printf("Произведение нечетных: %d\n",umn);
}

int main() {
    srand(time(NULL));
    int X[n]={0};
    for (int i =0;i<n;i++){
        int rand_i = rand()%100 - 50;
        X[i]=rand_i;
    }

    printf("массив X(n): "); print_array(X);
    int min1 = min_array(X);
    null(X);
    printf("1) "); print_array(X);
    int min2 = min_array(X);
    if (min1 != min2){ 
        printf("положение минимального элемента поменялось! \nбыло X[%d] стало X[%d]:%d\n",min1,min2,X[min2]);
        }else {
            printf("положение минимального элемента не поменялось \nбыло X[%d] стало X[%d]:%d\n",min1,min2,X[min2]);
        }
    sum_and_umn_array(X);
}
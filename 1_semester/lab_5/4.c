#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 6

int main() {
    int a[N*2]={0};
    long long int energy = 0;
    srand(time(NULL));
    int max = -60000;
    for (int i = 0; i<N*2; i++) {
        int rand_i = rand() % 65535 - 32768;
        a[i] = rand_i;
        printf("%d\n",rand_i);
        
    }  
    
    for (int i = 0; i<N*2;i = i + 2){
        printf(" s[%d] = %d + j(%d)\n",N/2,a[i],a[i+1]);
        energy = energy + (a[i]*a[i] + a[i+1]*a[i+1]); 
        if (max < a[i]){
            max = a[i];
        }
    }
    printf("signal_energy = %lld\n", energy);
    printf("max = %d\n",max);
}
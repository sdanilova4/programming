#include <stdio.h>
#define N 3

typedef unsigned int uint; 
typedef struct parall parall;

struct parall {
    unsigned int a;
    unsigned int b;
    unsigned int h;
};

void min_V_parall(parall p[]){
    uint min_V =  p[0].a*p[0].b*p[0].h;
    parall min_parall = p[0];
    for (int i = 1; i < N;i++){
        uint V_1 = p[i].a*p[i].b*p[i].h;
        if (V_1 < min_V) {
            min_V = V_1;
            min_parall = p[1];
        }
    }
    printf("наименьший объем %d\nПараллелепипед: a %d, b %d, h %d\n",min_V,min_parall.a,min_parall.b,min_parall.h);
}

parall create_N_parall(parall array_parall[]){
    for (int i = 0;i<N;i++){
        printf("Параллелепипед %d\nВведите сторону а> \n",i+1);
        scanf("%d",&array_parall[i].a);
        printf("Введите сторону b> \n");
        scanf("%d",&array_parall[i].b);
        printf("Введите сторону h> \n");
        scanf("%d",&array_parall[i].h);
        printf("~ ~ ~ ~ ~ ~ ~ ~ ~\n");
    }

}

int main(){
    // struct parall **array[N] = malloc(N*sizeof(*array));
    // struct parall array[N] = {{2,3,4},{7,8,9},{1,5,9}};
    struct parall array[N] = {};
    create_N_parall(array);
    min_V_parall(array);
}

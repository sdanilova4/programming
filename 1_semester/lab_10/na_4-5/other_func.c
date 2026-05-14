#include "func.h"
void min_V_parall(parall p[])
{
    uint min_V =  p[0].a*p[0].b*p[0].h;
    parall min_parall = p[0];
    for (int i = 1; i < N;i++)
    {
        uint V_1 = p[i].a*p[i].b*p[i].h;
        if (V_1 < min_V) {
            min_V = V_1;
            min_parall = p[1];
        }
    }
    printf("наименьший объем %d\nПараллелепипед: a %d, b %d, h %d\n",min_V,min_parall.a,min_parall.b,min_parall.h);
}

void create_N_parall(parall array_parall[])
{
    for (int i = 0;i<N;i++)
    {
        printf("Параллелепипед %d\nВведите сторону а> \n",i+1);
        scanf("%d",&array_parall[i].a);
        printf("Введите сторону b> \n");
        scanf("%d",&array_parall[i].b);
        printf("Введите сторону h> \n");
        scanf("%d",&array_parall[i].h);
        printf("~ ~ ~ ~ ~ ~ ~ ~ ~\n");
    }

}

void create_N_parall_point(parall *array_parall)
{
    for (int i = 0;i<N;i++)
    {
        if (array_parall == NULL) return;
        printf("Параллелепипед %d\nВведите сторону а> \n",i+1);
        scanf("%d",&array_parall[i].a);
        printf("Введите сторону b> \n");
        scanf("%d",&array_parall[i].b);
        printf("Введите сторону h> \n");
        scanf("%d",&array_parall[i].h);
        printf("~ ~ ~ ~ ~ ~ ~ ~ ~\n");
    }
}

void min_V_parall_point(parall p[])
{
    uint min_V =  p[0].a*p[0].b*p[0].h;
    parall min_parall = p[0];
    for (int i = 1; i < N;i++)
    {
        uint V_1 = p[i].a*p[i].b*p[i].h;
        if (V_1 < min_V) {
            min_V = V_1;
            min_parall = p[1];
        }
    }
    printf("наименьший объем %d\nПараллелепипед: a %d, b %d, h %d\n",min_V,min_parall.a,min_parall.b,min_parall.h);
}

void clear_arr(int n,parall *arr)
{
    free(arr);
    arr = NULL;
}
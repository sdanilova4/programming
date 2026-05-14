#ifndef FUNCTIONS_H 
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#define N 3

typedef unsigned int uint; 
typedef struct parall parall;

struct parall {
    unsigned int a;
    unsigned int b;
    unsigned int h;
};

void min_V_parall(parall p[]);
void create_N_parall(parall array_parall[]);
void create_N_parall_point(parall *array_parall);
void clear_arr(int n,parall *arr);

#endif
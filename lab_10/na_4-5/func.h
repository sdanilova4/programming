#ifndef FUNCTIONS_H 
#define FUNCTIONS_H

#include <stdio.h>
#define N 3

typedef unsigned int uint; 
typedef struct parall parall;

struct parall {
    unsigned int a;
    unsigned int b;
    unsigned int h;
};

void min_V_parall(parall p[]);
parall create_N_parall(parall array_parall[]);

#endif
#ifndef _COFFEEHOUSE_H_
#define _COFFEEHOUSE_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 100

typedef struct {
    const char *name;
    const char *cofee_bean;
    int price;
    const char *milk;
}coffeehouse_t;

extern const char *name_coffee[];
extern const char *coffee_beans[];
extern const char *milk[];

void fill_random_cofeehouse(coffeehouse_t array[N]);

void print_cofeehouses(coffeehouse_t array[N]);

void Selection_Sort(coffeehouse_t array[N]);

#endif
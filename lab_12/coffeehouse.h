#ifndef _COFFEEHOUSE_H_
#define _COFFEEHOUSE_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 5

typedef struct {
    const char *name;
    const char *cofee_bean;
    int price;
    const char *milk;
}coffeehouse_t;

const char *name_coffee[]={"Latte","Cappuccino","Flat White","Mocaccino","Macchiato","Raf coffee"};
const char *coffee_beans[]={ "Arabica","Robusta","Liberica","Excelsa"};
const char *milk[] = {"soy milk","almond milk","coconut milk", "oat milk"};

void fill_random_cofeehouse(coffeehouse_t array[N]);

void print_cofeehouses(coffeehouse_t array[N]);

void Selection_Sort(coffeehouse_t array[N]);

#endif
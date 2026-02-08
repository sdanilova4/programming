#include "coffeehouse.h"

const char *name_coffee[]={"Latte","Cappuccino","Flat White","Mocaccino","Macchiato","Raf coffee"};
const char *coffee_beans[]={ "Arabica","Robusta","Liberica","Excelsa"};
const char *milk[] = {"soy milk","almond milk","coconut milk", "oat milk"};


void fill_random_cofeehouse(coffeehouse_t array[N]) {

    for (int i = 0; i < N; i++)
    {
        array[i].name = name_coffee[(rand() % 5) + 1];
        array[i].cofee_bean = coffee_beans[(rand() % 3) + 1];
        array[i].price =(rand() % 10 + 1) * 10 + 40;
        array[i].milk = milk[(rand() % 3) + 1];
    }
} 

void print_cofeehouses(coffeehouse_t array[N]) {
    printf("== масив структур 'КОФЕЙНЯ' ==\n");
    printf("----------------------------------------------------\n");
    printf("|   название   |  тип зерна  | цена |  тип молока  |\n");
    printf("----------------------------------------------------\n");

    for (int i = 0; i < N; i++)
    {
        printf("|  %-11s | %-11s | %-4d | %-12s |\n", 
            array[i].name, array[i].cofee_bean,array[i].price,
            array[i].milk);
    }
    printf("----------------------------------------------------\n");
}

void Selection_Sort(coffeehouse_t array[N]) { //сортировка выбором, ищем наименьшее
    int min_ind;
    coffeehouse_t temp;
    for (int i = 0; i < N - 1; i++) 
    {
        min_ind = i;
        for (int j = i + 1; j < N; j++)
        {
            min_ind = array[min_ind].price < array[j].price? min_ind:j;
        }        
        if (min_ind != i) {
            temp = array[i];
            array[i] = array[min_ind];
            array[min_ind] = temp; 
        }
    }
}
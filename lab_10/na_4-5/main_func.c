#include "func.h"

int main(){
    parall *array = malloc(N*sizeof(array));
    // struct parall array[N] = {{2,3,4},{7,8,9},{1,5,9}};
    // struct parall array[N] = {};
    // create_N_parall(array);
    create_N_parall_point(array);
    min_V_parall(array);
    clear_arr(N,array);
}
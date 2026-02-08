#include "coffeehouse.h"

int main() {
    coffeehouse_t A[N];
    srand(time(NULL));
    fill_random_cofeehouse(A);
    print_cofeehouses(A);
    Selection_Sort(A);
    print_cofeehouses(A);
}
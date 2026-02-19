#include "coffeehouse.h"
#include <sys/time.h>


int main() {
    coffeehouse_t A[N];
    // coffeehouse_t* A = malloc(N * sizeof(coffeehouse_t));

    struct timeval start, end;

    srand(time(NULL));
    fill_random_cofeehouse(A);
    print_cofeehouses(A);
    
    gettimeofday(&start, NULL); // Замеряем время ДО

    // callback_fill_random_cofeehouse(A,Selection_Sort);
    Selection_Sort(A,sravn);

    gettimeofday(&end, NULL); // Замеряем время ПОСЛЕ

    print_cofeehouses(A);

    long seconds = end.tv_sec - start.tv_sec;
    long useconds = end.tv_usec - start.tv_usec;
    long total_useconds = seconds * 1000000 + useconds;

    printf("Время сортировки: %ld микросекунд (%f сек)\n", 
           total_useconds, total_useconds / 1000000.0);
}
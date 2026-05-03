#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// #define N 4

typedef struct {
    int start;
    int end;
    int N;
    double **A, **B, **C;
} inf_thread_t;

double** matrix_maker(int n){
    double** matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++){
        matrix[i] = (double*)malloc(n * sizeof(double));
    }
    return matrix;
}

void print_matrix(const char* name, double** matrix, int n) {
    printf("Матрица %s:\n", name);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4.0f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void* part_matrix(void* arg){
    inf_thread_t* arg_i = (inf_thread_t*)arg;

    for (int i = arg_i->start; i < arg_i->end;i++)
    {
        for (int j = 0; j<arg_i->N; j++)
        {
            for (int k = 0; k < arg_i->N; k++)
            {
                arg_i->C[i][j] += arg_i->A[i][k]*arg_i->B[k][j];
            }
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("Usage: %s <размер_матрицы> <кол-во_потоков> !!\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int num_threads = atoi(argv[2]);

    double** A =  matrix_maker(N);
    double** B =  matrix_maker(N);
    double** C =  matrix_maker(N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = 1.0;
            B[i][j] = 1.0;
            C[i][j] = 0.0;
        }
    }

    if (N < 5) {
        print_matrix("A",A,N);
        print_matrix("B",B,N);
    }


    pthread_t threads[num_threads];
    inf_thread_t t_arg[num_threads];

    int percentage = N / num_threads;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < num_threads; i++) {
        t_arg[i].N = N;
        t_arg[i].A = A; t_arg[i].B=B; t_arg[i].C=C;
        t_arg[i].start = i*percentage;

        if (i == num_threads - 1){
            t_arg[i].end = N;
        } else {
            t_arg[i].end = (i+1)*percentage;
        }
        
        pthread_create(&threads[i], NULL,part_matrix,&t_arg[i]);
    }

    for (int i = 0; i < num_threads; i++){
        pthread_join(threads[i],NULL);
    }

    if (N < 5) print_matrix("C", C, N);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_spent = (end.tv_sec - start.tv_sec) + 
                        (end.tv_nsec - start.tv_nsec) / 1e9;
    
    printf("%f\n", time_spent);
}
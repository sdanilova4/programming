
//gcc full_data_time_matrix.c -o time -lpthread
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    int start;
    int end;
    int N;
    double **A, **B, **C;
} inf_thread_t;

double** matrix_maker(int n) {
    double** matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double*)malloc(n * sizeof(double));
    }
    return matrix;
}

void free_matrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) free(matrix[i]);
    free(matrix);
}

void* part_matrix(void* arg) {
    inf_thread_t* arg_i = (inf_thread_t*)arg;
    for (int i = arg_i->start; i < arg_i->end; i++) {
        for (int j = 0; j < arg_i->N; j++) {
            arg_i->C[i][j] = 0;
            for (int k = 0; k < arg_i->N; k++) {
                arg_i->C[i][j] += arg_i->A[i][k] * arg_i->B[k][j];
            }
        }
    }
    return NULL;
}

int main() {
    int sizes[] = {500, 1000, 1500, 2000, 2500};
    int threads_counts[] = {1, 2, 4, 8, 16, 32, 64, 128};
    int num_sizes = 5;
    int num_threads = 8;

    FILE *fp = fopen("stats.csv", "w");
    if (fp == NULL) return 1;
    fprintf(fp, "N,Threads,Time\n");

    printf("массовое тестирование начинается...\n");

    for (int i = 0; i < num_sizes; i++) {
        int N = sizes[i];
        for (int j = 0; j < num_threads; j++) {
            int T = threads_counts[j];
            double **A = matrix_maker(N);
            double **B = matrix_maker(N);
            double **C = matrix_maker(N);

            for (int r = 0; r < N; r++) {
                for (int c = 0; c < N; c++) {
                    A[r][c] = 1.0; B[r][c] = 1.0;
                }
            }

            pthread_t *threads = malloc(T * sizeof(pthread_t));
            inf_thread_t *t_arg = malloc(T * sizeof(inf_thread_t));
            int percentage = N / T;

            struct timespec start, end;
            clock_gettime(CLOCK_MONOTONIC, &start);

            for (int t = 0; t < T; t++) {
                t_arg[t].N = N;
                t_arg[t].A = A; t_arg[t].B = B; t_arg[t].C = C;
                t_arg[t].start = t * percentage;
                t_arg[t].end = (t == T - 1) ? N : (t + 1) * percentage;
                pthread_create(&threads[t], NULL, part_matrix, &t_arg[t]);
            }

            for (int t = 0; t < T; t++) pthread_join(threads[t], NULL);

            clock_gettime(CLOCK_MONOTONIC, &end);

            double time_spent = (end.tv_sec - start.tv_sec) + 
                                (end.tv_nsec - start.tv_nsec) / 1e9;

            fprintf(fp, "%d,%d,%f\n", N, T, time_spent);
            printf("N=%4d | T=%3d | Time: %.4f sec\n", N, T, time_spent);
            fflush(fp); 
            free_matrix(A, N); free_matrix(B, N); free_matrix(C, N);
            free(threads); free(t_arg);
        }
    }

    fclose(fp);
    printf("Готово!!!\n");
}

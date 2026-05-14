#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5

void max_array(int n,int m, float **arr,int *max_i,int *max_j){
    int max = -51;
    for (int i =0;i<n;i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (max < arr[i][j])
            {
                max = arr[i][j];
                *max_i=i;
                *max_j=j;
            }
        }
    }
}

void print_array(int n, int m,float **arr) {
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            printf("%.0f ", arr[i][j]);
        }
        printf("\n");
    }
}

void clear_arr(int n,float **arr){
    for (int i = 0; i < n; i++) 
    {
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr);
    arr = NULL;
}

float** create_kvadrat(float **matrix,int max_i, int max_j){
    int size = (max_i < max_j) ? max_i + 1 : max_j + 1;
    int kvadrat_i = max_i - size + 1; 
    int kvadrat_j = max_j - size + 1;

    float **kvadrat = malloc(size* sizeof(*kvadrat));

    if (kvadrat_i >= 0 && kvadrat_j >= 0)
    {
        for (int i = 0; i < size;i++)
        {
            kvadrat[i] = malloc(size*sizeof(**kvadrat));
            if (kvadrat[i] == NULL) { printf("не удалось создать матрицу");}
            else { 
                for (int j = 0; j < size; j++)
                {
                    kvadrat[i][j] = matrix[kvadrat_i + i][kvadrat_j + j];

                }
            }
        } 
        return kvadrat;
    }
}


float** transponir(float **matrix,int max_i, int max_j){
    int size = (max_i < max_j) ? max_i + 1 : max_j + 1 ;
    int kvadrat_i = max_i - size + 1; 
    int kvadrat_j = max_j - size + 1;
    if (kvadrat_i >= 0 && kvadrat_j >= 0)
    {
        for (int i = 0; i < size;i++)
        {
            for (int j = i + 1; j < size; j++)
            {
                float temp = matrix[kvadrat_i + i][kvadrat_j + j];
                matrix[kvadrat_i + i][kvadrat_j + j] = matrix[kvadrat_i + j][kvadrat_j + i];
                matrix[kvadrat_i + j][kvadrat_j + i] = temp;
            }
        } 
    }
    return matrix;
}




void create_kvadrat_beta(float **matrix,int max_i, int max_j, int n,int m){
    int size = (max_i < max_j) ? max_i + 1 : max_j + 1 ;
    int kvadrat_i = max_i - size + 1; 
    int kvadrat_j = max_j - size + 1;
    printf("квадрат матрицы в нижнем углу которого максимальное число \n");
    if (kvadrat_i >= 0 && kvadrat_j >= 0){
        for (int i = 0; i < size;i++){
            for (int j = 0; j < size; j++){
                printf("%.0f ",matrix[kvadrat_i + i][kvadrat_j + j]);

            }printf("\n");
        } 
    }
}


void srednee(float **matrix,int n, int m){
    float sum = 0;    
    for (int i = 0;i<n;i++)
    {
        
        for (int j = 0; j < m;j++)
        {
            sum += matrix[i][j];
        }
    }
    printf("%.1f\n", sum/(n*m));
}


float** null_skalyar(float** matrix, int skalyar){
    for (int i = 0; i<N; i++)
    {
        for (int j = 0; j<N; j ++)
        {
            if (matrix[i][j] == 0)
            {
                matrix[i][j] = skalyar;
            }
        }
    }
    return matrix;
}


int main() {
    int skalyar;
    printf("Введите скаляр> ");scanf("%d",&skalyar);

    srand(time(NULL));

    float **matrix = malloc( N* sizeof(*matrix));

    for (int i =0;i<N;i++){
        matrix[i] = malloc(N * sizeof(**matrix));
        if (matrix[i] == NULL) { printf("не удалось создать матрицу");}
        else { 
            for (int j = 0; j < N; j++)
            {
                int rand_i = rand()%100 - 50;
                matrix[i][j]=rand_i;
            }
        }
    }

    int max_i, max_j;
    max_array(N,N,matrix,&max_i,&max_j);

    print_array(N,N,matrix);

    printf("**************\n");

    printf("квадрат в матрице, в правом нижнем углу которого расположен максимальный элемент\n");
    int size = (max_i < max_j) ? max_i + 1 : max_j + 1 ;
    float** kvadrat = create_kvadrat(matrix,max_i,max_j);
    print_array(size,size,kvadrat);

    printf("**************\n");

    printf("транспонируем квадрат \n");
    matrix = transponir(matrix, max_i, max_j);
    print_array(N,N,matrix);

    printf("**************\n");

    printf("Среднее арифметическое значение исходной матрицы: ");
    srednee(matrix, N,N);
    printf("Среднее арифметическое значение транспонированного квадрата: ");
    srednee(kvadrat,size,size);

    printf("**************\n");

    printf("Заменим нули в матрице на скаляр \n");
    matrix = null_skalyar(matrix,skalyar);
    print_array(N,N,matrix);



    clear_arr(N,matrix);
    clear_arr(size,kvadrat);
}
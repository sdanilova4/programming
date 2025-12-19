#include <stdio.h>

void creat_dop_array(int n, int i_rem,float array_dop[][n-1], float array[][n])
{
    for (int i = 1; i < n; i++)
    {
        int k = 0;
        for (int j = 0; j < n; j++) 
        {
            if (j == i_rem) continue;
            
            array_dop[i-1][k] = array[i][j];
            k++;
        }
    }
}

float opredel2(float array[][2]){
    return array[0][0]*array[1][1]-array[0][1]*array[1][0];
}

float opredel(int n,float array[][n]){
    float sum = 0;
    if (n == 2){
        return opredel2(array);
    }
    if (n > 2){
        for (int i = 0;i<n;i++){
            int znak = (i%2==0)? 1:-1;
            float array_dop[n-1][n-1];
            creat_dop_array(n, i, array_dop, array);
            sum += znak * array[0][i] * opredel(n-1, array_dop);
        }
        return sum;
    }
}

void x_array(int stolb,int n1, float array[n1][n1+1], float M[n1][n1]){
    for (int i = 0; i < n1; i++ ){
        for (int j = 0; j<n1;j++){
            if (stolb==j){
                M[i][j]=array[i][n1];
            } else {
                M[i][j]=array[i][j];
            }
        }
    }
}

void kramer(int n1, float array[n1][n1+1]){
   float del_arr[n1][n1];
    for (int i=0;i<n1;i++){
        for (int j=0;j<n1;j++){
            del_arr[i][j]=array[i][j];
        }
    }
    
    for (int i=0;i<n1;i++){
        float M[n1][n1];
        x_array(i,n1,array,M);
        float x = opredel(n1,M)/opredel(n1,del_arr);
        if (opredel(n1,del_arr)==0) {
            printf("Нет единственного решения.\n");
            break;
        }
        printf("x%d = %.2f \n",i+1,x);
}
    }
    

int main(){
    float M5[3][4]={{2, -3, 1,-7}, {1, 2, -3,14}, {-1, -1, 5,-18}};
    float M7[4][5]={{2,5,4,1,20},{1,3,2,1,11},{2,10,9,7,40},{3,8,9,2,37}};
    float M9[8][9]={{2,6,-2,3,3,6,1,6,22},{1,4,4,2,4,7,-2,3,39},{3,6,7,-1,0,5,3,1,34},{7,3,6,0,7,4,2,4,23},{1,0,-1,2,3,6,0,-2,3},{-1,0,2,6,-2,0,5,-1,26},{4,5,-2,7,4,4,5,-2,17},{3,3,4,6,-2,6,-2,2,37}};
    kramer(8,M9);

    // int N;
    // int x;
    // printf("Размер матрицы NxN: ");scanf("%d",&N);
    // float matrix[N][N+1];
    // for (int i = 0; i<N;i++){
    //     for (int j = 0; j < N +1;j++){
    //         printf("x(%d,%d) > ",i+1,j+1);scanf("%d",&x);matrix[i][j]=x;
    //     }
    // }
    // kramer(N,matrix);

    //  for (int i = 0; i<N;i++){
    //     for (int j = 0; j < N +1;j++){
    //         printf("%d ",matrix[i][j]);
    //     }
    //     printf("\n");}

}
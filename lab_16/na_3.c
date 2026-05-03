#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void cleanup_handler(void *arg) {
    printf("поток завершается, освобождение памяти\n");
}

void *pthread_work(){
    for (int i = 0; i<5;i++){
        pthread_mutex_lock(&mutex);
        printf("дочерний поток: %d\n",i+1);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *pthread_print_msg(void* arg){
    char *msg = (char *)arg;
    pthread_cleanup_push(cleanup_handler, NULL);
    for (int i = 0; i < 4;i++){
        printf("дочерний поток: %s (итерация %d)\n",msg,i+1);
        sleep(1);
    }
    pthread_cleanup_pop(0);
    return NULL;
}

void*sleepsort(void* arg){
    int value = *(int*)arg;

    sleep(value);

    printf("%d\n",value);
    fflush(stdout);return NULL;
}

int main(){

    // pthread_t tid;
    // pthread_create(&tid,NULL,pthread_work,NULL);
    // pthread_join(tid,NULL);
    // for (int i = 0; i<5;i++){
    //     printf("родительский поток: %d\n",i + 1);
    // }

    // pthread_t tid[4];
    // char* msg[4] = {"зима", "весна","лето","осень"};
    // for (int i = 0; i < 4;i++){
    //     pthread_create(&tid[i],NULL,pthread_print_msg,msg[i]);    
    // }
    // for (int i = 0; i < 4; i++) {
    //     sleep(2);
    //     printf("родительский поток: отменяю поток (%s)...\n",msg[i]);
    //     pthread_cancel(tid[i]);
    //     pthread_join(tid[i], NULL);
    // }

    int n = 10;
    int arr[n];
    for (int i = n; i > 0;i--){
        arr[i-1]=i;
    }
    pthread_t tids[n];

    printf("Начинаем сортировку ...\n");

    for (int i = 0; i < n; i++) {
        pthread_create(&tids[i], NULL, sleepsort, &arr[i]);
    }
    for (int i = 0; i < n; i++) {
        pthread_join(tids[i], NULL);
    }
    
    // pthread_t tid[4];
    // char* msg[4] = {"зима", "весна","лето","осень"};
    // for (int i = 0; i < 4;i++){
    //     printf("родительский поток: создаю поток (%s)...\n",msg[i]);
    //     pthread_create(&tid[i],NULL,pthread_print_msg,msg[i]);    
    // }
    // sleep(2);
    // printf("Родительский поток: прерываю всех!\n");
    // for (int i = 0; i < 4; i++) {
    //     pthread_cancel(tid[i]);
    //     pthread_join(tid[i], NULL);
    // }
}
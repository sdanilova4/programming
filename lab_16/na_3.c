#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void cleanup_handler(void *arg) {
    printf("поток завершается, освобождение памяти\n");
}

void *pthread_work(){
    for (int i = 0; i<5;i++){
        printf("дочерний поток: %d\n",i+1);
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

int main(){

    // pthread_t tid;
    // pthread_create(&tid,NULL,pthread_work,NULL);
    // pthread_join(tid,NULL);
    // for (int i = 0; i<5;i++){
    //     printf("родительский поток: %d\n",i + 1);
    // }

    pthread_t tid;
    char* msg[4] = {"зима", "весна","лето","осень"};
    for (int i = 0; i < 4;i++){
        pthread_create(&tid,NULL,pthread_print_msg,msg[i]);
        sleep(2);
        printf("родительский поток: отменяю поток (%s)...\n",msg[i]);
        pthread_cancel(tid);
    }
    pthread_join(tid, NULL);
}
/**
 * @file 02pthtraed_join.c
 * @author your name (you@domain.com)
 * @brief 获取已终止的线程的退出码
 * @version 0.1
 * @date 2024-09-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "apue.h"
#include <pthread.h>

void* fn1(void* arg) {
    printf("thread1 returning\n");
    return ((void*)1);
}

void* fn2(void* arg) {
    printf("treahd2 exiting\n");
    pthread_exit((void*)2);
}

int main(void) {
    int err;
    pthread_t tid1, tid2;
    void *tret;

    err = pthread_create(&tid1, NULL, fn1, NULL);
    if (err != 0)
    {
        err_exit(err, "can't create thread1");
    }
    
    err = pthread_create(&tid2, NULL, fn2, NULL);
    if (err != 0) {
        err_exit(err, "can't create thread2");
    }

    err = pthread_join(tid1, &tret);
    if (err != 0)
    {
        err_exit(err, "can't join with thread1");
    }
    printf("trehad1 exit code:%ld\n",(long)tret);

    err = pthread_join(tid2, &tret);
    if (err != 0)
    {
        err_exit(err, "can't join with thread2");
    }
    printf("thread2 exit code %ld\n", (long)tret);
    exit(0);

}


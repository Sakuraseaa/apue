/**
 * @file 01pthread_create.c
 * @author your name (you@domain.com)
 * @brief 打印线程ID.
 * @version 0.1
 * @date 2024-09-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "apue.h"
#include <pthread.h>

pthread_t ntid;

void printids(const char *s) {
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid,
    (unsigned long)tid, (unsigned long)tid);
}

void* thr_fn(void* arg) {
    printids("new thread: ");
    return (void*)0;
}

pthread_t ntid;
int main(void) {
    int err;

    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if(err != 0)
        err_exit(err, "can't create thread");
    printids("main thread:");
    sleep(1);
    exit(0);
}

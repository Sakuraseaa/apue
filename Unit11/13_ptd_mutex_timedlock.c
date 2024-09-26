/**
 * @file 13_ptd_mutex_timedlock.c
 * @author your name (you@domain.com)
 * @brief 规定最大阻塞时间的锁
 * @version 0.1
 * @date 2024-09-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "apue.h"
#include <pthread.h>

int main(void) {
    int err;
    struct timespec tout;
    struct tm* tmp;
    char buf[64];
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&lock);
    printf("mutex is locked\n");
    clock_gettime(CLOCK_REALTIME, &tout);
    tmp = localtime(&tout.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);
    printf("current time is %s\n", buf);

    tout.tv_sec += 10; /* 10 seconds from now */
    
    err = pthread_mutex_timedlock(&lock, &tout); /* caution: this could lead to deadlock*/
    clock_gettime(CLOCK_REALTIME, &tout);
    tmp = localtime(&tout.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);
    printf("the time is now %s\n", buf);
    if (err == 0)
        printf("mutex locked again!\n");
    else
        printf("can't lock mvtex again:%s\n", strerror(err));
    
    exit(0);
}
/**
 * @file 10_ptd_mutex.c
 * @author your name (you@domain.com)
 * @brief 本示例展示了互斥量 / 锁的玩法
 * @version 0.1
 * @date 2024-09-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdlib.h>
#include <pthread.h>

typedef struct foo {
    int f_count;
    pthread_mutex_t f_lock;
    int f_id;
    /* ...more stuff here...*/
}foo_t;

foo_t* foo_alloc(int id) {
    foo_t* fp = NULL;

    if ((fp = malloc(sizeof(foo_t))) != NULL) {
        fp->f_count = 1;
        fp->f_id = id;
        if (pthread_mutex_init(&fp, NULL)) {
            free(fp);
            return NULL;
        }
        /* ... continue initialization ..*/
    }

    return fp;
}

// add a reference to the object
void fool_hold(foo_t* fp) {
    
    pthread_mutex_lock(&fp->f_lock);
    fp->f_count++;
    pthread_mutex_unlock(&fp->f_lock);
}

// release a reference to the object
void foo_rele(foo_t* fp) {

    pthread_mutex_lock(&fp->f_lock);
    if(--fp->f_count == 0) {
        pthread_mutex_unlock(&fp->f_lock);
        pthread_mutex_destory(&fp->f_lock);
        free(fp);
    } else {
        pthread_mutex_unlock(&fp->f_lock);
    }
}
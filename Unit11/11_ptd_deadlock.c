/**
 * @file 11_ptd_deadlock.c
 * @author your name (you@domain.com)
 * @brief 本示例展示了2个锁的使用方法，通过仔细控制加锁顺序一致，来避免死锁
 * @version 0.1
 * @date 2024-09-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "apue.h"
#include <stdlib.h>
#include <pthread.h>

#define NHASH 29
#define HASH(id) (((unsigned long)id)%NHASH)

struct foo* fh[NHASH];
pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER; // !B::确保 fh 结构体，被修改的时候的一致性

typedef struct foo {
    int f_count;
    pthread_mutex_t f_lock; // !A::确保foo_t结构体，修改时候的一致性
    int f_id;
    struct foo *f_next; // protected by hashlock
    /* ...more stuff here...*/
}foo_t;

foo_t* foo_alloc(int id) {  // allocate the object
    
    foo_t* fp = NULL;
    int idx;
    
    if ((fp = malloc(sizeof(foo_t))) != NULL) {
        fp->f_count = 1;
        fp->f_id = id;
        if (pthread_mutex_init(&fp->f_lock, NULL)) {
            free(fp);
            return NULL;
        }
        idx = HASH(id);
        
        pthread_mutex_lock(&hashlock);
        fp->f_next = fh[idx];
        fh[idx] = fp;
        pthread_mutex_lock(&fp->f_lock);

        pthread_mutex_unlock(&hashlock);
        /* ... continue initialization ..*/
        pthread_mutex_unlock(&fp->f_lock);
    }

    return fp;
}

// add a reference to the object
void fool_hold(foo_t* fp) {
    
    pthread_mutex_lock(&fp->f_lock);
    fp->f_count++;
    pthread_mutex_unlock(&fp->f_lock);
}

// find an existing object
foo_t* foo_find(int id) {
    struct foo* fp;

    pthread_mutex_lock(&hashlock);
    for (fp = fh[HASH(id)]; fp != NULL; fp = fp->f_next) {
        if (fp->f_id == id) {
            fool_hold(fp);
            break;
        }
    }
    pthread_mutex_unlock(&hashlock);
    return fp;
}


// release a reference to the object
void foo_rele(foo_t* fp) {

    struct foo *tfp;
    int idx;

    pthread_mutex_lock(&fp->f_lock);
    if(fp->f_count == 1) {
        pthread_mutex_unlock(&fp->f_lock);
        
        pthread_mutex_lock(&hashlock);
        pthread_mutex_lock(&fp->f_lock);
        /*need to recheck the condition*/
        if (fp->f_count != 1) {
            fp->f_count--;
            pthread_mutex_unlock(&fp->f_lock);
            pthread_mutex_unlock(&hashlock);
            return;
        }

        /* remove from list */
        idx = HASH(fp->f_id);
        tfp = fh[idx];
        if (tfp == fp) {
            fh[idx] = fp->f_next;
        } else {
            while (tfp->f_next != fp)
                tfp = tfp->f_next;
            tfp->f_next = fp->f_next;
        }
        pthread_mutex_unlock(&hashlock);
        pthread_mutex_unlock(&fp->f_lock);
        pthread_mutex_destroy(&fp->f_lock);
        free(fp);
    } else {
        fp->f_count--;
        pthread_mutex_unlock(&fp->f_lock);
    }
}
/**
 * @file 15_ptd_condition.c
 * @author your name (you@domain.com)
 * @brief 演示了条件变量的使用，条件变量是用来同步线程的
 * @version 0.1
 * @date 2024-09-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <phtread.h>

typedef struct msg {
    struct mgs* m_next;
    /* ... more stuff here ... */
}msg_t;

msg_t* workq;

pthread_cond_t qread = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

void process_msg(void) {
    struct msg* mp;
    
    for(;;) {
        pthread_mutex_lock(&qlock);
        
        while (workq == NULL) {
            pthread_cond_wait(&qready, &qlock);
        }
        mp = workq;
        workq = mp->m_next;
        pthread_mutex_unlock(&qlock);
        /* now process the message mp */
    }
}

void enqueue_msg(void) {
    pthread_mutex_lock(&qlock);
    mp->m_next = workq;
    workq = mp;
    pthread_mutex_unlock(&qlock);
    pthread_cond_signal(&qread);
}

/**
 * @file 14_ptd_more.c
 * @author your name (you@domain.com)
 * @brief 作业请求队列由单个读写锁保护。多个工作线程获取单个主线程分配给他们的作业
 * 读写锁 也有带有超时的读写锁
 * pthread_rwlock_timedrlock();
 * pthread_rwlock_timedwrlock();
 * @version 0.1
 * @date 2024-09-27
 * 
 * @copyright Copyright (c) 2024
 */
#include <stdlib.h>
#include <pthread.h>

typedef struct job {
    struct job* j_next; /* 队列节点 */
    struct job* j_prev; 
    pthread_t j_id; //tells which thread handles this job
    /*... more stuff here ...*/
}job_t;

typedef struct queue {
    struct job *q_head; // 队列头节点
    struct job *q_tail; // 队列尾节点
    pthread_rwlock_t q_lock;
}queue_t;

// Initialize a queue.
int queue_init(queue_t* qp) {
    int err;

    qp->q_head = NULL;
    qp->q_tail = NULL;
    err = pthread_rwlock_init(&qp->q_lock, NULL);
    if (err != 0)
        return err;
    // ... continue initialization ...
    return 0;
}

// insert a job at the head of the queue, 在头节点之后插入一个
void job_insert(struct queue* qp, struct job* jp) {
    pthread_rwlock_wrlock(&qp->q_lock);

    jp->j_next = qp->q_head;
    jp->j_prev = NULL;
    if (qp->q_head != NULL)
        qp->q_head->j_prev = jp;
    else 
        qp->q_tail = jp;
    
    qp->q_head = jp;
    pthread_rwlock_unlock(&qp->q_lock);
}

// append a job on the tail of the queue
void job_append(queue_t* qp, job_t* jp) {
    pthread_rwlock_wrlock(&qp->q_lock);

    jp->j_next = NULL;
    jp->j_prev = qp->q_tail;
    if(qp->q_tail != NULL)
        qp->q_tail->j_next = jp;
    else
        qp->q_head = jp;

    qp->q_tail = jp;
    pthread_rwlock_unlock(&qp->q_lock);
}

// remove the given job from a queue
void job_remove(queue_t* qp, job_t* jp) {

    pthread_rwlock_wrlock(&qp->q_lock);
    if (jp == qp->q_head) {
        qp->q_head = jp->j_next;
        if (qp->q_tail == jp)
            qp->q_tail = NULL;
        else
            jp->j_next->j_prev = jp->j_prev;
    } else if (jp == qp->q_tail) {
        qp->q_tail = jp->j_prev;
        jp->j_prev->j_next = jp->j_next;
    } else {
        jp->j_prev->j_next = jp->j_next;
        jp->j_next->j_prev = jp->j_prev;
    }
    pthread_rwlock_unlock(&qp->q_lock);
}

// Find a job for the given thread ID.
job_t* job_find(queue_t* qp, pthread_t id) {
    job_t* jp;
    if(pthread_rwlock_rdlock(&qp->q_lock) != 0)
        return NULL;
    
    for (jp = qp->q_head; jp != NULL; jp = jp->j_next)
        if(pthread_equal(jp->j_id, id))
            break;
    pthread_rwlock_unlock(&qp->q_lock);
    return jp;
}

int main() {
    queue_t qt;
    job_t jt;

    queue_init(&qt);
    job_insert(&qt, &jt);
    job_remove(&qt, &jt);
}


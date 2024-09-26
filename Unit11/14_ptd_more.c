/**
 * @file 14_ptd_more.c
 * @author your name (you@domain.com)
 * @brief ��ҵ��������ɵ�����д����������������̻߳�ȡ�������̷߳�������ǵ���ҵ
 * @version 0.1
 * @date 2024-09-27
 * 
 * @copyright Copyright (c) 2024
 */
#include <stdlib.h>
#include <pthread.h>

typedef struct job {
    struct job* j_next; /* ���нڵ� */
    struct job* j_prev; 
    pthread_t j_id; //tells which thread handles this job
    /*... more stuff here ...*/
}job_t;

typedef struct queue {
    struct job *q_head; // ����ͷ�ڵ�
    struct job *q_tail; // ����β�ڵ�
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

// insert a job at the head of the queue, ��ͷ�ڵ�֮�����һ��
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
    
}
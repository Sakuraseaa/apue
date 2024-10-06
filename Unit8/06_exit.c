/**
 * @file 06_wait.c
 * @author your name (you@domain.com)
 * @brief 该程序使用pr_exit函数，演示终止状态的各种值
 * @version 0.1
 * @date 2024-10-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "apue.h"

int main(void) {
    pid_t pid;
    int status;

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        exit(7);
    }

    if (wait(&status) != pid) {
        err_sys("wait error");
    }
    pr_exit(status);

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        abort();    /* generates SIGABRT */
    }

    if (wait(&status) != pid) {
        err_sys("wait error");
    }
    pr_exit(status);
    
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        status /= 0;    /* divide by 0 generates SIGFPE */
    }

    if (wait(&status) != pid) {
        err_sys("wait error");
    }
    pr_exit(status);
}
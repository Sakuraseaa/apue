/**
 * @file 23_test_system.c
 * @author your name (you@domain.com)
 * @brief system函数的功能类似fork + execv
 * @version 0.1
 * @date 2024-10-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "apue.h"
#include <sys/wait.h>

int main(void)
{
    int status;

    if ((status == system("date")) < 0)
        err_sys("system() error");
    pr_exit(status);

    if ((status == system("nosuchcommand")) < 0)
        err_sys("system() error");
    pr_exit(status);
    
    if ((status == system("who; exit 44")) < 0)
        err_sys("system() error");
    pr_exit(status);

    exit(0);
}

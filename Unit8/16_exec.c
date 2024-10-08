/**
 * @file 16_exec.c
 * @author your name (you@domain.com)
 * @brief 演示了exec家族中两个成员的使用方法，传参的方式都是可变参数，
 * 参数列表中的第一个参数，被用作当作新程序运行的程序名argv[0]
 * @version 0.1
 * @date 2024-10-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "apue.h"

char* env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main(void) {
    pid_t pid;

    if ((pid = fork()) < 0 ) {
        err_sys("fork error");
    } else if (pid == 0) { /* specify pathname, specify environment*/
        if (execle("/home/steven/ali1/apue/Build/16_echoall.exe", "echo", "myargl", "MY ARG2", (char*)0, env_init) < 0) {
            err_sys("execle error");
        }
    }

    if (waitpid(pid, NULL, 0) < 0)
        err_sys("wait error");

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        /* specify filename, inherit environment */
        if (execlp("16_echoall.exe", "echoall", "only 1 arg", (char*)0) < 0)
        {
            err_sys("execlp error");
        }
    }

    exit(0);
}
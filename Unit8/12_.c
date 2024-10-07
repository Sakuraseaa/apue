/**
 * @file 12_.c
 * @author your name (you@domain.com)
 * @brief 本程序输出两个字符串，一个由子进程输出，一个由父进程输出
 *  因为输出依赖于内核使这两个进程运行的顺序及每个进程运行的时间长度，
 *  所以该程序包含了一个竞争条件
 * @version 0.1
 * @date 2024-10-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "apue.h"

static void charatatime(char*);

int main(void) {
    pid_t pid;

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        charatatime("output from child\n");
    } else {
        charatatime("output from parent\n");
    }
    exit(0);
}

static void charatatime(char* str) {
    char* ptr;
    int c;

    setbuf(stdout, NULL);
    for (ptr = str; (c = *ptr++) != 0; )
        putc(c, stdout);
}
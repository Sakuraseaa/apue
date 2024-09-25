/**
 * @file atexit.c
 * @author your name (you@domain.com)
 * @brief 注册进程的终止处理程序，其函数原型都是 void func(void);
 * @version 0.1
 * @date 2024-09-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "apue.h"

void e1(void) {
    printf("first exit handler\n");
}

void e2(void) {
    printf("second exit handler\n");
}

int main(void) {
    if (atexit(e2) != 0)
        err_sys("can't register e2");


    if (atexit(e1) != 0)
        err_sys("can't register e1");
    if (atexit(e1) != 0)
        err_sys("can't register e1");
    printf("main is done\n");

    return 0;
}
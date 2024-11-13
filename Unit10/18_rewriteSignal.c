/**
 * @file 18_rewriteSignal.c
 * @author your name (you@domain.com)
 * @brief 使用sigaction()系统调用 - 创建出signal系统调用
 * @version 0.1
 * @date 2024-11-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "apue.h"

// 如果信号处理程序是用sigaction设置的，那么其默认方式是补充相关启动系统调用
/* reliable version of signal(), using POSIX sigacion()*/
Sigfunc* signal(int signo, Sigfunc* func)
{
    struct sigaction act, oact;
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (signo == SIGALRM) {
    #ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
    #endif
    } else {
        act.sa_flags |= SA_RESTART;
    }
    if (sigaction(signo, &act, &oact) < 0)
        return SIG_ERR;
    return (oact.sa_handler);
}

/* 创建一版， 力图组织被中断的系统调用重启动*/
Sigfunc* signal(int signo, Sigfunc* func)
{
    struct sigaction act, oact;
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    #ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
    #endif
    if (sigaction(signo, &act, &oact) < 0)
        return SIG_ERR;
    return (oact.sa_handler);
}



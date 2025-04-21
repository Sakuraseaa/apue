/**
 * @file 1_8_errno.c    The strerror() and perror()
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>


int main(int argc, char* argv[]) {
    /* strerror 把 nr 映射为一个出错消息字符串，返回该字符串指针*/
    fprintf(stderr, "EACCES: %s \n", strerror(EACCES));
    fprintf(stderr, "ENOENT: %s \n", strerror(ENOENT));
    errno = ENOENT;
    errno = EBADF;

    /* perror 函数基于进程的errno的当前值，在标准错误上产生一条出错消息*/
    perror(argv[0]);
    //exit(0);

    return 0;
}
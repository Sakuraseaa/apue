/**
 * @file 1_10_signal.c  SIGNAL
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

#define MAXLINE 1024


static void sig_int(int signo) {
    printf("\ninterrupt\n%%");
}

int main(void) {
    char buf[MAXLINE];
    pid_t pid;
    int status;

    if(signal(SIGINT, sig_int) == SIG_ERR)
        printf("signal error \n");

    printf("$$$ ");
    while(fgets(buf, MAXLINE, stdin) != NULL) {
        if(buf[strlen(buf) - 1] == '\n')    buf[strlen(buf) - 1] = 0;
        if( (pid = fork()) < 0)
            printf("fork error \n");
        else if(pid == 0) {
            execlp(buf, buf, (char*)0);
            printf("couldn't execute: %s\n", buf);
            exit(127);
        }
        if((pid = waitpid(pid, &status, 0)) < 0)
            printf("waitpid error");
        printf("$$$ ");
    }

    exit(0);
}
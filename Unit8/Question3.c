#include "apue.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


void exit_state_print(siginfo_t* siginfo) {

    if (siginfo->si_code == CLD_EXITED) {
        printf("normal termination, exit status = %d\n", siginfo->si_status);
    } else if (siginfo->si_code==CLD_KILLED || siginfo->si_code==CLD_DUMPED) {
        printf("abnormal termination, signal number = %d%s\n", siginfo->si_status,
            siginfo->si_code == CLD_DUMPED ? "(core file generated)" : "");
    } else if (siginfo->si_code == CLD_STOPPED) {
        printf("child stopped, signal number = %d\n", siginfo->si_status);
    }
}

int main(void) {
    pid_t pid;
    int num;
    siginfo_t status;

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    } 
    else if (pid == 0) 
    {
        exit(7);
    }
    if (waitid(P_PID, pid, &status, WEXITED) ==  -1) // 阻塞等待
    {
        err_sys("wait error");
    }
    exit_state_print(&status);
    
    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)
    {
        abort();    /* generates SIGABRT */
    }
    if (waitid(P_PID, pid, &status, WEXITED)  ==  -1)
    {
        err_sys("wait error");
    }
    exit_state_print(&status);
    
    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)
    {
        num /= 0;    /* divide by 0 generates SIGFPE */
    }
    if (waitid(P_PID, pid, &status, WEXITED)  ==  -1){
        err_sys("wait error");
    }
    exit_state_print(&status);
}
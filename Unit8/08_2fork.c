/**
 * @file 08_2fork.c
 * @author your name (you@domain.com)
 * @brief fork 两次以避免僵死进程, 利用杀死父进程，使子进程被init进程接管的特性，避免僵尸进程
 * @version 0.1
 * @date 2024-10-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "apue.h"
#include <sys/wait.h>

int main(void) {
    pid_t pid;
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        if ((pid = fork()) < 0)
            err_sys("fork error");
        else if (pid > 0)
            exit(0);    /* parent from second fork == first child*/
    
        /** We're the second child; our parent becomes init as soon
         * as our real parent calls exit() in the statement above.
         * Here;s where we'd continue executing, knowing that when we're done,
         * init will reap our status.
         */
        sleep(2);
        printf("second child, parent pid = %ld\n", (long)getppid());
        exit(0);
    }

    if (waitpid(pid, NULL, 0) != pid) { /* wait for first child*/
        err_sys("waitpid error");
    }

    /*  We're the parent (the original process); we continue executing,
    *   knowing that we're not the parent of the second child.
    */
    exit(0);
}

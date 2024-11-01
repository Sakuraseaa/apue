
#include "apue.h"

int globvar = 6;

int main(void) {
    int var;
    pid_t pid;

    // ps -ef
    // ps aux
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        globvar++;  // child
        exit(0);
    } else {
        printf("i am parent, pid = %d\n", getpid());
        sleep(90);   // parent
    }
}
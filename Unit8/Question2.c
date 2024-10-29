#include "apue.h"

int globvar = 6;

void test()
{
    int pid;
    if ((pid = vfork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        globvar++;  // child
    }
}

int main(void) {
    int var;
    pid_t pid;

    var = 88;
    printf("before fork\n");

    test();
    
    int ret = printf("pid = %ld, glob = %d, ppid = %ld\n", (long)getpid(), globvar, (long)getppid());;
    exit(ret);
}
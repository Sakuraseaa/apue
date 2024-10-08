#include "apue.h"

int main(int argc, char const *argv[])
{
    pid_t pid;

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if ( pid == 0 )
    {
        if (execl("/home/steven/ali1/apue/Build/20_pro.sss", "testinterp",  
        "myargl", "MY ARG2", (char*)0) < 0)
        {
            err_sys("excel error");
        }
    }
    
    if (waitpid(pid, NULL, 0) < 0) /* parent */
        err_sys("waitpid error");
    
    return 0;
}

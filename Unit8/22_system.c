/**
 * @file 22_system.c
 * @author your name (you@domain.com)
 * @brief 本文件是对system(char*)函数的实现
 *  该函数把传入的字符串当作shell命令进行解析，执行
 * @version 0.1
 * @date 2024-10-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

int system(const char* cmdstring) /* version without signal handling*/
{
    pid_t pid;
    int status;

    if (cmdstring == NULL)  /* always a command processor with UNIX*/
        return 1;
    
    if ((pid = fork()) < 0 )
    {
        status = -1; /* probably out of processes */
    } 
    else if (pid == 0)
    {
        execl("/bin/sh", "sh", "-c", cmdstring, (char*)0);
        _exit(127);
    }
    else
    {
        while (waitpid(pid, &status, 0) < 0)
        {
            if (errno != EINTR)
            {
                status = -1; /* error other than EINTR form waitpid*/
                break;
            }
            
        }
        
    }

    return status;
}
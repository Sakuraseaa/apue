/**
 * @file 1_6_pid.c  The procedure is used to print process-identification
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "apue.h"

int main(int argc, char const *argv[])
{
    printf("process pid:%ld\n", (long)getpid());
    return 0;
}
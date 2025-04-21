/**
 * @file 1_9_uid.c The procedure prints the user ID and group ID
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
    printf("uid:%d, gid:%d\n", getuid(), getgid());
    return 0;
}


/* 字符串探究 */
// void strptr(char* str)
// {
//     str[0] = 'S';
//     str[1] = 'K';
// }
// int main() {
//     char* string = "hello world";
//     char S[5] = {'s','s','s','s','\0'};
//     int a = 4;
//     printf("%s, %#lx, %p\n", string, &string, string);
//     printf("%s, %#lx, %p\n", S, &S, S);
//     strptr(S);
//     printf("%s, %#lx\n", string, &string);
//     printf("%s, %#lx\n", S, &S);
// }
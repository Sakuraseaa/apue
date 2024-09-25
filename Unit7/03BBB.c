/**
 * @file 03BBB.c
 * @author your name (you@domain.com)
 * @brief 是否有方法不使用参数传递，全局变量这两种方法，
 * 将main中的参数argc和argv传递给它所调用的其他函数
 * @version 0.1
 * @date 2024-09-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>

typedef void (*callback)(int, char **);


void print_args();


int main(int argc, char *argv[]) {
    print_args(); // 间接传递 argc 和 argv
    return 0;
}

void print_args() {
    int argc = *(int*)((unsigned long*)main + 1);
    // char **argv = ((char**)((void*)main + 2));
    // for (int i = 0; i < argc; i++) {
    //     printf("Argument %d: %s\n", i, argv[i]);
    // }
    printf("%d", argc);
}

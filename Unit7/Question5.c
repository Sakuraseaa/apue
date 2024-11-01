#include "apue.h"

void e1(void) {
    printf("first exit handler\n");
}

void e2(void) {
    printf("second exit handler\n");
}
typedef void (*Exitfunc)(void);

int my_atexit(Exitfunc f1) // 修改原型
{
    return atexit(f1);
}
int main(void) {
    if (my_atexit(e2) != 0)
        err_sys("can't register e2");
    if (my_atexit(e1) != 0)
        err_sys("can't register e1");
    if (my_atexit(e1) != 0)
        err_sys("can't register e1");
    printf("main is done\n");

    return 0;
}
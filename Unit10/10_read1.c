/**
 * @file 10_read1.c
 * @author your name (you@domain.com)
 * @brief 带有时间限制的读取操作
 * @version 0.1
 * @date 2024-11-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "apue.h"

static void	sig_alrm(int);

int
main(void)
{
	int		n;
	char	line[MAXLINE];

	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		err_sys("signal(SIGALRM) error");

	alarm(10);
	if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
		err_sys("read error");
	alarm(0);

	write(STDOUT_FILENO, line, n);
	exit(0);
}

static void
sig_alrm(int signo)
{
	/* nothing to do, just return to interrupt the read */
}

#include "apue.h"
#include	<setjmp.h>
#include	<signal.h>
#include	<unistd.h>

unsigned int	sleep2(unsigned int);
static void		sig_int(int);
static jmp_buf	env_alrm;

static void
sig_alrm(int signo)
{
	longjmp(env_alrm, 1);
}

unsigned int
sleep2(unsigned int seconds)
{
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		return(seconds);
	if (setjmp(env_alrm) == 0) {
		alarm(seconds);		/* start the timer */
		pause();			/* next caught signal wakes us up */
	}
	return(alarm(0));		/* turn off timer, return unslept time */
}

int
main(void)
{
	unsigned int	unslept;

	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal(SIGINT) error");
	unslept = sleep2(5);
	printf("sleep2 returned: %u\n", unslept);
	exit(0);
}

static void
sig_int(int signo)
{
	int				i, j;
	volatile int	k;

	/*
	 * Tune these loops to run for more than 5 seconds
	 * on whatever system this test program is run.
	 */
	printf("\nsig_int starting\n");
	for (i = 0; i < 300000; i++)
		for (j = 0; j < 40000; j++)
			k += i * j;
	printf("sig_int finished\n");
}

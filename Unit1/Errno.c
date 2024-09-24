#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>


int main(int argc, char* argv[]) {
    fprintf(stderr, "EACCES: %s \n", strerror(EACCES));
    errno = ENOENT;
    perror(argv[0]);
    //exit(0);

    return 0;
}
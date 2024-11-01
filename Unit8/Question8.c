#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // 打开根目录
    DIR *dir = opendir("/");
    if (dir == NULL) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    // 获取目录流的文件描述符
    int fd = dirfd(dir);
    if (fd == -1) {
        perror("dirfd");
        closedir(dir);
        return EXIT_FAILURE;
    }

    // 获取并打印 close-on-exec 标志
    int flags = fcntl(fd, F_GETFD);
    if (flags == -1) {
        perror("fcntl");
        closedir(dir);
        return EXIT_FAILURE;
    }

    printf("Directory FD: %d\n", fd);
    printf("Close-on-exec flag is %s\n", (flags & FD_CLOEXEC) ? "set" : "not set");

    // 读取并打印目录项
    struct dirent *entry;
    printf("Contents of /:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("Found: %s\n", entry->d_name);
    }

    // 关闭目录
    closedir(dir);

    // 重新打开目录并打印关闭标志
    dir = opendir("/");
    if (dir == NULL) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    fd = dirfd(dir);
    if (fd == -1) {
        perror("dirfd");
        closedir(dir);
        return EXIT_FAILURE;
    }

    flags = fcntl(fd, F_GETFD);
    if (flags == -1) {
        perror("fcntl");
        closedir(dir);
        return EXIT_FAILURE;
    }

    printf("Re-opened Directory FD: %d\n", fd);
    printf("Re-opened Close-on-exec flag is %s\n", (flags & FD_CLOEXEC) ? "set" : "not set");

    // 再次读取并打印目录项
    printf("Contents of / after re-opening:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("Found: %s\n", entry->d_name);
    }

    // 关闭目录
    closedir(dir);

    return EXIT_SUCCESS;
}

#include <unistd.h>

void close_fds(int fd[2]) {
    close(fd[0]);
    close(fd[1]);
}
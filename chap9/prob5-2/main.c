
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid, child;
    int fd, status;

    if (argc < 4) {
        fprintf(stderr,
                "Usage: %s output command file\n",
                argv[0]);
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        fd = open(argv[1],
                  O_CREAT | O_TRUNC | O_WRONLY, 0660);

        if (fd == -1) {
            perror("open failed");
            exit(1);
        }

        if (dup2(fd, 1) == -1) {
            perror("dup2 failed");
            close(fd);
            exit(1);
        }

        close(fd);

        execvp(argv[2], &argv[2]);

        fprintf(stderr, "%s: execution failed\n",
                argv[2]);
        exit(1);
    }

    child = wait(&status);

    if (child == -1) {
        perror("wait failed");
        return 1;
    }

    printf("[%d] child process %d end\n",
           (int)getpid(), (int)child);

    return 0;
}

